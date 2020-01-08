/********************************************************************
 FileName:	user_4550.c
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
  1.0  First release
  
********************************************************************/

/* INCLUDES ******************************************************************/
#include <p18cxxx.h>
#include "simbuck_cfg.h"
#include "HardwareProfile.h"
#include "system/eeprom/eeprom.h"

#include "../USB/usb.h"
#include "../USB/usb_function_generic.h"

#include "processUSBpacket.h"
#include "interrupt.h"
#include "user/user_4550.h"
#include "user/userInits.h"



/* S I M L I B   I N C L U D E S **********************************************************/
#if defined(SIMBLOCK_DUAL_CAN)
  #include "HardwareProfile - SimblockDualCAN.h"
  #include "system/CAN/CAN2515drv.h"
  #include "system/CAN/CAN2515user.h"
  #include "system/CAN/CAN2515utils.h"
  #include "system/CAN/CAN_MsgList.h"
  //#include "../CAN/CAN_ProcessMsgCAN1.h"
#include "../device/EVBattMon/EVBatt_CANframe.h"

    #if defined(USE_CAN_2)
    //  #include "../CAN/CAN_ProcessMsgCAN2.h"
#include "../device/EVBattMon/EVBatt_CANframe.h"
    #endif

#endif

#if defined(SIMBLOCK_BATTMON_ADC)

#endif

/* D I S P L A Y S    I N C L U D E S **********************************************************/
#if defined(DISPLAY_4DSYSTEMS)
  #include "display/display4d.h"
  #include "system/serial/simbuckserial.h"
#endif

#if defined(DISPLAY_BATRON)
  #include "display/sed1565.h"
#endif

#if defined(USE_SPI)
 #include "system/spi/simbuckspi.h"
#endif


#if defined(SIMBUCKSPEEDBOX)
 #include "../device/speedbox/speedboxuser.h"
 #include "../device/speedbox/simstat.h"
 #include "../system/pwm/simbuckpwm.h"
#endif

/* C O M M O N  V A R I A B L E S *****************************************************/
#pragma udata
#if defined(SIMBUCK_BASEBOARD_4550)
extern USER_FLAGS USERFlags;       ///< structure for user semaphore
extern BOOL blinkStatusValid;      ///< Flag to indicate USB status via LED

extern unsigned char OUTPacket[64];
extern unsigned char INPacket[64];
extern USB_HANDLE USBGenericInHandle;
extern USB_HANDLE USBGenericOutHandle;
extern USER_FLAGS USERFlags;


#endif

#if defined(SIMBLOCK_DUAL_CAN)
extern volatile CAN_FLAGS CANFlags;  ///< structure for CAN semaphore
extern CAN_PERF CANPerf;             ///< structure for CAN performance data
#endif

#if defined(DISPLAY_4DSYSTEMS)
  extern unsigned char bytestosend[];
  extern unsigned char bytestoread[];
#endif
  
/* D E C L A R A T I O N S **************************************************/
#pragma code

/**
 * entry point for the users functions
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the entry point for the users functions
 *
 * Note:            None
 */

int ProcessUser(void)
{
    // called from main from the while(1) loop
    // this is where the Users function call(s) go

////////////////////////////////////////////////////////////////////////////////
//              C O R E    T E S T   F U N C T I O N S                        //







//              C O R E    T E S T   F U N C T I O N S                        //
////////////////////////////////////////////////////////////////////////////////

}

/* EOF user.c *****************************************************************/