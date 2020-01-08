/********************************************************************
 FileName:	CAN2515user.c
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


/* I N C L U D E S **********************************************************/

#include "simbuck_cfg.h"
#include "../HardwareProfile.h"
#include <p18cxxx.h>


/* S I M L I B   I N C L U D E S **********************************************************/
#if defined(SIMBLOCK_DUAL_CAN)
  #include "HardwareProfile - SimblockDualCAN.h"
  #include "system/spi/simbuckspi.h"
  #include "system/CAN/CAN2515drv.h"
  #include "system/CAN/CAN2515user.h"
  #include "system/CAN/CAN2515utils.h"
  #include "system/CAN/CAN_MsgList.h"
  #include "../CAN/CAN_ProcessMsgCAN1.h"

    #if defined(USE_CAN_2)
      #include "../CAN/CAN_ProcessMsgCAN2.h"
    #endif

  #include "CAN2515SelfTest.h"



/* C O M M O N  V A R I A B L E S *****************************************************/
#pragma udata
extern volatile CAN_FLAGS CANFlags;  ///< structure for CAN semaphore
extern CAN_PERF CANPerf;             ///< structure for CAN performance data

#endif

/* D E C L A R A T I O N S **************************************************/
#pragma code


/**
 * CAN Frame message definition
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function creates CAN Frame messages for CAN 1 and CAN 2
 *                  The counts for send and receive are monitored and resent in
 *                  a 3rd CAN frame.
 *
 * Note:            None
*/

void ssbDualCANSelfTest(void)
{

#if defined(SIMBLOCK_DUAL_CAN)

/* S E N D   M E S S A G E   L O O P *****************************************/

	if(CANFlags.snd_tmr_10)
	 {
           //CANFlags.snd_tmr_10=0;

           #if defined(USE_CAN_2)           // Temporary work-around for example!
             CANFlags.snd_tmr_10=1;         // We are using CAN2 at the same rate
           #endif                           // so we don't reset this yet

           // Decide which CAN node to use

            Select_CAN_1();
             CANFlags.cs_CAN_1 = 0;
             CANFlags.snd_CAN_1_BUFF=1;
             // Populate the data as required for the next message
	        CANPerf.msgs_sent_can_1++;         // the request at least
                CAN2515_write(TXB0D2, CANPerf.msgs_sent_can_1);
                CAN2515_write(TXB0D3, CANPerf.msgs_rcvd_can_1);
                  //and send it
                  CANsend(_B0);
             CANFlags.snd_CAN_1_BUFF=0;
             CANFlags.cs_CAN_1 = 1;
            DeSelect_CAN_1();

	 }

       #if defined(USE_CAN_2)
        if(CANFlags.snd_tmr_10)
	 {
           CANFlags.snd_tmr_10=0;

           // Decide which CAN node to use

            Select_CAN_2();
             CANFlags.cs_CAN_2 = 0;
             CANFlags.snd_CAN_2_BUFF=1;
              // Populate the data as required for the next message
              CANPerf.msgs_sent_can_2++;      // the request at least
              CAN2515_write(TXB0D2, CANPerf.msgs_sent_can_2);
              CAN2515_write(TXB0D3, CANPerf.msgs_rcvd_can_2);
                // and send it
                CANsend(_B0);

             CANFlags.snd_CAN_2_BUFF=0;
	     CANFlags.cs_CAN_2 = 1;
            DeSelect_CAN_2();

	 }

        #endif

        // Send the diagnostic message faster than the rest
        // this way the data should aslways be up-to-date
       	if(CANFlags.snd_tmr_diag)
	 {
           CANFlags.snd_tmr_diag=0;

           // Decide which CAN node to use
	    Select_CAN_1();
             CANFlags.cs_CAN_1 = 0;
              // Populate the data as required
              CAN2515_write(TXB1D0, CANPerf.msgs_sent_can_1);
              CAN2515_write(TXB1D1, CANPerf.msgs_rcvd_can_2);
              CAN2515_write(TXB1D2, CANPerf.msgs_missed_can_1);

              CAN2515_write(TXB1D4, CANPerf.msgs_sent_can_2);
              CAN2515_write(TXB1D5, CANPerf.msgs_rcvd_can_1);
              CAN2515_write(TXB1D6, CANPerf.msgs_missed_can_2);

             CANFlags.cs_CAN_1 = 1;
            DeSelect_CAN_1();

            Select_CAN_1();
             CANFlags.cs_CAN_1 = 0;
             CANFlags.snd_CAN_1_BUFF=1;
              CANPerf.msgs_sent_can_1++;         // the request at least
	        CANsend(_B1);
             CANFlags.snd_CAN_1_BUFF=0;
             CANFlags.cs_CAN_1 = 1;
            DeSelect_CAN_1();


	 }


/* E N D  S E N D  M E S S A G E  L O O P ************************************/


/* R E C E I V E   M E S S A G E S *******************************************/


     /* Check to see if we have an interrupt on the 2515 */
    #if defined(USE_CAN_1)
     if((PORTB & CAN_INT_1_MASK) == 0)          // MCP2515 INT pin is Active Low
      {
       CANPerf.msgs_rcvd_can_1++;

        Select_CAN_1();
        CANFlags.cs_CAN_1 = 0;
        CANreceive();
         CAN2515_clearIntFlags();

        CANFlags.cs_CAN_1 = 1;
       DeSelect_CAN_1();

       CANFlags.proc_CAN_1 = 1;                 // best look at the data then
      }
    #endif

    #if defined(USE_CAN_2)
     if((PORTB & CAN_INT_2_MASK) == 0)               // MCP2515 INT pin is Active Low
      {

       CANPerf.msgs_rcvd_can_2++;

      Select_CAN_2();
       CANFlags.cs_CAN_2 = 0;
       CANreceive();
        CAN2515_clearIntFlags();

        CANFlags.cs_CAN_2 = 1;
      DeSelect_CAN_2();

      CANFlags.proc_CAN_2 = 1;                 // best look at the data then

     }
    #endif



/* E N D  R E C E I V E   M E S S A G E S ************************************/


/* P R O C E S S   M E S S A G E S *******************************************/

    #if defined(USE_CAN_1)
        if(CANFlags.proc_CAN_1)
        {
         process_CAN_1_msg();
        }
    #endif


    #if defined(USE_CAN_2)
        if(CANFlags.proc_CAN_2)
        {
         process_CAN_2_msg();
        }
    #endif

/* E N D  P R O C E S S  M E S S A G E S *************************************/

 #endif
}


void InitSelfTest(void)
{
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
             CAN1SelfTestMessage();
	   CANFlags.cs_CAN_1 = 1;
          DeSelect_CAN_1();

          // Replace with the actual message(s) configuration call
          Select_CAN_1();
           CANFlags.cs_CAN_1 = 0;
             CAN1SelfTestResultsMessage();
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
             CAN2SelfTestMessage();
	   CANFlags.cs_CAN_2 = 1;
          DeSelect_CAN_2();
          #else
            #error CAN_1 MUST be enabled for the CAN_2 Clock input
          #endif
        #endif

      #if defined(SIMBLOCK_DUAL_CAN)
        #if defined(USE_CAN_LED)
          InitCANStatusLED();
        #endif
      #endif

}
