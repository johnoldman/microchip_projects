/********************************************************************
 FileName:	processUSBpacket.h
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

********************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  -----------------------------------------
 1.0.0 First release for Simbuck - Based from original file
                                    supplied for the LIBUSB
                                    demo in the Microchip
                                    solutions Library v2011-07-14

********************************************************************/

#ifndef PROCESSUSBPACKET_H
#define PROCESSUSBPACKET_H

/* I N C L U D E S **********************************************************/



/* D E F I N I T I O N S *****************************************************/


/* USB Protocol request messages */
#define DEVICE_VERSION          0x00
#define READ_EEPROM             0x14
#define WRITE_EEPROM            0x15
#define GET_BLOCK               0x16
#define GET_FUSES               0x20
#define GET_USER_CONFIG         0x21
#define GET_USER_STATUS         0x22
#define GET_PORTS               0x23


#if defined(SIMBLOCK_DUAL_CAN)
  #define READ_2515_ADDR        0x30
  #define READ_2515_RECV        0x31
  #define WRITE_2515_SEND       0x32

  #define SUPRESS_SEND          0x3E
  #define SSB_SELF_TEST         0x3F
#endif

/* SW BOOT */
#define RESET_DEVICE            0xFF



/* USB Potocol response messages */
#define SUCCESS                 0xA1
#define POSITIVE_RESPONSE	0xA2
#define NEGATIVE_RESPONSE	0xAD
#define ERROR_RESPONSE		0xAE
#define NOT_SUPPORTED		0xAF


/* P U B L I C  P R O T O T Y P E S ******************************************/
void ProcessUSB(void);


#endif //PROCESSUSBPACKET_H
