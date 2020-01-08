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
ifeq "$(wildcard nbproject/Makefile-local-EVBattPack.mk)" "nbproject/Makefile-local-EVBattPack.mk"
include nbproject/Makefile-local-EVBattPack.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=EVBattPack
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

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1730819898/selftest.o ${OBJECTDIR}/_ext/1659146991/hd44780.o ${OBJECTDIR}/_ext/1521062797/user_evbattpack.o ${OBJECTDIR}/_ext/1179366289/simbuckadc.o ${OBJECTDIR}/_ext/2093483868/ECAN_MsgList.o ${OBJECTDIR}/_ext/2093483868/ECAN_User.o ${OBJECTDIR}/_ext/1552693807/eeprom.o ${OBJECTDIR}/_ext/1151835195/simbuckserial.o ${OBJECTDIR}/_ext/1179348613/simbuckspi.o ${OBJECTDIR}/_ext/760557894/userInits.o ${OBJECTDIR}/_ext/760557894/interrupt.o ${OBJECTDIR}/_ext/1472/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1730819898/selftest.o.d ${OBJECTDIR}/_ext/1659146991/hd44780.o.d ${OBJECTDIR}/_ext/1521062797/user_evbattpack.o.d ${OBJECTDIR}/_ext/1179366289/simbuckadc.o.d ${OBJECTDIR}/_ext/2093483868/ECAN_MsgList.o.d ${OBJECTDIR}/_ext/2093483868/ECAN_User.o.d ${OBJECTDIR}/_ext/1552693807/eeprom.o.d ${OBJECTDIR}/_ext/1151835195/simbuckserial.o.d ${OBJECTDIR}/_ext/1179348613/simbuckspi.o.d ${OBJECTDIR}/_ext/760557894/userInits.o.d ${OBJECTDIR}/_ext/760557894/interrupt.o.d ${OBJECTDIR}/_ext/1472/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1730819898/selftest.o ${OBJECTDIR}/_ext/1659146991/hd44780.o ${OBJECTDIR}/_ext/1521062797/user_evbattpack.o ${OBJECTDIR}/_ext/1179366289/simbuckadc.o ${OBJECTDIR}/_ext/2093483868/ECAN_MsgList.o ${OBJECTDIR}/_ext/2093483868/ECAN_User.o ${OBJECTDIR}/_ext/1552693807/eeprom.o ${OBJECTDIR}/_ext/1151835195/simbuckserial.o ${OBJECTDIR}/_ext/1179348613/simbuckspi.o ${OBJECTDIR}/_ext/760557894/userInits.o ${OBJECTDIR}/_ext/760557894/interrupt.o ${OBJECTDIR}/_ext/1472/main.o


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-EVBattPack.mk dist/${CND_CONF}/${IMAGE_TYPE}/simbuck-libusb.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4685
MP_PROCESSOR_OPTION_LD=18f4685
MP_LINKER_DEBUG_OPTION= -u_DEBUGCODESTART=0x17d30 -u_DEBUGCODELEN=0x2d0 -u_DEBUGDATASTART=0xcf4 -u_DEBUGDATALEN=0xb
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1730819898/selftest.o: ../selftests/selftest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1730819898 
	@${RM} ${OBJECTDIR}/_ext/1730819898/selftest.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1730819898/selftest.o   ../selftests/selftest.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1730819898/selftest.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1730819898/selftest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1659146991/hd44780.o: ../system/display/hd44780.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1659146991 
	@${RM} ${OBJECTDIR}/_ext/1659146991/hd44780.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1659146991/hd44780.o   ../system/display/hd44780.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1659146991/hd44780.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1659146991/hd44780.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1521062797/user_evbattpack.o: ../device/EvBattPack/user_evbattpack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1521062797 
	@${RM} ${OBJECTDIR}/_ext/1521062797/user_evbattpack.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1521062797/user_evbattpack.o   ../device/EvBattPack/user_evbattpack.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1521062797/user_evbattpack.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1521062797/user_evbattpack.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179366289/simbuckadc.o: ../system/adc/simbuckadc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179366289 
	@${RM} ${OBJECTDIR}/_ext/1179366289/simbuckadc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179366289/simbuckadc.o   ../system/adc/simbuckadc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179366289/simbuckadc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179366289/simbuckadc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2093483868/ECAN_MsgList.o: ../system/ECAN/ECAN_MsgList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2093483868 
	@${RM} ${OBJECTDIR}/_ext/2093483868/ECAN_MsgList.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2093483868/ECAN_MsgList.o   ../system/ECAN/ECAN_MsgList.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2093483868/ECAN_MsgList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2093483868/ECAN_MsgList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2093483868/ECAN_User.o: ../system/ECAN/ECAN_User.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2093483868 
	@${RM} ${OBJECTDIR}/_ext/2093483868/ECAN_User.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2093483868/ECAN_User.o   ../system/ECAN/ECAN_User.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2093483868/ECAN_User.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2093483868/ECAN_User.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1552693807/eeprom.o: ../system/eeprom/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1552693807 
	@${RM} ${OBJECTDIR}/_ext/1552693807/eeprom.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1552693807/eeprom.o   ../system/eeprom/eeprom.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1552693807/eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1552693807/eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1151835195/simbuckserial.o: ../system/serial/simbuckserial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1151835195 
	@${RM} ${OBJECTDIR}/_ext/1151835195/simbuckserial.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1151835195/simbuckserial.o   ../system/serial/simbuckserial.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1151835195/simbuckserial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1151835195/simbuckserial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179348613/simbuckspi.o: ../system/spi/simbuckspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179348613 
	@${RM} ${OBJECTDIR}/_ext/1179348613/simbuckspi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179348613/simbuckspi.o   ../system/spi/simbuckspi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179348613/simbuckspi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179348613/simbuckspi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/userInits.o: ../user/userInits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760557894 
	@${RM} ${OBJECTDIR}/_ext/760557894/userInits.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/760557894/userInits.o   ../user/userInits.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/userInits.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/userInits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/interrupt.o: ../user/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760557894 
	@${RM} ${OBJECTDIR}/_ext/760557894/interrupt.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/760557894/interrupt.o   ../user/interrupt.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/main.o   ../main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/_ext/1730819898/selftest.o: ../selftests/selftest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1730819898 
	@${RM} ${OBJECTDIR}/_ext/1730819898/selftest.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1730819898/selftest.o   ../selftests/selftest.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1730819898/selftest.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1730819898/selftest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1659146991/hd44780.o: ../system/display/hd44780.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1659146991 
	@${RM} ${OBJECTDIR}/_ext/1659146991/hd44780.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1659146991/hd44780.o   ../system/display/hd44780.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1659146991/hd44780.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1659146991/hd44780.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1521062797/user_evbattpack.o: ../device/EvBattPack/user_evbattpack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1521062797 
	@${RM} ${OBJECTDIR}/_ext/1521062797/user_evbattpack.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1521062797/user_evbattpack.o   ../device/EvBattPack/user_evbattpack.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1521062797/user_evbattpack.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1521062797/user_evbattpack.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179366289/simbuckadc.o: ../system/adc/simbuckadc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179366289 
	@${RM} ${OBJECTDIR}/_ext/1179366289/simbuckadc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179366289/simbuckadc.o   ../system/adc/simbuckadc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179366289/simbuckadc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179366289/simbuckadc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2093483868/ECAN_MsgList.o: ../system/ECAN/ECAN_MsgList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2093483868 
	@${RM} ${OBJECTDIR}/_ext/2093483868/ECAN_MsgList.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2093483868/ECAN_MsgList.o   ../system/ECAN/ECAN_MsgList.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2093483868/ECAN_MsgList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2093483868/ECAN_MsgList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2093483868/ECAN_User.o: ../system/ECAN/ECAN_User.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2093483868 
	@${RM} ${OBJECTDIR}/_ext/2093483868/ECAN_User.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2093483868/ECAN_User.o   ../system/ECAN/ECAN_User.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2093483868/ECAN_User.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2093483868/ECAN_User.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1552693807/eeprom.o: ../system/eeprom/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1552693807 
	@${RM} ${OBJECTDIR}/_ext/1552693807/eeprom.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1552693807/eeprom.o   ../system/eeprom/eeprom.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1552693807/eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1552693807/eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1151835195/simbuckserial.o: ../system/serial/simbuckserial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1151835195 
	@${RM} ${OBJECTDIR}/_ext/1151835195/simbuckserial.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1151835195/simbuckserial.o   ../system/serial/simbuckserial.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1151835195/simbuckserial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1151835195/simbuckserial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1179348613/simbuckspi.o: ../system/spi/simbuckspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179348613 
	@${RM} ${OBJECTDIR}/_ext/1179348613/simbuckspi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1179348613/simbuckspi.o   ../system/spi/simbuckspi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1179348613/simbuckspi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179348613/simbuckspi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/userInits.o: ../user/userInits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760557894 
	@${RM} ${OBJECTDIR}/_ext/760557894/userInits.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/760557894/userInits.o   ../user/userInits.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/userInits.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/userInits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/interrupt.o: ../user/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760557894 
	@${RM} ${OBJECTDIR}/_ext/760557894/interrupt.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/760557894/interrupt.o   ../user/interrupt.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../eeprom" -I"../user" -I"../spi" -I"../serial" -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/main.o   ../main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/simbuck-libusb.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../18f4685_g.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "..\18f4685_g.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"$(BINDIR_)$(TARGETBASE).map" -w -l"/opt/microchip/mplabc18/v3.40/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_ICD3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/simbuck-libusb.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/simbuck-libusb.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../18f4685_g.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "..\18f4685_g.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"$(BINDIR_)$(TARGETBASE).map" -w -l"/opt/microchip/mplabc18/v3.40/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/simbuck-libusb.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/EVBattPack
	${RM} -r dist/EVBattPack

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
