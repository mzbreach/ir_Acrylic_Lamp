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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/plsWork.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/plsWork.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=I2C_LCD.c IR_lib.c final_main.c LedStrip_lib.c asm_lib.s

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/I2C_LCD.o ${OBJECTDIR}/IR_lib.o ${OBJECTDIR}/final_main.o ${OBJECTDIR}/LedStrip_lib.o ${OBJECTDIR}/asm_lib.o
POSSIBLE_DEPFILES=${OBJECTDIR}/I2C_LCD.o.d ${OBJECTDIR}/IR_lib.o.d ${OBJECTDIR}/final_main.o.d ${OBJECTDIR}/LedStrip_lib.o.d ${OBJECTDIR}/asm_lib.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/I2C_LCD.o ${OBJECTDIR}/IR_lib.o ${OBJECTDIR}/final_main.o ${OBJECTDIR}/LedStrip_lib.o ${OBJECTDIR}/asm_lib.o

# Source Files
SOURCEFILES=I2C_LCD.c IR_lib.c final_main.c LedStrip_lib.c asm_lib.s



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/plsWork.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GA002
MP_LINKER_FILE_OPTION=,--script=p24FJ64GA002.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/I2C_LCD.o: I2C_LCD.c  .generated_files/flags/default/2a7d92f560bf863e661e0758f2205d7d074b6403 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C_LCD.o.d 
	@${RM} ${OBJECTDIR}/I2C_LCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2C_LCD.c  -o ${OBJECTDIR}/I2C_LCD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/I2C_LCD.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/IR_lib.o: IR_lib.c  .generated_files/flags/default/7748b050b6e5ab6243c8d1f32c25f57e43a7dc8c .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/IR_lib.o.d 
	@${RM} ${OBJECTDIR}/IR_lib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  IR_lib.c  -o ${OBJECTDIR}/IR_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/IR_lib.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/final_main.o: final_main.c  .generated_files/flags/default/d81fa9042ccf97d0d9a9ad22830998d2a44119ae .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/final_main.o.d 
	@${RM} ${OBJECTDIR}/final_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  final_main.c  -o ${OBJECTDIR}/final_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/final_main.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/LedStrip_lib.o: LedStrip_lib.c  .generated_files/flags/default/23533e7c2d11da66933463b05357434ad74b160 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LedStrip_lib.o.d 
	@${RM} ${OBJECTDIR}/LedStrip_lib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  LedStrip_lib.c  -o ${OBJECTDIR}/LedStrip_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/LedStrip_lib.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/I2C_LCD.o: I2C_LCD.c  .generated_files/flags/default/7a284d415eed39f5dc92045908104744e3b0a608 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C_LCD.o.d 
	@${RM} ${OBJECTDIR}/I2C_LCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2C_LCD.c  -o ${OBJECTDIR}/I2C_LCD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/I2C_LCD.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/IR_lib.o: IR_lib.c  .generated_files/flags/default/bf3145d7ac2722b9972442558f65b0e1a4d135b8 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/IR_lib.o.d 
	@${RM} ${OBJECTDIR}/IR_lib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  IR_lib.c  -o ${OBJECTDIR}/IR_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/IR_lib.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/final_main.o: final_main.c  .generated_files/flags/default/84e4149ffa70197aa9058df7170e46f8aac2a981 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/final_main.o.d 
	@${RM} ${OBJECTDIR}/final_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  final_main.c  -o ${OBJECTDIR}/final_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/final_main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/LedStrip_lib.o: LedStrip_lib.c  .generated_files/flags/default/2b848f822e4756fc32ac80b134c374d644bd601c .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LedStrip_lib.o.d 
	@${RM} ${OBJECTDIR}/LedStrip_lib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  LedStrip_lib.c  -o ${OBJECTDIR}/LedStrip_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/LedStrip_lib.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/asm_lib.o: asm_lib.s  .generated_files/flags/default/ac3a04097f00577d89d1ccb0c5d714afc5df1f6 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/asm_lib.o.d 
	@${RM} ${OBJECTDIR}/asm_lib.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  asm_lib.s  -o ${OBJECTDIR}/asm_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/asm_lib.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/asm_lib.o: asm_lib.s  .generated_files/flags/default/c6ac1fb714f7a79d244c18045f5a9ee7356b8b08 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/asm_lib.o.d 
	@${RM} ${OBJECTDIR}/asm_lib.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  asm_lib.s  -o ${OBJECTDIR}/asm_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/asm_lib.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/plsWork.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/plsWork.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/plsWork.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/plsWork.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/plsWork.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
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
