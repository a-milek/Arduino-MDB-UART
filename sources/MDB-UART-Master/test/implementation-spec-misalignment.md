# Implementation vs MDB 4.2 Specification Misalignment

Review date: 2026-04-07
Spec reference: Docs/MDB_version_4-2.pdf (Version 4.2, February 2011)

## Critical

### 1. Bill Validator stacker capacity — wrong shift operand

**File:** BillValidator_M.c:765
**Spec:** Section 6.2, SETUP (31H) response Z7-Z8: Stacker Capacity, 2 bytes, e.g. 400 = 0190H

**Code:**
```c
BillValidatorSetupData.StackerCapacity = (MDB_BUFFER[6] << MDB_BUFFER[7]) | MDB_BUFFER[7];
```

**Expected:**
```c
BillValidatorSetupData.StackerCapacity = (MDB_BUFFER[6] << 8) | MDB_BUFFER[7];
```

**Impact:** Shifts by the value of the low byte instead of by 8 bits. For a 400-bill stacker (0x01, 0x90), computes `(1 << 144) | 0x90` — undefined behavior. Stacker capacity is always wrong. Affects `BV*CFG` response reporting.

### 2. Coin Hopper SETUP — CoinTypeCredit offset off by 3

**File:** CoinHopper_M.c:72
**Spec:** Section 10.3, SETUP (59H/71H) response, 26 bytes:

| Bytes | Field |
|-------|-------|
| Z1 (0) | Feature Level |
| Z2-Z3 (1-2) | Country/Currency Code |
| Z4 (3) | Coin Scaling Factor |
| Z5 (4) | Decimal Places |
| Z6 (5) | Max Response Time |
| Z7-Z8 (6-7) | Disabled Coins |
| Z9-Z10 (8-9) | Self-Filling Coins |
| Z11-Z26 (10-25) | Coin Type Credit, 16 bytes |

**Code:**
```c
for (int i = 10; i < MDB_BUFFER_COUNT; i++)
    CoinHopperSetupData[index].CoinTypeCredit[i - 7] = MDB_BUFFER[i];
```

**Expected:**
```c
for (int i = 10; i < MDB_BUFFER_COUNT; i++)
    CoinHopperSetupData[index].CoinTypeCredit[i - 10] = MDB_BUFFER[i];
```

**Impact:** Writes to CoinTypeCredit[3..18] instead of CoinTypeCredit[0..15]. First 3 coin types get stale/zero values, last 3 writes overflow the array. All coin value calculations for the hopper are wrong.

### 3. Coin Hopper Dispenser Status — wrong CoinTypeCredit index

**File:** CoinHopper_M.c:134
**Spec:** Section 10.3, DISPENSER STATUS (5AH/72H) response: Z1-Z2 = full flags, Z3-Z34 = 16 coin counts (2 bytes each)

**Code:**
```c
for (int i = 2; i < MDB_BUFFER_COUNT; i++)
{
    ...
    CoinHopperSetupData[index].CoinTypeCredit[i]  // i starts at 2, not the coin type index
    ...
    i++;  // hidden increment
}
```

**Expected:** Use `(i - 2) / 2` as coin type index (same as the byte-pair stepping), or refactor to `i += 2` in the loop header.

**Impact:** Looks up wrong coin type credits for dispenser status values. Also has hidden `i++` in body (same pattern fixed in BillValidator dispenser status).

## Medium

### 4. Coin Hopper Dispenser Status — fullflags tautological compare

**File:** CoinHopper_M.c:139

**Code:**
```c
if ((coinsqty == 0x00) && ((fullflags & (1 << ((i - 2) / 2))) == 1))
```

**Expected:**
```c
if ((coinsqty == 0x00) && ((fullflags & (1 << ((i - 2) / 2))) != 0))
```

**Impact:** Same bug pattern as the stacker-full issue fixed in `5bcef7f`. The bitwise AND yields `0` or a power-of-2, never `1` (except for bit 0). The `*ERR` suffix is only appended for coin type 0 full condition, not for types 1-15.

## Verified Correct

- Coin Changer SETUP (09H) response parsing: byte offsets Z1-Z23 match spec
- Coin Changer TUBE STATUS (0AH) response parsing: Z1-Z2 flags, Z3-Z18 counts
- Bill Validator SETUP (31H) response: all fields except stacker capacity
- Bill Validator STACKER (36H) response: full flag and bill count (fixed in `5bcef7f`)
- Bill Validator POLL (33H) response: bill routing and status decoding
- Coin Changer POLL (0BH) response: deposit/dispense/slug/status decoding
- All MDB command codes and peripheral addresses match spec Section 2.3
- Checksum validation algorithm (sum mod 256)
- ACK (0x00 mode=0) and NAK (0xFF mode=1) handling
- 9th bit (mode bit): address bytes mode=1, data bytes mode=0
