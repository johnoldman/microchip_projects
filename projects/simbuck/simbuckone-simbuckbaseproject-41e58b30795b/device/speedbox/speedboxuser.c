
/********************************************************************
 FileName:		speedboxuser.c
 Dependencies:	See INCLUDES section
 Processor:		PIC18 and PIC32 USB Microcontrollers
 Hardware:		This demo is intended to be used on Simbuck Baseboard4550
 				boards supported by the MCHPFSUSB stack.
 Complier:  	Microchip C18 (for PIC18)
 Company:		Deben Enterprises Ltd



 THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  -----------------------------------------
  1.0  First release

*******************************************************************************/

/** INCLUDES ******************************************************************/
#include <p18cxxx.h>
#include "simbuck_cfg.h"
#include "HardwareProfile.h"
#include "system/eeprom/eeprom.h"

#include "../USB/usb.h"
#include "../USB/usb_function_generic.h"

#include "speedboxuser.h"
#include "speedboxUSBpacket.h"
#include "../user/interrupt.h"
#include "simstat.h"

/** S I M L I B   I N C L U D E S *********************************************/
#if defined(SIMBLOCK_DUAL_CAN)
  #include "HardwareProfile - SimblockDualCAN.h"
  #include "system/spi/simbuckspi.h"
  #include "system/CAN/CAN2515drv.h"
  //#include "system/CAN/CAN2515utils.h"
  #include "system/CAN/CAN_MsgList.h"
#endif

/** D I S P L A Y S    I N C L U D E S ****************************************/
#if defined(DISPLAY_4DSYSTEMS)
  #include "display/display4d.h"
  #include "system/serial/simbuckserial.h"
#endif

/** C O M M O N  V A R I A B L E S ********************************************/
#pragma udata
extern volatile SIG_CONFIG SIGconfig;
static BYTE pattern;

extern unsigned char INPacket[64];		//User application buffer for sending IN packets to the host
unsigned char bytestosend[8];
unsigned char bytestoread[8];


#if defined(SIMBLOCK_DUAL_CAN)
  extern volatile CAN_FLAGS CANFlags;

int CAN_1_count;
int CAN_2_count;

#endif

/** D E C L A R A T I O N S ***************************************************/
#pragma code

int ProcessUser(void)
{

    /* check we have not changed pattern */
    pattern = checkSIGpatternSW();

    // If it has changed reset the pattern data
    if(SIGconfig.SIGpattern != pattern)
     {
      GetSIGpattern();
      SIGconfig.SIGpattern = pattern;
     }

    return 0;
}



