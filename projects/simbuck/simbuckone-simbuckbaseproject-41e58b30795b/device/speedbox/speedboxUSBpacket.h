#ifndef SPEEDBOXUSBPACKET_H
#define SPEEDBOXUSBPACKET_H

/** I N C L U D E S **********************************************************/



/** D E F I N I T I O N S *****************************************************/

/* USB Protocol request messages */
#define DEVICE_VERSION          0x00
#define READ_EEPROM             0x14
#define WRITE_EEPROM            0x15
#define GET_BLOCK               0x16

/* Simbuck Speedbox */
#define READ_INPUTS             0x17
#define READ_RELAYS             0x18
#define SET_RELAY_ON            0x19
#define SET_RELAY_OFF           0x1A

/* uC */
#define READ_PORTS              0x3A

/* MCP 2515*/
#define READ_2515_ADDR          0x4A

/* Simbuck RAM */
#define READ_PATTERN            0x5A

/* SW BOOT */
#define RESET_DEVICE            0xFF

/* USB Protocol request data bytes */


/* USB Potocol response messages */
#define SUCCESS                 0xA1
#define POSITIVE_RESPONSE	0xA2
#define NEGATIVE_RESPONSE	0xAD
#define ERROR_RESPONSE		0xAE
#define NOT_SUPPORTED		0xAF


/** P U B L I C  P R O T O T Y P E S ******************************************/
void ProcessUSB(void);


#endif //SPEEDBOXUSBPACKET_H

