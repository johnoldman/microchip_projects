/********************************************************************
 FileName:      HardwareProfile.h
 Dependencies:  See INCLUDES section
 Processor:     PIC18, PIC24, or PIC32 USB Microcontrollers
 Hardware:      The code is natively intended to be used on the
                  following hardware platforms:
                    PICDEM? FS USB Demo Board
                    PIC18F46J50 FS USB Plug-In Module
                    PIC18F87J50 FS USB Plug-In Module
                    Explorer 16 + PIC24 or PIC32 USB PIMs
                    PIC24F Starter Kit
                    Low Pin Count USB Development Kit
                  The firmware may be modified for use on other USB
                    platforms by editing this file (HardwareProfile.h)
 Compiler:  	Microchip C18 (for PIC18), C30 (for PIC24),
                  or C32 (for PIC32)
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the ?Company?) for its PIC� Microcontroller is intended and
 supplied to you, the Company?s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
  2.3   09/15/2008   Broke out each hardware platform into its own
                     "HardwareProfile - xxx.h" file
********************************************************************/

#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H


#include "simbuck_cfg.h"
//#define DEMO_BOARD USER_DEFINED_BOARD


#if !defined(DEMO_BOARD)
    #if defined(__C32__)
        #if defined(__32MX460F512L__)
            #if defined(PIC32MX460F512L_PIM)
                #include "HardwareProfile - PIC32MX460F512L PIM.h"
            #elif defined(SIMBUCK_BASEBOARD_PIC32)
                #include "HardwareProfile - PIC32 USB Starter Kit.h"
            #endif
        #elif defined(__32MX795F512L__)
            #if defined(PIC32MX795F512L_PIM)
                #include "HardwareProfile - PIC32MX795F512L PIM.h"
            #elif defined(SIMBUCK_BASEBOARD_PIC32)
                //PIC32 USB Starter Kit II
                #include "HardwareProfile - PIC32 USB Starter Kit.h"
            #endif
        #endif
    #endif


    ///#if defined(__18CXX)
    ///    #if defined(__18F4550)
    ///        #include "HardwareProfile - Baseboard4550.h"
    ///    #elif defined(__18F4685)
    ///        #include "HardwareProfile - Baseboard4685.h"
    ///    #endif
    ///#endif

        // handle stand-alone builds
        #if defined(SIMBUCK_BASEBOARD_4550)
            #include "HardwareProfile - Baseboard4550.h"
        #elif defined(SIMBUCK_BASEBOARD_4685)
            #include "HardwareProfile - Baseboard4685.h"
        #else
            #error "Board not defined."
        #endif


        #if defined(SIMBUCK_DEVICE_4550)
            #include "HardwareProfile - SimbuckDevice4550.h"
        #elif defined(SIMBUCKSPEEDBOX)
           #include "HardwareProfile - SimbuckSpeedbox.h"
        #else
           
        #endif


#endif

#if defined(DEMO_BOARD)
    #error "Board not defined.  Either define DEMO_BOARD for a custom board or select the correct processor for the board in use."
#endif

#endif  //HARDWARE_PROFILE_H
