/********************************************************************
 FileName:	user_32.h
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
#ifndef USER_32_H
#define USER_32_H

/* I N C L U D E S **********************************************************/


/* D E F I N I T I O N S ****************************************************/


/* V A R I A B L E S  *******************************************************/


/* S T R U C T U R E S ******************************************************/


/**
 * Structure to maintain a set of User system status flags
*/
typedef struct USER_FLAGS_32
{
    unsigned DEBUG:1;         ///< A Flag to dis-able functionality when testing

} USER_FLAGS_32;



/* P U B L I C  P R O T O T Y P E S *****************************************/

void ProcessUSB(void);
void ProcessUSB_IO(void);
int ProcessUser32(void);

#endif //USER_H

