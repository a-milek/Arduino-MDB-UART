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

---
---

# Responses (Firmware → Host)

All responses are ASCII strings terminated by `\r\n`. Multi-field responses use `*` as delimiter. Generic suffixes: `OK`, `NAK` (MDB negative-ack), `FAIL` (no MDB response / timeout).

---

## System Responses (SYS*)

| Response | Trigger | Description |
|---|---|---|
| `SYS*MDBSTART*<version>` | Power-on / reset | Firmware started, version string follows |
| `SYS*PING*OK` | Command `10*1` | System ping reply |
| `SYS*RESET*OK` | Command `10*99` | Software reset initiated |
| `SYS*VMCSET*READ*OK` | Startup | VMC settings loaded from EEPROM |
| `SYS*CDSET*READ*OK` | Startup | Cashless price settings loaded |
| `SYS*CCSET*READ*OK` | Startup | Coin changer options loaded |
| `SYS*CCSET*SAVE*OK` | Settings write | Coin changer options saved |
| `SYS*CCSET*RESET*OK` | Command `0*1` | Coin changer options reset to defaults |
| `SYS*BVSET*READ*OK` | Startup | Bill validator options loaded |
| `SYS*BVSET*SAVE*OK` | Settings write | Bill validator options saved |
| `SYS*BVSET*RESET*OK` | Command `0*2` | Bill validator options reset to defaults |
| `SYS*CHSET*READ*OK` | Startup | Coin hopper options loaded |
| `SYS*CHSET*SAVE*OK` | Settings write | Coin hopper options saved |
| `SYS*CHSET*RESET*OK` | Command `0*3` | Coin hopper options reset to defaults |

---

## Coin Changer Responses (CC*)

### Configuration & Identification

| Response | Description |
|---|---|
| `CC*CFG*<featureLevel>*<countryCode>*<minCoinValue>` | Setup data (feature level, ISO country, smallest coin value as formatted string) |
| `CC*COINSUP*<type>*<value>*<acceptEn>*<dispenseEn>` | Supported coin type (per tube-routable type) |
| `CC*ID*<mfg>*<serial>*<model>*<swVer>*<altPay>*<extDiag>*<manualFill>*<FTL>` | Device identification |
| `CC*CFGERR` | Setup data request failed |

### Tube Status

| Response | Description |
|---|---|
| `CC*TUBE*<type>*<value>*<count>*<full>` | Tube fill level (count=coins, full=0/1) |
| `CC*TUBE*<type>*<value>*<count>*<full>*ERR` | Tube reports full but count is 0 |
| `CC*TUBESTATREQ*OK` | Tube status request complete |
| `CC*TUBESTATREQ*FAIL` | Tube status request failed |

### Poll Events

| Response | Description |
|---|---|
| `CC*DEPOSIT*<type>*<value>*<route>*<tubeCount>` | Coin accepted (route: `CASHBOX`, `TUBE`, `NA`, `REJECT`) |
| `CC*MANUALDISP*<type>*<value>*<dispensed>*<tubeCount>` | Coins manually dispensed |
| `CC*SLUG*<count>` | Slug(s) detected |
| `CC*STATUS*JUSTRESET` | Device reset, firmware re-initializes |
| `CC*STATUS*ESCROWREQ` | Escrow lever activated |
| `CC*STATUS*PAYOUTBUSY` | Payout in progress |
| `CC*STATUS*NOCREDIT` | No credit |
| `CC*STATUS*BADTUBESENSOR` | Defective tube sensor |
| `CC*STATUS*DOUBLECOIN` | Double coin arrival |
| `CC*STATUS*UNPLUGGED` | Device disconnected |
| `CC*STATUS*TUBEJAM` | Tube jam |
| `CC*STATUS*ROMERROR` | ROM checksum error |
| `CC*STATUS*ROUTERROR` | Coin routing error |
| `CC*STATUS*BUSY` | Device busy |
| `CC*STATUS*COINJAM` | Coin jam |
| `CC*STATUS*FISHING` | Coin fishing attempt |

### Command Responses

| Response | Description |
|---|---|
| `CC*ENABLE*OK` / `CC*ENABLE*FAIL` | Enable coin acceptance |
| `CC*DISABLE*OK` / `CC*DISABLE*FAIL` | Disable coin acceptance |
| `CC*DISPENSE*OK` / `CC*DISPENSE*NAK` / `CC*DISPENSE*FAIL` | Dispense coins |
| `CC*COINCFG*<type>*<value>*<accept>*<dispense>*OK` | Individual coin type configured |
| `CC*FEATCFG*OK` | Feature configuration sent |
| `CC*FEATENABLE*OK` / `CC*FEATENABLE*FAIL` | Enable extended features |

### Alternative Payout

| Response | Description |
|---|---|
| `CC*SUMPAYOUT*OK` / `CC*SUMPAYOUT*FAIL` | Alternative payout initiated |
| `CC*PAYSTATUS*<value>*<count>` | Coins dispensed per type (during payout) |
| `CC*PAYSTATUS*BUSY` | Payout still running |
| `CC*PAYSTATUS*FAIL` | Payout status request failed |
| `CC*PAID*<value>` | Coin value paid during payout |
| `CC*PAYOUTEND` | Payout complete |
| `CC*DISP*FIN` | Dispense finished |

### Diagnostics

| Response | Description |
|---|---|
| `CC*DIAG*OK` | Diagnostic status ACK |
| `CC*DIAG*NAK` | Diagnostic status NAK |
| `CC*DIAG*ND` | Diagnostic data not available |
| `CC*DIAG*<status>` | Diagnostic status pair |

### Manual Fill/Payout Reports

| Response | Description |
|---|---|
| `CC*MANUALFILL*<value>*<count>` | Coins manually filled into tube |
| `CC*MANUALFILL*UNKNOWN` | No fill data |
| `CC*MANUALFILL*FAIL` | Fill report failed |
| `CC*MANUALPAYOUT*<value>*<count>` | Coins manually paid out |
| `CC*MANUALPAYOUT*UNKNOWN` | No payout data |
| `CC*MANUALPAYOUT*FAIL` | Payout report failed |

---

## Bill Validator Responses (BV*)

### Configuration & Identification

| Response | Description |
|---|---|
| `BV*CFG*<featureLevel>*<countryCode>*<minBillValue>*<decimalPlaces>*<stackerCapacity>*<escrow>` | Setup data |
| `BV*BILLSUP*<type>*<value>*<recycle>*<accept>*<escrow>*<recycle>*<manualDisp>*<security>` | Bill type support |
| `BV*ID*<mfg>*<serial>*<model>*<swVer>*<recycleSupport>*<FTL>` | Device identification |
| `BV*ID*LEVEL_LOW` | Feature level < 2, no ID available |
| `BV*CFG*ERR` | Setup data error |
| `BV*CFG4*ERR` | Identification error |

### Poll Events

| Response | Description |
|---|---|
| `BV*BILLACTION*<type>*<value>*<route>` | Bill accepted (route: `STACKER`, `ESCROW`, `RETURN`, `RECYCLER`, `DISREJECT`, `RECMANUAL`, `DISPMANUAL`, `REC2CB`) |
| `BV*ATTEMPTS*<count>` | Failed bill insertion attempts |
| `BV*STATUS*JUSTRESET` | Device reset |
| `BV*STATUS*BADMOTOR` | Motor failure |
| `BV*STATUS*BADSENSOR` | Sensor failure |
| `BV*STATUS*BUSY` | Device busy |
| `BV*STATUS*ROMERROR` | ROM checksum error |
| `BV*STATUS*JAM` | Bill jam |
| `BV*STATUS*BILLREMOVED` | Bill removed from escrow |
| `BV*STATUS*CBOXOUT` | Cashbox removed |
| `BV*STATUS*DISABLED` | Device disabled |
| `BV*STATUS*INVESCROW` | Invalid escrow request |
| `BV*STATUS*REJECT` | Bill rejected |
| `BV*STATUS*FISHING` | Fishing attempt |

### Stacker & Escrow

| Response | Description |
|---|---|
| `BV*STACKER*<count>*<full>` | Stacker status (bill count, full flag) |
| `BV*STACKER*NAK` | Stacker status NAK |
| `BV*STK*ERR` | Stacker error |
| `BV*ESC*OK` / `BV*ESC*FAIL` | Escrow stack/return |

### Command Responses

| Response | Description |
|---|---|
| `BV*ENABLE*OK` / `BV*ENABLE*NAK` / `BV*ENABLE*FAIL*<reason>` | Enable bill acceptance — see *Granular FAIL/NAK* below |
| `BV*DISABLE*OK` / `BV*DISABLE*NAK` / `BV*DISABLE*FAIL*<reason>` | Disable bill acceptance — see *Granular FAIL/NAK* below |
| `BV*BILLCFG*<type>*<value>*<accept>*<escrow>*<recycle>*<manDisp>*<security>*OK` | Individual bill type configured |
| `BV*BILLSEC*OK` / `BV*BILLSEC*FAIL` | Security levels set |
| `BV*FEATENABLE*OK` / `BV*FEATENABLE*FAIL` | Enable features |
| `BV*RECYCLENABLE*OK` / `BV*RECYCLENABLE*FAIL` | Enable recycler |
| `BV*RECYCLEDISABLE*OK` / `BV*RECYCLEDISABLE*FAIL` | Disable recycler |

#### Granular FAIL/NAK semantics — `BV*ENABLE` / `BV*DISABLE`

These two commands map to MDB `0x34 BILL TYPE`. The reply is classified as:

| Suffix | Meaning | Source on the wire |
|---|---|---|
| `*OK` | BV acknowledged the BILL TYPE command | MDB `ACK` (0x00) |
| `*NAK` | BV refused the command at MDB protocol level | MDB `NAK` (0xFF) |
| `*FAIL*TIMEOUT` | No reply from BV within t-response window | RX timeout |
| `*FAIL*OVERRUN` | RX buffer overflowed during reply | reply >37 bytes |
| `*FAIL*CHKSUM` | Reply was a data block but checksum did not match | bus corruption |
| `*FAIL*UARTERR1` / `*FAIL*UARTERR2` | UART hardware-level error during reception | parity/framing/HW |
| `*FAIL*UNEXPECTED` | Reply received cleanly but was data when ACK/NAK expected | protocol-level surprise |
| `*FAIL` | Catch-all for any future error code (older firmware emits only this) | — |

**Host implication.** Per MDB 4.3 §6.10 (page 99), BILL TYPE has no state preconditions — including during escrow. A `*NAK` therefore indicates a peripheral-level rejection (out-of-spec for compliant readers); host can treat as a hard error. `*FAIL*TIMEOUT` / `*UARTERR*` / `*CHKSUM` indicate **bus-level transmission issues** independent of the BV's intent. The host can decide policy (escalate, crash-clean, retry, etc.) based on the specific suffix rather than treating all failures equivalently.

### Dispenser/Recycler

| Response | Description |
|---|---|
| `BV*DSTATUS*<type>*<value>*<count>*<full>` | Dispenser bill type status |
| `BV*DSTATUS*<type>*<value>*<count>*<full>*ERR` | Dispenser error |
| `BV*DSTATUS*FAIL` | Dispenser status failed |
| `BV*DISPBILL*OK` / `BV*DISPBILL*NAK` / `BV*DISPBILL*FAIL` | Dispense bills |
| `BV*DISPBILL*FL_LOW` | Feature level insufficient |
| `BV*DISPBILL*BILLWAIT` | Recycler waiting for bill |
| `BV*DISPVALUE*OK` / `BV*DISPVALUE*NAK` / `BV*DISPVALUE*FAIL` | Dispense by value |
| `BV*DISPVALUE*FL_LOW` | Feature level insufficient |
| `BV*DISPVALUE*BILLWAIT` | Recycler waiting for bill |
| `BV*DISPSTATUS*PAYOUTBUSY` | Payout busy |
| `BV*DISPSTATUS*ESCROWREQ` | Escrow request |
| `BV*DISPSTATUS*BUSY` | Busy |
| `BV*DISPSTATUS*BADSENSOR` | Bad sensor |
| `BV*DISPSTATUS*BADMOTOR` | Bad motor |
| `BV*DISPSTATUS*JAM` | Jam |
| `BV*DISPSTATUS*ROMERROR` | ROM error |
| `BV*DISPSTATUS*DISABLED` | Disabled |
| `BV*DISPSTATUS*BILLWAIT` | Waiting for bill |
| `BV*DISPSTATUS*FILLEDKEY` | Filled key |

### Payout

| Response | Description |
|---|---|
| `BV*DPS*<type>*<value>*<count>` | Payout status per bill type |
| `BV*DPS*BUSY` | Payout busy |
| `BV*DPS*FAIL` | Payout status failed |
| `BV*DPS*FL_LOW` | Feature level insufficient |
| `BV*DPV*<value>` | Payout value dispensed |
| `BV*DPVFIN` | Payout finished |
| `BV*DPVUNK` | Unknown payout state |
| `BV*DPV*FAIL` | Payout value failed |
| `BV*DPV*FL_LOW` | Feature level insufficient |

---

## Coin Hopper Responses (CH1* / CH2*)

### Configuration & Identification

| Response | Description |
|---|---|
| `CH<n>*CFG*<featureLevel>*<countryCode>*<minCoinValue>` | Hopper setup data |
| `CH<n>*COINSUP*<type>*<value>*<enabled>*<selfFilling>` | Coin type support |
| `CH<n>*ID*<mfg>*<serial>*<model>*<swVer>*<FTL>` | Device identification |
| `CH<n>*ID*FL_LOW` | Feature level insufficient |
| `CH<n>*CFGERR` | Configuration error |

### Fill Status

| Response | Description |
|---|---|
| `CH<n>*FILL*<value>*<count>*<full>` | Coin fill level per type |
| `CH<n>*FILL*<value>*<count>*<full>*ERR` | Fill error (full but count 0) |
| `CH<n>*FILLERR` | Fill status request failed |

### Poll Events

| Response | Description |
|---|---|
| `CH<n>*DISPENSED*<mode>*<result>*<value>*<count>*<remaining>` | Coins dispensed |
| `CH<n>*STATUS*JUSTRESET` | Device reset |
| `CH<n>*STATUS*PAYOUTBUSY` | Payout in progress |
| `CH<n>*STATUS*ESCROWREQ` | Escrow request |
| `CH<n>*STATUS*BADSENSOR` | Bad sensor |
| `CH<n>*STATUS*NOSTART` | No start |
| `CH<n>*STATUS*DISPJAM` | Dispenser jam |
| `CH<n>*STATUS*ROMERROR` | ROM error |
| `CH<n>*STATUS*FILLEDKEY` | Filled key activated |

### Command Responses

| Response | Description |
|---|---|
| `CH<n>*DISPENSE*OK` / `NAK` / `FAIL` | Dispense coins |
| `CH<n>*SUMPAYOUT*OK` / `NAK` / `FAIL` | Dispense by value |
| `CH<n>*COINCFG*<type>*<value>*<manualDisp>*OK` | Coin type configured |

### Payout

| Response | Description |
|---|---|
| `CH<n>*PAYSTATUS*<type>*<value>*<count>` | Coins dispensed per type |
| `CH<n>*PAYSTATUS*BUSY` | Payout running |
| `CH<n>*PAYSTATUS*FAIL` | Payout status failed |
| `CH<n>*PAID*<value>` | Value paid |
| `CH<n>*PAYOUTEND` | Payout complete |
| `CH<n>*DISP*FIN` | Dispense finished |

---

## Cashless Reader Responses (CD1* / CD2*)

### Configuration & Setup

| Response | Description |
|---|---|
| `CD<n>*CONFIG*OK` / `NAK` / `FAIL` | Device setup sent |
| `CD<n>*CFGPRICE1*OK` / `NAK` / `FAIL` | 16-bit prices configured |
| `CD<n>*CFGPRICE2*OK` / `NAK` / `FAIL` | 32-bit prices configured |
| `CD<n>*CFGPRICE2*FL_LOW` | Feature level insufficient |
| `CD<n>*EXPIDREQ*OK` / `NAK` / `FAIL` | Expansion ID requested |
| `CD<n>*ENFEAT*OK` / `NAK` / `FAIL` | Optional features enabled |
| `CD<n>*ENFEAT*FL_LOW` | Feature level < 3 |

### Configuration Data (from device)

| Response | Description |
|---|---|
| `CD<n>*CFG1*<level>*<country>*<scale>*<dp>*<maxResp>*<refund>*<multivend>*<display>*<cashSale>` | Reader setup data |
| `CD<n>*CFG1*???` | Invalid/unknown feature level |
| `CD<n>*CFG2*<mfg>*<serial>*<model>*<swVer>*<FTL>*<32bit>*<multiCur>*<negVend>*<dataEntry>*<alwaysIdle>` | Expansion ID data |

### Session & Vend Events (from poll)

| Response | Description |
|---|---|
| `CD<n>*JSTRST` | Device just reset (firmware re-initializes) |
| `CD<n>*SBEGIN*<funds>` | Session begin — level 1 (funds only) |
| `CD<n>*SBEGIN*<funds>*<mediaID>*<payType>` | Session begin — level 2 |
| `CD<n>*SBEGIN*<funds>*<mediaID>*<payType>*<lang>*<country>*<flag1>*<flag2>*<flag3>` | Session begin — level 3 |
| `CD<n>*SBEGIN*ERROR_CANNOT_PARSE` | Session begin parse error |
| `CD<n>*VAPPR*<funds>` | Vend approved (available funds) |
| `CD<n>*VDENY` | Vend denied |
| `CD<n>*SCANCREQ` | Session cancel request |
| `CD<n>*SEND` | Session end |
| `CD<n>*CNCLD` | Cancelled |
| `CD<n>*REVAPP` | Revalue approved |
| `CD<n>*REVDENY` | Revalue denied |
| `CD<n>*REVLIMIT*<funds>` | Revalue limit amount |
| `CD<n>*DTR` | Date/time request |
| `CD<n>*DER*<mode>*<fields>` | Data entry request |
| `CD<n>*DECNCL` | Data entry cancelled |
| `CD<n>*DISPREQ*<type>*<text>` | Display request |
| `CD<n>*COOS` / `CD<n>*COOS*<state>` | Command out of sequence |
| `CD<n>*RESP???` | Unknown poll response |

### Errors

| Response | Description |
|---|---|
| `CD<n>*ERROR*<type>*<code>` | Error report. Types: `PMERR`, `COMERR`, `COMERR2`, `COMERR3`, `RFAIL`, `COMERR5`, `PAYSUP`, `SERV`, `TAMP`, `REFERR`, `UNASGND` |

### Vend Command Responses

| Response | Description |
|---|---|
| `CD<n>*VENDSUCCESS*OK` | Vend success acknowledged |
| `CD<n>*VENDSUCCESS*FAIL` | Vend success failed |
| `CD<n>*<context>*OK` / `NAK` / `FAIL` | Generic command response (context = command name like `VENDCANCEL`, `VENDREQ`, etc.) |

---

## Diagnostic Responses (DIAG:)

All diagnostic messages use the `DIAG:` prefix and are always `\r\n` terminated. They can be filtered by the host as non-protocol informational output.

| Response | Description |
|---|---|
| `DIAG:<addr>*RESET` | MDB device reset sent (addr in hex) |
| `DIAG:PRICES16` | 16-bit price setup in progress |
| `DIAG:EXPANSION` | Expansion ID request in progress |
| `DIAG:OPT` | Optional features enable in progress |
| `DIAG:ENABLE` | EDC enable in progress |
| `DIAG:9` / `DIAG:10` | Tube status diagnostic checkpoints |
| `DIAG:CD<n>*RR:i:<pos>/<total>` | Response parsing loop position |
| `DIAG:CD<n>*BS` | Session begin processing |
| `DIAG:CD<n>*MDBReceiveComplete:<val>` | MDB receive complete flag (on error) |
| `DIAG:CD<n>*MDBReceiveErrorFlag:<val>` | MDB receive error flag (on error) |
| `DIAG:EXPID:cnt:<n>` | Expansion ID data byte count |
| `DIAG:sbsize:<n>` | Session begin data size |
| `DIAG:scale:<dp>:<sf>` | Decimal places and scaling factor |
| `DIAG:<prefix>:<hex>` | Hex dump (from `EXT_UART_Transmit_HEXDUMP`) |
| `DIAG*PING` | Diagnostic ping reply (command `9*1`) |

---

## Response Format Notes

- All responses terminated with `\r\n`
- Fields separated by `*`
- Monetary values formatted as decimal strings (e.g. `"19.95"`, `"5.00"`)
- Country codes are ISO 4217 numeric (e.g. `985` = PLN)
- `<n>` in `CD<n>`, `CH<n>` is device index: `1` or `2`
- Boolean fields: `0` = disabled/no, `1` = enabled/yes
- Hex dumps are lowercase without separators (e.g. `0a1b2c3d`)
