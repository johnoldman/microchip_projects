/*******************************************************************************
 FileName:	simbuckpwm.c
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
 File Description: PWM module

 Document Reference:
  * Title - PIC18F2455/2550/4455/4550 Data Sheet
  *  Section - Section 15 CAPTURE/COMPARE/PWM(CCP) MODULES
  * Title - PIC18F2682/2685/4682/4685 Data Sheet
  *  Section - CAPTURE/COMPARE/PWM(CCP1) MODULES
  * Title - Simbuck Baseboard4550 User Guide
  *  Section -
  * Title - Simbuck Baseboard4685 User Guide
  *  Section -

 Interface Pins
  * Simbuck pin - uC Pin
__LOG(id, );


 Change History:
  Rev   Description
  ----  ------------------------------------------------------------------------

  1.0.0 First release for Simbuck - original file
                                    
*******************************************************************************/



/* I N C L U D E S ************************************************************/
#include "../simbuck_cfg.h"
#include "../HardwareProfile.h"
#include "GenericTypeDefs.h"
#include "../system/eeprom/eeprom.h"

#if defined(SIMBUCK_BASEBOARD_4550)
  #include <p18cxxx.h>
  #include "../user/user_4550.h"
  #include "simbuckpwm.h"

#endif

#if defined(SIMBUCK_BASEBOARD_4685)

  #include <p18cxxx.h>
  #include "../user/user_4685.h"
  #include "simbuckadc.h"

#endif


/* V A R I A B L E S **********************************************************/
#pragma udata
PWM_USER PWMUser;

/* D E C L A R A T I O N S ****************************************************/
#pragma code


/**
 * Initialise the PWM channel(s)
 *
 * Overview:        This function is the single point for initialising PWM peripheral
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Note: Simbuck Baseboard4550
 *          The 4550 uC has 2 channels available. 
 *
 * Note: Simbuck Baseboard4685
 *          The 4685 uC has 1 channel available.
 *
 * PWM requirements
 *      1. Set the PWM period by writing to the PR2
 *          register.
 *      2. Set the PWM duty cycle by writing to the
 *         CCPRxL register and CCPxCON<5:4> bits.
 *      3. Make the CCPx pin an output by clearing the
 *         appropriate TRIS bit.
 *      4. Set the TMR2 prescale value, then enable
 *         Timer2 by writing to T2CON.
 *      5. Configure the CCPx module for PWM operation.
 
 * Calculations:
 *
 * PWM Period = [(PR2) + 1] ? 4 ? TOSC ? (TMR2 Prescale Value)
 * PWM Duty Cycle = (CCPRXL:CCPXCON<5:4>) ? TOSC ? (TMR2 Prescale Value)
 *
 * Simbuck Baseboard 4550
 *
 * Simbuck Baseboard 4685
 *
*/

void PWM_init()
{
  
#if defined(SIMBUCK_BASEBOARD_4550)

  // setPWMDutyCycle(2, 0x01);     // MINIMUM Duty cycle
  // setPWMDutyCycle(2, 0x5D);     // 50% Duty cycle
  // setPWMDutyCycle(2, 0xBB);     // MAXIMUM Duty cycle (limited by PR2)
  
  TRISCbits.TRISC2 = OUTPUT_PIN;
  LATCbits.LATC2=1;
  
  TRISCbits.TRISC1 = OUTPUT_PIN;
  LATCbits.LATC1=1;

  CCP1CON=0x0C;                  // Single PWM mode
  setPWMDutyCycle(1, 0x00);      // TURN OFF
  

  CCP2CON=0x0C;                 // Single PWM mode
  setPWMDutyCycle(2, 0x00);     // TURN OFF

  T2CONbits.T2CKPS1 = 1;	// 16:1 Pre scale (2500Hz @ 20MHz)
  T2CONbits.T2CKPS0 = 1;
  
  //PR2=0xBA;                   // base frequency 4.011 KHz (measured)
  PR2=0xBB;                     // base frequency 3.99 KHz (measured)

  T2CONbits.TMR2ON = 1;		// start the Timer
 
}

#endif

#if defined(SIMBUCK_BASEBOARD_4685)
   // Setup the 

#endif



/**
 * Update the PWM channel(s)
 *
 * Overview:        This function is the single point for setting the PWM channel(s)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Note:
 *      The 4550 uC has 2 channels available.
 *      The 4685 uC has 1 channel available.
*/

char setPWMDutyCycle(char ch, unsigned int dc)
{
    char errVal = -1;
    dc = 4*dc;    // 1023/255 = 4

    switch(ch)
    {
        case 1:
            CCPR1L = dc>>2;                 // put the MSB 8 bits in CCPRxL
            CCP1CON &= 0xCF;                // bit<4:5> = 0
            CCP1CON |= (0x30 & (dc << 4));  // put LSB in CCP1CON (10bit resolution)
            errVal = 0;
            break;

        case 2:
            CCPR2L = dc>>2;                 // put the MSB 8 bits in CCPRxL
            CCP2CON &= 0xCF;                // bit<4:5> = 0
            CCP2CON |= (0x30 & (dc << 4));  // put LSB in CCP2CON (10bit resolution)
            errVal=0;
            break;

        default:
            // something went wrong!
            errVal = 3;
            break;

    }

    return errVal;
}


/**
 * set the PWM channel(s) direction
 *
 * Overview:        This function is the single point for setting the PWM channel(s) direction
 *
 * PreCondition:    CCP1/2 are driving Microchip TC4424 MOSFET chip or equivalent
 *
 * Input:           cannel number, duty-cycle
 *
 * Output:          None
 *
 * Note: The TC4424 uC has 2 modes available.
 *        LATCbits.LATCn=0;    // clockwise
 *        LATCbits.LATCn=1;    // anti-clockwise
 *
*/

char setPWMDirection(char ch, unsigned int d)
{
    char errVal = -1;

    switch(ch)
    {
        case 1:
            LATCbits.LATC2=d;
            errVal = 0;
            break;

        case 2:
            LATCbits.LATC1=d;
            errVal=0;
            break;

        default:
            // something went wrong!
            errVal = 4;
            break;

    }


    return errVal;
}