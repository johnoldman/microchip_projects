/********************************************************************
 FileName:	4Ddisplay.c
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

#if defined(DISPLAY_4DSYSTEMS)
#include "display4d.h"
#include "../system/eeprom/eeprom.h"
#include "../system/serial/simbuckserial.h"
#include "../user/user_4550.h"
#include "user/userInits.h"

/** V A R I A B L E S ********************************************************/
#pragma udata

extern unsigned char bytestosend[];
extern unsigned char bytestoread[];

extern USER_FLAGS USERFlags;

/** P R O T O T Y P E S *******************************************************/


/** D E C L A R A T I O N S **************************************************/
#pragma code


/******************************************************************************/
/* Set the Display hardware communications                                    */

#if defined(SGC)
void CheckComms(void)
{
    bytestosend[0] = ACTIVE;
    WriteBytes(1);
}


void GetVersionData(void)
{

    bytestosend[0] = VERSION;
    bytestosend[1] = ON_SCREEN;

    WriteBytes(2);
 }


void drawBaseScreen(void)
{
   int i;

   for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         }
   
  // clear the screen
   // bytestosend[0]= 0x42;
   // bytestosend[1]= 0xDD;
   // bytestosend[2]= 0xDD;
   //  WriteBytes(3);
     
      
for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         }

     for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         }

     bytestosend[0]= SET_PEN;
     bytestosend[1]= WIRE;
      WriteBytes(2);
   
          for(i=0;i<254;i++)
         {
             Nop();
         }
  
for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         }
  
     // Draw the main frames
    bytestosend[0]=0x72;
    bytestosend[1]=0x00;
    bytestosend[2]=0x00;
    bytestosend[3]=0x00;
    bytestosend[4]=0x20;
    bytestosend[5]=0x01;
    bytestosend[6]=0x3F;
    bytestosend[7]=0x00;
    bytestosend[8]=0xDC;
    bytestosend[9]=0x00;
    bytestosend[10]=0x1F;
    
     WriteBytes(11);

   //  while(USERFlags.serialbyte!=0x06);
 

   for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         }

for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         }

 /*
     // Draw the left frame
    bytestosend[0]=0x72;
    bytestosend[1]=0x00;
    bytestosend[2]=0x30;
    bytestosend[3]=0x00;
    bytestosend[4]=0x21;
    bytestosend[5]=0x00;
    bytestosend[6]=0x30;
    bytestosend[7]=0x00;
    bytestosend[8]=0xDB;
    bytestosend[9]=0x00;
    bytestosend[10]=0x1F;

     WriteBytes(11);

   //  while(USERFlags.serialbyte!=0x06);


   for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         }

for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         }

*/
        // Draw the centre frame
    bytestosend[0]=0x72;
    bytestosend[1]=0x00;
    bytestosend[2]=0x20;
    bytestosend[3]=0x00;
    bytestosend[4]=0x20;
    bytestosend[5]=0x01;
    bytestosend[6]=0x20;
    bytestosend[7]=0x00;
    bytestosend[8]=0xDC;
    bytestosend[9]=0x00;
    bytestosend[10]=0x1F;

     WriteBytes(11);

   //  while(USERFlags.serialbyte!=0x06);


   for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         }

for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         }



  // write the title
    bytestosend[0]=0x73;
    bytestosend[1]=0x0F;
    bytestosend[2]=0x01;
    bytestosend[3]=0x02;
    bytestosend[4]=0xFF;
    bytestosend[5]=0xFF;
    bytestosend[6]=0x50;
    bytestosend[7]=0x52;
    bytestosend[8]=0x4F;
    bytestosend[9]=0x42;
    bytestosend[10]=0x41;
    bytestosend[11]=0x54;
    bytestosend[12]=0x52;
    bytestosend[13]=0x4F;
    bytestosend[14]=0x4E;
    bytestosend[15]=0x00;

    WriteBytes(15);

     for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         } for(i=0;i<254;i++)
         {
             Nop();
         }

     USERFlags.drawbasescreen=0;
}

void updateDiplay(void)
{

    Nop();
       bytestosend[0]=0x72;
    bytestosend[1]=0x00;
    bytestosend[2]=0x00;
    bytestosend[3]=0x00;
    bytestosend[4]=0x20;
    bytestosend[5]=0x01;
    bytestosend[6]=0x3F;
    bytestosend[7]=0x00;
    bytestosend[8]=0xDC;
    bytestosend[9]=0x00;
    bytestosend[10]=0x1F;

     WriteBytes(11);

     while(USERFlags.serialbyte!=0x06);
    Nop();
}
  #endif
#endif  // 
/** EOF 4Ddisplay.c ***********************************************************/
