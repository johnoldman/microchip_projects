/*******************************************************************************
 FileName:	simbuckadc.c
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
 File Description: 10-bit Analogue to Digital Convertor module

 Document Reference:
  * Title - PIC18F2455/2550/4455/4550 Data Sheet
  *  Section - Section 19 10Bit Analogue-to-Digital Convertor(A/D)Module
  * Title - PIC18F2682/2685/4682/4685 Data Sheet
  *  Section -
  * Title - Simbuck Baseboard4550 User Guide
  *  Section -
  * Title - Simbuck Baseboard4685 User Guide
  *  Section -

 Register(s):
  * ADRESH >> A/D Result high
  * ADRESL >> A/D Result low
  * ADCON0 >> A/D Control operations
  * ADCON1 >> A/D Control pin functions
  * ADCON2 >> A/D Control clock and timing

 Interface Pins
  * Simbuck pin - uC Pin


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
  #include "simbuckadc.h"

#endif

#if defined(SIMBUCK_BASEBOARD_4685)

  #include <p18cxxx.h>
  #include "../user/user_4685.h"
  #include "simbuckadc.h"

#endif

/* V A R I A B L E S **********************************************************/
#pragma udata
ADC_USER ADCUser;
static int adc_values_array[10];


/* D E C L A R A T I O N S ****************************************************/
#pragma code


/**
 * Initialise the ADC channel(s)
 *
 * Overview:        This function is the single point for initialising ADC peripheral
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Note: Simbuck Baseboard4550
 *          The 4550 uC has 9 channels available. If the Simbuck ADC stepdown
 *          board is implemented then only the top 9 channels are passed through.
 *
 *          IF a conversion is performed on an unimplemented channel the return
 *          will be a full-scale measurement
 *
 * Note: Simbuck Baseboard4685
 *          The 4685 uC has 11 channels available. If the Simbuck ADC stepdown
 *          board is implemented then only 10 channels are passed through.
 *
 *          IF a conversion is performed on an unimplemented channel the return
 *          will be a full-scale measurement
 *
 * A/D conversion requirements
 *      - The Analogue Channel must be sampled for at least the minimum
 *        acquisition time before starting a conversion after selection
 *
 *      - TAD must be as short as possible but Greater than the minimum TAD
 *
 *      - TAD must be a multiple of 2^n
 *
 * Calculations: Simbuck Baseboard 4550
 *      TAD = 0.8uS From Table 28-29
 *      TACQ = 2.45uS (Equation 21-3)
 *      Fosc = 48Mhz[PLL]
 *      Tosc = 1/Fosc = 1/48000000 = 0.000000020833 = 20.833ns
 *
 *      0.8uS/20.833ns = 0.8/0.020833 = 38.4
 *
 *      Tosc*32 = 32*20.833ns = 0.666uS
 *      Tosc*64 = 64*20.833ns = 1.33uS
 *
 *      Tosc = 64 TAD
 *
 *      TACQ = 2*TAD
 *           = 2*1.33 = 2.66 (> 2.45)
 *
 *      TACQ/TAD = 2.45uS/1.33uS = 1.8
 *      TACQ = 2 TAD
 *
 * Calculations: Simbuck Baseboard 4685
 *      TACQ min = 12.86uS (Equation 19-3)
 *      TAD = 0.7uS From Table 27-25
 *      Fosc = 20MHz
 *
 *      Tosc = 1/Fosc = 1/20000000 = 0.00000005 = 50ns
 *             Tosc*16 = 16*50 = 800ns = 0.8uS
 *             Tosc*32 = 32*50 = 1600ns = 1.6uS
 *             Tosc*64 = 64*50 = 3200ns = 3.2uS
 *
 *      Tosc = 32

 *      TACQ = 2*TAD
 *           = 2*12.86 = 25.72
 *
 *      TACQ = 
 *           = 20*1.6 = 32
 *           = 16*1.6 = 25.6
 *           = 12*1.6 = 19.2 
 *           =  8*1.6 = 12.8
 *
 *      TACQ/TAD = 12.86uS/1.6uS = 8.04
 *      TACQ = 20 TAD

 *  *
*/

void ADC_init(void)
{
    int i;
    // Make sure the ADC module is switched off
    ADCON0bits.ADON = 0;

    // Select the pins to be used as Analogue
    ADCON1bits.PCFG0 = 0;
    ADCON1bits.PCFG1 = 0;
    ADCON1bits.PCFG2 = 0;
    ADCON1bits.PCFG3 = 0;

    // use Vss and Vdd for Reference voltage
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;


    // Select channel 0 first
    ADCON0bits.CHS0 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;

    // stay with little endian for justification(use all 10-bits)
    ADCON2bits.ADFM = 1;

#if defined(SIMBUCK_BASEBOARD_4550)
   // Setup the Acquisition time - 2 TAD
   ADCON2bits.ACQT0 = 1;
   ADCON2bits.ACQT1 = 0;
   ADCON2bits.ACQT2 = 0;
   // Setup the A/D Conversion Clock - 64 TAD
   ADCON2bits.ADCS0 = 0;
   ADCON2bits.ADCS1 = 1;
   ADCON2bits.ADCS2 = 1;
#endif

#if defined(SIMBUCK_BASEBOARD_4685)
   // Setup the Acquisition time - 20 TAD
   ADCON2bits.ACQT0 = 1;
   ADCON2bits.ACQT1 = 1;
   ADCON2bits.ACQT2 = 1;
   // Setup the A/D Conversion Clock - 32 TAD
   ADCON2bits.ADCS0 = 0;
   ADCON2bits.ADCS1 = 1;
   ADCON2bits.ADCS2 = 0;
#endif

   // now we need to set the TRIS pins
   CH0_ON;
   CH1_ON;
   CH2_ON;
   CH3_ON;
   CH4_ON;
   CH5_ON;
   CH6_ON;
   CH7_ON;
   CH8_ON;
   CH9_ON;

   // enable the peripheral
   // ADCON0bits.ADON = 1;

   //initialise values array
   for(i=0;i<10;i++)
   {
    adc_values_array[i] = 0;
   }


}

/**
 * Initialise the ADC channel(s)
 *
 * Overview:        This function is the single point for setting the ADC channel(s)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Note:
 *      The 4685 uC has 11 channels available. If the Simbuck ADC stepdown
 *      board is implemented then only 10 channels are passed through.
 *
 *      IF a conversion is performed on an unimplemented channel the return
 *      will be a full-scale measurement
*/

char selectChannel(char ch) 
{
    char lastADC;
    char newADC;

    // check A-D Conversion is finished
    if(!ADCON0bits.GO_DONE)
    {
      lastADC = ADCON0;
      // clear bits 5:2 0xC3
      ADCON0 = (lastADC & 0x3C);
      ADCON0 = ADCON0 | (ch << 2);
      newADC =(ADCON0 & 0x3C) >> 2;
      Nop();
      Nop();
    }
    else
       {
        newADC = ch; // set error code here for ADC_BUSY?
       }

    return newADC;
}

BOOL acquireADC(char ch)
{
  BOOL state = 0;

  if(ADCUser.getNext)
  {
   ADCON0=0x00;

   selectChannel(ch);
   ADCON0bits.ADON = 1;

   // Using interrupt
   ADCON0bits.GO_DONE = 1;
   state = 1;

   // Polling
   // while(ADCON0bits.GO_DONE); //wait for the conversion to finish
   // ADCON0bits.ADON = 0;
   // state = 1;

   }

 return state;

}

char storeADC(char ch)
{
   int *adc_values_array_ptr;
   int counts = 0;

   //get the address of the array
   adc_values_array_ptr = &adc_values_array[0];
   
    counts = (int)ADRESH << 8;
    counts = counts + (int)ADRESL;
 
   *(adc_values_array_ptr + ch) = (unsigned int)counts;

}


// load the selected CAN frame with the data
BYTE getHiByte(char ch)
{
   //get the address of the array
   int *adc_values_array_ptr;
   int counts;
   BYTE hiVal;

    // Get the Array pointer
    adc_values_array_ptr = &adc_values_array[0 + ch];

    // Load the values for the xxx buffer
    counts = *adc_values_array_ptr;
      hiVal = (BYTE)(counts >> 8);

   return hiVal;

}

// load the selected CAN frame with the data
BYTE getLoByte(char ch)
{
   //get the address of the array
   int *adc_values_array_ptr;
   int counts;
   BYTE loVal;

    // Get the Array pointer
    adc_values_array_ptr = &adc_values_array[0 + ch];

    // Load the values for the xxx buffer
    counts = *adc_values_array_ptr;
     loVal = (BYTE)(counts & 0x00FF);

   return loVal;

}