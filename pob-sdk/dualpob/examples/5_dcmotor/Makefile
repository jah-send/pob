# 
# Example makefile for the dual-pob board.
#
# (c) 2005-2008 POB-Technology. 

# You have only to modify EXE, SRC_FILES and POBLIB_PATH!

# Application's name
EXE=dcmotor

# File source list: Add your source!
SRC_FILES=main.c

# Path to the POB Library for dual-pob:
POBLIB_PATH=../../lib/

#### don't modify after this line! ####

# Temporary repertory
BUILD_PATH=.

# Source repertory
SRC_PATH=.

SOURCE_FILES =$(SRC_FILES)

# dual-pob CPU type
ATMEL_CPU=atmega128

# dual-pob CPU frequency
ATMEL_CPU_FRQ=16000000UL

# Project define
COMPILER_DEFINES= -DF_CPU=$(ATMEL_CPU_FRQ)

# Include search path
INCLUDE=-I$(POBLIB_PATH)/include/

# Use an external library
LIB_USE=-L"$(POBLIB_PATH)" -ldualpob

# Compiler
GCC=avr-gcc.exe

# Compiler options
COMPILER_OPTION=-Wall -gdwarf-2 -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -mmcu=$(ATMEL_CPU)

# Linker options
LINKER_OPTION=-mmcu=$(ATMEL_CPU) -Wl,-section-start==0x800100

# Hex file creation
HEX=avr-objcopy 
HEX_OPTIONS=-O ihex -R .eeprom  $(EXE).elf $(EXE).hex

## Compiler/linker macro:

# .c source macro:
COMPILER=$(GCC) $(COMPILER_OPTION) $(COMPILER_DEFINES) $(INCLUDE) -c

# .o linker macro:
LINKER=$(GCC) $(LINKER_OPTION) -o $(EXE).elf

# .o search path:
OBJ_FILES =$(patsubst %.c,$(BUILD_PATH)/%.o,$(SOURCE_FILES))

### Make target:

# build application
all:  $(OBJ_FILES)
	$(LINKER) $(OBJ_FILES) $(LIB_USE)
	$(HEX) $(HEX_OPTIONS)


# source search path:
vpath %.c  . $(SRC_PATH)

# building .o
$(BUILD_PATH)/%.o : %.c 
	$(COMPILER) -o $@ $<
	
clean:
	del /Q build\*.o 
	
##### END OF FILE