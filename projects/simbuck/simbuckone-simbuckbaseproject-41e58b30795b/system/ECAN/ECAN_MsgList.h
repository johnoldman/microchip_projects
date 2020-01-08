/*******************************************************************************
 FileName:	ECAN_MsgList.h
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

  1.0.0 First release for Simbuck

*******************************************************************************/
/* 
 * File:   ECAN_MsgList.h
 * Author: rjones
 *
 * Created on 19 October 2012, 13:37
 */

#ifndef ECAN_MSGLIST_H
#define	ECAN_MSGLIST_H

/* I N C L U D E S ************************************************************/
#include "GenericTypeDefs.h"


#define ECAN_SELFTEST_FRAME                     0x677
#define ECAN_SELFTEST_FRAME_BUFFER              TXB0CTRL

#define ECAN_CONTROL_FRAME                      0x678
#define ECAN_CONTROL_FRAME_BUFFER               TXB1CTRL

#define ECAN_DATA_FRAME                         0x679
#define ECAN_DATA_FRAME_BUFFER                  TXB2CTRL


/* Specific messages for EVBattMon */

#define BATT_PACK_1                             0xB1
#define BATT_PACK_2                             0xB2

#define ECAN_DATA_FRAME_1                       0x671
#define ECAN_DATA_FRAME_1_BUFFER                TXB0CTRL

#define ECAN_DATA_FRAME_2			0x672
#define ECAN_DATA_FRAME_2_BUFFER                TXB1CTRL

#define ECAN_DATA_FRAME_3                       0x673
#define ECAN_DATA_FRAME_3_BUFFER                TXB2CTRL

#define ECAN_DATA_FRAME_4			0x674
#define ECAN_DATA_FRAME_4_BUFFER                TXB0CTRL

#define ECAN_DATA_FRAME_5			0x675
#define ECAN_DATA_FRAME_5_BUFFER                TXB1CTRL


/**
 * Structure to maintain a set of User system messages requiring response
*/

typedef struct ECAN_MESSAGES
{
    // Structure of messages to receive
//     WORD ECAN_TEST_FRAME_MSG;           ///< CANID test message frame
//     WORD ECAN_RESULTS_FRAME_MSG;        ///< CANID results message frame
//     WORD ECAN_SELFTEST_FRAME_MSG;       ///< CANID selftest message frame
//     WORD ECAN_SELFRESULTS_FRAME_MSG;    ///< CANID selfttest results message frame
//     WORD ECAN_TEST_BYTE_MSG;            ///< CANID test byte message frame
     WORD ECAN_TEST_LED_CTRL_MSG;        ///< CANID LED control message frame

} ECAN_MESSAGES;


/* P R O T Y P E S ************************************************************/
unsigned long decodeIdentifier(unsigned long, unsigned char);
unsigned long encodeRespondToID(unsigned long, unsigned char);

void setMsgTarget(unsigned char, unsigned long, unsigned char);
void ECANSelfTestMessage(void);
void ECANCtrlMessage(void);
void ECAN_DataFrame_Message(void);

/* Specific messages for EVBattMon */
void ECAN_DataFrame_1_Message(void);
void ECAN_DataFrame_2_Message(void);
void ECAN_DataFrame_3_Message(void);
void ECAN_DataFrame_4_Message(void);
void ECAN_DataFrame_5_Message(void);

#endif	/* ECAN_MSGLIST_H */

