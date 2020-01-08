#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-speedBox_4550.mk)" "nbproject/Makefile-local-speedBox_4550.mk"
include nbproject/Makefile-local-speedBox_4550.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=speedBox_4550
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/simbuck-libusb.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/simbuck-libusb.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../usb_descriptors.c ../selftests/selftest.c ../system/CAN/CAN2515user.c ../system/CAN/CAN_useCAN1.c ../system/CAN/CAN_useCAN2.c ../system/CAN/CAN2515utils.c ../system/CAN/CAN_MsgList.c ../system/CAN/CAN2515drv.c ../system/display/display4d.c ../system/display/hd44780.c ../device/speedbox/simstat.c ../device/speedbox/speedboxuser.c ../system/eeprom/eeprom.c ../system/serial/simbuckserial.c ../system/pwm/simbuckpwm.c ../system/spi/simbuckspi.c "../system/USBstack/USB/Generic Device Driver/usb_function_generic.c" ../system/USBstack/USB/usb_device.c ../user/processUSBpacket.c ../user/userInits.c ../user/interrupt.c ../main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/usb_descriptors.o ${OBJECTDIR}/_ext/1730819898/selftest.o ${OBJECTDIR}/_ext/1179396225/CAN2515user.o ${OBJECTDIR}/_ext/1179396225/CAN_useCAN1.o ${OBJECTDIR}/_ext/1179396225/CAN_useCAN2.o ${OBJECTDIR}/_ext/1179396225/CAN2515utils.o ${OBJECTDIR}/_ext/1179396225/CAN_MsgList.o ${OBJECTDIR}/_ext/1179396225/CAN2515drv.o ${OBJECTDIR}/_ext/1659146991/display4d.o ${OBJECTDIR}/_ext/1659146991/hd44780.o ${OBJECTDIR}/_ext/938477934/simstat.o ${OBJECTDIR}/_ext/938477934/speedboxuser.o ${OBJECTDIR}/_ext/1552693807/eeprom.o ${OBJECTDIR}/_ext/1151835195/simbuckserial.o ${OBJECTDIR}/_ext/1179351275/simbuckpwm.o ${OBJECTDIR}/_ext/1179348613/simbuckspi.o ${OBJECTDIR}/_ext/1235981372/usb_function_generic.o ${OBJECTDIR}/_ext/1412100490/usb_device.o ${OBJECTDIR}/_ext/760557894/processUSBpacket.o ${OBJECTDIR}/_ext/760557894/userInits.o ${OBJECTDIR}/_ext/760557894/interrupt.o ${OBJECTDIR}/_ext/1472/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/usb_descriptors.o.d ${OBJECTDIR}/_ext/1730819898/selftest.o.d ${OBJECTDIR}/_ext/1179396225/CAN2515user.o.d ${OBJECTDIR}/_ext/1179396225/CAN_useCAN1.o.d ${OBJECTDIR}/_ext/1179396225/CAN_useCAN2.o.d ${OBJECTDIR}/_ext/1179396225/CAN2515utils.o.d ${OBJECTDIR}/_ext/1179396225/CAN_MsgList.o.d ${OBJECTDIR}/_ext/1179396225/CAN2515drv.o.d ${OBJECTDIR}/_ext/1659146991/display4d.o.d ${OBJECTDIR}/_ext/1659146991/hd44780.o.d ${OBJECTDIR}/_ext/938477934/simstat.o.d ${OBJECTDIR}/_ext/938477934/speedboxuser.o.d ${OBJECTDIR}/_ext/1552693807/eeprom.o.d ${OBJECTDIR}/_ext/1151835195/simbuckserial.o.d ${OBJECTDIR}/_ext/1179351275/simbuckpwm.o.d ${OBJECTDIR}/_ext/1179348613/simbuckspi.o.d ${OBJECTDIR}/_ext/1235981372/usb_function_generic.o.d ${OBJECTDIR}/_ext/1412100490/usb_device.o.d ${OBJECTDIR}/_ext/760557894/processUSBpacket.o.d ${OBJECTDIR}/_ext/760557894/userInits.o.d ${OBJECTDIR}/_ext/760557894/interrupt.o.d ${OBJECTDIR}/_ext/1472/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/usb_descriptors.o ${OBJECTDIR}/_ext/1730819898/selftest.o ${OBJECTDIR}/_ext/1179396225/CAN2515user.o ${OBJECTDIR}/_ext/1179396225/CAN_useCAN1.o ${OBJECTDIR}/_ext/1179396225/CAN_useCAN2.o ${OBJECTDIR}/_ext/1179396225/CAN2515utils.o ${OBJECTDIR}/_ext/1179396225/CAN_MsgList.o ${OBJECTDIR}/_ext/1179396225/CAN2515drv.o ${OBJECTDIR}/_ext/1659146991/display4d.o ${OBJECTDIR}/_ext/1659146991/hd44780.o ${OBJECTDIR}/_ext/938477934/simstat.o ${OBJECTDIR}/_ext/938477934/speedboxuser.o ${OBJECTDIR}/_ext/1552693807/eeprom.o ${OBJECTDIR}/_ext/1151835195/simbuckserial.o ${OBJECTDIR}/_ext/1179351275/simbuckpwm.o ${OBJECTDIR}/_ext/1179348613/simbuckspi.o ${OBJECTDIR}/_ext/1235981372/usb_function_generic.o ${OBJECTDIR}/_ext/1412100490/usb_device.o ${OBJECTDIR}/_ext/760557894/processUSBpacket.o ${OBJECTDIR}/_ext/760557894/userInits.o ${OBJECTDIR}/_ext/760557894/interrupt.o ${OBJECTDIR}/_ext/1472/main.o

# Source Files
SOURCEFILES=../usb_descriptors.c ../selftests/selftest.c ../system/CAN/CAN2515user.c ../system/CAN/CAN_useCAN1.c ../system/CAN/CAN_useCAN2.c ../system/CAN/CAN2515utils.c ../system/CAN/CAN_MsgList.c ../system/CAN/CAN2515drv.c ../system/display/display4d.c ../system/display/hd44780.c ../device/speedbox/simstat.c ../device/speedbox/speedboxuser.c ../system/eeprom/eeprom.c ../system/serial/simbuckserial.c ../system/pwm/simbuckpwm.c ../system/spi/simbuckspi.c ../system/USBstack/USB/Generic Device Driver/usb_function_generic.c ../system/USBstack/USB/usb_device.c ../user/processUSBpacket.c ../user/userInits.c ../user/interrupt.c ../main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-speedBox_4550.mk dist/${CND_CONF}/${IMAGE_TYPE}/simbuck-libusb.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4550
MP_PROCESSOR_OPTION_LD=18f4550
MP_LINKER_DEBUG_OPTION= -u_DEBUGCODESTART=0x7dc0 -u_DEBUGCODELEN=0x240 -u_DEBUGDATASTART=0x3f4 -u_DEBUGDATALEN=0xb
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/usb_descriptors.o: ../usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/usb_descriptors.o   ../usb_descriptors.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1730819898/selftest.o: ../selftests/selftest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1730819898 
	@${RM} ${OBJECTDIR}/_ext/1730819898/selftest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1730819898/selftest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1730819898/selftest.o   ../selftests/selftest.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1730819898/selftest.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1730819898/selftest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179396225/CAN2515user.o: ../system/CAN/CAN2515user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179396225 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN2515user.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN2515user.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179396225/CAN2515user.o   ../system/CAN/CAN2515user.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179396225/CAN2515user.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179396225/CAN2515user.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179396225/CAN_useCAN1.o: ../system/CAN/CAN_useCAN1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179396225 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN_useCAN1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN_useCAN1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179396225/CAN_useCAN1.o   ../system/CAN/CAN_useCAN1.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179396225/CAN_useCAN1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179396225/CAN_useCAN1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179396225/CAN_useCAN2.o: ../system/CAN/CAN_useCAN2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179396225 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN_useCAN2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN_useCAN2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179396225/CAN_useCAN2.o   ../system/CAN/CAN_useCAN2.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179396225/CAN_useCAN2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179396225/CAN_useCAN2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179396225/CAN2515utils.o: ../system/CAN/CAN2515utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179396225 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN2515utils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN2515utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179396225/CAN2515utils.o   ../system/CAN/CAN2515utils.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179396225/CAN2515utils.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179396225/CAN2515utils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179396225/CAN_MsgList.o: ../system/CAN/CAN_MsgList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179396225 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN_MsgList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN_MsgList.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179396225/CAN_MsgList.o   ../system/CAN/CAN_MsgList.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179396225/CAN_MsgList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179396225/CAN_MsgList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179396225/CAN2515drv.o: ../system/CAN/CAN2515drv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179396225 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN2515drv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN2515drv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179396225/CAN2515drv.o   ../system/CAN/CAN2515drv.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179396225/CAN2515drv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179396225/CAN2515drv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1659146991/display4d.o: ../system/display/display4d.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1659146991 
	@${RM} ${OBJECTDIR}/_ext/1659146991/display4d.o.d 
	@${RM} ${OBJECTDIR}/_ext/1659146991/display4d.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1659146991/display4d.o   ../system/display/display4d.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1659146991/display4d.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1659146991/display4d.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1659146991/hd44780.o: ../system/display/hd44780.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1659146991 
	@${RM} ${OBJECTDIR}/_ext/1659146991/hd44780.o.d 
	@${RM} ${OBJECTDIR}/_ext/1659146991/hd44780.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1659146991/hd44780.o   ../system/display/hd44780.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1659146991/hd44780.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1659146991/hd44780.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/938477934/simstat.o: ../device/speedbox/simstat.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/938477934 
	@${RM} ${OBJECTDIR}/_ext/938477934/simstat.o.d 
	@${RM} ${OBJECTDIR}/_ext/938477934/simstat.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/938477934/simstat.o   ../device/speedbox/simstat.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/938477934/simstat.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/938477934/simstat.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/938477934/speedboxuser.o: ../device/speedbox/speedboxuser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/938477934 
	@${RM} ${OBJECTDIR}/_ext/938477934/speedboxuser.o.d 
	@${RM} ${OBJECTDIR}/_ext/938477934/speedboxuser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/938477934/speedboxuser.o   ../device/speedbox/speedboxuser.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/938477934/speedboxuser.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/938477934/speedboxuser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1552693807/eeprom.o: ../system/eeprom/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1552693807 
	@${RM} ${OBJECTDIR}/_ext/1552693807/eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1552693807/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1552693807/eeprom.o   ../system/eeprom/eeprom.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1552693807/eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1552693807/eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1151835195/simbuckserial.o: ../system/serial/simbuckserial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1151835195 
	@${RM} ${OBJECTDIR}/_ext/1151835195/simbuckserial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1151835195/simbuckserial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1151835195/simbuckserial.o   ../system/serial/simbuckserial.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1151835195/simbuckserial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1151835195/simbuckserial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179351275/simbuckpwm.o: ../system/pwm/simbuckpwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179351275 
	@${RM} ${OBJECTDIR}/_ext/1179351275/simbuckpwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179351275/simbuckpwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179351275/simbuckpwm.o   ../system/pwm/simbuckpwm.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179351275/simbuckpwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179351275/simbuckpwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179348613/simbuckspi.o: ../system/spi/simbuckspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179348613 
	@${RM} ${OBJECTDIR}/_ext/1179348613/simbuckspi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179348613/simbuckspi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179348613/simbuckspi.o   ../system/spi/simbuckspi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179348613/simbuckspi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179348613/simbuckspi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1235981372/usb_function_generic.o: ../system/USBstack/USB/Generic\ Device\ Driver/usb_function_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1235981372 
	@${RM} ${OBJECTDIR}/_ext/1235981372/usb_function_generic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1235981372/usb_function_generic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1235981372/usb_function_generic.o   "../system/USBstack/USB/Generic Device Driver/usb_function_generic.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1235981372/usb_function_generic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1235981372/usb_function_generic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1412100490/usb_device.o: ../system/USBstack/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1412100490 
	@${RM} ${OBJECTDIR}/_ext/1412100490/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1412100490/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1412100490/usb_device.o   ../system/USBstack/USB/usb_device.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1412100490/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1412100490/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/processUSBpacket.o: ../user/processUSBpacket.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760557894 
	@${RM} ${OBJECTDIR}/_ext/760557894/processUSBpacket.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/processUSBpacket.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/760557894/processUSBpacket.o   ../user/processUSBpacket.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/processUSBpacket.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/processUSBpacket.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/userInits.o: ../user/userInits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760557894 
	@${RM} ${OBJECTDIR}/_ext/760557894/userInits.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/userInits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/760557894/userInits.o   ../user/userInits.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/userInits.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/userInits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/interrupt.o: ../user/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760557894 
	@${RM} ${OBJECTDIR}/_ext/760557894/interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/760557894/interrupt.o   ../user/interrupt.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/main.o   ../main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/_ext/1472/usb_descriptors.o: ../usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/usb_descriptors.o   ../usb_descriptors.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1730819898/selftest.o: ../selftests/selftest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1730819898 
	@${RM} ${OBJECTDIR}/_ext/1730819898/selftest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1730819898/selftest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1730819898/selftest.o   ../selftests/selftest.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1730819898/selftest.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1730819898/selftest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179396225/CAN2515user.o: ../system/CAN/CAN2515user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179396225 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN2515user.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN2515user.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179396225/CAN2515user.o   ../system/CAN/CAN2515user.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179396225/CAN2515user.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179396225/CAN2515user.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179396225/CAN_useCAN1.o: ../system/CAN/CAN_useCAN1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179396225 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN_useCAN1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN_useCAN1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179396225/CAN_useCAN1.o   ../system/CAN/CAN_useCAN1.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179396225/CAN_useCAN1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179396225/CAN_useCAN1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179396225/CAN_useCAN2.o: ../system/CAN/CAN_useCAN2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179396225 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN_useCAN2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN_useCAN2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179396225/CAN_useCAN2.o   ../system/CAN/CAN_useCAN2.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179396225/CAN_useCAN2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179396225/CAN_useCAN2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179396225/CAN2515utils.o: ../system/CAN/CAN2515utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179396225 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN2515utils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN2515utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179396225/CAN2515utils.o   ../system/CAN/CAN2515utils.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179396225/CAN2515utils.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179396225/CAN2515utils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179396225/CAN_MsgList.o: ../system/CAN/CAN_MsgList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179396225 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN_MsgList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN_MsgList.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179396225/CAN_MsgList.o   ../system/CAN/CAN_MsgList.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179396225/CAN_MsgList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179396225/CAN_MsgList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179396225/CAN2515drv.o: ../system/CAN/CAN2515drv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179396225 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN2515drv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179396225/CAN2515drv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179396225/CAN2515drv.o   ../system/CAN/CAN2515drv.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179396225/CAN2515drv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179396225/CAN2515drv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1659146991/display4d.o: ../system/display/display4d.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1659146991 
	@${RM} ${OBJECTDIR}/_ext/1659146991/display4d.o.d 
	@${RM} ${OBJECTDIR}/_ext/1659146991/display4d.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1659146991/display4d.o   ../system/display/display4d.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1659146991/display4d.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1659146991/display4d.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1659146991/hd44780.o: ../system/display/hd44780.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1659146991 
	@${RM} ${OBJECTDIR}/_ext/1659146991/hd44780.o.d 
	@${RM} ${OBJECTDIR}/_ext/1659146991/hd44780.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1659146991/hd44780.o   ../system/display/hd44780.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1659146991/hd44780.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1659146991/hd44780.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/938477934/simstat.o: ../device/speedbox/simstat.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/938477934 
	@${RM} ${OBJECTDIR}/_ext/938477934/simstat.o.d 
	@${RM} ${OBJECTDIR}/_ext/938477934/simstat.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/938477934/simstat.o   ../device/speedbox/simstat.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/938477934/simstat.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/938477934/simstat.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/938477934/speedboxuser.o: ../device/speedbox/speedboxuser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/938477934 
	@${RM} ${OBJECTDIR}/_ext/938477934/speedboxuser.o.d 
	@${RM} ${OBJECTDIR}/_ext/938477934/speedboxuser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/938477934/speedboxuser.o   ../device/speedbox/speedboxuser.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/938477934/speedboxuser.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/938477934/speedboxuser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1552693807/eeprom.o: ../system/eeprom/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1552693807 
	@${RM} ${OBJECTDIR}/_ext/1552693807/eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1552693807/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1552693807/eeprom.o   ../system/eeprom/eeprom.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1552693807/eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1552693807/eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1151835195/simbuckserial.o: ../system/serial/simbuckserial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1151835195 
	@${RM} ${OBJECTDIR}/_ext/1151835195/simbuckserial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1151835195/simbuckserial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1151835195/simbuckserial.o   ../system/serial/simbuckserial.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1151835195/simbuckserial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1151835195/simbuckserial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179351275/simbuckpwm.o: ../system/pwm/simbuckpwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179351275 
	@${RM} ${OBJECTDIR}/_ext/1179351275/simbuckpwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179351275/simbuckpwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179351275/simbuckpwm.o   ../system/pwm/simbuckpwm.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179351275/simbuckpwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179351275/simbuckpwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179348613/simbuckspi.o: ../system/spi/simbuckspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179348613 
	@${RM} ${OBJECTDIR}/_ext/1179348613/simbuckspi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179348613/simbuckspi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179348613/simbuckspi.o   ../system/spi/simbuckspi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179348613/simbuckspi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179348613/simbuckspi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1235981372/usb_function_generic.o: ../system/USBstack/USB/Generic\ Device\ Driver/usb_function_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1235981372 
	@${RM} ${OBJECTDIR}/_ext/1235981372/usb_function_generic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1235981372/usb_function_generic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1235981372/usb_function_generic.o   "../system/USBstack/USB/Generic Device Driver/usb_function_generic.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1235981372/usb_function_generic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1235981372/usb_function_generic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1412100490/usb_device.o: ../system/USBstack/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1412100490 
	@${RM} ${OBJECTDIR}/_ext/1412100490/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1412100490/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1412100490/usb_device.o   ../system/USBstack/USB/usb_device.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1412100490/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1412100490/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/processUSBpacket.o: ../user/processUSBpacket.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760557894 
	@${RM} ${OBJECTDIR}/_ext/760557894/processUSBpacket.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/processUSBpacket.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/760557894/processUSBpacket.o   ../user/processUSBpacket.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/processUSBpacket.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/processUSBpacket.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/userInits.o: ../user/userInits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760557894 
	@${RM} ${OBJECTDIR}/_ext/760557894/userInits.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/userInits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/760557894/userInits.o   ../user/userInits.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/userInits.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/userInits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/interrupt.o: ../user/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760557894 
	@${RM} ${OBJECTDIR}/_ext/760557894/interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/760557894/interrupt.o   ../user/interrupt.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../system" -I"../system/USBstack" -I"../system/USBstack/Include" -I"../system/USBstack/Include/USB" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/main.o   ../main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/simbuck-libusb.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../rm18f4550\ -\ Simbuck\ HID\ Bootload.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "..\rm18f4550 - Simbuck HID Bootload.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"$(BINDIR_)$(TARGETBASE).map" -w  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_ICD3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/simbuck-libusb.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/simbuck-libusb.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../rm18f4550\ -\ Simbuck\ HID\ Bootload.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "..\rm18f4550 - Simbuck HID Bootload.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"$(BINDIR_)$(TARGETBASE).map" -w  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/simbuck-libusb.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/speedBox_4550
	${RM} -r dist/speedBox_4550

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
