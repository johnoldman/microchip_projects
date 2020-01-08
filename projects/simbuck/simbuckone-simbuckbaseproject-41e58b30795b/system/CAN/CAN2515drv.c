/********************************************************************
 FileName:	CAN2515drv.c
 Dependencies:	See INCLUDES section
 Processor:	PIC18 and PIC32 USB Microcontrollers
 Hardware:      Simbuck Baseboards and PIC32 USB Starter kit
 Complier:  	Microchip C18 (for PIC18), C32 (for PIC32)
 Company:	Deben Enterprises Limited


 THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  -----------------------------------------
   1.0.0 First release for Simbuck - Based from original file
                                    supplied for the LIBUSB
                                    demo in the Microchip
                                    solutions Library v2011-07-14

********************************************************************

 *
/* I N C L U D E S **********************************************************/
#include "simbuck_cfg.h"
#include "../HardwareProfile.h"
#include "../HardwareProfile - SimblockDualCAN.h"
#include "GenericTypeDefs.h"


#if defined(SIMBUCK_BASEBOARD_4550)
 #include <p18cxxx.h>
 #include "../system/spi/simbuckspi.h"
 #include "CAN2515drv.h"
#endif

#if defined(SIMBLOCK_DUAL_CAN)

/* V A R I A B L E S ********************************************************/
#pragma udata
CAN_FLAGS CANFlags;

unsigned char CAN_1_rcv[14];        ///< CAN 1 Buffer 0
unsigned char CAN_2_rcv[14];        ///< CAN 2 Buffer 0
unsigned char CAN_3_rcv[14];        ///< CAN 1 Buffer 1
unsigned char CAN_4_rcv[14];        ///< CAN 2 Buffer 1

unsigned char CAN_update = 0x00;    ///< State Encoded byte defining which CAN frames have updated
                                    // 0000 0000 no updates
                                    // 0000 0001 rcv 1 update
                                    // 0000 0010 rcv 3 update
                                    // 0000 0100 rcv 2 update
                                    // 0000 1000 rcv 4 update

/* D E C L A R A T I O N S **************************************************/
#pragma code

/********************************************************************************/
/* 2515 Level '1' SPI functions							*/
/* Reference document - Microchip Datasheet 210801e				*/
/* Document Title - Stand-Alone CAN Controller with SPI Interface		*/
/* Document Chapter - Section 12 - SPI Interface				*/
/* Implement: 									*/
/*  RESET									*/
/*  READ									*/
/*  Read RX Buffer								*/
/*  WRITE									*/
/*  Load TX Buffer								*/
/*  RTS (Request To Send)							*/
/*  Read Status									*/
/*  RX Status									*/
/*  Bit Modify									*/
/*										*/
/********************************************************************************/


/*********************************************************************************/
/* RESET
*/

/**
 * Reset the MCP2515 CAN Controller prior to configuration
 *
 * PreCondition:    Configuration requirements defined in CAN_useCANx
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the single point for the software
 *                  RESEET of the MCP2515 CAN Controller
 *
 * Note:            None
*/
void CAN2515_reset(void)
{
  unsigned char ticCnt;
  unsigned char retVal;

 retVal = WriteSPI(CAN2515_RESET);

 // need to wait 128 tics
 for(ticCnt = 0;ticCnt<130;ticCnt++);

}

/*********************************************************************************/
/* READ
*/


/**
 * Read from the MCP2515 CAN controller
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the single point for reading the registers
 *                  of the MCP2515 CAN Controller
 *
 * Note:            None
*/
char CAN2515_read(unsigned char addr)
{
  unsigned char ReturnValue;

  CAN2515_select();

    while(WriteSPI(CAN2515_READ));
    while(WriteSPI(addr));

    ReturnValue = ReadSPI(SPI_CAN_DUMMY);

  CAN2515_unselect();

  return(ReturnValue);
}


/**
 * Read the Receive Status
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the single point for reading the received
 *                  CAN frame from the MCP2515 CAN Controller
 *
 * Note:            None
*/
char CAN2515_readRx(unsigned char addr, unsigned char type)
{
  unsigned char ReturnValue;
  unsigned char i;

  CAN2515_select();

    while(WriteSPI(CAN2515_READ));
    while(WriteSPI(addr));

     if(!CANFlags.cs_CAN_1)
     {

      for(i=0; i<13; i++)
	{
         if(type == 0)
         {
	  CAN_1_rcv[i] = ReadSPI(SPI_CAN_DUMMY);
          CAN_update |= 0x01;
         }
         else
            {
             CAN_3_rcv[i] = ReadSPI(SPI_CAN_DUMMY);
             CAN_update |= 0x02;
            }
        }
       }

    if(!CANFlags.cs_CAN_2 == 1)
      {

       for(i=0; i<=13; i++)
	 {
          if(type == 0)
           {
	    CAN_2_rcv[i] = ReadSPI(SPI_CAN_DUMMY);
            CAN_update |= 0x04;
           }
          else
             {
              CAN_4_rcv[i] = ReadSPI(SPI_CAN_DUMMY);
              CAN_update |= 0x08;
             }
  	 }

       }

  CAN2515_unselect();
  
  return(ReturnValue);
}

/*********************************************************************************/
/* Read RX Buffer
*/

/**
 * Read a received CAN frame
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the single point for reading the received
 *                  CAN frame from the MCP2515 CAN controller
 *
 * Note:            None
*/
unsigned char CAN2515_read_rxbuffer(unsigned char addr)
{

 unsigned char ReturnValue;

  CAN2515_select();

    while(WriteSPI(CAN2515_READ_RX_BUFF & addr));

      ReturnValue = ReadSPI(SPI_CAN_DUMMY);

  CAN2515_unselect();

 return ReturnValue;
}

/*********************************************************************************/
/* WRITE
*/


/**
 * Write to the MCP2515 CAN Controller
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the single point for Writing to the
 *                  MCP2515 CAN Controller registers
 *
 * Note:            None
*/
void CAN2515_write(unsigned char addr, unsigned char byte)
{

  CAN2515_select();

   while(WriteSPI(CAN2515_WRITE));
   while(WriteSPI(addr));
   while(WriteSPI(byte));

  CAN2515_unselect();

}

/*********************************************************************************/
/* Load TX Buffer
*/


/**
 * Load the Transmit Buffer
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the single point for Loading the Transmit Buffer
 *
 * Note:            None
*/
unsigned char CAN2515_loadtx(unsigned char buff)
{
  unsigned char retVal;

  CAN2515_select();

  retVal = WriteSPI(0x40 | 0x31);

  CAN2515_unselect();

  return retVal;

}

/*********************************************************************************/
/* RTS (RequestToSend)
*/


/**
 * Request To Send a CAN frame
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the single point for the Request To Send
 *                  of a CAN frame
 *
 * Note:            None
*/
unsigned char CAN2515_rts(unsigned char buff)
{
  unsigned char retVal;

  CAN2515_select();

  retVal = WriteSPI(buff);

  CAN2515_unselect();

  return retVal;

}


/*********************************************************************************/
/* Read Status
*/

/**
 * Read status
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the single point for reading the status of
 *                  the MCP2515 CAN Controller
 *
 * Note:            None
*/
unsigned char CAN2515_readstatus(void)
{
  unsigned char status;

   CAN2515_select();

  WriteSPI(CAN2515_READ_STATUS);     // Send code for Read Status command
    status = ReadSPI(SPI_CAN_DUMMY);

  CAN2515_unselect();

return status;

}


/*********************************************************************************/
/* RX Status
*/


/**
 * Read the receive status
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the single point for Reading the
 *                  receive status of the MCP2515 CAN Controller
 *
 * Note:            None
*/
unsigned char CAN2515_read_rxstatus(void)
{
   unsigned char status;

  CAN2515_select();

   while(WriteSPI(CAN2515_RX_STATUS));     // Send code for Read RX status command
    status = ReadSPI(SPI_CAN_DUMMY);

  CAN2515_unselect();

 return status;

}


/*********************************************************************************/
/* Bit Modify
*/


/**
 * Send Bit-Modify message to MCP2515 CAN Controller
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the single point for the sending the
 *                  Bit-Modify message to MCP2515 CAN Controller
 *
 * Note:            None
*/
unsigned char CAN2515_bitmodify(unsigned char addr, unsigned char mask, unsigned char value)
{
  CAN2515_select();

    while(WriteSPI(CAN2515_BIT_MODIFY));    // Send code for bit modify command
    while(WriteSPI(addr));                  // Send address of register to modify
    while(WriteSPI(mask));                  // Send mask of bits to modify in the register
    while(WriteSPI(value));                 // Send new data to be loaded into specified bits

  CAN2515_unselect();

 return(0);

}



/******************************************************************************/
/* Select the correct Controller Chip Select Pin
/*
/*   cs_mcp2515_CAN_x is defined in HardwareProfile - SimblockDualCAN
/*   
*/

/**
 * Select the correct CAN Controller chip
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is used for selecting the correct MCP2515
 *                  CAN Controller chipset
 *
 * Note:            cs_mcp2515_CAN_x is defined in HardwareProfile - SimblockDualCAN
*/
char CAN2515_select(void)
{


  char ERR = OK;

  if(!CANFlags.cs_CAN_1)
   {
     cs_mcp2515_CAN_1 = 0;              // Select the hardware
     ERR = 1;
   }
  else if(!CANFlags.cs_CAN_2)
    {
      cs_mcp2515_CAN_2 = 0;             // Select the hardware
      ERR = 2;
    }
    else
    {
      // we should set an error for no CS
        ERR = -1;
        return ERR;
    }
}


/********************************************************************************/
/* De-select the Controller Chip Select Pin
*/

/**
 * De-Select the MCP2515 CAN Controllers
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is used for de-selecting the MCP2515
 *                  CAN Controller chipsets when operations are complete
 *
 * Note:            cs_mcp2515_CAN_x is defined in HardwareProfile - SimblockDualCAN
*/
void CAN2515_unselect()
{
 
  cs_mcp2515_CAN_1 = 1;
  cs_mcp2515_CAN_2 = 1;
}

#endif



