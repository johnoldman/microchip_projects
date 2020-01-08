/********************************************************************
 FileName:	user_32.c
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

/* INCLUDES ******************************************************************/
 #include <plib.h>

#include "simbuck_cfg.h"
#include "HardwareProfile.h"

#include "USB/usb.h"
#include "USB/usb_function_generic.h"
#include "USB/usb_hal_pic32.h"
#include "user/user_32.h"
#include "processUSBpacket.h"


/* S I M L I B   I N C L U D E S **********************************************************/
#if defined(SIMBLOCK_DUAL_CAN)
  #include "HardwareProfile - SimblockDualCAN.h"
  #include "system/spi/simbuckspi.h"
  #include "system/CAN/CAN2515drv.h"
  #include "system/CAN/CAN2515user.h"
  #include "system/CAN/CAN2515utils.h"
  #include "system/CAN/CAN_MsgList.h"

#endif

#if defined(SIMBLOCK_BATTMON_ADC)

#endif

/* D I S P L A Y S    I N C L U D E S **********************************************************/
#if defined(DISPLAY_4DSYSTEMS)
  #include "display/display4d.h"
  #include "system/serial/simbuckserial.h"
#endif

#if defined(DISPLAY_BATRON)
  #include "display/sed1565.h"
#endif

/* C O M M O N  V A R I A B L E S *****************************************************/
#pragma udata

#if defined(SIMBLOCK_DUAL_CAN)
extern volatile CAN_FLAGS CANFlags;  ///< structure for CAN semaphore
extern CAN_PERF CANPerf;             ///< structure for CAN performance data


#endif



/* D E C L A R A T I O N S **************************************************/
#pragma code

/**
 * entry point for the users functions
 *
 * PreCondition:    All configurations and setup function have been executed
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is the entry point for the users functions
 *
 * Note:            None
 */
int ProcessUser32(void)
{
    // called from main from the while(1) loop
    // this is where the Users function call(s) go

    #if defined(SIMBLOCK_DUAL_CAN)

/* S E N D   M E S S A G E   L O O P *****************************************/

	if(CANFlags.snd_tmr_10)
	 {
           CANFlags.snd_tmr_10=0;

           // Decide which CAN node to use
	    Select_CAN_1();
             CANFlags.cs_CAN_1 = 0;
              // Populate the data as required

	      CAN2515_write(TXB0D3, CANPerf.msgs_sent_can_1);
              CAN2515_write(TXB0D4, CANPerf.msgs_rcvd_can_2);
              CAN2515_write(TXB0D5, CANPerf.msgs_missed_can_1);

            Select_CAN_1();
             CANFlags.cs_CAN_1 = 0;
             CANFlags.snd_CAN_1_BUFF=1;
	        CANsend(_B0);
             CANFlags.snd_CAN_1_BUFF=0;
             CANFlags.cs_CAN_1 = 1;
            DeSelect_CAN_1();

            CANPerf.msgs_sent_can_1++;



	 }


        if(CANFlags.snd_tmr_100)
	 {
           CANFlags.snd_tmr_100=0;

           #if defined(USE_CAN_2)
           // Decide which CAN node to use
	    Select_CAN_2();
             CANFlags.cs_CAN_2 = 0;

             // Populate the data as required

	      CAN2515_write(TXB0D3, CANPerf.msgs_sent_can_2);
              CAN2515_write(TXB0D4, CANPerf.msgs_rcvd_can_1);
              CAN2515_write(TXB0D5, CANPerf.msgs_missed_can_2);

            Select_CAN_2();
             CANFlags.cs_CAN_2 = 0;
             CANFlags.snd_CAN_2_BUFF=1;
	       CANsend(_B0);
             CANFlags.snd_CAN_2_BUFF=0;
	     CANFlags.cs_CAN_2 = 1;
            DeSelect_CAN_2();

            CANPerf.msgs_sent_can_2++;

	 }

    	if(CANFlags.snd_tmr_1000)
	 {
           CANFlags.snd_tmr_1000=0;

           // Decide which CAN node to use
	    Select_CAN_1();
             CANFlags.cs_CAN_1 = 0;
              // Populate the data as required
              CAN2515_write(TXB1D0, CANPerf.msgs_sent_can_1-1);
              CAN2515_write(TXB1D1, CANPerf.msgs_rcvd_can_2);
              CAN2515_write(TXB1D2, CANPerf.msgs_missed_can_1);
              CAN2515_write(TXB1D4, CANPerf.msgs_sent_can_2-1);
              CAN2515_write(TXB1D5, CANPerf.msgs_rcvd_can_1);
              CAN2515_write(TXB1D6, CANPerf.msgs_missed_can_2);

             CANFlags.cs_CAN_1 = 1;
            DeSelect_CAN_1();

            Select_CAN_1();
             CANFlags.cs_CAN_1 = 0;
             CANFlags.snd_CAN_1_BUFF=1;
	        CANsend(_B1);
             CANFlags.snd_CAN_1_BUFF=0;
             CANFlags.cs_CAN_1 = 1;
            DeSelect_CAN_1();

            #endif
	 }


/* E N D  S E N D  M E S S A G E  L O O P ************************************/


/* R E C E I V E   M E S S A G E S *******************************************/


     /* Check to see if we have an interrupt on the 2515 */

     if((PORTB & CAN_INT_1_MASK) == 0)                // MCP2515 INT pin is Active Low
      {

       CANPerf.msgs_rcvd_can_1++;

        Select_CAN_1();
        CANFlags.cs_CAN_1 = 0;
        CANreceive();
         CAN2515_clearIntFlags();
        CANFlags.cs_CAN_1 = 1;
       DeSelect_CAN_1();

      }

     if((PORTB & CAN_INT_2_MASK) == 0)               // MCP2515 INT pin is Active Low
      {

       CANPerf.msgs_rcvd_can_2++;

      Select_CAN_2();
       CANFlags.cs_CAN_2 = 0;
       CANreceive();
        CAN2515_clearIntFlags();
       CANFlags.cs_CAN_2 = 1;
      DeSelect_CAN_2();

     }




/* E N D  R E C E I V E   M E S S A G E S ************************************/

        #endif

 return 0;
}



/* EOF user_32.c **************************************************************/

