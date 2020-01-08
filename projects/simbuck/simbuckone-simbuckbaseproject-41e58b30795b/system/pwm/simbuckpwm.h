/*******************************************************************************
 FileName:	simbuckpwm.h
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
  * Simbuck pin - uC Pin
  * Simbuck pin - uC Pin
  * Simbuck pin - uC Pin
  * Simbuck pin - uC Pin



 Change History:
  Rev   Description
  ----  ------------------------------------------------------------------------

  1.0.0 First release for Simbuck - original file

*******************************************************************************/

#ifndef SIMBUCKPWM_H
#define SIMBUCKPWM_H

/* I N C L U D E S ************************************************************/
#include "GenericTypeDefs.h"


/* D E F I N E S **************************************************/
#define USE_PWM



/* S T R U C T S **************************************************************/

/**
 * Structure to maintain a set of current PWM readings
*/

//typedef struct PWM_VALUES
//{
//    PWM CH0_CNTS;
//    PWM CH1_CNTS;
//
//} PWM_VALUES;

typedef struct PWM_CHANNELS
{
     unsigned PWM_CH0:1;
     unsigned PWM_CH1:1;
     
} PWM_CHANNELS;

typedef struct PWM_USER
{
    unsigned DEBUG:1;                  ///< Switch off Hardware specific features for off-line debugging

} PWM_USER;

/* P U B L I C  P R O T O T Y P E S *******************************/
void PWM_init(void);
char setPWMDutyCycle(char, unsigned int);
char setPWMDDirection(char, unsigned int);

#endif // SIMBUCKPWM_H