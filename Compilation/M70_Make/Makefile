# Makefile - Sample programs
#
# DESCRIPTION
# This file contains rules for building
#

# Path of application
APP_PATH	=	C:\lohith\projects\LMW\Compilation

# Module name
OUTMODL		=	LMW.o

# Definition of compiler option
CC		=	ccmips -EL -mips3 -mno-branch-likely -G 0
CC_OPTIM	=	-O2 -funroll-loops -fno-strict-aliasing -fforce-addr
CC_COMPILER	=	-std=c9x -pipe -c -fasm -fno-rtti
CC_DEFINES	=	-DCPU=$(CPU) -DTOOL=gnule -DMIPSEL -DGCC960 -DVXWORKS54
LOCAL_DEFINE	=	-D_UNICODE -DUNICODE -DNC_TYPE_NX -DNO_WINDOWS -D_NCDVxWorks -DRW_MULTI_THREAD \
					-D_REENTRANT -D_INTERPRETER_ -DGCC960 -DUNDER_VXW -DNDEBUG
# Path of NC Designer include file
LOCAL_INCLUDE	=	-IC:/MELCNC/NCD2/M8/include_VxW \
					-IC:/MELCNC/NCD2/M8/include
C++_OPTION	=	-fno-for-scope -fno-builtin -fno-exceptions
CFLAGS		=	$(CC_OPTIM) \
				$(CC_COMPILER) $(CC_DEFINES) $(ADDED_CFLAGS) $(CC_INCLUDE) \
				$(LOCAL_DEFINE) $(LOCAL_INCLUDE) $(EXTRA_DEFINE) $(EXTRA_INCLUDE) 
C++FLAGS	=	$(CFLAGS) $(C++_OPTION)

# Definition of munch option
MUNCH_TCL	=	$(WIND_BASE)/host/src/hutils/munch.tcl
NM			=	nmmips -g
MAKE		=	ccmips -c -fdollars-in-identifiers -EL -mips3 -mno-branch-likely -G 0 \
				-ansi -DRW_MULTI_THREAD -D_REENTRANT -fno-exceptions -fno-rtti -fno-for-scope \
				-fno-builtin -O0 -funroll-loops -DMIPSEL -I. -I$(VXWORKS)/target/h \
				-DCPU=$(CPU) -D_VXWORKS -D_POSIX

# Definition of linker option
LD	=	ldmips -EL
LD_PARTIAL_FLAGS	=	-n -X -r

# Other definitions
RM	=	vxrm

# Peculiar header file path to the application
EXTRA_INCLUDE	=	-I$(APP_PATH)/Cpp

# Peculiar constant to application
EXTRA_DEFINE	= -DNCDSSample

# Definition of link object
TGT_CPP		=	$(APP_PATH)/Cpp
TNGSCL 		=	$(TGT_CPP)/GCALARMHIST.cxx\
			$(TGT_CPP)/GCATC_ARM_Sys.cxx\
			$(TGT_CPP)/GCATC_Info.cxx\
			$(TGT_CPP)/GCATC_MAG_Sys.cxx\
			$(TGT_CPP)/GCCAUTIONSCREEN.cxx\
			$(TGT_CPP)/GCChip_CONVY_Sys.cxx\
			$(TGT_CPP)/GCCONFIRM_WINDOW.cxx\
			$(TGT_CPP)/GCCoolant_Sys.cxx\
			$(TGT_CPP)/GCEOS.cxx\
			$(TGT_CPP)/GCGCODE.cxx\
			$(TGT_CPP)/GCHydraulic_Sys.cxx\
			$(TGT_CPP)/GCINITSCREEN.cxx\
			$(TGT_CPP)/GCINOUTL.cxx \
			$(TGT_CPP)/GCINOUTXY.cxx \
			$(TGT_CPP)/GCLMW.cxx \
			$(TGT_CPP)/GCLOGOSCREEN.cxx \
			$(TGT_CPP)/GCLubrication_Sys.cxx \
			$(TGT_CPP)/GCMAINSCREEN.cxx\
			$(TGT_CPP)/GCMaint_Home.cxx\
			$(TGT_CPP)/GCMCODE.cxx\
			$(TGT_CPP)/GCMTB_AXIS.cxx\
			$(TGT_CPP)/GCMTB_PASSWORD.cxx\
			$(TGT_CPP)/GCMTB_SPORIENTATION.cxx\
			$(TGT_CPP)/GCMTB_SPSPEED.cxx \
			$(TGT_CPP)/GCMTB_SYSINFO.cxx \
			$(TGT_CPP)/GCPower_Calc.cxx\
			$(TGT_CPP)/GCPower_Calc2.cxx\
			$(TGT_CPP)/GCPreventive_Maint.cxx\
			$(TGT_CPP)/GCSampleScreen.cxx\
			$(TGT_CPP)/GCSPINDLE_Status.cxx\
			$(TGT_CPP)/GCSUB_SysInfo.cxx\
			$(TGT_CPP)/GResource.c\
			$(TGT_CPP)/GLoc_Locale0.c
			

TEMP1		=	$(TNGSCL:%.c=%.o)
TEMP2		=	$(TEMP1:%.cpp=%.o)
LINK_OBJ	=	$(TEMP2:%.cxx=%.o)

$(OUTMODL) : $(LINK_OBJ)
	$(RM) $(OUTMODL) ctdt.o
	$(NM) $(LINK_OBJ) | wtxtcl $(MUNCH_TCL) -asm mips > ctdt.c
	$(MAKE) ctdt.c -o ctdt.o
	$(LD) $(LD_PARTIAL_FLAGS) -o $@ $(LINK_OBJ) ctdt.o

# Rule of suffix
.SUFFIXES : .c .cpp .cxx .o

.c.o :
	$(RM) $@
	$(CC) $(CFLAGS) $< -o $@

.cpp.o :
	$(RM) $@
	$(CC) $(C++FLAGS) $< -o $@

.cxx.o :
	$(RM) $@
	$(CC) $(C++FLAGS) $< -o $@
