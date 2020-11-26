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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FWH.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FWH.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../src/mdb/MDB.c ../src/mdb/MDB_BV.c ../src/mdb/MDB_CG.c ../src/mdb/mdb_cl.c ../src/system_config/default/framework/driver/flash/src/drv_flash_static.c ../src/system_config/default/framework/driver/usart/src/drv_usart_mapping.c ../src/system_config/default/framework/driver/usart/src/drv_usart_static.c ../src/system_config/default/framework/driver/usart/src/drv_usart_static_byte_model.c ../src/system_config/default/framework/osal/src/osal_freertos.c ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c ../src/system_config/default/framework/system/devcon/src/sys_devcon.c ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c ../src/system_config/default/framework/system/int/src/sys_int_pic32.c ../src/system_config/default/framework/system/ports/src/sys_ports_static.c ../src/system_config/default/framework/system/reset/src/sys_reset.c ../src/system_config/default/FreeRTOS/portable/MemMang/heap_1.c ../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX/port.c ../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.S ../src/system_config/default/FreeRTOS/croutine.c ../src/system_config/default/FreeRTOS/list.c ../src/system_config/default/FreeRTOS/queue.c ../src/system_config/default/FreeRTOS/tasks.c ../src/system_config/default/FreeRTOS/timers.c ../src/system_config/default/FreeRTOS/event_groups.c ../src/system_config/default/FreeRTOS/stream_buffer.c ../src/system_config/default/system_init.c ../src/system_config/default/system_interrupt.c ../src/system_config/default/filtering_exception_handler.c ../src/system_config/default/general-exception-context.S ../src/system_config/default/fassert.c ../src/system_config/default/system_tasks.c ../src/system_config/default/system_interrupt_a.S ../src/system_config/default/rtos_hooks.c ../src/main.c ../src/contacts.c ../src/delay_us.c ../src/hd44780.c ../src/moteurs.c ../src/parameters.c ../src/trap_security.c ../src/audits.c ../src/leds.c ../src/DS18B20.c ../src/dataCommun.c ../src/mainboard.c ../src/eeprom.c ../src/product.c ../src/modemGSM.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/659861937/MDB.o ${OBJECTDIR}/_ext/659861937/MDB_BV.o ${OBJECTDIR}/_ext/659861937/MDB_CG.o ${OBJECTDIR}/_ext/659861937/mdb_cl.o ${OBJECTDIR}/_ext/1923177420/drv_flash_static.o ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o ${OBJECTDIR}/_ext/327000265/drv_usart_static.o ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o ${OBJECTDIR}/_ext/485267206/osal_freertos.o ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mx.o ${OBJECTDIR}/_ext/340578644/sys_devcon.o ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/1735427962/sys_int_pic32.o ${OBJECTDIR}/_ext/822048611/sys_ports_static.o ${OBJECTDIR}/_ext/68765530/sys_reset.o ${OBJECTDIR}/_ext/542287462/heap_1.o ${OBJECTDIR}/_ext/1836182099/port.o ${OBJECTDIR}/_ext/1836182099/port_asm.o ${OBJECTDIR}/_ext/1606280809/croutine.o ${OBJECTDIR}/_ext/1606280809/list.o ${OBJECTDIR}/_ext/1606280809/queue.o ${OBJECTDIR}/_ext/1606280809/tasks.o ${OBJECTDIR}/_ext/1606280809/timers.o ${OBJECTDIR}/_ext/1606280809/event_groups.o ${OBJECTDIR}/_ext/1606280809/stream_buffer.o ${OBJECTDIR}/_ext/1688732426/system_init.o ${OBJECTDIR}/_ext/1688732426/system_interrupt.o ${OBJECTDIR}/_ext/1688732426/filtering_exception_handler.o ${OBJECTDIR}/_ext/1688732426/general-exception-context.o ${OBJECTDIR}/_ext/1688732426/fassert.o ${OBJECTDIR}/_ext/1688732426/system_tasks.o ${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o ${OBJECTDIR}/_ext/1688732426/rtos_hooks.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/contacts.o ${OBJECTDIR}/_ext/1360937237/delay_us.o ${OBJECTDIR}/_ext/1360937237/hd44780.o ${OBJECTDIR}/_ext/1360937237/moteurs.o ${OBJECTDIR}/_ext/1360937237/parameters.o ${OBJECTDIR}/_ext/1360937237/trap_security.o ${OBJECTDIR}/_ext/1360937237/audits.o ${OBJECTDIR}/_ext/1360937237/leds.o ${OBJECTDIR}/_ext/1360937237/DS18B20.o ${OBJECTDIR}/_ext/1360937237/dataCommun.o ${OBJECTDIR}/_ext/1360937237/mainboard.o ${OBJECTDIR}/_ext/1360937237/eeprom.o ${OBJECTDIR}/_ext/1360937237/product.o ${OBJECTDIR}/_ext/1360937237/modemGSM.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/659861937/MDB.o.d ${OBJECTDIR}/_ext/659861937/MDB_BV.o.d ${OBJECTDIR}/_ext/659861937/MDB_CG.o.d ${OBJECTDIR}/_ext/659861937/mdb_cl.o.d ${OBJECTDIR}/_ext/1923177420/drv_flash_static.o.d ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o.d ${OBJECTDIR}/_ext/327000265/drv_usart_static.o.d ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o.d ${OBJECTDIR}/_ext/485267206/osal_freertos.o.d ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mx.o.d ${OBJECTDIR}/_ext/340578644/sys_devcon.o.d ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mx.o.d ${OBJECTDIR}/_ext/1735427962/sys_int_pic32.o.d ${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d ${OBJECTDIR}/_ext/68765530/sys_reset.o.d ${OBJECTDIR}/_ext/542287462/heap_1.o.d ${OBJECTDIR}/_ext/1836182099/port.o.d ${OBJECTDIR}/_ext/1836182099/port_asm.o.d ${OBJECTDIR}/_ext/1606280809/croutine.o.d ${OBJECTDIR}/_ext/1606280809/list.o.d ${OBJECTDIR}/_ext/1606280809/queue.o.d ${OBJECTDIR}/_ext/1606280809/tasks.o.d ${OBJECTDIR}/_ext/1606280809/timers.o.d ${OBJECTDIR}/_ext/1606280809/event_groups.o.d ${OBJECTDIR}/_ext/1606280809/stream_buffer.o.d ${OBJECTDIR}/_ext/1688732426/system_init.o.d ${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d ${OBJECTDIR}/_ext/1688732426/filtering_exception_handler.o.d ${OBJECTDIR}/_ext/1688732426/general-exception-context.o.d ${OBJECTDIR}/_ext/1688732426/fassert.o.d ${OBJECTDIR}/_ext/1688732426/system_tasks.o.d ${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o.d ${OBJECTDIR}/_ext/1688732426/rtos_hooks.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/contacts.o.d ${OBJECTDIR}/_ext/1360937237/delay_us.o.d ${OBJECTDIR}/_ext/1360937237/hd44780.o.d ${OBJECTDIR}/_ext/1360937237/moteurs.o.d ${OBJECTDIR}/_ext/1360937237/parameters.o.d ${OBJECTDIR}/_ext/1360937237/trap_security.o.d ${OBJECTDIR}/_ext/1360937237/audits.o.d ${OBJECTDIR}/_ext/1360937237/leds.o.d ${OBJECTDIR}/_ext/1360937237/DS18B20.o.d ${OBJECTDIR}/_ext/1360937237/dataCommun.o.d ${OBJECTDIR}/_ext/1360937237/mainboard.o.d ${OBJECTDIR}/_ext/1360937237/eeprom.o.d ${OBJECTDIR}/_ext/1360937237/product.o.d ${OBJECTDIR}/_ext/1360937237/modemGSM.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/659861937/MDB.o ${OBJECTDIR}/_ext/659861937/MDB_BV.o ${OBJECTDIR}/_ext/659861937/MDB_CG.o ${OBJECTDIR}/_ext/659861937/mdb_cl.o ${OBJECTDIR}/_ext/1923177420/drv_flash_static.o ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o ${OBJECTDIR}/_ext/327000265/drv_usart_static.o ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o ${OBJECTDIR}/_ext/485267206/osal_freertos.o ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mx.o ${OBJECTDIR}/_ext/340578644/sys_devcon.o ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/1735427962/sys_int_pic32.o ${OBJECTDIR}/_ext/822048611/sys_ports_static.o ${OBJECTDIR}/_ext/68765530/sys_reset.o ${OBJECTDIR}/_ext/542287462/heap_1.o ${OBJECTDIR}/_ext/1836182099/port.o ${OBJECTDIR}/_ext/1836182099/port_asm.o ${OBJECTDIR}/_ext/1606280809/croutine.o ${OBJECTDIR}/_ext/1606280809/list.o ${OBJECTDIR}/_ext/1606280809/queue.o ${OBJECTDIR}/_ext/1606280809/tasks.o ${OBJECTDIR}/_ext/1606280809/timers.o ${OBJECTDIR}/_ext/1606280809/event_groups.o ${OBJECTDIR}/_ext/1606280809/stream_buffer.o ${OBJECTDIR}/_ext/1688732426/system_init.o ${OBJECTDIR}/_ext/1688732426/system_interrupt.o ${OBJECTDIR}/_ext/1688732426/filtering_exception_handler.o ${OBJECTDIR}/_ext/1688732426/general-exception-context.o ${OBJECTDIR}/_ext/1688732426/fassert.o ${OBJECTDIR}/_ext/1688732426/system_tasks.o ${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o ${OBJECTDIR}/_ext/1688732426/rtos_hooks.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/contacts.o ${OBJECTDIR}/_ext/1360937237/delay_us.o ${OBJECTDIR}/_ext/1360937237/hd44780.o ${OBJECTDIR}/_ext/1360937237/moteurs.o ${OBJECTDIR}/_ext/1360937237/parameters.o ${OBJECTDIR}/_ext/1360937237/trap_security.o ${OBJECTDIR}/_ext/1360937237/audits.o ${OBJECTDIR}/_ext/1360937237/leds.o ${OBJECTDIR}/_ext/1360937237/DS18B20.o ${OBJECTDIR}/_ext/1360937237/dataCommun.o ${OBJECTDIR}/_ext/1360937237/mainboard.o ${OBJECTDIR}/_ext/1360937237/eeprom.o ${OBJECTDIR}/_ext/1360937237/product.o ${OBJECTDIR}/_ext/1360937237/modemGSM.o

# Source Files
SOURCEFILES=../src/mdb/MDB.c ../src/mdb/MDB_BV.c ../src/mdb/MDB_CG.c ../src/mdb/mdb_cl.c ../src/system_config/default/framework/driver/flash/src/drv_flash_static.c ../src/system_config/default/framework/driver/usart/src/drv_usart_mapping.c ../src/system_config/default/framework/driver/usart/src/drv_usart_static.c ../src/system_config/default/framework/driver/usart/src/drv_usart_static_byte_model.c ../src/system_config/default/framework/osal/src/osal_freertos.c ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c ../src/system_config/default/framework/system/devcon/src/sys_devcon.c ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c ../src/system_config/default/framework/system/int/src/sys_int_pic32.c ../src/system_config/default/framework/system/ports/src/sys_ports_static.c ../src/system_config/default/framework/system/reset/src/sys_reset.c ../src/system_config/default/FreeRTOS/portable/MemMang/heap_1.c ../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX/port.c ../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.S ../src/system_config/default/FreeRTOS/croutine.c ../src/system_config/default/FreeRTOS/list.c ../src/system_config/default/FreeRTOS/queue.c ../src/system_config/default/FreeRTOS/tasks.c ../src/system_config/default/FreeRTOS/timers.c ../src/system_config/default/FreeRTOS/event_groups.c ../src/system_config/default/FreeRTOS/stream_buffer.c ../src/system_config/default/system_init.c ../src/system_config/default/system_interrupt.c ../src/system_config/default/filtering_exception_handler.c ../src/system_config/default/general-exception-context.S ../src/system_config/default/fassert.c ../src/system_config/default/system_tasks.c ../src/system_config/default/system_interrupt_a.S ../src/system_config/default/rtos_hooks.c ../src/main.c ../src/contacts.c ../src/delay_us.c ../src/hd44780.c ../src/moteurs.c ../src/parameters.c ../src/trap_security.c ../src/audits.c ../src/leds.c ../src/DS18B20.c ../src/dataCommun.c ../src/mainboard.c ../src/eeprom.c ../src/product.c ../src/modemGSM.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/FWH.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX575F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1836182099/port_asm.o: ../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1836182099" 
	@${RM} ${OBJECTDIR}/_ext/1836182099/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1836182099/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1836182099/port_asm.o.ok ${OBJECTDIR}/_ext/1836182099/port_asm.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -I"../src/system_config/default" -MMD -MF "${OBJECTDIR}/_ext/1836182099/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1836182099/port_asm.o ../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1836182099/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,-I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -I"../src/system_config/default" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1836182099/port_asm.o.d" "${OBJECTDIR}/_ext/1836182099/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/general-exception-context.o: ../src/system_config/default/general-exception-context.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/general-exception-context.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/general-exception-context.o 
	@${RM} ${OBJECTDIR}/_ext/1688732426/general-exception-context.o.ok ${OBJECTDIR}/_ext/1688732426/general-exception-context.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -I"../src/system_config/default" -MMD -MF "${OBJECTDIR}/_ext/1688732426/general-exception-context.o.d"  -o ${OBJECTDIR}/_ext/1688732426/general-exception-context.o ../src/system_config/default/general-exception-context.S  -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1688732426/general-exception-context.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,-I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -I"../src/system_config/default" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/general-exception-context.o.d" "${OBJECTDIR}/_ext/1688732426/general-exception-context.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o: ../src/system_config/default/system_interrupt_a.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o.ok ${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -I"../src/system_config/default" -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o.d"  -o ${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o ../src/system_config/default/system_interrupt_a.S  -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,-I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -I"../src/system_config/default" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o.d" "${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1836182099/port_asm.o: ../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1836182099" 
	@${RM} ${OBJECTDIR}/_ext/1836182099/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1836182099/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1836182099/port_asm.o.ok ${OBJECTDIR}/_ext/1836182099/port_asm.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -I"../src/system_config/default" -MMD -MF "${OBJECTDIR}/_ext/1836182099/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1836182099/port_asm.o ../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1836182099/port_asm.o.asm.d",--gdwarf-2,-I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -I"../src/system_config/default" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1836182099/port_asm.o.d" "${OBJECTDIR}/_ext/1836182099/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/general-exception-context.o: ../src/system_config/default/general-exception-context.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/general-exception-context.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/general-exception-context.o 
	@${RM} ${OBJECTDIR}/_ext/1688732426/general-exception-context.o.ok ${OBJECTDIR}/_ext/1688732426/general-exception-context.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -I"../src/system_config/default" -MMD -MF "${OBJECTDIR}/_ext/1688732426/general-exception-context.o.d"  -o ${OBJECTDIR}/_ext/1688732426/general-exception-context.o ../src/system_config/default/general-exception-context.S  -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1688732426/general-exception-context.o.asm.d",--gdwarf-2,-I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -I"../src/system_config/default" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/general-exception-context.o.d" "${OBJECTDIR}/_ext/1688732426/general-exception-context.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o: ../src/system_config/default/system_interrupt_a.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o.ok ${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -I"../src/system_config/default" -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o.d"  -o ${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o ../src/system_config/default/system_interrupt_a.S  -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o.asm.d",--gdwarf-2,-I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -I"../src/system_config/default" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o.d" "${OBJECTDIR}/_ext/1688732426/system_interrupt_a.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/659861937/MDB.o: ../src/mdb/MDB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659861937" 
	@${RM} ${OBJECTDIR}/_ext/659861937/MDB.o.d 
	@${RM} ${OBJECTDIR}/_ext/659861937/MDB.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/659861937/MDB.o.d" -o ${OBJECTDIR}/_ext/659861937/MDB.o ../src/mdb/MDB.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/659861937/MDB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/659861937/MDB_BV.o: ../src/mdb/MDB_BV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659861937" 
	@${RM} ${OBJECTDIR}/_ext/659861937/MDB_BV.o.d 
	@${RM} ${OBJECTDIR}/_ext/659861937/MDB_BV.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/659861937/MDB_BV.o.d" -o ${OBJECTDIR}/_ext/659861937/MDB_BV.o ../src/mdb/MDB_BV.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/659861937/MDB_BV.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/659861937/MDB_CG.o: ../src/mdb/MDB_CG.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659861937" 
	@${RM} ${OBJECTDIR}/_ext/659861937/MDB_CG.o.d 
	@${RM} ${OBJECTDIR}/_ext/659861937/MDB_CG.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/659861937/MDB_CG.o.d" -o ${OBJECTDIR}/_ext/659861937/MDB_CG.o ../src/mdb/MDB_CG.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/659861937/MDB_CG.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/659861937/mdb_cl.o: ../src/mdb/mdb_cl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659861937" 
	@${RM} ${OBJECTDIR}/_ext/659861937/mdb_cl.o.d 
	@${RM} ${OBJECTDIR}/_ext/659861937/mdb_cl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/659861937/mdb_cl.o.d" -o ${OBJECTDIR}/_ext/659861937/mdb_cl.o ../src/mdb/mdb_cl.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/659861937/mdb_cl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1923177420/drv_flash_static.o: ../src/system_config/default/framework/driver/flash/src/drv_flash_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1923177420" 
	@${RM} ${OBJECTDIR}/_ext/1923177420/drv_flash_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1923177420/drv_flash_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1923177420/drv_flash_static.o.d" -o ${OBJECTDIR}/_ext/1923177420/drv_flash_static.o ../src/system_config/default/framework/driver/flash/src/drv_flash_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1923177420/drv_flash_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o: ../src/system_config/default/framework/driver/usart/src/drv_usart_mapping.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/327000265" 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o.d" -o ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o ../src/system_config/default/framework/driver/usart/src/drv_usart_mapping.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/327000265/drv_usart_static.o: ../src/system_config/default/framework/driver/usart/src/drv_usart_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/327000265" 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/327000265/drv_usart_static.o.d" -o ${OBJECTDIR}/_ext/327000265/drv_usart_static.o ../src/system_config/default/framework/driver/usart/src/drv_usart_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/327000265/drv_usart_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o: ../src/system_config/default/framework/driver/usart/src/drv_usart_static_byte_model.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/327000265" 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o.d 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o.d" -o ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o ../src/system_config/default/framework/driver/usart/src/drv_usart_static_byte_model.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/485267206/osal_freertos.o: ../src/system_config/default/framework/osal/src/osal_freertos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/485267206" 
	@${RM} ${OBJECTDIR}/_ext/485267206/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/485267206/osal_freertos.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/485267206/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/485267206/osal_freertos.o ../src/system_config/default/framework/osal/src/osal_freertos.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/485267206/osal_freertos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/639803181/sys_clk_pic32mx.o: ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/639803181" 
	@${RM} ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/639803181/sys_clk_pic32mx.o.d" -o ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mx.o ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/639803181/sys_clk_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/340578644/sys_devcon.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/340578644/sys_devcon.o ../src/system_config/default/framework/system/devcon/src/sys_devcon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/340578644/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mx.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mx.o ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1735427962/sys_int_pic32.o: ../src/system_config/default/framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1735427962" 
	@${RM} ${OBJECTDIR}/_ext/1735427962/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1735427962/sys_int_pic32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1735427962/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1735427962/sys_int_pic32.o ../src/system_config/default/framework/system/int/src/sys_int_pic32.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1735427962/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/822048611/sys_ports_static.o: ../src/system_config/default/framework/system/ports/src/sys_ports_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/822048611" 
	@${RM} ${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/822048611/sys_ports_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/822048611/sys_ports_static.o ../src/system_config/default/framework/system/ports/src/sys_ports_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/68765530/sys_reset.o: ../src/system_config/default/framework/system/reset/src/sys_reset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/68765530" 
	@${RM} ${OBJECTDIR}/_ext/68765530/sys_reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/68765530/sys_reset.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/68765530/sys_reset.o.d" -o ${OBJECTDIR}/_ext/68765530/sys_reset.o ../src/system_config/default/framework/system/reset/src/sys_reset.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/68765530/sys_reset.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/542287462/heap_1.o: ../src/system_config/default/FreeRTOS/portable/MemMang/heap_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/542287462" 
	@${RM} ${OBJECTDIR}/_ext/542287462/heap_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/542287462/heap_1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/542287462/heap_1.o.d" -o ${OBJECTDIR}/_ext/542287462/heap_1.o ../src/system_config/default/FreeRTOS/portable/MemMang/heap_1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/542287462/heap_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1836182099/port.o: ../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1836182099" 
	@${RM} ${OBJECTDIR}/_ext/1836182099/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1836182099/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1836182099/port.o.d" -o ${OBJECTDIR}/_ext/1836182099/port.o ../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX/port.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1836182099/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1606280809/croutine.o: ../src/system_config/default/FreeRTOS/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1606280809" 
	@${RM} ${OBJECTDIR}/_ext/1606280809/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1606280809/croutine.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1606280809/croutine.o.d" -o ${OBJECTDIR}/_ext/1606280809/croutine.o ../src/system_config/default/FreeRTOS/croutine.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1606280809/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1606280809/list.o: ../src/system_config/default/FreeRTOS/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1606280809" 
	@${RM} ${OBJECTDIR}/_ext/1606280809/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1606280809/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1606280809/list.o.d" -o ${OBJECTDIR}/_ext/1606280809/list.o ../src/system_config/default/FreeRTOS/list.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1606280809/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1606280809/queue.o: ../src/system_config/default/FreeRTOS/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1606280809" 
	@${RM} ${OBJECTDIR}/_ext/1606280809/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1606280809/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1606280809/queue.o.d" -o ${OBJECTDIR}/_ext/1606280809/queue.o ../src/system_config/default/FreeRTOS/queue.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1606280809/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1606280809/tasks.o: ../src/system_config/default/FreeRTOS/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1606280809" 
	@${RM} ${OBJECTDIR}/_ext/1606280809/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1606280809/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1606280809/tasks.o.d" -o ${OBJECTDIR}/_ext/1606280809/tasks.o ../src/system_config/default/FreeRTOS/tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1606280809/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1606280809/timers.o: ../src/system_config/default/FreeRTOS/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1606280809" 
	@${RM} ${OBJECTDIR}/_ext/1606280809/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1606280809/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1606280809/timers.o.d" -o ${OBJECTDIR}/_ext/1606280809/timers.o ../src/system_config/default/FreeRTOS/timers.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1606280809/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1606280809/event_groups.o: ../src/system_config/default/FreeRTOS/event_groups.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1606280809" 
	@${RM} ${OBJECTDIR}/_ext/1606280809/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/1606280809/event_groups.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1606280809/event_groups.o.d" -o ${OBJECTDIR}/_ext/1606280809/event_groups.o ../src/system_config/default/FreeRTOS/event_groups.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1606280809/event_groups.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1606280809/stream_buffer.o: ../src/system_config/default/FreeRTOS/stream_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1606280809" 
	@${RM} ${OBJECTDIR}/_ext/1606280809/stream_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1606280809/stream_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1606280809/stream_buffer.o.d" -o ${OBJECTDIR}/_ext/1606280809/stream_buffer.o ../src/system_config/default/FreeRTOS/stream_buffer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1606280809/stream_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/system_init.o: ../src/system_config/default/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_init.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_init.o ../src/system_config/default/system_init.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/system_interrupt.o: ../src/system_config/default/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_interrupt.o ../src/system_config/default/system_interrupt.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/filtering_exception_handler.o: ../src/system_config/default/filtering_exception_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/filtering_exception_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/filtering_exception_handler.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1688732426/filtering_exception_handler.o.d" -o ${OBJECTDIR}/_ext/1688732426/filtering_exception_handler.o ../src/system_config/default/filtering_exception_handler.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/filtering_exception_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/fassert.o: ../src/system_config/default/fassert.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/fassert.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/fassert.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1688732426/fassert.o.d" -o ${OBJECTDIR}/_ext/1688732426/fassert.o ../src/system_config/default/fassert.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/fassert.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/system_tasks.o: ../src/system_config/default/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_tasks.o ../src/system_config/default/system_tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/rtos_hooks.o: ../src/system_config/default/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/rtos_hooks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1688732426/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1688732426/rtos_hooks.o ../src/system_config/default/rtos_hooks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/contacts.o: ../src/contacts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/contacts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/contacts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/contacts.o.d" -o ${OBJECTDIR}/_ext/1360937237/contacts.o ../src/contacts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/contacts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/delay_us.o: ../src/delay_us.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/delay_us.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/delay_us.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/delay_us.o.d" -o ${OBJECTDIR}/_ext/1360937237/delay_us.o ../src/delay_us.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/delay_us.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/hd44780.o: ../src/hd44780.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/hd44780.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/hd44780.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/hd44780.o.d" -o ${OBJECTDIR}/_ext/1360937237/hd44780.o ../src/hd44780.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/hd44780.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/moteurs.o: ../src/moteurs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/moteurs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/moteurs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/moteurs.o.d" -o ${OBJECTDIR}/_ext/1360937237/moteurs.o ../src/moteurs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/moteurs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/parameters.o: ../src/parameters.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/parameters.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/parameters.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/parameters.o.d" -o ${OBJECTDIR}/_ext/1360937237/parameters.o ../src/parameters.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/parameters.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/trap_security.o: ../src/trap_security.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/trap_security.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/trap_security.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/trap_security.o.d" -o ${OBJECTDIR}/_ext/1360937237/trap_security.o ../src/trap_security.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/trap_security.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/audits.o: ../src/audits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/audits.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/audits.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/audits.o.d" -o ${OBJECTDIR}/_ext/1360937237/audits.o ../src/audits.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/audits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/leds.o: ../src/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/leds.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/leds.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/leds.o.d" -o ${OBJECTDIR}/_ext/1360937237/leds.o ../src/leds.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/leds.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/DS18B20.o: ../src/DS18B20.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DS18B20.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DS18B20.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/DS18B20.o.d" -o ${OBJECTDIR}/_ext/1360937237/DS18B20.o ../src/DS18B20.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/DS18B20.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/dataCommun.o: ../src/dataCommun.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dataCommun.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dataCommun.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/dataCommun.o.d" -o ${OBJECTDIR}/_ext/1360937237/dataCommun.o ../src/dataCommun.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/dataCommun.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/mainboard.o: ../src/mainboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mainboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mainboard.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/mainboard.o.d" -o ${OBJECTDIR}/_ext/1360937237/mainboard.o ../src/mainboard.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/mainboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/eeprom.o: ../src/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/eeprom.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/eeprom.o.d" -o ${OBJECTDIR}/_ext/1360937237/eeprom.o ../src/eeprom.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/product.o: ../src/product.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/product.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/product.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/product.o.d" -o ${OBJECTDIR}/_ext/1360937237/product.o ../src/product.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/product.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/modemGSM.o: ../src/modemGSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modemGSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modemGSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/modemGSM.o.d" -o ${OBJECTDIR}/_ext/1360937237/modemGSM.o ../src/modemGSM.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/modemGSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/659861937/MDB.o: ../src/mdb/MDB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659861937" 
	@${RM} ${OBJECTDIR}/_ext/659861937/MDB.o.d 
	@${RM} ${OBJECTDIR}/_ext/659861937/MDB.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/659861937/MDB.o.d" -o ${OBJECTDIR}/_ext/659861937/MDB.o ../src/mdb/MDB.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/659861937/MDB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/659861937/MDB_BV.o: ../src/mdb/MDB_BV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659861937" 
	@${RM} ${OBJECTDIR}/_ext/659861937/MDB_BV.o.d 
	@${RM} ${OBJECTDIR}/_ext/659861937/MDB_BV.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/659861937/MDB_BV.o.d" -o ${OBJECTDIR}/_ext/659861937/MDB_BV.o ../src/mdb/MDB_BV.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/659861937/MDB_BV.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/659861937/MDB_CG.o: ../src/mdb/MDB_CG.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659861937" 
	@${RM} ${OBJECTDIR}/_ext/659861937/MDB_CG.o.d 
	@${RM} ${OBJECTDIR}/_ext/659861937/MDB_CG.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/659861937/MDB_CG.o.d" -o ${OBJECTDIR}/_ext/659861937/MDB_CG.o ../src/mdb/MDB_CG.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/659861937/MDB_CG.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/659861937/mdb_cl.o: ../src/mdb/mdb_cl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659861937" 
	@${RM} ${OBJECTDIR}/_ext/659861937/mdb_cl.o.d 
	@${RM} ${OBJECTDIR}/_ext/659861937/mdb_cl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/659861937/mdb_cl.o.d" -o ${OBJECTDIR}/_ext/659861937/mdb_cl.o ../src/mdb/mdb_cl.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/659861937/mdb_cl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1923177420/drv_flash_static.o: ../src/system_config/default/framework/driver/flash/src/drv_flash_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1923177420" 
	@${RM} ${OBJECTDIR}/_ext/1923177420/drv_flash_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1923177420/drv_flash_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1923177420/drv_flash_static.o.d" -o ${OBJECTDIR}/_ext/1923177420/drv_flash_static.o ../src/system_config/default/framework/driver/flash/src/drv_flash_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1923177420/drv_flash_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o: ../src/system_config/default/framework/driver/usart/src/drv_usart_mapping.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/327000265" 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o.d" -o ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o ../src/system_config/default/framework/driver/usart/src/drv_usart_mapping.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/327000265/drv_usart_static.o: ../src/system_config/default/framework/driver/usart/src/drv_usart_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/327000265" 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/327000265/drv_usart_static.o.d" -o ${OBJECTDIR}/_ext/327000265/drv_usart_static.o ../src/system_config/default/framework/driver/usart/src/drv_usart_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/327000265/drv_usart_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o: ../src/system_config/default/framework/driver/usart/src/drv_usart_static_byte_model.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/327000265" 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o.d 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o.d" -o ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o ../src/system_config/default/framework/driver/usart/src/drv_usart_static_byte_model.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/485267206/osal_freertos.o: ../src/system_config/default/framework/osal/src/osal_freertos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/485267206" 
	@${RM} ${OBJECTDIR}/_ext/485267206/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/485267206/osal_freertos.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/485267206/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/485267206/osal_freertos.o ../src/system_config/default/framework/osal/src/osal_freertos.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/485267206/osal_freertos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/639803181/sys_clk_pic32mx.o: ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/639803181" 
	@${RM} ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/639803181/sys_clk_pic32mx.o.d" -o ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mx.o ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/639803181/sys_clk_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/340578644/sys_devcon.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/340578644/sys_devcon.o ../src/system_config/default/framework/system/devcon/src/sys_devcon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/340578644/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mx.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mx.o ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1735427962/sys_int_pic32.o: ../src/system_config/default/framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1735427962" 
	@${RM} ${OBJECTDIR}/_ext/1735427962/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1735427962/sys_int_pic32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1735427962/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1735427962/sys_int_pic32.o ../src/system_config/default/framework/system/int/src/sys_int_pic32.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1735427962/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/822048611/sys_ports_static.o: ../src/system_config/default/framework/system/ports/src/sys_ports_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/822048611" 
	@${RM} ${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/822048611/sys_ports_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/822048611/sys_ports_static.o ../src/system_config/default/framework/system/ports/src/sys_ports_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/68765530/sys_reset.o: ../src/system_config/default/framework/system/reset/src/sys_reset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/68765530" 
	@${RM} ${OBJECTDIR}/_ext/68765530/sys_reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/68765530/sys_reset.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/68765530/sys_reset.o.d" -o ${OBJECTDIR}/_ext/68765530/sys_reset.o ../src/system_config/default/framework/system/reset/src/sys_reset.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/68765530/sys_reset.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/542287462/heap_1.o: ../src/system_config/default/FreeRTOS/portable/MemMang/heap_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/542287462" 
	@${RM} ${OBJECTDIR}/_ext/542287462/heap_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/542287462/heap_1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/542287462/heap_1.o.d" -o ${OBJECTDIR}/_ext/542287462/heap_1.o ../src/system_config/default/FreeRTOS/portable/MemMang/heap_1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/542287462/heap_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1836182099/port.o: ../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1836182099" 
	@${RM} ${OBJECTDIR}/_ext/1836182099/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1836182099/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1836182099/port.o.d" -o ${OBJECTDIR}/_ext/1836182099/port.o ../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX/port.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1836182099/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1606280809/croutine.o: ../src/system_config/default/FreeRTOS/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1606280809" 
	@${RM} ${OBJECTDIR}/_ext/1606280809/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1606280809/croutine.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1606280809/croutine.o.d" -o ${OBJECTDIR}/_ext/1606280809/croutine.o ../src/system_config/default/FreeRTOS/croutine.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1606280809/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1606280809/list.o: ../src/system_config/default/FreeRTOS/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1606280809" 
	@${RM} ${OBJECTDIR}/_ext/1606280809/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1606280809/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1606280809/list.o.d" -o ${OBJECTDIR}/_ext/1606280809/list.o ../src/system_config/default/FreeRTOS/list.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1606280809/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1606280809/queue.o: ../src/system_config/default/FreeRTOS/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1606280809" 
	@${RM} ${OBJECTDIR}/_ext/1606280809/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1606280809/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1606280809/queue.o.d" -o ${OBJECTDIR}/_ext/1606280809/queue.o ../src/system_config/default/FreeRTOS/queue.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1606280809/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1606280809/tasks.o: ../src/system_config/default/FreeRTOS/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1606280809" 
	@${RM} ${OBJECTDIR}/_ext/1606280809/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1606280809/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1606280809/tasks.o.d" -o ${OBJECTDIR}/_ext/1606280809/tasks.o ../src/system_config/default/FreeRTOS/tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1606280809/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1606280809/timers.o: ../src/system_config/default/FreeRTOS/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1606280809" 
	@${RM} ${OBJECTDIR}/_ext/1606280809/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1606280809/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1606280809/timers.o.d" -o ${OBJECTDIR}/_ext/1606280809/timers.o ../src/system_config/default/FreeRTOS/timers.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1606280809/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1606280809/event_groups.o: ../src/system_config/default/FreeRTOS/event_groups.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1606280809" 
	@${RM} ${OBJECTDIR}/_ext/1606280809/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/1606280809/event_groups.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1606280809/event_groups.o.d" -o ${OBJECTDIR}/_ext/1606280809/event_groups.o ../src/system_config/default/FreeRTOS/event_groups.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1606280809/event_groups.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1606280809/stream_buffer.o: ../src/system_config/default/FreeRTOS/stream_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1606280809" 
	@${RM} ${OBJECTDIR}/_ext/1606280809/stream_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1606280809/stream_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1606280809/stream_buffer.o.d" -o ${OBJECTDIR}/_ext/1606280809/stream_buffer.o ../src/system_config/default/FreeRTOS/stream_buffer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1606280809/stream_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/system_init.o: ../src/system_config/default/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_init.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_init.o ../src/system_config/default/system_init.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/system_interrupt.o: ../src/system_config/default/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_interrupt.o ../src/system_config/default/system_interrupt.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/filtering_exception_handler.o: ../src/system_config/default/filtering_exception_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/filtering_exception_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/filtering_exception_handler.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1688732426/filtering_exception_handler.o.d" -o ${OBJECTDIR}/_ext/1688732426/filtering_exception_handler.o ../src/system_config/default/filtering_exception_handler.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/filtering_exception_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/fassert.o: ../src/system_config/default/fassert.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/fassert.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/fassert.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1688732426/fassert.o.d" -o ${OBJECTDIR}/_ext/1688732426/fassert.o ../src/system_config/default/fassert.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/fassert.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/system_tasks.o: ../src/system_config/default/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_tasks.o ../src/system_config/default/system_tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1688732426/rtos_hooks.o: ../src/system_config/default/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/rtos_hooks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1688732426/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1688732426/rtos_hooks.o ../src/system_config/default/rtos_hooks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688732426/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/contacts.o: ../src/contacts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/contacts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/contacts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/contacts.o.d" -o ${OBJECTDIR}/_ext/1360937237/contacts.o ../src/contacts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/contacts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/delay_us.o: ../src/delay_us.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/delay_us.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/delay_us.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/delay_us.o.d" -o ${OBJECTDIR}/_ext/1360937237/delay_us.o ../src/delay_us.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/delay_us.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/hd44780.o: ../src/hd44780.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/hd44780.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/hd44780.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/hd44780.o.d" -o ${OBJECTDIR}/_ext/1360937237/hd44780.o ../src/hd44780.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/hd44780.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/moteurs.o: ../src/moteurs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/moteurs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/moteurs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/moteurs.o.d" -o ${OBJECTDIR}/_ext/1360937237/moteurs.o ../src/moteurs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/moteurs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/parameters.o: ../src/parameters.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/parameters.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/parameters.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/parameters.o.d" -o ${OBJECTDIR}/_ext/1360937237/parameters.o ../src/parameters.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/parameters.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/trap_security.o: ../src/trap_security.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/trap_security.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/trap_security.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/trap_security.o.d" -o ${OBJECTDIR}/_ext/1360937237/trap_security.o ../src/trap_security.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/trap_security.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/audits.o: ../src/audits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/audits.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/audits.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/audits.o.d" -o ${OBJECTDIR}/_ext/1360937237/audits.o ../src/audits.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/audits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/leds.o: ../src/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/leds.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/leds.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/leds.o.d" -o ${OBJECTDIR}/_ext/1360937237/leds.o ../src/leds.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/leds.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/DS18B20.o: ../src/DS18B20.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DS18B20.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DS18B20.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/DS18B20.o.d" -o ${OBJECTDIR}/_ext/1360937237/DS18B20.o ../src/DS18B20.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/DS18B20.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/dataCommun.o: ../src/dataCommun.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dataCommun.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dataCommun.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/dataCommun.o.d" -o ${OBJECTDIR}/_ext/1360937237/dataCommun.o ../src/dataCommun.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/dataCommun.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/mainboard.o: ../src/mainboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mainboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mainboard.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/mainboard.o.d" -o ${OBJECTDIR}/_ext/1360937237/mainboard.o ../src/mainboard.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/mainboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/eeprom.o: ../src/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/eeprom.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/eeprom.o.d" -o ${OBJECTDIR}/_ext/1360937237/eeprom.o ../src/eeprom.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/product.o: ../src/product.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/product.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/product.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/product.o.d" -o ${OBJECTDIR}/_ext/1360937237/product.o ../src/product.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/product.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/modemGSM.o: ../src/modemGSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modemGSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modemGSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -D_XC -D__XC -I"." -I".." -I"../src/system_config/default/" -I"../../../../../../../Microchip/Harmony/v2_06/framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../src/system_config/default/framework" -I"../src/system_config/default/FreeRTOS" -I"../src/system_config/default/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1360937237/modemGSM.o.d" -o ${OBJECTDIR}/_ext/1360937237/modemGSM.o ../src/modemGSM.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/modemGSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/FWH.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../src/system_config/default/bin/framework/peripheral/PIC32MX575F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/FWH.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\src\system_config\default\bin\framework\peripheral\PIC32MX575F512L_peripherals.a      -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/FWH.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../src/system_config/default/bin/framework/peripheral/PIC32MX575F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/FWH.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\src\system_config\default\bin\framework\peripheral\PIC32MX575F512L_peripherals.a      -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/FWH.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
