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
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/config/default/driver/at24/src/drv_at24.c ../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/i2c/plib_i2c1.c ../src/config/default/peripheral/nvm/plib_nvm.c ../src/config/default/peripheral/rcon/plib_rcon.c ../src/config/default/peripheral/uart/plib_uart3.c ../src/config/default/peripheral/uart/plib_uart1.c ../src/config/default/system/dma/sys_dma.c ../src/config/default/system/int/src/sys_int.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/interrupts_a.S ../src/config/default/exceptions.c ../src/config/default/freertos_hooks.c ../src/config/default/tasks.c ../src/audits.c ../src/parameters.c ../src/dataCommun.c ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c ../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../src/third_party/rtos/FreeRTOS/Source/croutine.c ../src/third_party/rtos/FreeRTOS/Source/list.c ../src/third_party/rtos/FreeRTOS/Source/queue.c ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c ../src/third_party/rtos/FreeRTOS/Source/timers.c ../src/third_party/rtos/FreeRTOS/Source/event_groups.c ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c ../src/MDB/MDB.c ../src/MDB/MDB_CG.c ../src/MDB/MDB_BV.c ../src/config/default/osal/osal_freertos.c ../src/hd44780.c ../src/delay_us.c ../src/leds.c ../src/DS18B20.c ../src/contacts.c ../src/moteurs.c ../src/main.c ../src/mainboard2.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/897820976/drv_at24.o ${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/60169480/plib_i2c1.o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ${OBJECTDIR}/_ext/1865569570/plib_rcon.o ${OBJECTDIR}/_ext/1865657120/plib_uart3.o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ${OBJECTDIR}/_ext/14461671/sys_dma.o ${OBJECTDIR}/_ext/1881668453/sys_int.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/interrupts_a.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ${OBJECTDIR}/_ext/1171490990/tasks.o ${OBJECTDIR}/_ext/1360937237/audits.o ${OBJECTDIR}/_ext/1360937237/parameters.o ${OBJECTDIR}/_ext/1360937237/dataCommun.o ${OBJECTDIR}/_ext/1665200909/heap_1.o ${OBJECTDIR}/_ext/951553248/port.o ${OBJECTDIR}/_ext/951553248/port_asm.o ${OBJECTDIR}/_ext/404212886/croutine.o ${OBJECTDIR}/_ext/404212886/list.o ${OBJECTDIR}/_ext/404212886/queue.o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ${OBJECTDIR}/_ext/404212886/timers.o ${OBJECTDIR}/_ext/404212886/event_groups.o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ${OBJECTDIR}/_ext/659830161/MDB.o ${OBJECTDIR}/_ext/659830161/MDB_CG.o ${OBJECTDIR}/_ext/659830161/MDB_BV.o ${OBJECTDIR}/_ext/1529399856/osal_freertos.o ${OBJECTDIR}/_ext/1360937237/hd44780.o ${OBJECTDIR}/_ext/1360937237/delay_us.o ${OBJECTDIR}/_ext/1360937237/leds.o ${OBJECTDIR}/_ext/1360937237/DS18B20.o ${OBJECTDIR}/_ext/1360937237/contacts.o ${OBJECTDIR}/_ext/1360937237/moteurs.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/mainboard2.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/897820976/drv_at24.o.d ${OBJECTDIR}/_ext/60165520/plib_clk.o.d ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d ${OBJECTDIR}/_ext/60169480/plib_i2c1.o.d ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d ${OBJECTDIR}/_ext/1865569570/plib_rcon.o.d ${OBJECTDIR}/_ext/1865657120/plib_uart3.o.d ${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d ${OBJECTDIR}/_ext/14461671/sys_dma.o.d ${OBJECTDIR}/_ext/1881668453/sys_int.o.d ${OBJECTDIR}/_ext/1171490990/initialization.o.d ${OBJECTDIR}/_ext/1171490990/interrupts.o.d ${OBJECTDIR}/_ext/1171490990/interrupts_a.o.d ${OBJECTDIR}/_ext/1171490990/exceptions.o.d ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d ${OBJECTDIR}/_ext/1171490990/tasks.o.d ${OBJECTDIR}/_ext/1360937237/audits.o.d ${OBJECTDIR}/_ext/1360937237/parameters.o.d ${OBJECTDIR}/_ext/1360937237/dataCommun.o.d ${OBJECTDIR}/_ext/1665200909/heap_1.o.d ${OBJECTDIR}/_ext/951553248/port.o.d ${OBJECTDIR}/_ext/951553248/port_asm.o.d ${OBJECTDIR}/_ext/404212886/croutine.o.d ${OBJECTDIR}/_ext/404212886/list.o.d ${OBJECTDIR}/_ext/404212886/queue.o.d ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d ${OBJECTDIR}/_ext/404212886/timers.o.d ${OBJECTDIR}/_ext/404212886/event_groups.o.d ${OBJECTDIR}/_ext/404212886/stream_buffer.o.d ${OBJECTDIR}/_ext/659830161/MDB.o.d ${OBJECTDIR}/_ext/659830161/MDB_CG.o.d ${OBJECTDIR}/_ext/659830161/MDB_BV.o.d ${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d ${OBJECTDIR}/_ext/1360937237/hd44780.o.d ${OBJECTDIR}/_ext/1360937237/delay_us.o.d ${OBJECTDIR}/_ext/1360937237/leds.o.d ${OBJECTDIR}/_ext/1360937237/DS18B20.o.d ${OBJECTDIR}/_ext/1360937237/contacts.o.d ${OBJECTDIR}/_ext/1360937237/moteurs.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/mainboard2.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/897820976/drv_at24.o ${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/60169480/plib_i2c1.o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ${OBJECTDIR}/_ext/1865569570/plib_rcon.o ${OBJECTDIR}/_ext/1865657120/plib_uart3.o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ${OBJECTDIR}/_ext/14461671/sys_dma.o ${OBJECTDIR}/_ext/1881668453/sys_int.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/interrupts_a.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ${OBJECTDIR}/_ext/1171490990/tasks.o ${OBJECTDIR}/_ext/1360937237/audits.o ${OBJECTDIR}/_ext/1360937237/parameters.o ${OBJECTDIR}/_ext/1360937237/dataCommun.o ${OBJECTDIR}/_ext/1665200909/heap_1.o ${OBJECTDIR}/_ext/951553248/port.o ${OBJECTDIR}/_ext/951553248/port_asm.o ${OBJECTDIR}/_ext/404212886/croutine.o ${OBJECTDIR}/_ext/404212886/list.o ${OBJECTDIR}/_ext/404212886/queue.o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ${OBJECTDIR}/_ext/404212886/timers.o ${OBJECTDIR}/_ext/404212886/event_groups.o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ${OBJECTDIR}/_ext/659830161/MDB.o ${OBJECTDIR}/_ext/659830161/MDB_CG.o ${OBJECTDIR}/_ext/659830161/MDB_BV.o ${OBJECTDIR}/_ext/1529399856/osal_freertos.o ${OBJECTDIR}/_ext/1360937237/hd44780.o ${OBJECTDIR}/_ext/1360937237/delay_us.o ${OBJECTDIR}/_ext/1360937237/leds.o ${OBJECTDIR}/_ext/1360937237/DS18B20.o ${OBJECTDIR}/_ext/1360937237/contacts.o ${OBJECTDIR}/_ext/1360937237/moteurs.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/mainboard2.o

# Source Files
SOURCEFILES=../src/config/default/driver/at24/src/drv_at24.c ../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/i2c/plib_i2c1.c ../src/config/default/peripheral/nvm/plib_nvm.c ../src/config/default/peripheral/rcon/plib_rcon.c ../src/config/default/peripheral/uart/plib_uart3.c ../src/config/default/peripheral/uart/plib_uart1.c ../src/config/default/system/dma/sys_dma.c ../src/config/default/system/int/src/sys_int.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/interrupts_a.S ../src/config/default/exceptions.c ../src/config/default/freertos_hooks.c ../src/config/default/tasks.c ../src/audits.c ../src/parameters.c ../src/dataCommun.c ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c ../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../src/third_party/rtos/FreeRTOS/Source/croutine.c ../src/third_party/rtos/FreeRTOS/Source/list.c ../src/third_party/rtos/FreeRTOS/Source/queue.c ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c ../src/third_party/rtos/FreeRTOS/Source/timers.c ../src/third_party/rtos/FreeRTOS/Source/event_groups.c ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c ../src/MDB/MDB.c ../src/MDB/MDB_CG.c ../src/MDB/MDB_BV.c ../src/config/default/osal/osal_freertos.c ../src/hd44780.c ../src/delay_us.c ../src/leds.c ../src/DS18B20.c ../src/contacts.c ../src/moteurs.c ../src/main.c ../src/mainboard2.c



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
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX470F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1171490990/interrupts_a.o: ../src/config/default/interrupts_a.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts_a.o 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts_a.o.ok ${OBJECTDIR}/_ext/1171490990/interrupts_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/interrupts_a.o.d" "${OBJECTDIR}/_ext/1171490990/interrupts_a.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/config/default" -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts_a.o.d"  -o ${OBJECTDIR}/_ext/1171490990/interrupts_a.o ../src/config/default/interrupts_a.S  -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1171490990/interrupts_a.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/config/default" -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/951553248/port_asm.o: ../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/951553248" 
	@${RM} ${OBJECTDIR}/_ext/951553248/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/951553248/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/951553248/port_asm.o.ok ${OBJECTDIR}/_ext/951553248/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/951553248/port_asm.o.d" "${OBJECTDIR}/_ext/951553248/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/config/default" -MMD -MF "${OBJECTDIR}/_ext/951553248/port_asm.o.d"  -o ${OBJECTDIR}/_ext/951553248/port_asm.o ../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/951553248/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/config/default" -mdfp=${DFP_DIR}
	
else
${OBJECTDIR}/_ext/1171490990/interrupts_a.o: ../src/config/default/interrupts_a.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts_a.o 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts_a.o.ok ${OBJECTDIR}/_ext/1171490990/interrupts_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/interrupts_a.o.d" "${OBJECTDIR}/_ext/1171490990/interrupts_a.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/config/default" -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts_a.o.d"  -o ${OBJECTDIR}/_ext/1171490990/interrupts_a.o ../src/config/default/interrupts_a.S  -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1171490990/interrupts_a.o.asm.d",--gdwarf-2,-I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/config/default" -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/951553248/port_asm.o: ../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/951553248" 
	@${RM} ${OBJECTDIR}/_ext/951553248/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/951553248/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/951553248/port_asm.o.ok ${OBJECTDIR}/_ext/951553248/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/951553248/port_asm.o.d" "${OBJECTDIR}/_ext/951553248/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/config/default" -MMD -MF "${OBJECTDIR}/_ext/951553248/port_asm.o.d"  -o ${OBJECTDIR}/_ext/951553248/port_asm.o ../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/951553248/port_asm.o.asm.d",--gdwarf-2,-I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -I"../src/config/default" -mdfp=${DFP_DIR}
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/897820976/drv_at24.o: ../src/config/default/driver/at24/src/drv_at24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/897820976" 
	@${RM} ${OBJECTDIR}/_ext/897820976/drv_at24.o.d 
	@${RM} ${OBJECTDIR}/_ext/897820976/drv_at24.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/897820976/drv_at24.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/897820976/drv_at24.o.d" -o ${OBJECTDIR}/_ext/897820976/drv_at24.o ../src/config/default/driver/at24/src/drv_at24.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/60169480/plib_i2c1.o: ../src/config/default/peripheral/i2c/plib_i2c1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/60169480" 
	@${RM} ${OBJECTDIR}/_ext/60169480/plib_i2c1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60169480/plib_i2c1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/60169480/plib_i2c1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/60169480/plib_i2c1.o.d" -o ${OBJECTDIR}/_ext/60169480/plib_i2c1.o ../src/config/default/peripheral/i2c/plib_i2c1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1865569570/plib_rcon.o: ../src/config/default/peripheral/rcon/plib_rcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1865569570" 
	@${RM} ${OBJECTDIR}/_ext/1865569570/plib_rcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865569570/plib_rcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1865569570/plib_rcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1865569570/plib_rcon.o.d" -o ${OBJECTDIR}/_ext/1865569570/plib_rcon.o ../src/config/default/peripheral/rcon/plib_rcon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1865657120/plib_uart3.o: ../src/config/default/peripheral/uart/plib_uart3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1865657120/plib_uart3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart3.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart3.o ../src/config/default/peripheral/uart/plib_uart3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1865657120/plib_uart1.o: ../src/config/default/peripheral/uart/plib_uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ../src/config/default/peripheral/uart/plib_uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/14461671/sys_dma.o: ../src/config/default/system/dma/sys_dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/14461671" 
	@${RM} ${OBJECTDIR}/_ext/14461671/sys_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/14461671/sys_dma.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/14461671/sys_dma.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/14461671/sys_dma.o.d" -o ${OBJECTDIR}/_ext/14461671/sys_dma.o ../src/config/default/system/dma/sys_dma.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1881668453/sys_int.o: ../src/config/default/system/int/src/sys_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1881668453" 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" -o ${OBJECTDIR}/_ext/1881668453/sys_int.o ../src/config/default/system/int/src/sys_int.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/initialization.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1171490990/freertos_hooks.o: ../src/config/default/freertos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d" -o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ../src/config/default/freertos_hooks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1171490990/tasks.o: ../src/config/default/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1171490990/tasks.o.d" -o ${OBJECTDIR}/_ext/1171490990/tasks.o ../src/config/default/tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/audits.o: ../src/audits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/audits.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/audits.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/audits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/audits.o.d" -o ${OBJECTDIR}/_ext/1360937237/audits.o ../src/audits.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/parameters.o: ../src/parameters.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/parameters.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/parameters.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/parameters.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/parameters.o.d" -o ${OBJECTDIR}/_ext/1360937237/parameters.o ../src/parameters.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/dataCommun.o: ../src/dataCommun.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dataCommun.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dataCommun.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/dataCommun.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/dataCommun.o.d" -o ${OBJECTDIR}/_ext/1360937237/dataCommun.o ../src/dataCommun.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1665200909/heap_1.o: ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1665200909" 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1665200909/heap_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1665200909/heap_1.o.d" -o ${OBJECTDIR}/_ext/1665200909/heap_1.o ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/951553248/port.o: ../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/951553248" 
	@${RM} ${OBJECTDIR}/_ext/951553248/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/951553248/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/951553248/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/951553248/port.o.d" -o ${OBJECTDIR}/_ext/951553248/port.o ../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/404212886/croutine.o: ../src/third_party/rtos/FreeRTOS/Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/404212886/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/404212886/croutine.o.d" -o ${OBJECTDIR}/_ext/404212886/croutine.o ../src/third_party/rtos/FreeRTOS/Source/croutine.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/404212886/list.o: ../src/third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/404212886/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/404212886/list.o.d" -o ${OBJECTDIR}/_ext/404212886/list.o ../src/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/404212886/queue.o: ../src/third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/404212886/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/404212886/queue.o.d" -o ${OBJECTDIR}/_ext/404212886/queue.o ../src/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o: ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d" -o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/404212886/timers.o: ../src/third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/404212886/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/404212886/timers.o.d" -o ${OBJECTDIR}/_ext/404212886/timers.o ../src/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/404212886/event_groups.o: ../src/third_party/rtos/FreeRTOS/Source/event_groups.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/404212886/event_groups.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/404212886/event_groups.o.d" -o ${OBJECTDIR}/_ext/404212886/event_groups.o ../src/third_party/rtos/FreeRTOS/Source/event_groups.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/404212886/stream_buffer.o: ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/404212886/stream_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/404212886/stream_buffer.o.d" -o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/659830161/MDB.o: ../src/MDB/MDB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659830161" 
	@${RM} ${OBJECTDIR}/_ext/659830161/MDB.o.d 
	@${RM} ${OBJECTDIR}/_ext/659830161/MDB.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659830161/MDB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/659830161/MDB.o.d" -o ${OBJECTDIR}/_ext/659830161/MDB.o ../src/MDB/MDB.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/659830161/MDB_CG.o: ../src/MDB/MDB_CG.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659830161" 
	@${RM} ${OBJECTDIR}/_ext/659830161/MDB_CG.o.d 
	@${RM} ${OBJECTDIR}/_ext/659830161/MDB_CG.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659830161/MDB_CG.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/659830161/MDB_CG.o.d" -o ${OBJECTDIR}/_ext/659830161/MDB_CG.o ../src/MDB/MDB_CG.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/659830161/MDB_BV.o: ../src/MDB/MDB_BV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659830161" 
	@${RM} ${OBJECTDIR}/_ext/659830161/MDB_BV.o.d 
	@${RM} ${OBJECTDIR}/_ext/659830161/MDB_BV.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659830161/MDB_BV.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/659830161/MDB_BV.o.d" -o ${OBJECTDIR}/_ext/659830161/MDB_BV.o ../src/MDB/MDB_BV.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1529399856/osal_freertos.o: ../src/config/default/osal/osal_freertos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1529399856" 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/1529399856/osal_freertos.o ../src/config/default/osal/osal_freertos.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/hd44780.o: ../src/hd44780.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/hd44780.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/hd44780.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/hd44780.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/hd44780.o.d" -o ${OBJECTDIR}/_ext/1360937237/hd44780.o ../src/hd44780.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/delay_us.o: ../src/delay_us.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/delay_us.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/delay_us.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/delay_us.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/delay_us.o.d" -o ${OBJECTDIR}/_ext/1360937237/delay_us.o ../src/delay_us.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/leds.o: ../src/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/leds.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/leds.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/leds.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/leds.o.d" -o ${OBJECTDIR}/_ext/1360937237/leds.o ../src/leds.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/DS18B20.o: ../src/DS18B20.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DS18B20.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DS18B20.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/DS18B20.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/DS18B20.o.d" -o ${OBJECTDIR}/_ext/1360937237/DS18B20.o ../src/DS18B20.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/contacts.o: ../src/contacts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/contacts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/contacts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/contacts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/contacts.o.d" -o ${OBJECTDIR}/_ext/1360937237/contacts.o ../src/contacts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/moteurs.o: ../src/moteurs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/moteurs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/moteurs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/moteurs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/moteurs.o.d" -o ${OBJECTDIR}/_ext/1360937237/moteurs.o ../src/moteurs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/mainboard2.o: ../src/mainboard2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mainboard2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mainboard2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/mainboard2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/mainboard2.o.d" -o ${OBJECTDIR}/_ext/1360937237/mainboard2.o ../src/mainboard2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
else
${OBJECTDIR}/_ext/897820976/drv_at24.o: ../src/config/default/driver/at24/src/drv_at24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/897820976" 
	@${RM} ${OBJECTDIR}/_ext/897820976/drv_at24.o.d 
	@${RM} ${OBJECTDIR}/_ext/897820976/drv_at24.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/897820976/drv_at24.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/897820976/drv_at24.o.d" -o ${OBJECTDIR}/_ext/897820976/drv_at24.o ../src/config/default/driver/at24/src/drv_at24.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/60169480/plib_i2c1.o: ../src/config/default/peripheral/i2c/plib_i2c1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/60169480" 
	@${RM} ${OBJECTDIR}/_ext/60169480/plib_i2c1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60169480/plib_i2c1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/60169480/plib_i2c1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/60169480/plib_i2c1.o.d" -o ${OBJECTDIR}/_ext/60169480/plib_i2c1.o ../src/config/default/peripheral/i2c/plib_i2c1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1865569570/plib_rcon.o: ../src/config/default/peripheral/rcon/plib_rcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1865569570" 
	@${RM} ${OBJECTDIR}/_ext/1865569570/plib_rcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865569570/plib_rcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1865569570/plib_rcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1865569570/plib_rcon.o.d" -o ${OBJECTDIR}/_ext/1865569570/plib_rcon.o ../src/config/default/peripheral/rcon/plib_rcon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1865657120/plib_uart3.o: ../src/config/default/peripheral/uart/plib_uart3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1865657120/plib_uart3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart3.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart3.o ../src/config/default/peripheral/uart/plib_uart3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1865657120/plib_uart1.o: ../src/config/default/peripheral/uart/plib_uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ../src/config/default/peripheral/uart/plib_uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/14461671/sys_dma.o: ../src/config/default/system/dma/sys_dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/14461671" 
	@${RM} ${OBJECTDIR}/_ext/14461671/sys_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/14461671/sys_dma.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/14461671/sys_dma.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/14461671/sys_dma.o.d" -o ${OBJECTDIR}/_ext/14461671/sys_dma.o ../src/config/default/system/dma/sys_dma.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1881668453/sys_int.o: ../src/config/default/system/int/src/sys_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1881668453" 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" -o ${OBJECTDIR}/_ext/1881668453/sys_int.o ../src/config/default/system/int/src/sys_int.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/initialization.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1171490990/freertos_hooks.o: ../src/config/default/freertos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1171490990/freertos_hooks.o.d" -o ${OBJECTDIR}/_ext/1171490990/freertos_hooks.o ../src/config/default/freertos_hooks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1171490990/tasks.o: ../src/config/default/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1171490990/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1171490990/tasks.o.d" -o ${OBJECTDIR}/_ext/1171490990/tasks.o ../src/config/default/tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/audits.o: ../src/audits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/audits.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/audits.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/audits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/audits.o.d" -o ${OBJECTDIR}/_ext/1360937237/audits.o ../src/audits.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/parameters.o: ../src/parameters.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/parameters.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/parameters.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/parameters.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/parameters.o.d" -o ${OBJECTDIR}/_ext/1360937237/parameters.o ../src/parameters.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/dataCommun.o: ../src/dataCommun.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dataCommun.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dataCommun.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/dataCommun.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/dataCommun.o.d" -o ${OBJECTDIR}/_ext/1360937237/dataCommun.o ../src/dataCommun.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1665200909/heap_1.o: ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1665200909" 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1665200909/heap_1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1665200909/heap_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1665200909/heap_1.o.d" -o ${OBJECTDIR}/_ext/1665200909/heap_1.o ../src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/951553248/port.o: ../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/951553248" 
	@${RM} ${OBJECTDIR}/_ext/951553248/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/951553248/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/951553248/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/951553248/port.o.d" -o ${OBJECTDIR}/_ext/951553248/port.o ../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/404212886/croutine.o: ../src/third_party/rtos/FreeRTOS/Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/404212886/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/404212886/croutine.o.d" -o ${OBJECTDIR}/_ext/404212886/croutine.o ../src/third_party/rtos/FreeRTOS/Source/croutine.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/404212886/list.o: ../src/third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/404212886/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/404212886/list.o.d" -o ${OBJECTDIR}/_ext/404212886/list.o ../src/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/404212886/queue.o: ../src/third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/404212886/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/404212886/queue.o.d" -o ${OBJECTDIR}/_ext/404212886/queue.o ../src/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o: ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o.d" -o ${OBJECTDIR}/_ext/404212886/FreeRTOS_tasks.o ../src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/404212886/timers.o: ../src/third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/404212886/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/404212886/timers.o.d" -o ${OBJECTDIR}/_ext/404212886/timers.o ../src/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/404212886/event_groups.o: ../src/third_party/rtos/FreeRTOS/Source/event_groups.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/event_groups.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/404212886/event_groups.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/404212886/event_groups.o.d" -o ${OBJECTDIR}/_ext/404212886/event_groups.o ../src/third_party/rtos/FreeRTOS/Source/event_groups.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/404212886/stream_buffer.o: ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/404212886" 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/404212886/stream_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/404212886/stream_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/404212886/stream_buffer.o.d" -o ${OBJECTDIR}/_ext/404212886/stream_buffer.o ../src/third_party/rtos/FreeRTOS/Source/stream_buffer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/659830161/MDB.o: ../src/MDB/MDB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659830161" 
	@${RM} ${OBJECTDIR}/_ext/659830161/MDB.o.d 
	@${RM} ${OBJECTDIR}/_ext/659830161/MDB.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659830161/MDB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/659830161/MDB.o.d" -o ${OBJECTDIR}/_ext/659830161/MDB.o ../src/MDB/MDB.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/659830161/MDB_CG.o: ../src/MDB/MDB_CG.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659830161" 
	@${RM} ${OBJECTDIR}/_ext/659830161/MDB_CG.o.d 
	@${RM} ${OBJECTDIR}/_ext/659830161/MDB_CG.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659830161/MDB_CG.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/659830161/MDB_CG.o.d" -o ${OBJECTDIR}/_ext/659830161/MDB_CG.o ../src/MDB/MDB_CG.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/659830161/MDB_BV.o: ../src/MDB/MDB_BV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659830161" 
	@${RM} ${OBJECTDIR}/_ext/659830161/MDB_BV.o.d 
	@${RM} ${OBJECTDIR}/_ext/659830161/MDB_BV.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659830161/MDB_BV.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/659830161/MDB_BV.o.d" -o ${OBJECTDIR}/_ext/659830161/MDB_BV.o ../src/MDB/MDB_BV.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1529399856/osal_freertos.o: ../src/config/default/osal/osal_freertos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1529399856" 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/1529399856/osal_freertos.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1529399856/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/1529399856/osal_freertos.o ../src/config/default/osal/osal_freertos.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/hd44780.o: ../src/hd44780.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/hd44780.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/hd44780.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/hd44780.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/hd44780.o.d" -o ${OBJECTDIR}/_ext/1360937237/hd44780.o ../src/hd44780.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/delay_us.o: ../src/delay_us.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/delay_us.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/delay_us.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/delay_us.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/delay_us.o.d" -o ${OBJECTDIR}/_ext/1360937237/delay_us.o ../src/delay_us.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/leds.o: ../src/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/leds.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/leds.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/leds.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/leds.o.d" -o ${OBJECTDIR}/_ext/1360937237/leds.o ../src/leds.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/DS18B20.o: ../src/DS18B20.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DS18B20.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DS18B20.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/DS18B20.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/DS18B20.o.d" -o ${OBJECTDIR}/_ext/1360937237/DS18B20.o ../src/DS18B20.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/contacts.o: ../src/contacts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/contacts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/contacts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/contacts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/contacts.o.d" -o ${OBJECTDIR}/_ext/1360937237/contacts.o ../src/contacts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/moteurs.o: ../src/moteurs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/moteurs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/moteurs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/moteurs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/moteurs.o.d" -o ${OBJECTDIR}/_ext/1360937237/moteurs.o ../src/moteurs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1360937237/mainboard2.o: ../src/mainboard2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mainboard2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mainboard2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/mainboard2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512L_DFP" -I"../src/mips" -I"../src/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../src/third_party/rtos/FreeRTOS/Source/include" -Wall -Waddress-attribute-use -MMD -MF "${OBJECTDIR}/_ext/1360937237/mainboard2.o.d" -o ${OBJECTDIR}/_ext/1360937237/mainboard2.o ../src/mainboard2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -fshort-enums -mdfp=${DFP_DIR}
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_REAL_ICE=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC0275F  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp=${DFP_DIR}
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp=${DFP_DIR}
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
