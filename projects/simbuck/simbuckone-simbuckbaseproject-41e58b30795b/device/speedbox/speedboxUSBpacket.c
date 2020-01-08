/********************************************************************
 FileName:		speedboxUSBpacket.c
 Dependencies:	See INCLUDES section
 Processor:		PIC18 USB Microcontrollers
 Hardware:		This demo is natively intended to be used on Microchip USB demo
 				boards supported by the MCHPFSUSB stack.  See release notes for
 				support matrix.  This demo can be modified for use on other hardware
 				platforms.
 Complier:  	Microchip C18 (for PIC18)
 Company:		Deben Enterprises Ltd.

/** I N C L U D E S **********************************************************/
#include "simbuck_cfg.h"
#include "HardwareProfile.h"

#if defined(SIMBUCK_BASEBOARD_4550) || defined(SIMBUCK_SPEEDBOX_4550)
 #include <p18cxxx.h>
#endif

#if defined(SIMBUCK_BASEBOARD_PIC32)
 #include <plib.h>
#endif

#include "speedboxUSBpacket.h"
#include "system/eeprom/eeprom.h"
#include "../USB/usb.h"
#include "../USB/usb_function_generic.h"
#include "speedbox/simstat/simstat.h"


/** V A R I A B L E S ********************************************************/
#pragma udata
extern unsigned char OUTPacket[64];		//User application buffer for receiving and holding OUT packets sent from the host
extern unsigned char INPacket[64];		//User application buffer for sending IN packets to the host
extern USB_HANDLE USBGenericInHandle;
extern USB_HANDLE USBGenericOutHandle;

extern volatile SIG_CONFIG SIGconfig;

/** D E C L A R A T I O N S **************************************************/
#pragma code


/******************************************************************************
 * Function:        void ProcessUSB(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is a place holder for user USB message
 * 		    Structure(s).
 *
 *
 * Note:            The user is expected to populate this function to pass
 *		    relevant data over the USB connection
 *****************************************************************************/
void ProcessUSB(void)
{
    char i;
    char offset;
    char reclen;

	// echo back the request
	INPacket[0] = OUTPacket[0];
	INPacket[1] = OUTPacket[1];
        INPacket[2] = 0x00;

        switch(OUTPacket[0])	//Data arrived
        {
	 case DEVICE_VERSION:    // Version request 0x00
	  switch(OUTPacket[1])
	    {
	     case 0:        // Usb stack version
		#if defined(MCHPFSUSB)
		  INPacket[2] = MAJOR_VERSION_USB;
		  INPacket[3] = MINOR_VERSION_USB;
                  INPacket[4] = DEBUG_VERSION_USB;
                #endif

                #if defined(HID_BOOTLOADER)
                  INPacket[2] = STACK_YEAR_USB;
		  INPacket[3] = STACK_MONTH_USB;
		  INPacket[4] = STACK_DAY_USB;
                #endif

                 INPacket[5] = BOOTLOAD_TYPE;

	     break;

	     case 1:        // Baseboard firmware version
	        INPacket[5] = BOOTLOAD_TYPE;
                INPacket[6] = MAJOR_VERSION_DB;
		INPacket[7] = MINOR_VERSION_DB;
		INPacket[8] = DEBUG_VERSION_DB;
                
             break;

             case 2:        // Firmware and USB stack version
                #if defined(MCHPFSUSB)
		  INPacket[2] = MAJOR_VERSION_USB;
		  INPacket[3] = MINOR_VERSION_USB;
                  INPacket[4] = DEBUG_VERSION_USB;
                #endif

                #if defined(HID_BOOTLOADER)
                  INPacket[2] = STACK_YEAR_USB;
		  INPacket[3] = STACK_MONTH_USB;
		  INPacket[4] = STACK_DAY_USB;
                #endif

                  INPacket[5] = BOOTLOAD_TYPE;
		  INPacket[6] = MAJOR_VERSION_DB;
		  INPacket[7] = MINOR_VERSION_DB;
		  INPacket[8] = DEBUG_VERSION_DB;

             break;

             default:
		INPacket[2] = NEGATIVE_RESPONSE;
		INPacket[3] = NOT_SUPPORTED;
            }
          break;

         case READ_EEPROM:    // 0x14 Read the EEPROM data from PC application.
             // we use the second byte for the data segment
             offset = OUTPacket[1];
             INPacket[3] = ReadFromEEPROM(offset);
            
         break;

         case WRITE_EEPROM:    // 0x15 Write the EEPROM data from PC application.
             // we use the second byte for the data segment
             offset = OUTPacket[1];
             reclen = OUTPacket[2];

             for(i=0;i<6;i++)
             {
               WriteToEEPROM(OUTPacket[2+i], offset+i);
               INPacket[4+i] = OUTPacket[2+i];
             }
            
             INPacket[3] = SUCCESS;

         break;

        case GET_BLOCK:         // 0x16 Read Config record from EEPROM
                                // we use the second byte for the data segment
                                // we use 3rd byte to define number bytes to read
             offset = OUTPacket[1];
             reclen = OUTPacket[2];

              for(i=0;i<reclen;i++)
              {
               INPacket[4+i] = ReadFromEEPROM(offset+i);
              }

             INPacket[3] = SUCCESS;

        break;

            case READ_INPUTS:  // 0x17 Selector Switch state
                
                INPacket[2] = LATD;
                INPacket[3] = PORTD;
                INPacket[4] = TRISD;

                INPacket[5] = LATB;
                INPacket[6] = PORTB;
                INPacket[7] = TRISB;

            break;

           #if defined(SIMBUCK_BASEBOARD_4550) || defined(SIMBUCK_SPEEDBOX_4550)
           case READ_RELAYS:  // 0x18 Relay states

                INPacket[2] = mROP_1_2;
                INPacket[3] = mROP_3_4;

            break;
           #endif

            case READ_PORTS:  // 0x3A
            #if defined(SIMBUCK_BASEBOARD_4550) || defined(SIMBUCK_SPEEDBOX_4550)
                INPacket[2] = PORTA;
            #endif
                INPacket[3] = PORTB;
                INPacket[4] = PORTC;
                INPacket[5] = PORTD;
                INPacket[6] = PORTE;

            break;

           case READ_PATTERN:  // 0x5A
                
                INPacket[4] = SIGconfig.num_Teeth;
                INPacket[5] = SIGconfig.num_GapTeeth;
                INPacket[6] = SIGconfig.CID_Start;

                for(i=0;i<7;i++)
                  {
                   INPacket[7+i] = SIGconfig.CID_teeth[i];
                  }


           break;

            #if defined(SIMBUCK_BASEBOARD_4550) || defined(SIMBUCK_SPEEDBOX_4550)
            case RESET_DEVICE:                  // Copied direct from HID Bootloader
	       {
		 UCONbits.SUSPND = 0;		//Disable USB module
		 UCON = 0x00;			//Disable USB module
		//And wait awhile for the USB cable capacitance to discharge down to disconnected (SE0) state.
		//Otherwise host might not realize we disconnected/reconnected when we do the reset.
		//A basic for() loop decrementing a 16 bit number would be simpler, but seems to take more code space for
		//a given delay.  So do this instead:
		for(i = 0; i < 0xFF; i++)
		  {
		    WREG = 0xFF;
		    while(WREG)
			{
			 WREG--;
			 _asm
			 bra	0	//Equivalent to bra $+2, which takes half as much code as 2 nop instructions
			 bra	0	//Equivalent to bra $+2, which takes half as much code as 2 nop instructions
			 _endasm
			}
		   }
		 Reset();
		}
		break;
            #endif

	default:
              INPacket[0] = ERROR_RESPONSE;
              INPacket[1] = NOT_SUPPORTED;
        }


	//Now check to make sure no previous attempts to send data to the host are still pending.  If any attemps are still
	//pending, we do not want to write to the endpoint 1 IN buffer again, until the previous transaction is complete.
	//Otherwise the unsent data waiting in the buffer will get overwritten and will result in unexpected behavior.
        if(!USBHandleBusy(USBGenericInHandle))
	  {
	           //The endpoint was not "busy", therefore it is safe to write to the buffer and arm the endpoint.
	           //The USBGenWrite() function call "arms" the endpoint (and makes the handle indicate the endpoint is busy).
	           //Once armed, the data will be automatically sent to the host (in hardware by the SIE) the next time the
	           //host polls the endpoint.  Once the data is successfully sent, the handle (in this case USBGenericInHandle)
	           //will indicate the the endpoint is no longer busy.
		   USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM,(BYTE*)&INPacket,USBGEN_EP_SIZE);
        }


 }//end ProcessIO






/** EOF user.c ***************************************************************/

