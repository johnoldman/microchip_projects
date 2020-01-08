/********************************************************************
 FileName:	interrupt.c
 Dependencies:	See INCLUDES section
 Processor:	PIC18 and PIC32 USB Microcontrollers
 Hardware:      Simbuck Baseboards and PIC32 USB Starter kit
 Complier:  	Microchip C18 (for PIC18), C32 (for PIC32)
 Company:	Deben Enterprises Limited


 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************************
 File Description: Simbuck base Interrupt routines
 Reference Documents:
  * Title - PIC18F2455/2550/4455/4550 Data Sheet	
  *  Section - 			
  * Title - PIC18F2682/2685/4682/4685 Data Sheet	
  *  Section - 			
  * Title - Simbuck Baseboard4550 User Guide	
  *  Section - 			
  * Title - Simbuck Baseboard4685 User Guide	
  *  Section - 	
 
 Register(s):  
 * INTCON  >> 
 * INTCON1 >> 
 * INTCON2 >> 
 * INTCON  >>
 * INTCON  >>

 Interface Pins
  * Simbuck pin - uC Pin


 Change History:
  Rev   Description
  ----  ------------------------------------------------------------------------

  1.0.0 First release for Simbuck - original file
                                    
*******************************************************************************/


/* I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "simbuck_cfg.h"
#include "../HardwareProfile.h"
#include "system/eeprom/eeprom.h"


#if defined(SIMBUCK_BASEBOARD_4550)
 #include "USB/usb.h"
 #include "USB/usb_function_generic.h"
 #include "processUSBpacket.h"
 #include "user/user_4550.h"
 #include "user/userInits.h"
 
#endif

#if defined(SIMBUCK_BASEBOARD_4685)
  #include "user/user_4685.h"
  #include "user/userInits.h"
  #include "../system/ECAN/ECAN_User.h"
  #include "../system/ECAN/ECAN_MsgList.h"
#endif

/* S I M L I B   I N C L U D E S **********************************************************/
#if defined(SIMBLOCK_STEPDOWN_ADC)
  #include "../system/adc/simbuckadc.h"
#endif

#if defined(SIMBLOCK_DUAL_CAN)
  #include "../HardwareProfile - SimblockDualCAN.h"
  #include "system/CAN/CAN2515drv.h"
  #include "system/CAN/CAN2515user.h"

#endif

#if defined(SIMBUCKSPEEDBOX)
 #include "../device/speedbox/simstat.h"
#endif

/* V A R I A B L E S ********************************************************/
#pragma udata
char temp;
static int tick_count;              ///> counter for periodic interval timer
extern USER_FLAGS USERFlags;

#if defined(SIMBLOCK_DUAL_CAN)
extern CAN_FLAGS CANFlags;
extern CAN_PERF CANPerf;
#endif

#if defined(SIMBUCK_BASEBOARD_4685)
extern ECAN_FLAGS ECANFlags;
#endif

#if defined(SIMBLOCK_STEPDOWN_ADC)
  extern struct ADC_USER ADCUser;
  extern struct ADC_VALUES ADCValues;
  extern struct ADC_VALUES *adc_values_ptr;
#endif

#if defined(SIMBUCKSPEEDBOX)
  extern volatile SIG_CONFIG SIGconfig;
#endif

static char uartbyte;
extern unsigned char bytestoread[];
static short index = 0;
    
/* D E C L A R A T I O N S **************************************************/
#pragma code


    //These are your actual interrupt handling routines.

    /**
    * High Priority Interrupt
    *
    * PreCondition:    All configurations and setup function have been executed
    *
    * Input:           None
    *
    * Output:          None
    *
    * Side Effects:    None
    *
    * Overview:        This function is the entry point for the users High
    *                  priority interrupt(s)
    *
    * Note:            This return will be a "retfie fast", since this is in
    *                  a #pragma interrupt section
    */
	#pragma interrupt YourHighPriorityISRCode
	void YourHighPriorityISRCode()
	{
          int  i;

		//Check which interrupt flag caused the interrupt.
		//Service the interrupt
		//Clear the interrupt flag
		//Etc.
        #if defined(USB_INTERRUPT)
	        USBDeviceTasks();
        #endif

#if defined(SIMBUCKSPEEDBOX)
    // the simulation is based on counting the interrupts.
    // for the generation of the simulation signals
    // CPS, CID, Rev/Min
    

    if (INTCON3bits.INT2IF) {
        SIGconfig.edgeCtr++;

        if ((SIGconfig.SIGn_active & 0x02)) {
            SIGconfig.CID_edges++;
            SIGconfig.cycle_edges++;
        }

        //deal with the Baseline [CPS] signal first
        if (SIGconfig.edgeCtr < (SIGconfig.num_Teeth << 1)) {
            if (SIGconfig.edgeCtr > (SIGconfig.num_GapTeeth << 1) - 1) {

                if (SIGconfig.edgeCtr & 0x01 == 1) {

                    mCPS_Toggle();
                    //T2CONbits.TMR2ON = 1;
                    for (i = 0; i < 21; i++) {
                        Nop();
                    }

                    mCPS_Toggle();
                }

            }
            else {
                mCPS_Hi(); // inverted by the Opto
            }
        } else {
            mREV_Lo(); // inverted by the Opto
            SIGconfig.edgeCtr = 0;
        }

        // Mark the revolution/cycle

        if (SIGconfig.edgeCtr == (SIGconfig.num_Teeth << 1) - 1) {
            mREV_Lo(); // inverted by the Opto
        } else {
            mREV_Hi(); // inverted by the Opto
        }

        Nop();

        // now deal with the CID signal
        // first when is it active
        if (SIGconfig.SIGn_active != 0x02) {
            if (SIGconfig.edgeCtr > (SIGconfig.CID_Start << 1) + SIGconfig.num_GapTeeth) {
                SIGconfig.SIGn_active += 0x02;
                SIGconfig.CID_edges = 0;

            }
        }

        if (SIGconfig.SIGn_active > 0) {
            if (SIGconfig.CID_edges >= SIGconfig.CID_period << 1) {

                // 4 nodes on CAM wheel so 8 transitions max
                if(SIGconfig.CID_transitions > 8)
                {
                 //reset the array index
                 SIGconfig.CID_transitions == 0;
                }
                // the next value is 0x00 so reset array index
                else if(SIGconfig.CID_teeth[SIGconfig.CID_transitions] == 0x00)
                {
                 SIGconfig.CID_transitions == 0;
                }
                //// get the next period tooth count
                else
                {
                SIGconfig.CID_transitions;
                }

                // Test for pin high or low
                //if pin high
                if (mCID == 1) {
                    mCID_Toggle();
                    mCID_inv = !mCID;


                    // use the old code
                    if(SIGconfig.CPS_Type==0)
                    {
                    SIGconfig.CID_period = SIGconfig.CID_PerLo;
                    SIGconfig.CID_edges = 0;
                    }

                    // use the new code
                    if(SIGconfig.CPS_Type==1)
                    {
                    SIGconfig.CID_period = SIGconfig.CID_teeth[SIGconfig.CID_transitions];
                    SIGconfig.CID_edges = 0;
                    }

                }
                else {
                    // if pin low
                    mCID_Toggle();
                    mCID_inv = !mCID;

                    // use the old code
                    if(SIGconfig.CPS_Type==0)
                    {
                    SIGconfig.CID_period = SIGconfig.CID_PerHi;
                    SIGconfig.CID_edges = 0;
                    }

                    // use the new code
                    if(SIGconfig.CPS_Type==1)
                    {
                    SIGconfig.CID_period = SIGconfig.CID_teeth[SIGconfig.CID_transitions];
                    SIGconfig.CID_edges = 0;
                    }


                }

                 // set the index for the next value for the next period
                 SIGconfig.CID_transitions++;

            }

        }
    }

    INTCON3bits.INT1IF = 0;
    INTCON3bits.INT2IF = 0;



#endif

        #if defined(SIMBLOCK_DUAL_CAN)
        // We could use RB On change but this has reliability issues
             /*   if(INTCONbits.RBIF == 1)
                 {
                  temp = PORTB;
                                    
                  if(!(PORTB & CAN_1_INT) > 0)                // MCP2515 INT pin is Active Low
                   {
                    CANFlags.int_CAN_1 = 1;
                    CANPerf.msgs_rcvd_can_1++;
                    Nop();
                   }

                  if(!(PORTB & CAN_2_INT) > 0)               // MCP2515 INT pin is Active Low
                   {
                    CANFlags.int_CAN_2 = 1;
                    CANPerf.msgs_rcvd_can_2++;
                    Nop();
                   }
                  
                  if(PORTB & CAN_INT_MASK == CAN_INT_MASK)
                   {
                    INTCONbits.RBIF = 0;
                   }

                }
          */
          #endif

          #if defined(SIMBLOCK_STEPDOWN_ADC)
            if(PIR1bits.ADIF == 1)
            {
              // clear interrupt flag
              ADCON0bits.ADON = 0;
            }

            PIR1bits.ADIF = 0;
        
          #endif
 
	}
        //This return will be a "retfie fast", since this is in a #pragma interrupt section

   /**
    * Low Priority Interrupt
    *
    * PreCondition:    All configurations and setup function have been executed
    *
    * Input:           None
    *
    * Output:          None
    *
    * Side Effects:    None
    *
    * Overview:        This function is the entry point for the users High
    *                  priority interrupt(s)
    *
    * Note:            This return will be a "retfie", since this is in
    *                  a #pragma interruptlow section
    */

	#pragma interruptlow YourLowPriorityISRCode
	void YourLowPriorityISRCode()
	{
      
	//Check which interrupt flag caused the interrupt.
	//Service the interrupt
	//Clear the interrupt flag
	//Etc.

	   if(INTCONbits.TMR0IF == 1)
	     {
               // Reset the timer
                TMR0H = 0xF4;
                //TMR0L = 0x48;   // 1.002ms measured
                //TMR0L = 0x49;   // 1.002ms measured
               TMR0L = 0x50;     // 998.2ms measured

              /* 'count' the 1ms increments */
	  	if(tick_count == 0)
		 {                
		   tick_count = 60000U;
   		 }
		  tick_count--;

       
              #if defined(SIMBUCK_BASEBOARD_4685)
	       
               if(tick_count%100 == 0)
                {
                 // wait 100ms for ADC to settle
                 if(!ADCUser.power)
                  {
                   ADCUser.power=1;
                   ADCUser.getNext=1;
                   LATD+=1;
                   ADCUser.getCounts=1;
                   Nop();
                  }
                }

               // defined wait time between ADC Acquisitions
               // im milliseconds
               if(ADCUser.adcWait > 0)
               {
                if(tick_count%ADCUser.adcWait == 0)
                 {
                  ADCUser.getNext = 1;
                  ADCUser.getCounts = 1;
                 }
               }
               else
               {
                ADCUser.getNext = 1;
                ADCUser.getCounts = 1;
               }

              #endif
            
	      // Reset the Timer 1ms[4550@20Mhz crystal HSPLL - 48MHz]
              #if defined(SIMBUCK_BASEBOARD_4550)
               if(tick_count%10 == 0)
                {
                  LATEbits.LATE2 = !LATEbits.LATE2;
                }

             #endif


                    #if defined(SIMBLOCK_DUAL_CAN)
                    // if(tick_count%5 == 0)
                    //   {
                        // send 10ms interval CAN messages
                    //    CANFlags.snd_tmr_diag=1;
                    //   }

                      if(tick_count%10 == 0)
                       {
                        // send 10ms interval CAN messages
                        CANFlags.snd_tmr_10=1;
                       }

                       if(tick_count%20 == 0)
                        {
                         // send 20ms interval CAN messages
                         CANFlags.snd_tmr_20=1;
                        }

                       if(tick_count%50 == 0)
                        {
                         // send 50ms interval CAN messages
                         CANFlags.snd_tmr_50=1;
                        }

                       if(tick_count%100 == 0)
                        {
                         // send 100ms interval CAN messages
                         CANFlags.snd_tmr_100=1;
                        }

                       if(tick_count%250 == 0)
                        {
                         // send 250ms interval CAN messages
                         CANFlags.snd_tmr_250=1;
                        }

                       if(tick_count%500 == 0)
                        {
                         // send 500ms interval CAN messages
                         CANFlags.snd_tmr_500=1;
                        }

                       if(tick_count%1000 == 0)
                        {
                         // send 1000ms interval CAN messages
                         CANFlags.snd_tmr_1000=1;
                        }
  
                      #endif

                       // Reset the Interrupt flag
			INTCONbits.T0IF = 0;
                      

	 	 }

        #if defined(DISPLAY_4DSYSTEMS)
           if(PIR1bits.RCIF == 1)
            {
             // Reset the SPI Pin  
             TRISCbits.TRISC7 = INPUT_PIN;

             bytestoread[index] = RCREG;
               // set an error for data overflow
               if(index>20) index=0;
                index++;
            PIR1bits.RCIF=0;
             
             // Reset the SPI Pin
             TRISCbits.TRISC7 = OUTPUT_PIN;
           }

        #endif

            #if defined(SIMBUCK_BASEBOARD_4685)

              if(PIR1bits.RCIF == 1)
               {
                if(RCSTA & 0x06)   // check for errors
                 {
                   RCSTAbits.CREN=0;
                   temp = RCREG;
                   RCSTAbits.CREN=1;
                 }
                else
                  {
                   uartbyte = RCREG;
                   PIR1bits.RCIF=0;

                #if defined(USE_EUSART)
                  USERFlags.RECVUART = 1;
                #endif
                
              }
             }


            #endif


	}	//This return will be a "retfie", since this is in a #pragma interruptlow section



    /**
    * Configure User Interrupts
    *
    * PreCondition:    All configurations and setup function have been executed
    *
    * Input:           None
    *
    * Output:          None
    *
    * Side Effects:    None
    *
    * Overview:        This function is the entry point for the users interrupts
    *                  configuration
    *
    * Note:            None
    *
    */

void InitUserInterrupts(void)
{

	/* Set interrupt priorities ********************************************
         *  1 = High priority
         *  0 = Low priority
        */
	
	//RCONbits.IPEN	 	 = 0;		// PIC16CXXX Compatibility mode
        RCONbits.IPEN 	 	 = 1;		// Enable priority levels on interrupts

	INTCON2bits.TMR0IP     = 0;		// TMR0 Overflow  Low Priority Interrupt
        //INTCON2bits.TMR0IP     = 1;		// TMR0 Overflow  High Priority Interrupt

        //INTCON2bits.RBIP        = 0;          //  RB Port change - low priority
        INTCON2bits.RBIP        = 0;            //  RB Port change - high priority

        //INTCON3bits.INT2IP       = 0;         // INT2 interrupt -  low priority
        //INTCON3bits.INT2IP       = 1;         // INT2 interrupt -  high priority
        
        //INTCON3bits.INT1IP       = 0;         // INT1 interrupt -  low priority
        //INTCON3bits.INT1IP       = 1;         // INT1 interrupt -  high priority

        //IPR1bits.SPPIP             = 1;	// Streaming Parallel Port Read/Write priority
        #if defined(SIMBUCK_BASEBOARD_4685)
          IPR1bits.ADIP              = 1; 	// A/D convertor interrupt priority
        #endif
        IPR1bits.RCIP              = 0; 	// EUSART Receive interrupt priority
        //IPR1bits.TXIP              = 0; 	// EUSART Transmit interrupt priority
        //IPR1bits.SSPIP             = 1; 	// Master Synchrnous Serial Port interrupt priority
        //IPR1bits.CCP1IP            = 1; 	// CCP1 interrupt priority
        //IPR1bits.TMR2IP            = 1;	// TMR2 match interrupt high priority
        //IPR1bits.TMR1IP            = 1;       // TMR1 match interrupt high priority

        //IPR2bits.OSCFIP             = 1;      // enables Oscillator fail interrupt priority
        //IPR2bits.CMIP               = 1;	// enables Comparator Interrupt priority
        //IPR2bits.USBIP              = 1;	// enables USB interrupt priority
        //IPR2bits.EEIP               = 1;      // enables EEPROM/Flash write Operation Interrupt priority
        //IPR2bits.BCLIP              = 1;	// enables Bus Collision Interrupt priority
        //IPR2bits.HLVDIP             = 1;	// enables High/Low voltage detect interrupt priority
        //IPR2bits.TMR3IP             = 1;	// enables TMR3 overflow interrupt priority
        //IPR2bits.CCP2IP             = 1;	// enables CCP2 Interrupt priority

	/* Set interrupt edges *********************************************/
        //INTCON2bits.INTEDG0     = 1;          // Rising edge
        //INTCON2bits.INTEDG1     = 1;          // Rising edge
        //INTCON2bits.INTEDG2     = 1;          // Rising edge


	/* Enable Interrupt(s) **************************************************/
	INTCONbits.TMR0IE	 = 1;		// Enables the TMR0 overflow interrupt
        //INTCONbits.INT0IE        =1;          // Enables INT0
        //INTCONbits.RBIE          = 0;           // Enables RB on Change interrupt

        //INTCON3bits.INT2E        = 1;         // Enables INT2
        //INTCON3bits.INT1E        = 1;         // Enables INT1

        #if !defined(SIMBUCK_BASEBOARD_4685)
         PIE1bits.SPPIE           = 0;          // enables Streaming Parallel Port interrupt
        #endif

        #if defined(SIMBUCK_BASEBOARD_4685)
         PIE1bits.ADIE            = 1;          // enables A/D Convertor interrupt
        #endif
         PIE1bits.RCIE            = 1;  	// enables EUSART Receive interrupt
         //PIE1bits.TXIE            = 1;	// enables EEUSART Transmit interrupt
         //PIE1bits.SSPIE           = 1;	// enables Master Synchronous Serial Port interrupt
         //PIE1bits.CCP1IE          = 1;	// enables CCP1 interrupt
         //PIE1bits.TMR2IE	    = 1;	// enables TMR2 overflow interrupt
         //PIE1bits.TMR1IE          = 1;	// enables TMR1 overflow interrupt

         //PIE2bits.OSCFIE          = 1;	// enables Oscillator fail interrupt
         //PIE2bits.CMIE            = 1;	// enables Comparator Interrupt
         //PIE2bits.USBIE           = 1;	// enables USB interrupt
         //PIE2bits.EEIE            = 1;	// enables EEPROM/Flash write Operation Interrupt
         //PIE2bits.BCLIE           = 1;	// enables Bus Collision Interrupt
         //PIE2bits.HLVDIE          = 1;	// enables High/Low voltage detect interrupt
         //PIE2bits.TMR3IE          = 1;	// enables TMR3 overflow interrupt
         //PIE2bits.CCP2IE          = 1;	// enables CCP2 Interrupt

   /* Clear Interrupt Flag(s) ***************************************************/
	INTCONbits.TMR0IF	 = 0;
        //INTCONbits.INT0IF        = 0;
        //INTCONbits.RBIF          = 0;

        //INTCON3bits.INT2F        = 0;
        //INTCON3bits.INT1F        = 0;

        #if defined(SIMBUCK_BASEBOARD_4550)
         PIR1bits.SSPIF           = 0;
        #endif
        #if defined(SIMBUCK_BASEBOARD_4685)
         PIR1bits.SSPIF           = 1;
        #endif
        PIR1bits.ADIF            = 0;
        PIR1bits.RCIF            = 0;
        PIR1bits.TXIF            = 0;
        //PIR1bits.SSPIF           = 0;
        //PIR1bits.CCP1IF          = 0;
        //PIR1bits.TMR2IF          = 0;
        //PIR1bits.TMR1IF	   = 0;

        //PIR2bits.OSCFIF          = 0;
        //PIR2bits.CMIF            = 0;
        //PIR2bits.USBIF           = 0;
        //PIR2bits.EEIF            = 0;
        //PIR2bits.BCLIF           = 0;
        //PIR2bits.HLVDIF          = 0;
        //PIR2bits.TMR3IF          = 0;
        //PIR2bits.CCP2IF          = 0;

	/* Enable Global Interrupt(s) ********************************************/
	//INTCONbits.GIE	  = 1;		// Enables all high priority interrupts
	//INTCONbits.PEIE	  = 1;		// Enables all low priority peripheral interrupts





/*  TMR0 interrupt	******************************************************

		T0CON	= 0x27
		TMR0ON	= 0
		T08BIT	= 0		// 16 bit
		T0CS	= 1		// instruction cycle
		T0SE	= 0		// low to high increment
		PSA	= 0		// pre scalar assigned
		T0PS2	= 1		// 1:256
		T0PS1	= 1
		T0PS0	= 1
*/

	 T0CONbits.TMR0ON	= 1;		// enables TMR0
	// T0CONbits.TMR0ON	  = 0;		// stops TMR0
	// T0CONbits.T08BIT	  = 1;		// enables 8bit timer
	 T0CONbits.T08BIT       = 0;		// enables 16bit timer
	// T0CONbits.T0CS	  = 1;		// Transition on T0CKI pin
	 T0CONbits.T0CS	    	= 0;		// Internal instruction cycle clock (CLKO)
	// T0CONbits.T0SE	  = 1;		// Increment on high-to-low transition on T0CKI pin
	 T0CONbits.T0SE	     	= 0;		// Increment on low-to-high transition on T0CKI pin
	// T0CONbits.PSA	  = 1;		// Timer0 prescaler is NOT assigned
	 T0CONbits.PSA	     	= 0;		// Timer0 prescaler is assigned

	/* Set clock/edges ******************************************************/
	INTCON2bits.INTEDG2  = 0;

	// Measured data TMR0H/TMR0L = 0 @ 20Mhz
	// T0CON |= 0x07;		// 1:256 	1398.0 mSec max period
	// T0CON |= 0x06;		// 1:128	699.1 mSec max period
	// T0CON |= 0x05;		// 1:64	  	349.5 mSec max period
	// T0CON |= 0x04;		// 1:32	  	174.8 mSec max period
	// T0CON |= 0x03;		// 1:16	  	 87.4 mSec max period
	// T0CON |= 0x02;		// 1:8	   	 43.7 mSec max period
	// T0CON |= 0x01;		// 1:4	  	 21.9 mSec max period
	// T0CON |= 0x00;		// 1:2	  	 10.9 mSec max period

         #if defined(SIMBUCK_BASEBOARD_4550)
	  T0CONbits.T0PS2		= 0;
	  T0CONbits.T0PS1		= 0;
	  T0CONbits.T0PS0		= 1;

          // Reset the Timer 1ms[4550@20Mhz crystal HSPLL - 48MHz]
	  TMR0H = 0xF4;
          //TMR0L = 0x48;   // 1.002ms measured
          //TMR0L = 0x49;   // 1.002ms measured
          TMR0L = 0x50;     // 998.2ms measured
        #endif

        #if defined(SIMBUCK_BASEBOARD_4685)
	  T0CONbits.T0PS2		= 0;
	  T0CONbits.T0PS1		= 0;
	  T0CONbits.T0PS0		= 1;

          // Reset the Timer 1ms[4685@20Mhz crystal HS]
          // TODO: measure this period
	  TMR0H = 0xFB;
          //TMR0L = 0x48;   // 1.002ms measured
          //TMR0L = 0x49;   // 1.002ms measured
          TMR0L = 0x18;     // 998.2ms measured
        #endif


        /*  TMR0 interrupt	******************************************************/

       	// Set up TMR2 interrupt
	/*  TMR2 interrupt	******************************************************

	When:
            TMR2 Prescaler = 1
	    TMR2 PostScalar = 1
            PR2 = 255
                Fosc = 47058.83 Hz [Full Rate USB clock]
                Period = 0.000021 seconds || 0.2 microseconds

		T2CON	= 0x07
			unimplemented	= 0		//
			T2OUTPS3 	= 0		// Timer 2 output PostScale  ||  0000 -> 1:1
			T2OUTPS2 	= 1		// Timer 2 output PostScale
			T2OUTPS1 	= 0		// Timer 2 output PostScale
			T2OUTPS0 	= 0		// Timer 2 output PostScale  ||  1111 -> 1:16
			TMR2ON		= 1             // Timer 2 on/off
			T2CKPS1		= 0		// Timer 2 Prescaler	 || 00 -> 1
			T2CKPS0		= 0		// Timer 2 Prescaler	 || 01 -> 4
										 || 1x -> 16

		TM2 = 253
		PR2 = 255


   /*  TMR2 interrupt	******************************************************/

		//T2CON = 0x10;
		//TMR2 = 00;
		//PR2 = 0xFF;

}

