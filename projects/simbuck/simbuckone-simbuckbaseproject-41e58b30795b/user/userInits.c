/********************************************************************
 FileName:	userInits.c
 Dependencies:	See INCLUDES section
 Processor:	PIC18 and PIC32 USB Microcontrollers
 Hardware:	This demo is intended to be used on Simbuck Baseboard4550
 		boards supported by the MCHPFSUSB stack.
 Complier:  	Microchip C18 (for PIC18), C32 (for PIC32)
 Company:	Deben Enterprises Ltd



 THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  -----------------------------------------
  1.0  First release

********************************************************************

/* I N C L U D E S **********************************************************/

#include "simbuck_cfg.h"
#include "../HardwareProfile.h"
#include "GenericTypeDefs.h"
#include "../system/eeprom/eeprom.h"


#if defined(SIMBUCK_BASEBOARD_4550)
  #include <p18cxxx.h>
  #include "user_4550.h"
  #include "interrupt.h"
  #include "userInits.h"

  //#include "../system/pwm/simbuckpwm.h"
  
#endif

#if defined(SIMBUCK_BASEBOARD_4685)
  #include <p18cxxx.h>
  #include "user_4685.h"
  #include "interrupt.h"
  #include "userInits.h"
  #include "../system/ECAN/ECAN_User.h"
  #include "../system/ECAN/ECAN_MsgList.h"
#endif

#if defined USE_EUSART
  #include "../system/serial/simbuckserial.h"
#endif


#if defined(SIMBLOCK_DUAL_CAN)
  #include "../HardwareProfile - SimblockDualCAN.h"
  #include "../system/spi/simbuckspi.h"
  #include "../system/CAN/CAN2515drv.h"
  #include "../system/CAN/CAN2515user.h"
  
 #if defined(SIMBUCK_BASEBOARD_4550)
  #include "../system/CAN/CAN_MsgList.h"
  #include  "../system/CAN/CAN_useCAN1.h"

     #if defined(USE_CAN_2)
      #include  "../system/CAN/CAN_useCAN2.h"
    #endif
 #endif
#endif


#if defined(DISPLAY_4DSYSTEMS)
  #include "display/display4d.h"
  #include "../system/serial/simbuckserial.h"
#endif

#if defined(DISPLAY_HD44780)
  #include "display/hd44780.h"

#endif

#if defined(SIMBLOCK_STEPDOWN_ADC)
  #include "../system/adc/simbuckadc.h"
#endif

#if defined(SIMBUCKSPEEDBOX)
 #include "../device/speedbox/simstat.h"
 #include "../system/pwm/simbuckpwm.h"
#endif

/* V A R I A B L E S ********************************************************/
#pragma udata

#if defined(SIMBUCK_BASEBOARD_4550)
  extern BOOL blinkStatusValid;
USER_FLAGS USERFlags;
#endif

#if defined(SIMBUCK_BASEBOARD_4685)
  USER_FLAGS USERFlags;
  unsigned char bytestosend[21];
  unsigned char bytestoread[8];
#endif


#if defined(SIMBLOCK_DUAL_CAN)
extern CAN_FLAGS CANFlags;
extern CAN_PERF CANPerf;
#endif

#if defined USE_EUSART
 #if defined(DISPLAY_4DSYSTEMS)
  unsigned char bytestosend[21];
  unsigned char bytestoread[21];
  int bytecount;
  #else
   unsigned char bytestosend[8];
   unsigned char bytestoread[8];
 #endif
#endif

#if defined(DISPLAY_HD44780)


#endif
  
#if defined(SIMBLOCK_STEPDOWN_ADC)
  extern struct ADC_USER ADCUser;
  extern struct ADC_VALUES ADCValues;
  extern unsigned int *adc_values_ptr;
#endif


/* D E C L A R A T I O N S **************************************************/
#pragma code

/* U S E R   I N I T I A L I S A T I O N ************************************/


/**
 * User initialisation of user defined data
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the entry point for the users initialisations
 *
 * Note:            None
*/
void UserInit(void)
{
   char resetCount;

   // start off by setting up any Debug code
 
   // Switch this on if you think there is
   // a reset from within the code
   if(USERFlags.resetCnt)
    {
     resetCount = ReadFromEEPROM(SW_RESET);
     resetCount+=1;
     WriteToEEPROM(resetCount, SW_RESET);
    }
    


/* B A S E B O A R D - 4 5 5 0   I N I T I A L I S A T I O N *****************/

      /* Set any default user configuration here */
      #if defined(SIMBUCK_BASEBOARD_4550)
        // debugging switch
        USERFlags.DEBUG = 0;
        USERFlags.slowUpdate = 1;
        USERFlags.fastUpdate = 1;
        
      	ADCON0 = 0x00;			// Turn off A/D
	ADCON1 = 0x0F;			// use as a digital input/output

	CCP1CONbits.CCP1M3 = 0;         // Switch off comparators
	CCP1CONbits.CCP1M2 = 0;
        CCP1CONbits.CCP1M1 = 0;
        CCP1CONbits.CCP1M0 = 0;

        TRISD = 0x00;                   // clear PORTD
        LATD =  0x00;
        PORTD = 0x00;

        /* enable LED on RE2 */
        TRISEbits.TRISE2 = 1;
        LATEbits.LATE2 = 1;

        /* Initialise User Structures */
        InitStructs();

        /* Initialise board LEDs */
        mInitAllLEDs();

       //Blink the USB state on the LEDs.
      #if defined(USE_USB_LED)
       blinkStatusValid = TRUE;
      #endif

       #if defined USE_EUSART
        InitUART();
        USERFlags.SENDUART = 0;
       #endif

      #if defined USE_PWM
       PWM_init();
        setPWMDutyCycle(1, 0x01);
        setPWMDutyCycle(2, 0x01);
      #endif

    #endif

/* B A S E B O A R D - 4 6 8 5  I N I T I A L I S A T I O N *****************/

       #if defined(SIMBUCK_BASEBOARD_4685)
        // debugging switch
        USERFlags.DEBUG = 0;
        USERFlags.resetCnt = 0;

        /* Initialise User Structures */
        InitStructs();

       #if defined USE_EUSART
        InitUART();
        USERFlags.SENDUART = 0;
       #endif

      #if defined(USE_ECAN)
        ECAN_init();
      #endif

  #endif

  #if defined(SIMBLOCK_STEPDOWN_ADC)

       ADC_init();
       // Clear ADC measurement register
       ADRESH = 0;
       ADRESL = 0;

    // if we want to send the data via CAN
    #if defined(USE_ECAN)
       // Make CAN Tx registers available in Access Bank
       CANCONbits.WIN2 = 1;       
       CANCONbits.WIN1 = 1;
       CANCONbits.WIN0 = 1;

       // load a frame for testing
       //ECANCtrlMessage();
       ECAN_DataFrame_1_Message();
       ECAN_DataFrame_2_Message();
       ECAN_DataFrame_3_Message();
       ECAN_DataFrame_4_Message();
       ECAN_DataFrame_5_Message();

    #endif
      
  #endif

 


/* S I M B U C K  D E V I C E   4 6 8 5   I N I T I A L I S A T I O N *********/

        #if defined(SIMBUCK_DEVICE_4685)
          UserDeviceInit();
          /* Initialise User Structures */
          InitStructs();
        #endif




/* S I M B L O C K   I N I T I A L I S A T I O N ******************************/


       /* set up SPI comms for the 2515 Controllers */
      #if defined(SIMBLOCK_DUAL_CAN)
        mInitCANPins();
        // make sure nothing is selected
        DeSelect_CAN_1();
        DeSelect_CAN_2();

        InitSPI();

        // now we set up the CAN controllers
        #if defined(USE_CAN_1)
        Select_CAN_1();
         CANFlags.cs_CAN_1 = 0;
	  CAN2515_setcontroller(0);
         CANFlags.cs_CAN_1 = 1;
        DeSelect_CAN_1();

        // Replace with the actual message(s) configuration call
          Select_CAN_1();
           CANFlags.cs_CAN_1 = 0;
             CAN1ValidateMessage();
	   CANFlags.cs_CAN_1 = 1;
          DeSelect_CAN_1();

          // Replace with the actual message(s) configuration call
          Select_CAN_1();
           CANFlags.cs_CAN_1 = 0;
             CAN1ValidateResultsMessage();
	   CANFlags.cs_CAN_1 = 1;
          DeSelect_CAN_1(); 
        #endif

        #if defined(USE_CAN_2)
          #if defined(USE_CAN_1)
           Select_CAN_2();
         CANFlags.cs_CAN_2 = 0;
	  CAN2515_setcontroller(1);
         CANFlags.cs_CAN_2 = 1;
        DeSelect_CAN_2();

        // Replace with the actual message(s) configuration call
         Select_CAN_2();
          CANFlags.cs_CAN_2 = 0;
            CAN2ValidateMessage();
	   CANFlags.cs_CAN_2 = 1;
          DeSelect_CAN_2();

         Select_CAN_2();
          CANFlags.cs_CAN_2 = 0;
            CAN2SelfTestMessage();
	   CANFlags.cs_CAN_2 = 1;
          DeSelect_CAN_2();

          #else
            #error CAN_1 MUST be enabled for the CAN_2 Clock input
          #endif

          // create the Response IDs
          createCAN1IDList();
          createCAN2IDList();

        #endif

        #if defined(USE_CAN_LED)
          InitCANStatusLED();
        #endif

      #endif


/* D I S P L A Y   I N I T I A L I S A T I O N ********************************/


      #if defined(DISPLAY_BATRON)
        BATRON_CS_disable();
        mInitSED1565();
        BATRON_CS_enable();
         SED1565HardReset();
        BATRON_CS_disable();

        SED1565Bootstrap_display();
        batron_status = SED1565ReadStatus();
        Nop();
       // SED1565ScreenTest();
      #endif

    #if defined(DISPLAY_4DSYSTEMS)

      InitUART();
     
      testcomms();

     for(bytecount=20;bytecount>=0;bytecount--)
      {
       bytestosend[bytecount] = 0xFF;
      }
    
      WriteBytes(20);


      // If using SPI we need to reset the peripheral
      #if defined(SIMBLOCK_DUAL_CAN)
       InitSPI();
      #endif
    
    
 #endif

/* D E V I C E   I N I T I A L I S A T I O N ********************************/

 #if defined(SIMBUCKSPEEDBOX)
       mInit_OPTO();
 #endif

        // set up Interrupts
        InitUserInterrupts();
      

 /* Enable Global Interrupt(s) ********************************************/
     INTCONbits.GIE	 	 = 1;	// Enables all high priority interrupts
     INTCONbits.PEIE	 	 = 1;	// Enables all low priority peripheral interrupts
       

}//end UserInit


/**
 * User initialisation of defined structures
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the entry point for the users functions
 *
 * Note:            None
*/
void InitStructs(void)
{
/* U S E R ******************************************************************/

    USERFlags.DEBUG=0;
    USERFlags.resetCnt=1;
    USERFlags.cpuload = 0;
    USERFlags.fastUpdate = 1;
    USERFlags.slowUpdate = 1;

    
   #if defined(DISPLAY_4DSYSTEMS)
    USERFlags.FRONT=0;
    USERFlags.REAR=0;
   #endif

   #if defined(USE_EUSART)
    USERFlags.SENDUART=0;
    USERFlags.RECVUART=0;
    USERFlags.RECVBUFF_FULL=0;
   #endif


/* S I M B L O C K S ********************************************************/
  
#if defined(SIMBLOCK_DUAL_CAN)
    
    CANFlags.DEBUG=0;
    CANFlags.NOSEND=0;
    CANFlags.NOSEND_CAN_1=0;
    CANFlags.NOSEND_CAN_2=0;
    CANFlags.ALLMSGS_CAN_1=1;          ///< Receive ALL CAN messages
    CANFlags.ALLMSGS_CAN_2=0;          ///< Receive ALL CAN messages
    CANFlags.ENABLE_CAN_1=0;
    CANFlags.ENABLE_CAN_2=0;
    CANFlags.int_CAN_1=0;
    CANFlags.int_CAN_2=0;
    CANFlags.cs_CAN_2=1;
    CANFlags.cs_CAN_1=1;
    CANFlags.proc_CAN_1=0;
    CANFlags.proc_CAN_2=0;
    CANFlags.proc_CAN_1_0=0;
    CANFlags.proc_CAN_1_1=0;
    CANFlags.proc_CAN_2_0=0;
    CANFlags.proc_CAN_2_1=0;
    CANFlags.err_CAN_2=0;
    CANFlags.err_CAN_1=0;
    CANFlags.snd_tmr_diag=1;
    CANFlags.snd_tmr_10=0;
    CANFlags.snd_tmr_20=0;
    CANFlags.snd_tmr_50 =0;
    CANFlags.snd_tmr_100=0;
    CANFlags.snd_tmr_250=0;
    CANFlags.snd_tmr_500=0;
    CANFlags.snd_tmr_1000=0;
    CANFlags.snd_CAN_2_BUFF=0;
    CANFlags.snd_CAN_1_BUFF=0;


    CANPerf.run_self_test=0;
    CANPerf.msgs_sent_can_1=0;
    CANPerf.msgs_rcvd_can_1=0;
    CANPerf.msgs_sent_can_2=0;
    CANPerf.msgs_rcvd_can_2=0;
    CANPerf.msgs_missed_can_1=0;
    CANPerf.msgs_missed_can_2=0;

#endif


#if defined(SIMBLOCK_STEPDOWN_ADC)

    ADCUser.DEBUG=0;
    ADCUser.power=0;
    ADCUser.mode=0;
    ADCUser.getNext=0;
    ADCUser.getCounts=0;
    ADCUser.storeCounts=0;
    ADCUser.loadTx=0;
    ADCUser.sendTx=0;
    ADCUser.sendTx0=0;
    ADCUser.sendTx1=0;
    ADCUser.sendTx2=0;
    ADCUser.useCAN=0;

    #if defined(USE_ECAN)
     ADCUser.useCAN=1;
    #endif

    ADCUser.useUART=0;
    #if defined(USE_EUSART)
     ADCUser.useUART=1;
    #endif

    ADCUser.updateChannel=0;
    ADCUser.activeChannel=0;
    ADCUser.maxChannels = MAX_CHANNELS;
    ADCUser.adcWait=1;

#endif


/* D I S P L A Y S **********************************************************/

  #if defined(DISPLAY_4DSYSTEMS)
    #if defined(SGC)
      SGCFlags.DEBUG=0;
      SGCFlags.RESET_display=1;
      SGCFlags.TIMEOUT_display=0;
      SGCFlags.COMMS_confirmed=0;
      SGCFlags.drawbasescreen=0;
      SGCFlags.displayReady=0;
      SGCFlags.ticCnt=0;
      SGCFlags.serialbyte=0;
      SGCFlags.receivedBytes=0;
#endif

   #endif

      /* D E V I C E   I N I T I A L I S A T I O N ********************************/

 #if defined(SIMBUCKSPEEDBOX)
       InitSIGconfig();
 #endif
}

