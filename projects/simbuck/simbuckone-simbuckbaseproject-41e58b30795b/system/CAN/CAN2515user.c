/********************************************************************
 FileName:	CAN2515user.c
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
  1.0  First release

********************************************************************/


/* I N C L U D E S **********************************************************/

#include "simbuck_cfg.h"
#include "../HardwareProfile.h"
#include "../HardwareProfile - SimblockDualCAN.h"

#if defined(SIMBUCK_BASEBOARD_4550)
 #include <p18cxxx.h>

#endif


#if defined(SIMBLOCK_DUAL_CAN)
#include "GenericTypeDefs.h"
#include "../system/spi/simbuckspi.h"
#include "CAN2515drv.h"
#include "CAN2515user.h"
#include "CAN2515utils.h"
#include "CAN_useCAN1.h"
#include "CAN_useCAN2.h"

/* V A R I A B L E S ********************************************************/
#pragma udata

CAN_PERF CANPerf;
extern CAN_FLAGS CANFlags;

extern unsigned char CAN_1_rcv[14];
extern unsigned char CAN_2_rcv[14];

/* P R O T T Y P E S ********************************************************/


/* D E C L A R A T I O N S *************************************************/
#pragma code

/****************************************************************************/
/* 2515 high level functions						*/
/* Reference document - Microchip Datasheet 210801e			*/
/* Document Title - Stand-Alone CAN Controller with SPI Interface       */
/* 									*/
/*	Implements: 							*/
/*			CAN2515_getmode					*/
/*			CAN2515_setmode					*/
/*									*/
/*    Helper functions:							*/
/*			CAN2515_select					*/
/*			CAN2515_unselect				*/
/*									*/
/****************************************************************************/


/**
 * receive a CAN frame
 *
 * PreCondition:    2515CAN_init must have been run
 *
 * Input:           None
 *
 * Output:          Retrieve data from previously determined Controller
 *
 *
 * Side Effects:    None
 *
 * Overview:        This function is the key source of CAN data for
 *		    the High Level Protocol[HLP]
 *
 * Note:            None
 */

void CANreceive(void)
{
   unsigned char rx_statflag;
   unsigned char rx_type;
   unsigned char rx_recv;
   unsigned char rx_filter;

   unsigned int retVal;

	 // check the received message
	  rx_statflag = CAN2515_read_rxstatus();

          // which receive buffer
	  rx_recv = (rx_statflag & 0xC0) >> 6;

	  // what type of message has been received
	  // Std, Std remote, extd, extd remote
	  rx_type = (rx_statflag & 0x18) >> 3;

	  // which  filter let it in
	  rx_filter = rx_statflag & 0x07;

          switch(rx_statflag & 0xC0)
	   {
	    case 64:
		  CAN2515_readRx(RXB0SIDH, 0);
                  if(CANFlags.int_CAN_1)
                  {
                  CANFlags.proc_CAN_1_0 = 1;            // data in CAN_1_rcv
                  }
                  else
                    {
                     CANFlags.proc_CAN_2_0 = 1;            // data in CAN_2_rcv
                    }
		  break;

	    case 128:
		   CAN2515_readRx(RXB1SIDH, 0);
		   if(CANFlags.int_CAN_1)
                    {
                    CANFlags.proc_CAN_1_0 = 1;            // data in CAN_1_rcv
                    }
                    else
                      {
                       CANFlags.proc_CAN_2_0 = 1;         // data in CAN_2_rcv
                      }
                 break;

	    case 192:                                   // we have been slow and messsages are
                                                        // piling up!
	      CAN2515_readRx(RXB0SIDH, 0);
                if(CANFlags.int_CAN_1)
                  {
                  CANFlags.proc_CAN_1_0 = 1;            // data in CAN_1_rcv
                  }
                  else
                    {
                     CANFlags.proc_CAN_2_0 = 1;         // data in CAN_2_rcv
                    }
	      CAN2515_readRx(RXB1SIDH, 3);
		if(CANFlags.int_CAN_1)
                  {
                  CANFlags.proc_CAN_1_1 = 1;            // data in CAN_3_rcv
                  }
                  else
                    {
                     CANFlags.proc_CAN_2_1 = 1;        // data in CAN_4_rcv
                    }
              break;

	  default:
	     retVal = (rx_statflag << 8);
		  CAN2515_write(CAN2515_REG_CANINTF, 0x00);
//		  CANFlags.msg_CAN=0;
	     break;

  	}

  

}

/**
 * send CAN frame
 *
 * PreCondition:     2515CAN_init must have been run
 *
 * Input:             buff -> the Transmit buffer(s) that need to be sent
 *
 * Output:           Transmits pre-loaded CAN frame from defined TX buffer
 *
 * Side Effects:    None
 *
 * Overview:        This function is the key source of CAN data to request
 *		    additional data from the Control module and/or eanble/enact
 * 		    pre-defined functions
 *
 * Note:            None
 *
 */

void CANsend(unsigned char buff)
{

   if(CANFlags.DEBUG == 1)
	return;

	 switch(buff)
		{

			case 0:
			// Send _B0
			CAN2515_write(CAN2515_REG_TXB0CTRL, 0x00);
			CAN2515_rts(CAN2515_RTS_B0);
				//while(CAN2515_readstatus() & 0x10) ;  // wait for TXREQ to clear
			break;

			case 1:
			// Send _B1
			CAN2515_write(CAN2515_REG_TXB1CTRL, 0x00);
			CAN2515_rts(CAN2515_RTS_B1);
				//while(CAN2515_readstatus() & 0x10) ;  // wait for TXREQ to clear
			break;

			case 2:
			// Send _B2
			CAN2515_write(CAN2515_REG_TXB2CTRL, 0x00);
			CAN2515_rts(CAN2515_RTS_B2);
				//while(CAN2515_readstatus() & 0x40) ;  // wait for TXREQ to clear
			break;

			case 3:
			// Send _B0 and _B1
			CAN2515_write(CAN2515_REG_TXB0CTRL, 0x00);
			CAN2515_rts(CAN2515_RTS_B0);
				//while(CAN2515_readstatus() & 0x04) ;  // wait for TXREQ to clear
			CAN2515_write(CAN2515_REG_TXB1CTRL, 0x00);
			CAN2515_rts(CAN2515_RTS_B1);
				//while(CAN2515_readstatus() & 0x10) ;  // wait for TXREQ to clear
			break;

			case 4:
			// Send _B0 and _B2
			CAN2515_write(CAN2515_REG_TXB0CTRL, 0x00);
			CAN2515_rts(CAN2515_RTS_B0);
				//while(CAN2515_readstatus() & 0x04) ;  // wait for TXREQ to clear
			CAN2515_write(CAN2515_REG_TXB2CTRL, 0x00);
			CAN2515_rts(CAN2515_RTS_B2);
				//while(CAN2515_readstatus() & 0x40) ;  // wait for TXREQ to clear
			break;

			case 5:
			// Send _B1 and _B2
			CAN2515_write(CAN2515_REG_TXB1CTRL, 0x00);
			CAN2515_rts(CAN2515_RTS_B1);
				//while(CAN2515_readstatus() & 0x10) ;  // wait for TXREQ to clear
			CAN2515_write(CAN2515_REG_TXB2CTRL, 0x00);
			CAN2515_rts(CAN2515_RTS_B2);
				//while(CAN2515_readstatus() & 0x40) ;  // wait for TXREQ to clear
			break;

			case 6:
			// Send _B0 and _B1 and _B2
			CAN2515_write(CAN2515_REG_TXB0CTRL, 0x00);
			CAN2515_rts(CAN2515_RTS_B0);
				//while(CAN2515_readstatus() & 0x04) ;  // wait for TXREQ to clear
			CAN2515_write(CAN2515_REG_TXB1CTRL, 0x00);
			CAN2515_rts(CAN2515_RTS_B1);
				//while(CAN2515_readstatus() & 0x10) ;  // wait for TXREQ to clear
			CAN2515_write(CAN2515_REG_TXB2CTRL, 0x00);
			CAN2515_rts(CAN2515_RTS_B2);
				//while(CAN2515_readstatus() & 0x40) ;  // wait for TXREQ to clear
			break;


			default:
			break;

		}

}


/********************************************************************************/
/*  getRegister
*/

/**
 * Retrieve the CAN ID of the CAN frame
 *
 * PreCondition:     2515CAN_init must have been run
 *
 * Input:            rxBbuff -> the Transmit buffer(s) that need to be sent
 *
 * Output:           Transmits pre-loaded CAN frame from defined TX buffer
 *
 * Side Effects:    None
 *
 * Overview:        This function is the key source of retrieving the CAN ID
 *                  from the data on the bus.
 *
 * Note:            Retrieving the CAN ID from the data on the bus is only#
 *                  suitable for debug checks. Use the Filter mechanism for
 *                  normal operations.
 *
 */
unsigned long getCANID(unsigned char rxBuff)
{

  unsigned char rcv_addr;
  unsigned long CAN_ident;


	// get the CAN ID - why? I already know from the context
	// what the message type is and from the filter which message
	// is in the buffer! If I choose to do it that way

	if(rxBuff != 1)
	  {
	   CAN_ident = CAN2515_read(RXB0SIDH);      // Read the high byte (SIDH - SID10:SID3);
	   CAN_ident = CAN_ident << 8;
	   CAN_ident += CAN2515_read(RXB0SIDL);	    // Read the low byte (SIDL - SID2:SID0);
	   rcv_addr = RXB0DLC;

	  }
	  else
		  {
		   CAN_ident = CAN2515_read(RXB1SIDH);      // Read the high byte (SIDH - SID10:SID3);
	   	   CAN_ident = CAN_ident << 8;
	   	   CAN_ident += CAN2515_read(RXB1SIDL);	    // Read the low byte (SIDL - SID2:SID0);
		   rcv_addr = RXB1DLC;
		  }

        return CAN_ident;
}


/**
 * read the Receive buffer
 *
 * PreCondition:  2515CAN_init must have been run
 *
 * Input:            rxBuff
 *
 * Output:           none
 *
 *
 * Side Effects:    updates data in the relevant container
 *
 * Overview:       This function is the key source of CAN data
		   from the Control module
 *
 * Note:            None
 */

/****************************************************************************/
void CAN2515_readRX(unsigned char rxBuff)
{
  unsigned char i;

 if(CANFlags.DEBUG == 1)
	return;

 
   if(CANFlags.int_CAN_1)
     {
      
      for(i=0; i<=13; i++)
	{
	 CAN_1_rcv[i] = CAN2515_read(rxBuff);
        }
       }


    if(CANFlags.int_CAN_2 == 1)
      {
       
       for(i=0; i<=13; i++)
	 {
          CAN_2_rcv[i] = CAN2515_read(rxBuff);
  	 }
     
       }

  
}


/********************************************************************************/
/*  Clear down all interrupt flags
*/

/**
 * clear the Interrupt flags in the MCP2515 CAN controller
 *
 * PreCondition:  2515CAN_init must have been run
 *
 * Input:            none
 *
 * Output:           none
 *
 * Side Effects:    updates data in the relevant container
 *
 * Overview:       This function is a utlity function to simplify
 *                 clearing Interrupt flags
 *
 * Note:            None
 */

void CAN2515_clearIntFlags(void)
{
  	//CAN2515_bitmodify(CAN2515_REG_CANINTF, 0xC0, 0x00);
	CAN2515_write(CAN2515_REG_EFLG, 0x00);
	CAN2515_write(CAN2515_REG_CANINTF, 0x00);

}


/********************************************************************************/
/*  getRegister
*/

/**
 * read a register from the MCP2515 CAN controller
 *
 * PreCondition:  2515CAN_init must have been run
 *
 * Input:            none
 *
 * Output:           none
 *
 * Side Effects:    updates data in the relevant container
 *
 * Overview:       This function is a utlity function to enable access to the
 *                 registers of the MCP2515 CAN Controller for debugging
 *
 * Note:            None
 */
unsigned char CAN2515_getregister(unsigned char addr)
{
  unsigned char reg_value;
  //Nop();
	reg_value = CAN2515_read(addr);

  return reg_value;
}

/********************************************************************************/
/* set up the Controller Chip
*/


/**
 * setup the CP2515 CAN controller for use
 *
 * PreCondition:  2515CAN_init must have been run
 *
 * Input:            none
 *
 * Output:           none
 *
 * Side Effects:    updates data in the relevant container
 *
 * Overview:       This function is a utlity function to enable a simplified
 *                 mechanism to configure the MCP2515 CAN Controller
 *
 * Note:            None
 */
unsigned char CAN2515_setcontroller(signed char controller)
{
  unsigned char CANmode;

	if(controller == 0)
	 {
	  Select_CAN_1();
           CANFlags.cs_CAN_1 = 0;
	    CAN2515_config_CAN_1(0);

	      CAN2515_setmode(CAN2515_MODE_NORMAL);
	      CANmode = CAN2515_getmode();

	   CANFlags.cs_CAN_1 = 1;
	  DeSelect_CAN_1();

	}

	if(controller == 1)
	 {
	  Select_CAN_2();
           CANFlags.cs_CAN_2 = 0;
	     CAN2515_config_CAN_2();

	       CAN2515_setmode(CAN2515_MODE_NORMAL);
	       CANmode = CAN2515_getmode();

 	   CANFlags.cs_CAN_2 = 1;
	  DeSelect_CAN_2();
	 }
    return CANmode;
}

void InitCANStatusLED(void)
{

       /* enable LED on RE2 */
       PORTE = 0x00;

       TRISEbits.TRISE2 = OUTPUT_PIN;
        mLED_3_Off();

       TRISEbits.TRISE1 = OUTPUT_PIN;
        mLED_2_Off();

       TRISEbits.TRISE0 = OUTPUT_PIN;
         mLED_1_On();

}

#endif


/********************************************************************************/
/* update register map 															*/

/*unsigned char CAN2515_updatemap(void)
{
	
  CAN2515_regs._CANCTRL = CAN2515_read(CAN2515_REG_CANCTRL);
  CAN2515_regs._CANSTAT = CAN2515_read(CAN2515_REG_CANSTAT);
  CAN2515_regs._CANINTF = CAN2515_read(CAN2515_REG_CANINTF);
  CAN2515_regs._CANINTE = CAN2515_read(CAN2515_REG_CANINTE);
  CAN2515_regs._ERFLG = CAN2515_read(CAN2515_REG_EFLG);  	
  CAN2515_regs._TX0CTRL = CAN2515_read(CAN2515_REG_TXB0CTRL);
  CAN2515_regs._TX1CTRL = CAN2515_read(CAN2515_REG_TXB1CTRL);
  CAN2515_regs._TXRTSCTRL = CAN2515_read(CAN2515_REG_TXRTSCTRL);
  CAN2515_regs._BFPCTRL =  CAN2515_read(CAN2515_REG_BFPCTRL);
  CAN2515_regs._RX0CTRL = CAN2515_read(CAN2515_REG_RXB0CTRL);
  CAN2515_regs._RX1CTRL = CAN2515_read(CAN2515_REG_RXB1CTRL);

  return 0;
}
*/

/* EOF CAN2515user.c ***************************************************************/



