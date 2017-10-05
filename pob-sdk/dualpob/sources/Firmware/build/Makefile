###############################################################################
# Makefile for the project dualpob_firmware
###############################################################################

## General Flags
PROJECT = dualpob_firmware
MCU = atmega128
TARGET = dualpob_firmware.elf
CC = avr-gcc.exe

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -DF_CPU=16000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += 
LDFLAGS += -Wl,-section-start==0x800100


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0


## Include Directories
INCLUDES = -I"T:\project\dual_pob\libpob_atmel\include" 

## Library Directories
LIBDIRS = -L"T:\project\dual_pob\libpob_atmel" 

## Libraries
LIBS = -ldualpob 

## Objects that must be built in order to link
OBJECTS = main.o pobeye_command.o uart_command.o communication.o uart_test_program.o i2c_command.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) dualpob_firmware.hex dualpob_firmware.eep size

## Compile
main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

pobeye_command.o: ../pobeye_command.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart_command.o: ../uart_command.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

communication.o: ../communication.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart_test_program.o: ../uart_test_program.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

i2c_command.o: ../i2c_command.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) dualpob_firmware.elf dep/* dualpob_firmware.hex dualpob_firmware.eep

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

