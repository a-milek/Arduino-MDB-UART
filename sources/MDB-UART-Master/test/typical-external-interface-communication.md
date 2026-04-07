# Typical External Interface Communication

This document describes the host-to-VMC external UART protocol: command format, response messages, and a real-world traffic example.

## Command Format

Commands are sent to the VMC as ASCII strings over the EXT UART (8-bit, 9600 baud by default).

```
<top_code>*<sub_code>*[param1*param2*...]+
```

- Fields are `*`-delimited
- Terminated by `+` (triggers processing)
- Top and sub codes are decimal integers

## Command Reference

### 0: Reset

| Sub | Description |
|-----|-------------|
| 0 | Reset all devices |
| 1 | Reset coin changer options |
| 2 | Reset bill validator options |
| 3 | Reset coin hopper options |

### 1: Coin Changer

| Sub | Description | Parameters |
|-----|-------------|------------|
| 1 | MDB reset | |
| 2 | Get setup + tube status + ID | |
| 3 | Enable acceptance | `[accept_mask]*[dispense_mask]*` (default 0xFFFF) |
| 4 | Disable acceptance | |
| 5 | Dispense coins | `cointype*quantity*` |
| 6 | Alternative payout | `value*` |
| 8 | Enable single coin type | `cointype*accept*dispense*` |
| 9 | Config features | `alt_payout*ext_diag*ctrl_manual*` |
| 0x0a | Tube status (diagnostic) | |

### 2: Bill Validator

| Sub | Description | Parameters |
|-----|-------------|------------|
| 1 | MDB reset | |
| 2 | Get setup data | |
| 3 | Enable acceptance | |
| 4 | Disable acceptance | |
| 5 | Escrow accept/reject | `0 or 1*` |
| 6 | Dispense bills | `count*value*` |
| 7 | Dispense by value | `value*` |
| 8 | Enable bill type | `a*b*c*d*e*f*` (6 params) |
| 9 | Config features | `features_byte*` |
| 10 | Cancel payout | |

### 3: Coin Hopper

Requires hopper index as first parameter: `3*<1 or 2>*<sub>*...+`

| Sub | Description | Parameters |
|-----|-------------|------------|
| 1 | MDB reset | |
| 2 | Get setup + ID | |
| 6 | Dispense coins | `cointype*count*` |
| 7 | Dispense by value | `value*` |
| 8 | Enable manual dispense | `cointype*enable*` |

### 9: Diagnostic / Cashless

| Sub | Description | Parameters |
|-----|-------------|------------|
| 1 | Ping | |
| 2 | Full cashless init sequence | |
| 3 | Vend request | `price*item_number*` |
| 4 | Vend success | `item_number*` |
| 5 | Session complete | |
| 6 | Reader reset | |
| 7 | Enable/disable reader | `edc_byte*` |
| 8 | Vend failure | |
| 9 | Cash sale | `price*item_number*` |
| 10 | Vend cancel | |

### 10: System

| Sub | Description |
|-----|-------------|
| 1 | Ping (responds `SYS*PING*OK`) |
| 99 | Software reset |

## Response Format

All responses are ASCII, `*`-delimited, terminated with `\r\n`.

### System

| Response | Description |
|----------|-------------|
| `SYS*MDBSTART*<version>` | Startup banner |
| `SYS*PING*OK` | Ping reply |
| `SYS*RESET*OK` | Reset acknowledgment (before CPU reset) |

### Coin Changer (CC\*)

| Response | Fields | Description |
|----------|--------|-------------|
| `CC*CFG*<level>*<currency>*<min_value>` | Feature level, currency code, min dispensable value | Setup data |
| `CC*COINSUP*<tube>*<value>*<accept>*<dispense>` | Tube 1-16, coin value, accept flag, dispense flag | Per coin type |
| `CC*TUBE*<tube>*<value>*<count>*<full>` | Tube number, coin value, quantity, full flag | Tube status |
| `CC*TUBESTATREQ*OK/FAIL` | | Tube status request result |
| `CC*DEPOSIT*<type>*<value>*<route>*<count>` | Coin type, value, CASHBOX/TUBE/REJECT, coins in tube | Coin inserted |
| `CC*SLUG*<count>` | Slug count | Slugs detected |
| `CC*STATUS*<status>` | ESCROWREQ, PAYOUTBUSY, NOCREDIT, BADTUBESENSOR, DOUBLECOIN, UNPLUGGED, TUBEJAM, ROMERROR, ROUTERROR, BUSY, JUSTRESET, COINJAM, FISHING | Poll status |
| `CC*MANUALDISP*<type>*<value>*<disp>*<left>` | Coin type, value, dispensed count, remaining | Manual dispense event |
| `CC*ENABLE*OK/FAIL` | | Acceptance enabled |
| `CC*DISABLE*OK/FAIL` | | Acceptance disabled |
| `CC*DISPENSE*OK/NAK/FAIL` | | Dispense result |
| `CC*PAID*<value>` | Amount dispensed | Alternative payout value |
| `CC*PAYOUTEND` | | Payout complete |
| `CC*PAYSTATUS*<value>*<count>` | Coin value, remaining qty (or BUSY/FAIL) | Payout progress |
| `CC*DIAG*OK/NAK/ND` | | Diagnostic status |
| `CC*ID*<mfg>*<serial>*<model>*` | Manufacturer, serial, model | Identification |

### Bill Validator (BV\*)

| Response | Fields | Description |
|----------|--------|-------------|
| `BV*CFG*<level>*<currency>*<min_value>*<decimals>*<stacker_cap>*<escrow>` | Feature level, currency, min value, decimal places, stacker capacity, escrow support | Setup data |
| `BV*BILLSUP*<type>*<value>*<recycle>*<accept>*<escrow>*<recycle>*<manual>*<security>` | Bill type 1-16, value, 6 feature flags | Per bill type |
| `BV*STACKER*<count>*<full>` | Bills in stacker, full flag | Stacker status |
| `BV*DSTATUS*<type>*<value>*<count>*<full>` | Bill type, value, quantity, full flag | Dispenser status |
| `BV*BILLACTION*<type>*<value>*<route>` | Bill type, value, STACKER/ESCROW/RETURN/RECYCLER | Bill event |
| `BV*STATUS*<status>` | JUSTRESET, BADSENSOR, BUSY, ROMERROR, JAM, BILLREMOVED, CBOXOUT, DISABLED, INVESCROW, REJECT, FISHING | Poll status |
| `BV*ATTEMPTS*<count>` | Attempt count | Bills rejected while disabled |
| `BV*ENABLE*OK/FAIL` | | Acceptance enabled |
| `BV*DISABLE*OK/FAIL` | | Acceptance disabled |
| `BV*ESC*OK/FAIL` | | Escrow result |
| `BV*ID*<mfg>*<serial>*<model>*` | Manufacturer, serial, model | Identification |

### Cashless Device (CD1\*, CD2\*)

| Response | Fields | Description |
|----------|--------|-------------|
| `CD<n>*CFG1*<level>*<currency>*<scale>*<decimals>*<max_time>*<refund>*<multivend>*<display>*<cashsale>` | 9 fields | Device configuration |
| `CD<n>*VAPPR*<funds>` | Available funds | Vend approved |
| `CD<n>*SBEGIN*<funds>*<media_id>*<payment_type>*<language>*<country>*<flags...>` | Variable fields | Session begin |
| `CD<n>*SEND` | | Reader command sent |
| `CD<n>*EDC*OK` | | Reader enabled/disabled |
| `CD<n>*SCOMPL*OK` | | Session complete |
| `CD<n>*VDENY` | | Vend denied |
| `CD<n>*CNCLD` | | Vend cancelled |
| `CD<n>*VENDCANCEL*OK` | | Vend cancel acknowledged |
| `CD<n>*CSHSALE*OK` | | Cash sale reported |
| `CD<n>*JSTRST` | | Device just reset |
| `CD<n>*ERROR*<msg>*<code>` | Error string, code 0-15 | Error report |

### Coin Hopper (CH1\*, CH2\*)

| Response | Fields | Description |
|----------|--------|-------------|
| `CH<n>*CFG*<level>*<currency>*<min_value>` | Feature level, currency, min value | Setup data |
| `CH<n>*COINSUP*<type>*<value>*<available>*<self_filling>` | Coin type, value, flags | Per coin type |
| `CH<n>*FILL*<value>*<qty>*<full>` | Coin value, quantity, full flag | Filler status |
| `CH<n>*DISPENSE*OK/NAK/FAIL` | | Dispense result |
| `CH<n>*DISPENSED*<mode>*<result>*<value>*<qty>*<left>` | AUTO/MANUAL, OK/FAIL, value, qty, remaining | Dispense report |
| `CH<n>*STATUS*<status>` | ESCROWREQ, PAYOUTBUSY, BADSENSOR, DISPJAM, ROMERROR, JUSTRESET, FILLEDKEY | Poll status |

### Diagnostic / Debug

| Response | Description |
|----------|-------------|
| `DIAG*PING` | Diagnostic ping echo |
| `DIAG:<prefix>:<hex>` | Hex dump (e.g. `DIAG:MDBSEND:0cffffffff08`) |
| `WMDIAG*<msg>` | Internal debug markers |

## Typical Startup Sequence

Captured from a live system (firmware 1.2.2) with:
- Coin changer: MEI CF7400MDB, feature level 3
- Bill validator: ITL NV1 REV 3-29, feature level 1
- Cashless reader 1: feature level 2
- Currency: PLN (ISO 4217 code 1985)

```
SYS*MDBSTART*1.2.2                          <- startup banner with version

SYS*VMCSET*READ*OK                          <- EEPROM settings loaded
SYS*CDSET*READ*OK
SYS*CCSET*READ*OK
SYS*BVSET*READ*OK
SYS*CHSET*READ*OK

CD1*RESET*OK                                <- cashless reader 1 reset
CD2*RESET*FAIL                              <- cashless reader 2 not connected

CD1*CFG1*2*1985*1*2*40*1*0*1*1              <- CD1 config: FL2, PLN, scale=1, dp=2

CC*STATUS*JUSTRESET                         <- coin changer reports JUSTRESET on first poll
CC*CFG*3*1985*0.10                          <- CC setup: FL3, PLN, min value 0.10
CC*COINSUP*1*0.10*1*1                       <- supported coins with accept/dispense flags
CC*COINSUP*2*0.20*1*1
CC*COINSUP*3*0.50*1*1
CC*COINSUP*4*1.00*1*1
CC*COINSUP*5*2.00*1*1

CC*ID*MEI*4599GF12078 *CF7400MDB   *127*1*1*1*0  <- CC identification

CC*TUBE*1*0.10*0*0                          <- tube status: tube 4 has 31 coins
CC*TUBE*2*0.20*0*0
CC*TUBE*3*0.50*0*0
CC*TUBE*4*1.00*31*0
CC*TUBE*5*2.00*1*0
CC*TUBE*6*5.00*0*0
CC*TUBESTATREQ*OK

BV*STATUS*DISABLED                          <- BV initial state
BV*STATUS*JUSTRESET                         <- BV reports JUSTRESET
BV*CFG*1*1985*1.00*2*300*1                  <- BV setup: FL1, PLN, scale=1.00, dp=2, stacker=300, escrow=yes
BV*ID*ITL*0000001F82A4*NV1 REV 3-29*111*0*0  <- BV identification
BV*BILLSUP*1*10.00*0*1*1*1*1*1             <- supported bills with feature flags
BV*BILLSUP*2*20.00*0*1*1*1*1*1
BV*BILLSUP*3*50.00*0*1*1*1*1*1
BV*BILLSUP*4*100.00*0*1*1*1*1*1
BV*BILLSUP*5*200.00*0*1*1*1*1*1

BV*STACKER*0*0                              <- stacker: 0 bills, not full

SYS*DEVONLINE*CC                            <- devices online
SYS*DEVONLINE*BV

DIAG:DIAGST:0300                            <- periodic CC diagnostics begin
CC*DIAG*OK
```

## Typical Runtime Traffic

Captured during normal operation with a cashless vend cycle and coin deposit:

```
CD1*EDC*OK                                   <- cashless reader enabled
DIAG:MDBSEND:0c000000000c
CC*DISABLE*OK                                <- coins disabled (vend session)
DIAG:MDBSEND:340000000034
BV*DISABLE*OK                                <- bills disabled (vend session)
CD1*SCOMPL*OK                                <- session complete
CD1*SEND                                     <- reader re-init
CD1*EDC*OK                                   <- reader re-enabled
DIAG:MDBSEND:0cffffffff08
CC*ENABLE*OK                                 <- coins re-enabled
DIAG:MDBSEND:34ffffffff30
BV*ENABLE*OK                                 <- bills re-enabled

CC*TUBE*1*0.10*0*0                           <- periodic tube status poll
CC*TUBE*2*0.20*0*0
CC*TUBE*3*0.50*0*0
CC*TUBE*4*1.00*31*0                          <- 31 coins of 1.00 in tube 4
CC*TUBE*5*2.00*0*0
CC*TUBE*6*5.00*0*0
CC*TUBESTATREQ*OK

BV*STACKER*0*0                               <- stacker empty, not full

CC*DEPOSIT*5*2.00*TUBE*1                     <- 2.00 coin deposited into tube

CD1*VENDCANCEL*OK                            <- vend cancelled
DIAG:MDBSEND:0c000000000c
CC*DISABLE*OK                                <- coins disabled for new session

DIAG:DIAGST:0300
CC*DIAG*OK                                   <- periodic diagnostic (every ~37 polls)

DIAG:MDBSEND:130500c80000e0
CD1*CSHSALE*OK                               <- cash sale: 0x00C8 = 200 units = 2.00
CD1*EDC*OK
CC*DISABLE*OK
BV*DISABLE*OK
CD1*SCOMPL*OK
CD1*SEND
CD1*EDC*OK
CC*ENABLE*OK
BV*ENABLE*OK

CC*TUBE*4*1.00*31*0                          <- tube status after transaction
CC*TUBE*5*2.00*1*0                           <- tube 5 now has 1 coin (the deposit)
CC*TUBESTATREQ*OK

DIAG:DIAGST:0300                             <- periodic diagnostics continue
CC*DIAG*OK
```

### Typical Cycle Pattern

1. **Startup**: EEPROM settings loaded, devices reset, SETUP/ID queries, JUSTRESET handling
2. **Idle**: CC diagnostic polls every ~37 cycles, tube status every ~666 cycles
3. **Vend session**: CC+BV disabled -> cashless session -> CC+BV re-enabled
4. **Coin deposit**: `CC*DEPOSIT` with coin type, value, routing, tube count
5. **Cash sale**: `CD*CSHSALE` with MDB send showing price bytes
6. **Status polling**: All devices polled continuously; offline devices decrement `OfflinePollsCount`

### Notes

- `CC*COINSUP` only lists coin types that are **routeable to tubes** (per SETUP response Z6-Z7 routing bits). A coin type may still appear in `CC*TUBE` with a value and 0 count if the changer knows the denomination but has no physical tube for it (e.g. 5.00 PLN goes to cashbox only).
