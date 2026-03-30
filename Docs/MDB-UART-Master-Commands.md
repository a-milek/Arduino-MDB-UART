# MDB-UART-Master — Supported Commands

This document describes all MDB bus commands sent by the master firmware and all external UART commands accepted from the host PC.

---

## External UART Protocol

Commands are sent from the host PC to the master over the EXT UART (9600 8-N-1).

**Format:** `<top>*<sub>*[param1]*[param2]*...` followed by CR+LF
**All values are decimal ASCII integers.**

---

## 0 — System Reset

| Command | Description |
|---|---|
| `0*0` | Reset all MDB devices |
| `0*1` | Reset Coin Changer options (EEPROM) |
| `0*2` | Reset Bill Validator options (EEPROM) |
| `0*3` | Reset Coin Hopper options (EEPROM) |

---

## 1 — Coin Changer (MDB addr `0x08`)

| Command | Parameters | Description |
|---|---|---|
| `1*1` | — | Reset device (`MDB RESET`) |
| `1*2` | — | Read setup data, tube status, identification |
| `1*3` | `[acceptMask]` `[dispenseMask]` | Enable coin acceptance (16-bit masks, default `0xFFFF`) |
| `1*4` | — | Disable coin acceptance |
| `1*5` | `coinType` `qty` | Dispense coins (type 1–16, qty 1–15) |
| `1*6` | `value` | Alternative payout by value (8-bit) |
| `1*8` | `coinType` `enableAccept` `enableDispense` | Enable/disable individual coin type |
| `1*9` | `altPayout` `extDiag` `manualFill` | Configure features (each param: 0 or 1) |
| `1*10` | — | Get tube status |

### MDB Commands Issued
| Byte | Sub | Description |
|---|---|---|
| `0x0B` | — | POLL |
| `0x09` | — | SETUP — read feature level, currency, scaling, coin credits |
| `0x0A` | — | STATUS — read tube fill levels |
| `0x0C` | — | COIN TYPE — set accept/dispense enable masks |
| `0x0D` | — | DISPENSE — dispense coins (type in low nibble, qty in high nibble) |
| `0x0F` | `0x00` | EXPANSION ID — manufacturer code, serial, model, version |
| `0x0F` | `0x01` | EXPANSION FEATURE — configure alt payout / ext diag / manual fill |
| `0x0F` | `0x02` | EXPANSION PAYOUT — initiate alternative payout |
| `0x0F` | `0x03` | EXPANSION PAYOUT STATUS — poll payout status |
| `0x0F` | `0x04` | EXPANSION PAYOUT VALUE — get payout value |
| `0x0F` | `0x05` | EXPANSION DIAG — extended diagnostic (feature level ≥ 2) |
| `0x0F` | `0x06` | EXPANSION COIN TYPE — enable individual coin type |

---

## 2 — Bill Validator (MDB addr `0x30`)

| Command | Parameters | Description |
|---|---|---|
| `2*1` | — | Reset device (`MDB RESET`) |
| `2*2` | — | Read setup data |
| `2*3` | — | Enable bill acceptance (all types) |
| `2*4` | — | Disable bill acceptance |
| `2*5` | `action` | Escrow: `0` = return bill, `1` = stack bill |
| `2*6` | `billType` `qty` | Dispense bills by type and quantity |
| `2*7` | `value` | Dispense bills by value (16-bit) |
| `2*8` | `billType` `enableAccept` `enableEscrow` `enableRecycle` `enableManualDispense` `highSecurity` | Configure individual bill type |
| `2*9` | `recyclerEnable` | Configure features (recycler enable: 0 or 1) |
| `2*10` | — | Cancel payout |

### MDB Commands Issued
| Byte | Sub | Description |
|---|---|---|
| `0x33` | — | POLL |
| `0x31` | — | SETUP — feature level, currency, scaling, stacker capacity, escrow, security |
| `0x32` | — | SECURITY — set security levels for all bill types |
| `0x34` | — | BILL TYPE — set accept/escrow enable masks |
| `0x35` | — | ESCROW — stack (`0x01`) or return (`0x00`) escrowed bill |
| `0x36` | — | STACKER — get stacker capacity and fill count |
| `0x37` | `0x00` | EXPANSION ID — manufacturer code, serial, model, version |
| `0x37` | `0x01/0x02` | EXPANSION FEATURE — enable features (level dependent) |
| `0x37` | `0x03/0x05` | EXPANSION DISPENSER STATUS — get recycler dispenser status |
| `0x37` | `0x04` | EXPANSION RECYCLER — enable/disable recycler bill types |
| `0x37` | `0x06` | EXPANSION DISPENSE — dispense bills by type and count |
| `0x37` | `0x07` | EXPANSION DISPENSE VALUE — dispense by value |
| `0x37` | `0x08` | EXPANSION PAYOUT STATUS — payout in progress status |
| `0x37` | `0x09` | EXPANSION PAYOUT VALUE — amount dispensed so far |
| `0x37` | `0x0A` | EXPANSION CANCEL PAYOUT — cancel active payout |

---

## 3 — Coin Hoppers (MDB addrs `0x58` / `0x70`)

Hopper index is `1` or `2` (second parameter).

| Command | Parameters | Description |
|---|---|---|
| `3*1*1` | — | Reset hopper 1 |
| `3*2*1` | — | Reset hopper 2 |
| `3*1*2` | — | Read setup data and identification (hopper 1) |
| `3*2*2` | — | Read setup data and identification (hopper 2) |
| `3*1*6` | `coinType` `qty` | Dispense coins from hopper 1 |
| `3*2*6` | `coinType` `qty` | Dispense coins from hopper 2 |
| `3*1*7` | `value` | Dispense by value from hopper 1 (16-bit) |
| `3*2*7` | `value` | Dispense by value from hopper 2 (16-bit) |
| `3*1*8` | `coinType` `enable` | Enable/disable manual dispense coin type (hopper 1) |
| `3*2*8` | `coinType` `enable` | Enable/disable manual dispense coin type (hopper 2) |

### MDB Commands Issued
Addresses: hopper 1 = `0x58`, hopper 2 = `0x70`. Poll bytes: `0x5B` / `0x7B`.

| Byte | Sub | Description |
|---|---|---|
| `0x5B`/`0x7B` | — | POLL |
| `0x59`/`0x71` | — | SETUP — feature level, currency, scaling, coin credits |
| `0x5A`/`0x72` | — | ID — manufacturer code, serial, model, version |
| `0x5C`/`0x74` | — | COIN TYPE — enable manual dispense mask |
| `0x5D`/`0x75` | `0x00` | DISPENSE COINS — by type and count |
| `0x5D`/`0x75` | `0x01` | DISPENSE VALUE — by value |
| `0x5E`/`0x76` | `0x00` | DISPENSER STATUS — get dispenser status |
| `0x5E`/`0x76` | `0x01` | PAYOUT VALUE — amount dispensed |
| `0x5F`/`0x77` | `0x00` | PAYOUT STATUS — payout in progress status |

---

## 9 — Cashless Reader Diagnostics (MDB addrs `0x10` / `0x60`)

These commands target cashless reader **index 0** (`0x10`).

| Command | Parameters | Description |
|---|---|---|
| `9*1` | — | PING — responds `DIAG*PING` |
| `9*2` | — | Full cashless init sequence (setup → prices → expansion ID → opt features → EDC enable) |
| `9*3` | `price` `itemNumber` | Vend request (price as decimal, e.g. `19.95`) |
| `9*4` | `itemNumber` | Vend success |
| `9*5` | — | Session complete |
| `9*6` | — | Reader reset |
| `9*7` | `cmd` | EDC command (raw value) |
| `9*8` | — | Vend failure |
| `9*9` | `price` `itemNumber` | Cash sale |
| `9*10` | — | Vend cancel |

### MDB Commands Issued
| Byte | Sub | Description |
|---|---|---|
| `0x12`/`0x62` | — | POLL |
| `0x11`/`0x61` | — | SETUP — VMC config data + min/max price |
| `0x13`/`0x63` | `0x00` | VEND REQUEST — item price and number |
| `0x13`/`0x63` | `0x01` | VEND CANCEL |
| `0x13`/`0x63` | `0x02` | VEND SUCCESS — actual vend amount |
| `0x13`/`0x63` | `0x03` | VEND FAILURE |
| `0x13`/`0x63` | `0x04` | SESSION COMPLETE |
| `0x13`/`0x63` | `0x06` | NEGATIVE VEND REQUEST |
| `0x14`/`0x64` | `0x00` | READER DISABLE |
| `0x14`/`0x64` | `0x01` | READER ENABLE |
| `0x14`/`0x64` | `0x02` | READER CANCEL |
| `0x14`/`0x64` | `0x03` | DATA ENTRY RESPONSE — 8-byte key data |
| `0x15`/`0x65` | `0x00` | REVALUE REQUEST — add funds |
| `0x15`/`0x65` | `0x01` | REVALUE LIMIT REQUEST |
| `0x17`/`0x67` | `0x00` | EXPANSION REQUEST ID — peripheral identification |
| `0x17`/`0x67` | `0x03` | EXPANSION WRITE TIME/DATE — 10-byte BCD datetime |
| `0x17`/`0x67` | `0x04` | EXPANSION ENABLE OPTIONS — optional feature flags |

---

## 10 — System

| Command | Parameters | Description |
|---|---|---|
| `10*1` | — | System PING — responds `SYS*PING*OK` |
| `10*99` | — | Software reset (ATmega4808 `RSTCTRL`) |

---

## Automatic Polling Schedule

The master polls all online devices in every main loop iteration (~100 ms cycle):

| Device | Poll address | Periodic task |
|---|---|---|
| Coin Changer | `0x0B` | Tube status every 666 cycles; extended diag every 37 cycles |
| Bill Validator | `0x33` | Stacker + dispenser status every 666 cycles |
| Coin Hopper 1 | `0x5B` | Dispenser status every 666 cycles |
| Coin Hopper 2 | `0x7B` | Dispenser status every 666 cycles |
| Cashless Reader 1 | `0x12` | Every cycle |
| Cashless Reader 2 | `0x62` | Every cycle |

A device is considered **offline** when its `OfflinePollsCount` reaches zero. Its status LED turns off and it is excluded from non-poll commands until it responds again.
