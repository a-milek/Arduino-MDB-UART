# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build System

Both projects use **GNU Make**. Build artifacts go into `build/debug/` or `build/release/` inside each project directory (not the old Atmel Studio `Debug/` folder). Requires `avr-gcc` and `avr-binutils` on PATH.

```sh
# From sources/ — build both projects
make              # debug build
make release      # release build
make clean        # clean all

# From sources/MDB-UART-Master/ or sources/MDB-SLAVE/
make              # debug build (default)
make release      # release (-Os, NDEBUG)
make size         # print memory usage
make flash        # flash via avrdude
make flash-eep    # flash EEPROM only
```

**MDB-UART-Master** (ATmega4808) uses UPDI programming — set `PORT` in the Makefile to your USB-serial adapter (e.g. `COM3`). Default programmer: `serialupdi`.

**MDB-SLAVE** (ATmega644P) uses ISP — default programmer: `usbasp`. Has a `make fuses` target for setting fuses (16 MHz external crystal).

The `.cproj` Atmel Studio files are kept for reference but are no longer the primary build mechanism.

## Project Structure

```
sources/
  MDB-SLAVE/          # Slave firmware — emulates MDB cashless/bill-validator peripheral
  MDB-UART-Master/    # Master firmware — acts as VMC (bus master), bridges to host PC
Compiled_firmware/    # Pre-built hex/eep images for ATmega644PA, ATmega1284P, ATmega2560
Docs/                 # MDB spec (MDB_version_4-2.pdf) and user manuals
PCB/                  # Sprint Layout 6.0 PCB files and schematics
```

## Architecture

### MDB Protocol
MDB is a 9-bit UART bus at 9600 baud. The 9th bit (`mode` bit) distinguishes address bytes (mode=1) from data bytes (mode=0). This is modeled as:
```c
typedef struct { unsigned char data; unsigned char mode; } MDB_Byte;
```
All MDB I/O uses this struct. The bus is half-duplex: master polls slaves, slaves respond with data or `ACK`/`NAK`/`RET`.

### UART Mapping
Both projects use two hardware UARTs:
- **USART1** → MDB bus (9-bit, 9600 baud, to/from payment peripherals)
- **USART0** → EXT/host UART (8-bit, 9600 baud, to/from host PC or upstream controller)

In the 4808 port, these are abstracted via macros in `USART_M_conf.h` (`MDB_USART`, `EXT_USART`).

### MDB-UART-Master (`sources/MDB-UART-Master/`)
Acts as the MDB bus master (VMC). Main loop in `main.c`:
1. `DispatchExternalCommand()` — parse commands arriving from host over EXT UART
2. `CountCycles()` — periodic timer: triggers tube-status poll every 666 cycles, extended diagnostics every 37 cycles
3. `DispatchCommandOrPoll()` — polls each device or dispatches a pending command:
   - Coin Changer (addr `0x0B`) via `CoinChanger_M.c`
   - Coin Hopper x2 (addr `0x5B`, `0x73`) via `CoinHopper_M.c`
   - Cashless Readers x2 (addr `0x10`, `0x60`) via `Cashless_M.c`
   - Bill Validator (addr `0x33`) via `BillValidator_M.c`
4. `DispatchDeviceLED()` — updates status LEDs based on `OfflinePollsCount`

Each device is tracked by a `mdbdevice` struct (`Status`, `OfflinePollsCount`). `Status == 0` means offline/not initialized.

External commands from the host arrive as ASCII strings terminated by `\r\n`. The parser lives in `ExternalCmd_M.c` / `EXTCMD_PROCESS()`. Command format uses `*` as delimiter (e.g., `DIAG*PING`, `WM*RVR*19.95*0`).

Settings (prices, device options) are stored in EEPROM and loaded at startup via `ReadSettings()` → `Settings_M.c`.

### MDB-SLAVE (`sources/MDB-SLAVE/`)
Emulates MDB slave devices (cashless reader, bill validator). Main loop:
1. `MDBCommandHandler()` — receives MDB frames from the bus master, dispatches by address:
   - `0x30` range → `HandleBillValidatorCommand()` in `BillValidator.c`
   - `0x10`/`0x60` range → `HandleCashlessCommand()` in `Cashless.c` (currently commented out)
2. `EXTCMD_PROCESS()` — handles commands from external host

Slave-side cashless protocol state machine lives in `Cashless.c` / `VMC.c`. Slave replies are built as `MDB_Byte` arrays and sent via `MDB_Send()`.

### Key Interfaces
- `MDB_Send(data[], len)` — send raw MDB frame (checksum appended automatically)
- `EXT_UART_Transmit_S(str)` / `EXT_UART_Transmit(buf)` — send text to host
- `PollDevice(addr)` — generic MDB poll: sends `addr` with mode=1, reads response
- `EXTCMD_PROCESS()` — parse and dispatch one complete external command

## Active Development Notes

- Current branch `atmega-4808-v2` is an in-progress port from ATmega1284/644/2560 to **ATmega 4808** (AVR-Dx series). The USART peripheral registers differ significantly (USART_M_conf.h abstracts this).
- MDB-SLAVE cashless support is ~90% written but untested against real hardware.
- `F_CPU` is passed via project config, not hardcoded (except in MDB-SLAVE files which still have `#ifndef F_CPU / #define F_CPU 16000000UL` guards).
- `.orig` files (e.g., `Cashless_M.c.orig`) are backup snapshots of pre-port code — not built.
