###############################################################################################
# Makefile for the project OpenDecoder22GBM (which adds RS-bus feedback)
# Modified by: AP (20-02-2011 / 10-01-2014)
# Note: FUSES settings for:
# 8535: avrdude -c USBasp -p atmega8535 -U lfuse:w:0x8e:m -U hfuse:w:0xd9:m
# 16A:  avrdude -c USBasp -p atmega16 -U lfuse:w:0xae:m -U hfuse:w:0xd9:m
# 32A:  avrdude -c USBasp -p atmega32 -U lfuse:w:0x8e:m -U hfuse:w:0xd9:m
# 644P: avrdude -c USBasp -p atmega644p -U lfuse:w:0xce:m -U hfuse:w:0xd9:m -U efuse:w:0xfe:m
# Note: select the lowest BODLEVEL (lowest brown-out voltage) the AVR supports
# Fuse settings according to http://www.engbedded.com/fusecalc/
###############################################################################################

## Project dependent Flags: select those matching your hardware
## ==== Flags for OpenDecoder22GBM ====
PROJECT = OPENDECODER22GBM
XTAL = 11059200
MCU = atmega16
## possible MCU values: atmega8535 atmega16 atmega32 atmega164a atmega324a atmega644p

## Other Flags
TARGET = OpenDecoder22GBM.elf
CC = avr-gcc
PROGRAMMER = -c USBasp
AVRDUDE = avrdude $(PROGRAMMER) -p $(MCU)

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -DF_CPU=$(XTAL) -DTARGET_HARDWARE=$(PROJECT) -Os
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=OpenDecoder22GBM.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = adc_hardware.o global.o lcd_ap.o lcd.o led.o occupancy.o rs_bus_hardware.o rs_bus_messages.o speed.o dcc_receiver.o cv_pom.o main.o timer1.o config.o dcc_decode.o relays.o myeeprom.o 

## Objects explicitly added by the user
LINKONLYOBJECTS =  

## Build
all: $(TARGET) OpenDecoder22GBM.hex OpenDecoder22GBM.eep OpenDecoder22GBM.lss size

## Compile
adc_hardware.o: adc_hardware.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

config.o: config.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

cv_pom.o: cv_pom.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

dcc_decode.o: dcc_decode.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

dcc_receiver.o: dcc_receiver.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

global.o: global.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

lcd.o: lcd.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

lcd_ap.o: lcd_ap.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

led.o: led.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

main.o: main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

myeeprom.o: myeeprom.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

occupancy.o: occupancy.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

relays.o: relays.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

rs_bus_hardware.o: rs_bus_hardware.c 
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

rs_bus_messages.o: rs_bus_messages.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

speed.o: speed.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

timer1.o: timer1.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) OpenDecoder22GBM.elf dep/* OpenDecoder22GBM.hex OpenDecoder22GBM.eep OpenDecoder22GBM.lss OpenDecoder22GBM.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

flash:	all
	$(AVRDUDE) -U flash:w:OpenDecoder22GBM.hex:i -U eeprom:w:OpenDecoder22GBM.eep:a

