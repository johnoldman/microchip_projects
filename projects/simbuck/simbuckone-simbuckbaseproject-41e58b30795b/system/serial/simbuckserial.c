/********************************************************************
 FileName:		simbuckserial.c
 Dependencies:	See INCLUDES section
 Processor:		PIC18 and PIC32 USB Microcontrollers
 Hardware:		This demo is intended to be used on Simbuck Baseboard4550
 				boards supported by the MCHPFSUSB stack.
 Complier:  	Microchip C18 (for PIC18), C32 (for PIC32)
 Company:		Deben Enterprises Ltd


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

********************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "../simbuck_cfg.h"
#include "../HardwareProfile.h"
#include "GenericTypeDefs.h"
#include "simbuckserial.h"
#include "../system/eeprom/eeprom.h"

#if defined(SIMBUCK_BASEBOARD_4550)
  #include "../user/user_4550.h"
  #include  "../user/userInits.h"       // the size of the buffer is defined in here 
#endif

#if defined(SIMBUCK_BASEBOARD_4685)
  #include "../user/user_4685.h"
  #include  "../user/userInits.h"       // the size of the buffer is defined in here
#endif

#if defined USE_EUSART

/** V A R I A B L E S ********************************************************/
#pragma udata
extern USER_FLAGS USERFlags;
unsigned char uartbyte;
extern unsigned char bytestosend[];        ///< Define Buffer size in userInits
extern unsigned char bytestoread[];        ///< Define Buffer size in userInits

static short buff = 0;
static int voltsfront=0;
static int voltsrear=0;

#if defined(SIMBLOCK_DUAL_CAN)
extern unsigned char CAN_1_rcv[14];        ///< CAN 1 Buffer 0
extern unsigned char CAN_2_rcv[14];        ///< CAN 2 Buffer 0
extern unsigned char CAN_3_rcv[14];        ///< CAN 1 Buffer 1
extern unsigned char CAN_4_rcv[14];        ///< CAN 2 Buffer 1

extern unsigned char CAN_update = 0x00;    ///< State Encoded byte defining which CAN frames have updated

#endif



/** P R O T O T Y P E S ******************************************************/


/** D E C L A R A T I O N S **************************************************/
#pragma code

/********************************************************************************/
/* Level '0' Serial functions 														*/
/* Set up UART			   	*/

void InitUART(void)
{

  // Confirm the EUSART pins as we may be using the
  // SPI bus too!

#if defined(SIMBUCK_BASEBOARD_4550) | defined(SIMBUCK_BASEBOARD_4685)

   //Default all pins to digital

  ADCON1 = 0x0F;      //Digital pins
  CMCON = 0x07;       //Digital pins

  // Confirm the EUSART pins as we may be using the
  // SPI bus too!
   TRISCbits.TRISC7 = INPUT_PIN;     // Rx
   TRISCbits.TRISC6 = OUTPUT_PIN;     // Tx

  

   /**  T X S T A *****************************************************

		CSRC     = 1		// Clock Source select bit
		TX9      = 0		// 9 bit transmit enable [8 bit transmit]
		TXEN 	 = 0		// Transmit enable
		SYNC     = 0		// EUSART mode select bit [asynchronous]
		SENDB    = 0	        // Send break character
		BRGH	 = 0            // High baud rate select bit
		TRMT	 = 0		// Transmit shift register Status bit
		TX9D	 = 0		// 9th bit transmit data
*/
   
            TXSTA = 0x00;
            TXSTAbits.CSRC=0;
            TXSTAbits.SYNC=0;
            TXSTAbits.BRGH=1;

            //TXSTA = 0x20;


   /**  R C S T A *****************************************************

		SPEN     = 1		// Serial Port enable
		RX9        = 0		 // 9 bit receive enable
    		SREN 	 = 0		// Single Receive enable
		CREN     = 1		// Continuous receive enable
    		ADDEN   = 0           // Address detect enable
		FERR	  = 0		// Framing error bit
		OERR	 = 0		// Overrun error bit
		RX9D	  = 0		// 9th bit of received data
 
*/
   
        RCSTA = 0x00;
        RCSTAbits.SPEN = 1;
        RCSTAbits.SREN = 0;
        RCSTAbits.CREN = 1;

       


   /**  B A U D C O N  *****************************************************

		ABDOVF    = 0         // AutoBaud acquisition rollover status bit
		RCIDL        = 0	// Receive Operation Idle status bit
		RXDTP        = 0	// Received data polarty Select bit
		TXCKP        = 0	// Clock and data polarity select bit
		BRG16        = 1	// 16bit baud rate register enable bit
		not used     = 0	//  unimplemented
		WUE           = 0	// Wakeup enable bit
		ABDEN	    = 0        // Autobaud detect enable bit

*/
            BAUDCON = 0x00;
            BAUDCONbits.BRG16=1;
            BAUDCONbits.TXCKP=0;


            #if defined(SIMBUCK_BASEBOARD_4550)
            // 115200 baud@48MHz [4550USB]
            // ((48,000,000/115200)/4)-1 = 103.166
            SPBRG = 0x67;                  
            SPBRGH= 0x00;                
            #endif

            #if defined(SIMBUCK_BASEBOARD_4685)
            // 115200 baud@20MHz [4685ECAN]
            // ((20,000,000/115200)/4)-1 = 42.402
            SPBRG = 0x2A;                  
            SPBRGH= 0x00;                
            #endif


#endif

          
}

//#if defined(DISPLAY_4DSYSTEMS)
void testcomms(void)
{
  char testval;

  #if defined USE_SPI
   // set to a UART Pin
   TRISCbits.TRISC7 = INPUT_PIN;
  #endif

   testval = 0x01;

    TXSTAbits.TXEN = 1;
     TXREG = testval;
      while(!TXSTAbits.TRMT);
  
    TXSTAbits.TXEN = 0;

    #if defined USE_SPI
     // set to a SPI Pin
     TRISCbits.TRISC7 = OUTPUT_PIN;
    #endif
}



char WriteBytes(char sz)
{
   int i;

  #if defined USE_SPI
   // Reset back to a UART Pin
   TRISCbits.TRISC7 = INPUT_PIN;
  #endif

   for(i=0;i<=sz;i++)
    {
      TXSTAbits.TXEN = 1;
       TXREG = bytestosend[i];
        while(!TXSTAbits.TRMT);
    }

     TXSTAbits.TXEN = 0;


    #if defined USE_SPI
     // Reset back to a SPI Pin
     TRISCbits.TRISC7 = OUTPUT_PIN;
    #endif

    return 0;
}




#if defined(SIMBLOCK_DUAL_CAN)
 #if defined(DISPLAY_4DSYSTEMS)
void populateSendBuffer(int offset)
{

    char i = offset;
    char recsz = 8;
    unsigned char tempval=0;

    float val=0;
    float volt=0;

  
    bytestosend[0]=0x3A;
    // Each CAN Receive buffer contains 8 bytes of data
    // byte 1 of the UART send Buffer needs 0x3A for
    // the first byte to allow the display UART to receive
    // the data. This prevents false triggering when the
    // Tx pin is toggled during SPI transmission
    
      for(i=0;i<=recsz;i++)
       {
        bytestosend[i+offset] = CAN_1_rcv[i+5];   // Only want the data bytes
       }
      
      for(i=0;i<=recsz;i++)
       {
        tempval = CAN_1_rcv[i+5];
        val = (float)((tempval/32)+8);
        volt  += val;

        
       }

    
       if(USERFlags.FRONT)
        {
         voltsfront = 0;
         voltsfront = (int)volt;
        }
       if(USERFlags.REAR)
        {
         voltsrear = 0;
         voltsrear = (int)volt;
        }
     
    tempval = voltsfront + voltsrear;
    

    bytestosend[19] = (unsigned char)tempval;


}
  #endif
 #endif
#endif

//#endif
