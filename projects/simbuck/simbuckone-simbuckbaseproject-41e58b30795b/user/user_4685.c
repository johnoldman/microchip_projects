/********************************************************************
 FileName:		user_4685.c
 Dependencies:	See INCLUDES section
 Processor:	PIC18 and PIC32 USB Microcontrollers
 Hardware:      Simbuck Baseboards and PIC32 USB Starter kit
 Complier:  	Microchip C18 (for PIC18), C32 (for PIC32)
 Company:	Deben Enterprises Limited


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

/* INCLUDES ******************************************************************/
#include "simbuck_cfg.h"
#include "HardwareProfile.h"

#if defined(SIMBUCK_BASEBOARD_4685)
  #include <p18cxxx.h>
  #include "user/user_4685.h"
  #include "user/userInits.h"
#endif

/* S I M L I B   I N C L U D E S **********************************************************/
#if defined(SIMBLOCK_STEPDOWN_ADC)
  #include "../system/adc/simbuckadc.h"
  #include "../system/interrupt/interrupt.h"
#endif

/* D I S P L A Y S    I N C L U D E S **********************************************************/
#if defined(DISPLAY_4DSYSTEMS)
  #include "display/display4d.h"
  #include "system/serial/simbuckserial.h"
#endif

#if defined(DISPLAY_BATRON)
  #include "display/sed1565.h"
#endif

#include "system/GenericTypeDefs.h"
#include "../system/serial/simbuckserial.h"
#include "../system/ECAN/ECAN_User.h"
#include "../system/ECAN/ECAN_MsgList.h"

/* C O M M O N  V A R I A B L E S *****************************************************/
#pragma udata

extern USER_FLAGS USERFlags;        ///< structure for user semaphore
extern ECAN_FLAGS ECANFlags;        ///< structure for ECAN semaphore

#if defined(USE_EUSART)
extern unsigned char uartbyte;      ///< data for UART buffer
extern unsigned char bytestosend[]; ///< buffer for UART data Tx
extern unsigned char bytestoread[]; ///< buffer for UART data Rx
#endif

 #if defined(SIMBLOCK_STEPDOWN_ADC)
  extern struct ADC_USER ADCUser;
  extern char resetCount;
  #endif


#pragma idata
static short byte_count = 0;        ///< UART byte counter
static char msg_cnt = 0;

/* D E C L A R A T I O N S **************************************************/
#pragma code

/**
 * entry point for the users functions
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

void ProcessUser(void)
{
    int start_tm_hi, finish_tm_hi;
    int start_tm_lo, finish_tm_lo;
    
    // called from main from the while(1) loop
    // this is where the Users function call(s) go
  
#if defined(USE_EUSART)
   if(USERFlags.SENDUART)
   {
     USERFlags.SENDUART = 0;   
     testcomms();
   }

   if(USERFlags.RECVUART)
   {
     USERFlags.RECVUART = 0;
     bytestoread[byte_count] = uartbyte;
     byte_count++;

     if(byte_count >= 8)
      {
        USERFlags.RECVBUFF_FULL = 1;
        byte_count = 0;
      }
   }

   if(USERFlags.RECVBUFF_FULL)
   {
      USERFlags.RECVBUFF_FULL = 0;
      // process buffer
   }
#endif

   /* ECAN send example
#if defined(USE_ECAN)
   if(ECANFlags.snd_CAN_BUFF)
    {
     //LATD+=1;
     //temp=TXB0CON;
    
     ECANFlags.snd_CAN_BUFF = 0;

     CANCONbits.WIN2 = 1;       // Make TXn available in Access Bank
     CANCONbits.WIN1 = 1;
     CANCONbits.WIN0 = 1;

     ECANSelfTestMessage();
     ECANCtrlMessage();
     
     TXB0CONbits.TXREQ = 1;
     TXB1CONbits.TXREQ = 1;
     TXB2CONbits.TXREQ = 1;

    }
#endif */

   // ADC StepDown example
    if(ADCUser.power)
     {
      if(ADCUser.getCounts)
       {
        ADCUser.getCounts = 0;
        acquireADC(ADCUser.activeChannel);
        ADCUser.activeChannel+=1;
        // Set flag to store the counts
        ADCUser.storeCounts = 1;
          // A Normal User will likely NOT use 0 indexing
          if(ADCUser.activeChannel == ADCUser.maxChannels)
           {
            Nop();
            // Reset count
            ADCUser.activeChannel = 0;
           }
        // collect metrics
        LATD +=1;
        msg_cnt+=1;
        start_tm_hi = TMR0H;
        start_tm_lo = TMR0L;
       }
      else
         {
          // acquireADC() is 'waiting'
         }
     }


   if(ADCUser.storeCounts)
   {
     ADCUser.storeCounts = 0;
 
     storeADC(ADCUser.updateChannel);
     ADCUser.updateChannel+=1;
 
     if(ADCUser.updateChannel == ADCUser.maxChannels)
      {
       ADCUser.updateChannel = 0;
      }

     // Send message to outside world

     // 10-bit ADC
     if(!ADCUser.mode)
      {
       if(ADCUser.updateChannel%2 == 0)
        {
         ADCUser.loadTx = 1;
        }
       }

      // 8-bit ADC
      if(ADCUser.mode)
       {
       if(ADCUser.updateChannel%3 == 0)
        {
         ADCUser.loadTx = 1;
        }
       }

     // collect metrics
     finish_tm_hi = TMR0H;
     finish_tm_lo = TMR0L;

   }

   // 10-bit ADC requires 2-bytes in CAN frame for each measurement
   //  8-bit ADC requires 1-bytes in CAN frame for each measurement
    
   if(ADCUser.loadTx)
   {
     ADCUser.loadTx = 0;
     {
      #if defined(USE_EUSART)
      if(ADCUser.useUART)
      {
       if(USERFlags.SENDUART==1)
        {
         Nop();
         USERFlags.SENDUART=0;
         //populateSendBuffer(1);
         InitUART();
         WriteBytes(20);

         #if defined(USE_SPI)
          InitSPI();
         #endif
        }
      }
      #endif

      #if defined(USE_ECAN)
      if(ADCUser.useCAN)
      {
       if(ADCUser.updateChannel == 2)
        {
         // load transmit buffer with data
          ECAN_DataFrame_1_Message();
          populateCANBuffer(ECAN_DATA_FRAME_1_BUFFER, D1, 4, 0);
           TXB0CONbits.TXREQ = 1;
           Nop();
        }

        if(ADCUser.updateChannel == 4)
        {
          ECAN_DataFrame_2_Message();
          populateCANBuffer(ECAN_DATA_FRAME_2_BUFFER, D1, 4, 2);
            TXB1CONbits.TXREQ = 1;
        }

        if(ADCUser.updateChannel == 6)
        {
          ECAN_DataFrame_3_Message();
          populateCANBuffer(ECAN_DATA_FRAME_3_BUFFER, D1, 4, 4);
           TXB2CONbits.TXREQ = 1;
        }

       if(ADCUser.updateChannel == 8)
        {
          ECAN_DataFrame_4_Message();
          populateCANBuffer(ECAN_DATA_FRAME_4_BUFFER, D1, 4, 6);
           TXB0CONbits.TXREQ = 1;
        }

        if(ADCUser.updateChannel == 0 )
        {
          ECAN_DataFrame_5_Message();
          populateCANBuffer(ECAN_DATA_FRAME_5_BUFFER, D1, 4, 8);
            TXB1CONbits.TXREQ = 1;
        }

     }
     #endif

    }
   }
}


/** EOF user.c ***************************************************************/

