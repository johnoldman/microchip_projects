/* 
 * File:   hd44780.h
 * Author: rjones
/********************************************************************
 FileName:	4Ddisplay.h
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
#ifndef DISPLAY4D_H
#define DISPLAY4D_H

/** D E F I N E S *************************************************************/
// define the pins 
#define     LCD_SELECT_DATA                 // Select Display Data
#define     LCD_SELECT_INST                 // Select Display Instructions  
#define     LCD_READWRITE                   // Select Read/Write signal
#define     LCD_ENABLE                      // Select Read/Write enable


/** S y s t e m   F u n c t i o n s *******************************************/
void LCD_init(void);



/** P U B L I C  P R O T O T Y P E S ******************************************/



#endif	/* HD44780_H */

