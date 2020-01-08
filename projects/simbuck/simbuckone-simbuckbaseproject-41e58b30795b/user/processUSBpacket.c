/********************************************************************
 FileName:	processUSBpacket.c
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

 ********************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  -----------------------------------------
 1.0.0 First release for Simbuck - Based from original file
                                    supplied for the LIBUSB
                                    demo in the Microchip
                                    solutions Library v2011-07-14

 ********************************************************************/


/* I N C L U D E S **********************************************************/
#include "simbuck_cfg.h"
#include "HardwareProfile.h"
#include "USB/usb.h"
#include "USB/usb_function_generic.h"
#include "processUSBpacket.h"
#include "userInits.h"

#if defined(SIMBUCK_BASEBOARD_4550)
#include <p18cxxx.h>
#include "system/eeprom/eeprom.h"
#include "userInits.h"
#include "selftests/selftest.h"
#endif


#if defined(SIMBLOCK_DUAL_CAN)
#include "HardwareProfile - SimblockDualCAN.h"
#include "../system/CAN/CAN2515drv.h"
#include "../system/CAN/CAN2515user.h"
#include "../system/CAN/CAN2515SelfTest.h"
#endif

/* V A R I A B L E S ********************************************************/
#pragma udata
extern unsigned char OUTPacket[64];
extern unsigned char INPacket[64];
extern USB_HANDLE USBGenericInHandle;
extern USB_HANDLE USBGenericOutHandle;
extern USER_FLAGS USERFlags;
extern MCU_REGS MCU_regs;

#if defined(SIMBLOCK_DUAL_CAN)
extern CAN_FLAGS CANFlags;
extern CAN_PERF CANPerf;

extern unsigned char CAN_1_rcv[14];
extern unsigned char CAN_2_rcv[14];
extern unsigned char CAN_3_rcv[14];
extern unsigned char CAN_4_rcv[14];
extern unsigned char CAN_update; // 0000 0000 no updates
// 0000 0001 rcv 1 update
// 0000 0010 rcv 3 update
// 0000 0100 rcv 2 update
// 0000 1000 rcv 4 update

unsigned short frame_offset = 0x1C; ///< the length of the receiver buffer in bytes;

#endif

/* D E C L A R A T I O N S **************************************************/
#pragma code

/**
 * User USB message structure
 *
 * PreCondition:    USB communications has been established
 *
 * Input:           A Correctly formatted byte stream
 *                           <REQ><CTRL><RECLEN><DATA><DATA..>
 *                  OUTPacket [0]  [1]    [2]    [3]   [..]
 *
 * Output:          The response bytes to the request
 *                          <REQ><CTRL><RECLEN><ERR><DATA><DATA..>
 *                  INPacket [0]  [1]    [2]    [3]  [4]   [5]
 *
 * Side Effects:    None
 *
 * Overview:        This function is a place holder for user USB message
 * 		    Structure(s).
 *                  
 *
 * Note:            The user is expected to populate this function with user
 *		    relevant data over the USB connection
 */

void ProcessUSB(void) {
    char i, mode, ctrl;
    char offset;
    char reclen;
    char monitor;
    char stat_LED;
    char chipselect;

    // echo back the request
    mode = OUTPacket[0];
    ctrl = OUTPacket[1];
    INPacket[0] = mode;
    INPacket[1] = ctrl;
    

    switch (OUTPacket[0]) //Data arrived
    {
        case DEVICE_VERSION: // Version request 0x00
        {
            switch (OUTPacket[1]) {
                case 1: // Usb stack version
#if defined(MCHPFSUSB)
                    INPacket[3] = MAJOR_VERSION_USB;  // USB Stack
                    INPacket[4] = MINOR_VERSION_USB;
                    INPacket[5] = DEBUG_VERSION_USB;

                    INPacket[2] = 0x06;
                    break;
#endif

#if defined(HID_BOOTLOADER)
                    INPacket[3] = STACK_YEAR_USB;     // USB Stack
                    INPacket[4] = STACK_MONTH_USB;
                    INPacket[5] = STACK_DAY_USB;

                    INPacket[2] = 0x06;
                    break;
#endif
#if defined(MCHPFSUSB)
                case 2: // Baseboard firmware version
                    INPacket[3] = MAJOR_VERSION_USB;  // USB Stack
                    INPacket[4] = MINOR_VERSION_USB;
                    INPacket[5] = DEBUG_VERSION_USB;

                    INPacket[6] = BOOTLOAD_TYPE;
                    INPacket[7] = MAJOR_VERSION_DB;     // Firmware
                    INPacket[8] = MINOR_VERSION_DB;
                    INPacket[9] = DEBUG_VERSION_DB;

                    INPacket[2] = 0x0A;
                    break;
#endif
 #if defined(HID_BOOTLOADER)
                case 2: // Firmware

                    INPacket[3] = STACK_YEAR_USB;
                    INPacket[4] = STACK_MONTH_USB;
                    INPacket[5] = STACK_DAY_USB;

                    INPacket[6] = BOOTLOAD_TYPE;

                    INPacket[7] = SIMBUCK_BOOT_MAJOR;
                    INPacket[8] = SIMBUCK_BOOT_MINOR;
                    INPacket[9] = SIMBUCK_BOOT_DOT;

                    //INPacket[7] = MAJOR_VERSION_DB;
                    //INPacket[8] = MINOR_VERSION_DB;
                    //INPacket[9] = DEBUG_VERSION_DB;
#endif
                    INPacket[2] = 0x0A;
                    break;

#if defined(MCHPFSUSB)
                case 3:  // Bootloader
                    INPacket[3] = MAJOR_VERSION_USB;  // USB Stack
                    INPacket[4] = MINOR_VERSION_USB;
                    INPacket[5] = DEBUG_VERSION_USB;

                    INPacket[6] = BOOTLOAD_TYPE;
                    INPacket[7] = USB_MAJOR_VER;     // Firmware
                    INPacket[8] = USB_MINOR_VER;
                    INPacket[9] = USB_DOT_VER;

                    INPacket[2] = 0x0A;
                    break;
#endif
 #if defined(HID_BOOTLOADER)
                case 3: // Bootloader

                    INPacket[3] = STACK_YEAR_USB;
                    INPacket[4] = STACK_MONTH_USB;
                    INPacket[5] = STACK_DAY_USB;

                    INPacket[6] = BOOTLOAD_TYPE;
                    INPacket[7] = SIMBUCK_BOOT_MAJOR;
                    INPacket[8] = SIMBUCK_BOOT_MINOR;
                    INPacket[9] = SIMBUCK_BOOT_DOT;

                    INPacket[2] = 0x0A;
                    break;
#endif
                    
                   }
                 }
            break;


        case READ_EEPROM: // 0x14 Read the EEPROM data from PC application.
        { // we use the second byte for the data segment
            offset = OUTPacket[1];
            INPacket[3] = ReadFromEEPROM(offset);

            INPacket[2] = 0x04;
        }
            break;

        case WRITE_EEPROM: // 0x15 Write the EEPROM data from PC application.
        { // we use the second byte for the data segment
            offset = OUTPacket[1];
            reclen = OUTPacket[2];

            for (i = 0; i < 6; i++) {
                WriteToEEPROM(OUTPacket[2 + i], offset + i);
                INPacket[4 + i] = OUTPacket[2 + i];
            }

            INPacket[3] = SUCCESS;
            INPacket[2] = 0x09;

        }
            break;

        case GET_BLOCK: // 0x16 Read Config record from EEPROM
        { // we use the second byte for the data segment
            // we use 3rd byte to define number bytes to read
            offset = OUTPacket[1];
            reclen = OUTPacket[2];

            for (i = 0; i < reclen; i++) {
                INPacket[4 + i] = ReadFromEEPROM(offset + i);
            }

            INPacket[3] = SUCCESS;

            INPacket[2] = reclen + 3;
        }
            break;

            /// case GET_FUSES: //0x20
            /// {
            ///
            /// }
            ///     break;

        case GET_USER_CONFIG: //0x21 - the user configuration
        {
            monitor = 0;
            monitor |= USERFlags.DEBUG;
            monitor << 1;

            monitor |= USERFlags.cpuload;
            monitor << 1;

            monitor |= USERFlags.slowUpdate;
            monitor << 1;

            monitor |= USERFlags.fastUpdate;
            monitor << 1;

            monitor |= USERFlags.resetCnt;
            monitor << 1;
           
          //  stat_LED = 0;
          //  stat_LED |= USERFlags.USB_STATUS_LED;
          //  stat_LED << 1;

          //  stat_LED |= USERFlags.CAN_STATUS_LED;

            INPacket[3] = monitor;
            INPacket[4] - stat_LED;

            INPacket[2] = 5;
        }
            break;

        case GET_USER_STATUS: //0x22 the register setup
        {
            INPacket[3] = MCU_regs._TRISE;
            INPacket[4] = MCU_regs._TRISD;
            INPacket[5] = MCU_regs._TRISC;
            INPacket[6] = MCU_regs._TRISB;
            INPacket[7] = MCU_regs._TRISA;
            INPacket[8] = MCU_regs._PIE1;
            INPacket[9] = MCU_regs._PIE2;
            INPacket[10] = MCU_regs._PIR1;
            INPacket[11] = MCU_regs._PIR2;
            INPacket[12] = MCU_regs._IPR1;
            INPacket[13] = MCU_regs._IPR2;
            INPacket[14] = MCU_regs._RCON;

            INPacket[15] = MCU_regs._INTCON;
            INPacket[16] = MCU_regs._INTCON2;
            INPacket[17] = MCU_regs._INTCON3;

            INPacket[2] = 18;
        }
            break;

        case GET_PORTS: //0x23
        {
            INPacket[3] = MCU_regs._PORTE;
            INPacket[4] = MCU_regs._PORTD;
            INPacket[5] = MCU_regs._PORTC;
            INPacket[6] = MCU_regs._PORTB;
            INPacket[7] = MCU_regs._PORTA;
            INPacket[8] = MCU_regs._LATE;
            INPacket[9] = MCU_regs._LATD;
            INPacket[10] = MCU_regs._LATC;
            INPacket[11] = MCU_regs._LATB;
            INPacket[12] = MCU_regs._LATA;

            INPacket[2] = 13;
        }
            break;


#if defined(SIMBLOCK_DUAL_CAN)
        case READ_2515_ADDR:
        {
            // get the first byte for the Controller
            // get the second byte for the address
            chipselect = OUTPacket[1];
            offset = OUTPacket[2];

            if (chipselect == 0) {
                Select_CAN_1();
            } else {
                Select_CAN_2();
            }

            INPacket[2] = offset;
            INPacket[3] = CAN2515_getregister(offset);

            // de_select the Controller
            if (chipselect == 0) {
                DeSelect_CAN_1();
            } else {
                DeSelect_CAN_2();
            }
        }
            break;

        case READ_2515_RECV:
        {
            // CAN 1
            for (i = 2; i < 16; i++) {
                INPacket[i] = CAN_1_rcv[i];
            }
            CANFlags.proc_CAN_1_0 = 0;


            for (i = 16; i < 30; i++) {
                INPacket[i] = CAN_3_rcv[i - 16];
            }
            CANFlags.proc_CAN_1_1 = 0;


            // CAN 2
            for (i = 2; i < 16; i++) {
                INPacket[i + frame_offset] = CAN_2_rcv[i];
            }
            CANFlags.proc_CAN_2_0 = 0;


            for (i = 16; i < 30; i++) {
                INPacket[i + (frame_offset + frame_offset)] = CAN_4_rcv[i - 16];
            }
            CANFlags.proc_CAN_2_1 = 0;

            CAN_update << 0x04; // put the uodate bits into the top nybble
            INPacket[1] = CAN_update; // Host needs to check top and bottom nybble
            // to see which data has changed
        }
            break;

        case WRITE_2515_SEND:
        {
            Nop();
        }
            break;

            // needs to provide for CAN 1 and CAN 2
            ////         case SUPRESS_SEND:
            ////          {
            ////           if(OUTPacket[1] == 0)
            ////            {
            ////             CANFlags.NOSEND_CAN_1 == 0;
            ////            }
            ////           else if(OUTPacket[1] == 1)
            ////            {
            ////             CANFlags.NOSEND_CAN_2 == 1;
            ////            }
            ////           else
            ////             {
            ////               // Set Error
            ////             }
            ////
            ////          }
            ////         break;

        case SSB_SELF_TEST:
        {
            if (OUTPacket[1] == 1) {
                CANPerf.run_self_test = 1;
                ///InitSelfTest();
            } else {
                CANPerf.run_self_test = 0;
                /// InitCAN1Messages();
                /// InitCAN2Messages();
            }
        }
            break;

#endif


#if defined(SIMBUCK_BASEBOARD_4550)
        case RESET_DEVICE: // Copied direct from HID Bootloader
        {
            UCONbits.SUSPND = 0; //Disable USB module
            UCON = 0x00; //Disable USB module
            //And wait awhile for the USB cable capacitance to discharge down to disconnected (SE0) state.
            //Otherwise host might not realize we disconnected/reconnected when we do the reset.
            //A basic for() loop decrementing a 16 bit number would be simpler, but seems to take more code space for
            //a given delay.  So do this instead:
            for (i = 0; i < 0xFF; i++) {
                WREG = 0xFF;
                while (WREG) {
                    WREG--;
                    _asm
                    bra 0 //Equivalent to bra $+2, which takes half as much code as 2 nop instructions
                            bra 0 //Equivalent to bra $+2, which takes half as much code as 2 nop instructions
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
    if (!USBHandleBusy(USBGenericInHandle)) {
        //The endpoint was not "busy", therefore it is safe to write to the buffer and arm the endpoint.
        //The USBGenWrite() function call "arms" the endpoint (and makes the handle indicate the endpoint is busy).
        //Once armed, the data will be automatically sent to the host (in hardware by the SIE) the next time the
        //host polls the endpoint.  Once the data is successfully sent, the handle (in this case USBGenericInHandle)
        //will indicate the the endpoint is no longer busy.
        USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (BYTE*) & INPacket, USBGEN_EP_SIZE);
    }


}//end ProcessIO





/* EOF user.c ***************************************************************/
