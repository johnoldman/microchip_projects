/********************************************************************
 FileName:     	HardwareProfile - SimbuckSpeedBox.h
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

#ifndef HARDWARE_PROFILE_SIMBUCKSPEEDBOX_H
#define HARDWARE_PROFILE_SIMBUCKSPEEDBOX_H

    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/


/** S W I T C H  D A T A **********************************************/

/* Switch inputs  ******************************************************
*	TRISDbits.TRISD3 = INPUT_PIN		// input 3  0xnn
*	TRISDbits.TRISD2 = INPUT_PIN		// input 2  0xnn
*	TRISDbits.TRISD1 = INPUT_PIN		// input 1  0xnn
*	TRISDbits.TRISD0 = INPUT_PIN		// input 0  0xnn
***********************************************************************/

#define mInitRIP()		TRISD |= 0x0F;

#define mRIP_3			LATDbits.LATD3;
#define mRIP_2			LATDbits.LATD2;
#define mRIP_1			LATDbits.LATD1;
#define mRIP_0			LATDbits.LATD0;

/** O U T P U T  D A T A **********************************************
*	TRISDbits.TRISD7 = OUTPUT_PIN;		// CPS          OPTO_4  MOLEX Pin 11
*	TRISDbits.TRISD6 = OUTPUT_PIN;		// CID          OPTO_3  MOLEX Pin 9
*	TRISDbits.TRISD5 = OUTPUT_PIN;		// CID inverted OPTO_2  MOLEX Pin 7
*	TRISDbits.TRISD4 = OUTPUT_PIN;		// REV/MIN      OPTO_1  MOLEX Pin 5
*****************************************************************************/

#define mInit_OPTO()		TRISDbits.TRISD7=OUTPUT_PIN;LATDbits.LATD7=0;TRISDbits.TRISD6=OUTPUT_PIN;LATDbits.LATD6=0;TRISDbits.TRISD5=OUTPUT_PIN;LATDbits.LATD5=0;TRISDbits.TRISD4=OUTPUT_PIN;LATDbits.LATD4=0;

#define mCPS			LATDbits.LATD7
#define mCPS_Hi() 	   	mCPS = 1;
#define mCPS_Lo()		mCPS = 0;
#define mCPS_Toggle()  	   	mCPS = !mCPS;

#define mCID			LATDbits.LATD6
#define mCID_Hi() 	   	mCID = 1;
#define mCID_Lo()		mCID = 0;
#define mCID_Toggle()  	   	mCID = !mCID;

#define mCID_inv		LATDbits.LATD5
#define mCID_inv_Hi() 	   	mCID_inv = 1;
#define mCID_inv_Lo()		mCID_inv = 0;
#define mCID_inv_Toggle()  	MCID_inv = !mCID_inv;

#define mREV			LATDbits.LATD4
#define mREV_Hi() 	   	mREV = 1;
#define mREV_Lo()		mREV = 0;
#define mREV_Toggle()  	   	mREV = !mREV;


#endif  //HARDWARE_PROFILE_SIMBUCKSPEEDBOX_H
