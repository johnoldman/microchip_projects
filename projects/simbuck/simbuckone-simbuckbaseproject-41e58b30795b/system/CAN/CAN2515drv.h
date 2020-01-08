#ifndef CAN2515DRV_H
#define CAN2515DRV_H

/* I N C L U D E S **********************************************************/
#include "GenericTypeDefs.h"

/** F I R M W A R E   V E R S I O N *******************************************/
#define DEBUG_VERSION_SB_CAN    0x00
#define MINOR_VERSION_SB_CAN    0x01
#define MAJOR_VERSION_SB_CAN    0x00

/* D E F I N I T I O N S ****************************************************/
#define USE_CAN_1               // This must be active as it runs the clock(s)
#define USE_CAN_2               // You can turn this off from here
#define USE_SPI

// define CAN rates
#define CAN2515_125			125
#define CAN2515_250			250
#define CAN2515_500			500
#define CAN2515_1000			1000

// define SJW
#define CAN2515_SJW_1TQ       0x00 /* SJW is 1*TQ */
#define CAN2515_SJW_2TQ       0x40 /* SJW is 2*TQ */
#define CAN2515_SJW_3TQ       0x80 /* SJW is 3*TQ */
#define CAN2515_SJW_4TQ       0xC0 /* SJW is 4*TQ */

// define segments
#define CAN2515_PROP_DELAY		3
#define CAN2515_PHASESEG_1		8
#define CAN2515_PHASESEG_2		8

/* Addresses */
#define CAN2515_REG_CNF1 		0x2A
#define CAN2515_REG_CNF2 		0x29
#define CAN2515_REG_CNF3 		0x28
#define CAN2515_REG_CANCTRL		0x0F
#define CAN2515_REG_CANSTAT		0x0E
#define CAN2515_REG_CANINTE		0x2B
#define CAN2515_REG_CANINTF		0x2C
#define CAN2515_REG_TXB0CTRL            0x30
#define CAN2515_REG_TXB1CTRL            0x40
#define CAN2515_REG_TXB2CTRL            0x50
#define CAN2515_REG_TXRTSCTRL           0x0D
#define CAN2515_REG_BFPCTRL		0x0C
#define CAN2515_REG_RXB0CTRL            0x60
#define CAN2515_REG_RXB1CTRL            0x70
#define CAN2515_REG_EFLG		0x2D

/* Commands */
#define CAN2515_RESET			0xC0
#define CAN2515_READ			0x03
#define CAN2515_READ_RX_BUFF            0x90	// AND the lower nibble for actual command
#define CAN2515_WRITE			0x02
#define CAN2515_LOAD_TX_BUFF            0x40	// AND last 3 bits for actual command
#define CAN2515_RTS_B2			0x84
#define CAN2515_RTS_B1			0x82
#define CAN2515_RTS_B0			0x81
#define CAN2515_READ_STATUS		0xA0
#define CAN2515_RX_STATUS		0xB0
#define CAN2515_BIT_MODIFY		0x05

/* Data */
//#define CAN2515_DUMMY		0x24 /* Dummy BYTE to clock out SPI data     */
#define SPI_CAN_DUMMY		0x90	// dummy byte to read back SPI data
#define CAN2515_MODE_NORMAL   	0x00 /* Normal (send and receive messages)   */
#define CAN2515_MODE_SLEEP    	0x20 /* Wait for interrupt                   */
#define CAN2515_MODE_LOOPBACK 	0x40 /* Testing - messages stay internal     */
#define CAN2515_MODE_LISTEN   	0x60 /* Listen only -- don't send            */
#define CAN2515_MODE_CONFIG   	0x80 /* Configuration (1XX0 0000 is Config)  */


/* Receive buffer */
#define RXB0CTRL                0x60
#define RXB0SIDH                0x61
#define RXB0SIDL                0x62
#define RXB0EID8                0x63
#define RXB0EID0                0x64
#define RXB0DLC                 0x65
#define RXB0D0			0x66
#define RXB0D1			0x67
#define RXB0D2			0x68
#define RXB0D3			0x69
#define RXB0D4			0x6A
#define RXB0D5			0x6B
#define RXB0D6			0x6C
#define RXB0D7			0X6D

#define RXB1CTRL                0x70
#define RXB1SIDH                0x71
#define RXB1SIDL                0x72
#define RXB1EID8                0x73
#define RXB1EID0                0x74
#define RXB1DLC                 0x75
#define RXB1D0			0x76
#define RXB1D1			0x77
#define RXB1D2			0x78
#define RXB1D3			0x79
#define RXB1D4			0x7A
#define RXB1D5			0x7B
#define RXB1D6			0x7C
#define RXB1D7			0x7D


#define CAN2515_REG_RXM0SIDH    0x20
#define CAN2515_REG_RXM0SIDL    0x21
#define RXM0EID8                0x22
#define RXM0EID0                0x23

#define RXM1SIDH                0x24
#define RXM1SIDL                0x25
#define RXM1EID8                0x26
#define RXM1EID0                0x27


/*  Transmit buffer */
#define TXB0CTRL                0x30
#define TXB0SIDH                0x31
#define TXB0SIDL                0x32
#define TXB0EID8                0x33
#define TXB0EID0                0x34
#define TXB0DLC                 0x35
#define TXB0D0			0x36
#define TXB0D1			0x37
#define TXB0D2			0x38
#define TXB0D3			0x39
#define TXB0D4			0x3A
#define TXB0D5			0x3B
#define TXB0D6			0x3C
#define TXB0D7			0x3D


#define TXB1CTRL                0x40
#define TXB1SIDH                0x41
#define TXB1SIDL                0x42
#define TXB1EID8                0x43
#define TXB1EID0                0x44
#define TXB1DLC			0x46
#define TXB1D0			0x46
#define TXB1D1			0x47
#define TXB1D2			0x48
#define TXB1D3			0x49
#define TXB1D4			0x4A
#define TXB1D5			0x4B
#define TXB1D6			0x4C
#define TXB1D7			0x4D


#define TXB2CTRL                0x50
#define TXB2SIDH                0x51
#define TXB2SIDL                0x52
#define TXB2EID8                0x53
#define TXB2EID0                0x54
#define TXB2DLC			0x57
#define TXB2D0			0x56
#define TXB2D1			0x57
#define TXB2D2			0x58
#define TXB2D3			0x59
#define TXB2D4			0x5A
#define TXB2D5			0x5B
#define TXB2D6			0x5C
#define TXB2D7			0x5D


/* Filters */
#define RXF0SIDH        0x00
#define RXF0SIDL        0x01
#define RXF0EID8        0x02
#define RXF0EID0        0x03

#define RXF1SIDH        0x04
#define RXF1SIDL        0x05
#define RXF1EID8        0x06
#define RXF1EID0        0x07

#define RXF2SIDH        0x08
#define RXF2SIDL        0x09
#define RXF2EID8        0x0A
#define RXF2EID0        0x0B

#define RXF3SIDH        0x010
#define RXF3SIDL        0x011
#define RXF3EID8        0x012
#define RXF3EID0        0x013

#define RXF4SIDH        0x014
#define RXF4SIDL        0x015
#define RXF4EID8        0x016
#define RXF4EID0        0x017

#define RXF5SIDH        0x018
#define RXF5SIDL        0x019
#define RXF5EID8        0x01A
#define RXF5EID0        0x01B

/* Filter match */
#define RXF0			0
#define RXF1			1
#define RXF2			2
#define RXF3			3
#define RXF4			4
#define RXF5			5
#define RXF0_ROLL		6
#define RXF1_ROLL		7

/* TXBnCTRL Bits */
#define ABTF			0x40
#define MLOA			0x20
#define TXERR			0x10
#define TXREQ			0x08

/* My stuff **/
#define _STANDARD		0x00
#define _EXTENDED		0x08
#define _B0			0x00
#define _B1			0x01
#define _B2			0x02
#define _B0_B1			0x03
#define _B0_B2			0x04
#define _B1_B2			0x05
#define _B0_B1_B2		0x06

#define RX0                     0x60
#define RX1                     0x70
#define DLC                     0x04
#define D0                      0x05
#define D1                      0x06
#define D2                      0x07
#define D3                      0x08
#define D4                      0x09
#define D5                      0x0A
#define D6                      0x0B
#define D7                      0x0C

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
typedef struct CAN_FLAGS
{

	 unsigned DEBUG:1;                  ///< Switch off Hardware specific features for off-line debugging
         unsigned NOSEND:1;                 ///< Switch off send messages
         unsigned NOSEND_CAN_1:1;           ///< Switch off send messages CAN 1
         unsigned NOSEND_CAN_2:1;           ///< Switch off send messages CAN 2
	 unsigned ALLMSGS_CAN_1:1;          ///< Receive ALL messages CAN bus 1
         unsigned ALLMSGS_CAN_2:1;          ///< Receive ALL messages CAN Bus 2
         unsigned ENABLE_CAN_1:1;           ///< Supress sending user messages CAN 1 - does not stop Ack etc
         unsigned ENABLE_CAN_2:1;           ///< Supress sending user messages CAN 2 - does not stop Ack etc
 	 unsigned int_CAN_1:1;              ///< INT pin set on CAN 2
         unsigned int_CAN_2:1;              ///< INT pin set on CAN 1
	 unsigned cs_CAN_2:1;               ///< Select CAN 2 controller
	 unsigned cs_CAN_1:1;               ///< Select CAN 1 controller
         unsigned proc_CAN_1:1;             ///< process received message CAN 1
	 unsigned proc_CAN_2:1;             ///< process received message CAN 2
	 unsigned proc_CAN_1_0:1;           ///< process received message CAN 1 Buffer 0
	 unsigned proc_CAN_1_1:1;           ///< process received message CAN 1 Buffer 1
         unsigned proc_CAN_2_0:1;           ///< process received message CAN 2 Buffer 0
	 unsigned proc_CAN_2_1:1;           ///< process received message CAN 2 Buffer 1
	 unsigned err_CAN_2:1;              ///< error on CAN 2
	 unsigned err_CAN_1:1;              ///< error on CAN 1
         unsigned snd_tmr_diag:1;           ///< 5ms flag for selftest message transmission
	 unsigned snd_tmr_10:1;             ///< 10ms flag for periodic message transmission
         unsigned snd_tmr_20:1;             ///< 20ms flag for periodic message transmission
         unsigned snd_tmr_50:1;             ///< 30ms flag for periodic message transmission
         unsigned snd_tmr_100:1;            ///< 100ms flag for periodic message transmission
         unsigned snd_tmr_250:1;            ///< 250ms flag for periodic message transmission
         unsigned snd_tmr_500:1;            ///< 500ms flag for periodic message transmission
         unsigned snd_tmr_1000:1;           ///< 1 sec flag for periodic message transmission
       	 unsigned snd_CAN_2_BUFF:1;         ///< send message from CAN 2
	 unsigned snd_CAN_1_BUFF:1;         ///< send message from CAN 1

      	 
} CAN_FLAGS;


/*typedef struct CAN2515_REGS
{
     unsigned char _CANCTRL;
     unsigned char _CANSTAT;
     unsigned char _CANINTF;
     unsigned char _CANINTE;
     unsigned char _ERFLG;
     unsigned char _TX0CTRL;
     unsigned char _TX1CTRL;
     unsigned char _TXRTSCTRL;
     unsigned char _BFPCTRL;
     unsigned char _RX0CTRL;
     unsigned char _RX1CTRL;

    }CAN2515_REGS;
*/

/* P U B L I C  P R O T O T Y P E S *****************************************/
void CAN2515_reset(void);
char CAN2515_read(unsigned char addr);
unsigned char CAN2515_read_rxbuffer(unsigned char);
void CAN2515_write(unsigned char, unsigned char);
unsigned char CAN2515_loadtx(unsigned char);
unsigned char CAN2515_rts(unsigned char);
unsigned char CAN2515_readstatus(void);
unsigned char CAN2515_read_rxstatus(void);
unsigned char CAN2515_bitmodify(unsigned char, unsigned char, unsigned char);
char CAN2515_readRx(unsigned char, unsigned char);
char CAN2515_select(void);
void CAN2515_unselect(void);

#endif //CAN2515DRV_H
