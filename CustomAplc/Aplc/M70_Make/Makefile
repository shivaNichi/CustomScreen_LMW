# Makefile - Sample programs
#
# DESCRIPTION
# This file contains rules for building
#

# Path of application
APP_PATH	=	C:\lohith\projects\LMW\CustomAplc\Aplc

# Module name
OUTMODL		=	aplc.o

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
TGT_CPP	=	$(APP_PATH)/Cpp
TNGSCL 	=	$(TGT_CPP)/aplcmain.c


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
