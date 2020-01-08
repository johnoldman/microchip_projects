/*******************************************************************************
 *
 *                Simbuck Firmware Version 1.0
 *
 *******************************************************************************
 * FileName:        simbuck_cfg.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18, PIC32
 * Compiler:        C18 3.42 <=> C32 2.02
 * Company:         Deben Enterprises Ltd.
 ******************************************************************************/

#ifndef SIMBUCK_CFG_H
#define SIMBUCK_CFG_H

/** D E V I C E ***************************************************************/
/* Uncomment the device that you are using */
#define SIMBUCKSPEEDBOX                  // set configuration to baseboard_4550/Speedbox device
//#define EVBATTMON                        // set configuration to baseboard_4550/Battery Monitor device
//#define EVBATTPACK                       // set configuration to baseboard_4685/Battery Pack monitor device

//#define SIMBUCK_DEVICE_4550
//#define SIMBUCK_DEVICE_4685

#if defined(SIMBUCKSPEEDBOX)
 #define SIMBUCK_BASEBOARD_4550
 #define USE_USB_LED
 //#define SIMBLOCK_DUAL_CAN
 #define HID_BOOTLOADER
#endif

#if defined(EVBATTMON)
 #define SIMBUCK_BASEBOARD_4550
 #define USE_USB_LED
 #define SIMBLOCK_DUAL_CAN
 #define DISPLAY_4DSYSTEMS
 #define HID_BOOTLOADER
#endif

#if defined(EVBATTPACK)
 #define SIMBUCK_BASEBOARD_4685
 #define SIMBLOCK_STEPDOWN_ADC
 //#define SERIAL_BOOTLOADER
#endif

#if defined SIMBUCK_DEVICE_4550
 #define SIMBUCK_BASEBOARD_4550
 #define HID_BOOTLOADER
 #define USE_USB_LED
 #define DISPLAY_HD44780
#endif


/** B A S E B O A R D S *******************************************************/
/* Uncomment the baseboard that you want to use */
//#define SIMBUCK_BASEBOARD_4550
//#define SIMBUCK_BASEBOARD_4685


/** S I M B L O C K S *********************************************************/
/* Uncomment the hardware simblocks that you want to use */
//#define SIMBLOCK_DUAL_CAN
//#define SIMBLOCK_STEPDOWN_ADC
//#define SIMBLOCK_PROTOBOARD

/** D I S P L A Y S ***********************************************************/

//#define DISPLAY_4DSYSTEMS
//#define DISPLAY_BATRON
//#define DISPLAY_HD44780

/** B O O T L O A D E R *******************************************************/

/* Uncomment the Bootloader that you want to use */
//#define MCHPFSUSB                 // not implemented
//#define HID_BOOTLOADER              // Microchip modified HID Bootloader
//#define TINY_BOOTLOADER           // not implemented
//#define PUF_BOOTLOADER            // not implemented
//#define CAN_BOOTLOADER            // to be implemented
//#define SERIAL_BOOTLOADER         // Microchip modified Serial Bootloader

/** S T A T U S   L E D  ******************************************************/
//#define USE_USB_LED
//#define USE_CAN_LED

/** F I R M W A R E   V E R S I O N S *****************************************/
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */

#if defined(SIMBUCK_BASEBOARD_4550)
/** Firmware content ***********************************************************

version 0.1.0

 Firmware Versioning
 EEPROM read and write

 Bootloading:
  0x0F on PORTD
  Softboot from EEPROM value BOOTVALUE[0xA5]

 Basic Interrupt handling (Low and High ISR)
  TMR0 - 1ms interval
--------------------------------------------------------------------------------
 version 0.2.0

 SPI connectivity
  CAN Controller configuration:
  Basic Send loop CAN transmit
  Basic CAN Receive

--------------------------------------------------------------------------------
 version 0.3.0

 UART support for 4DSystems Screen

 -------------------------------------------------------------------------------
 version 0.4.0

 PWM - basic support
 ADC - supported for AN0-4(RA0-4)

 -----------------------------------------------------------------------------*/

  #define DEBUG_DEVICE_VER    0x00
  #define MINOR_DEVICE_VER    0x03
  #define MAJOR_DEVICE_VER    0x00

#endif

 /*****************************************************************************/


#if defined(SIMBUCK_BASEBOARD_4685)
/** Firmware content ***********************************************************

 version 0.1.0

 Firmware Versioning
 EEPROM read and write

 Basic Interrupt handling (Low and High ISR)
  TMR0 - 1ms interval
  ADC measurement
  ECAN send
  UART send?

*/

  #define DEBUG_VERSION_DB    0x00
  #define MINOR_VERSION_DB    0x01
  #define MAJOR_VERSION_DB    0x00
#endif

 /*****************************************************************************/


#if defined(EVBATTMON)
/** Firmware content ***********************************************************

version 0.1.0

 A Direct port of the basic project files - 27/01/13
 Create new:                        -> HardwareProfile - EVBattMon.h
             user.c/h               -> user_evbattmon.c/h
             CAN_MsgList.c/h        -> EVBatt_CAN_MsgList.c/h
             CAN_ProcessMsgCAN1.c/h -> processCANframe.c/h
   
 Firmware Versioning
 EEPROM read and write

 Bootloading:
  0x0F on PORTD
  Softboot from EEPROM value BOOTVALUE[0xA5]

 Basic Interrupt handling (Low and High ISR)
  TMR0 - 1ms interval
  SPI connectivity
  CAN Controller configuration:
  Basic Send loop CAN transmit
  Basic CAN Receive

 -----------------------------------------------------------------------------*/

  #define DEBUG_VERSION_DB    0x00
  #define MINOR_VERSION_DB    0x01
  #define MAJOR_VERSION_DB    0x00

#endif
/******************************************************************************/


#if defined(EVBATTPACK)
/** Firmware content ***********************************************************

version 0.1.0

 Firmware Versioning
 EEPROM read and write
 UART Send
 UART Receive

 Bootloading:
  Softboot from UART BREAK

 Basic Interrupt handling (Low and High ISR)
  TMR0 - 1ms interval
  ECAN Controller configuration:
   CAN transmit

 -----------------------------------------------------------------------------*/

  #define DEBUG_VERSION_DB    0x00
  #define MINOR_VERSION_DB    0x01
  #define MAJOR_VERSION_DB    0x00

#endif
/******************************************************************************/


#if defined(SIMBUCKSPEEDBOX)
/** Firmware content ***********************************************************

version 0.0.4

Bootloading
EEPROM read and write
Firmware Versioning

Basic Interrupt handling (Low and High ISR)
TMR0 - 1ms interval
Output to OPTO

Read Switch inputs
Switch Relays - On to Close contactors

SPI connectivity
CAN Controller configuration
Basic Send loop CAN transmit
--------------------------------------------------------------------------------
version 0.0.5
Add temporary 'fudge' to enable
inverted CID to operate across
an engine cycle
--------------------------------------------------------------------------------
0.0.6
Add ability to mimic bi-directional
sensor output
--------------------------------------------------------------------------------
0.1.6
 Implemented HID Bootloader for Windows 7 capability
 Remove Bi-Directional 'fudge'
 Implement multi-lobe camshaft signalling

------------------------------------------------------------------------------*/

  #define DEBUG_VERSION_DB    0x06
  #define MINOR_VERSION_DB    0x01
  #define MAJOR_VERSION_DB    0x00

#endif
/******************************************************************************/


/**  3 r d  P A R T Y  L I B R A R Y  V E R S I O N S *************************/

#if defined(SIMBUCK_BASEBOARD_4550)
  #if defined(MCHPFSUSB)
    /* PICDEM FS USB Demo Version */
    #define USB_STACK_LIB       0x01    //  MCHPUSB Usb stack
    #define MINOR_VERSION_USB   0x02    //  Version 1.2
    #define MAJOR_VERSION_USB   0x01
    #define BOOTLOAD_TYPE       0x01

  #elif defined(HID_BOOTLOADER)
    /* Microchip Solutions Library v2011-07-16 */
    #define USB_STACK_LIB       0x02    // HID USB stack
    #define STACK_YEAR_USB      0x0B	// 2011
    #define STACK_MONTH_USB     0x07	// 07
    #define STACK_DAY_USB       0x0C	// 14
    //need these until Java app is fixed - used in Simbuck Signal Generator
    #define MINOR_VERSION_USB   0x02    //   Version 1.2
    #define MAJOR_VERSION_USB   0x01
    #define BOOTLOAD_TYPE       0x02

   #define SIMBUCK_BOOT_MAJOR   0x01   // First release - based off USB stack 0x02
   #define SIMBUCK_BOOT_MINOR   0x01
   #define SIMBUCK_BOOT_DOT     0x00

#elif defined(SIMBUCK_BASEBOARD_4685)
   #if defined(CAN_BOOTLOADER)
     #define BOOTLOAD_TYPE      0x06
   #endif

   #else
     #define BOOTLOAD_TYPE      0x00
   #endif
#endif

/**  3 r d  P A R T Y  L I B R A R Y  V E R S I O N S *************************/

#endif //SIMBUCK_CFG_H
