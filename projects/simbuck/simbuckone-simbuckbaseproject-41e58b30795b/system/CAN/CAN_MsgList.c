/********************************************************************
 FileName:	CAN_MsgList.c
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

#if defined(SIMBUCK_BASEBOARD_4550)
 #include <p18cxxx.h>
#endif

#if defined(SIMBLOCK_DUAL_CAN)
#include "../HardwareProfile - SimblockDualCAN.h"
#include "GenericTypeDefs.h"
#include "CAN_MsgList.h"
#include "CAN2515drv.h"
#include "CAN2515utils.h"
#include "CAN2515user.h"

/* V A R I A B L E S ********************************************************/
#pragma udata
CAN_MESSAGES CAN_messages;      ///< structure for CAN user semaphore
extern CAN_FLAGS CANFlags;
extern CAN_PERF CANPerf;

/* D E C L A R A T I O N S ****************************************************/
#pragma code

/******************************************************************************/
/* 2515 high level functions						      */
/* Reference document - Microchip Datasheet 210801e			      */
/* Document Title - Stand-Alone CAN Controller with SPI Interface	      */
/* 									      */
/*	Defines the message transmit buffers for the user level CAN layer:    */
/*		CAN1SelfTestMessage					      */
/*		CAN2SelfTestMessage                                           */
/*		CANSefTestResultsMessage                                      */
/*                                      				      */
/*    Helper functions:							      */
/*		createResponseList					      */
/*									      */
/******************************************************************************/


/******************************************************************************/
/* CAN messages -> tx buffer 						      */
/* messages @10ms                                                             */
/******************************************************************************/


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
 * Overview:        This function creates a CAN Frame message definition
 *
 * Note:            None
*/
void CAN1SelfTestMessage(void)
{
	setMsgTarget(CAN2515_REG_TXB0CTRL, CAN1_SELFTEST_FRAME, _STANDARD);

	CAN2515_write(TXB0D0, PORTB);
	CAN2515_write(TXB0D1, CANPerf.msgs_sent_can_1);
	CAN2515_write(TXB0D2, CANPerf.msgs_rcvd_can_2);
	CAN2515_write(TXB0D3, 0x00);
	CAN2515_write(TXB0D4, 0x00);
	CAN2515_write(TXB0D5, 0x00);
	CAN2515_write(TXB0D6, TXB0SIDL);
	CAN2515_write(TXB0D7, TXB0SIDH);

}

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
 * Overview:        This function creates a CAN Frame message definition
 *
 * Note:            None
*/
void CAN2SelfTestMessage(void)
{
	setMsgTarget(CAN2515_REG_TXB1CTRL, CAN2_SELFTEST_FRAME, _STANDARD);

	CAN2515_write(TXB1D0, 0x2F);
	CAN2515_write(TXB1D1, CANPerf.msgs_sent_can_2);
	CAN2515_write(TXB1D2, CANPerf.msgs_rcvd_can_2);
	CAN2515_write(TXB1D3, 0x00);
	CAN2515_write(TXB1D4, 0x00);
	CAN2515_write(TXB1D5, 0x00);
	CAN2515_write(TXB1D6, TXB1SIDL);
	CAN2515_write(TXB1D7, TXB1SIDH);

}

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
 * Overview:        This function creates a CAN Frame message definition
 *
 * Note:            None
*/
void CAN1SelfTestResultsMessage(void)
{
	setMsgTarget(CAN2515_REG_TXB1CTRL, CAN1_SELF_TEST_RESULTS_FRAME, _STANDARD);

	CAN2515_write(TXB1D0, 0x3F);
	CAN2515_write(TXB1D1, 0x00);
	CAN2515_write(TXB1D2, 0x00);
	CAN2515_write(TXB1D3, 0x00);
	CAN2515_write(TXB1D4, 0x00);
	CAN2515_write(TXB1D5, 0x00);
	CAN2515_write(TXB1D6, TXB1SIDL);
	CAN2515_write(TXB1D7, TXB1SIDH);

}

/**
 * Create the response list for the Message Processing
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function creates a response list for Message Processing
 *
 * Note:            None
*/


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
 * Overview:        This function creates a CAN Frame message definition
 *
 * Note:            None
*/
void CAN1ValidateMessage(void)
{
	setMsgTarget(CAN2515_REG_TXB0CTRL, CAN1_TEST_FRAME, _STANDARD);

	CAN2515_write(TXB0D0, PORTB);
	CAN2515_write(TXB0D1, CANPerf.msgs_sent_can_1);
	CAN2515_write(TXB0D2, CANPerf.msgs_rcvd_can_2);
	CAN2515_write(TXB0D3, 0x00);
	CAN2515_write(TXB0D4, 0x00);
	CAN2515_write(TXB0D5, 0x00);
	CAN2515_write(TXB0D6, TXB0SIDL);
	CAN2515_write(TXB0D7, TXB0SIDH);

}

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
 * Overview:        This function creates a CAN Frame message definition
 *
 * Note:            None
*/
void CAN2ValidateMessage(void)
{
	setMsgTarget(CAN2515_REG_TXB0CTRL, CAN2_TEST_FRAME, _STANDARD);

	CAN2515_write(TXB0D0, PORTB);
	CAN2515_write(TXB0D1, CANPerf.msgs_sent_can_2);
	CAN2515_write(TXB0D2, CANPerf.msgs_rcvd_can_2);
	CAN2515_write(TXB0D3, 0x00);
	CAN2515_write(TXB0D4, 0x00);
	CAN2515_write(TXB0D5, 0x00);
	CAN2515_write(TXB0D6, TXB0SIDL);
	CAN2515_write(TXB0D7, TXB0SIDH);

}

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
 * Overview:        This function creates a CAN Frame message definition
 *
 * Note:            None
*/
void CAN1ValidateResultsMessage(void)
{
	setMsgTarget(CAN2515_REG_TXB1CTRL, CAN1_RESULTS_FRAME, _STANDARD);

	CAN2515_write(TXB1D0, 0x3F);
	CAN2515_write(TXB1D1, 0x00);
	CAN2515_write(TXB1D2, 0x00);
	CAN2515_write(TXB1D3, 0x00);
	CAN2515_write(TXB1D4, 0x00);
	CAN2515_write(TXB1D5, 0x00);
	CAN2515_write(TXB1D6, TXB1SIDL);
	CAN2515_write(TXB1D7, TXB1SIDH);

}



// Encode the CANIDs to enable message identification from the SIDH/L Registers
// Improves performance in CAN_ProcessMessageCANx
void createCAN1IDList(void)
{
  CAN_messages.CAN1_TEST_FRAME_MSG  = (encodeRespondToID(CAN1_TEST_FRAME, _STANDARD)) >> 16;
  CAN_messages.CAN1_TEST_BYTE_MSG = (encodeRespondToID(CAN1_TEST_BYTE, _STANDARD)) >> 16;
  CAN_messages.CAN1_RESULTS_FRAME_MSG  = (encodeRespondToID(CAN1_RESULTS_FRAME, _STANDARD)) >> 16;
  CAN_messages.CAN1_SELFTEST_FRAME_MSG = (encodeRespondToID(CAN1_SELFTEST_FRAME, _STANDARD)) >> 16;
  CAN_messages.CAN1_SELFRESULTS_FRAME_MSG = (encodeRespondToID(CAN1_SELF_TEST_RESULTS_FRAME, _STANDARD)) >> 16;
  CAN_messages.CAN_TEST_LED_CTRL_MSG = (encodeRespondToID(CAN_TEST_CTRL_FRAME, _STANDARD)) >> 16;
}


// Encode the CANIDs to enable message identification from the SIDH/L Registers
// Improves performance in CAN_ProcessMessageCANx
void createCAN2IDList(void)
{
  CAN_messages.CAN2_TEST_FRAME_MSG  = (encodeRespondToID(CAN2_TEST_FRAME, _STANDARD)) >> 16;
  CAN_messages.CAN2_TEST_BYTE_MSG = (encodeRespondToID(CAN2_TEST_BYTE, _STANDARD)) >> 16;
  CAN_messages.CAN2_RESULTS_FRAME_MSG  = (encodeRespondToID(CAN2_RESULTS_FRAME, _STANDARD)) >> 16;
  CAN_messages.CAN2_SELFTEST_FRAME_MSG = (encodeRespondToID(CAN2_SELFTEST_FRAME, _STANDARD)) >> 16;
  CAN_messages.CAN2_SELFRESULTS_FRAME_MSG = (encodeRespondToID(CAN2_SELF_TEST_RESULTS_FRAME, _STANDARD)) >> 16;
}

#endif
