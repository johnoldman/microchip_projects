/********************************************************************
 FileName:	CAN2515utils.c
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

********************************************************************/

/* I N C L U D E S **********************************************************/
#include "simbuck_cfg.h"
#include "../HardwareProfile.h"

#if defined(SIMBUCK_BASEBOARD_4550)
 #include <p18cxxx.h>
#endif

#if defined(SIMBLOCK_DUAL_CAN)
#include "../HardwareProfile - SimblockDualCAN.h"
#include "CAN2515drv.h"
#include "CAN2515utils.h"
#include "CAN_useCAN1.h"
#include "CAN_useCAN2.h"

/* V A R I A B L E S ********************************************************/
#pragma udata
WORD IDENTIFIER;            ///> CAN Identifier


/* P R O T O T Y P E S ******************************************************/
extern CAN_FLAGS CANFlags;


/* D E C L A R A T I O N S **************************************************/
#pragma code


/*****************************************************************************/
/* 2515 level '2' functions */
/* Reference document - Microchip Datasheet 210801e
/* Document Title - Stand-Alone CAN Controller with SPI Interface
/*
/* Document Chapter - Section 10 - Modes of Operation
/*	Implements:
/*			CAN2515_getmode
/*			CAN2515_setmode
/*
/*    Helper functions:
/*			CAN2515_select
/*			CAN2515_unselect
/*			encodeIdentifier
/*			decodeIdentifier
/*
/******************************************************************************/

/******************************************************************************/
/* calculate CAN messageID
*/

/**
 * Calculate the CAN ID
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is utility function to calculate CAN ID
 *                  for the MCP2515 CAN Controller
 *
 * Note:            The 'Human' readable CAN ID needs to be mapped into
 *                  the correct registers.
*/
unsigned long encodeIdentifier(unsigned char reg, unsigned long canID, unsigned char type)
{

  int i;
  static unsigned long can_ID;
  unsigned char byteVal;
  static unsigned char addr;
  unsigned char extended = type;
  static unsigned char canIDbuf[4] = {0x00, 0x00, 0x00, 0x00};
  unsigned long int returnValue = 0x00000000;

  addr = reg;
  can_ID = canID;

  if(CANFlags.DEBUG)
   {
	 canIDbuf[0] = (can_ID & 0xFF000000) >> 24;
	 canIDbuf[1] = (can_ID & 0x00FF0000) >> 16;
	 canIDbuf[2] = (can_ID & 0x0000FF00) >> 8;
	 canIDbuf[3] = (can_ID & 0x000000FF);
	 }
//   else
  //     {
	//	 extended = CAN2515_read(reg + 0x02);
	  // }

    	 if(extended & 0x08)
          {
	       // extended message
	   canIDbuf[3] =  can_ID & 0xFF;
	   canIDbuf[2] =  (can_ID >> 0x08) & 0xFF;

	     can_ID = canID >> 16;

	       canIDbuf[1] =  can_ID & 0x03;
	       canIDbuf[1] +=  (can_ID & 0x1C) << 3;
  	       canIDbuf[1] |=  0x08; //set .exide bit

	       canIDbuf[0] =  can_ID >>5;
	    }
	     else
		    {
		     //standard message
			 can_ID = canID & 0xFFFF;

		     canIDbuf[0] =  can_ID >> 0x03;
		     canIDbuf[1] = (can_ID & 0x07) << 0x05 ;
		     canIDbuf[2] =  0;
		     canIDbuf[3] =  0;
		   	}


  for(i=0;i<3;i++)
    {
      returnValue = (returnValue + canIDbuf[i]) << 8;
  	  addr += 1;
	  CAN2515_write(addr, canIDbuf[i]);
    }
   	  addr += 1;
	  CAN2515_write(addr, canIDbuf[3]);
	  returnValue += canIDbuf[3];

  return returnValue;
}

/******************************************************************************/
/* calculate CAN response messageID
*/

/**
 * Calculate the response CAN ID
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is utility function to calculate CAN ID
 *                  for the MCP2515 CAN Controller
 *
 * Note:            The 'Human' readable CAN ID needs to be mapped into
 *                  the correct registers.
*/
unsigned long encodeRespondToID(unsigned long canID, unsigned char type)
{
  int i = 0;
  static unsigned long can_ID;
  unsigned char byteVal;
  unsigned char extended = type;
  static unsigned char canIDbuf[4] = {0x00, 0x00, 0x00, 0x00};
  unsigned long int returnValue = 0x00000000;

  can_ID = canID;

  if(CANFlags.DEBUG)
   {
	 canIDbuf[0] = (can_ID & 0xFF000000) >> 24;
	 canIDbuf[1] = (can_ID & 0x00FF0000) >> 16;
	 canIDbuf[2] = (can_ID & 0x0000FF00) >> 8;
	 canIDbuf[3] = (can_ID & 0x000000FF);
	 }
//   else
  //     {
	//	 extended = CAN2515_read(reg + 0x02);
	  // }

    	 if(extended & 0x08)
          {
	       // extended message
		   canIDbuf[3] =  can_ID & 0xFF;
	       canIDbuf[2] =  (can_ID >> 0x08) & 0xFF;

		   can_ID = canID >> 16;

	       canIDbuf[1] =  can_ID & 0x03;
	       canIDbuf[1] +=  (can_ID & 0x1C) << 3;
  	       canIDbuf[1] |=  0x08; //set .exide bit

	       canIDbuf[0] =  can_ID >>5;
	    }
	     else
		    {
		     //standard message
			 can_ID = canID & 0xFFFF;

		     canIDbuf[0] =  can_ID >> 0x03;
		     canIDbuf[1] = (can_ID & 0x07) << 0x05 ;
		     canIDbuf[2] =  0;
		     canIDbuf[3] =  0;
		   	}

	for(i=0;i<3;i++)
    {
      returnValue = (returnValue + canIDbuf[i]) << 8;
    }

	  returnValue += canIDbuf[3];

    return returnValue;
}


/****************************************************************************/
/* Decode CAN identifier
*/


/**
 * Decode the CAN ID
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is utility function to calculate CAN ID
 *                  from the MCP2515 CAN Controller to 'Human' readable form
 *
 * Note:            The 'Human' readable CAN ID needs to be mapped from
 *                  the correct registers.
*/
void decodeIdentifier(unsigned long can_ID, unsigned char extended)
{
  unsigned long byteVal;
  unsigned long CAN_ident;
  unsigned long canFrameX_ID;
  static unsigned char canIDbuf[4] = {0x00, 0x00, 0x00, 0x00};

	 canIDbuf[3] = 0x00;
	 canIDbuf[2] = 0x00;
	 canIDbuf[1] = (char)can_ID >> 8;
	 canIDbuf[0] = (char)can_ID & 0x0F;


	////canFrame.IDENTIFIER = 0x0000;

	 ////canIDbuf[0] = CAN2515_read(can_ID + 1);
	 ////canIDbuf[1] = CAN2515_read(can_ID + 2);
	 ////canIDbuf[2] = CAN2515_read(can_ID + 3);
	 ////canIDbuf[3] = CAN2515_read(can_ID + 4);


/*********************************************************************
* Test Code
	 ////canIDbuf[0] = 0xFB;
	 ////canIDbuf[1] = 0xE0;
	 ////canIDbuf[2] = 0x00;
	 ////canIDbuf[3] = 0x00;
	 ////extended = 0x00;

     ////canIDbuf[0] = 0xC6;
	 ////canIDbuf[1] = 0xCA;
	 ////canIDbuf[2] = 0x33;
	 ////canIDbuf[3] = 0xF1;
	 ////extended = 0x08;
*********************************************************************/
  //  Nop();

    // get standard id first

	CAN_ident = canIDbuf[0];
	CAN_ident = CAN_ident << 3;


	can_ID = (canIDbuf[1] & 0xE0) >> 5;
	CAN_ident = CAN_ident | can_ID;

	// if it is an extended id shift the canID up to make room
	// for the extended data

	 if(extended == _EXTENDED)
      {
       CAN_ident = CAN_ident << 18;

		// now recover EID17-16
		byteVal = canIDbuf[1] & 0x03;
	    CAN_ident |= (byteVal << 16);

	   // now extract the next byte
	   byteVal = canIDbuf[2];
	   CAN_ident |= (byteVal << 8);

	   // and the final byte
	   CAN_ident |= canIDbuf[3];

	   canFrameX_ID |= CAN_ident;
	  }
      else
        {
	 IDENTIFIER |= CAN_ident;
        }

//     Nop();

}


/********************************************************************************/
/* CAN messages -> Identifiers
*/

/**
 * Calculate the CAN ID
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           CTRL
 *                  target
 *                  type
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is utility function to calculate CAN ID
 *                  for the MCP2515 CAN Controller
 *
 * Note:            The 'Human' readable CAN ID needs to be mapped into
 *                  the correct registers for the given message.
*/

void setMsgTarget(unsigned char CTRL, unsigned long target, unsigned char type)
{
    unsigned long CAN_ident;
	unsigned int can_ID;

	static unsigned char canIDbuf[4] = {0x00, 0x00, 0x00, 0x00};

   //unsigned long encodeIdentifier(unsigned char reg, unsigned long canID, unsigned char type)

	CAN_ident = encodeIdentifier(CTRL, target, type);
	 canIDbuf[0] = (CAN_ident & 0xFF000000) >> 24;
	 canIDbuf[1] = (CAN_ident & 0x00FF0000) >> 16;
	 canIDbuf[2] = (CAN_ident & 0x0000FF00) >> 8;
	 canIDbuf[3] = (CAN_ident & 0x000000FF);

    //prepare to load the registers
	//CANFlags.cs_CAN_1 = 1;

	// get standard id first
	can_ID = canIDbuf[0];
	CAN2515_write(CTRL + 1, can_ID);

    can_ID = canIDbuf[1];
	CAN2515_write(CTRL + 2, can_ID);

	can_ID = canIDbuf[2];
	CAN2515_write(CTRL + 3, can_ID);

	can_ID = canIDbuf[3];
	CAN2515_write(CTRL + 4, can_ID);

	CAN2515_write(CTRL + 5, 0x08);


}

/********************************************************************************/
/*  Get operating mode
*/

/**
 * Get the operating mode of the CAN controller
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the single point for retrieving the CAN mode
 *                  for the MCP2515 CAN Controller
 *
 * Note:            None
*/

unsigned char CAN2515_getmode(void)
{
  unsigned char mode;
  mode = CAN2515_read(CAN2515_REG_CANSTAT);

  return (mode & 0xE0);         // Mask off the OPMODE2:OPMODE0 bits and return this value
					  	// This indicates the MCP2515s current mode
}


/********************************************************************************/
/*  Set operating mode
*/

/**
 * Set the operating mode of the CAN controller
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the single point for setting the CAN mode
 *                  for the MCP2515 CAN Controller
 *
 * Note:            None
*/

void CAN2515_setmode(unsigned char mode)
{
  //CAN2515_write(CAN2515_REG_CANCTRL, mode);

 CAN2515_bitmodify(CAN2515_REG_CANCTRL, 0xE0, mode);

}

#endif


