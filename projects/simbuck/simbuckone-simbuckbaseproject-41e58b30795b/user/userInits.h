/********************************************************************
 FileName:	userInits.h
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

#ifndef USERINITS_H
#define USERINITS_H

/* I N C L U D E S **********************************************************/
#if defined(DISPLAY_4DSYSTEMS)
  #include "display/display4d.h"
  #include "system/serial/simbuckserial.h"
#endif

#if defined(DISPLAY_HD44780)
  #include "display/hd44780.h"

#endif

/* D E F I N I T I O N S ****************************************************/


/* S T R U C T U R E S ******************************************************/

/**
 * Structure to maintain a set of User system status flags
*/

typedef struct USER_FLAGS
{
    unsigned DEBUG:1;       ///< A Flag to dis-able functionality when testing
    unsigned cpuload:1;     ///< A Flag to estimate load
    unsigned resetCnt:1;    ///< A Flag to enable functionality to test for SW reset
    unsigned slowUpdate:1;  ///< A Flag to trigger slow update of hot Application data structure
    unsigned fastUpdate:1;  ///< A Flag to trigger fast update of hot Application data structure

    #if defined(USE_EUSART)
    unsigned SENDUART:1;
    unsigned RECVUART:1;
    unsigned RECVBUFF_FULL:1;
    #endif

    #if defined(DISPLAY_4DSYSTEMS)
    unsigned FRONT:1;
    unsigned REAR:1;
    #endif

    #if defined(DISPLAY_HD44780)
    unsigned USE_8BIT:1;
    #endif

} USER_FLAGS;


/* P U B L I C  P R O T O T Y P E S *****************************************/
void UserInit(void);
void InitStructs(void);
void InitUserInterrupts(void);

// this needs to move to the ECAN files
//void populateCANBuffer(int buff, char start, char len, char ch);

#endif //USERINITS_H
