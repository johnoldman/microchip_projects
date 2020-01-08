/********************************************************************
 FileName:     	HardwareProfile - Baseboard4550.h
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

#ifndef HARDWARE_PROFILE_BASEBOARD4550_H
#define HARDWARE_PROFILE_BASEBOARD4550_H

    //The Simbuck platform supports the USE_SELF_POWER_SENSE_IO
    //and USE_USB_BUS_SENSE_IO features.  Uncomment the below line(s) if
    //it is desireable to use one or both of the features.
    #define USE_SELF_POWER_SENSE_IO

    #if defined(USE_SELF_POWER_SENSE_IO)
    #define self_power          PORTAbits.RA0
    #define tris_self_power     TRISAbits.TRISA0    // Input
    #else
    #define self_power          1
    #endif

    #define USE_USB_BUS_SENSE_IO
  
    #if defined(USE_USB_BUS_SENSE_IO)
    #define USB_BUS_SENSE       PORTAbits.RA1
    #define tris_usb_bus_sense  TRISAbits.TRISA1    // Input
    #else
    #define USB_BUS_SENSE       1
    #endif


    //Uncomment the following line to make the output HEX of this  
    //  project work with the MCHPUSB Bootloader    
    //#define PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER
	
    //Uncomment the following line to make the output HEX of this 
    //  project work with the HID Bootloader
    #define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER		

    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/



    /** LED ************************************************************/
    #define mInitAllLEDs()      LATE &= 0xF0; TRISE &= 0xF0;
    
    #define mLED_1              LATEbits.LATE0
    #define mLED_2              LATEbits.LATE1
    #define mLED_3              LATEbits.LATE2

    #define mGetLED_1()         mLED_1
    #define mGetLED_2()         mLED_2
    #define mGetLED_3()         mLED_3

    #define mLED_1_On()         mLED_1 = 1;
    #define mLED_2_On()         mLED_2 = 1;
    #define mLED_3_On()         mLED_3 = 1;

    #define mLED_1_Off()        mLED_1 = 0;
    #define mLED_2_Off()        mLED_2 = 0;
    #define mLED_3_Off()        mLED_3 = 0;
    
    #define mLED_1_Toggle()     mLED_1 = !mLED_1;
    #define mLED_2_Toggle()     mLED_2 = !mLED_2;
    #define mLED_3_Toggle()     mLED_3 = !mLED_3;


    /** I/O pin definitions ********************************************/
    #define INPUT_PIN           1
    #define OUTPUT_PIN          0

    #define SELECT              0
    #define DESELECT            1

#endif  //HARDWARE_PROFILE_BASEBOARD4550_H
