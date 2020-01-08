/********************************************************************
 FileName:     	HardwareProfile - SimblockDualCAN.h
 Dependencies:  See INCLUDES section
 Processor:     PIC18 USB Microcontrollers
 Hardware:      Simbuck Baseboard4550
 Compiler:      Microchip C18
 Company:       Deben Enterprises Limited


 THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   03/03/2012   Initial release

********************************************************************/

#ifndef HARDWARE_PROFILE_SIMBLOCKDUALCAN_H
#define HARDWARE_PROFILE_SIMBLOCKDUALCAN_H

    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/

/** S P I : Chip Select Lines ***************************************
*	TRISAbits.TRISA1 = OUTPUT_PIN;		// Chip select - HS CAN
*	TRISAbits.TRISA2 = OUTPUT_PIN;		// Chip select - LS CAN
/*********************************************************************/


 /** S P I : Chip Select Lines ***************************************
*	TRISAbits.TRISA1 = OUTPUT_PIN;		// Chip select - HS CAN
*	TRISAbits.TRISA2 = OUTPUT_PIN;		// Chip select - LS CAN
/*********************************************************************/
   
    #define CAN_1_INT               PORTBbits.RB5
    #define CAN_2_INT               PORTBbits.RB4

    #define tris_cs_mcp2515_CAN_1   TRISBbits.TRISB2    // Output
    #define cs_mcp2515_CAN_1        LATBbits.LATB2      // was RA1 [CAN_1_CS]
                                                        // error in original design
                                                        //

    #define tris_cs_mcp2515_CAN_2   TRISBbits.TRISB3    // Output
    #define cs_mcp2515_CAN_2        LATBbits.LATB3      // was RA2 [CAN_2_CS]
                                                        // error in original design

    #define mInitCANPins()      TRISBbits.TRISB2=0;TRISBbits.TRISB3=0;TRISBbits.TRISB7=1;TRISBbits.TRISB6=1;



    #define CAN_INT_1_MASK          0x20
    #define CAN_INT_2_MASK          0x10

    #define Select_CAN_1()       cs_mcp2515_CAN_1=SELECT;
    #define DeSelect_CAN_1()     cs_mcp2515_CAN_1=DESELECT;

    #define Select_CAN_2()       cs_mcp2515_CAN_2=SELECT;
    #define DeSelect_CAN_2()     cs_mcp2515_CAN_2=DESELECT;



    /** I/O pin definitions ********************************************/
    #define INPUT_PIN           1
    #define OUTPUT_PIN          0
    #define SELECT              0
    #define DESELECT            1

/** Error flag definitions ********************************************/

#define OK      0


#endif  //HARDWARE_PROFILE_SIMBLOCKDUALCAN_H
