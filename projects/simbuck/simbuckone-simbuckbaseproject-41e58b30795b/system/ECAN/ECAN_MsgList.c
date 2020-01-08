/********************************************************************
 FileName:	ECAN_MsgList.c
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

  1.0.0 First release for Simbuck

*******************************************************************************/


/* I N C L U D E S ************************************************************/
#include <p18cxxx.h>
#include "simbuck_cfg.h"
#include "../HardwareProfile.h"
#include "ECAN_MsgList.h"
#include "ECAN_User.h"

/* V A R I A B L E S ********************************************************/
#pragma udata
ECAN_MESSAGES ECAN_messages;      ///< structure for ECAN fixed messages
ECAN_FLAGS ECANFlags;             ///< structure for CAN user semaphore
WORD IDENTIFIER;                  ///< CAN message Identifier

/* D E C L A R A T I O N S ****************************************************/
#pragma code

/**
 * CAN Frame message definition
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Changes the Target Id and D0-D7 data for transmit buffer 0
 *
 * Overview:        This function creates a CAN Frame message definition
 *
 * Note:            None
*/
void ECAN_DataFrame_1_Message(void)
{
   setMsgTarget(ECAN_DATA_FRAME_1_BUFFER, ECAN_DATA_FRAME_1, _STANDARD);
        
        TXB0D0 = TXB0SIDH;
        TXB0D5 = 0x00;
        TXB0D6 = 0x00;
	TXB0D7 = TXB0SIDL;
        

}


/**
 * CAN Frame message definition
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Changes the Target Id and D0-D7 data for transmit buffer 1
 *
 * Overview:        This function creates a CAN Frame message definition
 *
 * Note:            None
*/
void ECAN_DataFrame_2_Message(void)
{
   setMsgTarget(ECAN_DATA_FRAME_2_BUFFER, ECAN_DATA_FRAME_2, _STANDARD);

        TXB1D0 = TXB1SIDH;
        TXB1D5 = 0x00;
        TXB1D6 = 0x00;
	TXB1D7 = TXB1SIDL;

}

/**
 * CAN Frame message definition
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Changes the Target Id and D0-D7 data for Transmit Buffer 2
 *
 * Overview:        This function creates a CAN Frame message definition
 *
 * Note:            None
*/
void ECAN_DataFrame_3_Message(void)
{
   setMsgTarget(ECAN_DATA_FRAME_3_BUFFER, ECAN_DATA_FRAME_3, _STANDARD);

        TXB2D0 = TXB2SIDH;
        TXB2D5 = 0x00;
        TXB2D6 = 0x00;
	TXB2D7 = TXB2SIDL;


}

/**
 * CAN Frame message definition
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Changes the Target Id and D0-D7 data for transmit buffer 0
 *
 * Overview:        This function creates a CAN Frame message definition
 *
 * Note:            None
*/
void ECAN_DataFrame_4_Message(void)
{
   setMsgTarget(ECAN_DATA_FRAME_4_BUFFER, ECAN_DATA_FRAME_4, _STANDARD);

	TXB0D0 = TXB0SIDH;
       	TXB0D7 = TXB0SIDL;

}


/**
 * CAN Frame message definition
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Changes the Target Id and D0-D7 data transmit buffer 1
 *
 * Overview:        This function creates a CAN Frame message definition
 *
 * Note:            None
*/
void ECAN_DataFrame_5_Message(void)
{
   setMsgTarget(ECAN_DATA_FRAME_5_BUFFER, ECAN_DATA_FRAME_5, _STANDARD);

	TXB1D0 = TXB1SIDH;
	TXB1D7 = TXB1SIDL;

}


/**
 * CAN Frame message definition
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function creates a CAN Frame message definition
 *
 * Note:            None
*/
void ECANSelfTestMessage(void)
{
   setMsgTarget(TXB0CTRL, ECAN_SELFTEST_FRAME, _STANDARD);

	TXB0D0 = PORTB;
	TXB0D1 = 0x01;
	TXB0D2 = 0x10;
	TXB0D3 = 0x20;
	TXB0D4 = 0x80;
	TXB0D5 = 0x55;
	TXB0D6 = 0x91;
	TXB0D7 = 0x91;

       


}


/**
 * CAN Frame message definition
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function creates a CAN Frame message definition
 *
 * Note:            None
*/
void ECANCtrlMessage(void)
{
   setMsgTarget(TXB2CTRL, ECAN_CONTROL_FRAME, _STANDARD);

	TXB2D0 = 0x00;
	TXB2D1 = 0x00;
	TXB2D2 = 0x01;
	TXB2D3 = 0x00;
	TXB2D4 = 0x00;
	TXB2D5 = 0x00;
	TXB2D6 = 0x93;
	TXB2D7 = 0x93;



}

/**
 * CAN Frame message definition
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function creates a CAN Frame message definition
 *
 * Note:            None
*/
void ECAN_DataFrame_Message(void)
{
   setMsgTarget(TXB1CTRL, ECAN_DATA_FRAME, _STANDARD);

	TXB1D0 = PORTB;
	TXB1D1 = 0x01;
	TXB1D2 = 0x10;
	TXB1D3 = 0x20;
	TXB1D4 = 0x80;
	TXB1D5 = 0x55;
	TXB1D6 = 0x92;
	TXB1D7 = 0x92;


}


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
  //unsigned char byteVal;
  static unsigned char addr;
  unsigned char extended = type;
  static unsigned char canIDbuf[4] = {0x00, 0x00, 0x00, 0x00};
  unsigned long int returnValue = 0x00000000;

  unsigned char *BUFFER_ptr;

    // make sure the transmit buffers are in the Access Bank
    CANCONbits.WIN2 = 1;
    CANCONbits.WIN1 = 1;
    CANCONbits.WIN0 = 1;

   //get the address of the register
   BUFFER_ptr = &TXB2CON;
   BUFFER_ptr += reg;

  addr = reg;
  can_ID = canID;

  if(ECANFlags.DEBUG)
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
	  addr = canIDbuf[i];
          BUFFER_ptr+=1;
          *BUFFER_ptr = canIDbuf[i];
    }
   	  addr += 1;
	  addr = canIDbuf[3];
	  returnValue += canIDbuf[3];
           BUFFER_ptr+=1;
          *BUFFER_ptr = canIDbuf[3];

          BUFFER_ptr+=1;
          *BUFFER_ptr = DLC;

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
/*unsigned long encodeRespondToID(unsigned long canID, unsigned char type)
{
  int i = 0;
  static unsigned long can_ID;
  unsigned char byteVal;
  unsigned char extended = type;
  static unsigned char canIDbuf[4] = {0x00, 0x00, 0x00, 0x00};
  unsigned long int returnValue = 0x00000000;

  can_ID = canID;

  if(ECANFlags.DEBUG)
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
*/
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
unsigned long decodeIdentifier(unsigned long can_ID, unsigned char extended)
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

        return CAN_ident;
}


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
 *                  for the ECAN Controller
 *
 * Note:            The 'Human' readable CAN ID needs to be mapped into
 *                  the correct registers for the given message.
*/

void setMsgTarget(unsigned char reg, unsigned long target, unsigned char type)
{

  int i;
  unsigned char *BUFFER_ptr;

  static unsigned long can_ID;
  static unsigned char canIDbuf[4] = {0x00, 0x00, 0x00, 0x00};

  // make sure the transmit buffers are in the Access Bank
    CANCONbits.WIN2 = 1;
    CANCONbits.WIN1 = 1;
    CANCONbits.WIN0 = 1;

   //get the address of the register
   BUFFER_ptr = &TXB2CON;
   BUFFER_ptr += reg;

  if(ECANFlags.DEBUG)
   {
     can_ID = target;
     canIDbuf[0] = (can_ID & 0xFF000000) >> 24;
     canIDbuf[1] = (can_ID & 0x00FF0000) >> 16;
     canIDbuf[2] = (can_ID & 0x0000FF00) >> 8;
     canIDbuf[3] = (can_ID & 0x000000FF);
  }

    	 if(type & 0x08)
          {
	       // extended message
	   canIDbuf[3] =  can_ID & 0xFF;
	   canIDbuf[2] =  (can_ID >> 0x08) & 0xFF;

	   can_ID = target >> 16;

	       canIDbuf[1] =  can_ID & 0x03;
	       canIDbuf[1] +=  (can_ID & 0x1C) << 3;
  	       canIDbuf[1] |=  0x08; //set .exide bit

	       canIDbuf[0] =  can_ID >>5;
	    }
	     else
		{
		//standard message
		 can_ID = target & 0xFFFF;

		 canIDbuf[0] =  can_ID >> 0x03;
		 canIDbuf[1] = (can_ID & 0x07) << 0x05 ;
		 canIDbuf[2] =  0;
		 canIDbuf[3] =  0;
               }

  for(i=0;i<3;i++)
    {
     BUFFER_ptr+=1;
    *BUFFER_ptr = canIDbuf[i];
    }

   BUFFER_ptr+=1;
   *BUFFER_ptr = canIDbuf[3];

   BUFFER_ptr+=1;
   *BUFFER_ptr = DLC;
}
