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
SOURCEFILES_QUOTED_IF_SPACED=I2C_LCD.c IR_lib.c final_main.c LedStrip_lib.c ../../asm_lib.s

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/I2C_LCD.o ${OBJECTDIR}/IR_lib.o ${OBJECTDIR}/final_main.o ${OBJECTDIR}/LedStrip_lib.o ${OBJECTDIR}/_ext/43898991/asm_lib.o
POSSIBLE_DEPFILES=${OBJECTDIR}/I2C_LCD.o.d ${OBJECTDIR}/IR_lib.o.d ${OBJECTDIR}/final_main.o.d ${OBJECTDIR}/LedStrip_lib.o.d ${OBJECTDIR}/_ext/43898991/asm_lib.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/I2C_LCD.o ${OBJECTDIR}/IR_lib.o ${OBJECTDIR}/final_main.o ${OBJECTDIR}/LedStrip_lib.o ${OBJECTDIR}/_ext/43898991/asm_lib.o

# Source Files
SOURCEFILES=I2C_LCD.c IR_lib.c final_main.c LedStrip_lib.c ../../asm_lib.s



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
${OBJECTDIR}/I2C_LCD.o: I2C_LCD.c  .generated_files/flags/default/3da3f2e9c08fd8788f7d894da433891deaa0aa49 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C_LCD.o.d 
	@${RM} ${OBJECTDIR}/I2C_LCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2C_LCD.c  -o ${OBJECTDIR}/I2C_LCD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/I2C_LCD.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/IR_lib.o: IR_lib.c  .generated_files/flags/default/a5bacfd2d9c32b484d4fb8b8c799f06885abc098 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/IR_lib.o.d 
	@${RM} ${OBJECTDIR}/IR_lib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  IR_lib.c  -o ${OBJECTDIR}/IR_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/IR_lib.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/final_main.o: final_main.c  .generated_files/flags/default/4a2a8afd66202746acd703df01e2f26ffc788532 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/final_main.o.d 
	@${RM} ${OBJECTDIR}/final_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  final_main.c  -o ${OBJECTDIR}/final_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/final_main.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/LedStrip_lib.o: LedStrip_lib.c  .generated_files/flags/default/c6e3fbdb02f7824a24530c7eec75293171763dec .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LedStrip_lib.o.d 
	@${RM} ${OBJECTDIR}/LedStrip_lib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  LedStrip_lib.c  -o ${OBJECTDIR}/LedStrip_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/LedStrip_lib.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/I2C_LCD.o: I2C_LCD.c  .generated_files/flags/default/8270e92408258e168852fa935a79f7529409fede .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C_LCD.o.d 
	@${RM} ${OBJECTDIR}/I2C_LCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2C_LCD.c  -o ${OBJECTDIR}/I2C_LCD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/I2C_LCD.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/IR_lib.o: IR_lib.c  .generated_files/flags/default/c862ef7dea479917564f553b74e5aa09bc6f37d8 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/IR_lib.o.d 
	@${RM} ${OBJECTDIR}/IR_lib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  IR_lib.c  -o ${OBJECTDIR}/IR_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/IR_lib.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/final_main.o: final_main.c  .generated_files/flags/default/1018878f52f713f6fe27efa898cf3ac710ff1a66 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/final_main.o.d 
	@${RM} ${OBJECTDIR}/final_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  final_main.c  -o ${OBJECTDIR}/final_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/final_main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/LedStrip_lib.o: LedStrip_lib.c  .generated_files/flags/default/7f1c54420a3ebda9968543d7338f34e532618209 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LedStrip_lib.o.d 
	@${RM} ${OBJECTDIR}/LedStrip_lib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  LedStrip_lib.c  -o ${OBJECTDIR}/LedStrip_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/LedStrip_lib.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/43898991/asm_lib.o: ../../asm_lib.s  .generated_files/flags/default/bcf1122c37292103c642851217399c0f53fc87c9 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}/_ext/43898991" 
	@${RM} ${OBJECTDIR}/_ext/43898991/asm_lib.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/asm_lib.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../asm_lib.s  -o ${OBJECTDIR}/_ext/43898991/asm_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/_ext/43898991/asm_lib.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/43898991/asm_lib.o: ../../asm_lib.s  .generated_files/flags/default/a92206983d861208ce6772ad941314fdefd9a3e .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}/_ext/43898991" 
	@${RM} ${OBJECTDIR}/_ext/43898991/asm_lib.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/asm_lib.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../asm_lib.s  -o ${OBJECTDIR}/_ext/43898991/asm_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/_ext/43898991/asm_lib.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
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
