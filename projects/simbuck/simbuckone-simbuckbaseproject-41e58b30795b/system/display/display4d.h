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
 #define USE_EUSART

// uses the UART for host-display commnnications
#define mInit4DPins()  TRISBbits.TRISB7=0;TRISBbits.TRISB6=1;TRISBbits.TRISB5=0;

// select which  mode
#define GFX          // Graphics processor
//#define SGC        // Serial Slave device

// define the Display UART messages
#define     ACK            0x06        // Positive response
#define     NAK            0x15        // Negative Response

#define     OFF_SCREEN     0x00        // Send data to buffer
#define     ON_SCREEN      0x01        // Echo data to screen
#define     SOLID          0x00        // graphics objects drawn solid
#define     WIRE           0x01        // graphics objects drawn WIREFRAME
#define     TERMINATE      0x00        // "string" termination value

// general commands - may require additional data bytes to function
#define     ERASE          0x45        // Clear Screen
#define     ACTIVE         0x55        // Autobaud - Mandatory to initialise comms
#define     VERSION        0x56        // Request Version data

// graphics commands - will need additional position/colour data
#define     LINE           0x4C        // Draw a line + 10 data
#define     RECTANGLE      0x72        // Draw a rectangle + 10 data
#define     SET_PEN        0x70        // graphics objects drawn solid/wireframe

// text commands
#define     ASCII          0x73        // Draw ASCII Formatted text + variable data

/** S y s t e m   F u n c t i o n s *******************************************/
void CheckComms(void);
void GetVersionData(void);
void drawBaseScreen(void);
void updateDisplay(void);

/** P U B L I C  P R O T O T Y P E S ******************************************/


#endif // DISPLAY4D_H

