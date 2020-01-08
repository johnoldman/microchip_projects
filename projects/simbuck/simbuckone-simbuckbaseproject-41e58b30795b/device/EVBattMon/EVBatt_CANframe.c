/********************************************************************
 FileName:	EVBatt_CANframe.c
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
#include <p18cxxx.h>
#include "simbuck_cfg.h"
#include "../HardwareProfile.h"
#include "../HardwareProfile - SimblockDualCAN.h"
#include "user/userInits.h"


#if defined(SIMBLOCK_DUAL_CAN)
 #include "GenericTypeDefs.h"
 #include "EVBatt_CAN_MsgList.h"
 #include "EVBatt_CANframe.h"
 #include "CAN/CAN2515user.h"
 #include "system/CAN/CAN2515user.h"
 #include "system/CAN/CAN2515drv.h"


#if defined(DISPLAY_4DSYSTEMS)
  #include "display/display4d.h"
  #include "system/serial/simbuckserial.h"
#endif



/* V A R I A B L E S ********************************************************/
#pragma udata
extern USER_FLAGS USERFlags;

#if defined(SIMBLOCK_DUAL_CAN)
 extern CAN_FLAGS CANFlags;
 extern CAN_MESSAGES CAN_messages;
 extern unsigned char CAN_update;
 extern unsigned char CAN_1_rcv[];        ///< CAN 1 Buffer 0
 extern unsigned char CAN_3_rcv[];        ///< CAN 1 Buffer 1
#endif

extern unsigned char OUTPacket[];
unsigned char *USB_ptr;

extern unsigned char bytestosend[];
// create a pointer to the serial transmit buffer
unsigned char *BUFFER_ptr;
static char updated = 0;
int totalvoltsfront = 0;
int totalvoltsrear = 0;

/* P R O T O T Y P E S ********************************************************/

/* D E C L A R A T I O N S *************************************************/
#pragma code


/****************************************************************************/
/* 2515 high level functions						    */
/****************************************************************************/

// RX0 D0 = 0x66
// RX1 D0 = 0x76




void process_CAN_1_msg(void)
{
  WORD CAN1_Id;
  
  unsigned char datapos = 1;

   if(CANFlags.proc_CAN_1)
   {
    if(CANFlags.proc_CAN_1_0)           // data received into CAN_1_rcv[]
     {
      // Read the buffered frame SIDL
      CAN1_Id = CAN_1_rcv[datapos];
       processMessage(1, CAN1_Id);
     
        CANFlags.proc_CAN_1_0 = 0;
     }

     if(CANFlags.proc_CAN_1_1)          // data received into CAN_3_rcv[]
     {
       // Read the buffered frame SIDL
      CAN1_Id = CAN_3_rcv[datapos];
       processMessage(2, CAN1_Id);

        CANFlags.proc_CAN_1_1 = 0;
     }
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

void processMessage(char bus, char CAN_Id)
{
    char dataPos = D1;
    char i;

    BUFFER_ptr = &bytestosend[0];
    USB_ptr = &OUTPacket[0];

    switch(CAN_Id)
    {
        case 0x20:
             BUFFER_ptr++;   // First byte needs to be ':'
             updated += 0x01;
            break;

        case 0x40:
             BUFFER_ptr+=5;
             updated +=2;
            break;

        case 0x60:
            BUFFER_ptr+=9;
            updated +=4;
            break;

        case 0x80:
            BUFFER_ptr+=13;
            updated +=8;
            break;

       case 0xA0:
            BUFFER_ptr+=17;
            updated =+16;
            break;

        default:
            USB_ptr+=2;
            for(i=0;i>14;i++)
             {
              *USB_ptr++ = CAN_1_rcv[i];
             }
            for(i=0;i>14;i++)
             {
              *USB_ptr++ = CAN_3_rcv[i];
             }
            break;
    }

    for(i=0; i<4; i++)
      {
       if(bus <= 2)
        {
         *BUFFER_ptr++ = CAN_1_rcv[dataPos++];
        }
        else
          {
           *BUFFER_ptr++ = CAN_3_rcv[dataPos++];
          }
      }

    if(updated & 0x10)
    {
     updated = 0;
     bytestosend[0] = ':';

     for(i=0;i<21;i++)
     {
      if(bytestosend[i] == 0)
      {
          Nop();
          Nop();
      }
     }


     //USERFlags.SENDUART=1;
    }
    else
       {
        // provide a facility to monitor activity
        bytestosend[0] = updated;
       }

    Nop();
     USERFlags.SENDUART=1;
    Nop();
}



void process_CAN_2_msg(void)
{

}

#endif

