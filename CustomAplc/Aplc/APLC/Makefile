# Makefile - Sample program
# DESCRIPTION
# This file contains rules for building

# Path of application
APP_PATH	=	E:\SVN\200NCC2\10_ÔOÓ‹\35_Source\20_Android_SpeedImproved\APLC\source

# Module name
OUTMODL		=	aplc.o

# Path of NC Designer include file
DESIGNER_PATH	=	$(APP_PATH)/include

# Definition of compiler option
CC		=	ccmips -EL -mips4 -mno-branch-likely -mcpu=vr5400
CC_OPTIM	=	-Os -funroll-loops -fno-strict-aliasing -fforce-addr
CC_COMPILER	=	-std=c9x -fasm -fno-rtti -pipe -c
CC_DEFINES	=	-DCPU=$(CPU) -DGCC960 -DVXWORKS54
LOCAL_DEFINE	=	-D_UNICODE -DUNICODE -DNC_TYPE_NX -DNO_WINDOWS -D_NCDVxWorks -DRW_MULTI_THREAD \
			-D_REENTRANT -D_INTERPRETER_ -DGCC960 -DUNDER_VXW -DNDEBUG
LOCAL_INCLUDE	=	-I$(DESIGNER_PATH)
C++_OPTION	=	-fno-for-scope -fno-builtin -fno-exceptions
CFLAGS		=	$(CC_OPTIM) \
			$(CC_COMPILER) $(CC_DEFINES) $(ADDED_CFLAGS) $(CC_INCLUDE) \
			$(LOCAL_DEFINE) $(LOCAL_INCLUDE) $(EXTRA_DEFINE) $(EXTRA_INCLUDE) 
C++FLAGS	=	$(CFLAGS) $(C++_OPTION)

#Definition of munch option
MUNCH_TCL	=	$(WIND_BASE)/host/src/hutils/munch.tcl
NM		=	nmmips -g
MAKE		=	ccmips -c -fdollars-in-identifiers -EL -mips4 -mno-branch-likely -G 0 \
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
EXTRA_DEFINE	=	-DSAMPLE

# Definition of link object
TGT_CPP	=	$(APP_PATH)/Cpp

TNGSCL 	=	$(TGT_CPP)/main_udp7.c

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