/********************************************************************
 FileName:	CAN_ProcessMsgCAN1.c
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

********************************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  ------------------------------------------------------------------------

  1.0.0 First release for Simbuck - Based from original file
                                    supplied for the LIBUSB
                                    demo in the Microchip
                                    solutions Library v2011-07-14

*******************************************************************************/


/* I N C L U D E S **********************************************************/
#include "simbuck_cfg.h"
#include "../HardwareProfile.h"
#include "../HardwareProfile - SimblockDualCAN.h"
#include "user/userInits.h"

#if defined(SIMBUCK_BASEBOARD_4550)
 #include <p18cxxx.h>
 #include "user/user_4550.h"
#endif

#if defined(SIMBLOCK_DUAL_CAN)

#include "GenericTypeDefs.h"
#include "CAN2515user.h"
#include "system/CAN/CAN2515user.h"
#include "system/CAN/CAN2515drv.h"
#include "system/CAN/CAN_MsgList.h"
#include "system/CAN/CAN_ProcessMsgCAN1.h"

#if defined(DISPLAY_4DSYSTEMS)
  #include "display/display4d.h"
  #include "system/serial/simbuckserial.h"
#endif



/* V A R I A B L E S ********************************************************/
#pragma udata
extern USER_FLAGS USERFlags;
extern CAN_FLAGS CANFlags;
extern CAN_MESSAGES CAN_messages;
extern unsigned char CAN_update;
extern unsigned char CAN_1_rcv[14];        ///< CAN 1 Buffer 0
extern unsigned char CAN_3_rcv[14];        ///< CAN 1 Buffer 1
extern unsigned char bytestosend[];


static char count = 0;

int totalvoltsfront = 0;
int totalvoltsrear = 0;

/* P R O T O T Y P E S ********************************************************/

/* D E C L A R A T I O N S *************************************************/
#pragma code

/****************************************************************************/
/* 2515 high level functions												*/
/****************************************************************************/

// RX0 D0 = 0x66
// RX1 D0 = 0x76


void process_CAN_1_msg(void)
{
  WORD CAN1_Id;
  unsigned char temp;

  unsigned char datapos = 0;

  /* test code to know we are receiving messages */
   if(count == 0)
    {
     count = 60000U;
    }
    count--;


    if(CAN_update & 0x01)           // data received into CAN_1_rcv[]
     {
      // Read the buffered frame
      CAN1_Id = CAN_1_rcv[datapos];
      CAN1_Id = CAN1_Id << 8;
      datapos++;
      CAN1_Id += CAN_1_rcv[datapos];

      process_CAN_1_Message(CAN1_Id);
        CANFlags.proc_CAN_1_0 = 0;
     }

     if(CAN_update & 0x02)          // data received into CAN_3_rcv[]
     {
       // Receive the frame
      CAN1_Id = CAN_3_rcv[datapos];
      CAN1_Id = CAN1_Id << 8;
      datapos++;
      CAN1_Id += CAN_3_rcv[datapos];

      process_CAN_1_Message(CAN1_Id);
        CANFlags.proc_CAN_1_1 = 0;
     }

 //  CANFlags.cs_CAN_1 = 1;
 // DeSelect_CAN_1();

  CANFlags.proc_CAN_1 = 0;

}

/* Process the Received messages that we need to extract data from.
 *  We are packing the messages using a simple byte based protocol instead
 *  of the more complex bit-based methodology.
 *
 *  Extract the number of messages received and if greater than
 *  a threshold toggle an LED
*/


void process_CAN_1_Message(WORD Id)
{
  unsigned char framepos;    // position in the receive frame buffer
  unsigned char datapos;     // position in the receive buffer


  /* CAN 1 receives CAN2_TEST_FRAME 0x771
    D3 -> CANPerf.msgs_sent_can_2
    D4 -> CANPerf.msgs_rcvd_can_2

   */

  if(CAN_messages.CAN2_TEST_FRAME_MSG == Id)	// 0x771
   {
    // if we are using the 4D Systems Display
    #if defined(DISPLAY_4DSYSTEMS)
     USERFlags.FRONT=1;
     populateSendBuffer(1);
     USERFlags.SENDUART=1;
     USERFlags.FRONT=0;
    #endif

     if(CAN_update & 0x01)
     {
        //temp = CAN_1_rcv[4];    // DLC
        //temp = CAN_1_rcv[CAN_2_MSG_RCV_CNT];

       if(CAN_1_rcv[CAN_2_MSG_RCV_CNT] > 127)
         {
           mLED_1_On();
         }
       else
          {
            mLED_1_Off();
          }
       }

     if(CAN_update & 0x02)
     {
      if(CAN_3_rcv[CAN_2_MSG_RCV_CNT] > 127)
         {
           mLED_1_On();
         }
       else
          {
            mLED_1_Off();
          }
        }
      }


   if(CAN_messages.CAN2_SELFTEST_FRAME_MSG == Id)	// 0x571
    {
     // if we are using the 4D Systems Display
     #if defined(DISPLAY_4DSYSTEMS)
      USERFlags.REAR=1;
      populateSendBuffer(10);
      USERFlags.SENDUART=1;
      USERFlags.REAR=0;
     #endif
    }


  if(CAN_messages.CAN_TEST_LED_CTRL_MSG == Id)	// 0x779
   {
     if(CAN_update & 0x01)
     {
        //temp = CAN_1_rcv[4];    // DLC
        //temp = CAN_1_rcv[CAN_2_MSG_RCV_CNT];

       if(CAN_1_rcv[RED_LED_SW] != 0)
         {
           mLED_3_Off();            // We are switch the ground so logic is reversed
         }
       else
          {
            mLED_3_On();
          }
       }

     if(CAN_update & 0x02)
     {
      if(CAN_3_rcv[RED_LED_SW] != 0)
         {
           mLED_3_Off();                // We are switch the ground so logic is reversed
         }
       else
          {
            mLED_3_On();
          }
        }
      }
}

#endif
