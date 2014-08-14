#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1062337698/comgt.o \
	${OBJECTDIR}/_ext/1062337698/coninfo.o \
	${OBJECTDIR}/_ext/1062337698/corebase.o \
	${OBJECTDIR}/_ext/1062337698/main.o \
	${OBJECTDIR}/_ext/1062337698/mainlog.o \
	${OBJECTDIR}/_ext/1062337698/monitor.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/open3g

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/open3g: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/open3g ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1062337698/comgt.o: ../open3g/./source/comgt.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1062337698
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1062337698/comgt.o ../open3g/./source/comgt.c

${OBJECTDIR}/_ext/1062337698/coninfo.o: ../open3g/./source/coninfo.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1062337698
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1062337698/coninfo.o ../open3g/./source/coninfo.c

${OBJECTDIR}/_ext/1062337698/corebase.o: ../open3g/./source/corebase.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1062337698
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1062337698/corebase.o ../open3g/./source/corebase.c

${OBJECTDIR}/_ext/1062337698/main.o: ../open3g/./source/main.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1062337698
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1062337698/main.o ../open3g/./source/main.c

${OBJECTDIR}/_ext/1062337698/mainlog.o: ../open3g/./source/mainlog.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1062337698
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1062337698/mainlog.o ../open3g/./source/mainlog.c

${OBJECTDIR}/_ext/1062337698/monitor.o: ../open3g/./source/monitor.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1062337698
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1062337698/monitor.o ../open3g/./source/monitor.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/open3g

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
