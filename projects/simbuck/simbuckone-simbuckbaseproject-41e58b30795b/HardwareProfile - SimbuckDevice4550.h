/********************************************************************
 FileName:     	HardwareProfile - SimbuckDevice4550.h
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

#ifndef HARDWARE_PROFILE_SIMBUCKDEVICE4550_H
#define HARDWARE_PROFILE_SIMBUCKDEVICE4550_H


    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/


    /** LED ************************************************************/
    #define mInitAlertLEDs()      LATD &= 0xF0; TRISD &= 0xF0;

    #define mAlert_1              LATDbits.LATD7
    #define mGetAlert_1()         mAlert_1
    #define mAlert_1_On()         mAlert_1 = 1;
    #define mAlert_1_Off()        mAlert_1 = 0;
    #define mAlert_1_Toggle()     mAlert_1 = !mAlert_1;

    #define mAlert_2              LATDbits.LATD6
    #define mGetAlert_2()         mAlert_2
    #define mAlert_2_On()         mAlert_2 = 1;
    #define mAlert_2_Off()        mAlert_2 = 0;
    #define mAlert_2_Toggle()     mAlert_2 = !mAlert_2;

    #define mAlert_3              LATDbits.LATD5
    #define mGetAlert_3()         mAlert_3
    #define mAlert_3_On()         mAlert_3 = 1;
    #define mAlert_3_Off()        mAlert_3 = 0;
    #define mAlert_3_Toggle()     mAlert_3 = !mAlert_3;

    #define mAlert_4              LATDbits.LATD4
    #define mGetAlert_4()         mAlert_4
    #define mAlert_4_On()         mAlert_4 = 1;
    #define mAlert_4_Off()        mAlert_4 = 0;
    #define mAlert_4_Toggle()     mAlert_4 = !mAlert_4;


    /** I/O pin definitions ********************************************/


#endif  //HARDWARE_PROFILE_SIMBUCKDEVICE4550_H
