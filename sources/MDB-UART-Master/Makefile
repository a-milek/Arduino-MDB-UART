# MDB-UART-Master — ATmega4808
# Requires: avr-gcc, avr-binutils, avrdude
# Programming interface: UPDI (e.g. serialupdi via USB-serial adapter)

TARGET  = MDB-UART-Master
MCU     = atmega4808
F_CPU   = 3333333UL

BUILD  ?= debug
BUILDDIR = build/$(BUILD)

# Local overrides (not committed): create local.mk to set TOOLCHAIN_PATH, PORT, etc.
-include local.mk

# Set TOOLCHAIN_PATH to override the toolchain (without trailing slash).
# Or put it in local.mk:
#   TOOLCHAIN_PATH = C:/Users/.../avr-gcc/7.3.0-atmel3.6.1-arduino7/bin
ifdef TOOLCHAIN_PATH
CC       = "$(TOOLCHAIN_PATH)/avr-gcc"
OBJCOPY  = "$(TOOLCHAIN_PATH)/avr-objcopy"
OBJDUMP  = "$(TOOLCHAIN_PATH)/avr-objdump"
SIZE     = "$(TOOLCHAIN_PATH)/avr-size"
else
CC       = avr-gcc
OBJCOPY  = avr-objcopy
OBJDUMP  = avr-objdump
SIZE     = avr-size
endif

SRCS = \
    main.c \
    BillValidator_M.c \
    Cashless_M.c \
    CoinChanger_M.c \
    CoinHopper_M.c \
    ExternalCmd_M.c \
    LEDControl_M.c \
    MDB_M.c \
    Settings_M.c \
    USART_M.c

OBJS = $(patsubst %.c,$(BUILDDIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

COMMON_FLAGS = \
    -mmcu=$(MCU) \
    -DF_CPU=$(F_CPU) \
    -std=c99 \
    -funsigned-char \
    -funsigned-bitfields \
    -fpack-struct \
    -fno-common \
    -Wall \
    -Wl,--relax

ifeq ($(BUILD),release)
CFLAGS = $(COMMON_FLAGS) -Os -DNDEBUG
else
CFLAGS = $(COMMON_FLAGS) -Os -g2 -DDEBUG
endif

LDFLAGS = -lm

# Flashing — ATmega4808 uses UPDI, not ISP
# Adjust PORT to your USB-serial adapter (e.g. COM3 or /dev/ttyUSB0)
PROGRAMMER = serialupdi
PORT       = COM3
AVRDUDE    = avrdude
AVRDUDE_FLAGS = -c $(PROGRAMMER) -p m4808 -P $(PORT)

# ── Targets ────────────────────────────────────────────────────────────────

.PHONY: all debug release flash flash-eep size clean compiledb

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

compiledb:
	python3 -m compiledb make --dry-run

clean:
	rm -rf build/

-include $(DEPS)
