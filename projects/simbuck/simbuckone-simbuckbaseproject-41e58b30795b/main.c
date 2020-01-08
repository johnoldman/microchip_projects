/*******************************************************************************
 FileName:	main.c
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

********************************************************************************
 File Description:

 Change History:
  Rev   Description
  ---   ------------------------------------------------------------------------

  1.0.0 First release for Simbuck - Based from original file
                                    supplied for the LIBUSB
                                    demo in the Microchip
                                    solutions Library v2011-07-14
*******************************************************************************/



/* INCLUDES *******************************************************************/

#include "simbuck_cfg.h"
#include "HardwareProfile.h"
#include "../user/userInits.h"


#if defined(SIMBUCK_BASEBOARD_4550)
  #include <p18cxxx.h>
  #include "USB/usb.h"
  #include "USB/usb_function_generic.h"
  #include "interrupt.h"
  #include "system/eeprom/eeprom.h"
  #include "processUSBpacket.h"
  #include "user/user_4550.h"
  #include "selftests/selftest.h"
#endif


#if defined(SIMBUCK_BASEBOARD_4685)
  #include <p18cxxx.h>
  #include "user/user_4685.h"
  #include "selftests/selftest.h"
#endif

/* CONFIGURATION *************************************************************/

/* Baseboard 4550 >> On-Board USB */

#if defined(SIMBUCK_BASEBOARD_4550)
	//Add the configuration pragmas here for your hardware platform
	#pragma config PLLDIV   = 5             // (20 MHz input)
        #pragma config CPUDIV   = OSC1_PLL2     // CPU System Clock PostScalar [96 MHz PLL Src: /2]
	#pragma config USBDIV   = 2             // USB Clock source from 96MHz PLL/2
	#pragma config FOSC     = HSPLL_HS      // Oscillator selection
	#pragma config FCMEN    = OFF           // Fail Safe cock monitor
	#pragma config IESO     = OFF           // Internal/External Switch over
	#pragma config PWRT     = OFF           // Power-Up timer
	#pragma config BOR      = ON            // Brown-Out reset
	#pragma config BORV     = 3             // Brown-Out voltage
	#pragma config VREGEN   = ON            // USB Voltage regulator
	#pragma config WDT      = OFF           // Watchdog timer
	#pragma config WDTPS    = 32768         // Watchdog PostScalar
	#pragma config MCLRE    = ON            // MCLR Enable
	#pragma config LPT1OSC  = OFF           // Low Power Timer1 oscillator
	#pragma config PBADEN   = OFF           // PORTB[4:0] Digital IO on reset
	#pragma config CCP2MX   = ON            // CCP2 IO multiplex with RC1
	#pragma config STVREN   = ON            // Stack Overflow reset
	#pragma config LVP      = OFF           // Low Voltage ICSP
	#pragma config ICPRT    = ON            // Dedicated In-Circuit Debug/Programming
	#pragma config XINST    = OFF           // Extended Instruction Set
        #pragma config DEBUG    = ON            // Background debugger
	#pragma config CP0      = OFF           // Code Protection Block 0
	#pragma config CP1      = OFF           // Code Protection Block 1
	#pragma config CP2      = OFF           // Code Protection Block 2
	#pragma config CP3      = OFF           // Code Protection Block 3
	#pragma config CPB      = ON            // Code Protection Boot Block
	#pragma config CPD      = OFF           // Code Protection data EEPROM
        #pragma config WRT0     = OFF           // Write Protection Block 0
	#pragma config WRT1     = OFF           // Write Protection Block 1
	#pragma config WRT2     = OFF           // Write Protection Block 2
	#pragma config WRT3     = OFF           // Write Protection Block 3
	#pragma config WRTB     = ON            // Write Protection Boot Block
	#pragma config WRTC     = OFF           // Write Protection Configuration register
	#pragma config WRTD     = OFF           // Write Protection data EEPROM
	#pragma config EBTR0    = OFF           // Table Read Protection Block 0
	#pragma config EBTR1    = OFF           // Table Read Protection Block 1
	#pragma config EBTR2    = OFF           // Table Read Protection Block 2
	#pragma config EBTR3    = OFF           // Table Read Protection Block 3
	#pragma config EBTRB    = OFF           // Table Read Protection Boot Block


/* Baseboard 4685 >> On-Board CAN */

 #elif defined(SIMBUCK_BASEBOARD_4685)
	//Add the configuration pragmas here for your hardware platform
        #pragma config OSC      = HS            // when you have a 20MHz crystal oscillator connected externally
	#pragma config PWRT     = OFF           // Power-Up timer
	#pragma config WDT      = OFF           // Watchdog timer
	#pragma config WDTPS    = 32768         // Watchdog PostScalar
	#pragma config MCLRE    = ON            // MCLR Enable
	#pragma config LPT1OSC  = OFF           // Low Power Timer1 oscillator
	#pragma config PBADEN   = OFF           // PORTB[4:0] Digital IO on reset
        #pragma config DEBUG    = ON            // Background debugger
	#pragma config XINST    = OFF           // Extended Instruction Set
        #pragma config BBSIZ    = 1024          // 1K words Boot Block
	#pragma config LVP      = OFF           // Low Voltage ICSP
       	#pragma config STVREN   = ON            // Stack Overflow/Underflow reset
	#pragma config CP1      = OFF           // Code Protection Block 1
	#pragma config CP2      = OFF           // Code Protection Block 2
	#pragma config CP3      = OFF           // Code Protection Block 3
	#pragma config CPB      = OFF           // Code Protection Boot Block
	#pragma config CPD      = OFF           // Code Protection data EEPROM
        #pragma config WRT0     = OFF           // Write Protection Block 0
	#pragma config WRT1     = OFF           // Write Protection Block 1
	#pragma config WRT2     = OFF           // Write Protection Block 2
	#pragma config WRT3     = OFF           // Write Protection Block 3
	#pragma config WRTB     = OFF           // Write Protection Boot Block
	#pragma config WRTC     = OFF           // Write Protection Configuration register
	#pragma config WRTD     = OFF           // Write Protection data EEPROM
	#pragma config EBTR0    = OFF           // Table Read Protection Block 0
	#pragma config EBTR1    = OFF           // Table Read Protection Block 1
	#pragma config EBTR2    = OFF           // Table Read Protection Block 2
	#pragma config EBTR3    = OFF           // Table Read Protection Block 3
	#pragma config EBTRB    = OFF           // Table Read Protection Boot Block

#else
    #error No hardware board defined, see "HardwareProfile.h"
#endif

/* PRIVATE PROTOTYPES *********************************************/
static void InitializeSystem(void);
void BackgroundTask(void);

/* PUBLIC PROTOTYPES *********************************************/
extern void YourHighPriorityISRCode(void);
extern void YourLowPriorityISRCode(void);


/* BASEBOARD4550 PROTOTYPES *********************************************/
#if defined(SIMBUCK_BASEBOARD_4550)
  void USBDeviceTasks(void);
  void ProcessUSB_IO(void);

 #if defined(USE_USB_LED)
  void BlinkUSBStatus(void);
 #endif

#endif


#if defined(SIMBUCK_BASEBOARD_4685) || defined(SIMBUCK_DEVICE_4685)
  void ProcessCAN_IO(void);

  // Prevent application code from being written into FLASH memory space
  // needed for the Bootloader firmware at addresses 0 through 3FFh.
  //#pragma romdata BootloaderProgramMemorySpace = 0x6
  //const rom char bootloaderProgramMemorySpace[0x800 - 0x6];

#endif

/* VARIABLES ******************************************************/
#if defined(__18F2455) || defined(__18F2550) || defined(__18F4455) || defined(__18F4550)\
    || defined(__18F2458) || defined(__18F2453) || defined(__18F4558) || defined(__18F4553)
    #pragma udata USB_VARIABLES=0x500
#elif defined(__18F4450) || defined(__18F2450)
    #pragma udata USB_VARIABLES=0x480
#else
    #pragma udata
#endif


#if defined(SIMBUCK_BASEBOARD_4550)
USB_HANDLE USBGenericOutHandle; ///< OUT endpoint handle
USB_HANDLE USBGenericInHandle;  ///< IN endpoint handle
unsigned char OUTPacket[64];	///< User application buffer for receiving and holding OUT packets sent from the host
unsigned char INPacket[64];	///< User application buffer for sending IN packets to the host
extern USER_FLAGS USERFlags;    ///< structure for user semaphore

#if defined(USE_USB_LED)
 BOOL blinkStatusValid;    ///< Flag to indicate USB status via LED
#endif

//#pragma udata

#endif

#if defined(SIMBUCK_BASEBOARD_4685) || defined(SIMBUCK_DEVICE_4685)
extern USER_FLAGS USERFlags;    ///< structure for user semaphore


//#pragma udata

#endif

#pragma udata VECTOR_MAP



/* VECTOR REMAPPING ***********************************************/
#if defined(__18CXX)
	//On PIC18 devices, addresses 0x00, 0x08, and 0x18 are used for
	//the reset, high priority interrupt, and low priority interrupt
	//vectors.  However, the current Microchip USB bootloader
	//examples are intended to occupy addresses 0x00-0x7FF or
	//0x00-0xFFF depending on which bootloader is used.  Therefore,
	//the bootloader code remaps these vectors to new locations
	//as indicated below.  This remapping is only necessary if you
	//wish to program the hex file generated from this project with
	//the USB bootloader.  If no bootloader is used, edit the
	//usb_config.h file and comment out the following defines:
	//#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER
	//#define PROGRAMMABLE_WITH_USB_LEGACY_CUSTOM_CLASS_BOOTLOADER

	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
		#define REMAPPED_RESET_VECTOR_ADDRESS		0x1100
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1108
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1118
	#elif defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x800
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818
	#else
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x00
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x08
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x18
	#endif

	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
	extern void _startup (void);        // See c018i.c in your C18 compiler dir
	#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
	#endif
	#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
	void Remapped_High_ISR (void)
	{
	     _asm goto YourHighPriorityISRCode _endasm
	}
	#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
	void Remapped_Low_ISR (void)
	{
	     _asm goto YourLowPriorityISRCode _endasm
	}

	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
	//Note: If this project is built while one of the bootloaders has
	//been defined, but then the output hex file is not programmed with
	//the bootloader, addresses 0x08 and 0x18 would end up programmed with 0xFFFF.
	//As a result, if an actual interrupt was enabled and occured, the PC would jump
	//to 0x08 (or 0x18) and would begin executing "0xFFFF" (unprogrammed space).  This
	//executes as nop instructions, but the PC would eventually reach the REMAPPED_RESET_VECTOR_ADDRESS
	//(0x1000 or 0x800, depending upon bootloader), and would execute the "goto _startup".  This
	//would effective reset the application.

	//To fix this situation, we should always deliberately place a
	//"goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS" at address 0x08, and a
	//"goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS" at address 0x18.  When the output
	//hex file of this project is programmed with the bootloader, these sections do not
	//get bootloaded (as they overlap the bootloader space).  If the output hex file is not
	//programmed using the bootloader, then the below goto instructions do get programmed,
	//and the hex file still works like normal.  The below section is only required to fix this
	//scenario.
	#pragma code HIGH_INTERRUPT_VECTOR = 0x08
	void High_ISR (void)
	{
	     _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
	}
	#pragma code LOW_INTERRUPT_VECTOR = 0x18
	void Low_ISR (void)
	{
	     _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
	}
	#endif	//end of "#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_LEGACY_CUSTOM_CLASS_BOOTLOADER)"

	//#pragma code


	

#endif




/* DECLARATIONS ***************************************************/
#pragma code

/** 
 * Main program entry point.
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *
 * @todo Move configuration fuses to seperate include
*/

#if defined(__18CXX)
void main(void)
#else
int main(void)
#endif
{   
    InitializeSystem();

#if defined(SIMBUCK_BASEBOARD_4550)
    #if defined(USB_INTERRUPT)
        USBDeviceAttach();
	#endif
#endif



    while(1)
    {

    #if defined(SIMBUCK_BASEBOARD_4550)
      #if defined(USB_POLLING)
	// Check bus status and service USB interrupts.
        USBDeviceTasks(); // Interrupt or polling method.  If using polling, must call
        				  // this function periodically.  This function will take care
        				  // of processing and responding to SETUP transactions 
        				  // (such as during the enumeration process when you first
        				  // plug in).  USB hosts require that USB devices should accept
        				  // and process SETUP packets in a timely fashion.  Therefore,
        				  // when using polling, this function should be called 
        				  // frequently (such as once about every 100 microseconds) at any
        				  // time that a SETUP packet might reasonably be expected to
        				  // be sent by the host to your device.  In most cases, the
        				  // USBDeviceTasks() function does not take very long to
        				  // execute (~50 instruction cycles) before it returns.
        #endif
      #endif

		
	#if defined(SIMBUCK_BASEBOARD_4550)
           ProcessUSB_IO();
       
        #elif defined(SIMBUCK_BASEBOARD_4685)
           ProcessCAN_IO();

         #elif defined(SIMBUCK_DEVICE_4685)
           ProcessCAN_IO();

       #else
         #error No hardware controller board defined"
      #endif

    }//end while
}//end main


/**
 * Centralised initialisation
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization
 *                  routine. All required USB initialization routines
 *                  are called from here.
 *
 *                  User application initialization routine should
 *                  also be called from here.                  
 *
 * Note:            None
 */

static void InitializeSystem(void)
{
    #if (defined__18CXX)
        ADCON1 |= 0x0F;                 // Default all pins to digital
   
    #elif defined(__C32__)
        AD1PCFG = 0xFFFF;
    #endif

   #if defined(SIMBUCK_BASEBOARD_4550)
//	The USB specifications require that USB peripheral devices must never source
//	current onto the Vbus pin.  Additionally, USB peripherals should not source
//	current on D+ or D- when the host/hub is not actively powering the Vbus line.
//	When designing a self powered (as opposed to bus powered) USB peripheral
//	device, the firmware should make sure not to turn on the USB module and D+
//	or D- pull up resistor unless Vbus is actively powered.  Therefore, the
//	firmware needs some means to detect when Vbus is being powered by the host.
//	A 5V tolerant I/O pin can be connected to Vbus (through a resistor), and
// 	can be used to detect when Vbus is high (host actively powering), or low
//	(host is shut down or otherwise not supplying power).  The USB firmware
// 	can then periodically poll this I/O pin to know when it is okay to turn on
//	the USB module/D+/D- pull up resistor.  When designing a purely bus powered
//	peripheral device, it is not possible to source current on D+ or D- when the
//	host is not actively providing power on Vbus. Therefore, implementing this
//	bus sense feature is optional.  This firmware can be made to use this bus
//	sense feature by making sure "USE_USB_BUS_SENSE_IO" has been defined in the
//	HardwareProfile.h file.    
    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif
    
//	If the host PC sends a GetStatus (device) request, the firmware must respond
//	and let the host know if the USB peripheral device is currently bus powered
//	or self powered.  See chapter 9 in the official USB specifications for details
//	regarding this request.  If the peripheral device is capable of being both
//	self and bus powered, it should not return a hard coded value for this request.
//	Instead, firmware should check if it is currently self or bus powered, and
//	respond accordingly.  If the hardware has been configured like demonstrated
//	on the PICDEM FS USB Demo Board, an I/O pin can be polled to determine the
//	currently selected power source.  On the PICDEM FS USB Demo Board, "RA2" 
//	is used for	this purpose.  If using this feature, make sure "USE_SELF_POWER_SENSE_IO"
//	has been defined in HardwareProfile.h, and that an appropriate I/O pin has been mapped
//	to it in HardwareProfile.h.
  #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;	// See HardwareProfile.h
    #endif
    
  	USBGenericOutHandle = 0;
	USBGenericInHandle = 0;		
  #endif    


  #if defined(SIMBUCK_BASEBOARD_4550)
    USBDeviceInit();	//usb_device.c.  Initializes USB module SFRs and firmware


       UserInit();			//Application related initialization.  See user.c
                                        //variables to known states.

        // clear the BOOT value from the EEPROM
        WriteToEEPROM(BOOTCLEAR, BOOTADDR);
        //WriteToEEPROM(BOOTVALUE, BOOTADDR);

       //// mInitAllLEDs();		 // !! This can and does override user settings !!
	////blinkStatusValid = TRUE; //Blink the normal USB state on the LEDs.

    #endif

    #if defined(SIMBUCK_BASEBOARD_4685)

        ADCON1 |= 0x0F;                 // Default all pins to digital
        
        UserInit();

    #endif


}//end InitializeSystem




/**
 * Place holder for calling user routines
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is a place holder for other user routines.
 *                  It is a mixture of both USB and non-USB tasks. Non-USB tasks
 *                  are called via ProcessUser...() so this file does NOT
 *                  require editing.
 *
 * Note:            None
 */

#if defined(SIMBUCK_BASEBOARD_4550)
void ProcessUSB_IO(void)
{
   BackgroundTask();
   ProcessUser();
  
    //Blink the LEDs according to the USB device status, but only do so if the PC application isn't connected and controlling the LEDs.
    #if defined(SIMBUCK_BASEBOARD_4550) & defined(USE_USB_LED)
     if(blinkStatusValid)
      {
        BlinkUSBStatus();
      }
    #endif

   

    //User Application USB tasks below.
    //Note: The user application should not begin attempting to read/write over the USB
    //until after the device has been fully enumerated.  After the device is fully
    //enumerated, the USBDeviceState will be set to "CONFIGURED_STATE".
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;
    
    //As the device completes the enumeration process, the USBCBInitEP() function will
    //get called.  In this function, we initialize the user application endpoints (in this
    //example code, the user application makes use of endpoint 1 IN and endpoint 1 OUT).
    //The USBGenRead() function call in the USBCBInitEP() function initializes endpoint 1 OUT
    //and "arms" it so that it can receive a packet of data from the host.  Once the endpoint
    //has been armed, the host can then send data to it (assuming some kind of application software
    //is running on the host, and the application software tries to send data to the USB device).
    
    //If the host sends a packet of data to the endpoint 1 OUT buffer, the hardware of the SIE will
    //automatically receive it and store the data at the memory location pointed to when we called
    //USBGenRead().  Additionally, the endpoint handle (in this case USBGenericOutHandle) will indicate
    //that the end/point is no longer busy.  At this point, it is safe for this firmware to begin reading
    //from the endpoint buffer, and processing the data.  In this example, we have implemented a few very
    //simple commands.  For example, if the host sends a packet of data to the endpoint 1 OUT buffer, with the
    //first byte = 0x80, this is being used as a command to indicate that the firmware should "Toggle LED(s)".
    if(!USBHandleBusy(USBGenericOutHandle))		//Check if the endpoint has received any data from the host.
    {

          ProcessUSB();
            //Re-arm the OUT endpoint for the next packet:
	    //The USBGenRead() function call "arms" the endpoint (and makes it "busy").  If the endpoint is armed, the SIE will 
	    //automatically accept data from the host, if the host tries to send a packet of data to the endpoint.  Once a data 
	    //packet addressed to this endpoint is received from the host, the endpoint will no longer be busy, and the application
	    //can read the data which will be sitting in the buffer.
        USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM,(BYTE*)&OUTPacket,USBGEN_EP_SIZE);
    }

    
    

}//end ProcessIO
#endif

#if defined(SIMBUCK_BASEBOARD_4685)
void ProcessCAN_IO(void)
{
   ProcessUser();
   BackgroundTask();
}
#endif



/**
 * USB device state indicator
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        BlinkUSBStatus turns on and off LEDs 
 *                  corresponding to the USB device state.
 *
 * Note:            mLED macros can be found in HardwareProfile - xxx.h
 *                  USBDeviceState is declared and updated in
 *                  usb_device.c.
 *
 * @todo Move BlinkUSBStatus to user file
 */

#if defined(SIMBUCK_BASEBOARD_4550)
void BlinkUSBStatus(void)
{
    static WORD led_count=0;        
    
    if(led_count == 0)led_count = 60000U;
    led_count--;

    if(USBSuspendControl == 1)
    {
        if(led_count%20000==0)
        {
            mLED_2_Toggle();
            mLED_1_Off();
        }//end if
    }
    else
    {
        if(USBDeviceState == DETACHED_STATE)
        {
            mLED_1_Off();
            mLED_2_Off();
        }
        else if(USBDeviceState == ATTACHED_STATE)
        {
            mLED_1_On();
            mLED_2_On();
        }
        else if(USBDeviceState == POWERED_STATE)
        {
            mLED_1_On();
            mLED_2_Off();
        }
        else if(USBDeviceState == DEFAULT_STATE)
        {
            mLED_2_On();
        }
        else if(USBDeviceState == ADDRESS_STATE)
        {
           if(led_count==0)
            {
                mLED_1_Toggle();
				
		TRISEbits.TRISE2=1;
		mLED_3_Off();

                if(mGetLED_1())
                {
                    mLED_2_Off();
                }
                else
                {
                    mLED_2_On();
					
                }
            }//end if
        }
        else if(USBDeviceState == CONFIGURED_STATE)
        {
            if(led_count==0)
            {
                mLED_1_Toggle();
				
				

                if(mGetLED_1())
                {
                    mLED_2_Off();
                }
                else
                {
                    mLED_2_On();
                }
            }//end if
        }//end if(...)
    }//end if(UCONbits.SUSPND...)

}//end BlinkUSBStatus
#endif


void BackgroundTask(void)
{
    LATDbits.LATD0 = !LATDbits.LATD0;

    /** Run any required data collection tasks **/
    if(USERFlags.fastUpdate)
    {
     fastUpdate();
    }

    if(USERFlags.slowUpdate)
    {
     slowUpdate();
    }
}

// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************
// ******************************************************************************************************
// The USB firmware stack will call the callback functions USBCBxxx() in response to certain USB related
// events.  For example, if the host PC is powering down, it will stop sending out Start of Frame (SOF)
// packets to your device.  In response to this, all USB devices are supposed to decrease their power
// consumption from the USB Vbus to <2.5mA each.  The USB module detects this condition (which according
// to the USB specifications is 3+ms of no bus activity/SOF packets) and then calls the USBCBSuspend()
// function.  You should modify these callback functions to take appropriate actions for each of these
// conditions.  For example, in the USBCBSuspend(), you may wish to add code that will decrease power
// consumption from Vbus to <2.5mA (such as by clock switching, turning off LEDs, putting the
// microcontroller to sleep, etc.).  Then, in the USBCBWakeFromSuspend() function, you may then wish to
// add code that undoes the power saving things done in the USBCBSuspend() function.

// The USBCBSendResume() function is special, in that the USB stack will not automatically call this
// function.  This function is meant to be called from the application firmware instead.  See the
// additional comments near the function.

/**
 * USB suspend Callback
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Call back that is invoked when a USB suspend is detected
 *
 * Note:            None
 */

#if !defined(SIMBUCK_BASEBOARD_4685)
void USBCBSuspend(void)
{
	//Example power saving code.  Insert appropriate code here for the desired
	//application behavior.  If the microcontroller will be put to sleep, a
	//process similar to that shown below may be used:
	
	//ConfigureIOPinsForLowPower();
	//SaveStateOfAllInterruptEnableBits();
	//DisableAllInterruptEnableBits();
	//EnableOnlyTheInterruptsWhichWillBeUsedToWakeTheMicro();	//should enable at least USBActivityIF as a wake source
	//Sleep();
	//RestoreStateOfAllPreviouslySavedInterruptEnableBits();	//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.
	//RestoreIOPinsToNormal();									//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.

	//IMPORTANT NOTE: Do not clear the USBActivityIF (ACTVIF) bit here.  This bit is 
	//cleared inside the usb_device.c file.  Clearing USBActivityIF here will cause 
	//things to not work as intended.	
	

    #if defined(__C30__)
    #if 0
        U1EIR = 0xFFFF;
        U1IR = 0xFFFF;
        U1OTGIR = 0xFFFF;
        IFS5bits.USB1IF = 0;
        IEC5bits.USB1IE = 1;
        U1OTGIEbits.ACTVIE = 1;
        U1OTGIRbits.ACTVIF = 1;
        Sleep();
    #endif
    #endif
}

#endif

/**
 * USB interrupt bit is set
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the USB interrupt bit is set
 *		    In this example the interrupt is only used when the device
 *		    goes to sleep when it receives a USB suspend command
 *
 * Note:            None
 */

#if !defined(SIMBUCK_BASEBOARD_4685)
#if 0
void __attribute__ ((interrupt)) _USB1Interrupt(void)
{
    #if !defined(self_powered)
        if(U1OTGIRbits.ACTVIF)
        {
            IEC5bits.USB1IE = 0;
            U1OTGIEbits.ACTVIE = 0;
            IFS5bits.USB1IF = 0;
        
            //USBClearInterruptFlag(USBActivityIFReg,USBActivityIFBitNum);
            USBClearInterruptFlag(USBIdleIFReg,USBIdleIFBitNum);
            //USBSuspendControl = 0;
        }
    #endif
}
#endif
#endif

/**
 * Wakeup from USB suspend Callback
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The host may put USB peripheral devices in low power
 *		    suspend mode (by "sending" 3+ms of idle).  Once in suspend
 *		    mode, the host may wake the device back up by sending non-
 *		    idle state signalling.
 *				
 *		    This call back is invoked when a wakeup from USB suspend
 *		    is detected.
 *
 * Note:            None
 */

#if !defined(SIMBUCK_BASEBOARD_4685)
void USBCBWakeFromSuspend(void)
{
	// If clock switching or other power savings measures were taken when
	// executing the USBCBSuspend() function, now would be a good time to
	// switch back to normal full power run mode conditions.  The host allows
	// a few milliseconds of wakeup time, after which the device must be 
	// fully back to normal, and capable of receiving and processing USB
	// packets.  In order to do this, the USB module must receive proper
	// clocking (IE: 48MHz clock must be available to SIE for full speed USB
	// operation).
}
#endif

/**

 * Isochronous pipes Callback
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB host sends out a SOF packet to full-speed
 *                  devices every 1 ms. This interrupt may be useful
 *                  for isochronous pipes. End designers should
 *                  implement callback routine as necessary.
 *
 * Note:            None
 */

#if !defined(SIMBUCK_BASEBOARD_4685)
void USBCB_SOF_Handler(void)
{
    // No need to clear UIRbits.SOFIF to 0 here.
    // Callback caller is already doing that.
}
#endif

/**
 * USB error interrupt Callback
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The purpose of this callback is mainly for
 *                  debugging during development. Check UEIR to see
 *                  which error causes the interrupt.
 *
 * Note:            None
 */

#if !defined(SIMBUCK_BASEBOARD_4685)
void USBCBErrorHandler(void)
{
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.

	// Typically, user firmware does not need to do anything special
	// if a USB error occurs.  For example, if the host sends an OUT
	// packet to your device, but the packet gets corrupted (ex:
	// because of a bad connection, or the user unplugs the
	// USB cable during the transmission) this will typically set
	// one or more USB error interrupt flags.  Nothing specific
	// needs to be done however, since the SIE will automatically
	// send a "NAK" packet to the host.  In response to this, the
	// host will normally retry to send the packet again, and no
	// data loss occurs.  The system will typically recover
	// automatically, without the need for application firmware
	// intervention.
	
	// Nevertheless, this callback function is provided, such as
	// for debugging purposes.
}
#endif

/**
 * non-standard USB chapter 9 request Callback
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        When SETUP packets arrive from the host, some
 * 		    firmware must process the request and respond
 *		    appropriately to fulfill the request.  Some of
 *		    the SETUP packets will be for standard
 *		    USB "chapter 9" (as in, fulfilling chapter 9 of
 *		    the official USB specifications) requests, while
 *		    others may be specific to the USB device class
 *		    that is being implemented.  For example, a HID
 *		    class device needs to be able to respond to
 *		    "GET REPORT" type of requests.  This
 *		    is not a standard USB chapter 9 request, and
 *		    therefore not handled by usb_device.c.  Instead
 *		    this request should be handled by class specific
 *		    firmware, such as that contained in usb_function_hid.c.
 *
 * Note:            None
 */

#if !defined(SIMBUCK_BASEBOARD_4685)
void USBCBCheckOtherReq(void)
{
}//end
#endif

/**
 * SETUP, bRequest: SET_DESCRIPTOR request Callback
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USBCBStdSetDscHandler() callback function is
 *		    called when a SETUP, bRequest: SET_DESCRIPTOR request
 *		    arrives.  Typically SET_DESCRIPTOR requests are
 *		    not used in most applications, and it is
 *		    optional to support this type of request.
 *
 * Note:            None
 */

#if !defined(SIMBUCK_BASEBOARD_4685)
void USBCBStdSetDscHandler(void)
{
    // Must claim session ownership if supporting this request
}//end
#endif

/**

 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the device becomes
 *                  initialized, which occurs after the host sends a
 * 		    SET_CONFIGURATION (wValue not = 0) request.  This
 *		    callback function should initialize the endpoints
 *		    for the device's usage according to the current
 *		    configuration.
 *
 * Note:            None
 */

#if !defined(SIMBUCK_BASEBOARD_4685)
void USBCBInitEP(void)
{
    USBEnableEndpoint(USBGEN_EP_NUM,USB_OUT_ENABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM,(BYTE*)&OUTPacket,USBGEN_EP_SIZE);
}
#endif

/**
 * Wake-up PC Callback
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB specifications allow some types of USB
 * 		    peripheral devices to wake up a host PC (such
 *		    as if it is in a low power suspend to RAM state).
 *		    This can be a very useful feature in some
 *		    USB applications, such as an Infrared remote
 *		    control receiver. If a user presses the "power"
 *		    button on a remote control, it is nice that the
 *		    IR receiver can detect this signalling, and then
 *		    send a USB "command" to the PC to wake up.
 *					
 *		    The USBCBSendResume() "callback" function is used
 *		    to send this special USB signalling which wakes
 *		    up the PC.  This function may be called by
 *		    application firmware to wake up the PC.  This
 *		    function should only be called when:
 *					
 *		    1.  The USB driver used on the host PC supports
 *			the remote wakeup capability.
 *		    2.  The USB configuration descriptor indicates
 *		 	the device is remote wakeup capable in the
 *			bmAttributes field.
 *		    3.  The USB host PC is currently sleeping,
 *		 	and has previously sent your device a SET
 *		        FEATURE setup packet which "armed" the
 *			remote wakeup capability.   
 *
 *			This callback should send a RESUME signal that
 *                      has the period of 1-15ms.
 *
 * Note:            Interrupt vs. Polling
 *                  -Primary clock
 *                  -Secondary clock ***** MAKE NOTES ABOUT THIS *******
 *                   > Can switch to primary first by calling USBCBWakeFromSuspend()
 *
 *                  The modifiable section in this routine should be changed
 *                  to meet the application needs. Current implementation
 *                  temporary blocks other functions from executing for a
 *                  period of 1-13 ms depending on the core frequency.
 *
 *                  According to USB 2.0 specification section 7.1.7.7,
 *                  "The remote wakeup device must hold the resume signaling
 *                  for at lest 1 ms but for no more than 15 ms."
 *                  The idea here is to use a delay counter loop, using a
 *                  common value that would work over a wide range of core
 *                  frequencies.
 *
 *                  That value selected is 1800.
 *
 *                  See table below:
 *                 
 *                  Core Freq(MHz)   <--->   MIP    <--->  RESUME Signal Period (ms)
 *                      48              12            1.05
 *                       4               1           12.6
 *                  
 *                  * These timing could be incorrect when using code
 *                    optimization or extended instruction mode,
 *                    or when having other interrupts enabled.
 *                    Make sure to verify using the MPLAB SIM's Stopwatch
 *                    and verify the actual signal on an oscilloscope.
 */

#if !defined(SIMBUCK_BASEBOARD_4685)
void USBCBSendResume(void)
{
    static WORD delay_count;            
    
    USBResumeControl = 1;                // Start RESUME signaling
    
    delay_count = 1800U;                // Set RESUME line for 1-13 ms
    do
    {
        delay_count--;
    }while(delay_count);
    USBResumeControl = 0;
}
#endif

/**
 * Notify a user application that a USB event occurred
 *
 * PreCondition:    None
 *
 * Input:           USB_EVENT event - the type of event
 *                  void *pdata - pointer to the event data
 *                  WORD size - size of the event data
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called from the USB stack to
 *                  notify a user application that a USB event
 *                  occured.  This callback is in interrupt context
 *                  when the USB_INTERRUPT option is selected.
 *
 * Note:            None
 */

#if !defined(SIMBUCK_BASEBOARD_4685)
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size)
{
    switch(event)
    {
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER:
            Nop();
            break;
        default:
            break;
    }      
    return TRUE; 
}
#endif


/* EOF main.c ***************************************************************/
