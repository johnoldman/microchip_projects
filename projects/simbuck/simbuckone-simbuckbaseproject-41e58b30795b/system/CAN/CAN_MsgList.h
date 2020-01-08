/*******************************************************************************
 FileName:	CAN_MsgList.h
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
*******************************************************************************/

#ifndef CAN_MSGLIST_H
#define CAN_MSGLIST_H

/* I N C L U D E S ************************************************************/
#include "GenericTypeDefs.h"

// Definition for the 'send' frame ID

#define CAN1_TEST_FRAME				0x770
#define CAN2_TEST_FRAME				0x771
#define CAN1_TEST_BYTE				0x640
#define CAN2_TEST_BYTE				0x650
#define CAN1_RESULTS_FRAME                      0x775
#define CAN2_RESULTS_FRAME                      0x776

#define CAN1_SELFTEST_FRAME                     0x570
#define CAN2_SELFTEST_FRAME			0x571
#define CAN1_SELF_TEST_RESULTS_FRAME            0x575
#define CAN2_SELF_TEST_RESULTS_FRAME            0x576

#define CAN_TEST_CTRL_FRAME                     0x779

#define CAN_1_MSG_RCV_CNT                       D2
#define CAN_2_MSG_RCV_CNT                       D2
#define RED_LED_SW                              D5


/* P R O T Y P E S **********************************************************/

/**
 * Structure to maintain a set of User system messages requiring response
*/
typedef struct CAN_MESSAGES
{
    // Structure of messages to receive
     WORD CAN1_TEST_FRAME_MSG;          ///< CANID Bus 1 message frame
     WORD CAN2_TEST_FRAME_MSG;          ///< CANID Bus 2 message frame
     WORD CAN1_RESULTS_FRAME_MSG;        ///< CANID Bus 1 message frame
     WORD CAN2_RESULTS_FRAME_MSG;        ///< CANID Bus 1 message frame
     WORD CAN1_SELFTEST_FRAME_MSG;      ///< CANID Bus 1 message frame
     WORD CAN2_SELFTEST_FRAME_MSG;      ///< CANID Bus 2 message frame
     WORD CAN1_SELFRESULTS_FRAME_MSG;    ///< CANID Bus 1 message frame
     WORD CAN2_SELFRESULTS_FRAME_MSG;    ///< CANID Bus 2 message frame
     WORD CAN1_TEST_BYTE_MSG;           ///< CANID Bus 1 message frame
     WORD CAN2_TEST_BYTE_MSG;           ///< CANID Bus 2 message frame
     WORD CAN_TEST_LED_CTRL_MSG;        ///< CANID Bus message frame

} CAN_MESSAGES;





/* D E F I N I T I O N S ****************************************************/
void CAN1SelfTestMessage(void);
void CAN2SelfTestMessage(void);
void CAN1SelfTestResultsMessage(void);
void CAN1ValidateMessage(void);
void CAN2ValidateMessage(void);
void CAN1ValidateResultsMessage(void);

void createCAN1IDList(void);
void createCAN2IDList(void);

#endif //CAN_MSGLIST_H
