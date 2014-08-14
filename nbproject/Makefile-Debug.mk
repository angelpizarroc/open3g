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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/source/comgt.o \
	${OBJECTDIR}/source/coninfo.o \
	${OBJECTDIR}/source/corebase.o \
	${OBJECTDIR}/source/main.o \
	${OBJECTDIR}/source/mainlog.o \
	${OBJECTDIR}/source/monitor.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/open3g_1

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/open3g_1: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/open3g_1 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/source/comgt.o: source/comgt.c 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/comgt.o source/comgt.c

${OBJECTDIR}/source/coninfo.o: source/coninfo.c 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/coninfo.o source/coninfo.c

${OBJECTDIR}/source/corebase.o: source/corebase.c 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/corebase.o source/corebase.c

${OBJECTDIR}/source/main.o: source/main.c 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/main.o source/main.c

${OBJECTDIR}/source/mainlog.o: source/mainlog.c 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/mainlog.o source/mainlog.c

${OBJECTDIR}/source/monitor.o: source/monitor.c 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/monitor.o source/monitor.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/open3g_1

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
