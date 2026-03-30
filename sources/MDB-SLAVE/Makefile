# MDB-SLAVE — ATmega644P
# Requires: avr-gcc, avr-binutils, avrdude
# Programming interface: ISP (e.g. USBasp)

TARGET  = MDB-SLAVE
MCU     = atmega644p
# F_CPU is defined in source files as 16000000UL; override here if needed
F_CPU   = 16000000UL

BUILD  ?= debug
BUILDDIR = build/$(BUILD)

CC       = avr-gcc
OBJCOPY  = avr-objcopy
OBJDUMP  = avr-objdump
SIZE     = avr-size

SRCS = \
    main.c \
    BillValidator.c \
    Cashless.c \
    ExternalCmd.c \
    LEDControl.c \
    MDB.c \
    Settings.c \
    USART.c \
    USD.c \
    VMC.c

OBJS = $(patsubst %.c,$(BUILDDIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

COMMON_FLAGS = \
    -mmcu=$(MCU) \
    -DF_CPU=$(F_CPU) \
    -std=c99 \
    -funsigned-char \
    -funsigned-bitfields \
    -fpack-struct \
    -Wall

ifeq ($(BUILD),release)
CFLAGS = $(COMMON_FLAGS) -Os -DNDEBUG
else
CFLAGS = $(COMMON_FLAGS) -O1 -g2 -DDEBUG
endif

LDFLAGS = -lm

# Flashing — ATmega644P uses ISP
PROGRAMMER    = usbasp
AVRDUDE       = avrdude
AVRDUDE_FLAGS = -c $(PROGRAMMER) -p m644p

# Fuses for 16 MHz external crystal (verify against datasheet before burning)
LFUSE = 0xFF
HFUSE = 0x99
EFUSE = 0xFD

# ── Targets ────────────────────────────────────────────────────────────────

.PHONY: all debug release flash flash-eep fuses size clean

all: $(BUILDDIR)/$(TARGET).hex $(BUILDDIR)/$(TARGET).eep

debug:
	$(MAKE) BUILD=debug all

release:
	$(MAKE) BUILD=release all

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: %.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILDDIR)/$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/$(TARGET).hex: $(BUILDDIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(BUILDDIR)/$(TARGET).eep: $(BUILDDIR)/$(TARGET).elf
	$(OBJCOPY) -j .eeprom \
	    --set-section-flags=.eeprom=alloc,load \
	    --change-section-lma .eeprom=0 \
	    -O ihex $< $@ 2>/dev/null || touch $@

$(BUILDDIR)/$(TARGET).lss: $(BUILDDIR)/$(TARGET).elf
	$(OBJDUMP) -h -S $< > $@

size: $(BUILDDIR)/$(TARGET).elf
	$(SIZE) --format=avr --mcu=$(MCU) $<

flash: $(BUILDDIR)/$(TARGET).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$<:i

flash-eep: $(BUILDDIR)/$(TARGET).eep
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U eeprom:w:$<:i

fuses:
	$(AVRDUDE) $(AVRDUDE_FLAGS) \
	    -U lfuse:w:$(LFUSE):m \
	    -U hfuse:w:$(HFUSE):m \
	    -U efuse:w:$(EFUSE):m

clean:
	rm -rf build/

-include $(DEPS)
