/********************************************************************
 FileName:	hd44780.c
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

  1.0.0 First release for Simbuck

*******************************************************************************/


/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "../HardwareProfile - Baseboard4550.h"
#include "simbuck_cfg.h"


#if defined(DISPLAY_HD44780)
#include "hd44780.h"
#include "../user/user_4550.h"
#include "user/userInits.h"

/** V A R I A B L E S ********************************************************/
#pragma udata
extern USER_FLAGS USERFlags;


/** P R O T O T Y P E S *******************************************************/


/** D E C L A R A T I O N S **************************************************/
#pragma code


/******************************************************************************/

#endif
/** EOF hd45780.c ***********************************************************/