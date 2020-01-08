/********************************************************************
 FileName:	CAN_useCAN2.c
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
#include "system/CAN/CAN_useCAN2.h"
#include "system/CAN/CAN2515drv.h"
#include "system/CAN/CAN_MsgList.h"



/* V A R I A B L E S ********************************************************/
#pragma udata
extern CAN_FLAGS CANFlags;
extern CAN_MESSAGES CAN_messages;

/* P R O T T Y P E S ********************************************************/

/* D E C L A R A T I O N S *************************************************/
#pragma code

/****************************************************************************/
/* 2515 high level functions						*/
/* Reference document - Microchip Datasheet 210801e			*/
/* Document Title - Stand-Alone CAN Controller with SPI Interface	*/
/* 									*/
/*	Implements: 							*/
/*			CAN2515_getmode					*/
/*			CAN2515_setmode					*/
/*									*/
/*    Helper functions:						        */
/*			CAN2515_select					*/
/*			CAN2515_unselect				*/
/*									*/
/****************************************************************************/





/**
 * Configure the CAN 2 CAN controller
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
void CAN2515_config_CAN_2(void)
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

	// 125kBits@20MHz -> 62.5%
	//CAN2515_write(CAN2515_REG_CNF1, 0x09);
	//CAN2515_write(CAN2515_REG_CNF2, 0x90);
	//CAN2515_write(CAN2515_REG_CNF3, 0x02);

	// set the RX interrupt pins to high impedance
	// as we are not using them
	CAN2515_write(CAN2515_REG_BFPCTRL, 0x00);


	// set the external RTS pins to high impedance
	// as we are not using them
	CAN2515_write(CAN2515_REG_TXRTSCTRL, 0x00);

	// Set the CAN controller functions
	// We do not need Clock out pin enabled <2>
	
	CAN2515_write(CAN2515_REG_CANCTRL, 0x00);
	
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


        if(CANFlags.ALLMSGS_CAN_2 == 1)
	 {
	  CAN2515_write(RXB0CTRL, 0x60);
	  CAN2515_write(RXB1CTRL, 0x60);	// Receive ALL messages
	 }
	  else
		 {
		  //CAN2515_write(RXB0CTRL, 0x40);
	  	  //CAN2515_write(RXB1CTRL, 0x40);	 // Receive valid Extended messages
							 // that meet filter criteria
		  CAN2515_write(RXB0CTRL, 0x20);
		  CAN2515_write(RXB1CTRL, 0x20);      // Receive valid standard messages
						    // that meet filter criteria
		  //CAN2515_write(RXB0CTRL, 0x00);
		  //CAN2515_write(RXB1CTRL, 0x00);    // Receive ALL valid messages
						    // that meet filter criteria
		}


	/* Configure Receive buffer 0 Mask and Filters */

	// set up the Receive buffers for the
	// active messages we are interested in
	// These are :
	//
	//

	CAN2515_write(CAN2515_REG_RXM0SIDH, 0x7F);
        CAN2515_write(CAN2515_REG_RXM0SIDL, 0xF0);

	CAN2515_write(RXM1SIDH, 0xE9);
	CAN2515_write(RXM1SIDL, 0xFF);

	// High priority
	// 0x770 
	CAN2515_write(RXF0SIDH, 0x62);
	CAN2515_write(RXF0SIDL, 0x00);

    // 0x7E N
	CAN2515_write(RXF1SIDH, 0x0F);
	CAN2515_write(RXF1SIDL, 0xC0);

    // 0x748 Diagnostic response
	CAN2515_write(RXF2SIDH, 0xE9);
	CAN2515_write(RXF2SIDL, 0x00);

	// 0x749 Diagnostic response
	CAN2515_write(RXF3SIDH, 0xE9);
	CAN2515_write(RXF3SIDL, 0x20);

	// 0x74A Diagnostic response
	CAN2515_write(RXF4SIDH, 0xE9);
	CAN2515_write(RXF4SIDL, 0x40);

	// 0x74B Diagnostic response
	CAN2515_write(RXF5SIDH, 0x62);
	CAN2515_write(RXF5SIDL, 0x00);


}	


void InitCAN2Messages(void)
{
          #if defined(USE_CAN_2)
           #if defined(USE_CAN_1)
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
}

#endif



