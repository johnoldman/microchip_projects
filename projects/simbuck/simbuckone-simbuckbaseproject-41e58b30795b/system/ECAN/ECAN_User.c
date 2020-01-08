/********************************************************************
 FileName:	ECAN_User.c
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

********************************************************************************
 File Description: ECAN module

 Document Reference:
  * Title - PIC18F2682/2685/4682/4685 Data Sheet
  *  Section - Section 23 ECAN Technology
  * Title - Simbuck Baseboard4685 User Guide
  *  Section - 

 Register(s):


 Interface Pins
  * Simbuck pin - uC Pin

 Change History:
  Rev   Description
  ----  ------------------------------------------------------------------------

  1.0.0 First release for Simbuck

********************************************************************/

/*
 * File:   simbuckecan.c
 * Author: rjones
 *
 * Created on 16 October 2012, 18:38
 */


/* I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "simbuck_cfg.h"
#include "HardwareProfile.h"
#include "ECAN_User.h"
#include "ECAN_MsgList.h"

/* S I M L I B   I N C L U D E S **********************************************************/
#if defined(SIMBLOCK_STEPDOWN_ADC)
  #include "../system/adc/simbuckadc.h"
#endif


/* V A R I A B L E S **********************************************************/
#pragma udata

/* P R O T 0 T Y P E S ********************************************************/


/* D E C L A R A T I O N S ****************************************************/
#pragma code

void ECAN_init(void)
{
    char mode;
    int baud = 500;

    // Set TRISB<3>
    TRISBbits.RB3 = 1;

   /** Initalise ECAN
    *   1: Set Configuration mode
    *   2: Select ECAN operational mode
    *     Legacy, Enhanced Legacy, Enhanced FIFO [ECANCON<7:5>: 00, 01, 10]
    *   3: Set the baud rate registers
    *   4: Set filter and mask registers
    *   5: Set ECAN to mode required by application
    */

   mode = ECAN_setmode(ECAN_MODE_CONFIG);

   if(mode == ECAN_MODE_CONFIG)
    {
     // set the ECAN mode
     ECANCON = ECAN_LEGACY;      // MODE 0
     //ECANCON = ECAN_ENHANCED;    // MODE 1

     // set Bit rate values
     ECAN_setbaud(baud);
     //Set IO Control Register
     CIOCONbits.ENDRHI=1;
     CIOCONbits.CANCAP=0;

     // Setup Programmable buffers
     //  B0 is a Transmit buffer AND B2,B3,B4,B5 are Transmit buffers
    BSEL0 = 0xF8;   //1111 10--

     // Initialize Receive Masks
     //  The first mask is used that accepts all SIDs and no EIDs
     RXM0EIDH = 0x00;    //
     RXM0EIDL = 0x00;
     RXM0SIDH = 0xFF;    // Standard ID FILTER
     RXM0SIDL = 0xE0;

     //  The second mask is used that accepts all SIDs and EIDs
     RXM1EIDH = 0x00;    // 0's for EID and SID
     RXM1EIDL = 0x00;
     RXM1SIDH = 0xFF;
     RXM1SIDL = 0xE0;

    // Enable Filters
    //  Only using first three filters
    RXFCON0 = 0x07;     //Enable Filters 0,1,2
    RXFCON1 = 0x00;     //Disable all others

    // Assign Filters to Masks
    MSEL0 = 0xC0;     //Assign Filters 0-2 to Mask 0   // No mask
    MSEL1 = 0xFF;     //Assign Filters 4-7 to Mask     // No mask
    MSEL2 = 0xFF;     //Assign Filters 8-11 to Mask    // No mask
    MSEL3 = 0xFF;     //Assign Filters 12-15 to Mask   // No mask

    // Assign Filters to Buffers

    RXFBCON0 = 0x10;     //Assign Filter 0 to RXB0, and Filter 1 to RXB1
    RXFBCON1 = 0xF2;     //Assign Filter 2 to B0, Filter 2 no filter

    RXFBCON2 = 0xFF;     //Assign the rest of the buffers with no filter
    RXFBCON3 = 0xFF;
    RXFBCON4 = 0xFF;
    RXFBCON5 = 0xFF;
    RXFBCON6 = 0xFF;
    RXFBCON7 = 0xFF;

    // Initialize Receive Filters
    //  Filter 0 = 0x196
    //  Filter 1 = 0x19A
    //  Filter 2 = 0x19E
    RXF0EIDH = 0x00;
    RXF0EIDL = 0x00;
    RXF0SIDH = 0x32;
    RXF0SIDL = 0xC0;
    RXF1EIDH = 0x00;
    RXF1EIDL = 0x00;
    RXF1SIDH = 0x33;
    RXF1SIDL = 0x40;
    RXF2EIDH = 0x00;
    RXF2EIDL = 0x00;
    RXF2SIDH = 0x33;
    RXF2SIDL = 0xC0;

     CANCONbits.WIN2 = 1;       // Make TX0 available in Access Bank
     CANCONbits.WIN1 = 1;
     CANCONbits.WIN0 = 1;

     // Set transmit buffer to Standard
     TXB0SIDLbits.EXIDE = _STANDARD;
     TXB1SIDLbits.EXIDE = _STANDARD;
     TXB2SIDLbits.EXIDE = _STANDARD;

     ECAN_setmode(ECAN_MODE_NORMAL);
   }

}


char ECAN_setmode(char mode)
{
   CANCON = mode;
   while(CANSTAT & mode != mode);

   return CANSTAT & mode;
}


int ECAN_setbaud(int baud)
{
    switch(baud)
    {
        case 500:
            BRGCON1=0x00;
            break;

        case 250:
            BRGCON1=0x09;
            break;

        case 125:
            BRGCON1=0x13;
            break;

        default:
            BRGCON1=0x00;
            baud = 500;
            break;
    }

    BRGCON2=0xBA;
    BRGCON3=0x07;
    
    return baud;
}

void populateCANBuffer(unsigned int buff, char start, char len, char ch)
{
    // buff tells us which of the 3 buffers to use
    // so get a pointer to this buffer
    int i, byteVal;
    unsigned char *BUFFER_ptr;

    // we need a pointer to the data array as well
    //int *adc_values_array_ptr;
    //get the address of the array
    //adc_values_array_ptr = &adc_values_array[0];

    // make sure the transmit buffers are in the Access Bank
    CANCONbits.WIN2 = 1;
    CANCONbits.WIN1 = 1;
    CANCONbits.WIN0 = 1;

   //get the address of the register
   BUFFER_ptr = &TXB2CON;
   BUFFER_ptr += buff;
   BUFFER_ptr += start;

   // point to the value needed

  for(i=start;i<start+len;i+=2)
   {
     byteVal = getHiByte(ch);
     *BUFFER_ptr = byteVal;
       BUFFER_ptr++;

     byteVal = getLoByte(ch);
     *BUFFER_ptr = byteVal;
       BUFFER_ptr++;
       ch++;
   }
}

/* EOF simbuckecan.c **********************************************************/