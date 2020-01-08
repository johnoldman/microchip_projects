/*******************************************************************************
 FileName:	simbuckadc.h
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

#ifndef SIMBUCKADC_H
#define SIMBUCKADC_H

/* I N C L U D E S ************************************************************/
#include "GenericTypeDefs.h"


/* D E F I N E S **************************************************/
#define MAX_CHANNELS    10

#define CH0     0x00        ///< A/D Channel 1
#define CH1     0x01        ///< A/D Channel 2
#define CH2     0x02        ///< A/D Channel 3
#define CH3     0x03        ///< A/D Channel 4
#define CH4     0x04        ///< A/D Channel 5
#define CH5     0x05        ///< A/D Channel 6
#define CH6     0x06        ///< A/D Channel 7
#define CH7     0x07        ///< A/D Channel 8
#define CH8     0x08        ///< A/D Channel 9
#define CH9     0x09        ///< A/D Channel 10

#define CH0_ON  TRISAbits.RA0 = INPUT_PIN;
#define CH1_ON  TRISAbits.RA1 = INPUT_PIN;
#define CH2_ON  TRISAbits.RA2 = INPUT_PIN;
#define CH3_ON  TRISAbits.RA3 = INPUT_PIN;
#define CH4_ON  TRISAbits.RA5 = INPUT_PIN;
#define CH5_ON  TRISEbits.RE0 = INPUT_PIN;
#define CH6_ON  TRISEbits.RE1 = INPUT_PIN;
#define CH7_ON  TRISEbits.RE2 = INPUT_PIN;

#if defined(SIMBUCK_BASEBOARD_4550)
#define CH8_ON TRISBbits.RB2 = INPUT_PIN;
#define CH9_ON TRISBbits.RB3 = INPUT_PIN;
#endif

#if defined(SIMBUCK_BASEBOARD_4685)
#define CH8_ON TRISBbits.RB1 = INPUT_PIN;
#define CH9_ON TRISBbits.RB4 = INPUT_PIN;
#endif

#define CH0_OFF TRISAbits.RA0 = OUTPUT_PIN;
#define CH1_OFF TRISAbits.RA1 = OUTPUT_PIN;
#define CH2_OFF TRISAbits.RA2 = OUTPUT_PIN;
#define CH3_OFF TRISAbits.RA3 = OUTPUT_PIN;
#define CH4_OFF TRISAbits.RA5 = OUTPUT_PIN;
#define CH5_OFF TRISEbits.RE0 = OUTPUT_PIN;
#define CH6_OFF TRISEbits.RE1 = OUTPUT_PIN;
#define CH7_OFF TRISEbits.RE2 = OUTPUT_PIN;

#if defined(SIMBUCK_BASEBOARD_4550)
#define CH8_OFF TRISBbits.RB2 = OUTPUT_PIN;
#define CH9_OFF TRISBbits.RB3 = OUTPUT_PIN;
#endif

#if defined(SIMBUCK_BASEBOARD_4685)
#define CH8_OFF TRISBbits.RB1 = OUTPUT_PIN;
#define CH9_OFF TRISBbits.RB4 = OUTPUT_PIN;
#endif


/* S T R U C T S **************************************************************/

/**
 * Structure to maintain a set of current ADC readings
*/
typedef struct ADC_VALUES
{
     WORD CH0_CNTS;
     WORD CH1_CNTS;
     WORD CH2_CNTS;
     WORD CH3_CNTS;
     WORD CH4_CNTS;
     WORD CH5_CNTS;
     WORD CH6_CNTS;
     WORD CH7_CNTS;
     WORD CH8_CNTS;
     WORD CH9_CNTS;
     
} ADC_VALUES;

typedef struct ADC_CHANNELS
{
     unsigned ADC_CH0:1;
     unsigned ADC_CH1:1;
     unsigned ADC_CH2:1;
     unsigned ADC_CH3:1;
     unsigned ADC_CH4:1;
     unsigned ADC_CH5:1;
     unsigned ADC_CH6:1;
     unsigned ADC_CH7:1;
     
     unsigned CH_8:1;
     unsigned CH_9:1;
     
} ADC_CHANNELS;

typedef struct ADC_USER
{
    unsigned DEBUG:1;                  ///< Switch off Hardware specific features for off-line debugging
    unsigned power:1;                  ///< Flag to enable settling time before any acquisition
    unsigned mode:1;                   ///< 0 = 10-bit; 1 = 8-bit
    unsigned getNext:1;                ///< Flag to release for next acquisition
    unsigned getCounts:1;              ///< Flag to perform conversion
    unsigned storeCounts:1;            ///< Flag to copy ADRESH:ADRESL
    unsigned loadTx:1;                 ///< Flag to invoke loading CAN buffers
    unsigned sendTx:1;                 ///< Flag to allow CAN scheduling
    unsigned sendTx0:1;                ///< Flag to allow CAN scheduling
    unsigned sendTx1:1;                ///< Flag to allow CAN scheduling
    unsigned sendTx2:1;                ///< Flag to allow CAN scheduling
    unsigned useCAN:1;                 ///> Flag to allow CAN scheduling
    unsigned useUART:1;                ///> Flag to allow UART scheduling
    char updateChannel;                ///< 'Flag' used to update data array
    char activeChannel;                ///< The current active ADC channel
    char maxChannels;                  ///< The number of active ADC channel
    char adcWait;                      ///< Calibratable 'wait' time between acquisitions
} ADC_USER;

/* P U B L I C  P R O T O T Y P E S *******************************/
void ADC_init(void);
char selectChannel(char);
BOOL acquireADC(char);
char storeADC(char);
BYTE getHiByte(char);
BYTE getLoByte(char);

#endif // SIMBUCKADC_H