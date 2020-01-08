/********************************************************************
 FileName:	ECAN_User.h
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

  1.0.0 First release for Simbuck -

********************************************************************/


/* 
 * File:   simbuckecan.h
 * Author: rjones
 *
 * Created on 16 October 2012, 18:38
 */

#ifndef ECAN_USER_H
#define	ECAN_USER_H

/* I N C L U D E S **********************************************************/


/* D E F I N I T I O N S ****************************************************/

#define ECAN_BUS_DIFF      0x20 /* using a differential bus */
#define ECAN_CAPTURE       0x10 /* Enable/disable CAN capture on CCP1 */

// define SJW
#define ECAN_SJW_1TQ       0x00 /* SJW is 1*TQ */
#define ECAN_SJW_2TQ       0x40 /* SJW is 2*TQ */
#define ECAN_SJW_3TQ       0x80 /* SJW is 3*TQ */
#define ECAN_SJW_4TQ       0xC0 /* SJW is 4*TQ */

// define segments
#define ECAN_PROP_DELAY		3
#define ECAN_PHASESEG_1		8
#define ECAN_PHASESEG_2		8


/* Modes */
#define ECAN_MODE_NORMAL   	0x00 /* Normal (send and receive messages)   */
#define ECAN_MODE_SLEEP   	0x20 /* Wait for interrupt                   */
#define ECAN_MODE_LOOPBACK 	0x40 /* Testing - messages stay internal     */
#define ECAN_MODE_LISTEN   	0x60 /* Listen only -- don't send            */
#define ECAN_MODE_CONFIG   	0x80 /* Configuration (1xx_   is Config)     */

/* operational mode
Legacy, Enhanced Legacy, Enhanced FIFO [ECANCON<7:5>: 00, 01, 10]
*/

#define ECAN_LEGACY             0x00
#define ECAN_ENHANCED           0x40
#define ECAN_FIFO               0x80

/* Make it easier to control message send combinations **/
#define _STANDARD		0x00
#define _EXTENDED		0x08
#define _B0			0x00
#define _B1			0x01
#define _B2			0x02
#define _B0_B1			0x03
#define _B0_B2			0x04
#define _B1_B2			0x05
#define _B0_B1_B2		0x06

#define TXB0CTRL                0x0020      // adder
#define TXB1CTRL                0x0010      // adder
#define TXB2CTRL                0x0000      // default - no adder

#define DLC                     0x08

#define D0                      0x06
#define D1                      0x07
#define D2                      0x08
#define D3                      0x09
#define D4                      0x0A
#define D5                      0x0B
#define D6                      0x0C
#define D7                      0x0D

#define ECAN_BUFFER_0           BSEL0bits.B0TXEN
#define ECAN_BUFFER_1           BSEL0bits.B1TXEN
#define ECAN_BUFFER_2           BSEL0bits.B2TXEN
#define ECAN_BUFFER_3           BSEL0bits.B3TXEN
#define ECAN_BUFFER_4           BSEL0bits.B4TXEN
#define ECAN_BUFFER_5           BSEL0bits.B5TXEN

#define ECAN_Tx                 1
#define ECAN_Rx                 0


/* Error States */
#define CAN2515_BUS_OFF                      0x05
#define CAN2515_ERROR_PASSIVE_TX             0x04
#define CAN2515_ERROR_PASSIVE_RX             0x03
#define CAN2515_ERROR_ACTIVE_WITH_TXWARN     0x02
#define CAN2515_ERROR_ACTIVE_WITH_RXWARN     0x01
#define CAN2515_ERROR_ACTIVE                 0x00


/* S T R U C T U R E S ******************************************************/

/**
 * Structure to maintain a set of CAN system status flags
*/
typedef struct ECAN_FLAGS
{

	 unsigned DEBUG:1;                  ///< Switch off Hardware specific features for off-line debugging
	 unsigned ALLMSGS:1;                ///< Receive ALL messages
         unsigned NOSEND:1;                 ///< Supress sending user messages - does not stop Ack etc
 	 unsigned int_CAN:1;                ///< INT pin set on CAN
         unsigned proc_CAN_1:1;             ///< process received message CAN 1
	 unsigned proc_CAN_1_0:1;           ///< process received message CAN 1 Buffer 0
	 unsigned proc_CAN_1_1:1;           ///< process received message CAN 1 Buffer 1
         unsigned err_CAN:1;                ///< error on CAN bus
         unsigned snd_tmr_diag:1;           ///< 5ms flag for selftest message transmission
	 unsigned snd_tmr_10:1;             ///< 10ms flag for periodic message transmission
         unsigned snd_tmr_20:1;             ///< 20ms flag for periodic message transmission
         unsigned snd_tmr_50:1;             ///< 30ms flag for periodic message transmission
         unsigned snd_tmr_100:1;            ///< 100ms flag for periodic message transmission
         unsigned snd_tmr_250:1;            ///< 250ms flag for periodic message transmission
         unsigned snd_tmr_500:1;            ///< 500ms flag for periodic message transmission
         unsigned snd_tmr_1000:1;           ///< 1 sec flag for periodic message transmission
       	 unsigned snd_CAN_BUFF:1;           ///< send message from CAN 


} ECAN_FLAGS;


/* P U B L I C  P R O T O T Y P E S *****************************************/

void ECAN_init(void);
char ECAN_setmode(char);
int ECAN_setbaud(int);
void populateCANBuffer(unsigned int, char, char, char);

#endif	/* ECAN_USER_H */

