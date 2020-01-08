/********************************************************************
 FileName:	simbuckspi.c
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
 File Description:

 Change History:
  Rev   Description
  ----  ------------------------------------------------------------------------

  1.0.0 First release for Simbuck - Based from original file
                                    supplied for the LIBUSB
                                    demo in the Microchip
                                    solutions Library v2011-07-14

*******************************************************************************/
  

/* I N C L U D E S **********************************************************/

#include "simbuck_cfg.h"
#include "HardwareProfile.h"
#include "system/eeprom/eeprom.h"

#if defined(SIMBUCK_BASEBOARD_4550)
  #include <p18cxxx.h>
#endif

#if defined(SIMBUCK_BASEBOARD_4685)
  #include <p18cxxx.h>
#endif

/* S I M L I B   I N C L U D E S **********************************************************/
//#if defined(SIMBLOCK_DUAL_CAN)
//  #include "HardwareProfile - SimblockDualCAN.h"
////  #include "system/spi/simbuckspi.h"
//  #include "system/CAN/CAN2515drv.h"
  //#include "system/CAN/CAN2515utils.h"

//#endif


/* V A R I A B L E S ********************************************************/
#pragma udata


/* P R O T O T Y P E S ******************************************************/


/* D E C L A R A T I O N S **************************************************/
#pragma code

/********************************************************************************/
/* Level '0' SPI functions 														*/
/* Set up SPI			   														*/

/**
 * Initialise the SPI bus
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the single point for the setting the SPI bus
 *
 * Note:            None
*/

void InitSPI(void)
{


#if defined(DISPLAY_4DSYSTEMS)
  // Make sure we have disabled the USART
  // The USART Peripheral takes over the C7 Pin
  // and prevents SPI comms
  RCSTAbits.SPEN = 0;
#endif

#if defined(SIMBUCK_BASEBOARD_4550)
   TRISCbits.TRISC7 = OUTPUT_PIN;       ///< SDO
   TRISBbits.TRISB0 = INPUT_PIN;	///< SDI
   TRISBbits.TRISB1 = OUTPUT_PIN;	///< SCK
#elif defined(SIMBUCK_BASEBOARD_4685)
    TRISCbits.TRISC5 = OUTPUT_PIN;      ///< SDO
    TRISCbits.TRISC4 = INPUT_PIN;	///< SDI
    TRISCbits.TRISC3 = OUTPUT_PIN;	///< SCK
#else
    // do nothing

#endif
    
    // Setup the Chip Select pins

  #if defined(SIMBLOCK_DUAL_CAN)
      
    /*  S S P C O N 1	******************************************************

		WCOL	= 0		// Write Collision
		SSPOV	= 0		// Receive overflow
		SSPEN	= 0		// Enables port and configures SPI pins
		CKP	= 0		// Clock polarity idle state - High [MCP2515]
		SSPM3	= 0		// Mode select bit
		SSPM2	= 0		// Mode select bit
		SSPM1	= 0		// Mode select bit
		SSPM0	= 1		// Mode select bit - SPI Master Fosc/64

*/

   // prepare the SPI bus for use
    SSPCON1bits.SSPEN=0;

    SSPCON1bits.CKP=1;

    SSPCON1bits.SSPM3=0;
    SSPCON1bits.SSPM2=0;
    SSPCON1bits.SSPM1=0;
    SSPCON1bits.SSPM0=1;


/*  S S P S T A T	******************************************************

		SMP	=	 1		// input data sampled at end of data output time
		CKE	=	 1		// SPI Clock - Transmit on transition idle to active
		D/A	=	 0		// not used for SPI (I2C mode)
		P	=	 0		// not used for SPI (I2C mode)
		S	= 	 0		// not used for SPI (I2C mode)
		R/W	= 	 0		// not used for SPI (I2C mode)
		UA	=	 0		// not used for SPI (I2C mode)
		BF	=	 0-1            // receive complete SSPBUFF full
*/

     SSPSTATbits.CKE=0;
     SSPSTATbits.SMP=1;


   // Enable Synchronous Serial Port
   SSPCON1bits.SSPEN = 1;
    
   #endif

} // end InitSPI()


/*************************************************************************/
/* Physically write a byte to the SPI bus								 */

 
/**
 * Writes a byte to the SPI bus
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the single point for writing to the SPI bus
 *
 * Note:            None
*/
unsigned char WriteSPI( unsigned char data_out )
{
   
  SSPBUF = data_out;           // write byte to SSPBUF register
  if (SSPCON1 & 0x80 )        // test if write collision occurred
   {
    return ( -1 );              // if WCOL bit is set return negative #
   } 
  else
  {
    while(!SSPSTATbits.BF);  // wait until bus cycle complete 
  }
  
  
  return ( 0 );             // if WCOL bit is not set return non-negative#

}

/****************************************************************************/
/* Physically read a byte from the SPI bus 									*/


/**
 * Reads a byte from the SPI bus
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the single point for reading from the SPI bus
 *
 * Note:            None
*/
unsigned char ReadSPI(unsigned char dummybyte)
{
     
   SSPBUF = dummybyte;                  // initiate bus cycle
    while(!SSPSTATbits.BF);
   
    return SSPBUF;

}

  




