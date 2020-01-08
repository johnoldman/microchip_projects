/********************************************************************
 FileName:	CAN2515user.h
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


#ifndef CAN2515_USER_H
#define CAN2515_USER_H

/* I N C L U D E S **********************************************************/
#include "GenericTypeDefs.h"

/* D E F I N I T I O N S ****************************************************/
#define rx0             0x60        ///< Start address of Receive buffer RX0
#define rx1             0x70        ///< Start address of Receive buffer RX1
#define d0              0x05        ///< Data Byte D0 Receive Buffer address Offset
#define d1              0x06        ///< Data Byte D1 Receive Buffer address Offset
#define d2              0x07        ///< Data Byte D2 Receive Buffer address Offset
#define d3              0x08        ///< Data Byte D3 Receive Buffer address Offset
#define d4              0x09        ///< Data Byte D4 Receive Buffer address Offset
#define d5              0x0A        ///< Data Byte D5 Receive Buffer address Offset
#define d6              0x0B        ///< Data Byte D6 Receive Buffer address Offset
#define d7              0x0C        ///< Data Byte D7 Receive Buffer address Offset

/* S T R U C T U R E S ******************************************************/

/**
 * Structure to maintain a set of message counts
 *  for Performance checks and analysis
 */

typedef struct CAN_PERF
{
    unsigned char run_self_test:1;           ///< run hardware self test
    unsigned char msgs_sent_can_1;           ///< messages sent from CAN 1
    unsigned char msgs_rcvd_can_1;           ///< messages received by CAN 1
    unsigned char msgs_sent_can_2;           ///< messages sent from CAN 2
    unsigned char msgs_rcvd_can_2;           ///< messages received by CAN 2
    unsigned char msgs_missed_can_1;         ///< missed messages CAN 1
    unsigned char msgs_missed_can_2;         ///< missed messages CAN 2

} CAN_PERF;



/* P R O T Y P E S **********************************************************/
unsigned char CAN2515_getmode(void);
void CAN2515_setmode(unsigned char);
unsigned char CAN2515_getregister(unsigned char);
void CANreceive(void);
void CANsend(unsigned char);
void CAN2515_readRX(unsigned char);

unsigned long getCANID(unsigned char);

void CAN2515_clearIntFlags(void);
void initialiseCANFlags(void);
unsigned char CAN2515_setcontroller(signed char);

void InitCANStatusLED(void);
//unsigned char CAN2515_updatemap(void);


#endif //CAN2515_USER_H
