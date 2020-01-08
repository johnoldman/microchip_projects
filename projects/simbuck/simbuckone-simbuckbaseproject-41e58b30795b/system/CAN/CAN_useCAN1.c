/********************************************************************
 FileName:	CAN_useCAN1.c
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
 File Description:

 Change History:
  Rev   Description
  ----  ------------------------------------------------------------------------

  1.0.0 First release for Simbuck - Based from original file
                                    supplied for the LIBUSB
                                    demo in the Microchip
                                    solutions Library v2011-07-14

********************************************************************/

/* I N C L U D E S **********************************************************/
#include "simbuck_cfg.h"
#include "../HardwareProfile.h"
#include "../HardwareProfile - SimblockDualCAN.h"

#if defined(SIMBUCK_BASEBOARD_4550)
 #include <p18cxxx.h>
 #include "user/user_4550.h"
#endif

#if defined(SIMBLOCK_DUAL_CAN)
#include "GenericTypeDefs.h"
#include "system/CAN/CAN_useCAN1.h"
#include "system/CAN/CAN2515drv.h"

  #if defined(SIMBUCK_BASEBOARD_4550)
    #include "system/CAN/CAN_MsgList.h"
  #endif

 
/* V A R I A B L E S ********************************************************/
#pragma udata
extern CAN_FLAGS CANFlags;
extern CAN_MESSAGES CAN_messages;

/* P R O T T Y P E S ********************************************************/

/* D E C L A R A T I O N S *************************************************/
#pragma code

/****************************************************************************/
/* Configure High Speed CAN Controller							  */

/**
 * Configure the CAN 1 CAN controller
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the entry point for configuring CAn 2
 *
 * Note:            None
*/

void CAN2515_config_CAN_1(unsigned char msg_set)
{

	if(CANFlags.DEBUG)
	 {
	  return;
	 }

	CAN2515_reset();

	// set the baud rate
	// 500kBits@20MHz -> 70%
	CAN2515_write(CAN2515_REG_CNF1, 0x01);
	CAN2515_write(CAN2515_REG_CNF2, 0x92);
	CAN2515_write(CAN2515_REG_CNF3, 0x02);

	// set the baud rate
	// 500kBits@20MHz -> 65%
	//CAN2515_write(CAN2515_REG_CNF1, 0x00);
	//CAN2515_write(CAN2515_REG_CNF2, 0xAD);
	//CAN2515_write(CAN2515_REG_CNF3, 0x06);

	// 125kBits@20MHz -> 62.5%
	//CAN2515_write(CAN2515_REG_CNF1, 0x09); 
	//CAN2515_write(CAN2515_REG_CNF2, 0x90);  
	//CAN2515_write(CAN2515_REG_CNF3, 0x02); 



	// set the TX interrupt pins to high impedance
	// as we are not using them
	CAN2515_write(CAN2515_REG_BFPCTRL, 0x00);

	// set the external RTS pins to high impedance
	// as we are not using them
	CAN2515_write(CAN2515_REG_TXRTSCTRL, 0x00);

	// Set the CAN controller functions
	// We need Clock out pin enabled <2>
	// clock - do NOT need to divide <1:0>

	CAN2515_write(CAN2515_REG_CANCTRL, 0x04);

	// set the interrupts
	// MEERE -> <7>
	// EERIE -> <5>
	// RX1IE -> <1>
	// RX0IE -> <0>

	CAN2515_write(CAN2515_REG_CANINTE, 0x03);

	// Clear interrupt flags
	CAN2515_write(CAN2515_REG_CANINTF, 0x00);

	// Set the transmit priorities for the response messages
	// as High Intermediate <1:0>
	CAN2515_write(CAN2515_REG_TXB0CTRL, 0x02);
	CAN2515_write(CAN2515_REG_TXB1CTRL, 0x02);
	CAN2515_write(CAN2515_REG_TXB2CTRL, 0x02);


       	if(CANFlags.ALLMSGS_CAN_1 == 1)
	 {
	  CAN2515_write(RXB0CTRL, 0x60);	// Receive ALL messages
	  CAN2515_write(RXB1CTRL, 0x60);
	 }
	  else
		 {
		   //CAN2515_write(RXB0CTRL, 0x40);
	  	   //CAN2515_write(RXB1CTRL, 0x40);	 // Receive valid Extended messages
							 // that meet filter criteria
		   CAN2515_write(RXB0CTRL, 0x20);        // Receive valid standard messages
		   CAN2515_write(RXB1CTRL, 0x20);	 // that meet filter criteria

		   //CAN2515_write(RXB0CTRL, 0x00);
		   //CAN2515_write(RXB1CTRL, 0x00);      // Receive ALL valid messages
							 // that meet filter criteria
		}

		/* Configure Receive buffer 0 Mask and Filters */

	  // set up the Receive buffers for the
	  // active messages we are interested in
	  // Only diagnostic:

    if(msg_set == 0)
     {
//	  Nop();
	  CAN2515_write(CAN2515_REG_RXM0SIDH, 0xFD);
          CAN2515_write(CAN2515_REG_RXM0SIDL, 0x00);

	  CAN2515_write(RXM1SIDH, 0xE5);
	  CAN2515_write(RXM1SIDL, 0xC0);

      // High priority
	  // 0x72E Diagnostic response
	  CAN2515_write(RXF0SIDH, 0xFD);
	  CAN2515_write(RXF0SIDL, 0x00);

	  // 0x7E8
	  CAN2515_write(RXF1SIDH, 0x00);
	  CAN2515_write(RXF1SIDL, 0x00);

	  // 0x6E8
	  CAN2515_write(RXF2SIDH, 0xE5);
	  CAN2515_write(RXF2SIDL, 0xC0);

	  //
	  CAN2515_write(RXF3SIDH, 0x00);
	  CAN2515_write(RXF3SIDL, 0x00);

	  //
	  CAN2515_write(RXF4SIDH, 0x00);
	  CAN2515_write(RXF4SIDL, 0x00);

	  CAN2515_write(RXF5SIDH, 0x00);
	  CAN2515_write(RXF5SIDL, 0x00);

	 // end msg_set 0
	}

	if(msg_set == 1)
	 {

	 /* Configure Receive buffer 0 Mask and Filters */

	 // set up the Receive buffers for the
	 // active messages we are interested in

// 	 Nop();
 	 CAN2515_write(CAN2515_REG_RXM0SIDH, 0x7F);
	 CAN2515_write(CAN2515_REG_RXM0SIDL, 0xF0);

	 CAN2515_write(RXM1SIDH, 0x7F);
	 CAN2515_write(RXM1SIDL, 0xF0);
	 // High priority

     // 0x72E Diagnostic response
	 CAN2515_write(RXF0SIDH, 0xE5);
	 CAN2515_write(RXF0SIDL, 0xC0);

	 // 0x12A n
	 CAN2515_write(RXF1SIDH, 0x25);
	 CAN2515_write(RXF1SIDL, 0x40);

	 // 0x160 Key Position and BOO (09MY)
	 //CAN2515_write(RXF2SIDH, 0x2C);
	 //CAN2515_write(RXF2SIDL, 0x00);

	 // 0x3EE Door status
	 CAN2515_write(RXF2SIDH, 0x7D);
	 CAN2515_write(RXF2SIDL, 0xC0);

	 // 0x369 EPB
	 CAN2515_write(RXF3SIDH, 0x6D);
	 CAN2515_write(RXF3SIDL, 0x20);

	 // 0x1D1 VS
	 CAN2515_write(RXF4SIDH, 0x3A);
	 CAN2515_write(RXF4SIDL, 0x20);

	 ///////////////////////////////////////////

	 // 0x83 PRNDL
	 CAN2515_write(RXF5SIDH, 0x10);
	 CAN2515_write(RXF5SIDL, 0x60);

	 // 0x127 Clutch
	 //CAN2515_write(RXF5SIDH, 0x24);
	 //CAN2515_write(RXF5SIDL, 0xE0);

	 //////////////////////////////////////////
	 // end msg_set 1
	}


}

void InitCAN1Messages(void)
{
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

}

#endif
