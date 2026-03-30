# MDB / ICP — Multi-Drop Bus / Internal Communication Protocol

**Version 4.2 — February 2011**

---

         Multi-Drop Bus /
Internal Communication Protocol

## Mdb / Icp

          Supported by the Technical Members of:

| NAMA | National | Automatic Merchandising Association |
|---|---|---|
| EVA | European | Vending Association |
| EVMMA | European | Vending Machine Manufacturers Association |

                   Version 4.2
                   February, 2011

     National Automatic Merchandising Association
              20 N. Wacker Drive, Suite 3500
           Chicago, Illinois 60606-3120 USA
           312-346-0370 FAX 312-704-4140
                     www.vending.org

(this page intentionally left blank)

                                 Table of Contents
           Revisions
           Introduction
           Section 1
           General Information

### 1. Introduction

### 2. Operational and Application Notes

### 3. Levels and Options

           Section 2
           Communication Format

### 1. Byte Format

### 2. Block Format

### 3. Peripheral Addresses

### 4. Software Operational Rules

### 5. Typical Session Examples

### 6. File Transport Layer

           Section 3
           Bus Timing

### 1. Timing Definitions

### 2. Timing Specifications

### 3. Timing Diagram

           Section 4
           Hardware Specification

### 1. Bus Power Supply Definition

                  2. Bus Transmitter/Receiver Specification

### 3. Connector Specification

### 4. Example Schematic

            Section 5
            Coin Acceptor/Changer
            VMC/Peripheral Communication Specifications

### 1. Introductions

### 2. VMC Commands

### 3. VMC Command Format

                   4. Changer Non-Response Time

### 5. Changer Power Requirements

                   6. Coin Acceptor/Changer Examples

           Section 6
           Bill Validator
           VMC/Peripheral Communication Specifications

### 1. Introductions

### 2. VMC Commands

### 3. VMC Command Format

                    4. Bill Validator Non-Response Tome

### 5. Bill Validator Power Requirements

                    6. Bill Validator / Recycler Examples
           Section 7
           Cashless Device(s)
           VMC/Peripheral Communication Specifications

### 1. Introduction

### 2. State Definitions

### 3. Command Protocol

### 4. Cashless Device Command Response Formats

                  5. Cashless Device Non-Response Time

### 6. Cashless Device Power Requirements

### 7. Example Vend Sessions

           Section 8
           Communications Gateway
           VMC/Peripheral Communication Specifications

### 1. Introduction

### 2. VMC Commands

### 3. Communications Gateway Command Format

                  4. Communications Gateway Non-Response Time

### 5. Communications Gateway Power Requirements

### 6. Communications Gateway Examples

            Section 9
            Universal Satellite Device
            VMC/Peripheral Communication Specifications

### 1. Introduction

### 2. USD Summary

### 3. Command Protocol

### 4. USD Power Requirements

                   5. Examples - Mode 1 / 2 / 3 Sessions
                   6. Examples - Data Block Transfers
                   7. Examples - Communications

            Section 10
            Coin Hopper or Tube – Dispenser
            VMC/Peripheral Communication Specifications

### 1. Introduction

### 2. VMC Commands

### 3. VMC Command Format

                   4. Dispenser Non-Response Time

### 5. Dispenser Power Requirements

            Appendix 1
            Currency Codes

           Appendix 2
           Battery Operated Card Reader

           Appendix 3
           MDB Recommended “Best Practices”

Revisions

Version 4.2
Version 4.1 of this specification is the sixth release of the international Multi-Drop Bus /
Internal Communication Protocol (MDB / ICP). This specification is the continued
effort put forth by technical members of NAMA and the EVA. The basis for this
specification is the Version 4.1 international Multi-Drop Bus / Internal
Communication Protocol (MDB / ICP) released in July, 2010.

There is just one major change within cashless device(s) section, related to cashless
devices commonly new in public (credit card) transactions. These devices, especially
contactless operated, need an uninterrupted transaction starting with the actual correct
vend price and therefore are not able to deliver a begin session in front of the
transaction. Previous work arounds have been

        - Always starting a begin session by cashless with “unknown credit”, which of
             course interferes with cash payment (normally a VMC would disable
             coin/bill acceptance, while a session is active)

        - Forcing the customer to hold the payment media twice to the cashless
             device, once to start the session and second after pressing the selection to
             do the transaction.

The new modification allows such cashless devices, to identify themselves with an
option bit, telling the VMC, that they are capable of accepting vend request, negative
vend request and, if possible, revalue request, while in the enabled state as well as in
the idle state.

If this option bit is set, a VMC will produce a vend request to the cashless whenever a
selection is pressed and not sufficient cash credit is available. The cashless will
proceed with this request like in the idle state. If in between, the customer will not
present a valid cashless payment media and instead insert cash, the VMC will cancel
the vend request with a vend cancel command and after this is accepted, a session
complete to return to the enabled state.

## Section 1 – General Information

     Section 1.3.3
        - Added b5, “always idle session” option

## Section 7 – Cashless Device(s)

     Section 7.2.3
        - Added the “always idle session” option
     Section 7.3
        - Added the “always idle session” option
     Section 7.4.4

      - Added b5, “always idle session” option in Ident response
     Section 7.7
      - Added example #11, vend session (always idle session option set)
      - Added example #12, vend session cancelled (always idle session option
           set)
      - Added example #13, vend session timeout (always idle session option set)

Version 4.1
Version 4.1 of this specification is the fifth release of the international Multi-Drop Bus /
Internal Communication Protocol (MDB / ICP). This specification is the continued
effort put forth by technical members of NAMA and the EVA. The basis for this
specification is the Version 4.0 international Multi-Drop Bus / Internal
Communication Protocol (MDB / ICP) released in April, 2009.

Of special note are the two major changes that were made to the specification:

        - Changed the address of the second Coin Hopper / Tube Dispenser device
              peripheral in Section 10 from 68H to 70H.
        - Added the Age Verification Device peripheral (address 68H) in Section 11.

The following lists the primary revisions to the Version 4.1 of the MDB / ICP.

## Section 2 – Communication Format

     Section 2.3
        - Changed the address for the second Coin Hopper or Tube – Dispenser to
           01110xxxB (70H).

        - Added address 01101xxxB (68H) for the Age Verification Device.

## Section 5 – Coin Changer

          - Corrected Page 5.14:
                 Expansion command send diagnostic status (0F 05) response data:
                 16 bytes: Z1-Z16 changed to 2 bytes: Z1-Z2

## Section 6 – Bill Validator / Recycler

        - Corrected Page 6.6:
                Notes: 1. Dispenser setup (3703) command replaced by recycler
                enabled (3704).
        - Corrected Page 6.13:
                Under VMC Data: 19 bytes: Y1- Y19 replaced by Y1- Y18.
                Y3-Y19 replaced by Y3 – Y18 = 16 bytes
        - Corrected Page 6.14:
                Y19 replaced by Y18
        - Page 6.21, added after Expansion/ID:

## Feature Enable 

##  Ack

## Section 10 – Coin Hopper or Tube - Dispenser

     Section 10.1, 10.2, 10.3
        - Changed second device address to 01110xxxB (70H).

## Section 11 – Age Verification Device

        - Added entire section.

Version 4.0
Version 4.0 of this specification is the fourth release of the international Multi-Drop Bus
/ Internal Communication Protocol (MDB / ICP). This specification is the continued
effort put forth by technical members of NAMA and the EVA. The basis for this
specification is the Version 3.0 international Multi-Drop Bus / Internal
Communication Protocol (MDB / ICP) released on March 26, 2003.

Of special note are the three major changes that were made to the specification:

        - Added the Bill Recycler command set to the Bill Validator / Recycler device
             peripheral in Section 6.
        - Added a second address to the Coin Hopper / Tube Dispenser device
             peripheral in Section 10.
        - Added the MDB Recommended “Best Practices” as Appendix 3.

The following lists the primary revisions to the Version 4.0 of the MDB / ICP.

## Section 2 – Communication Format

     Section 2.3
        - Added address 01101xxxB (68H) for the second Coin Hopper or Tube –
           Dispenser.

## Section 5 – Coin Acceptor / Changer

     Section 5.3
        - Added information regarding “Just Reset”.
        - Corrected typo for POLL command to `08h`.
        - Added “Type activity” definitions in POLL Status section.
        - Added Section 5.6 Coin Acceptor/Changer Examples.

## Section 6 – Bill Validator

     Section 6.3
        - Added information regarding “Just Reset”.
        - Added “Type activity” definitions in POLL Status section
        - Added all new command/responses for the Bill Recycler.

## 37H - 03H     Recycler Setup

## 37H - 04H     Recycler Enable

## 37H - 05H     Bill Dispense Status

## 37H - 06H     Dispense Bill

## 37H - 07H     Dispense Value

## 37H - 08H     Payout Status

## 37H - 09H     Payout Value Poll

## 37H - 0Ah     Payout Cancel

        - Added Section 5.6 Bill Validator/Recycler Examples.

## Section 7 – Cashless

     Section 7.3
        - Added information regarding “allows selection without displaying balance”
            in the Begin Sessions (03H) – Funds Available response.

     Section 7.5
        - Added information regarding using the Non-Response time for commands
           that require data to be returned.

     Section 7.7
        - Added Controller “ACKs” to the end of the card reader session examples.

## Section 8 – Communication Gateway

     Section 8.2
        - Added 1FH/02H TIME/DATE REQUEST to VMC Command table.

     Section 8.3
        - Added option bit b2 : Expansion Time/Date Request command
        - Added 1FH/02H TIME/DATE REQUEST command/response.

## Section 9 – Universal Satellite Device (USD)

     Section 9.3
        - Corrected errors in 07H - Z3 to Z33 designations.

## Section 10 – Coin Hopper or Tube - Dispenser

     Section 10.1, 10.2, 10.3
        - Added a second devices as address 11001xxxB (68H).
        - Expanded on the "Coins Dispensed" section of the DISPENSER STATUS
            response.

Appendix 3 – MDB Recommended “Best Practices”
      - Added entire appendix.

Version 3.0
Version 3.0 of this specification is the third release of the international Multi-Drop Bus /
Internal Communication Protocol (MDB / ICP). This specification is the continued
effort put forth by technical members of NAMA and the EVA. The basis for this
specification is the Version 2.0 international Multi-Drop Bus / Internal
Communication Protocol (MDB / ICP) released on October 4, 2002.

Of special note are the four major changes that were made to the specification:

        - Added a second Cashless Device peripheral address in Section 7
        - Replaced the Audit Unit with the Communications Gateway in Section 8
        - Added the Coin Hopper or Tube – Dispenser in Section 10 (new)
        - Assigned 2 addresses to be used for experimental peripherals

The following lists the primary revisions to the Version 3.0 of the MDB / ICP.

## Section 1 – General Information

     Section 1.3
        - Changed the Level and Options chart for the Communications Gateway
           and the Coin Hopper or Tube – Dispenser

## Section 2 – Communication Format

     Section 2.2
        - Added headers for the Response Codes
        - Clarified non response processing for Master-to-Peripheral and Peripheral-
           to-Master communication.
     Section 2.3
      - Updated the Peripheral Address table for the Communications Gateway,
           Coin Hopper, Cashless Payment 1, and Experimental addresses
      - Defined the use of the experimental addresses
     Section 2.5
      - Added new RESET examples F & G.

## Section 5 – Coin Acceptor / Changer

     Section 5.2
        - Renamed the STATUS command to SETUP command
        - Added a new Possible Credited Coin Removal status code (`0Dh`)

## Section 6 – Bill Validator

     Section 6.2
        - Renamed the STATUS command to SETUP command
        - Added a new Possible Credited Bill Removal status code (`0Ch`)

## Section 7 – Cashless Device(s)                       (New Cashless Device #2)

     Changed name from Cashless Payment to Cashless Device

     Section 7.1
        - Added information regarding the dual addresses for two Cashless Device
           peripherals (`10h` and `60h`)
     Section 7.3
        - Updated Command & Response table for dual addresses
     Section 7.4
        - Updated Command/Response Formats for dual addresses

## Section 8 – Communications Gateway                       (New Peripheral)

     Sections 8.1 through 8.6
        - Replaced former Audit Unit sections with new Communications Gateway
            Sections

## Section 9 –Universal Satellite Device (USDC)

     Section 9.3
        - Updated POLL table with proper number of bytes (FTL portion)
        - Changed “numeric row and column” to “Item Number”

## Section 10 – Coin Hopper or Tube – Dispenser              (New Peripheral)

      Sections 10.1 through 10.5
        - Added complete new sections

Version 2.0
Version 2.0 of this specification is the second release of the international Multi-Drop
Bus / Internal Communication Protocol (MDB / ICP). This specification is the
culmination of effort put forth by technical members of NAMA, the EVMMA, and the
EVA. The basis for this specification is the Version 1.0 international Multi-Drop Bus /
Internal Communication Protocol (MDB / ICP) released on October 14, 1998.

The following lists the primary revisions to the Version 2.0 of the MDB / ICP

Introduction
     Foreword
      - Clarified that the Standard is a communication interface

## Section 1 - General Information

     Section 1.1
      - Added 3rd paragraph noting interface specification vs. system specification
     Section 1.3
      - Added entire Levels and Options section

## Section 2 - Communication Format

     Section 2.1
      - Changed Mode Bit Master-to-Peripheral text
     Section 2.2
      - Removed “command” from Master-to-Peripheral 4 paragraph
                                                       th

      - Changed RET description
     Section 2.3
      - Defined address 0000xxxB (00H) for VMC
      - Provided address information to show hexadecimal format
     Section 2.4
      - Changed format to 2.4.X sub-sections and added 2.4.4 on Levels
     Section 2.5
      - Changed RET description
     Section 2.6
      - Added complete File Transport Layer Section

## Section 3 - Bus Timing

     Section 3.1
      - Added 2nd sentence to tsetup

## Section 4 - Hardware Specification

     Section 4.3
      - Modified complete section and added AMP as alternate source to Molex
     Section 4.4
      - Added pin numbers to schematic

## Section 5 - Coin Acceptor / Changer

     Section 5.1
      - Provided additional address information
     Section 5.3
      - Added recommended RESET command sequence
      - Modified STATUS response to indicate Country / Currency Codes
      - Modified County / Currency Code to include ISO 4217 (Appendix A1)
      - Added Note 2 to DISPENSE (ODH) command
      - Added FTL POLLed responses
      - Added FTL “b3” option bit
      - Added FTL expansion commands
      - Cosmetic changes to all EXPANSION commands
      - Split ALTERNATIVE PAYOUT (0FH-02H) and PAYOUT STATUS (0FH-
            03H) command into two separate commands (cosmetic change only)
      - Added text to ALTERNATIVE PAYOUT (0FH-02H) Y1 description
      - Added Note 3 to ALTERNATIVE PAYOUT STATUS (0FH-03H)
     Section 5.5
      - Added “See Note 2 …” text
      - Added “If both peripherals supported” to Note

## Section 6 - Bill Validator

     Section 6.1
      - Provided additional address information
     Section 6.3
      - Added recommended RESET command sequence
      - Modified STATUS response to indicate Country / Currency Codes
      - Modified County / Currency Code to include ISO 4217 (Appendix A1)
      - Added Level 2 information
      - Added Level 2 option bytes w/ new EXPANSION COMMANDs:
| 37H | 01H | Level | 2 Option Bit Enable |
|---|---|---|---|
| 37H | 02H | Level | 2 Identification |

      - Added FTL POLLed responses
      - Added FTL “b0” option bit
      - Added FTL expansion commands
      - Modified last sentence in SECURITY command to link to Z9-Z10
            STATUS response
      - Cosmetic changes to all EXPANSION commands

     Section 6.5
      - Added “If both peripherals supported” to Note

## Section 7 - Cashless Payment

     Section 7.2 & 7.2.7
      - Added Level 03 Negative Vend Request
     Section 7.2.2
      - Changed 1st sentence to link Setup to 7.4.1 information
     Section 7.2.4
      - Added Negative Vend and Revalue
     Section 7.2.7
      - Added Level 03 Negative Vend Request
     Section 7.3
      - Added bold text regarding defining currency at the beginning of a session
      - Broke uninterruptable table into VMC Command and Reader Response
      - Added Level 03 NEGATIVE VEND REQUEST to VMC Command table
      - Added Level 03 DATA ENTRY REQUEST to Reader Response table
      - Highlighted command out of sequence hard resets from VMC
      - Moved Vend Failure Sequence to 7.4.8
     Section 7.3 – Table 1
      - Changed name to COMMANDS & RESPONSES
      - Changed Comment column to VMC / Reader Level Support
      - Linked all commands and responses to Levels
      - Added DATA ENTRY REQUEST POLLed responses
      - Added FTL POLLed responses
      - Added FTL commands
      - Added NEGATIVE VEND REQUEST responses
      - Defined 14H-1AH and 20H-FEH as “For Future Use”
     Section 7.4.1
      - Cosmetically modified RESET command sequence
      - Added 32 bit SETUP MAX/MIN PRICE
      - Changed text following Reader response
     Section 7.4.2
      - Clarified Level 01 information (reader has no revalue capability)
      - Added Level 03 information
      - Modified SETUP response to indicate Country / Currency Codes
      - Modified County / Currency Code to include ISO 4217 (Appendix A1)
      - Added bold Note in Z3-Z4 County / Currency Code
      - Added definition for Miscellaneous Options “b4 – b7”
     Section 7.4.3
      - Added Level 03 SETUP if Expanded Currency Mode
     Section 7.4.4
      - Added Level 03 BEGIN SESSION response if Expanded Currency Mode
      - Added Level 03 VEND APPROVED response if Expanded Currency Mode

      - Added Level 03 PERIPHERAL ID response if Expanded Currency Mode
      - Clarified COMMAND OUT OF SEQUENCE definition
      - Added Level 03 REVALUE LIMIT AMOUNT response if Expanded Currency
           Mode
      - Added Level 03 DATA ENTRY REQUEST response if Data Entry Mode
      - Added Level 03 DATA ENTRY CANCEL response if Data Entry Mode
      - Added Level 03 FTL REQ TO RCV response if FTL Mode
      - Added Level 03 FTL RETRY / DENY response if FTL Mode
      - Added Level 03 FTL SEND BLOCK response if FTL Mode
      - Added Level 03 FTL OK TO SEND response if FTL Mode
      - Added Level 03 FTL REQ TO SEND response if FTL Mode
     Section 7.4.5
      - Added Level 03 VEND command if Expanded Currency Mode
      - Added Level 03 VEND APPROVED response if Expanded Currency Mode
     Section 7.4.8
      - Added Vend Failure (from 7.3)
     Section 7.4.10
      - Added Level 03 VEND command if Expanded Currency Mode
     Section 7.4.11 (new)
      - Added complete Level 03 NEGATIVE VEND Request section
     Section 7.4.15 (new)
      - Added complete Level 03 DATA ENTRY Request section
     Section 7.4.16
      - Added Level 03 REVALUE Request command if Expanded Currency Mode
     Section 7.4.17
      - Added Level 03 REVALUE Limit Request command if Expanded Currency
           Mode
     Section 7.4.18
      - Added Level 03 EXPANSION REQUEST ID response if Expanded
           Currency Mode
     Section 7.4.22
      - Added Level 03 EXPANSION ENABLE OPTIONS command
     Section 7.4.23
      - Added Level 03 FTL REQ TO RCV command & responses if FTL Mode
     Section 7.4.24
      - Added Level 03 FTL RETRY / DENY command if FTL Mode
     Section 7.4.25
      - Added Level 03 FTL SEND BLOCK command & response if FTL Mode
     Section 7.4.26
      - Added Level 03 FTL OK TO SEND command if FTL Mode
     Section 7.4.27
      - Added Level 03 FTL REQ TO SEND command & responses if FTL Mode
     Section 7.7
      - Added Example Vend Session #10 (Single Negative Vend)

## Section 8 - Audit Device

     Section 8.1
      - Provided additional address information
     Section 8.3
      - Added FTL POLLed responses
      - Added FTL “b3” option bit
      - Added FTL expansion commands

## Section 9 - Universal Satellite Device

     Section 9.1
      - Provided additional address information
     Section 9.3
      - Added FTL POLLed responses
      - Added FTL “b2” option bit
      - Added FTL expansion commands
     Document Revision History
      - Deleted

Appendix 1 - Currency Codes
    - Added entire section (based on ISO 4217)

Appendix 2 - Battery Operated Card Reader
    - Added entire section

__________________________________________________________________

Version 1.0
Version 1.0 of this specification is the first release of the international Multi-Drop Bus /
Internal Communication Protocol (MDB / ICP). This specification is the culmination
of effort put forth by technical members of NAMA, the EVMMA, and the EVA. The
basis for this specification is the International Multi-Drop Bus Interface Standard
published by NAMA and the Internal Communication Protocol published by the
EVMMA. The NAMA document was originally introduced on October 19, 1993 and later
revised on August 19, 1994, June 20, 1997, and October 15, 1997. The EVMMA
document was adopted in 1994 and later revised in 1995.

The following lists the primary revisions to the original two documents which were
“combined” to create Version 1.0 of the MDB / ICP. In actuality, the NAMA MDB was
the basis of the MDB / ICP with the exception of Section 7 which came from the
EVMMA ICP. Besides typographical corrections and actual feature changes (below),
the entire document was edited to provide a more uniform appearance.

The following lists the primary revisions to the Version 1.0 of the MDB / ICP.

Hardware Specification - Section 4.3
    - Added drawings of the MDB male and female connectors.

Coin Acceptor / Changer - Section 5.3
      - Added Expansion commands:
                 0F-05 Send Current Diagnostic Status
                 0F-06 Send Controlled Manual Fill Report
                 0F-07 Send Controlled Manual Payout Report

Coin Acceptor / Changer - Section 5.5
      - Added coin acceptance and coin payout power requirements for coin
          changers using motorized payout mechanisms.
      - Added note about simultaneously supplying bill validator transport power.

Bill Validator - Section 6.5
      - Added note about simultaneously supplying coin mechanism coin
            acceptance power.

Cashless Payment - Section 7.2.6
    - Added Level 02 Revalue capability.

Cashless Payment - Section 7.3
    - Added Level 02 REVALUE REQUEST.
    - Removed NAK (NCK) response from uninterruptable state and
          unexecutable command descriptions.
    - Eliminated the BUSY response to vend failure sequences.
    - Modified Table 1 per above.

Cashless Payment - Section 7.4.1
    - Further defined the initializing sequence following a RESET command.

Cashless Payment - Section 7.4.2
    - Further defined the Z7 Application Maximum Response Time.
    - Added Z8 – b3 for supporting the VEND/CASH SALE subcommand.

Cashless Payment - Section 7.4.4
    - Begin Session (`03h`) - Added Level 02 Reader Z4-Z10 data.
    - Malfunction/Error (`0Ah`) - Added error code 1100 (refund error).
    - Command Out of Sequence (`0Bh`) - Added Z2 data.
    - Eliminated Busy (`0Ch`) response.
    - Added Level 02 Reader Revalue Approved (`0Dh`) response.
    - Added Level 02 Reader Revalue Denied (`0Eh`) response.
    - Added Level 02 Reader Revalue Limit Amount (`0Fh`) response.

      - Added Level 02 Reader User File Data (`10h`) response.
      - Added Level 02 Reader Time/Date Request (`11h`) response.

Cashless Payment - Section 7.4.10
    - Added Level 01 Reader CASH SALE (`13h`/`05h`) VMC command.

Cashless Payment - Section 7.4.14
    - Added Level 02 Reader Revalue - Request (`15h`/`00h`) VMC command.

Cashless Payment - Section 7.4.15
    - Added Level 02 Reader Revalue – Limit Request (`15h`/`01h`) VMC
          command.

Cashless Payment - Section 7.4.17
    - Obsoleted EXPANSION – Read User File (`17h`/`01h`) VMC command.

Cashless Payment - Section 7.4.18
    - Obsoleted EXPANSION – Write User File (`17h`/`02h`) VMC command.

Cashless Payment - Section 7.4.19
    - Added Level 02 Reader Write Time/Date File (`17h`/`03h`) VMC command.

Cashless Payment - Section 7.5
    - Further defined the non-response time with the “Application Maximum
          Response Time” Z7.

Cashless Payment - Section 7.6 (original ICP Spec)
    - Moved this section (ICP Payment Media Return Button) to Section 7.3.2.

Cashless Payment - Section 7.6 (MDB/ICP Spec)
    - Previously was the ICP 7.7 with no modifications.

                           (this page intentionally left blank)

Introduction

Foreword

This voluntary Standard contains basic requirements for a vending machine
communication interface within the limitations given below and in the General
Information section of this Standard. These requirements are based on sound
engineering principles, research, field experience, and an appreciation of the problems
of manufacture, installation, and use derived from consultation with and information
obtained from manufacturers, users, and others having specialized experience. These
requirements are subject to revision as further experience and investigation may show it
necessary or desired.

NAMA, in performing its functions in accordance with its objectives, does not assume or
undertake to discharge any responsibility of the manufacturer or any other party. The
opinions and findings of NAMA represent its professional judgment given with due
consideration to the necessary limitations of practical operation and state of the art at
the time the NAMA Standard is processed. NAMA shall not be responsible to anyone
for use or reliance upon Standard by anyone. NAMA shall not incur any obligation or
liability for damages, including consequential damages, arising out of or in connection
with the use, interpretation of, reliance upon this Standard.

Standard Review

A complete review of this standard shall be conducted at least every five years to keep
requirements consistent with technology. These reviews shall be conducted by
representatives from industry and user groups on the NAMA Vending Technology
Standards Committee at that time.

                            (this page intentionally left blank)

Section 1
   General Information

#### 1.1 Introduction

This document defines a serial bus interface for electronically controlled vending
machines. The interface is a 9600 baud Master-Slave arrangement where all
peripherals are Slaves to a Master controller.

The intent of this document is to standardize vending machines that employ electronic
control (traditionally known as vending mechanism controller - VMC) so that all vending
and peripheral equipment communicates identically.

It should be noted that this document is a vending machine interface / protocol
specification and not a vending machine system specification. Each machine
manufacturer should provide a specification on the overall operation of the machine.

#### 1.2 Operational and Application Notes

The serial bus, or Multi-Drop Bus (MDB) is configured for Master-Slave operation.
There is one Master with capability of communicating with up to thirty-two peripherals.
The Master is defined as the Vending Machine Controller (VMC).

Each peripheral is assigned a unique address and command set. The master will “poll”
the Bus for peripheral activity. That is, each peripheral is asked for activity, and
responds with either an acknowledge, negative acknowledgment, or specific data
dependent on its current activity. If a peripheral does not respond within a predefined
time, (t-non-response as defined in the peripheral sections) it is assumed that it is not
present on the Bus.

Bus interference, or “crashes” are prevented because each peripheral only responds
upon being polled. Since there is only one master, and all communication is initiated by
the Master, Bus “crashes” are easily precluded.

All peripherals will recognize a disable command, or commands, sent by the Master.
This allows for disabling of individual peripherals for various reasons, for example,
power management techniques.

Error checking and correction is accomplished by using checksums (CHK) and a
retransmit command.

#### 1.3 Levels and Options

Since the introduction of the earliest Multi-Drop Bus specification, functional levels and
operational options have been established for most of the peripherals on the MDB/ICP
interface. These have provided the capability for new features to be implemented as
new requirements and features were needed for the international vending industry.

#### 1.3.1 Levels

Levels of peripheral functionality were established when a major change occurred in the
peripheral that added extended commands and responses. Due to potential conflicts
between a VMC level and a peripheral level, neither the VMC nor the peripheral should
issue a command or reply with a response that is not supported by the other device.

The VMC must initially determine (via the appropriate STATUS or SETUP command)
the level of a peripheral before determining which commands it can issue to that device.
A VMC must only send commands that are supported by the peripheral. For
example, a Level 3 command may only be issued to a Level 3 or higher peripheral and
must not be issued to a Level 1 or 2 peripheral.

The Cashless Payment and the Universal Satellite Device can also learn the respective
level of the VMC for that device. This information is sent via the SETUP command. It
is the responsibility of the peripheral to only send responses that are supported
by the VMC. For example, a Level 3 response may only be sent to a Level 3 or higher
VMC and must not be sent to a Level 1 or 2 VMC. Effectively, the VMC and peripheral
should support the highest common level.

For total compatibility, VMCs and peripherals should support all lower levels. For new
designs after July 2000, it is strongly recommended that VMCs and peripherals
must support all lower levels. Commercial or regional issues may cause machine or
peripheral manufacturers to implement only specific levels; however, this is a decision
(and risk) made by the machine or peripheral manufacturer.

#### 1.3.2 Options

Options were established in the peripherals to provide various additional operational
features that may be required for specific vending applications. As the name implies,
these features are “above and beyond” the standard core of required functionality.

At power on and after a Bus Reset or a RESET command, all options are
disabled. During the initialization command sequences, the VMC determines the
optional features supported by the peripherals. The VMC will then enable the
features it is going to use. Until the feature is enabled, it is the responsibility of the
peripheral to ignore feature specific commands and not respond with feature specific
responses.

#### 1.3.3 Currently Established Levels and Options

The following table provides a brief description of each of the currently established
levels and options of the various MDB/ICP peripherals. Please refer to the specific
sections for each device for more detailed information.

| Peripherals | Levels | Options | Description |
|---|---|---|---|

| Coin | Changer | 1 | n/a | Never released |  |  |
|---|---|---|---|---|---|---|
|  |  | 2 | none | Supports standard commands |  |  |
|  |  | 3 | below | Supports Expansion ID command | and | optionally |

                                       supports commands for features below
| b0 | Alternative Payout Method |  |
|---|---|---|
| b1 | Extended Diagnostics |  |
| b2 | Controlled Manual Fill and | Payout |
| b3 | File Transport Layer (FTL) |  |

| Bill | Validator | 1 | none | Supports | standard | commands | and | Expansion | ID |
|---|---|---|---|---|---|---|---|---|---|

                                       command without options
| 2 | below | Supports | expansion | ID | command | with | options |
|---|---|---|---|---|---|---|---|

                                       and optionally supports commands for features
                                       below
| b0 | File | Transport | Layer | (FTL) |
|---|---|---|---|---|
| b1 | Bill | Recycling |  |  |

| Cashless |  | 1 | below | Supports | standard commands and Expansion | ID |
|---|---|---|---|---|---|---|
| Device #1 | & #2 |  |  | command. | Readers do not have revaluation |  |

                                       capability
| b0* | Reader | is capable of restoring | funds to | card |
|---|---|---|---|---|
| b1* | Reader | is multivend capable |  |  |
| b2* | Reader | has a display available |  |  |
| b3* | Reader | supports VEND-CASH SALE | command |  |

                                          *bits in the SETUP-Config command
| 2 | above | Supports | Revalue, | Time/Date, | Read | User | File |
|---|---|---|---|---|---|---|---|

                                       (obsolete), and Write User File (obsolete)
                                       commands

| Peripherals | Levels | Options | Description |
|---|---|---|---|

| Cashless |  | 3 | above | Supports expansion ID command with options |
|---|---|---|---|---|
| Device #1 & | #2 |  | & | and optionally supports commands for features |
| (continued) |  |  | below | below (bits in the Level 3 Expansion ID |

                                          command)
| b0** | File Transport Layer (FTL) |
|---|---|
| b1** | 16 or 32 Bit Monetary Format |
| b2** | Multi Currency / Multi Lingual |
| b3** | Negative Vend |
| b4** | Data Entry |
| b5** | Always Idle Session |

                                          **bits in the Level 3 Expansion ID command

| Communications | 1 | none | Obsolete | (former Audit Unit) |  |
|---|---|---|---|---|---|
| Gateway | 2 | none | Obsolete | (former Audit Unit) |  |
|  | 3 | below | Supports | Expansion ID command | and |

                                          optionally supports commands for features
                                          below
| b0 | File Transport Layer | (FTL) |
|---|---|---|
| b1 | Verbose Mode |  |
| b2 | Expansion Time/Date |  |

| Universal |  | 1 | below | Supports all basic commands and optionally |
|---|---|---|---|---|
| Satellite | Device |  |  | supports commands for features below |
| (USD) |  |  | b0 | USD is capable of storing and controlling |

                                          pricing
| b1 | USD is capable | of selecting | items | to | vend |
|---|---|---|---|---|---|
| b2 | File Transport | Layer (FTL) |  |  |  |

| Coin | Hopper or | 1 | below | Supports Expansion ID command and |
|---|---|---|---|---|
| Tube | - Dispenser |  |  | optionally supports commands for features |

                                          below
| b0 | File | Transport | Layer | (FTL) |
|---|---|---|---|---|

Section 2
   Communication Format

#### 2.1 Byte Format

| Baud | Rate: | 9600 | NRZ |
|---|---|---|---|

| Serial | Bit | Format: | 1 | Start | Bit |
|---|---|---|---|---|---|

                              8 Data Bits
                              1 Mode Bit
                              1 Stop Bit

                              11 Bits Total

## Lsb                                                  Msb

| Start | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | Mode | Stop |
|---|---|---|---|---|---|---|---|---|---|---|

Mode Bit: Master-to-Peripheral

The mode bit differentiates between ADDRESS bytes and DATA bytes. ADDRESS
bytes must be read by all peripherals, DATA bytes are only read by the peripheral that
has been addressed.

The mode bit is set (logic one) to indicate an ADDRESS byte, and not set (logic zero) to
indicate a DATA byte.

Mode Bit: Peripheral-to-Master

The mode bit must be set on the last byte sent when data is sent from a Slave to the
Master.

#### 2.2 Block Format

Master-to-Peripheral

A Communication Block for Master-to-Slave transmissions is defined as an Address
byte, optional data bytes, and a CHK byte. A block is limited to a maximum of thirty-six
(36) bytes.

The upper five bits (MSB) of the Address Byte will be used for addressing. That is, bits
7,6,5,4,3 of the previous byte description will be used for addressing.

The lower three bits (i.e. 2,1,0) of the Address Byte will contain peripheral specific
commands. This will allow up to eight instructions to be embedded in the first byte of a
block.

The VMC Master will respond to data from a peripheral with an Acknowledgment
(ACK), Negative Acknowledgment (NAK), or Retransmit (RET). These are defined later
in the document. The 5 mS time-out (t-response) described in the Bus Timing section
of this document is the equivalent of a NAK.

If the addressed Slave does not respond within the 5 mS time-out (silence), the Master
may repeat the same command, or send a different command, until it receives an
answer or until the end of the Non-Response time, as defined in the peripheral
sections. See Example in 2.5D. The RESET command should not be used as a
recovery method to a 5 mS time-out (t-response) until after exceeding the Non-
response time. The VMC may send commands to any other peripheral during this time.

Peripheral-to-Master

A Communication Block for Slave-to-Master transmissions consists of either a data
block and a CHK byte, a acknowledgment (ACK), or a negative acknowledgment

## (Nak).

The 5 mS time-out (t-response) described in the Bus Timing section of this document
is the equivalent of a NAK command. In addition, it is recommended that the peripheral
use this time-out as the NAK when a reception error of the ADDRESS byte occurs.
This will prevent several peripherals from trying to simultaneously respond with a NAK.

A data block consists of one or more data bytes followed by a CHK byte. The CHK byte
is defined later in this document.

The data block and CHK byte are limited to a maximum size of 36 bytes.

A CHK byte is not required when a peripheral responds with NAK or ACK byte. ACK
and NAK are defined later in this document.

The peripheral must set the mode bit on the last byte sent to signify end of
transmission. This will be either the CHK byte of a block, a NAK byte, or an ACK byte.
The mode bit must not be set except for the conditions above.

A peripheral response of ACK or NAK signifies the end of the exchange.

When a peripheral responds with a data block, the VMC must respond with an ACK,
NAK or RET. If the Master cannot respond within the 5 mS time-out (t-response) the
peripheral must repeat the data block, or append it, at the next possible occasion (i.e. to
a later POLL). The same behavior is to apply when the Master responds with NAK.

CHK Byte

A CHK byte must be sent at the end of each block of data. The CHK byte is a
checksum calculated by adding the ADDRESS byte and all DATA bytes. The CHK byte
is not included in the summation. The carry bit for CHK additions is ignored since the
CHK byte is limited to eight bits.

The following example shows a CHK byte calculation for a possible response to a
STATUS command sent to a USA changer slave. See section 5 for details of byte
meanings.

              02H Changer feature level
              00H Country code for USA
              01H Country code for USA
              05H Coin scaling factor
              02H Decimal place
              00H Coin type routing
              07H Coin type routing
              01H Coin type 0 has value of 1 scaling factor
              02H Coin type 1 has value of 2 scaling factor
              05H Coin type 2 has value of 5 scaling factor
              14H Coin type 3 has value of 20 scaling factor
              FFH Coin type 4 is a token
              12CH Therefore the CHK byte would be equal to 2CH

A checksum will be performed on all full blocks of communication. A checksum will not
be performed on ACK, NAK, or RET bytes.

Response Codes

The following codes are reserved for the ACK, NAK and RET bytes:

| ACK | 00H | (acknowledgment/checksum | correct) |
|---|---|---|---|

| RET | AAH | (Retransmit | the | previously | sent | data. |
|---|---|---|---|---|---|---|

                                 Only the VMC can transmit this byte)

| NAK | FFH | (Negative | acknowledge) |
|---|---|---|---|

                                    The VMC and peripheral must also recognize the 5
                                    mS time-out (t-response) as a NAK.

| NOTE: | To | improve | system | reliability | it | is | recommended | that | when | receiving | ACK, |
|---|---|---|---|---|---|---|---|---|---|---|---|

              NAK, or RET the receiving device counts the number of bits set in the
              byte. This method will require at least two bit errors in the byte before the
              byte can be mis-interpreted.

Bus Reset

The VMC may reset all peripherals by pulling the transmit line “active” for a minimum of
100 mS. This informs all peripherals to abort any activity and return to its power-on
reset state. Details of this state for each peripheral are provided in later sections of this
document. It is recommended that the VMC re-initialize each peripheral after this type
of reset.

#### 2.3 Peripheral Addresses

The addresses below are defined. Note again that the bits shown are the upper five bits
(7,6,5,4,3) of the Address Byte and will be used for all addressing including the File
Transport Layer described in Section 2.6. The lower three bits (2,1,0) are used for the
command.

| Address | Definition |
|---|---|

| 00000xxxB | (00H) | Reserved for VMC |
|---|---|---|
| 00001xxxB | (08H) | Changer |
| 00010xxxB | (10H) | Cashless Device #1 |
| 00011xxxB | (18H) | Communications Gateway |
| 00100xxxB | (20H) | Display |
| 00101xxxB | (28H) | Energy Management System |
| 00110xxxB | (30H) | Bill Validator |
| 00111xxxB | (38H) | Reserved for Future Standard Peripheral |
| 01000xxxB | (40H) | Universal Satellite Device #1 |
| 01001xxxB | (48H) | Universal Satellite Device #2 |
| 01010xxxB | (50H) | Universal Satellite Device #3 |
| 01011xxxB | (58H) | Coin Hopper or Tube – Dispenser 1 |
| 01100xxxB | (60H) | Cashless Device #2 |
| 01101xxxB | (68H) | Age Verification Device |
| 01101xxxB | (70H) | Coin Hopper or Tube – Dispenser 2 |
| 01111xxxB | (78H) | Reserved for Future Standard Peripherals |
| . | . | . |
| . | . | . |
| . | . | . |
| 11011xxxB | (D8H) | Reserved for Future Standard Peripherals |
| 11100xxxB | (E0H) | Experimental Peripheral #1 |
| 11101xxxB | (E8H) | Experimental Peripheral #2 |
| 11110xxxB | (F0H) | Vending Machine Specific Peripheral #1 |
| 11111xxxB | (F8H) | Vending Machine Specific Peripheral #2 |

Experimental Peripheral Addresses
Experimental Peripheral addresses 11100xxxB (E0H) and 11101xxxB (E8H) are
reserved for use by manufacturers when designing and field testing potential new
MDB/ICP devices. These addresses are temporary and once the new device is
approved by NAMA and the EVA, the device will be assigned a different permanent
peripheral address. Use of the Experimental Peripheral addresses shall be limited to
“in house” testing and “closed site” field trials. Manufacturers must understand that any
devices in the field with Experimental Peripheral addresses must be recalled or updated
to the permanent address if the device is approved by NAMA and the EVA. If not
approved by NAMA and the EVA, the devices must be recalled or have their addresses
changed to the Vending Machine Specific peripheral addresses described below.

Vending Machine Specific Peripheral Addresses
Vending Machine Specific peripheral addresses (addresses 11110xxxB (F0H) and
11111xxxB (F8H)) are reserved for Non-Standard or proprietary applications. These
devices are allowed a unique set of commands.

All other peripherals are defined as Standard devices. These peripherals must follow
the specifications to ensure compatibility between manufacturers.

#### 2.4 Software Operational Rules

#### 2.4.1 Power Budget

The VMC must regulate the power budget. That is, peripherals must be enabled and
disabled dependent on power availability. The power bus is defined later in this
document.

#### 2.4.2 Bytes

During multi-byte messages the most significant byte is sent first.

      Any bytes within a command or response that are not specifically defined
      should be left in a 0 state. For Level 03 or lower coin mechanisms, Level
      01 bill validators, and Level 01 card readers, this is not a requirement but
      a suggestion.

#### 2.4.3 Polling

The following are recommendations for the methods of VMC to peripheral software
operation.

      Each peripheral should be polled every 25-200 milliseconds. This can be done
      by the POLL command or any other appropriate command.

      If a peripheral has not responded to a poll for its maximum Non-Response time,
      the VMC should continue to poll the peripheral at least every ten seconds with a
      RESET command. (See Example G in Section 2.5).

#### 2.4.4 Levels

Due to potential conflicts between a VMC level and a peripheral level, neither the VMC
nor the peripheral should issue a command or reply with a response that is not
supported by the other device.

The VMC must initially determine (via the appropriate STATUS or SETUP command)
the level of a peripheral before determining which commands it can issue to that device.
A VMC must only send commands that are supported by the peripheral. For
example, a Level 3 command may only be issued to a Level 3 or higher peripheral and
must not be issued to a Level 1 or 2 peripheral.

The Cashless Payment and the Universal Satellite Device can also learn the respective
level of the VMC for that device. This information is sent via the SETUP command. It
is the responsibility of the peripheral to only send responses that are supported

by the VMC. For example, a Level 3 response may only be sent to a Level 3 or higher
VMC and must not be sent to a Level 1 or 2 VMC. Effectively, the VMC and peripheral
should support the highest common level.
For total compatibility, VMCs and peripherals should support all lower levels. For new
designs after July 2000, it is strongly recommended that VMCs and peripherals
must support all lower levels. Commercial or regional issues may cause machine or
peripheral manufacturers to implement only specific levels; however, this is a decision
(and risk) made by the machine or peripheral manufacturer.

#### 2.5 Typical Session Examples

| A.       The | diagram | below | represents | a typical | transmission | when | a peripheral | is | idle. |
|---|---|---|---|---|---|---|---|---|---|

VMC:

## Add*            Chk

Peripheral:

                                     ACK*

| B.       The | diagram | below | represents | a typical | transmission | when | a peripheral | has | data |
|---|---|---|---|---|---|---|---|---|---|

         to return.
VMC:

## Add*            Chk                                            Ack

Peripheral:

## Dat            Dat         Chk*

| C.       The | diagram | below | represents | a typical | transmission | when | the | VMC | has | data | to |
|---|---|---|---|---|---|---|---|---|---|---|---|

         send.
VMC:

## Add*            Dat           Dat          Chk

Peripheral:

                                                                 ACK*
*Indicates mode bit set

| D.       The | diagram | below | represents | a typical | transmission | when | the | VMC | determines |
|---|---|---|---|---|---|---|---|---|---|

         a CHK is not correct. The VMC will respond one of two ways:

         Send a NAK to the peripheral to indicate that the information was not received
         correctly then perform other tasks. Note: When the Master answers with NAK (or
         silence which is treated equally) the slave has to repeat the response, in order to
         ensure the execution of the response (i.e. coin reception etc.).

                                              OR

         The VMC may send a retransmit (RET) command alerting the peripheral to
         retransmit the previously sent data.

VMC:

| ADD* | DAT | CHK | RET | ACK |
|---|---|---|---|---|

Peripheral:

## Dat       Dat         Chk*         Dat    Dat         Chk*

*Indicates mode bit set.

| E.       This | diagram | represents | a situation | where | the | peripheral | does | not | respond | within |
|---|---|---|---|---|---|---|---|---|---|---|

         the 5 mS time-out (t-response).

VMC:

## Add*           Chk                 Add*          Chk

Peripheral:

| [silence…] | ACK* |
|---|---|

| F.       This | diagram | represents | a situation | where | the | peripheral | does | not | respond | to |
|---|---|---|---|---|---|---|---|---|---|---|

         command and after its maximum Non-Response time, is reset by the controller.

| Controller | Peripheral | Comment |
|---|---|---|

| Command | X           |  |  |  |
|---|---|---|---|---|
|  |  | Response | Normal | response |

| Command | Y           |  |  |  |
|---|---|---|---|---|
|  |  | [silence…] | No | response |

| Command | Y           |  |  |  |
|---|---|---|---|---|
|  |  | [silence…] | No | response |

| Command | Y           |  |  |  |
|---|---|---|---|---|
|  |  | [silence…] | No | response |

                                                        Peripheral does not response
                                                        within its allocated Non-
                                                        Response Time.

| RESET |  |  | Software Reset |
|---|---|---|---|
|  |  | [silence…] | Peripheral in initialization |

                                                        routine

## Reset              

|  | ACK | Peripheral | operational | again |
|---|---|---|---|---|

## Poll               

|  | JUST | RESET | Peripheral | indicates | finished |
|---|---|---|---|---|---|

                                                        RESET processing

## Ack                

                                                        Peripheral initialization
                                                        sequence is performed as
                                                        recommended in each
                                                        peripheral section.

  G. This diagram represents a situation where the peripheral is disconnected or goes
     offline. The controller should send a RESET command every 10 seconds to
     determine if, and when, the peripheral becomes active again.

| Controller | Peripheral | Comment |
|---|---|---|

| Command | X           |  |  |  |
|---|---|---|---|---|
|  |  | Response | Normal | response |

| Command | Y           |  |  |  |
|---|---|---|---|---|
|  |  | [silence…] | No | response |

| Command | Y           |  |  |  |
|---|---|---|---|---|
|  |  | [silence…] | No | response |

| Command | Y           |  |  |  |
|---|---|---|---|---|
|  |  | [silence…] | No | response |

                                                     Peripheral does not response
                                                     within its allocated Non-
                                                     Response Time.

| RESET |  |  | Software Reset |
|---|---|---|---|
|  |  | [silence…] | Peripheral offline |

| RESET |  |  | Software Reset |
|---|---|---|---|
|  |  | [silence…] | Peripheral offline |

                                                     Wait 10 seconds

## Reset              

|  | [silence…] | Peripheral | offline |
|---|---|---|---|

                                                     Wait 10 seconds

## Reset              

| [silence…] | Peripheral | offline |
|---|---|---|

                                                     Wait 10 seconds

## Reset              

| [silence…] | Peripheral | offline |
|---|---|---|

#### 2.6 File Transport Layer

The File Transport Layer (FTL) provides a method to send and/or receive high level
information between peripherals or between a peripheral and the VMC. It is not
intended to be used for standard vending credit and control functions. An example
would be loading new validation parameters into a coin changer or bill validator.

Since the MDB/ICP interface is “driven” by the VMC, it has to be a network manager for
all FTL data transfers. It acts as a temporary mailbox and data switch for FTL blocks;
however, the information that is sent via FTL does not have to be interpreted by the
VMC. The VMC simply uses the destination and source address information provided
in the MDB/ICP command and response structure to forward the data to the proper
recipient.

#### 2.6.1 FTL Process Overview

If a peripheral needs to transfer data to another peripheral (or the VMC):
- The VMC must poll the peripheral,
- The peripheral must answer with a “REQUEST TO SEND”,
- The VMC must get approval to forward data (if necessary),
- The VMC requests the first data block,
- The VMC ACKs the first block and forwards to destination,
- The process repeats until all blocks are sent.

If the VMC needs to transfer data to a peripheral:
- The VMC must send a “REQUEST TO SEND”,
- The peripheral approves or denies the transfer request,
- If approved, the VMC sends the first data block,
- The peripheral ACKs the first data block,
- The process repeats until all blocks are sent.

If a peripheral (A) needs to request a transfer of data from another peripheral (B):
- The VMC must poll the peripheral A,
- Peripheral A must send a “REQUEST TO RECEIVE”,
- The VMC forwards the request to peripheral B,
- Peripheral B decides to honor the request or not,
- If approved, peripheral B sends the first data block,
- The VMC forwards the data block to peripheral A,
- The process repeats until all blocks are sent.

#### 2.6.2 FTL Detailed VMC Operation

The VMC must act as a network manager, it is responsible for checking peripheral
status and managing network resources as described below, it must:
- Be aware of which peripherals are active and support the FTL. If a file transfer is
    requested involving a peripheral that does not support it, the VMC should deny the
    transfer using RETRY/DENY defined later.
- Poll peripherals to become aware that a data transfer is requested.
- Read data blocks from selected peripherals.
- If VMC receives a NAK, it should attempt to finish current command/response up to
    5 times. After that, it should abort file transfer as defined by the protocol.
- Send data blocks to destination device, if not the VMC itself.
- Repeat these steps for all data blocks, as needed.

#### 2.6.3 FTL General Operation

- The FTL "session" would transfer a "file" using several "blocks". The "Dest" and
    "Src" are switched by the VMC directing each block to its destination.
- All responses can be sent immediately after receipt of command or the command
    can be ACK’ed and the response sent in a delayed fashion (meeting all appropriate
    time-outs). However, FTL responses must NOT be combined with responses to any
    other commands, at any time.
- File transfers less than 256 blocks are terminated by sending an empty data file
    (SEND BLOCK with no data). File transfers of exactly 256 blocks are terminated by
    block #FE followed by block #FF.
- It is recommended that files larger than one block:
         1) Include a CRC in their data. The transport layer is not responsible for
         checking for correct CRCs.
         2) Include a time out mechanism to prevent system dead locks. The transport
         layer is not responsible for checking for dead locked file transfers.
- To prevent a system dead lock, the VMC must poll other peripherals during all data
    transfers and service them accordingly.
- Since the VMC is not knowledgeable about the contents of the file transfer it should
    not disable any peripherals due to a transfer request. This will be the responsibility
    of the peripherals themselves. They may internally disable and report so to the VMC
    if possible, or they may just stop responding to the VMC until ready. The latter may
    cause the VMC to try to reset the peripheral.

#### 2.6.4 FTL Command and Response Sets For All Components

The table below defines the VMC commands and peripheral responses that occur
during an FTL data transfer. Note that the peripheral responses can either be
immediate to the VMC’s command or delayed and provided to a subsequent POLL.
Definitions are provided on the following page.

| Command | /       VMC | Resp | Source | Data | (bytes) | Destination | Response |
|---|---|---|---|---|---|---|---|

                     1
| Response | Cmd |  |  |  |  |
|---|---|---|---|---|---|
| REQ TO | α7/FE | 1F | Dest | (1) | OK TO SEND or |
| SEND |  |  | Src | (1) | RETRY/DENY |
|  |  |  | File ID | (1) |  |
|  |  |  | Length | (1) |  |
|  |  |  | Control | (1) |  |
| OK TO SEND | α7/FD | 1E | Dest | (1) | SEND BLOCK (repeated |
|  |  |  | Src | (1) | until whole file is |

                                                           transferred)
| SEND BLOCK | α7/FC | 1D | Dest |  |  | (1) | ACK |
|---|---|---|---|---|---|---|---|
|  |  |  | Block # |  |  | (1) |  |
|  |  |  | Data | (1 | to | 31) |  |
| RETRY/DENY | α7/FB | 1C | Dest |  |  | (1) | ACK |
|  |  |  | Src |  |  | (1) |  |
|  |  |  | Retry delay |  |  | (1) |  |
| REQ TO RCV | α7/FA | 1B | Dest |  |  | (1) | SEND BLOCK (repeated |
|  |  |  | Src |  |  | (1) | until whole file is |
|  |  |  | File ID |  |  | (1) | transferred) or |
|  |  |  | Max Length |  |  | (1) | RETRY/DENY |
|  |  |  | Control |  |  | (1) |  |

Note 1: The α7 represents the address of the destination device (defined in
        Section 2.3) logically OR’d with a hexadecimal `0x07`.

| Dest | 1 | byte |
|---|---|---|

       The destination address of the peripheral where the data block (not the whole
       file) is being sent to. All addresses refer to the standard MDB defined peripheral
       addresses as defined in Section 2.3. Note that 00000xxx (00H) will be used for
       the VMC. Examples are a changer (08H), audit system (18H), bill validator
       (30H), and universal satellite device #2 (48H).

| Src | 1 | byte |
|---|---|---|

       The source address of the peripheral where the data block (not the whole file)
       is being sent from. All addresses refer to the standard MDB defined peripheral
       addresses as defined in Section 2.3. Note that 00000xxx (00H) will be used for
       the VMC. Examples are the same as in the Dest above.

| File | ID | 1 | byte |
|---|---|---|---|

       The type of information desired. NAMA will maintain a list of standard file ID’s
       and a definition of what each file type means. Note that if a device responds with
       a “Retry delay” of FFH it should be interpreted that this device does not support
       the requested function.

       Currently defined file IDs include:

       00H: Manufacture ID information. This file must start with the manufactures
            three character manufactures code, anything after that would be up to the
            manufacture to define.

       01H: DTS defined file. This file must follow the format defined in the EVA-DTS
            standard. This would include the DXS record as well as all data up to and
            including the DXE record.

       0F0H to 0FFH: This range of files may be used for Manufacturer Specific
             information. The content and format of these files are left up to the
             manufacturer to define.

       Additional ID proposals must be evaluated by the NAMA MDB/ICP technical
       standard committee.

| (Max) | Length | 1 | byte |
|---|---|---|---|

       The total number of blocks that will (can) be included in the entire file. This byte
       should be used as a counter to determine the amount of data blocks to be
       transferred.

| Control | 1 | byte |
|---|---|---|

      This byte contains information that can be used by the VMC and peripherals to
      determine how the data transfer is conducted. Included controls are:

| b0: | Reset | after | transfer. | The | receiving | peripheral | should | reset | itself | after | the |
|---|---|---|---|---|---|---|---|---|---|---|---|

             file transfer is complete.
| b1: | End | of | File. | The | last | block | of | the | current | FTL | session | contains | the | end | of |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

             this file. If clear (=0), then another FTL session will follow with additional
             blocks. If set (=1), then this is the last (or only) FTL session to be sent.
      b2 - b7: Not used, must be set to 0

| Block | #                                                                          1 | byte |
|---|---|---|

      The sequential number of this block, within the total file, that is being
      requested/sent. All data blocks must be identified by a block number, counting
      up from 0 (first block) to 255.

| Data | Block | 1 | to | 31 | byte(s) |
|---|---|---|---|---|---|

      The actual data portion of the block. All data must fit into a 31 byte, or less,
      string. The standard MDB CHK byte will signify the end of block. (Peripherals will
      have to use inter-byte time out when receiving blocks from the VMC.) Knowledge
      of the contents of this data is only required by the source and destination
      devices.

| Retry | Delay | 1 | byte |
|---|---|---|---|

      A time delay that the sender should wait before trying to re-send the entire data
      file again. If a device is not capable of receiving a file in its current state, this byte
      should represent the number of seconds before it will be ready to receive the
      data. If the device simply refuses to accept the file it must answer with a “Retry
      Never” signified by a 00H retry delay. If the device is not present, block
      synchronization is lost, or other failure mode arises a “Retry Never” should be
      used to abort/deny the current file transfer.

File Transport Layer Examples

Below are examples of data transfers between the VMC and a peripheral or between
two different peripherals via the VMC.

## Successful Transfer – Vmc To Peripheral A

| Peripheral | A | VMC | Peripheral | B               Comments |  |
|---|---|---|---|---|---|
|  |  | REQ TO SEND |  | Request to | send |
|  |  | (α7/FE) |  | “n” blocks |  |

## Ok To Send   

(1E)

##  Ack

##  Send Block

| (α7/FC) | Repeated | “n” | times |
|---|---|---|---|

## Ack          

## Denied Transfer – Vmc To Peripheral A

| Peripheral | A    VMC | Peripheral | B               Comments |
|---|---|---|---|

##  Req To Send

                (α7/FE)
| RETRY/00 | (1C) |                                               Denied |
|---|---|---|

##  Ack

## Successful Request – Vmc To Peripheral A

| Peripheral | A   VMC | Peripheral | B                Comments |
|---|---|---|---|

              POLL (varies)
| REQ TO | RCV |  | Request | receive | “n” |
|---|---|---|---|---|---|
| (1B) |  |  | blocks |  |  |

##  Ack

##  Send Block

| (α7/FC) | Repeated | “n” | times |
|---|---|---|---|

## Ack          

## Denied Request – Vmc To Peripheral A

| Peripheral | A     VMC | Peripheral | B               Comments |
|---|---|---|---|

              POLL (varies)
| REQ TO | RCV |  | Request | receive | “n” |
|---|---|---|---|---|---|
| (1B) |  |  | blocks |  |  |

##  Ack

|  | RETRY/00 | Denied |
|---|---|---|

                 (α7/FB)

## Ack          

## Vmc Aborted Transfer – Vmc To Peripheral A

| Peripheral | A | VMC | Peripheral | B        Comments |  |
|---|---|---|---|---|---|
|  |  | REQ TO SEND |  | Request to | send |
|  |  | (α7/FE) |  | “n” blocks |  |

## Ok To Send   

(1E)

##  Ack

##  Send Block

| (α7/FC) | Repeated | “n” | times |
|---|---|---|---|

## Ack          

|  | RETRY/00 | Aborted! |
|---|---|---|

               (α7/FB)

## Ack          

## Peripheral Abort Transfer – Vmc To Peripheral A

| Peripheral | A | VMC | Peripheral | B   Comments |  |
|---|---|---|---|---|---|
|  |  | REQ TO SEND |  | Request to | send |
|  |  | (α7/FE) |  | “n” blocks |  |

## Ok To Send   

(1E)

##  Ack

##  Send Block

                (α7/FC)
| RETRY/00 |  | Aborted! |
|---|---|---|

(1C)

##  Ack

## Successful Transfer – Peripheral A To Vmc

| Peripheral | A   VMC | Peripheral | B        Comments |
|---|---|---|---|

              POLL (varies)
| REQ TO | SEND |  | Request to | send |
|---|---|---|---|---|
| (1F) |  |  | “n” blocks |  |

##  Ack

##  Ok To Send

               (α7/FD)
| SEND | BLOCK |  | Repeated | “n” | times |
|---|---|---|---|---|---|

(1D)

##  Ack

## Denied Transfer – Peripheral A To Vmc

| Peripheral A |  | VMC |  | Peripheral | B      Comments |  |
|---|---|---|---|---|---|---|
|  |  | POLL | (varies) |  | Request to | send |
| REQ TO SEND |  |  |  |  | “n” blocks |  |

(1F)

##  Ack

|  | RETRY/00 | Denied |
|---|---|---|

                (α7/FB)

## Ack           

## Successful Transfer – Peripheral A To Peripheral B

| Peripheral | A   VMC | Peripheral | B  Comments |
|---|---|---|---|

              POLL (varies)
| REQ TO | SEND |  | Request to | send |
|---|---|---|---|---|
| (1F) |  |  | “n” blocks |  |

##  Ack

## Req To Send    

               (1F) (α7/FE)

##  Ok To Send

                                 (1E)

## Ack            

##  Ok To Send

               (α7/FD)
| SEND | BLOCK |  | Repeated | “n” | times |
|---|---|---|---|---|---|

(1D)

##  Ack

## Send Block     

               (α7/FC)

##  Ack

## Denied Transfer – Peripheral A To Peripheral B

| Peripheral | A    VMC | Peripheral | B      Comments |
|---|---|---|---|

               POLL (varies)
| REQ TO | SEND |  | Request to | send |
|---|---|---|---|---|
| (1F) |  |  | “n” blocks |  |

##  Ack

## Req To Send     

                (1F) (α7/FE)
|  | RETRY/00 | (1C) | Denied |
|---|---|---|---|

## Ack             

##  Retry/00

                (α7/FB)

## Ack           

## Successful Request - Peripheral A To Peripheral B

| Peripheral | A   VMC | Peripheral | B  Comments |
|---|---|---|---|

              POLL (varies)
| REQ TO | RCV |  | Request | receive | “n” |
|---|---|---|---|---|---|
| (1B) |  |  | blocks |  |  |

##  Ack

## Req To Rcv     

               (α7/FA)
|  | SEND | BLOCK | Repeated | “n” | times |
|---|---|---|---|---|---|

                                  (1D)

## Ack            

##  Send Block

               (α7/FC)

## Ack          

## Denied Request – Peripheral A To Peripheral B

| Peripheral | A     VMC | Peripheral | B      Comments |
|---|---|---|---|

              POLL (varies)
| REQ TO | RCV |  | Request | receive | “n” |
|---|---|---|---|---|---|
| (1B) |  |  | blocks |  |  |

##  Ack

## Req To Rcv     

                 (α7/FA)
|  | RETRY/00 | (1C) | Denied |
|---|---|---|---|

## Ack            

##  Retry/00

                 (α7/FB)

## Ack          

## Peripheral A Transfer To Peripheral B – Aborted By A

| Peripheral | A    VMC | Peripheral | B   Comments |
|---|---|---|---|

               POLL (varies)
| REQ TO | SEND |  | Request to | send |
|---|---|---|---|---|
| (1F) |  |  | “n” blocks |  |

##  Ack

## Req To Send    

                (α7/FE)

##  Ok To Send

                                 (1E)

## Ack            

##  Ok To Send

                (α7/FD)

## Send Block    

(1D)

##  Ack

## Send Block     

                (α7/FC)

##  Ack

                        .
| . | Repeated | “n” | times |
|---|---|---|---|

                        .
               POLL (varies)
| RETRY/00 | (1C) |                                  Aborted! |
|---|---|---|

##  Ack

## Retry/00       

                (α7/FB)

##  Ack

## Peripheral A Transfer To Peripheral B – Aborted By B

| Peripheral | A    VMC | Peripheral | B   Comments |
|---|---|---|---|

               POLL (varies)
| REQ TO | SEND |  | Request to | send |
|---|---|---|---|---|
| (1F) |  |  | “n” blocks |  |

##  Ack

## Req To Send    

                (α7/FE)

##  Ok To Send

                                 (1E)

## Ack            

##  Ok To Send

                (α7/FD)

## Send Block    

(1D)

##  Ack

## Send Block     

                (α7/FC)

##  Ack

                         .
| . | Repeated | “n” | times |
|---|---|---|---|

                         .

##  Poll

                (varies)REQ
                BLOCK (α7/FD)

## Send Block    

(1D)

##  Ack

## Send Block     

                (α7/FC)
                                RETRY/00 (1C) Aborted!

## Ack            

##  Retry/00

                (α7/FB)

## Ack           

Section 3
  Bus Timing

#### 3.1 Timing Definitions

| Baud | rate | = | The | rate | of | bit | transfer | per | second. |
|---|---|---|---|---|---|---|---|---|---|

| t | = | The maximum time | allowed between |
|---|---|---|---|
| inter-byte | (max.) | bytes in a block | transmission. |

| t | = | The maximum time any device, |  |
|---|---|---|---|
| response | (max.) | master or peripheral, will take | to |

                                        respond to a valid communication.

| t |  | =              The minimum | time of the Bus Reset |
|---|---|---|---|
| break | (VMC) | signal sent | by the VMC to reset all |

                                        peripherals.

| t |  | = | The | minimum set-up time before the |
|---|---|---|---|---|
|  | setup |  | VMC | attempts to communicate after |

                                        a reset signal. Peripheral devices may
                                        choose to not respond for up to the non-
                                        response time defined in each peripheral
                                        section.

#### 3.2 Timing Specifications

| Baud | Rate | = | 9600 | +1%/-2% | NRZ |
|---|---|---|---|---|---|

| t | = | 1.0 | mS |
|---|---|---|---|

                 inter-byte (max.)

| t | = | 5.0 | mS |
|---|---|---|---|

                 response (max.)

| t | = | 100 | mS |
|---|---|---|---|

                 break (min.)

| t | = | 200 | mS |
|---|---|---|---|

                 setup (min.)

| NOTE: | All | peripherals | have | the | option | of | not | responding | to | the | VMC. | Non- |
|---|---|---|---|---|---|---|---|---|---|---|---|---|

               response timing is defined in the peripheral specification.

#### 3.3 Timing Diagram

  Controller

## Dat           Chk                Break   Setup      Add*

  Peripheral

                                                             t break
                                           t response
| t | inter-byte | t | setup |
|---|---|---|---|

       NOTE: * indicates that the mode bit is set

Section 4
   Hardware Specification

#### 4.1 Bus Power Supply Definition

The information below defines the minimum VMC voltage output. The actual current
ratings per peripheral will be defined in their respective sections.

Power supply filtering is optional, therefore if a peripheral requires more power, or
tighter regulation, they may elect to supply their own power, or filtering, from available
sources elsewhere in the machine.

VMC Voltage Output:

| Minimum | = | 20 | VDC | rms.(rectified | and | optionally |
|---|---|---|---|---|---|---|

                                  filtered)

| Nominal | = | 34 | VDC | unreg.(rectified | and | filtered) |
|---|---|---|---|---|---|---|

                                  24 VDC rms.(rectified only)

| Maximum | = | 42.5* | VDC(ripple | voltage | upper | limit) |
|---|---|---|---|---|---|---|

                                  - High line input may allow 45 VDC
                                  peak (max.).

#### 4.2 Bus Transmitter / Receiver Specification

The following section describes the 5V, optically isolated, current loop system between
the Master and the Slave.

VMC Master:

             Transmit:

| Minimum | source current (active): | 100 | mA | @ 4V |
|---|---|---|---|---|
| Maximum | leakage current (inactive): | 100 | uA |  |

| NOTES: | 1) | The | transmit | line | must | be | able | to | withstand | a short | while |
|---|---|---|---|---|---|---|---|---|---|---|---|

                           in the active mode.

                           2) 15 mA should be added for each peripheral over six.

              Receive:

| Minimum | input | current | (active): | 15 mA | @ 1V |
|---|---|---|---|---|---|
| Maximum | input | current | (inactive): | 1 mA |  |

Peripheral Slave:

              Receive:

| Maximum | input | current | (active): | 15 mA @ | 4V |
|---|---|---|---|---|---|
| Maximum | input | current | (inactive): | 100 uA |  |

              Transmit:

| Minimum | sink current (active): | 15 | mA | @ 1V |
|---|---|---|---|---|
| Maximum | leakage current (inactive): | 30 | uA |  |

#### 4.3 Connector Specification

Connector assemblies supplied by the NAMA approved suppliers, noted in Section
4.3.6, are intermateable and meet or exceed the minimum requirements identified in
Sections 4.3.1, 4.3.2, 4.3.3, 4.3.4, and 4.3.5 when tested in the mated condition.
NAMA must approve any supplier changes to the fit, form, or function. Discrete
components, i.e. contacts, are not required to be inter-changeable between supplier
products.

#### 4.3.1. Material

#### 4.3.1.1. Terminal: Phosphor Bronze

#### 4.3.1.2. Plating: Tin or Tin/Lead

#### 4.3.1.3. Housing: UL 94V-2 nylon

#### 4.3.2. Ratings

| Section | Item | Requirement |
|---|---|---|

#### 4.3.2.1. Rated Voltage (Max)                                             600 Volts AC

#### 4.3.2.2. Maximum Rated Current (Six Circuit)                               7 Amps

#### 4.3.2.3. Ambient Temperature Range (including terminal T-rise)         -40°C to +105°C

#### 4.3.3. Electrical Performance

| Section | Item | Test | Condition | Requirement |
|---|---|---|---|---|

#### 4.3.3.1. Contact              Mate Connectors, measure by dry circuit, 20

| Resistance | mV | max., | 10 | mA. | Wire | resistance | shall | be | 10 | mΩ | Max. |
|---|---|---|---|---|---|---|---|---|---|---|---|

                                 removed from the measured value.

#### 4.3.3.2. Insulation           Mate Connectors, apply 500V DC between             1000 MΩ Min.

| Resistance | adjacent | terminal | or | ground. |
|---|---|---|---|---|

#### 4.3.3.3. Dielectric           Mate Connectors, apply 1500V AC for 1              No Breakdown.

| Strength | minute | between | adjacent | terminal | or | ground. |
|---|---|---|---|---|---|---|

#### 4.3.4. Mechanical Performance

| Section | Item | Test | Condition | Requirement |
|---|---|---|---|---|

#### 4.3.4.1. Insertion and         Insert and withdraw connectors at a speed          Noted Below

            Withdrawal Force rate of 25 +/- 3mm / minute.
| 6 | Pos | Insertion | Max. | 6 Pos Withdrawal | Min. |  |
|---|---|---|---|---|---|---|
| Initial |  |  | th |  |  |  |
|  |  |  | 30 cycle | Initial | 30th | cycle |

#### 41.2 N                  38.2 N                    2.9 N                2.4 N

#### 4.3.4.2. Crimping Pull Out Mount the crimped terminal, apply axial force

| Force | on | the | wire | at | a rate | of | 25 | +/- | 3mm | minute. |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  |  |  |  |  |  |  |  |  |  | 16 AWG | 88 | N Min. |
|  |  |  |  |  |  |  |  |  |  | 18 AWG | 88 | N Min. |
|  |  |  |  |  |  |  |  |  |  | 20 AWG | 59 | N Min. |
|  |  |  |  |  |  |  |  |  |  | 22 AWG | 39 | N Min. |
|  |  |  |  |  |  |  |  |  |  | 24 AWG | 29 | N Min. |
|  |  |  |  |  |  |  |  |  |  | 26 AWG | 20 | N Min. |
|  |  |  |  |  |  |  |  |  |  | 28 AWG | 10 | N Min. |

#### 4.3.4.3. Terminal Insertion   Insert the crimped terminal into the housing.        15 N Max.

            Force

#### 4.3.4.4. Terminal/Housing     Apply axial pull out force at the speed rate of      22 N Min.

| Retention | Force | 25 | +/- | 3mm | / minute. |
|---|---|---|---|---|---|

#### 4.3.4.5. Locking /            Measure force to lock & unlock connector          Lock: 30 N Max.

| Unlocking | Force | housings | (without | contacts) | at | a rate | of | 25 | +/- | Unlock: | 50 | N Min. |
|---|---|---|---|---|---|---|---|---|---|---|---|---|

                                 3mm / minute.

#### 4.3.5. Environmental Performance

| Section | Item | Test | Condition | Requirement |
|---|---|---|---|---|

#### 4.3.5.1. Repeated           When mated up to 30 cycles            Contact

| Insertion / | repeatedly | by | rate | of | 10 | cycles | per | Resistance | 20 | mΩ | Max. |
|---|---|---|---|---|---|---|---|---|---|---|---|
| Withdrawal | minute. |  |  |  |  |  |  |  |  |  |  |

#### 4.3.5.2. Temperature Rise   Carrying rated current load.                 30°C Rise Max.

#### 4.3.5.3. Vibration          Amplitude: 1.5mm P-P                  Appearance No Damage

| Sweep Time: | 10-55-10 | Hz in 1 | Contact | 20 mΩ Max. |
|---|---|---|---|---|
| minute. |  |  | Resistance |  |
| Duration: 2 | hours in | each X,Y,Z | Discontinuity | 1 µ sec. |
| axis. |  |  |  | Max. |

#### 4.3.5.4. Shock              50 G; 3 strokes in each X,Y,Z         Appearance No Damage

| axis. | Contact | 20 | mΩ | Max. |
|---|---|---|---|---|

                                                                     Resistance
                                                                     Discontinuity 1 µ sec Max.

#### 4.3.5.5. Heat Resistance    105 +/- 2°C, 96 hours                 Appearance No Damage

| Contact | 20 | mΩ | Max. |
|---|---|---|---|

                                                                     Resistance

#### 4.3.5.6. Cold Resistance    -40 +/- 3°C, 96 hours                 Appearance No Damage

| Contact | 20 | mΩ | Max. |
|---|---|---|---|

                                                                     Resistance

#### 4.3.5.7. Humidity           Temperature: 60 +/- 2°C               Appearance No Damage

| Relative Humidity: | 90% | - 95% | Contact | 20 mΩ Max. |
|---|---|---|---|---|
| Duration: 96 hours |  |  | Resistance |  |
|  |  |  | Dielectric | No |
|  |  |  | Strength | Breakdown |
|  |  |  | Insulation | 1000 MΩ |
|  |  |  | Resistance | Min. |

#### 4.3.5.8. Temperature        5 Cycles:                             Appearance No Damage

| Cycling | a) | - 55°C ; 30 Minutes | Contact | 20 | mΩ | Max. |
|---|---|---|---|---|---|---|
|  | b) | 105°C ; 30 Minutes | Resistance |  |  |  |

#### 4.3.5.9. Salt Spray         48 +/- 4 hours exposure to salt       Appearance No Damage

| spray | from | 5 +/- | 1% | solution | at | 35 | Contact | Res. | 20 | mΩ | Max. |
|---|---|---|---|---|---|---|---|---|---|---|---|

## +/- 2°C.

#### 4.3.5.10   SO2 Gas          24 hour exposure to 50 +/- 5 ppm      Appearance     No Damage

| . | SO2 | gas | at | 40 | +/- | 2°C. | Contact | Res. | Max. |
|---|---|---|---|---|---|---|---|---|---|

#### 4.3.6 Approved Suppliers and Part Numbers

#### 4.3.6.1. Suppliers

| Molex | :       Mini-Fit, Jr.TM Product |
|---|---|
| AMP: | AMP-DUACTM Product |

#### 4.3.6.2. Peripherals

| Connector: | Six | (6) | Circuit | Receptacle | Housing |
|---|---|---|---|---|---|

                     Molex 39-01-2060
                     AMP P/N 106527-6

| Terminals: | Female | Contacts | (sockets), | Tin |
|---|---|---|---|---|

                     Molex 39-00-0065
                     AMP P/N 106528-2 or 106529-2

       Strain Relief: The strain relief shall not exceed a Maximum Form Factor of 0.85 inch wide x

#### 0.75 inch high x 1.90 inch long, excluding integrated hinges and wire ties.

                     Molex 15-04-0296
                     AMP P/N 1375618-1

#### 4.3.6.3. Bus Harness

| Connector: | Six | (6) | Circuit | Plug | Housing |
|---|---|---|---|---|---|

                     Molex 39-01-2061
                     AMP P/N 794550-6 or 794542-6

| Terminals: | Male | Contacts | (pins), | Tin |
|---|---|---|---|---|

                     Molex 39-00-0067
                     AMP P/N 794578-1 or 794576-1

#### 4.3.6.4. VMC Connector (Direct PCB Mount)

       Vertical Header: Male Contacts (pins), Tin
                     Molex 39-28-1063
                     AMP P/N 794664-6

       Right Angle Header: Male Contacts (pins), Tin
                     Molex 39-30-1060
                     AMP P/N 794448-1

#### 4.3.6.5. Approved Parts – Alternate Form Factors

         Select applications may require connector configurations with alternate form
         factors. Alternate form factor connectors may be used provided they are:

            - provided by the Approved Suppliers listed
            - part of the Approved Supplier Product Family portfolio
            - intermateable with the approved connector part numbers listed
            - meet the performance objectives set forth in this specification

Connector Pin-out:

             Line 1 - 34 VDC
             Line 2 - DC Power Return
             Line 3 - N/C
             Line 4 - Master Receive
             Line 5 - Master Transmit
             Line 6 - Communications Common

| 6 | 3 | 3 | 6 |
|---|---|---|---|

| 5 | 2 | 2 | 5 |
|---|---|---|---|

| 4 | 1 | 1 | 4 |
|---|---|---|---|

| Peripheral Connector | VMC | / Bus Connector |
|---|---|---|
| Face View |  | Face View |
| Receptacle |  | Header |
| (Sockets) |  | (Pins) |

#### 4.4 Example Schematic

| VMC | << | Peripheral |
|---|---|---|

          VMC Voltage Output

                           1

| 2 | Slave |
|---|---|

## +5 Vdc

                                                                  Rcv

                                                                  Xmit

| Master | Slave |
|---|---|

                     Transmit

                           5
                                                                  Rcv

                                                                  Xmit

## +5 Vdc

                                                        Slave 3
| CMOS | Master |
|---|---|
| Gate | Receive |

                                                                  Rcv
                           4

                  Communications
                     Common
                                                                  Xmit

                           6

Section 5
  Coin Acceptor/Changer
  VMC/Peripheral Communication Specifications

#### 5.1 Introduction

      This section defines the communication bytes sent and received by a coin
      accepting device (“Changer”). As defined in Section 2.3, the changer’s
      address is 00001xxxB (08H).

      Unless stated otherwise, all information is assumed to be in a binary format.

      There are currently two levels of support defined for the coin mechanism
      interface, Level 2 and Level 3. The level of coin mechanism operation is sent
      to the VMC in the response to the STATUS command (defined later in this
      section). The following paragraphs will define how a VMC should
      differentiate between each level.

      Level 2 Changers

      For level 2 changers, VMC operation consists of monitoring inputs from the
      coin mechanism, accumulating credit, issuing a coin acceptance disable
      command when appropriate, and issuing appropriate payout commands
      based on the VMC resident payout algorithms and escrow rules.

      Level 3 Changers

      For level 3 changers, VMC operation is the same as defined above for level
      2, with the addition of the EXPANSION command and its implications
      (defined later in this section). The VMC has the option of sending the
      EXPANSION command to the coin mechanism to determine the coin
      mechanism’s manufacturer code, serial number, model/tuning revision,
      software version, and optional features. Based on the optional feature
      information the VMC will determine the appropriate operating mode (in other
      words, modes that both the coin mechanism and the VMC can support),
      enable any appropriate coin mechanism features by sending an appropriate
      feature enable command back to the coin mechanism, and enter the proper
      operating mode. This technique allows all VMCs and peripherals to
      accommodate existing feature capabilities and provides a means for
      upgrading Level 3 equipment.

#### 5.2 VMC Commands

| Command | Hex | Code | Description |
|---|---|---|---|

| RESET | 08H | Command | for | changer | to | self-reset |
|---|---|---|---|---|---|---|

| SETUP | *              09H | Request | for | changer | setup | information. |
|---|---|---|---|---|---|---|

| TUBE | STATUS | 0AH | Request | for | changer | tube | status. |
|---|---|---|---|---|---|---|---|

| POLL | 0BH | Request | for | changer | activity | status. |
|---|---|---|---|---|---|---|

| COIN | TYPE | 0CH | Signifies | coin | types | accepted | and |
|---|---|---|---|---|---|---|---|

                                         allowable coin dispensing. This
                                         command is followed by setup data.
                                         See command format section.

| DISPENSE | 0DH | Command | to | dispense | a coin | type. |
|---|---|---|---|---|---|---|

                                         Followed by coin type to dispense.
                                         See command format section.

| EXPANSION | 0FH | Command to allow addition of |
|---|---|---|
| COMMAND |  | features and future enhancements. |

                                         Changers at feature level 2 do not support
                                         this command.

      NOTE: An EXPANSION command is always followed by a “sub-command.”
      This command allows for feature additions.

      - In Version 1.0 & 2.0, SETUP was called STATUS.

#### 5.3 VMC Command Format

| VMC Command | Code | VMC Data |
|---|---|---|
| RESET | 08H | No data bytes |

      This command is the vehicle that the VMC should use to tell the changer that
      it should return to its default operating mode. With the exception of the ACK
      response, it should abort all communication and disable all acceptance until
      otherwise instructed by the VMC.

      The following initialization sequence is recommended for all new VMCs
      designed after July, 2000. It should be used after “power up”, after issuing
      the RESET command, after issuing the Bus Reset (pulling the transmit line
      “active” for a minimum of 100 mS), or anytime a POLL command results in a
      “JUST RESET” response (i.e., peripheral self resets).

      POLL – `08h`
           To obtain “JUST RESET” response
      SETUP – `09h`
          To obtain changer level and configuration information
      EXPANSION IDENTIFICATION – 0F `00h` (Level 03+ only)
          To obtain additional changer information and options
      EXPANSION FEATURE ENABLE – 0F `01h` (Level 03+ only)
          To enable desired options
      EXPANSION SEND DIAG STATUS – 0F `05h` (Level 03+ & option b1 only)
          To request the changer to report its current state of operation
      TUBE STATUS – `0Ah` (Note 1)
           To obtain tube status / change information
      COIN TYPE – `0Ch`
           To enable desired coin acceptance and disable manual coin payout if
           desired

      Note 1 – A minimum 500 msec delay is required between a reset (regardless
      of type) and the first TUBE STATUS command for certain models of the
      existing MDB coin changer field base.

| VMC Command | Code | Changer Response Data |
|---|---|---|
| SETUP | 09H | 23 bytes: Z1 - Z23 |

| Z1 | =          Changer | Feature | Level | - 1 | byte |
|---|---|---|---|---|---|

                    Indicates the feature level of the changer. This will distinguish
                    the changers feature level to the VMC. Current defined levels:

| Level | 2: | Supports | “core” | command | set. | These | are: |
|---|---|---|---|---|---|---|---|

## Reset, Status, Tube Status, Poll, Coin

                                  TYPE, and DISPENSE. (Z1 = `02h`)

| Level | 3: | Supports | level | two | and | the | EXPANSION |
|---|---|---|---|---|---|---|---|

                                  command addition changer model number,
                                  manufacturer code, turning revision, etc. See the
                                  details of EXPANSION command later in this
                                  document. (Z1=`03h`)

| Z2 | - Z3 | =     Country | / Currency | Code | - 2 | bytes |
|---|---|---|---|---|---|---|

                    The packed BCD country / currency code of the changer can be
                    sent in two different forms depending on the value of the left
                    most BCD digit.

                    If the left most digit is a 0, the International Telephone Code is
                    used to indicate the country that the changer is set-up for. For
                    example, the USA code is 00 01H (Z2 = 00 and Z3 = 01).

                    If the left most digit is a 1, the latest version of the ISO 4217
                    numeric currency code is used (see Appendix A1). For
                    example, the code for the US dollar is 18 40H (Z2 = 18 and Z3
                    = 40) and for the Euro is 1978 (Z2 = 19 and Z3 = 78).

                    All new designs after July, 2000 must use the ISO 4217
                    numeric currency codes as listed in Appendix A1.

| Z4 | =          Coin | Scaling | Factor | - 1 | byte |
|---|---|---|---|---|---|

                    All accepted coin values must be evenly divisible by this
                    number. For example, this could be set to 05H for the USA
                    nickel.

| Z5 | =          Decimal | Places | - 1 | byte |
|---|---|---|---|---|

                    Indicates the number of decimal places on a credit display. For
                    example, this could be set to 02H in the USA.

| Z6 | - Z7 | =     Coin | Type | Routing | - 2 | bytes |
|---|---|---|---|---|---|---|

                    Indicates what coin types can be routed to the Changer’s tubes.

                    b15 b14 b13 b12 b11 b10 b9 b8 | b7 b6 b5 b4 b3 b2 b1 b0

## Z6                                                                 Z7

                    Bit is set to indicate a coin type can be routed to the tube. Valid
                    coin types are 0 to 15.

| Z8 | - Z23 | =    Coin | Type | Credit | - 16 | bytes |
|---|---|---|---|---|---|---|

                    Indicates the value of coin types 0 to 15. Values must be sent
                    in ascending order. This number is the coin's monetary value
                    divided by the coin scaling factor. Unused coin types are sent
                    as 00H. Unsent coin types are assumed to be zero. It is not
                    necessary to send all coin types. Coin type credits sent as FFH
                    are assumed to be vend tokens. That is, their value is assumed
                    to worth one vend.

                    The bytes position in the 16 byte string indicates the coin
                    type(s). For example, the first byte sent would indicate the
                    value of coin type 0, the second byte sent would indicate the
                    value of coin type 1, and so on. For example, the USA coin
                    types may be; Coin type 0 = nickel, Coin type 1 = dime, Coin
                    type 2 = quarter, Coin type 3 = dollar.

| VMC Command | Code | Changer Response Data |
|---|---|---|
| TUBE STATUS | 0AH | 18 bytes: Z1 - Z18 |

| Z1 | - Z2 | =     Tube | Full | Status | - 2 | bytes |
|---|---|---|---|---|---|---|

                    Indicates status of coin tube for coin types 0 to 15.

                    b15 b14 b13 b12 b11 b10 b9 b8 | b7 b6 b5 b4 b3 b2 b1 b0

## Z1                                                                 Z2

                    A bit is set to indicate a full tube. For example, bit 7 = set would
                    indicate the tube for coin type 7 is full.

| Z3 | - Z18 | =    Tube | Status | - 16 | bytes |
|---|---|---|---|---|---|

                    Indicates the greatest number of coins that the changer “knows”
                    definitely are present in the coin tubes. A bytes position in the
                    16 byte string indicates the number of coins in a tube for a

                    particular coin type. For example, the first byte sent indicates
                    the number of coins in a tube for coin type 0. Unsent bytes are
                    assumed to be zero. For tube counts greater than 255, counts
                    should remain at 255.

| NOTE: | If | a changer | can | detect | a tube | jam, | defective | tube | sensor, | or |
|---|---|---|---|---|---|---|---|---|---|---|

      other malfunction, it will indicate the tube is "bad" by sending a tube full status
      and a count of zero for the malfunctioning coin type.

| VMC Command | Code | Changer Response Data |
|---|---|---|
| POLL | 0BH | 16 bytes: Z1 - Z16 |

| Z1 | - Z16 | =    Changer | Activity | - 16 | bytes |
|---|---|---|---|---|---|

                    Indicates the changer activity. If there is nothing to report, the
                    changer should send only an ACK. Otherwise, the only valid
                    responses are:

      Coins Dispensed Manually:

## Z1       Z2

                 (1yyyxxxx) (zzzzzzzz)

| yyy | = | The | number of | coins dispensed. |
|---|---|---|---|---|
| xxxx | = | The | coin type | dispensed (0 to 15) |
| zzzzzzzz | = | The | number of | coins in the tube. |

      Coins Deposited:

## Z1            Z2

| (01yyxxxx) | (zzzzzzzz) |
|---|---|

| yy | = | Coin | routing. | 00: | CASH | BOX |
|---|---|---|---|---|---|---|

## 01: Tubes

## 10: Not Used

## 11: Reject

| xxxx | = | Coin | type | deposited | (0 | to | 15). |
|---|---|---|---|---|---|---|---|

| zzzzzzzz | = | The | number | of | coins | in | the | tube |
|---|---|---|---|---|---|---|---|---|

                                          for the coin type accepted.

      Status:
| (00000001) | =        Escrow | request1 | - An | escrow | lever | activation |
|---|---|---|---|---|---|---|

                                       has been detected.
| (00000010) | =        Changer | Payout | Busy2 | - The | changer | is | busy |
|---|---|---|---|---|---|---|---|

                                       activating payout devices.

| (00000011) | =        No | Credit1 | - A | coin | was | validated | but | did | not |
|---|---|---|---|---|---|---|---|---|---|

                                       get to the place in the system when credit is
                                       given.
| (00000100) | =        Defective | Tube | Sensor1 | - The | changer | has |
|---|---|---|---|---|---|---|

                                       detected one of the tube sensors behaving
                                       abnormally.
| (00000101) | =        Double | Arrival1 | - Two | coins | were | detected | too |
|---|---|---|---|---|---|---|---|

                                       close together to validate either one.
| (00000110) | =        Acceptor | Unplugged2 | - The | changer | has |
|---|---|---|---|---|---|

                                       detected that the acceptor has been removed.
| (00000111) | =        Tube | Jam1 | - A | tube | payout | attempt | has |
|---|---|---|---|---|---|---|---|

                                       resulted in jammed condition.
| (00001000) | =        ROM | checksum | error1 | - The | changers | internal |
|---|---|---|---|---|---|---|

                                       checksum does not match the calculated
                                       checksum.
| (00001001) | =        Coin | Routing | Error1 | - A | coin | has | been |
|---|---|---|---|---|---|---|---|

                                       validated, but did not follow the intended
                                       routing.
| (00001010) | =        Changer | Busy2 | - The | changer | is | busy | and | can |
|---|---|---|---|---|---|---|---|---|

                                       not answer a detailed command right now.
| (00001011) | =        Changer | was | Reset1 | - The | changer | has |
|---|---|---|---|---|---|---|

                                       detected an Reset condition and has returned
                                       to its power-on idle condition.
| (00001100) | =        Coin | Jam1 | - A | coin(s) | has | jammed | in | the |
|---|---|---|---|---|---|---|---|---|

                                       acceptance path.
| (00001101) | =        Possible | Credited | Coin | Removal1 | – There | has |
|---|---|---|---|---|---|---|

                                       been an attempt to remove a credited coin.
                                          Note:
                                          - changers must have a means to disable this
                                                code due to potential older VMC issues.
                                          - virtually all VMCs designed prior to this code’s
                                                introduction (10/16/02) will not support it.
                                          - It is a vending machine system issue as to
                                                what is done when this code is received.
      Slug:
| (001xxxxx) | =        xxxxx | is | the | number | of | slugs | since | the | last |
|---|---|---|---|---|---|---|---|---|---|

                                       activity.

| NOTES: | The | Changer | may | send | several | of | one | type | activity*, | up | to | 16 | bytes |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

              total. This will permit zeroing counters such as slug, inventory, and
              status.
| 1 | Sent | once | each | occurrence |
|---|---|---|---|---|
| 2 | Sent | once | each | POLL |

              - Type activity is defined as Coins Dispensed Manually, Coins Deposited,
              Status, and Slug. All may be combined in a response to a POLL command
              providing the total number of bytes does not exceed 16. Note that Coins
              Dispensed Manually and Coins Deposited are dual byte codes.

      File Transport Layer POLLed responses:

      Note that all FTL responses are defined in Section 2.6. For the coin changer,
      the source address will always be the changer (08H) as defined in Section
      2.3.

             Z1

| 1B | REQ | TO | RCV | The | coin | changer | is | requesting | to |
|---|---|---|---|---|---|---|---|---|---|

                                         receive data from a device or VMC.

                                         Z2 = Destination address of response
                                         Z3 = Source address of response (08H)
                                         Z4 = File ID
                                         Z5 = Maximum length
                                         Z6 = Control

| 1C | RETRY/DENY | The | coin | changer | is | requesting | a device | or |
|---|---|---|---|---|---|---|---|---|

                                         VMC to retry or deny the last FTL
                                         command.

                                         Z2 = Destination address of response
                                         Z3 = Source address of response (08H)
                                         Z4 = Retry delay

| 1D | SEND | BLOCK | The | coin | changer | is | sending | a block | of | data |
|---|---|---|---|---|---|---|---|---|---|---|

                                         (maximum of 31 bytes) to a device or VMC.

                                         Z2 = Destination address of data
                                         Z3 = Block #
                                         Z4-Z34 = Data (maximum of 31 bytes)

| 1E | OK | TO | SEND | The | coin | changer | is | indicating | that | it |
|---|---|---|---|---|---|---|---|---|---|---|

                                         is OK for a device or VMC to send it data.

                                         Z2 = Destination address of response
                                         Z3 = Source address of response (08H)

| 1F | REQ | TO | SEND | The | coin | changer | is | requesting | to |
|---|---|---|---|---|---|---|---|---|---|

                                         send data to a device or VMC.

                                         Z2 = Destination address of response
                                         Z3 = Source address of response (08H)
                                         Z4 = File ID
                                         Z5 = Maximum length
                                         Z6 = Control

| VMC Command | Code | VMC Data |  |  |
|---|---|---|---|---|
| COIN TYPE | 0CH | 4 bytes: | Y1 | - Y4 |

| Y1 | - Y2 | =     Coin | Enable | - 2 | bytes |
|---|---|---|---|---|---|

      b15 b14 b13 b12 b11 b10 b9 b8 | b7 b6 b5 b4 b3 b2 b1 b0

## Y1                                                            Y2

      A bit is set to indicate a coin type is accepted. For example, bit 6 is set to
      indicate coin type 6, bit 15 is set to indicate coin type 15, and so on. To
      disable the changer, disable all coin types by sending a data block containing
      0000H. All coins are automatically disabled upon reset.

| Y3 | - Y4 | =     Manual | Dispense | Enable | - 2 | bytes |
|---|---|---|---|---|---|---|

      b15 b14 b13 b12 b11 b10 b9 b8 | b7 b6 b5 b4 b3 b2 b1 b0

## Y3                                                            Y4

      A bit is set to indicate dispense enable. For example, bit 2 is set to enable
      dispensing of coin type 2. This command enables/disables manual
      dispensing using optional inventory switches. All manual dispensing switches
      are automatically enabled upon reset.

| VMC Command | Code | VMC Data |
|---|---|---|
| DISPENSE | 0DH | 1 byte: Y1 |

      b7 b6 b5 b4 b3 b2 b1 b0
                                Y1

      Bits b3, b2, b1, b0 indicate coin type to be dispensed. Valid codes are 0H to
      FH to indicate coin types 0 to 15.

      Bits b7, b6, b5, b4 indicate the number of coins to be dispensed.

| NOTE | 1: | If | two | coin | types | have | the | same | value, | the | highest | coin | type |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                    should be paid out first.

| NOTE | 2: | There | is | no | defined | limit | on | how | long | the | actual | dispense | takes |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                    since the command allows for up to 15 coins to be paid out. The
                    payout cycle begins when the changer ACKs the VMC’s
                    DISPENSE (0DH) command. This cycle typically lasts a
                    minimum of 100 mS and ends when the changer stops
                    dispensing the desired number of coins. VMCs should monitor
                    the Changer Payout Busy response to the POLL command to
                    determine when the entire payout cycle is completed.

                    However, it must be noted that other than ACKing the
                    DISPENSE (0DH) command, the changer does not have to
                    respond during the payout cycle provided the payout cycle is
                    less than the changer's non-response time and the changer
                    starts responding again prior to the end of the non-response
                    time. Thus, it is acceptable for the changer to never report
                    Changer Payout Busy, but simply start ACKing the POLL
                    commands upon completion of a payout cycle provided the non-
                    response time has not been exceeded.

## Level Three Capabilities - Expansion Command

      The following describes the currently defined expansion commands.

      Sub-command 00H is used for a changer that has the capability of reporting
      model number, serial number, and so on.

| VMC Command | Code Sub-Command | Changer Response Data |
|---|---|---|
| EXPANSION | 0FH 00H | 33 bytes: Z1 - Z33 |

## Command              Identification

| Z1 | - Z3 | =     Manufacturer | Code | - 3 | bytes |
|---|---|---|---|---|---|

                    Identification code for the equipment supplier. Sent as ASCII
                    characters. Currently defined codes are listed in the EVA
                    document entitled "European Vending Association Data
                    Transfer Standard" (EVA-DTS), the Audit Data Lists section,
                    sub-section 2, "Manufacturer Codes".

| Z4 | - Z15 | =    Serial | Number | - 12 | bytes |
|---|---|---|---|---|---|

                    Factory assigned serial number. All bytes must be sent as
                    ASCII characters, zeros (30H) and blanks (20H) are acceptable.

      Z16 - Z27 = Model #/Tuning Revision - 12 bytes

                    Manufacturer assigned model number and tuning number. All
                    bytes must be sent as ASCII characters, zeros (30H) and
                    blanks (20H) are acceptable. Each manufacturer should
                    include information concerning the changer tuning revision.

      Z28 - Z29 = Software Version - 2 bytes

                    Current software version. Must be sent in packed BCD.

      Z30 - Z33 = Optional Features - 4 bytes

                    Each of the 32 bits indicate an optional features availability. If
                    the bit is set the feature is available. Bits should be sent in
                    descending order, i.e. bit 31 is sent first and bit 0 is sent last.
                    Currently defined options are:

| b0 | -          Alternative | Payout | method. | This | method | allows |
|---|---|---|---|---|---|---|

                                  changer designs that determine change payout.
                                  That is, the payout algorithm may reside in the
                                  changer instead of the VMC.

| b1 | -           Extended | Diagnostic | command | supported. | This |
|---|---|---|---|---|---|

                                   command allows the VMC to request diagnostic
                                   status of the coin changer.

| b2 | -           Controlled | Manual | Fill | and | Payout | commands |
|---|---|---|---|---|---|---|

                                   supported. These commands allows the VMC to
                                   request the number of coin inserted or dispensed
                                   while the changer was in a controlled manual fill
                                   or payback mode.

| b3 | -           File | Transport | Layer | (FTL) | supported | as | defined |
|---|---|---|---|---|---|---|---|

                                   in Section 2.6.

| b4 | - b31 | Available | for | future | use |
|---|---|---|---|---|---|

| VMC Command | Code Sub-Command | VMC Data |  |  |
|---|---|---|---|---|
| EXPANSION | 0FH 01H | 4 bytes: | Y1 | - Y4 |

## Command              Feature Enable

      This command is used to enable each of the optional features defined in Z30-
      Z33 above. To enable a feature a bit is set to one. All optional features are
      disabled after reset.

| VMC Command | Code Sub-command | VMC Data | Changer Response |
|---|---|---|---|
| EXPANSION | 0FH 02H | Y1 | None |

## Command              Payout

      (Alternative
          Payout)

| Y1 | =          Value | of | coins | to | be | paid | out | - 1 | byte |
|---|---|---|---|---|---|---|---|---|---|

                    This value is expressed as the number of coin scaling factors
                    that would sum to the value. For example, in a USA system
                    using a scaling factor of 05, if the change to be paid out is 75
                    cents, then Y1 will equal fifteen. That is, the sum of fifteen
                    nickels equal 75 cents. The coin changer will determine which
                    actual denominations of coins will be paid out. In the 75 cent
                    example, the coins may be 3 quarters; or, 7 dimes & 1 nickel;
                    or, 2 quarters & 2 dimes & 1 nickel, etc.

| VMC Command | Code | Sub-command | VMC Data | Changer Response |
|---|---|---|---|---|
| EXPANSION | 0FH | 03H | None | 16 bytes: Z1-Z16 |

## Command              Payout Status

      (Alternative
          Payout)

| Z1 | - Z16 | =     Number | of | each | coin | type | paid | out | - 16 | bytes |
|---|---|---|---|---|---|---|---|---|---|---|

                     This is the changer's response to the last VMC Alternative
                     PAYOUT command (0FH-02H). Bytes are sent in ascending
                     order of coin types. A bytes position in the string indicates the
                     coin type. That is, byte one is the number of coins for coin type
                     1, byte two is the number of coins for coin type two, and so on.
                     Unsent bytes are assumed to be zero.

                     The changer clears payout data after an ACK response from
                     the VMC.

                     The VMC should compare the value of the coins paid out to the
                     (0FH-02H) Alternative PAYOUT command’s Y1.

| NOTES: | 1) | If | the | changer’s | payout | is | busy | it | will | respond | to | the |
|---|---|---|---|---|---|---|---|---|---|---|---|---|

                        Alternative PAYOUT STATUS command with an ACK only.

                 2) If no coins have been paid out, at least one zero valued data
                    byte must be sent.

                     3) There is no defined limit on how long the actual payout
                        takes. See Note 2 under the DISPENSE (0DH) command.

| VMC Command | Code | Sub-command | Changer Response | Data |
|---|---|---|---|---|
| EXPANSION | 0FH | 04H | 1 byte: Z1 |  |

## Command      Payout Value Poll

      (Alternative
          Payout)

| Z1 | = | Changer | Payout | Activity | - 1 | byte |
|---|---|---|---|---|---|---|

                           An interval value (scaled) which indicates the amount of
                           paid out change since the previous PAYOUT VALUE
                           POLL (or between the initial Alternative PAYOUT
                           command (0FH-02H) and the first PAYOUT VALUE

## Poll).

                           An 00H response indicates no coins were paid out since
                           the previous PAYOUT VALUE POLL (or the initial
                           Alternative PAYOUT command (0FH-02H)).

                           An ACK only indicates that the change payout is finished.
                           This should be followed by the PAYOUT STATUS
                           command (0FH-03H) to obtain the complete payout data.

      NOTE: The initial intent of this command is to determine the amount of
      change paid out so that the credit display can be decremented as coins are
      dispensed.

| VMC Command | Code Sub-Command | Changer Response | Data |
|---|---|---|---|
| EXPANSION | 0FH 05H | 2 bytes: Z1-Z2 |  |

## Command             Send Diagnostic Status

Send Current Diagnostic Status - This command requests the changer to report
its current state of operation. The VMC should periodically transmit the command
approximately every 1 to 10 seconds.
.

Z1-Z2 = Current changer diagnostic information

      The changer reports its current state of operation in a 2 byte code. Z1 is the
      main code and Z2 is the sub-code. The code is reported as long as the
      condition exists and stops being reported as soon as the condition does not
      exist. Multiple 2 byte codes may be sent in response to a single command
      which could result in a maximum of eight 2 byte codes (16 bytes total).

      The following tables identify the currently defined extended diagnostic codes:

| Z1 | / Z2 | Status |  | Cause(s) of Status / Error |
|---|---|---|---|---|
| 01 | / 00 | Powering | up | Changer powering up / initialization |
| 02 | / 00 | Powering | down | Changer powering down |
| 03 | / 00 | OK |  | Changer fully operational and ready to |

                                           accept coins
| 04 | / 00 | Keypad | shifted | MODE | key | pressed | and | held | so | that |
|---|---|---|---|---|---|---|---|---|---|---|

                                           LED flashes indicating keypad in shifted
                                           state. Reverts to normal mode if no key
                                           pressed for 15 seconds
| 05 | / 10 | Manual | Fill | / Payout | active | Manual | Fill | or | Manual | Payout | mode | of |
|---|---|---|---|---|---|---|---|---|---|---|---|---|

                                          operation in progress (under control of
                                          the changer). This response must be
                                          reported at least once to allow the VMC
                                          to request a manual fill or manual
                                          payout report.
| 05 | / 20 | New Inventory Information | Changer not in Manual inventory mode, |
|---|---|---|---|
|  |  | Available | but new inventory information available. |
| 06 | / 00 | Inhibited by VMC | All coin acceptance inhibited at request |

                                           of VMC, possibly due to product
                                           dispenser jams, completely sold out,
                                           etc.
| 10 | / Z2 | General | changer | error | Z2 | defined | as: |
|---|---|---|---|---|---|---|---|

                                               00 Non specific error.
                                               01 Check sum error #1. A check sum error
                                               over a particular data range of configuration
                                               field detected.
                                               02 Check sum error #2. A check sum error
                                               over a secondary data range or
                                               configuration field detected.
                                               03 Low line voltage detected. The changer
                                               has disabled acceptance or payout due to a
                                               low voltage condition.

| Z1 / Z2 | Status |  | Cause(s) of Status / Error |  |
|---|---|---|---|---|
| 11 / Z2 | Discriminator | module | Z2 defined as: |  |
|  | error |  | 00 Non specific discriminator | error. |

                                               10 Flight deck open.
                                               11 Escrow Return stuck open.
                                               30 Coin jam in sensor.
                                               41 Discrimination below specified standard.
                                               50 Validation sensor A out of range. The
                                               acceptor detects a problem with sensor A.
                                               51 Validation sensor B out of range. The
                                               acceptor detects a problem with sensor B.
                                               52 Validation sensor C out of range. The
                                               acceptor detects a problem with sensor C.
                                               53 Operating temperature exceeded. The
                                               acceptor detects the ambient temperature
                                               has exceeded the changer's operating
                                               range, thus possibly affecting the
                                               acceptance rate.
                                               54 Sizing optics failure. The acceptor
                                               detects an error in the sizing optics.
| 12 | / Z2 | Accept | gate | module | error | Z2 | defined | as: |
|---|---|---|---|---|---|---|---|---|

                                              00 Non specific accept gate error.
                                              30 Coins entered gate, but did not exit.
                                              31 Accept gate alarm active.
                                              40 Accept gate open, but no coin detected.
                                              50 Post gate sensor covered before gate
                                              opened.
| 13 | / Z2 | Separator | module | error | Z2 | defined | as: |
|---|---|---|---|---|---|---|---|

                                               00 Non specific separator error
                                               10 Sort sensor error. The acceptor detects
                                               an error in the sorting sensor.
| 14 | / Z2 | Dispenser | module | error | Z2 | defined | as: |
|---|---|---|---|---|---|---|---|

                                               00 Non specific dispenser error.
| 15 | / Z2 | Coin Cassette | / tube | Z2 | defined | as: |  |  |
|---|---|---|---|---|---|---|---|---|
|  |  | module error |  |  | 00 Non | specific | cassette | error. |

                                               02 Cassette removed.
                                               03 Cash box sensor error. The changer
                                               detects an error in a cash box sensor.
                                               04 Sunlight on tube sensors. The changer
                                               detects too much ambient light on one or
                                               more of the tube sensors.

Diagnostic Status EVA-DTS Correlation

The Extended Diagnostic information reported may be used by the vending machine
controller as desired (i.e., service mode displays); however, EVA-DTS data
elements could also be used for reporting to a host system. Examples are:

      o Via a translation of the Z1/Z2 code to one of the Fault Lists as described
      in Section 10 of the EVA-DTS.

      o Via the EA201 Event Identification element with the format EAxxyy where
      xx = Z1 and yy = Z2.

      o Via a customer / manufacture specific coding scheme using the MA5xx
      fields.

| VMC Command | Code Sub-Command | Changer Response | Data |
|---|---|---|---|
| EXPANSION | 0FH 06H | 16 bytes Z1-Z16 |  |

## Command             Send Controlled Manual Fill Report

Send Controlled Manual Fill Report - This command requests the changer to
report the number of coins inserted during a changer controlled manual fill
(controlled bulk fill) mode. While in this mode, the changer must not report coins
inserted in response to the POLL command.

Z1-Z16 = number of controlled manual mode filled coins (by coin type)

      A single byte is reported for each coin type, 0 to 15. For example, Z1 =
      number of coins of coin type 0 added in a controlled manual fill mode. Any
      amount above 255 will be reported as 255, i.e. it will reach a maximum limit.

      Only coin types supported are required to be reported. Counts for unsent
      coins types will be assumed to be unchanged.

Notes: After power on, changer reset, closing of the machine door, or a change in
controlled manual fill status in the changer (changer indicated it was in controlled
manual fill mode via CM0510 then changed to any other state) the machine should
request the controlled manual coin fill data from the changer using the above
command.

See EVA-DTS correlation at end of SEND CONTROLLED MANUAL PAYOUT
REPORT (0F-07H) command.

| VMC Command | Code Sub-Command | Changer Response | Data |
|---|---|---|---|
| EXPANSION | 0FH 07H | 16 bytes Z1-Z16 |  |

## Command             Send Controlled Manual Payout Report

Send Controlled Manual Payout Report - This command requests the changer
to report the number of coins dispensed during a changer controlled manual payout
(controlled bulk dispense) mode. Note that this does not include the coins
dispensed via the individual dispense switches.

If the new Controlled Manual Fill / Payout command is implemented in the coin
mech and enabled by the VMC (`0Fh`, `01h`, bit 2 of Y1 to Y4), while in a controlled
manual payout (dispense) mode, the changer must not report the coins paid out in
response to the POLL command. Conversely, if the changer does not support the
new command or the VMC does not enable it, the changer should report the coins
paid out in response to the POLL command.

Z1-Z16 = number of controlled manual mode dispensed coins (by coin type)

      A single byte is reported for each coin type 0 to 15. For example, Z1 =
      number of coins of coin type 0 dispensed in a controlled manual payout
      mode. Any amount above 255 will be reported as 255, i.e. it will reach a
      maximum limit.

      Only coin types supported are required to be reported. Counts for unsent
      coin types will be assumed to be unchanged.

Note: After power on, changer reset, closing of the machine door, or a change in
controlled manual payout status in the changer (changer indicated it was in
controlled manual payout mode via CM0510 then changed to any other state) the
machine should request the controlled manual coin payout data from the changer
using the above command.

Controlled Manual Fill / Payout EVA-DTS Correlation

The controlled manual fill and payout coin information may be used by the vending
machine controller as desired (i.e., service mode displays); however, EVA-DTS data
elements could be used for reporting to a host system. Examples are:

| CA3XX | CA4XX | CA1704 | CA1705 |
|---|---|---|---|

| Controlled Manual | Fill | 0F06 | n/a | 0F06 | n/a |
|---|---|---|---|---|---|
| VMC Tube Fill |  | VMC | n/a | VMC | n/a |

| Controlled Manual Payout | n/a | 0F07* | n/a | 0F07* |
|---|---|---|---|---|
| VMC Coin Payout | n/a | VMC | n/a | VMC |
| Manual Dispense Switches | n/a | 0B | n/a | 0B |

       *If extended 0F06 & 0F07 commands are implemented.
        If extended 0F06 & 0F07 commands are not implemented in the coin mech
        or not enabled by the VMC, the coin mech will respond to the POLL
        command with the controlled manual payout coins.

With the above, the CA3XX & CA4XX fields can continue to be the primary fields for
cash audit and the CA1704 & CA1705 fields can be used for indicating controlled
manually filled / dispensed coins.

Coin Tube Audit Fields

As a reference, below are the agreed CA17XX data elements that provide detailed
coin tube count information and controlled-manual coin tube insertion / dispense
information. These were approved by the EVA - DTS Technical Sub Committee on
January 27, 1997.

| Block | Data | Charac- | Length | Element |
|---|---|---|---|---|
| Identifier | Contents | teristic | Min Max |  |

Reference

| CA17 | Coin | Type | Number | N | 01 | 03 | CA1701 |
|---|---|---|---|---|---|---|---|

             (per MDB coin type)

| Value | of | Coin | N | 01 | 08 | CA1702 |
|---|---|---|---|---|---|---|

| Number | of | Coins | N | 01 | 08 | CA1703 |
|---|---|---|---|---|---|---|

             in Tube

| Number | of | Coins | N | 01 | 08 | CA1704 |
|---|---|---|---|---|---|---|

             Inserted during
             Controlled-Manual Fill

| Number | of | Coins | N | 01 | 08 | CA1705 |
|---|---|---|---|---|---|---|

             Dispensed during
             Controlled-Manual Payout

Definitions:

| CA1701 | The | coin | type | number | as | referred | to | in | the | MDB | Interface |
|---|---|---|---|---|---|---|---|---|---|---|---|

      Specification. If not an MDB system, the number represents the coin's
      position in the coin set starting with the lowest value coin accepted. Note if
      two or more vintage of the same coin is accepted, the oldest one is first.

         For example, the Canadian coin types may be:

| 0 | Old Nickel | 3 | Quarter |
|---|---|---|---|
| 1 | New Nickel | 4 | $1 Dollar |
| 2 | Dime | 5 | $2 Dollar |

| CA1702 | The | cash | value | of | the | coin | (units | base). |
|---|---|---|---|---|---|---|---|---|

         For example, the Canadian coin types would be:

| Nickel | 5 | $1 | Dollar | 100 |
|---|---|---|---|---|
| Dime | 10 | $2 | Dollar | 200 |
| Quarter | 25 |  |  |  |

| CA1703 | The | number | of | coins | in | the | coin | tube | (or | tubes | if | multiple | tubes |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

      per coin) that are reported by the coin mech during normal vending
      operations. Note that this is the "best known tube count" and may be
      inaccurate if coins were manually added or removed by hand.

| CA1704 | The | number | of | coins | inserted | while | the | changer | was | in |
|---|---|---|---|---|---|---|---|---|---|---|

      Controlled manual fill mode. Controlled manual fill indicates that the coins
      are being inserted under the control of the coin mech or VMC. Coins are not
      being loaded by hand through the tops of the tubes.

| CA1705 | The | number | of | coins | dispensed | while | the | changer | was | in |
|---|---|---|---|---|---|---|---|---|---|---|

      controlled manual payout mode. Controlled manual payout indicates that the
      coins are being dispensed under the control of the coin mech or VMC. Coins
      are not being removed by hand by "dumping" the tubes.

      VMC Command Code Sub-command VMC Data Changer Response
| EXPANSION | 0FH | FAH |  |  | Y1-Y5 | Z1 | - Zn | (immediate | or |
|---|---|---|---|---|---|---|---|---|---|
| COMMAND | FTL | REQ | TO | RCV |  |  |  | POLLed) |  |

      The VMC is requesting to receive data from the changer whose destination
      address will always be (08H). Note that all FTL Commands / Responses are
      defined in Section 2.6.

| Y1 | = | Destination address of command | (08H) |
|---|---|---|---|
| Y2 | = | Source address of command |  |
| Y3 | = | File ID |  |
| Y4 | = | Maximum length |  |
| Y5 | = | Control |  |

| Z1 | = | 1DH which indicates | SEND BLOCK |
|---|---|---|---|
| Z2 | = | Destination address | of data |
| Z3 | = | Block # |  |
| Z4 | - Z34 | =    Data (maximum of 31 | bytes) |

                                 or
| Z1 | =          1CH which indicates RETRY / DENY |
|---|---|
| Z2 | =          Destination address of response |
| Z3 | =          Source address of response (08H) |
| Z4 | =          Retry delay |

      VMC Command Code Sub-command VMC Data Changer Response
| EXPANSION | 0FH | FBH | Y1-Y3 | None |
|---|---|---|---|---|

## Command     Ftl Retry / Deny

      The VMC is retrying, denying, or aborting a data transfer to/from the changer
      whose destination address will always be (08H). Note that all FTL
      Commands / Responses are defined in Section 2.6.

| Y1 | =          Destination address of command | (08H) |
|---|---|---|
| Y2 | =          Source address of command |  |
| Y3 | =          Retry delay |  |

      VMC Command Code Sub-command VMC Data Changer Response
| EXPANSION | 0FH | FCH | Y1-Y33 | None |
|---|---|---|---|---|

## Command     Ftl Send Block

      The VMC is sending data to the changer whose destination address will
      always be (08H). Note that all FTL Commands / Responses are defined in
      Section 2.6.

| Y1 | =       Destination | address | of | command | & data | (08H) |
|---|---|---|---|---|---|---|
| Y2 | =       Block # |  |  |  |  |  |

      Y3 - Y33 = Data (maximum of 31 bytes)

      VMC Command Code Sub-command VMC Data Changer Response
| EXPANSION | 0FH | FDH |  | Y1-Y2 | Z1-Z34 | (immediate | or |
|---|---|---|---|---|---|---|---|
| COMMAND | FTL | OK TO | SEND |  |  | POLLed) |  |

      The VMC is indicating that it is OK for the changer to transfer data. The
      destination address will always be the changer (08H). Note that all FTL
      Commands / Responses are defined in Section 2.6.

| Y1 | =          Destination address of command | (08H) |
|---|---|---|
| Y2 | =          Source address of command |  |

| Z1 | = | 1DH which indicates SEND BLOCK |
|---|---|---|
| Z2 | = | Destination address of data |
| Z3 | = | Source address of data |
| Z4 | - Z34 | =    Data (maximum of 31 bytes) |

      VMC Command Code Sub-command VMC Data Changer Response
| EXPANSION | 0FH | FEH |  |  | Y1-Y5 | Z1 | (immediate | or |
|---|---|---|---|---|---|---|---|---|
| COMMAND | FTL | REQ | TO | SEND |  |  | POLLed) |  |

      The VMC is requesting to send data to the changer whose destination
      address will always be (08H). Note that all FTL Commands / Responses are
      defined in Section 2.6.

| Y1 | = | Destination address of command | (08H) |
|---|---|---|---|
| Y2 | = | Source address of command |  |
| Y3 | = | File ID |  |
| Y4 | = | Maximum length |  |
| Y5 | = | Control |  |

| Z1 | =          1EH which indicates OK TO SEND |
|---|---|
| Z2 | =          Destination address of response |
| Z3 | =          Source address of response (08H) |

                                 or
| Z1 | = | 1CH which indicates RETRY / DENY |
|---|---|---|
| Z2 | = | Destination address of response |
| Z3 | = | Source address of response (08H) |
| Z4 | = | Retry delay |

| VMC Command | Code Sub-command | VMC Data | Changer | Response |
|---|---|---|---|---|
| EXPANSION | 0FH FFH | Y1-Yn | Z1-Zn |  |

## Command     Diagnostics

| Y1 | - Yn | =     Device | manufacturer | specific | instruction | for | implementing |
|---|---|---|---|---|---|---|---|

                    various manufacturing or test modes. Y1 - Yn implies that any
                    number of bytes can be used for the VMC data to the
                    peripheral.

| Z1 | - Zn | =     Device | manufacturer | specific | responses | after | receiving |
|---|---|---|---|---|---|---|---|

                    manufacturing or test instructions. Z1 - Zn implies that any
                    number of bytes can be used for the changer response data
                    from the peripheral.

#### 5.4 Changer Non-Response Time

      The maximum non-response time for the changer is two seconds.

#### 5.5 Changer Power Requirements

      The current draw for any changer must fall within the following limits. All
      measurements are at the minimum VMC Voltage Output.

| Idle | mode | = | 200 | mA. | (max.) | continuous |
|---|---|---|---|---|---|---|

| Coin | acceptance | = | 1.8 | A. | (max.) | for | up | to | 2 seconds |
|---|---|---|---|---|---|---|---|---|---|

                                  (For coin changers using solenoid based payout
                                  mechanisms - typical of 3 tube changers sold in
                                  the US market. Vending machines sold into the
                                  US market are required to supply this power.)

#### 1.0 A. (max.) for up to 2 seconds

                                  (For coin changers using motorized payout
                                  mechanisms - typical of 4 tube changers.)

| Coin | payout | = | 3.6 | A. | (max.) | for | 100 | mS. | with | 400 | mS. | idle |
|---|---|---|---|---|---|---|---|---|---|---|---|---|

                                  current between pulses during the coin payout
                                  cycle.
                                  (For coin changers using solenoid based payout
                                  mechanisms - typical of 3 tube changers sold in
                                  the US market. Vending machines sold into the
                                  US market are required to supply this power.)

#### 1.8 A. (max.) during the coin payout cycle.

                                  (For coin changers using motorized payout
                                  mechanisms - typical of 4 tube changers.

See Note 2 under the DISPENSE (0DH) command for further information on the
coin payout cycles.)

      Note: If both peripherals are supported, vending machines should be able to
      provide sufficient power to simultaneously supply the above power
      requirements for both the coin changer Coin Acceptance and bill validator
      Bill Transport as specified in Section 6.5.

#### 5.6 Coin Acceptor/Changer Examples

| Event |  | Exchange |
|---|---|---|
| Power up at VMC or JUST RESET received by | VMC | Reset sequence |
| any other time without reset sequence |  | Enable sequence |
| Enter service mode |  | Disable sequence |
| Enter sales mode |  | Enable sequence |
| Consumer inserts coin |  | Coin Accept sequence |
| Credit acceptance is suspended (max. vend | price | Disable sequence |

      achieved, free vend token accepted, etc.)
| Coins | are | dispensed | Disable | sequence |
|---|---|---|---|---|

                                                                    Dispense sequence
                                                                    Enable sequence
| Error situation is detected at coin mech. |  |  | Error sequence |
|---|---|---|---|
| Manual dispense of coins at coin mech. (only | while | door | Manual Dispense |
| is open) |  |  | sequence |
| Manual filling of coins at coin mech. |  |  | Manual Filling sequence |

Reset sequence
| VMC |  | Coin | Mechanism | Comments |
|---|---|---|---|---|
| RESET |  |  |  | Reset command |

##     Ack

| POLL |  |  |  | Allow peripheral to |
|---|---|---|---|---|
|  |  | JUST | RESET | confirm RESET command |

## Ack                          

| STATUS |  |  |  |  | Collect operational |
|---|---|---|---|---|---|
|  |  | COIN | MECH. | CONFIG. | parameters |

## Ack                          

| EXPANSION/ID |  |  |  |  | Collect | asset | inf. | and |
|---|---|---|---|---|---|---|---|---|
|  |  | COIN | MECH. | ID | options | list |  |  |

## Ack                          

| EXPANSION/ | FEATURE |  | Enable | compatible | options |
|---|---|---|---|---|---|

## Enable

##     Ack

Error sequence
| VMC | Coin | Mechanism | Comments |
|---|---|---|---|

## Poll                         

|  |  | STATUS/ERROR | Error | sent | from | coin |
|---|---|---|---|---|---|---|
| ACK |  |  | mech. |  |  |  |

Enable sequence
| VMC |  |  | Coin | Mechanism | Comments |
|---|---|---|---|---|---|
| TUBE | STATUS |  |  |  | Update current tube |
|  |  |  | TUBE | STATUS | status counters |

## Ack                        

| COIN | TYPE | ENABLE |  | Enable | appropriate | coin | types |
|---|---|---|---|---|---|---|---|

##     Ack

Disable sequence
| VMC |  |  |  | Coin | Mechanism | Comments |  |  |
|---|---|---|---|---|---|---|---|---|
| COIN | TYPE | ENABLE |  |  |  | Disable all | coin | types |

##     Ack

| Coin | Accepted | sequence |  |  |
|---|---|---|---|---|
| VMC |  | Coin | Mechanism | Comments |

## Poll                       

|  | COINS | DEPOSITED | Coin | type, | routing, | and | tube |
|---|---|---|---|---|---|---|---|

                                                     count

## Ack                        

| Coin | dispense | sequence | VMC | algorithm |  |
|---|---|---|---|---|---|
| VMC |  |  |  | Coin Mechanism | Comments |
| TUBE | STATUS |  |  |  | Update current tube |
|  |  |  |  | TUBE STATUS | status counters |

## Ack                        

| DISPENSE |  | Pay | out | first | coin |
|---|---|---|---|---|---|

##     Ack

| POLL |  |  |  |  | Check to make sure coin |
|---|---|---|---|---|---|
|  |  | PAY | OUT | BUSY | pay out is complete |

## Ack                        

                           .
                           .
                           .
| POLL |  |  |  |  | Changer confirms coin |
|---|---|---|---|---|---|
|  |  |  | ACK |  | pay out complete |
| TUBE | STATUS |  |  |  | Update current tube |
|  |  |  | TUBE | STATUS | status counters |

## Ack                        

| DISPENSE |  |  | Pay out | second | coin |
|---|---|---|---|---|---|
|  |  | ACK | etc. |  |  |

| Coin | dispense | sequence | Alternative | pay | out |
|---|---|---|---|---|---|

                           method
| VMC |  | Coin | Mechanism | Comments |  |  |  |  |
|---|---|---|---|---|---|---|---|---|
| EXPANSION/ |  |  |  | Report value | to | be | paid | out |

## Alt. Pay Out

##     Ack

| EXPANSION/ |  | Request | paid | value |
|---|---|---|---|---|

## Alt. Pay Out Value

POLL
|  | VALUE | PAID | “value” | paid | since | last | VALUE |
|---|---|---|---|---|---|---|---|

                                                     POLL (may be 00)

## Ack                        

                            .
                            .
                            .
| EXPANSION/ |  | Request | paid | value |
|---|---|---|---|---|

## Alt. Pay Out Value

POLL
|  |  | ACK | Pay out | is complete |
|---|---|---|---|---|
| EXPANSION/ |  |  | Request | pay out status |

## Alt. Pay Out Status

|  |  |  | COINS PAID | Itemization of coins |
|---|---|---|---|---|
| ACK |  |  |  | paid |
| TUBE | STATUS |  |  | Update current tube |
|  |  |  | TUBE STATUS | status counters |

## Ack                        

| Manual | dispense | sequence |  |  |
|---|---|---|---|---|
| VMC |  | Coin | Mechanism | Comments |

## Poll                       

|  | COINS DISPENSED | Number, type, | and tube | levels |
|---|---|---|---|---|
|  | MANUALLY | for coin just | manually |  |

                                                     dispensed

## Ack                        

| TUBE | STATUS |  |  |  | Update | current tube |
|---|---|---|---|---|---|---|
|  |  |  | TUBE | STATUS | status | counters |

## Ack                        

| Manual | fill | sequence |  |  |
|---|---|---|---|---|
| VMC |  | Coin | Mechanism | Comments |

## Expansion Command          

(Send controlled manual
fill report)
|  | NUMBER OF | Number for coins manually |  |
|---|---|---|---|
|  | CONTROLLED MANUAL | filled, only possible, if | the |
|  | MODE FILLED COINS | changer supports extended |  |

                                                     diagnostics and/or controlled
                                                     manual filled and payout
                                                     reports (at least b2 set in the
                                                     options bytes)

## Ack                        

| TUBE | STATUS |  |  |  | Update | current tube |
|---|---|---|---|---|---|---|
|  |  |  | TUBE | STATUS | status | counters |

## Ack                        

Section 6
   Bill Validator / Recycler
   VMC/Peripheral Communication Specifications

#### 6.1 Introduction

      This section defines the communication bytes sent and received between a Bill
      Validator / Recycler and the VMC. In the text below, all references to “bill
      validator” includes the optional bill recycler except where expressly noted.

      As defined in Section 2.3, the bill validator’s address is 00110xxxB (30H).

      Unless stated otherwise, all information is assumed to be in a binary format.

      There are currently two levels of support defined for the bill validator interface,
      Level 1 and Level 2. The level of bill validator operation is sent to the VMC in the
      response to the STATUS command (defined later in this section). The following
      paragraphs will define how a VMC should differentiate between each level.

      Level 1 Bill Validators

      Level 1 bill validators support all standard functions, but do not support any
      optional features.

      Level 2 Bill Validators

      Level 2 bill validators support all standard functions plus various optional features
      as defined in Section 6.3 under the Expansion command 37-02H. Based on the
      optional feature information the VMC will determine the appropriate operating
      mode (in other words, modes that both the bill validator and the VMC can
      support), enable any appropriate features by sending an appropriate feature
      enable command back to the bill validator, and enter the proper operating mode.
      This technique allows all VMCs and peripherals to accommodate existing feature
      capabilities and provides a means for upgrading Level 2 equipment.

      Level 2 bill validator / recyclers will also support all standard functions plus the
      optional recycling feature as defined in Section 6.3 under the Expansion
      command 37-02H. Additional commands 37-03H through 37-09H allow control of
      the bill recycler. The unit should NOT respond to any Recycler/Dispensor
      commands or send any Recycler POLL responses unless the Bill Recycler
      expansion commands are enabled by the VMC (b1=1) and the VMC has
      request the DISPENSER SETUP (37 03) command.

#### 6.2 VMC Commands

      .
| Command | Hex | Code | Description |
|---|---|---|---|

| RESET | 30H | Command | for | bill | validator | to | self-reset. |
|---|---|---|---|---|---|---|---|

| SETUP | *              31H | Request | for | bill | validator | setup | information. |
|---|---|---|---|---|---|---|---|

| SECURITY | 32H | Sets | Validator | Security | Mode |
|---|---|---|---|---|---|

| POLL | 33H | Request | for | Bill | Validator | activity | Status. |
|---|---|---|---|---|---|---|---|

| BILL | TYPE | 34H | Indicates | Bill | Type | enable | or | disable. |
|---|---|---|---|---|---|---|---|---|

                                         Command is followed by set-up data.
                                         See command format.

| ESCROW | 35H | Sent | by | VMC | to | indicate | action | for |
|---|---|---|---|---|---|---|---|---|

                                         a bill in escrow.

| STACKER | 36H | Indicates | stacker | full | and | the |
|---|---|---|---|---|---|---|

                                         number of bills.

| EXPANSION | 37H | Command to allow addition of | features and |
|---|---|---|---|
| COMMAND |  | future enhancements. Level 1 | and above bill |

                                         validators must support this command.

      NOTE: The expansion command is always followed by a sub-command.

      - In Version 1.0 & 2.0, SETUP was called STATUS.

#### 6.3 VMC Command Format

| VMC Command | Code | VMC Data |
|---|---|---|
| RESET | 30H | No data bytes |

      This command is the vehicle that the VMC should use to tell the validator that it
      should return to its default operating mode. It should reject any bills in the
      validation process, return any bills in the escrow position, and disable all other
      activity until otherwise instructed by the VMC.

      The following initialization sequence is recommended for all new VMCs designed
      after July, 2000. It should be used after “power up”, after issuing the RESET
      command, after issuing the Bus Reset (pulling the transmit line “active” for a
      minimum of 100 mS), or anytime a POLL command results in a “JUST RESET”
      response (i.e., peripheral self resets).

      POLL – `33h`
           To obtain “JUST RESET” response
      SETUP – `31h`
          To obtain bill validator level and configuration information
      EXPANSION IDENTIFICATION – 37 `00h` (Level 01+)
          To obtain additional bill validator information
      EXPANSION IDENTIFICATION w/ OPTION BITS – 37 `02h` (Level 02+ only)
          To obtain additional bill validator information and options
      EXPANSION FEATURE ENABLE – 37 `01h` (Level 02+ only)
          To enable desired options
      STACKER – `36h`
          To obtain stacker status and number of bills
      BILL TYPE – `34h`
            To enable desired bill acceptance and desired bill escrow capability

| VMC Command | Code | Validator | Response | Data |
|---|---|---|---|---|
| SETUP | 31H | 27 bytes: | Z1 - Z27 |  |

| Z1 | = | Bill | Validator | Feature | Level | - 1 | byte |
|---|---|---|---|---|---|---|---|

                    Indicates current feature level of the bill validator. Currently defined
                    levels are:
                             Level 1 - does not support option bits (Z1 = `01h`)
| Level | 2 - | supports | option | bits | (Z1 | = 02h) |
|---|---|---|---|---|---|---|

| Z2 | - Z3 | =     Country | / Currency | Code | - 2 | bytes |
|---|---|---|---|---|---|---|

                    The packed BCD country / currency code of the bill validator can be
                    sent in two different forms depending on the value of the left most
                    BCD digit.

                    If the left most digit is a 0, the International Telephone Code is used
                    to indicate the country that the validator is set-up for. For example,
                    the USA code is 00 01H (Z2 = 00 and Z3 = 01).

                    If the left most digit is a 1, the latest version of the ISO 4217 numeric
                    currency code is used (see Appendix A1). For example, the code for
                    the US dollar is 18 40H (Z2 = 18 and Z3 = 40) and for the Euro is
                    1978 (Z2 = 19 and Z3 = 78).

                    All new designs after July, 2000 must use the ISO 4217 numeric
                    currency codes as listed in Appendix A1.

| Z4 | - Z5 | =     Bill | Scaling | Factor | - 2 | bytes |
|---|---|---|---|---|---|---|

                    All accepted bill values must be evenly divisible by this number. For
                    example, this could be set to 0064H for the USA.

| Z6 | = | Decimal | Places | - 1 | byte |
|---|---|---|---|---|---|

                    Indicates the number of decimal places on a credit display. For
                    example, this could be set to 02H for the USA.

| Z7 | - Z8 | =     Stacker | Capacity | - 2 | bytes |
|---|---|---|---|---|---|

                    Indicates the number of bills that the stacker will hold. For example,
                    400 bill capacity = 0190H.

| Z9 | - Z10 | =    Bill | Security | Levels | - 2 | bytes |
|---|---|---|---|---|---|---|

                    Indicates the security level for bill types 0 to 15. Since not all
                    validators support multiple security levels, validators that do not have
                    this feature must report a “high” security level.

| Z11 | = | Escrow/No | Escrow | - 1 | byte |
|---|---|---|---|---|---|

                    Indicates the escrow capability of the bill validator. If Z11 = 00H, the
                    bill validator does not have escrow capability. If Z11 = FFH, the bill
                    validator has escrow capability.
      Z12 - Z27 = Bill Type Credit - 16 bytes
                  Indicates the value of the bill types 0 to 15. Values must be sent in
                  ascending order. This number is the bill's monetary value divided by
                  the bill scaling factor. Unused bill types are sent as 00H. Unsent bill
                  types are assumed to be zero. FFH bills are assumed to be vend
                  tokens.

| VMC | Command | Code | VMC | Data |
|---|---|---|---|---|

| SECURITY |  | 32H |  |  | 2 | Bytes: | Y1 | - Y2 |
|---|---|---|---|---|---|---|---|---|
| Y1 - Y2 = | Bill | Type(s) | - 2 | bytes |  |  |  |  |

                    b15 b14 b13 b12 b11 b10 b9 b8 | b7 b6 b5 b4 b3 b2 b1 b0

## Y1                                                                Y2

                    A bit is set to indicate the type of bill(s) which are set to a “high”
                    security level. Note that validators that do not support dual security
                    levels should report a “high” security level in the response bytes Z9-
                    Z10 to the STATUS (31H) command.

| VMC | Command | Code | Validator | Response | Data |
|---|---|---|---|---|---|

| POLL |  |  | 33H | 16 bytes: Z1 | - Z16 |
|---|---|---|---|---|---|
| Z1 - | Z16 | =    Bill | Validator | Activity - 16 bytes |  |

                    Indicates the validator activity, for example, the type and number of
                    bills accepted, stacker position, recycler actions, or error conditions.
                    If there is nothing to report, the validator should send only an ACK.
                    Otherwise, the only valid responses are:
      Bills Accepted:
                   Indicates the type and number of bills accepted, validator stacker
                   status, or recycler status. The first four Bill Routing responses (yyy =
                   000 to 011) should be used to add or subtract credit. The last four
                   Bill Routing responses (yyy = 100 to 111) are for audit information
                   (EVS-DTS fields).
                    Z1
                    (1yyyxxxx)
| yyy | = | Bill | Routing; | 000: | BILL | STACKED |
|---|---|---|---|---|---|---|

                                                 001: ESCROW POSITION2
                                                 010: BILL RETURNED
                                                 011: BILL TO RECYCLER1
                                                 100: DISABLED BILL REJECTED
                                                 101: BILL TO RECYCLER – MANUAL FILL1,3
                                                 110: MANUAL DISPENSE1
                                                 111: TRANSFERRED FROM RECYCLER

## To Cashbox1

| xxxx | = | Bill | Type | (0 | to | 15) |
|---|---|---|---|---|---|---|

                    Notes:

### 1. These responses can only be sent if the Bill Recycler

                           expansion commands are enabled by the VMC (b1=1) and
                           the VMC has request the RECYCLER ENABLE (37 04)
                           command.

### 2. A bill should not be considered secure unless the VMC gets

                           the Bill Stacked or Bill To Recycler response.

### 3. If during manual fill mode a bill is put into the cashbox the

                           validator/recycler must report a “BILL TO RECYCLER –
                           MANUAL FILL” and “TRANSFERRED FROM RECYCLER TO

## Cashbox”.

                           (Status codes continued on next two pages)

| Status: |  | Bill Validator (Only) |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|
|  | (00000001) | =          Defective Motor3 - One | of | the | motors | has | failed | to |

                                         perform its expected assignment.
| (00000010) | =          Sensor | Problem3 | - One | of | the | sensors | has | failed |
|---|---|---|---|---|---|---|---|---|

                                         to provide its response.
| (00000011) | =          Validator | Busy2 | - The | validator | is | busy | and | can | not |
|---|---|---|---|---|---|---|---|---|---|

                                         answer a detailed command right now.
| (00000100) | =          ROM | Checksum | Error3 | - The | validators | internal |
|---|---|---|---|---|---|---|

                                         checksum does not match the calculated
                                         checksum.
| (00000101) | =          Validator | Jammed3 | - A | bill(s) | has | jammed | in | the |
|---|---|---|---|---|---|---|---|---|

                                         acceptance path.
| (00000110) | =          Validator | was | reset1 | - The | validator | has | been | reset |
|---|---|---|---|---|---|---|---|---|

                                         since the last POLL.
| (00000111) | =          Bill | Removed1 | - A | bill | in | the | escrow | position | has |
|---|---|---|---|---|---|---|---|---|---|

                                         been removed by an unknown means. A BILL
                                         RETURNED message should also be sent.
| (00001000) | =          Cash | Box | out | of | position3 | - The | validator | has |
|---|---|---|---|---|---|---|---|---|

                                         detected the cash box to be open or removed.
| (00001001) | =          Validator | Disabled2 | - The | validator | has | been |
|---|---|---|---|---|---|---|

                                         disabled, by the VMC or because of internal
                                         conditions.
| (00001010) | =          Invalid | Escrow | request1 | - An | ESCROW | command |
|---|---|---|---|---|---|---|

                                         was requested for a bill not in the escrow position.
| (00001011) | =          Bill | Rejected1 | - A | bill | was | detected, | but | rejected |
|---|---|---|---|---|---|---|---|---|

                                         because it could not be identified.
| (00001100) | =          Possible | Credited | Bill | Removal1 | – There | has | been |
|---|---|---|---|---|---|---|---|

                                         an attempt to remove a credited (stacked) bill.
                                            Note:
                                            - validators must have a means to disable this code
                                                  due to potential older VMC issues.
                                            - virtually all VMCs designed prior to this code’s
                                                  introduction (10/16/02) will not support it.
                                            - It is a vending machine system issue as to what is
                                                  done when this code is received.

| (010xxxxx) | =          Number | of | attempts | to | input | a bill | while | validator | is |
|---|---|---|---|---|---|---|---|---|---|

                                         disabled.1

| NOTE: | The | validator may send several of one | type activity* up to 16 bytes total. |  |  |  |
|---|---|---|---|---|---|---|
|  |  | 1   Sent once each occurrence. |  |  |  |  |
|  |  | 2   Sent once each POLL |  |  |  |  |
|  |  | 3   Sent once each occurrence. | The validator is then disabled until | the | condition | is |

                        removed. Validator will respond with validator disabled until repaired or
                        replaced.
            - Type activity is defined as Bills Accepted and Status. All may be combined in a
             response to a POLL command providing the total number of bytes does not
             exceed 16.

| Status: |  | Bill Recycler (Only) |  |
|---|---|---|---|
| (00100001) | =            Escrow | request1 - An escrow lever | activation |

                                           has been detected. If a button is present and
                                           activated.
| (00100010) | =           Dispenser | Payout | Busy2 | - The | dispenser | is |
|---|---|---|---|---|---|---|

                                           busy activating payout devices.
| (00100011) | =           Dispenser | Busy2 | - The | dispenser | is | busy | and |
|---|---|---|---|---|---|---|---|

                                           can not answer a detailed command right now.
| (00100100) | =           Defective | Dispenser | Sensor4 | - The | dispenser | has |
|---|---|---|---|---|---|---|

                                           detected one of the dispenser sensors behaving
                                           abnormally.
| (00100101) | =           Not Used |  |
|---|---|---|
| (00100110) | =           Dispenser | did not start / motor problem4. |
| (00100111) | =           Dispenser | Jam4 - A dispenser payout attempt |

                                           has resulted in jammed condition.
| (00101000) | =           ROM | checksum | error4 | - The | dispensers | internal |
|---|---|---|---|---|---|---|

                                           checksum does not match the calculated
                                           checksum. (If separate from validator
                                           microprocessor.)
| (00101001) | =           Dispenser | disabled | – dispenser | disabled |
|---|---|---|---|---|

                                           because of error or bill in escrow position.
| (00101010) | =           Bill waiting2,5 – waiting | for | customer removal |
|---|---|---|---|
| (00101011) | =           Not Used |  |  |
| (00101100) | =           Not Used |  |  |
| (00101101) | =           Not Used |  |  |
| (00101110) | =           Not Used |  |  |
| (00101111) | =           Filled key pressed1 – The | VMC | should request |

                                           a new DISPENSER STATUS.
| NOTES: | The | dispenser | may | send | several | of | one | type | activity, | up | to |
|---|---|---|---|---|---|---|---|---|---|---|---|

                    16 bytes total include both bill validator and bill recycler. This will permit
                    zeroing counters such as inventory and status. These responses can only
                    be sent if the Bill Recycler expansion commands are enabled by the VMC
                    (b1=1) and the VMC has request the DISPENSER SETUP (37 03)
                    command.
                    1 Sent once each occurrence.
                    2 Sent once each POLL
                    3 Not used
                    4 Sent once each occurrence. The dispenser is then internally disabled
                       until the condition is removed. If the validator can still be used.
                       Dispenser will respond with dispenser disabled until the condition is
                       removed. If the failure affects both the validator and dispenser it will
                       respond with both validator disabled and dispenser disabled until the
                       condition is removed.
                    5 VMC must monitor this flag along with the PAYOUT VALUE POLL
                       command (alternate Poll (33H) and Payout Status (37H-09H)
                       commands) to determine when the recycler dispense operations are
                       complete, or if a bill is in the inlet waiting for a customer to remove it.

      File Transport Layer POLLed responses:

      Note that all FTL responses are defined in Section 2.6. For the bill validator, the
      source address will always be the validator (30H) as defined in Section 2.3.

             Z1

| 1B | REQ | TO | RCV | The | bill | validator | is | requesting | to |
|---|---|---|---|---|---|---|---|---|---|

                                         receive data from a device or VMC.

                                         Z2 = Destination address of response
                                         Z3 = Source address of response (30H)
                                         Z4 = File ID
                                         Z5 = Maximum length
                                         Z6 = Control

| 1C | RETRY/DENY | The | bill | validator | is | requesting | a device | or |
|---|---|---|---|---|---|---|---|---|

                                         VMC to retry or deny the last FTL command.

                                         Z2 = Destination address of response
                                         Z3 = Source address of response (30H)
                                         Z4 = Retry delay

| 1D | SEND | BLOCK | The | bill | validator | is | sending | a block | of | data |
|---|---|---|---|---|---|---|---|---|---|---|

                                         (maximum of 31 bytes) to a device or VMC.

                                         Z2 = Destination address of data
                                         Z3 = Block #
                                         Z4-Z34 = Data (maximum of 31 bytes)

| 1E | OK | TO | SEND | The | bill | validator | is | indicating | that | it | is | OK | for |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                                         the device or VMC to send it data.

                                         Z2 = Destination address of response
                                         Z3 = Source address of response (30H)

| 1F | REQ | TO | SEND | The | bill | validator | is | requesting | to |
|---|---|---|---|---|---|---|---|---|---|

                                         send data to a device or VMC.

                                         Z2 = Destination address of response
                                         Z3 = Source address of response (30H)
                                         Z4 = File ID
                                         Z5 = Maximum length
                                         Z6 = Control

| VMC Command | Code | VMC Data |  |  |
|---|---|---|---|---|
| BILL TYPE | 34H | 4 bytes: | Y1 | - Y4 |

| Y1 | - Y2 | =     Bill | Enable | - 2 | bytes |
|---|---|---|---|---|---|

                    Indicates what type of bills are accepted.

                    b15 b14 b13 b12 b11 b10 b9 b8 | b7 b6 b5 b4 b3 b2 b1 b0

## Y1                                                                  Y2

                    Bill types are 0 to 15. A bit is set to indicate acceptance of bill type.

      NOTE: Sending 0000H disables the bill validator.

| Y3 | - Y4 | =     Bill | Escrow | Enable: |
|---|---|---|---|---|

                    b15 b14 b13 b12 b11 b10 b9 b8 | b7 b6 b5 b4 b3 b2 b1 b0

## Y3                                                                  Y4

                    Bill types are 0 to 15. A bit is set to indicate enable of escrow for a
                    bill type.

      NOTE: On power-up or reset all bill acceptance and escrow are disabled.

| VMC | Command | Code | VMC | Data |
|---|---|---|---|---|

| ESCROW | 35H | 1 | byte: | Y1 |
|---|---|---|---|---|

| Y1 | =          Escrow | status | - 1 | byte |
|---|---|---|---|---|

| If | Y1 | = 0; | Return bill in | the escrow position. |
|---|---|---|---|---|
| If | Y1 | = xxxxxxx1; | Stack the bill | (“x” indicates don’t |

                                                  care)

| NOTE: | After | an | ESCROW | command | the | bill | validator | should | respond | to |
|---|---|---|---|---|---|---|---|---|---|---|

      POLL command with the BILL STACKED, BILL RETURNED, INVALID ESCROW
      or BILL TO RECYCLER message within 30 seconds. If a bill becomes jammed in
      a position where the customer may be able to retrieve it, the bill validator should
      send a BILL RETURNED message.

      It is the responsibility of the VMC to stack or return any bills in escrow PRIOR to
      issuing the DISPENSE BILL or DISPENSE VALUE message. Leaving a bill in
      escrow position may lead to failed recycler operations.

| VMC Command | Code | Validator Response | Data |
|---|---|---|---|
| STACKER | 36H | 2 bytes: Z1 - Z2 |  |

      Indicates stacker full condition and the number of bills in the stacker.

## Z1            Z2

      (Fxxxxxxx) (xxxxxxxx)
      F = 1 if stacker is full, 0 if not.

      xxxxxxxxxxxxxxx = The number of bills in the stacker.

      LEVEL ONE and TWO+ CAPABILITIES - EXPANSION COMMAND

      In order to allow existing VMCs to operate with original Level 1 or new Level 2 bill
      validators, a separate identification sub-command has been introduced to handle
      the additional 4 bytes of Option Bit information.

      The original sub-command 00H is used for obtaining Z1 to Z29 identification
      information from bill validators. This information includes the model number,
      serial number, software version, etc, but not the option bits. Note that if a
      Level 2+ bill validator is sent the 00H sub-command, it must not report the
      Z30 to Z33 option bytes.

      Sub-command 01H is used for Level 2+ bill validators to enable option bits
      reported in the expansion command 02H sub-command below.

      The new sub-command 02H is used for obtaining Z1 to Z33 identification
      information from Level 2+ bill validators. This information includes the model
      number, serial number, software version, etc, and the option bits (Z30-Z33).

| VMC Command | Code Sub-Command | Validator | Response | Data |
|---|---|---|---|---|
| EXPANSION | 37H 00H | 29 bytes: | Z1 - Z29 |  |

## Command                 Level 1 Identification Without Option Bits

| Z1 | - Z3 | =       Manufacturer | Code | - 3 | bytes |
|---|---|---|---|---|---|

                      Identification code for the equipment supplier. Sent as ASCII
                      characters. Currently defined codes are listed in the EVA document
                      entitled " European Vending Association Data Transfer
                      Standard" (EVA-DTS), the Audit Data Lists section, sub-section 2,
                      "Manufacturer Codes".

| Z4 | - Z15 | =    Serial | Number | - 12 | bytes |
|---|---|---|---|---|---|

                    Factory assigned serial number. All bytes must be sent as ASCII
                    characters, zeros (30H) and blanks (20H) are acceptable.

      Z16 - Z27 = Model #/Tuning Revision - 12 bytes
                  Manufacturer assigned model number. All bytes must be sent as
                  ASCII characters, zeros (30H) and blanks (20H) are acceptable.

      Z28 - Z29 = Software Version - 2 bytes
                  Current software version. Must be sent in packed BCD.

| VMC Command | Code Sub-Command | VMC Data |  |  |
|---|---|---|---|---|
| EXPANSION | 37H 01H | 4 bytes: | Y1 | - Y4 |

## Command              Level 2+ Feature Enable

      This command is used to enable each of the Level 2+ optional features defined in
      the Level 2+ Identification response bytes Z30-Z33 below. To enable a feature a
      bit is set to one. All optional features are disabled after reset.

| VMC Command | Code Sub-Command | Validator | Response | Data |
|---|---|---|---|---|
| EXPANSION | 37H 02H | 33 bytes: | Z1 – Z33 |  |

## Command              Level 2+ Identification With Option Bits

| Z1 | - Z3 | =     Manufacturer | Code | - 3 | bytes |
|---|---|---|---|---|---|

                    Identification code for the equipment supplier. Sent as ASCII
                    characters. Currently defined codes are listed in the EVA document
                    entitled " European Vending Association Data Transfer
                    Standard" (EVA-DTS), the Audit Data Lists section, sub-section 2,
                    "Manufacturer Codes".

| Z4 | - Z15 | =    Serial | Number | - 12 | bytes |
|---|---|---|---|---|---|

                    Factory assigned serial number. All bytes must be sent as ASCII
                    characters, zeros (30H) and blanks (20H) are acceptable.

      Z16 - Z27 = Model #/Tuning Revision - 12 bytes
                  Manufacturer assigned model number. All bytes must be sent as
                  ASCII characters, zeros (30H) and blanks (20H) are acceptable.

      Z28 - Z29 = Software Version - 2 bytes
                  Current software version. Must be sent in packed BCD.

      Z30 - Z33 = Optional Features - 4 bytes

                    Each of the 32 bits indicate an optional features availability. If the bit
                    is set the feature is available. Bits should be sent in descending
                    order, i.e. bit 31 is sent first and bit 0 is sent last. Currently defined
                    options are:

| b0 | -            File | Transport | Layer | (FTL) | supported | as | defined | in |
|---|---|---|---|---|---|---|---|---|

                                    Section 2.6.
| b1 | - | Bill Recycling supported |
|---|---|---|
| b2 | - b31 | Available for future use |

| VMC Command | Code Sub-Command | Recycler | Response | Data |
|---|---|---|---|---|
| EXPANSION | 37H 03H | 2 bytes: | Z1 – Z2 |  |

## Command              Recycler Setup

      (Bill Recycler)

| Z1 | – Z2 | =     Bill | Type | Routing | - 2 | bytes |
|---|---|---|---|---|---|---|

                    Indicates what bill types can be routed to the Recycler dispenser.

                    b15 b14 b13 b12 b11 b10 b9 b8 | b7 b6 b5 b4 b3 b2 b1 b0

## Z1                              Z2

                    Bit is set to indicate a bill type can be routed to the dispenser. Valid bill
                    types are 0 to 15.

| VMC Command | Code Sub-Command | VMC Data |  |  |
|---|---|---|---|---|
| EXPANSION | 37H 04H | 19 bytes: | Y1 | – Y18 |

## Command              Recycler Enable

      (Bill Recycler)

| Y1 | - Y2 | =     Manual | Dispense | Enable | - 2 | bytes |
|---|---|---|---|---|---|---|

                    b15 b14 b13 b12 b11 b10 b9 b8 | b7 b6 b5 b4 b3 b2 b1 b0

## Y1                              Y2

                    A bit is set to indicate manual dispense enable. For example, bit 2 is set to
                    enable manual dispensing of bill type 2. This command enables/disables
                    manual dispensing using optional inventory switches. All manual
                    dispensing switches are automatically disabled upon reset.

| Y3 | – Y18 | =    Bills | Recycler | Enabled | - 16 | bytes |
|---|---|---|---|---|---|---|

                    Indicates which bills will be routed to the Recycler:
                           0 = Bill type disable
                           1 = Only High qualitybills are used
                           2 = Only High and Medium quality bills are used
                           3 = Use all possible bills (this is the recommended setting –
                           the recycler will use its internal setting to determine what bill
                           are put into the recycler)

                    Note: Y3 = Bill Type 0 while Y18 = Bill type 15

| VMC | Command | Code | Sub-Command | Recycler Response | Data |
|---|---|---|---|---|---|
|  | EXPANSION |  | 37H 05H | 34 bytes: Z1 | – Z34 |

## Command           Bill Dispense Status

     (Bill Recycler)

| Z1 | - Z2 | =     Dispenser | Full | Status | - 2 | bytes |
|---|---|---|---|---|---|---|

                    Indicates status of dispenser for bill types 0 to 15.

                    b15 b14 b13 b12 b11 b10 b9 b8 | b7 b6 b5 b4 b3 b2 b1 b0

## Z1                                       Z2

                    A bit is set to indicate a full dispenser. For example, bit 7 = set would indicate
                    the dispenser for bill type 7 is full.

| Z3 | – Z34 | =    Bill | Count | - 32 | bytes |
|---|---|---|---|---|---|

                    Indicates the greatest number of bills that the dispenser “knows” definitely
                    are present in the dispenser. A word (2 bytes) position in the 32 byte string
                    indicates the number of bills in a dispenser for a particular bill type. For
                    example, the first 2 bytes sent indicate the number of bills in a dispenser
                    for dispenser type 0. Unsent bytes are assumed to be zero. For dispenser
                    counts greater than 65535, counts should remain at 65535.

| NOTE: | If | a dispenser | can | detect | a dispenser | jam, | defective | dispenser |
|---|---|---|---|---|---|---|---|---|

      sensor, or other malfunction, it will indicate the dispenser is "bad" by sending a
      dispenser full status and a count of zero for the malfunctioning bill type.

| VMC Command | Code Sub-Command | VMC Data |  |  |
|---|---|---|---|---|
| EXPANSION | 37H 06H | 3 bytes: | Y1 | – Y3 |

## Command              Dispense Bill

      (Bill Recycler)

| Y1 | =          Bill | type | to | be | dispensed |
|---|---|---|---|---|---|

                    b7 b6 b5 b4 b3 b2 b1 b0
                    Bits b7, b6, b5, b4 = 0.
                    Bits b3, b2, b1, b0 indicate bill type to be dispensed.

                    Valid codes are 0H to FH to indicate bill types 0 to 15.

| Y2 | - Y3 | =     Number | of | bills | to | be | dispensed | of | bill | type | defined | in | Y1 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                    There is no defined limit on how long the actual dispense takes since the
                    command allows for up to 65535 bills to be paid out. The payout cycle
                    begins when the dispenser ACKs the VMC’s DISPENSE BILL command.
                    The VMC should wait at least 30 seconds per bill. If the VMC wants to
                    stop the dispensing of bills it can send the CANCEL command.

                    The VMC must send the PAYOUT VALUE POLL message during the
                    dispense operation to monitor payout, decrement the vendor display, and
                    determine when the operation is complete. The VMC must also send the
                    POLL command to determine if any bills are moved from the recycler to
                    the cashbox or a bill is in the inlet waiting for a customer to remove it.
                    After the dispense operation is complete the PAYOUT STATUS command
                    must be sent to determine what bills were dispensed.

                    Only one payout operation (DISPENSE BILL or DISPENSE VALUE) may
                    be active at one time. The bill validator is not expected to buffer additional
                    dispense or payout commands while the current command is active. In
                    addition, the VMC should not issue the DISPENSE BILL command if a bill
                    is waiting to for customer removal or if any bills are in the escrow position.

| VMC Command | Code Sub-Command | VMC Data |  |  |
|---|---|---|---|---|
| EXPANSION | 37H 07H | 2 bytes: | Y1, | Y2 |

## Command              Dispense Value

      (Bill Recycler)

| Y1 | – Y2 | =     Value | of | bills | to | be | paid | out. |
|---|---|---|---|---|---|---|---|---|

                    Y1 and Y2 are defined as the total value of bills to be paid out. This value
                    is expressed as the actual credit value divided by the bill scaling factor.
                    For example, in a USA system using a scaling factor of 100 (64H), if the
                    change to be paid out is $15.00, then Y1 will equal 15. The bill dispenser
                    will determine which actual denominations of bills will be paid out. In the

                    $15.00 example, the bills may be 3 $5 bills; or, 1 $10 bill & 1 $5 bill; or, 2
                    $5 bills & 5 $1 bills, etc. .

                    There is no defined limit on how long the actual dispense takes. The
                    payout cycle begins when the dispenser ACKs the VMC’s DISPENSE
                    VALUE command. The VMC should wait at least 30 seconds per bill. If
                    the VMC wants to stop the dispensing of bills it can send the CANCEL
                    command.

                    The VMC must send the PAYOUT VALUE POLL message during the
                    dispense operation to monitor payout, decrement the vendor display, and
                    determine when the operation is complete. The VMC must also send the
                    POLL command to determine if any bills are moved from the recycler to
                    the cashbox or a bill is in the inlet waiting for a customer to remove it.
                    After the dispense operation is complete the PAYOUT STATUS command
                    must be sent to determine what bills were dispensed.

                    Only one payout operation (DISPENSE BILL or DISPENSE VALUE) may
                    be active at one time. The bill validator is not expected to buffer additional
                    dispense or payout commands while the current command is active. In
                    addition, the VMC should not issue the DISPENSE BILL command if a bill
                    is waiting to for customer removal or if any bills are in the escrow position.

| VMC Command | Code Sub-Command | Recycler Response Data |
|---|---|---|
| EXPANSION | 37H 08H | 32 bytes: Z1 – Z32 |

## Command              Payout Status

      (Bill Recycler)

| Z1 | – Z32 | =    Number | of | each | bill | type | paid | out | (2 | bytes | per | bill | type). |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                    This is the dispenser's response to the last VMC DISPENSE BILL (37-06)
                    or DISPENSE VALUE (37-07) command. Bytes are sent in ascending
                    order of bill types. A byte’s position in the string indicates the bill type.
                    That is, bytes one and two are the number of bills for bill type 1, bytes
                    three and four are the number of bills for bill type two, and so on. Unsent
                    bytes above the bill types dispensed are assumed to be zero.

                    The dispenser clears payout data after an ACK response from the VMC.

                    The VMC should compare the value of the bills paid out to the VMC
                    DISPENSE BILL (37-06) or DISPENSE VALUE (37-07) command.

| NOTES: | 1) | If | the | dispenser’s | payout | is | busy | it | will | respond | to | the | PAYOUT |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                    STATUS command with an ACK only.

                    2) If no bills have been paid out, at least one zero valued data byte
                       must be sent.

| VMC Command | Code Sub-Command | Recycler | Response | Data |
|---|---|---|---|---|
| EXPANSION | 37H 09H | 2 bytes: | Z1 – Z2 |  |

## Command              Payout Value Poll

      (Bill Recycler)

| Z1 | – Z2 | = | Dispenser | Payout | Activity | - 2 | bytes |
|---|---|---|---|---|---|---|---|

                    An interval value (scaled) which indicates the amount of paid out bills since
                    the previous PAYOUT VALUE POLL (or between the initial DISPENSE
                    VALUE command and the first PAYOUT VALUE POLL).

                    A 00H response indicates no bills were paid out since the previous
                    PAYOUT VALUE POLL (or the initial DISPENSE VALUE command).

                    An ACK only indicates that the bill payout is finished. This must be
                    followed by the PAYOUT STATUS command to obtain the complete
                    payout data.

| NOTE: | The | initial | intent | of | this | command | is | to | determine | the | amount | of | bills |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                    paid out so that the credit display can be decremented as bills are
                    dispensed.

| VMC Command | Code Sub-Command | Recycler | Response | Data |
|---|---|---|---|---|
| EXPANSION | 37H 0AH | None |  |  |

## Command              Payout Cancel

      (Bill Recycler)

| NOTE: | The | Recycler | should | stop | the | active | payout | function | within | 30 |
|---|---|---|---|---|---|---|---|---|---|---|

                    seconds. The VMC must continue to send the PAYOUT VALUE
                    POLL until it receives an ACK indicating the payout is complete.
                    The VMC must then send the PAYOUT STATUS to determine what
                    bill were dispensed.

                    The VMC MUST issue this command if it implements any type of
                    payout timeout.

VMC Command Code Sub-command VMC Data Validator Response
| EXPANSION | 37H | FAH |  |  | Y1-Y5 | Z1 | (immediate | or |
|---|---|---|---|---|---|---|---|---|
| COMMAND | FTL | REQ | TO | RCV |  |  | POLLed) |  |

      The VMC is requesting to receive data from the bill validator whose destination
      address will always be (30H). Note that all FTL Commands / Responses are
      defined in Section 2.6.

| Y1 | = | Destination address of command | (30H) |
|---|---|---|---|
| Y2 | = | Source address of command |  |
| Y3 | = | File ID |  |
| Y4 | = | Maximum length |  |
| Y5 | = | Control |  |

| Z1 | = | 1DH which indicates | SEND BLOCK |
|---|---|---|---|
| Z2 | = | Destination address | of data |
| Z3 | = | Block # |  |
| Z4 | - Z34 | =    Data (maximum of 31 | bytes) |

                                 or
| Z1 | =          1CH which indicates RETRY / DENY |
|---|---|
| Z2 | =          Destination address of response |
| Z3 | =          Source address of response (30H) |
| Z4 | =          Retry delay |

      VMC Command Code Sub-command VMC Data Validator Response
| EXPANSION | 37H | FBH | Y1-Y3 | None |
|---|---|---|---|---|

## Command     Ftl Retry / Deny

      The VMC is retrying, denying, or aborting a data transfer to/from the bill validator
      whose destination address will always be (30H). Note that all FTL Commands /
      Responses are defined in Section 2.6.

| Y1 | =          Destination address of command | (30H) |
|---|---|---|
| Y2 | =          Source address of command |  |
| Y3 | =          Retry delay |  |

      VMC Command Code Sub-command VMC Data Validator Response
| EXPANSION | 37H | FCH | Y1-Y33 | None |
|---|---|---|---|---|

## Command     Ftl Send Block

      The VMC is sending data to the bill validator whose destination address will
      always be (30H). Note that all FTL Commands / Responses are defined in
      Section 2.6.

| Y1 | =       Destination | address | of | command | & data | (30H) |
|---|---|---|---|---|---|---|
| Y2 | =       Block # |  |  |  |  |  |

      Y3 - Y33 = Data (maximum of 31 bytes)

      VMC Command Code Sub-command VMC Data Validator Response
| EXPANSION | 37H | FDH |  | Y1-Y2 | Z1-Z34 | (immediate | or |
|---|---|---|---|---|---|---|---|
| COMMAND | FTL | OK TO | SEND |  |  | POLLed) |  |

      The VMC is indicating that it is OK for the bill validator to transfer data. The
      destination address will always be the validator (30H). Note that all FTL
      Commands / Responses are defined in Section 2.6.

| Y1 | =          Destination address of command | (30H) |
|---|---|---|
| Y2 | =          Source address of command |  |

| Z1 | = | 1DH which indicates SEND BLOCK |
|---|---|---|
| Z2 | = | Destination address of data |
| Z3 | = | Source address of data |
| Z4 | - Z34 | =    Data (maximum of 31 bytes) |

      VMC Command Code Sub-command VMC Data Validator Response
| EXPANSION | 37H | FEH |  |  | Y1-Y5 | Z1 | (immediate | or |
|---|---|---|---|---|---|---|---|---|
| COMMAND | FTL | REQ | TO | SEND |  |  | POLLed) |  |

      The VMC is requesting to send data to the bill validator whose destination address
      will always be (30H). Note that all FTL Commands / Responses are defined in
      Section 2.6.

| Y1 | = | Destination address of command | (30H) |
|---|---|---|---|
| Y2 | = | Source address of command |  |
| Y3 | = | File ID |  |
| Y4 | = | Maximum length |  |
| Y5 | = | Control |  |

| Z1 | =             1EH which indicates OK TO SEND |
|---|---|
| Z2 | =             Destination address of response |
| Z3 | =             Source address of response (30H) |

                                    or
| Z1 | = | 1CH which indicates RETRY / DENY |
|---|---|---|
| Z2 | = | Destination address of response |
| Z3 | = | Source address of response (30H) |
| Z4 | = | Retry delay |

| VMC Command | Code Sub-Command | VMC Data | Val Response |
|---|---|---|---|
| EXPANSION | 37H FFH | Y1-Yn | Z1 - Zn |

## Command                Diagnostics

| Y1 | - Yn | =        Device | manufacturer | specific | instruction | for | implementing | various |
|---|---|---|---|---|---|---|---|---|

                       manufacturing or test modes. Y1 - Yn implies that any number of
                       bytes can be used for the VMC data to the peripheral.

| Z1 | - Zn | =        Device | manufacturer | specific | responses | after | receiving |
|---|---|---|---|---|---|---|---|

                       manufacturing or test instructions. Z1 - Zn implies that any number
                       of bytes can be used for the bill validator response data from the
                       peripheral.

#### 6.4 Bill Validator / Recycler Non-Response Time

      The maximum non-response time for the bill validator is five seconds.

#### 6.5 Bill Validator / Recycler Power Requirements

      The current draw for any bill validator must fall within the following limits. All
      measurements are at the minimum VMC Voltage Output.

| Idle | mode | = | 200 | mA. | (avg.) | continuous |
|---|---|---|---|---|---|---|

| Bill | transport | = | 2.5 | A. | (max.) | up | to | 30 | seconds |
|---|---|---|---|---|---|---|---|---|---|

| Bill | dispense | = | 2.5 | A. | (max.) | up | to | 30 | seconds | per | bill |
|---|---|---|---|---|---|---|---|---|---|---|---|

Note: If both peripherals are supported, vending machines should be able to provide
sufficient power to simultaneously supply the above power requirements for both the bill
validator Bill Transport and coin mechanism Coin Acceptance as specified in Section
5.5.

#### 6.6 Bill Validator Examples

| Event | Exchange |
|---|---|
| Power up at VMC or JUST RESET received by VMC any | Reset sequence |
| other time without reset sequence | Enable sequence |
| Mode switch activated, enter service mode | Disable sequence |
| Mode switch activated, enter sales mode | Enable sequence |
| Consumer inserts bill | Accept sequence |
| Bill in escrow position is stacked | Stack sequence |
| Bill in escrow position is returned | Return sequence |
| Error situation is detected at validator | Error sequence |
| Error situation is detected at validator/stacker | Stack control sequence |
| Bill dispense | Bill Dispense request |
| Value dispense | Value Payout request |
| Bill dispense with bill in escrow | Bill Dispense w/ Bill in Escrow |
| Value dispense with bill in escrow | Value Payout w/ Bill in escrow |
| Cancel dispense | Value Payout Cancelled |
| Multiple dispense | Multiple Dispense (or Payout) |

                                                     Requests

Reset sequence
| VMC |  | Bill | Validator | Comments |
|---|---|---|---|---|
| RESET |  |  |  | Reset command |

##     Ack

| POLL |  |  |  | Allow peripheral to |
|---|---|---|---|---|
|  |  | JUST | RESET | confirm RESET command |

## Ack                        

| STATUS |  |  |  | Collect operational |
|---|---|---|---|---|
|  |  | VALIDATOR | CONFIG. | parameters |

## Ack                        

| SECURITY |  |  | Update bill security |
|---|---|---|---|
|  |  | ACK | Levels (Optional) |
| EXPANSION/ID |  |  | Collect asset info. |

##     Validator Id

## Ack                        

## Feature Enable             

##     Ack

| RECYCLER | SETUP |  | If | a recycler | is | available |
|---|---|---|---|---|---|---|

##     Bill Routing

## Ack                        

| RECYCLER | ENABLE |  | If | a recycler | is | available |
|---|---|---|---|---|---|---|

##     Ack

Enable sequence
| Controller |  | Bill | Validator | Comments |  |
|---|---|---|---|---|---|
| STACKER |  |  |  | Update stacker | count |

##     Bill Count

## Ack                        

| BILL | TYPE | ENABLE |  |  | Enable appropriate |
|---|---|---|---|---|---|
|  |  |  |  | ACK | bill types |

Disable sequence
| Controller |  | Bill | Validator | Comments |  |
|---|---|---|---|---|---|
| BILL TYPE ENABLE |  |  |  | Disable all | bill |
|  |  | ACK |  | types |  |

Error sequence
| Controller | Bill | Validator | Comments |
|---|---|---|---|

## Poll                       

|  |  | STATUS/ERROR | Error sent from |
|---|---|---|---|
| ACK |  |  | Bill validator |

| Accept sequence | Bill | stacked |  |
|---|---|---|---|
| Controller |  | Bill Validator | Comments |

## Poll                       

|  | BILL | ACCEPTED | Bill | type | and | routing |
|---|---|---|---|---|---|---|

## Ack                                                 (Escrow Position)

                           .
                           .
                           .
| ESCROW |  | Send | bill | to | stacker |
|---|---|---|---|---|---|

##     Ack

                           .
                           .
                           .

## Poll                       

|  | BILL | ACCEPTED | Bill | type | and | routing |
|---|---|---|---|---|---|---|

## Ack                                                 (Bill Stacked)

| Accept sequence | Bill | returned |  |
|---|---|---|---|
| Controller |  | Bill Validator | Comments |

## Poll                       

|  | BILL | ACCEPTED | Bill | type | and | routing |
|---|---|---|---|---|---|---|

## Ack                                                 (Escrow Position)

                           .
                           .
                           .

| ESCROW |  |  | Return bill | to |
|---|---|---|---|---|
|  |  | ACK | consumer |  |

                           .
                           .
                           .

## Poll                       

|  | BILL | ACCEPTED | Bill | type | and | routing |
|---|---|---|---|---|---|---|

## Ack                                                 (Bill Returned)

| Check | stacker | after | Bill | stacked |
|---|---|---|---|---|

Accept sequence
| Controller | Bill | Validator | Comments |
|---|---|---|---|

## Poll                       

|  | BILL | ACCEPTED | Bill | type | and | routing |
|---|---|---|---|---|---|---|

## Ack                                                 (Bill Stacked)

                           .
                           .
                           .
| STACKER |  | Update | stacker | count |
|---|---|---|---|---|

##     Bill Count

## Ack                        

| BILL | TYPE | ENABLE |  | Disable | all | bill | types, | if | stacker |
|---|---|---|---|---|---|---|---|---|---|

                                                     is full

##     Ack

Dispense Sequence
| Controller | Bill | Validator | Comments |
|---|---|---|---|

## Poll                        

|  | BILL | WAITING | Inlet | blocked, | pending |
|---|---|---|---|---|---|

                                                       customer

## Ack                         

## Poll                        

|  |  |  | ACK | Inlet unblocked |
|---|---|---|---|---|
| DISPENSE | BILL |  |  | Dispense # of bills |

##      Ack

## Payout Value Poll           

##      Value Paid

## Ack                         

| POLL |  |  | Inlet blocked, bill transferred |
|---|---|---|---|
|  |  | ACK | from the recycler to the |

                                                       cashbox, or error code
                            •
                            - Repeat last 2 commands
                            •

## Payout Value Poll           

|  | ACK | Payout | Complete |
|---|---|---|---|

## Payout Status               

|  | BILLS | PAID | Count | of | each | bill | type |
|---|---|---|---|---|---|---|---|

## Ack                         

## Bill Dispense Status        

|  | DISPENSER | STATUS | Update | Bill | counts |
|---|---|---|---|---|---|

## Ack                         

Value Payout
| Controller | Bill | Validator | Comments |
|---|---|---|---|

## Poll                        

|  | BILL | WAITING | Inlet | blocked, | pending |
|---|---|---|---|---|---|

                                                     customer

## Ack                         

## Poll                        

|  |  |  | ACK | Inlet unblocked |
|---|---|---|---|---|
| DISPENSE | VALUE |  |  | Dispense Value |

##      Ack

## Payout Value Poll           

##      Value Paid

## Ack                         

| POLL |  |  | Inlet blocked, bill transferred |
|---|---|---|---|
|  |  | ACK | from the recycler to the |

                                                     cashbox, or error code
                            •
                            - Repeat last 2 commands
                            •

## Payout Value Poll           

|  | ACK | Payout | Complete |
|---|---|---|---|

## Payout Status               

|  | BILLS | PAID | Count | of | each | bill | type |
|---|---|---|---|---|---|---|---|

## Ack                         

## Bill Dispense Status        

|  | DISPENSER | STATUS | Update | Bill | counts |
|---|---|---|---|---|---|

## Ack                         

Dispense Sequence w/ bill in escrow
| Controller | Bill | Validator | Comments |
|---|---|---|---|

## Poll                        

##      Bill In Escrow

## Ack                         

                            •
                            •
                            •
| ESCROW |  |  | Return bill | to |
|---|---|---|---|---|
|  |  | ACK | consumer |  |

                            •
                            •
                            •

## Poll                        

|  | BILL | ACCEPTED | Bill | type | and | routing |
|---|---|---|---|---|---|---|

## Ack                                                 (Bill Returned)

## Poll                        

|  | BILL | WAITING | Inlet | blocked, | pending |
|---|---|---|---|---|---|

                                                     customer

## Ack                         

## Poll                        

|  |  |  | ACK | Inlet unblocked |
|---|---|---|---|---|
| DISPENSE | BILL |  |  | Dispense # of bills |

##      Ack

## Payout Value Poll           

##      Value Paid

## Ack                         

| POLL |  |  | Inlet blocked, bill transferred |
|---|---|---|---|
|  |  | ACK | from the recycler to the |

                                                     cashbox, or error code
                            •
                            - Repeat last 2 commands
                            •

## Payout Value Poll           

|  | ACK | Payout | Complete |
|---|---|---|---|

## Payout Status               

|  | BILLS | PAID | Count | of | each | bill | type |
|---|---|---|---|---|---|---|---|

## Ack                         

## Bill Dispense Status        

|  | DISPENSER | STATUS | Update | Bill | counts |
|---|---|---|---|---|---|

## Ack                         

Value payout w/ bill in escrow
| Controller | Bill | Validator | Comments |
|---|---|---|---|

## Poll                        

##      Bill In Escrow

## Ack                         

                            •
                            •
                            •
| ESCROW |  |  | Return bill | to |
|---|---|---|---|---|
|  |  | ACK | consumer |  |

                            •
                            •
                            •

## Poll                        

|  | BILL | ACCEPTED | Bill | type | and | routing |
|---|---|---|---|---|---|---|

## Ack                                                 (Bill Returned)

## Poll                        

|  | BILL | WAITING | Inlet | blocked, | pending |
|---|---|---|---|---|---|

                                                     customer

## Ack                         

## Poll                        

|  |  |  | ACK | Inlet unblocked |
|---|---|---|---|---|
| DISPENSE | VALUE |  |  | Dispense value |

##      Ack

## Payout Value Poll           

##      Value Paid

## Ack                         

| POLL |  |  | Inlet blocked, bill transferred |
|---|---|---|---|
|  |  | ACK | from the recycler to the |

                                                     cashbox, or error code
                            •
                            - Repeat last 2 commands
                            •

## Payout Value Poll           

|  | ACK | Payout | Complete |
|---|---|---|---|

## Payout Status               

|  | BILLS | PAID | Count | of | each | bill | type |
|---|---|---|---|---|---|---|---|

## Ack                         

## Bill Dispense Status        

|  | DISPENSER | STATUS | Update | Bill | counts |
|---|---|---|---|---|---|

## Ack                         

Operation Cancelled
| Controller | Bill | Validator | Comments |
|---|---|---|---|

                            - Payout or dispense in progress
                            •
                            •
| PAYOUT | CANCEL |  |  | Request to | abort |
|---|---|---|---|---|---|
|  |  |  | ACK | consumer |  |

## Payout Value Poll           

##      Value Paid

## Ack                         

| POLL |  |  | Inlet blocked, bill transferred |
|---|---|---|---|
|  |  | ACK | from the recycler to the |

                                                     cashbox, or error code
                            •
                            - Repeat last 2 commands
                            •

## Poll                        

|  | ACK | Inlet | unblocked |
|---|---|---|---|

## Payout Status               

|  | BILLS | PAID | Count | of | each | bill | type |
|---|---|---|---|---|---|---|---|

## Ack                         

## Bill Dispense Status        

|  | DISPENSER | STATUS | Update | Bill | counts |
|---|---|---|---|---|---|

## Ack                         

Multiple Operations

| Controller | Bill | Validator | Comments |
|---|---|---|---|

## Poll                        

|  | BILL | WAITING | Inlet | blocked, | pending |
|---|---|---|---|---|---|

                                                     customer

## Ack                         

## Poll                        

|  |  |  | ACK | Inlet unblocked |
|---|---|---|---|---|
| DISPENSE | BILL |  |  | Dispense # of bills |

##      Ack

                            •
                            •
                            •

## Payout Value Poll           

##      Value Paid

## Ack                         

| POLL |  |  | Inlet blocked, bill transferred |
|---|---|---|---|
|  |  | ACK | from the recycler to the |

                                                     cashbox, or error code
                            •
                            •
                            •

## Payout Value Poll           

|  | ACK | Payout | Complete |
|---|---|---|---|

## Payout Status               

|  | BILLS | PAID | Count | of | each | bill | type |
|---|---|---|---|---|---|---|---|

## Ack                         

## Bill Dispense Status        

|  | DISPENSER | STATUS | Update | Bill | counts |
|---|---|---|---|---|---|

## Ack                         

## Poll                        

|  | BILL | WAITING | Inlet | blocked, | pending |
|---|---|---|---|---|---|

                                                     customer

## Ack                         

## Poll                        

|  |  |  | ACK | Inlet unblocked |
|---|---|---|---|---|
| DISPENSE | BILL |  |  | Dispense # of bills |

##      Ack

                            •
                            •
                            •

## Payout Value Poll           

##      Value Paid

## Ack                         

| POLL |  |  | Inlet blocked, bill transferred |
|---|---|---|---|
|  |  | ACK | from the recycler to the |

                                                     cashbox, or error code
                            •
                            - Repeat last 2 commands
                            •

## Payout Value Poll           

|  | ACK | Payout | Complete |
|---|---|---|---|

## Payout Status               

|  | BILLS | PAID | Count | of | each | bill | type |
|---|---|---|---|---|---|---|---|

## Ack                         

## Bill Dispense Status        

|  | DISPENSER | STATUS | Update | Bill | counts |
|---|---|---|---|---|---|

## Ack                         

## Poll                        

|  | BILL | WAITING | Inlet | blocked, | pending |
|---|---|---|---|---|---|

                                                     customer

## Ack                         

## Poll                        

|  | ACK | Inlet | unblocked |
|---|---|---|---|

Section 7
   Cashless Device(s)
   VMC/Peripheral Communication Specifications

#### 7.1 Introduction

This section defines the communications bytes sent and received between the cashless
device(s) and the Vending Machine Controller (VMC). As defined in Section 2.3, there are two
cashless device addresses; Cashless #1, 00010xxxB (10H) and Cashless #2, 11000xxxB
(60H). The second address has been assigned to allow for two unique forms of cashless
devices to be resident in the vending machine simultaneously. An example would be a card
based system as Cashless Device #1 (10H) and a mobile phone based system as Cashless
Device #2 (60H). Everything defined in this section will be common to the two cashless
devices – only the addresses will be different.

Unless otherwise stated, all monetary values used by the cashless devices and the VMC will
be sixteen bit (Level 01 & 02) or thirty-two bit (Level 03 if 32 bit option enabled), unsigned
binary numbers. The numbers will be sent most significant byte first and scaled using the
parameters provided by the cashless device’s READER CONFIGURATION DATA response.

#### 7.2 State Definitions

MDB cashless devices may be viewed as state machines. These states are as follows:

             1) Inactive
             2) Disabled
             3) Enabled
             4) Session Idle
             5) Vend
             6) Revalue (Level 02/03 cashless devices)
             7) Negative Vend (Level 03 cashless devices)

#### 7.2.1 Inactive

This is the state of the cashless device at power up or after a reset. While in the Inactive state,
cashless devices will NOT be accepted for vending purposes. The cashless device cannot
leave this state until all Setup information is received from the VMC.

#### 7.2.2 Disabled

The cashless device automatically enters this state from the Inactive state when it has
received the Setup information specified in 7.4.1. It will also enter the Disabled state from the
Enabled state when it receives the READER DISABLE command. While in the Disabled state,
payment medias will NOT be accepted for vending purposes. The cashless device will remain
in this state until either a READER ENABLE command is received (when it will enter the
Enabled state) or a RESET is received (when it will enter the Inactive state). For power

management purposes, current consumption will not exceed idle mode specification during
disabled state.

#### 7.2.3 Enabled

In this state, cashless devices may be used for MDB transactions. The cashless device will
remain in this state until a valid payment media is read (when it will enter the Session Idle
state), a READER DISABLE command is received (when it will return to the Disabled state) or
a RESET is received (when it will enter the Inactive state).

When the device is enabled to operate in an “always idle” state, a request vend will directly
enter the vend session, as well as a negative request vend will directly enter the negative vend
request session. During enabled “always idle” state, the cashless device may although
perform normal sessions starting with a BEGIN SESSION command – the VMC needs to
accept both and should after detecting a BEGIN SESSION response act the whole session
like “always idle” state disabled” temporarily.

#### 7.2.4 Session Idle

In the Enabled state, when a valid payment media is processed, the cashless device will issue
a BEGIN SESSION response to a VMC POLL and enter the Session Idle state. This indicates
that the cashless device is available for vending activities. The only structured exit from the
Session Idle state is through the SESSION COMPLETE message from the VMC. The
SESSION COMPLETE command will cause the cashless device to respond with an END
SESSION message and enable/disable itself appropriately. Vend / Negative Vend / Revalue
commands will cause the cashless device to leave the Session Idle state and enter the Vend /
Negative Vend / Revalue state when products are selected and purchased.

#### 7.2.5 Always Idle

When the device is able to operate in an “Always Idle” state (enabled with the Optional
Feature Bits of the EXPANSION Enable Options command), a VEND REQUEST from the
Enabled state will directly enter the Vend state. Additionally, when the device is able to
operate in an “Always Idle” state, a NEGATIVE VEND REQEQUEST will directly enter the
Negative Vend Request state.

#### 7.2.5 Vend

This state is entered from the Session Idle state upon reception of a VEND REQUEST
message from the VMC. The entire Vend state is an uninterruptable command/response
sequence. The cashless device will return to the Session Idle state upon completion of this
sequence.

#### 7.2.6 Revalue       (Level 02 / 03 Cashless Devices)

This state is entered from the Session Idle state upon reception of a REVALUE REQUEST
message from the VMC. The entire Revalue state is an uninterruptable command/response
sequence. The cashless device will return to the Session Idle state upon completion of this
sequence.

#### 7.2.7 Negative Vend Request (Level 03 Cashless Devices)

This state is entered from the Session Idle state upon reception of a NEGATIVE VEND
REQUEST message from the VMC. The entire Negative Vend Request state is an
uninterruptable command/response sequence. The cashless device will return to the Session
Idle state upon completion of this sequence.

#### 7.3 Command Protocol

After the VMC has issued a command, no new commands may be issued until all data
generated in response to that command has been received from the cashless device. The
complete response may be an ACK only (e.g. the READER ENABLE command). Alternatively,
it may consist of an informational response (e.g. READER CONFIGURATION DATA).
The cashless device may provide an informational response in two ways. It may respond
immediately with the requested data, or the cashless device may ACK the VMC command. If
ACKed, the VMC must issue POLLs until the cashless device responds with the requested
data, or until the Application Maximum Response Time (defined in READER
CONFIGURATION response) has elapsed.

The cashless device will define the currency type at the beginning of each session. The
currency type will be used for all following transactions in that session. If the VMC
does not support this currency type, it will end the session.

Below are the uninterruptable VMC commands which require an informational cashless device
response and their associated result:
| VMC Command |  |  | Cashless Device Response | Result |
|---|---|---|---|---|
| SETUP/CONFIGURATlON | DATA | => | READER CONFIGURATION |  |

                                      DATA

## Expansion/Request Id =>               Peripheral Id

## Reader Cancel =>                      Cancelled

## Vend Request... Vend Cancel => Vend Denied*

## Vend Request =>                       Vend Denied*

| VEND | REQUEST | => | VEND | APPROVED | => | VEND | SUCCESS* |
|---|---|---|---|---|---|---|---|
| VEND | REQUEST | => | VEND | APPROVED | => | VEND | FAILURE* |

## Negative Vend Request =>              Negative Vend Denied*

| NEGATIVE | VEND | REQUEST | => | NEGATIVE | VEND | NEGATIVE | VEND |
|---|---|---|---|---|---|---|---|

## Approved =>                  Success*

| NEGATIVE | VEND | REQUEST | => | NEGATIVE | VEND | NEGATIVE | VEND |
|---|---|---|---|---|---|---|---|

## Approved =>                  Failure*

## Revalue Request=>                     Revalue

## Approved/Denied*

## Session Complete =>                   End Session

*These VEND / NEGATIVE VEND / REVALUE REQUEST response sequences constitute the
Vend / Negative Vend / Revalue Request states.

Below are the uninterruptable POLLed cashless device which require an informational
response from the VMC:

| VMC | Command | & Data | Cashless | Device | Response | Result |
|---|---|---|---|---|---|---|

## Poll =>                                    Data Entry Request +

                                           DISPLAY REQUEST (optional)
| POLL | => |  |  |  |  | DATA | ENTRY | CANCEL | Cancelled |
|---|---|---|---|---|---|---|---|---|---|
| DATA | ENTRY | RESPONSE | w/ | FFs | => |  |  |  | Cancelled |

Any command may be issued by the VMC at anytime providing the above command protocol
is observed. There are four exceptions to this rule:

      1) VEND REQUEST, REVALUE REQUEST, and NEGATIVE VEND REQUEST
         response sequences may only be initiated in the Session Idle state. In other words,
         the Cashless Device does not allow an “Always Idle” state unless enabled from
         setting the corresponding enable bit in the enable options command. If this option is
         enabled, the VEND REQUEST, the NEGATIVE VEND REQUEST, and the
         REVALUE REQUEST are allowed also during Enabled state.
      2) The VMC may issue a VEND CANCEL command after issuing a VEND REQUEST,
         but before receiving a VEND APPROVED/DENIED response. In this case the
         cashless device will issue a VEND DENIED response to satisfy the original VEND
         REQUEST response requirement.
      3) The cashless device may issue DISPLAY REQUESTs in response to POLLs at any
         time, if the VMC’s display is available for use.
      4) The RESET command is allowed at any time, it is not subject to any restrictions.

If a VMC command is received by the cashless device while it is in one of the preceding
uninterruptable states, the following will occur:

         The cashless device will ACK the offending command (no data response will be
         forthcoming). The cashless device will respond to the next poll with the “COMMAND
         OUT OF SEQUENCE” response (0BH).

It should be pointed out to cashless device developers that a command out of sequence
will always cause the VMC to issue a RESET command to the cashless device.

#### 7.3.1 Multi-Message Response Format

The multi-message response format permits the cashless device to send multiple messages in
response to a single command or POLL. Because all messages are of a fixed length, there is
no confusion determining where one message ends and the next message begins. (The total
message length is subject to the 36 byte limit imposed by Section 2 of this standard.)

For example, if a cashless device fails to correctly write a payment media after a VEND
REQUEST, it may need to report:

## 1) Vend Denied

2) MALFUNCTION/ERROR subcode `07h`

## 3) Session Cancel Request

The multi-message response (hex) would look like this:

## 06 0A 07 04 1B*

| 1 | 2      3 |
|---|---|

The first byte above (marked 1) is the VEND DENIED message. The next two bytes (marked
2) are the MALFUNCTION/ERROR message. The third and final message is the CANCEL
SESSION REQUEST (marked 3). An eight bit checksum with the mode bit set (marked 4)
finishes the message.

It is important to note that the controller must service the messages in the order in which they
are received. This is necessary to ensure that command protocol is maintained.

#### 7.3.2 Coin Mechanism Escrow Return Actions

If present, the cashless device return button is controlled by the cashless device and it is the
responsibility of the cashless device to terminate a vend sequence if the return button is
pressed during a vend sequence.

The reaction of the VMC to the coin mechanism escrow return will vary depending upon the
state of the system at the time it is pressed. If escrow return is allowed then a coin
mechanism escrow return should be interpreted as VEND CANCEL or END OF SESSION.

       1) In the Enabled state, the VMC should send a READER CANCEL command to the
          cashless device. This allows the user to abort a pre-approved on-line authorisation
          request.

       2) In the Session Idle state, the VMC should send a SESSION COMPLETE command
          to the cashless device. This will return the cashless device to the Enabled state. The
          escrow return may cause the system to enter the revalue state prior to the VMC
          sending the “SESSION COMPLETE” command.

       3) In the Vend state, before the cashless device has sent a VEND APPROVED or a
          VEND DENIED, the VMC should send a VEND CANCEL command to the cashless
          device. This will cancel the vend and cause the cashless device to refund the
          payment media if necessary.

       4) In all other cases, no message is sent from the VMC to the cashless device.

## Table 1: Commands & Responses

| Command | Code Sub-command | /                   Response | VMC / Cashless |
|---|---|---|---|
|  | Data |  | Level Support |
| Reset | 10H (none) | No Data * | (Level 01+) |

        60H
| Setup | 11H | 00H - Config Data | 01H - Reader | (Level | 01+) |
|---|---|---|---|---|---|
|  | 61H |  | Config Data |  |  |
|  |  | 01H - Max/Min Prices | No Data * | (Level | 01+) |
| Poll | 12H | (none) | 00H - Just Reset | (Level | 01+) |
|  | 62H |  | 01H - Reader Config Data | (Level | 01+) |
|  |  |  | 02H - Display Request | (Level | 01+) |
|  |  |  | 03H - Begin Session | (Level | 01+) |
|  |  |  | 04H - Session Cancel | (Level | 01+) |

                                                   Request
| 05H | - Vend Approved |  | (Level | 01+) |
|---|---|---|---|---|
| 06H | - Vend Denied |  | (Level | 01+) |
| 07H | - End Session |  | (Level | 01+) |
| 08H | - Cancelled |  | (Level | 01+) |
| 09H | - Peripheral ID |  | (Level | 01+) |
| 0AH | - Malfunction / | Error | (Level | 01+) |
| 0BH | - Cmd Out Of |  | (Level | 01+) |

                                                   Sequence
| 0DH | - Revalue | (Level | 02+) | (option) |
|---|---|---|---|---|

                                                   Approved
| 0EH | - Revalue | Denied | (Level | 02+) | (option) |
|---|---|---|---|---|---|
| 0FH | - Revalue | Limit | (Level | 02+) | (option) |

                                                   Amount
| 10H | - User File | Data | (Level | 02) ** |
|---|---|---|---|---|
| 11H | - Time/Date |  | (Level | 02+) (option) |

                                                   Request
| 12H | - Data | Entry | (Level | 03+) | (option) |
|---|---|---|---|---|---|

                                                   Request
| 13H | - Data Entry Cancel | (Level 03+) | (option) |
|---|---|---|---|
| 14H | -1AH | (For Future | Use) |
| 1BH | - FTL REQ TO RCV | (Level 03+) | (option) |
| 1CH | - FTL RETRY / | (Level 03+) | (option) |

                                                         DENY
| 1DH | - FTL | SEND | (Level | 03+) | (option) |
|---|---|---|---|---|---|

## Block

| 1EH | - FTL | OK TO SEND | (Level | 03+) | (option) |
|---|---|---|---|---|---|
| 1FH | - FTL | REQ TO | (Level | 03+) | (option) |

                                                       SEND
| 20H | - FEH | (For Future | Use) |
|---|---|---|---|
| FFH | - Diagnostic | (Level 01+) |  |

                                             Response
| Vend | 13H | 00H | - Vend | Request | 05H | - Vend | Approved | (Level | 01+) |
|---|---|---|---|---|---|---|---|---|---|
|  | 63H |  |  |  | 06H | - Vend | Denied | (Level | 01+) |

| 01H | - Vend Cancel | 06H - Vend Denied | (Level | 01+) |
|---|---|---|---|---|
| 02H | - Vend Success | No Data * | (Level | 01+) |
| 03H | - Vend Failure | No Data * | (Level | 01+) |
| 04H | - Session | 07H - End Session | (Level | 01+) |

                            Complete
|  |  | 05H | - Cash Sale | No Data * | (Level | 01+) |  |
|---|---|---|---|---|---|---|---|
|  |  | 06H | - Negative Vend | 05H – Vend Approved | (Level | 03+) | option) |
|  |  |  | Request | 06H – Vend Denied | (Level | 03+) | (option) |
| Reader | 14H | 00H | - Reader Disable | No Data * | (Level | 01+) |  |
|  | 64H | 01H | - Reader Enable | No Data * | (Level | 01+) |  |
|  |  | 02H | - Reader Cancel | 08H - Cancelled | (Level | 01+) |  |
|  |  | 03H | - Data Entry | No Data * | (Level | 03+) | (option) |

                            Response
| Revalue | 15H | 00H | - Revalue | 0DH - Revalue Approved | (Level | 02+)   (option) |
|---|---|---|---|---|---|---|
| (option) | 65H |  | Request | 0EH - Revalue Denied | (Level | 02+)   (option) |
|  |  | 01H | - Revalue Limit | 0FH - Revalue Limit | (Level | 02+)   (option) |
|  |  |  | Request | Amount |  |  |
|  |  |  |  | 0EH - Revalue Denied | (Level | 02+) (option) |
| Expansion | 17H | 00H | - Request ID | 09H - Peripheral ID | (Level | 01+) |
|  | 67H | 01H | - Read User File 10H | - User File Data | (Level | 02) ** |
|  |  | 02H | - Write User File No | Data * | (Level | 02) ** |
|  |  | 03H | - Write     (option) | No Data * | (Level | 02+) (option) |

                            Time/Date
| 04H | - Optional | No | Data | (Level | 03+) |
|---|---|---|---|---|---|

                            Feature
                            Enabled
| FAH | - FTL |  | (option) | 1DH - SEND BLOCK | (Level | 03+) | (option) |
|---|---|---|---|---|---|---|---|
|  | REQ | TO | RCV | 1CH - RETRY / DENY | (Level | 03+) | (option) |
| FBH | - FTL |  | (option) | No Data | (Level | 03+) | (option) |

## Retry / Deny

| FCH | - FTL | (option) | No | Data | (Level | 03+) | (option) |
|---|---|---|---|---|---|---|---|

## Send Block

| FDH | - FTL | (option) | 1DH | - SEND | BLOCK | (Level | 03+) | (option) |
|---|---|---|---|---|---|---|---|---|

## Ok To Send

| FEH | - FTL      (option) | 1EH - OK TO SEND | (Level | 03+) | (option) |
|---|---|---|---|---|---|
|  | REQ TO SEND | 1CH - RETRY/DENY | (Level | 03+) | (option) |
| FFH | - Diagnostics | FFH - Diagnostic | (Level | 01+) |  |

                                                     Response

- No Data response = peripheral just responds with ACK or NAK
** Obsolete Command – Do not use for new designs. Use EXPANSION - Diagnostics.
The term (option) indicates that the command/response is a feature enabled by option bits.

NOTE: Cashless device responses which are part of request / response sequences are listed
more than once in the above table since the cashless device may respond either immediately
to the request (within 5 milliseconds) or to a later POLL.

#### 7.4 VMC/ Cashless Device Command/Response Formats

In the following section, the term “Reader” will indicate either Cashless Device #1 or #2.

#### 7.4.1 Reset and Initialising

## Reset

## (10H / 60H)

Reader response:

 No Data response

If this command is received by a cashless device it should terminate any ongoing transaction
(with an appropriate credit adjustment, if appropriate), eject the payment media (if applicable),
and go to the Inactive state.
All Level 02 and above VMCs must follow the RESET command with the following cashless
device initializing sequence: (Any new Level 01 VMCs are recommended to follow the
sequence.)
Note that the example shows commands for Cashless Device #1 (10H) only. They would be
the same for Cashless Device #2 (address 60H).

POLL – `12h`
     To obtain “JUST RESET” response
SETUP CONFIGURATION DATA – 11 `00h`
    To send the VMC’s configuration data and obtain the cashless device’s data
SETUP MAX/MIN PRICE – 11 `01h`
    To send the maximum and minimum prices in the VMC. These prices must be
    sent as Level 01/02 16 bit credit.
EXPANSION REQUEST ID – 17 `00h`
    To obtain additional cashless device information and options (options in Level 03+ only)
EXPANSION ENABLE OPTIONS – 17 `04h` (Level 03+ only)
    To enable desired options
SETUP MAX/MIN PRICE – 11 `01h` (Level 03+ and option bits 1 & 2 only)
    If 32 bit currency option and/or multi currency – multi lingual is enabled (i.e. bits 1 & 2 of
    expansion enable options), perform SETUP MAX/MIN PRICE again to get 32 bit credit
    and/or user currency – user language (this conditions will be known as EXPANDED
    CURRENCY MODE in the rest of the document).
READER ENABLE – 14 `01h`
    To enable cashless device (if desired)

#### 7.4.2 SETUP - Config Data

|  |  | Config | VMC | Columns | Rows | Display |
|---|---|---|---|---|---|---|
| SETUP |  | Data | Feature | on | On | Info |
| (11H / | 61H) | (00H) | Level | Display | Display |  |

## Y1            Y2            Y3              Y4           Y5

| Y1 | :     Configuration | data. |
|---|---|---|

                VMC is sending its configuration data to reader.
| Y2 | :     VMC | Feature | Level. |
|---|---|---|---|

                Indicates the feature level of the VMC. The available feature levels are:
                  01 - The VMC is not capable or will not perform the advanced features
                       as specified in Table 1: COMMANDS & RESPONSES following
                       Section 7.3.2. The reader will not provide advanced information to
                       the VMC, but can do the advanced features internally (transparently
                       to the VMC). The reader has no revaluation capability.
                  02 - The VMC is capable and willing to perform the advanced features as
                       specified in Table 1: COMMANDS & RESPONSES following
                       Section 7.3.2. The reader will provide advanced information to the
                       VMC (if possible) and will not do the advanced features internally.
                  03 - The VMC is able to support level 02, but also supports some or all of
                       the optional features listed in the EXPANSION ID command (i.e., file
                       transfer, 32 bit credit, multi-currency / language features, negative
                       vend, and / or data entry).
| Y3 | :     Columns | on | Display. | The | number | of | columns | on | the | display. | Set | to | 00H | if |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                the display is not available to the reader.
| Y4 | :     Rows | on | Display. |
|---|---|---|---|

                The number of rows on the display
| Y5 | :     Display | Information | – xxxxxyyy |
|---|---|---|---|

                xxxxx = Unused
| yyy | =      Display type |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|
| 000 | :      Numbers, upper | case | letters, | blank | and | decimal | point. |
| 001 | :      Full ASCII |  |  |  |  |  |  |

                010-111: Unassigned

Reader Response:

| Reader | Reader | Country | Country | Scale | Decimal | Application | Miscellaneous |
|---|---|---|---|---|---|---|---|
| Config | Feature | Code | Code | Factor | Places | Maximum | Options |
| Data | Level | High | Low |  |  | Response |  |
| (01H) |  |  |  |  |  | Time |  |

## Z1       Z2         Z3         Z4        Z5          Z6        Z7            Z8

| Z1 | :     READER | - Configuration | data. |
|---|---|---|---|

                Indicates the payment media reader is responding to a SETUP –
                Configuration data request from the VMC.

| Z2 | :     Reader | Feature | Level. |
|---|---|---|---|

               Indicates the feature level of the reader. Currently feature levels are:
                 01 - The reader is not capable or will not perform the advanced features
                      as specified in Table 1: COMMANDS & RESPONSES following
                      Section 7.3.2. The reader will not provide advanced information to
                      the VMC, but can do the advanced features internally (transparently
                      to the VMC). The reader has no revaluation capability.
                 02 - The reader is capable and willing to perform the advanced features
                      as specified in Table 1: COMMANDS & RESPONSES following
                      Section 7.3.2. The reader will provide advanced information to the
                      VMC (if possible) and will not do the advanced features internally.
                 03 - The reader is able to support level 02, but also supports some or all
                      of the optional features listed in the EXPANSION ID command (i.e.,
                      file transfer, 32 bit credit, multi-currency / language features,
                      negative vend, and / or data entry).
      Z3-Z4 : Country / Currency Code - packed BCD.
              The packed BCD country / currency code of the reader can be sent in two
              different forms depending on the value of the left most BCD digit.
               If the left most digit is a 0, the International Telephone Code is used to
               indicate the country that the reader is set-up for. For example, the USA
               code is 00 01H (Z3 = 00 and Z4 = 01).
               If the left most digit is a 1, the latest version of the ISO 4217 numeric
               currency code is used (see Appendix A1). For example, the code for the
               US dollar is 18 40H (Z2 = 18 and Z3 = 40) and for the Euro is 1978 (Z3 =
               19 and Z4 = 78). Use FFFFh if the country code in unknown.
               For level 3 cashless devices, it is mandatory to use the ISO 4217 numeric
               currency code (see Appendix A1).

| Z5 | :     Scale | Factor. |
|---|---|---|

               The multiplier used to scale all monetary values transferred between the
               VMC and the reader.
| Z6 | :     Decimal | Places. |
|---|---|---|

               The number of decimal places used to communicate monetary values
               between the VMC and the payment media reader.

               All pricing information sent between the VMC and the payment media
               reader is scaled using the scale factor and decimal places. This
               corresponds to:
                                          ActualPrice = P ⋅ X ⋅ 10 − Y
               where P is the scaled value send in the price bytes, and X is the scale
               factor, and Y is the number of decimal places. For example if there are 2
               decimal places and the scale factor is 5, then a scaled price of 7 will
               mean an actual of 0.35.

| Z7 | :       Application | Maximum | Response | Time | - seconds. |
|---|---|---|---|---|---|

                  The maximum length of time a reader will require to provide a response
                  to any command from the VMC. The value reported here supercedes the
                  payment reader’s default NON-RESPONSE time defined in section 7.5 if
                  the value reported here is greater. (See Section 7.5)
| Z8 | :       Miscellaneous Options – xxxxyyyy |  |  |  |  |  |
|---|---|---|---|---|---|---|
|  | xxxx:     Unused (must be set to 0) |  |  |  |  |  |
|  | yyyy:     Option bits |  |  |  |  |  |
|  | b0=0:     The payment media reader is | NOT | capable | of | restoring | funds |

                            to the user’s payment media or account. Do not request
                            refunds.
| b0=1: | The | payment | media | reader | is | capable | of | restoring | funds | to | the |
|---|---|---|---|---|---|---|---|---|---|---|---|

                            user’s payment media or account. Refunds may be requested.
| b1=0: | The | payment | media | reader | is | NOT | multivend | capable. |
|---|---|---|---|---|---|---|---|---|

                            Terminate session after each vend.
| b1=1: | The | payment | media | reader | is | multivend | capable. | Multiple |
|---|---|---|---|---|---|---|---|---|

                            items may be purchased within a single session.
| b2=0: | The | payment | media | reader | does | NOT have a display. |
|---|---|---|---|---|---|---|
| b2=1: | The | payment | media | reader | does | have its own display. |
| b3=0: | The | payment | media | reader | does | NOT support the |

                            VEND/CASH SALE subcommand.
| b3=1: | The | payment | media | reader | does | support | the | VEND/CASH |
|---|---|---|---|---|---|---|---|---|

                            SALE subcommand.
| b4-b7=0 | Any | future | options | must | be | covered | by | the | EXPANSION |
|---|---|---|---|---|---|---|---|---|---|

                            COMMAND option bits.

#### 7.4.3 SETUP – Max / Min Prices

              Max / Min Maximum Minimum
| SETUP | Prices | Price | Price |
|---|---|---|---|

## (11H / 61H)   (01H)

## Y1        Y2-Y3   Y4-Y5

Level 01 / 02 / 03 Readers

| Y1 | :        Max | / Min | prices |
|---|---|---|---|

                   Indicates the VMC is sending the price range to the reader.
       Y2 - Y3 : Maximum Price – scaled
                 This information should be sent as soon as the VMC prices have been
                 established and any time there is a change in the maximum price, If the
                 VMC does not know the maximum price, FFFFh should be sent.
| Y4 | -Y5 | :    Minimum | Price | – scaled |
|---|---|---|---|---|

                   This information should be sent as soon as the VMC prices have been
                   established and any time there is a change in the minimum price. If the
                   VMC does not know the minimum price, 0000h should be sent.

|  | Max / | Maximum | Minimum | Currency |
|---|---|---|---|---|
| SETUP | MinPrices | Price | Price | Code |

## (11H / 61H) (01H)     Y2-Y5   Y6-Y9     Y10-Y11

            Y1
Level 03 (EXPANDED CURRENCY MODE) Readers

| Y1 | :       Max | / Min | prices |
|---|---|---|---|

                  Indicates the VMC is sending the price range to the reader.
       Y2 – Y5 : Maximum Price – scaled
                 This information should be sent as soon as the VMC prices have been
                 established and any time there is a change in the maximum price, If the
                 VMC does not know the maximum price, FFFFFFFFh should be sent.
       Y6 –Y9 : Minimum Price – scaled
                This information should be sent as soon as the VMC prices have been
                established and any time there is a change in the minimum price. If the
                VMC does not know the minimum price, 00000000h should be sent.
       Y10-Y11 Currency Code
               The currency code used during this command per ISO 4217 (see
               Appendix A1). The value is configured as packed BCD with the leading
               digit a 1 (one). For example, the code for the US dollar would be 1840
               (Z10 = 18 and Z11 = 40). and for the Euro is 1978 (Z10 = 19 and Z11 =
               78).

Reader response:

 No Data response

#### 7.4.4 POLL

   POLL

## (12H / 62H)

The POLL command is used by the VMC to obtain information from the payment media
reader. This information may include user actions (CANCEL SESSION REQUEST), hardware
malfunctions (MALFUNCTION /ERROR), software malfunctions (COMMAND OUT OF
SEQUENCE) or information explicitly requested by the controller (READER
CONFIGURATION DATA). An ACK response indicates that no error states exist, and either
no information request is pending or pending information is not yet ready for transmission.

In addition to an ACK, the VMC may receive the following POLL responses from the payment
media reader.

Reader responses:

Just
Reset

## (00H)

Z1

## Z1 :         Just Reset

                     Indicates the payment media reader has been reset.
                     Note: the difference between ACK and JUST RESET responses is:

## 00H 00H*    =Just Reset

## 00H*        =Ack

                                                         *mode bit=1

| Reader | Reader | Country | Country | Scale | Decimal | Application | Miscellaneous |
|---|---|---|---|---|---|---|---|
| Config | Feature | Code | Code | Factor | Places | Maximum | Options |
| Info | Level | High | Low |  |  | Response |  |
| (01H) |  |  |  |  |  | Time |  |

## Z1        Z2         Z3         Z4        Z5         Z6        Z7            Z8

See paragraph 7.4.2 for a detailed explanation of this response.

| Display | Display | Display |
|---|---|---|
| Request | Time | Data |

## (02H)

## Z1         Z2         Z3-Z34

## Z1 :        Display Request

                    The payment media reader is requesting a message to be displayed on
                    the VMC’s display.
| Z2 | :        Display | Time | - 0.1 | second | units |
|---|---|---|---|---|---|

                    The requested display time. Either the VMC or the payment media
                    reader may overwrite the message before the time has expired.
        Z3-Z34 : Display Data – ASCII
                 The message to be displayed. Formatting (leading and/or trailing blanks)
                 is the responsibility of the payment media reader.

                    The number of bytes must equal the product of Y3 and Y4 up to a
                    maximum of 32 bytes in the setup/configuration command.

| Begin | Funds |
|---|---|

Session Available

## (03H)

## Z1        Z2-Z3

Level 01 Readers

| Z1 | :      BEGIN | SESSION | (level | 01 | readers) |
|---|---|---|---|---|---|

                 Allow a patron to make a selection, but do not dispense product until
                 funds are approved.
       Z2-Z3 : Funds Available – scaled
               a. Lesser of the user’s payment media or account balance or FFFEh
                   units.
                 b. Not yet determined - FFFFh. (Allows selection without displaying balance)

| Begin | Funds | Payment Payment | Payment |
|---|---|---|---|
| Session | Available | media ID Type | Data |

## (03H)

## Z1        Z2-Z3     Z4-Z7   Z8      Z9-Z10

Level 02 / 03 Readers

| Z1 | :       BEGIN | SESSION | (level | 02/03 | readers) |
|---|---|---|---|---|---|

                  Allow a patron to make a selection, but do not dispense product until
                  funds are approved.
| Z2-Z3 | :    Funds | Available | – scaled |
|---|---|---|---|

                  a. Lesser of the user’s payment media or account balance or FFFEh
                      units.
                  b. Not yet determined - FFFFh. (Allows selection without displaying balance)
| Z4-Z7 | :    Payment | media | ID. |
|---|---|---|---|

                  00000000h-FFFFFFFEh=Payment media identification number.
|  | FFFFFFFFh | = | unknown | payment | media | ID. |
|---|---|---|---|---|---|---|
| Z8 | :       Type of payment: |  |  |  |  |  |

                  00xxxxxxb = normal vend card (refer EVA-DTS Standard, Appendix
                               A.1.1 Definitions)
                  x1xxxxxxb = test media
                  1xxxxxxxb = free vend card
                  xx000000b -0 VMC default prices.
| xx000001b | -1 | User Group |  | (Z9 = EVA-DTS Element DA701) |
|---|---|---|---|---|
|  |  | Price list | number | (Z10 = EVA-DTS Element LA101)* |
| xx000010b | -2 | User Group |  | (Z9 = EVA-DTS Element DA701) |

                                Discount group index (Z10 = EVA-DTS Element MA403)
                  xx000011b -3 Discount percentage factor (Z9=00, Z10 = 0 to 100**,
                                report as positive value in EVA-DTS Element MA404)

| xx000100b | -4 | Surcharge | percentage | factor | (Z9=00, | Z10 | = 0 | to | 100**, |
|---|---|---|---|---|---|---|---|---|---|

                                  report as negative value in EVA-DTS Element MA404)

                              - User Group is a segmentation of all authorized users. It
                               allows selective cost allocation. A User Group usually has
                               no direct relation to a price list.
                               Price Lists are tables of prices. Each Price List contains an
                               individual price for each product.
                               Discount Group indicates the Price List on which the
                               Percentage Factor will be applied.
                               If the User Group, the Price List or Discount Group is
                               unknown by the VMC, the normal prices are used (Z8 is
                               defaulted to `00h`).
                               Minimum value for Z9 and Z10 is 0.

                               ** Percentages are expressed in binary (00 to `64h`)

                               Note:
                                These functions may NOT be supported by all VMCs.

      Z9-Z10 : Payment data as defined above.

| Begin | Funds | Payment Payment | Payment | User | User | Card |
|---|---|---|---|---|---|---|
| Session | Available | media ID Type | Data | Language | Currency | Options |
| (03H) |  |  |  |  | Code |  |

## Z1       Z2-Z5    Z6-Z9    Z10    Z11-Z12 Z13-Z14                 Z15-Z16 Z17

Level 03 (EXPANDED CURRENCY MODE) Readers

| Z1 | :       BEGIN | SESSION | (level | 03 | readers | / EXPANDED | CURRENCY | MODE) |
|---|---|---|---|---|---|---|---|---|

                 Allow a patron to make a selection, but do not dispense product until
                 funds are approved.
| Z2-Z5 | :    Funds | Available | – scaled |
|---|---|---|---|

                 a. Lesser of the user’s payment media or account balance or
                     FFFFFFFEh units.
                 b. Not yet determined - FFFFFFFFh.
| Z6-Z9 | :    Payment | media | ID. |
|---|---|---|---|

                 00000000h-FFFFFFFEh=Payment media identification number.
|  | FFFFFFFFh | = | unknown | payment | media | ID. |
|---|---|---|---|---|---|---|
| Z10 | :    Type of payment: |  |  |  |  |  |

               00xxxxxxb = normal vend card (refer EVA-DTS Standard, Appendix
                            A.1.1 Definitions)
               x1xxxxxxb = test media
               1xxxxxxxb = free vend card
               xx000000b -0 VMC default prices.

| xx000001b | -1 | User Group |  | (Z11 | = EVA-DTS | Element | DA701) |
|---|---|---|---|---|---|---|---|
|  |  | Price list | number | (Z12 | = EVA-DTS | Element | LA101)* |
| xx000010b | -2 | User Group |  | (Z11 | = EVA-DTS | Element | DA701) |

                                  Discount group index (Z12 = EVA-DTS Element MA403)
| xx000011b | -3 | Discount | percentage | factor | (Z11=00, | Z12 | = 0 | to | 100**, |
|---|---|---|---|---|---|---|---|---|---|

                                  report as positive value in EVA-DTS Element MA404)
| xx000100b | -4 | Surcharge | percentage | factor | (Z11=00, | Z12 | = 0 | to | 100**, |
|---|---|---|---|---|---|---|---|---|---|

                                  report as negative value in EVA-DTS Element MA404)

                              - User Group is a segmentation of all authorized users. It
                               allows selective cost allocation. A User Group usually has
                               no direct relation to a price list.
                               Price Lists are tables of prices. Each Price List contains an
                               individual price for each product.
                               Discount Group indicates the Price List on which the
                               Percentage Factor will be applied.
                               If the User Group, the Price List or Discount Group is
                               unknown by the VMC, the normal prices are used (Z10 is
                               defaulted to `00h`).
                               Minimum value for Z11 and Z12 is 0.

                               ** Percentages are expressed in binary (00 to `64h`)

                          Note:
                            These functions may NOT be supported by all VMCs.
      Z11-Z12: Payment data as defined above.
      Z13-Z14 User language to use during this session (2 ASCII characters per ISO
              639:latest version). The user language is read from the patrons card
              and, if supported, should be used instead of the VMC default language
              (taken according to the setup command International Telephone code)
              up to the next “session complete”. If the VMC is not able to support this
              language, the default setting should be used.
      Z15-Z16 User currency code to use during this session per ISO 4217 (see
              Appendix A1). The value is configured as packed BCD with the leading
              digit a 1 (one). For example, the code for the US dollar would be 1840
              (Z15 = 18 and Z16 = 40). and for the Euro is 1978 (Z6 = 19 and Z7 =
              78).
| Z17 | Card options | (overrides any previous default settings for reader) |
|---|---|---|
|  | b0=0:    The | VMC displays the credit if it is programmed to do so |
|  | b0=1:    The | VMC must not display the credit (privacy purpose – user |

                          option)
| b1=0: | The | actual | inserted | patrons | card | has | no refund capability |
|---|---|---|---|---|---|---|---|
| b1=1: | The | actual | inserted | patrons | card | has | refund capability (Note: |

                          reader with refund capability may be used with both type of
                          cards)
| b2=0 | The | actual | inserted | patrons | card | has | no revalue capability |
|---|---|---|---|---|---|---|---|
| b2=1 | The | actual | inserted | patrons | card | has | revalue & negative vend |

                              capability
| b3-b7: | Reserved | for | future | extensions | (unused | bits | must | be | set | to | 0) |
|---|---|---|---|---|---|---|---|---|---|---|---|

                Refund means the ability to put money back on the inserted patrons card up to the
                value of the last transaction. Revalue means the ability to put money back on the
                inserted patrons card up to any value.

                The card reader will define the currency type at the beginning of each card
                session. The currency type will be used for all following transactions in that
                session. If the VMC does not support this currency type, it will end the
                session.

Session
Cancel Request

## (04H)

Z1

## Z1 :       Session Cancel Request

                    The payment media reader is requesting the VMC to cancel the session.
                    The VMC should initiate an eventual SESSION COMPLETE. This response
                    is sent to the VMC whenever the payment media is removed or a request for
                    removal from the reader is made by the user (e.g. if a return button on the
                    reader is pressed).

| Vend | Vend |
|---|---|

Approved Amount

## (05H)

## Z1          Z2-Z3

Level 01 / 02 / 03 Readers

Refer to paragraph 7.4.5 for detailed explanation.

| Vend | Vend |
|---|---|

Approved Amount

## (05H)

## Z1         Z2-Z5

Level 03 (EXPANDED CURRENCY MODE) Readers

Refer to paragraph 7.4.5 for detailed explanation.

Vend
Denied

## (06H)

Z1

Refer to paragraph 7.4.5 for detailed explanation.

End
Session

## (07H)

Z1

Refer to paragraph 7.4.9 for detailed explanation.

Cancelled

## (08H)

Z1

Refer to paragraph 7.4.14 for detailed explanation.

| Peripheral | Manufacturer | Serial | Model      Software |
|---|---|---|---|
| ID | Code | Number | Number Version |

## (09H)

## Z1          Z2-Z4         Z5-Z16 Z17-Z28 Z29-Z30

Level 01 / 02 / 03 Readers (If VMC indicates Level 01 or 02)

## Z1 :        Peripheral Id

                    Reader is sending peripheral ID information.
| Z2 | - Z4 | :   Manufacturer | Code | - ASCII |
|---|---|---|---|---|

                    Identification code for the equipment supplier. Currently defined codes
                    are listed in the EVA document entitled "European Vending
                    Association Data Transfer Standard" (EVA-DTS), the Audit Data
                    Lists section, sub-section 2, "Manufacturer Codes".
| Z5-Z16 | :    Serial | Number | – ASCII |
|---|---|---|---|

                    Factory assigned serial number.
        Z17-Z28 : Model Number - ASCII
                  Manufacturer assigned model number.
        Z29-Z30 : Software Version - packed BCD
                  Current software version.

| Peripheral | Manufacturer | Serial | Model     Software Optional |
|---|---|---|---|
| ID | Code | Number | Number Version Feature bits |

## (09H)

## Z1          Z2-Z4        Z5-Z16 Z17-Z28 Z29-Z30 Z31 - Z34

Level 03 Readers (If VMC indicates Level 03)

## Z1 :       Peripheral Id

                      Reader is sending peripheral ID information.
| Z2 | - Z4 | :     Manufacturer | Code | - ASCII |
|---|---|---|---|---|

                      Identification code for the equipment supplier. Currently defined codes
                      are listed in the EVA document entitled "European Vending
                      Association Data Transfer Standard" (EVA-DTS), the Audit Data
                      Lists section, sub-section 2, "Manufacturer Codes".
| Z5-Z16 | :      Serial | Number | – ASCII |
|---|---|---|---|

                      Factory assigned serial number.
        Z17-Z28 : Model Number - ASCII
                  Manufacturer assigned model number.
        Z29-Z30 : Software Version - packed BCD
                  Current software version.
| Z31- | Z34 | Optional | Feature | Bits. | Each | of | the | 32 | bits | indicate | an | optional | feature |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                      availability. Bits should be sent in descending order, i.e. bit 31 is sent
                      first and bit 0 is sent last. Options must be enabled by the VMC using
                      the Expansion Optional Feature Bit Enable (17H-04H) command and
                      all features are disabled after a reset. Currently defined options are:
                      b0 - File Transport Layer supported
                      b1 - 0 = 16 bit monetary format, 1 = 32 bit monetary format
                      b2 – support multi currency / multi lingual
                      b3 – allow Negative Vend
                      b4 – allow data entry
                      b5 – allow “Always Idle” state
                      b6 to b31 not used (should be set to 0)
                      Note: If 32 bit monetary format (b1) and or multi currency / multi lingual (b2)
                      options are enabled, this condition will be known as EXPANDED
                      CURRENCY MODE in the rest of the document.

| Malfunction | / Error | Error | Code |
|---|---|---|---|

## (0Ah)

## Z1                      Z2

## Z1 :        Malfunction/Error

                    The payment media reader is reporting a malfunction or error.

        Z2 :  Error Code – xxxxyyyy
| xxxx | error types |
|---|---|
| 0000: | Payment media Error1 |
| 0001: | Invalid Payment media1 |
| 0010: | Tamper Error1 |
| 0011: | Manufacturer Defined Error1 |

| 0100: | Communications Error2 |  |  |
|---|---|---|---|
| 0101: | Reader Requires Service2 |  |  |
| 0110: | Unassigned2 |  |  |
| 0111: | Manufacturer Defined Error2 |  |  |
| 1000: | Reader Failure3 |  |  |
| 1001: | Communications Error3 |  |  |
| 1010: | Payment media Jammed3 |  |  |
| 1011: | Manufacturer Defined Error |  |  |
| 1100: | Refund error – internal reader | credit | lost |
| 1101-1111: | Unassigned |  |  |

                1 Transient error - Reported once
                2 Non-transient error - Reported every POLL until cleared. Reader still
                functional.
                3 Non-transient error - Reported every POLL until cleared. Reader not
                presently functional.

                yyyy = Manufacturer defined subcode

     Transient Error Handling
     The error will be reported to the VMC until it has been ACKnowledged. The error state
     will be cleared in the reader, and normal operations will continue.

     Non-transient Error Handling
     The error will be reported to the VMC at each POLL as long as it exists. If the reader is
     still functional, multi-message responses will allow normal responses in addition to the
     error report.

Note: Refund error is sent from the media reader when it is not able to refund money to the
payment media following a failed or cancelled vend. The reader internally cancels the credit
and the credit is lost.

Command
Out of
Sequence

## (0Bh)

Z1
Level 01 Readers

| Z1 | :     COMMAND | OUT | OF | SEQUENCE | (Level | 01 | readers) |
|---|---|---|---|---|---|---|---|

                The payment media reader has received a command that is not
                executable in its current state, or that violates one of the uninterruptable
                sequences. The offending command should be ACKed but not acted
                upon the reader. The VMC will send the RESET command to the reader
                upon reception of this response. Note that the reader will continue with

                any credit update process prior to resetting.

Command Status
Out of
Sequence

## (0Bh)

## Z1          Z2

Level 02 / 03 Readers

| Z1 | :     COMMAND | OUT | OF | SEQUENCE. | (Level | 02/03 | readers) |
|---|---|---|---|---|---|---|---|

                The payment media reader has received a command that is not
                executable in its current state, or that violates one of the uninterruptable
                sequences. The offending command should be ACKed but not acted
                upon the reader. The VMC will send the RESET command to the reader
                upon reception of this response. Note that the reader will continue with
                any credit update process prior to resetting.
| Z2 | :     Status |
|---|---|

                The state of the payment media reader.
                 01: Inactive state
                 02: Disabled state
                 03: Enabled state
                 04: Session idle state
                 05: Vend state
                 06: Revalue state
                 07: Negative Vend state

Revalue
Approved

## (0Dh)

Z1
Level 02 / 03 Readers

Refer to paragraph 7.4.16 for detailed explanation.

Revalue
Denied

## (0Eh)

Z1
Level 02 / 03 Readers

Refer to paragraph 7.4.16 for detailed explanation.

| Revalue | Revalue |
|---|---|

Limit Amount Limit Amount

## (0Fh)

## Z1             Z2-Z3

Level 02 / 03 Readers

Refer to paragraph 7.4.17 for detailed explanation.

| Revalue | Revalue |
|---|---|

Limit Amount Limit Amount

## (0Fh)

## Z1           Z2-Z5

Level 03 (EXPANDED CURRENCY MODE) Readers
Refer to paragraph 7.4.17 for detailed explanation.

| User |  | Number |  | Length |  | User |
|---|---|---|---|---|---|---|
| File | Data | of User | File | Of User | File | Data |

## (10H)

| Z1        Z2 | Z3 | Z4-Zn |
|---|---|---|

Level 02 Readers
Obsolete Response – Do not use for new designs!! (Use EXPANSION – Diagnostics)
Refer to paragraph 7.4.19 for detailed explanation.

Time/Date
Request

## (11H)

Z1
Level 02 / 03 Readers

## Z1 :        Time Date Request

                   In certain circumstances it will be necessary to synchronize the real
                   time clock of the card reader with real time clock of the VMC. The card
                   reader will respond with TIME/DATE REQUEST to a POLL command
                   of the VMC. The VMC will follow with the EXPANSION-WRITE
                   TIME/DATE FILE to the card reader. Refer to paragraph 7.4.19.

| Data | Entry | Data | Entry | Length |
|---|---|---|---|---|

Request Response and Repeat Bit

## (12H)                Z2

Z1
Level 03 Readers (if Data Entry option enabled)

## Z1 :     Data Entry Request

                The reader is making a DATA ENTRY REQUEST.
| Z2 | :     DATA | ENTRY | LENGTH | and | REPEAT | BIT |
|---|---|---|---|---|---|---|

                rnnnnnnnn
                r – Repeat Bit (0 = initial request / 1 = repeated requests
                nnnnnnn – number of requested characters / keys

Depending on the type of data being entered, it is a higher level system decision on whether or
not the data is displayed on either the vending machine or card reader. If the data is not
displayed (a recommendation for certain types of sensitive data) the vending machine or card
reader display can still be optionally used to indicate a prompt and/or representation of the
data entered for user feedback (i.e., asterisks *****).

If the card reader uses the vending machine’s display for Data Entry information, it must
concatenate the DATA ENTRY REQUEST Response (12H) with the DISPLAY REQUEST
response (02H). Upon receipt of the response pair, the vending machine controller will give its
display to the card reader for the duration of the Data Entry session plus the amount of time
specified in the Z2 Display Time following the end of the session (regardless of a normal or
cancelled session). In essence, the vending machine controller will not write anything to its
display during the Data Entry session plus the Z2 time. The reader will be able to update the
Data Entry information on the vending machine’s display by sending additional DISPLAY
REQUEST responses during the Data Entry session.

Please see additional DATA ENTRY procedures in Section 7.4.15.

Data Entry
Cancel

## (13H)

Z1
Level 03 Readers (if Data Entry option enabled)

## Z1 :     Data Entry Cancel

                The user has pushed the reader’s RETURN button before completing the
                DATA ENTRY. The VMC should terminate all DATA ENTRY activity in
                progress.

FTL

## Req To Rcv

## (1Bh)

Z1
Level 03 Readers (if File Transport Layer option enabled)

## Z1 :     Ftl Req To Rcv

                The reader is requesting to receive data from a device or VMC.
| Z2 | :     FTL | Destination | Address |
|---|---|---|---|

                The destination address of the response as defined in Section 2.6.
| Z3 | :     FTL | Source | Address | (Reader | = 10H | / 60H) |
|---|---|---|---|---|---|---|

                The source address of the response as defined in Section 2.6.
| Z4 | :     FTL | File | ID |
|---|---|---|---|

                The type of information desired as defined in Section 2.6.
| Z5 | :     FTL | Maximum | Length |
|---|---|---|---|

                The total number of blocks in the file as defined in Section 2.6.
| Z6 | :     FTL | Control |
|---|---|---|

                Data transfer control information as defined in Section 2.6.

FTL

## Retry/Deny

## (1Ch)

Z1
Level 03 Readers (if File Transport Layer option enabled)

## Z1 :     Ftl Retry / Deny

                The reader is requesting a device or VMC to retry or deny the last FTL
                command.
| Z2 | :     FTL | Destination | Address |
|---|---|---|---|

                The destination address of the response as defined in Section 2.6.
| Z3 | :     FTL | Source | Address | (Reader | = 10H | / 60H) |
|---|---|---|---|---|---|---|

                The source address of the response as defined in Section 2.6.
| Z4 | :     FTL | Retry | Delay |
|---|---|---|---|

                The retry delay as defined in Section 2.6.

FTL
SEND

## Block

## (1Dh)

Z1
Level 03 Readers (if File Transport Layer option enabled)

## Z1 :     Ftl Send Block

                 The reader is sending a block of data (maximum of 31 bytes) to a device
                 or VMC.
| Z2 | :     FTL | Destination | Address |
|---|---|---|---|

                 The destination address of the response as defined in Section 2.6.
| Z3 | :     FTL | Block |
|---|---|---|

                 The sequential number of the block as defined in Section 2.6.
        Z4- Z34 FTL Data (maximum of 31 bytes)
| : | The | actual | data | portion | of | the | block | as | defined | in | Section | 2.6. |
|---|---|---|---|---|---|---|---|---|---|---|---|---|

FTL

## Ok To Send

## (1Eh)

Z1
Level 03 Readers (if File Transport Layer option enabled)

## Z1 :     Ftl Ok To Send

                 The reader is indicating that it is OK for the device or VMC to send it data.
| Z2 | :     FTL | Destination | Address |
|---|---|---|---|

                 The destination address of the response as defined in Section 2.6.
| Z3 | :     FTL | Source | Address | (Reader | = 10H | / 60H) |
|---|---|---|---|---|---|---|

                 The source address of the response as defined in Section 2.6.

FTL

## Req To

SEND

## (1Fh)

Z1
Level 03 Readers (if File Transport Layer option enabled)

## Z1 :     Ftl Req To Send

                  The reader is requesting to send data to a device or VMC.
| Z2 | :     FTL | Destination | Address |
|---|---|---|---|

                  The destination address of the response as defined in Section 2.6.
| Z3 | :     FTL | Source | Address | (Reader | = 10H | / 60H) |
|---|---|---|---|---|---|---|

                  The source address of the response as defined in Section 2.6.
| Z4 | :     FTL | File | ID |
|---|---|---|---|

                  The type of information desired as defined in Section 2.6.
| Z5 | :     FTL | Maximum | Length |
|---|---|---|---|

                  The total number of blocks in the file as defined in Section 2.6.
| Z6 | :     FTL | Control |
|---|---|---|

                  Data transfer control information as defined in Section 2.6.

| Diagnostics | User |
|---|---|
| Response | Defined |
| (FFH) | Data |
| Z1 | Z2-Zn |

Refer to paragraph 7.4.28 for detailed explanation.

#### 7.4.5 VEND - Request

|  | Vend | Item | Item |
|---|---|---|---|
| Vend | Request | Price | Number |

## (13H / 63H) (00H)

## Y1       Y2-Y3       Y4-Y5

Level 01 / 02 / 03 Readers

## Y1 :     Vend Request

                  The patron has made a selection. The VMC is requesting vend approval
                  from the payment media reader before dispensing the product.
         Y2-Y3 : Item Price - scaled
                 The price of the selected product.

         Y4-Y5 : Item Number
                 The item number of the selected product. This number is defined by the
                 manufacturer, and set to FFFFh for undefined or not implemented.

Reader response:

| Vend | Vend |
|---|---|
| Approved | Amount |

## (05H)

## Z1              Z2-Z3

## Z1 :      Vend Approved

                   Allow the selected product to be dispensed.
         Z2-Z3 : Vend Amount - scaled
                 This is the amount deducted from the user’s payment media or account.
                 This may not match the amount specified in the VEND REQUEST
                 command; it may be surcharged or discounted.
                 FFFFh - an electronic token was used.

| NOTE: | The | VMC | must | use | Vend | Amount | to | update | the | credit | on |
|---|---|---|---|---|---|---|---|---|---|---|---|

                                the screen. The Reader must fill this field with the used
                                amount for the transaction.

Vend
Denied

## (06H)

Z1

## Z1 :      Vend Denied

                   Approval denied for the patron’s selection. Do not dispense any products.

|  | Vend | Item | Item |
|---|---|---|---|
| Vend | Request | Price | Number |

## (13H / 63H) (00H)

## Y1      Y2-Y5 Y6-Y7

Level 03 (EXPANDED CURRENCY MODE) Readers

## Y1 :      Vend Request

                   The patron has made a selection. The VMC is requesting vend approval
                   from the payment media reader before dispensing the product.
         Y2-Y5 : Item Price – scaled
                 The price of the selected product.
         Y6-Y7 : Item Number
                 The item number of the selected product. This number is defined by the
                 manufacturer, and set to FFFFh for undefined or not implemented.

Reader Response:

| Vend | Vend |
|---|---|

Approved Amount

## (05H)

## Z1         Z2-Z5

Level 03 (EXPANDED CURRENCY MODE) Readers

## Z1 :     Vend Approved

               Allow the selected product to be dispensed.
      Z2-Z5 : Vend Amount - scaled
              This is the amount deducted from the user’s payment media or account.
              This may not match the amount specified in the VEND REQUEST
              command; it may be surcharged or discounted.
              FFFFFFFFh - an electronic token was used.

| NOTE: | The | VMC | must | use | Vend | Amount | to | update | the | credit | on |
|---|---|---|---|---|---|---|---|---|---|---|---|

                             the screen. The Reader must fill this field with the used
                             amount for the transaction.

#### 7.4.6 VEND - Cancel

              Vend
| Vend | Cancel |
|---|---|

## (13H / 63H)   (01H)

              Y1

## Y1 :       Vend Cancel

                  This command can be issued by the VMC to cancel a VEND REQUEST
                  command before a VEND APPROVED/DENIED has been sent by the
                  payment media reader. The payment media reader will respond to VEND
                  CANCEL with a VEND DENIED and return to the Session Idle state.

Reader response:

 Vend
Denied

## (06H)

  Z1

See paragraph 7.4.5 for explanation.

#### 7.4.7 VEND - Success

|  | Vend | Item |
|---|---|---|
| Vend | Success | Number |

## (13H / 63H)      (02H)

## Y1      Y2-Y3

## Y1 :        Vend Success

                   The selected product has been successfully dispensed.
| Y2-Y3 | :     Item | number |
|---|---|---|

                   The item number of the selected product. This number is defined by the
                   manufacturer, and set to FFFFh for undefined or not implemented.
| NOTE | A | reset | between | VEND | APPROVED | and | VEND | SUCCESS | shall | be |
|---|---|---|---|---|---|---|---|---|---|---|

                   interpreted as a VEND SUCCESS.

Reader response:

 No Data response

#### 7.4.8 VEND - Failure

              Vend
| Vend | Failure |
|---|---|

## (13H / 63H)   (03H)

              Y1

## Y1 :     Vend Failure

                A vend has been attempted at the VMC but a problem has been detected
                and the vend has failed. The product was not dispensed. Funds should
                be refunded to user’s account.

Reader response:

 No Data response

Vend failure sequence
    In order to ensure that a reader refunds after a Vend Failure command, the VMC must
    send at least a single Poll command to obtain the reader possible answers:

| ACK |  | Refund | Complete |  |  |  |
|---|---|---|---|---|---|---|
| MALFUNCTION | ERROR | Refund | error-internal | reader | credit | lost |

code 1100yyyy
| SILENCE | Refund | in | progress. | VMC | must | repoll | reader | until | ACK | or |
|---|---|---|---|---|---|---|---|---|---|---|

                              Malfunction error answer for maximum NON Response
                              time.

#### 7.4.9 SESSION COMPLETE

            Session
| Vend | Complete |
|---|---|

## (13H / 63H) (04H)

            Y1

## Y1 :     Session Complete

                This tells the payment media reader that the session is complete and to
                return to the Enabled state. SESSION COMPLETE is part of a
                command/response sequence that requires an END SESSION response
                from the reader.

Reader response:

End
Session

## (07H)

Z1

## Z1 :      End Session

                 This command is issued in response to a SESSION COMPLETE
                 command. The END SESSION response indicates the reader has
                 returned to the Enabled state. If “END SESSION” is not received by the
                 VMC within a the maximum application non-response time, the VMC
                 must issue a “RESET” command.

#### 7.4.10 CASH SALE

|  | Cash | Item | Item |
|---|---|---|---|
| Vend | Sale | Price | Number |

## (13H / 63H)    (05H)

## Y1       Y2-Y3     Y4-Y5

| Level | 01 | / 02 | / 03 | Readers |
|---|---|---|---|---|

## Y1 :      Cash Sale

                 A cash sale (cash only or cash and cashless) has been successfully
                 completed by the VMC.
       Y2-Y3 : Item Price – scaled
               The price of the selected product or cash portion of the price.
       Y4-Y5 : Item Number
               The item number of the selected product. This number is defined by the
               manufacturer, and set to FFFFh for undefined or not implemented.

Note: This command is issued for cash auditing applications and is sent to the payment
media reader if the SETUP/CONFIGURATION bit (b3) is enabled anytime a valid cash
transaction is completed via a coin mechanism or bill validator.

Reporting of free vends, token vends, etc. should commonly be done, using the following item
number conventions:

Set bit b15 in item number to signal the cash vend as a free vend
Set bit b14 in item number to signal the cash vend as a test vend
Set bit b13 in item number to signal the cash vend as a negative vend (an item was returned
and cash was payed out)
Set bit b12 in item number to signal the cash vend as a token vend

Reader response:

 No Data response

|  | Cash | Item | Item | Item |
|---|---|---|---|---|
| Vend | Sale | Price | Number | Currency |

## (13H)    (05H)

## Y1        Y2-Y5 Y6-Y7    Y8-Y9

                 Level 03 (EXPANDED CURRENCY MODE) Readers

## Y1 :     Cash Sale

                 A cash sale (cash only or cash and cashless) has been successfully
                 completed by the VMC.
        Y2-Y5 : Item Price – scaled
                The price of the selected product or cash portion of the price.
        Y6-Y7 : Item Number
                The item number of the selected product. This number is defined by the
                manufacturer, and set to FFFFh for undefined or not implemented.
        Y8-Y9 : Item Currency
                The currency for the item price used during the vend. This value may be
                converted within the reader to the readers balancing currency. The item
                currency is sent using the numeric code as defined in ISO 4217 (see
                Appendix A1). The value is configured as packed BCD with the leading
                digit a 1 (one). For example, the code for the US dollar would be 1840
                (Z10 = 18 and Z11 = 40). and for the Euro is 1978 (Z10 = 19 and Z11 =
                78).

Note: This command is issued for cash auditing applications and is sent to the payment
media reader if the SETUP/CONFIGURATION bit (b3) is enabled anytime a valid cash
transaction is completed via a coin mechanism or bill validator.

Reader response:

No Data response

#### 7.4.11 Negative Vend Request

            Neg.Vend Item  Item
| Vend | Request | Value | Number |
|---|---|---|---|

## (13H / 63H) (06H)

## Y1       Y2-Y3 Y4-Y5

Level 03 Reader

## Y1 :     Negative Vend Request

                The patron has inserted an item. The VMC is requesting negative vend
                approval from the payment media reader before accepting the returned
                product.
       Y2-Y3 : Item value – scaled
               The value of the inserted product (16 Bit).
       Y4-Y5 : Item Number
               The item number of the inserted product. This number is defined by the
               manufacturer, and set to FFFFh for undefined or not implemented.

Reader response:

| Vend | Vend |
|---|---|

Approved Amount

## (05H)

## Z1         Z2-Z3

Level 03 (EXPANDED CURRENCY MODE disabled) Readers

## Z1 :     Vend Approved

                Allow the returned product to be accepted, i.e. this means, the reader will
                be able to credit the value to the patrons card, when a vend success will
                follow the approved.
       Z2-Z3 : Vend Amount – scaled
               This is the amount of credit, which will be added to the user’s payment
               media or account. This may not match the amount specified in the
               NEGATIVE VEND REQUEST command; it may be surcharged or
               discounted.
               FFFFh - an electronic token will be credited.

            Neg.Vend Item  Item
| Vend | Request | Value | Number |
|---|---|---|---|

## (13H / 63H) (06H)

## Y1       Y2-Y5 Y6-Y7

Level 03 (EXPANDED CURRENCY MODE) Readers

## Y1 :     Negative Vend Request

                The patron has inserted an item. The VMC is requesting negative vend
                approval from the payment media reader before accepting the returned
                product.
       Y2-Y5 : Item value – scaled

                  The value of the inserted product.
         Y6-Y7 : Item Number
                 The item number of the inserted product. This number is defined by the
                 manufacturer, and set to FFFFh for undefined or not implemented.

Reader response:

| Vend | Vend |
|---|---|

Approved Amount

## (05H)

## Z1         Z2-Z5

Level 03 (EXPANDED CURRENCY MODE) Readers

## Z1 :     Vend Approved

                  Allow the returned product to be accepted, i.e. this means, the reader will
                  be able to credit the value to the patrons card, when a vend success will
                  follow the approved.
         Z2-Z5 : Vend Amount – scaled
                 This is the amount of credit, which will be added to the user’s payment
                 media or account. This may not match the amount specified in the
                 NEGATIVE VEND REQUEST command; it may be surcharged or
                 discounted.
                 FFFFFFFFh - an electronic token will be credited.

Vend
Denied

## (06H)

Z1

## Z1 :     Vend Denied

                  Approval denied for the returned product. Do not accept the product or
                  return it if possible.

Note: This command is used in the uninterruptable vend sequence like the normal REQUEST
VEND and is followed by the normal responses VEND APPROVED or VEND DENIED, for the
reader to confirm the credit update possibility and the final VEND SUCCESS or VEND
FAILURE command to update the patron’s credit.

Designers of cashless devices must pay special attention in implementing this command,
especially for non locking readers. Credit should only be generated on the media upon final
reception of VEND SUCCESS to avoid unwanted credit in the system.

Designers of both the VMC and the readers have to deal with fault conditions of such a system
carefully. A normal sequence description is added to the example vend sessions with hints to
different application features.

#### 7.4.12 READER - Disable

| Reader | Disable |
|---|---|

## (14H / 64H) (00H)

            Y1

## Y1 :     Reader Disable

                This informs the payment media reader that it has been disabled, i.e. it
                should no longer accept a patron’s payment media for the purpose of
                vending. Vending activities may be re-enabled using the READER
                ENABLE command. The payment media reader should retain all SETUP
                information.
| NOTE | Any | transaction | in | progress | will | not | be | affected | and | should | continue | to | its |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                normal completion.

Reader response:

 No Data response

#### 7.4.13 READER - Enable

| Reader | Enable |
|---|---|

## (14H / 64H) (01H)

            Y1

## Y1 :     Reader Enable

                This informs the payment media reader that is has been enabled, i.e. it
                should now accept a patron’s payment media for vending purposes. This
                command must be issued to a reader in the Disabled state to enable
                vending operations.

Reader response:

 No Data response

#### 7.4.14 READER - Cancel

| Reader | Cancel |
|---|---|

## (14H / 64H) (02H)

            Y1

## Y1 :      Reader Cancel

                 This command is issued to abort payment media reader activities which
                 occur in the Enabled state. It is the first part of a command/response
                 sequence which requires a CANCELLED response from the reader.

Reader response:

Cancelled

## (08H)

Z1

## Z1 :      Cancelled

                 This is the reader’s response to the READER CANCEL command from
                 the VMC. This command comprises a command/response sequence. Its
                 use is only appropriate in the Enabled state.

#### 7.4.15 DATA ENTRY – Response (Key Entries)

The purpose of the overall Data Entry request / response sequence is to allow the machine
user to enter data (i.e., a card validation number) using the selection buttons on the vending
machine.

The DATA ENTRY request / response sequence can occur in the Enabled state only. It
is the responsibility of the reader to enforce this rule.

Depending on the type of data being entered, it is a higher level system decision on whether or
not the data is displayed on either the vending machine or card reader. If the data is not
displayed (a recommendation for certain types of sensitive data) the vending machine or card
reader display can still be optionally used to indicate a prompt and/or representation of the
data entered for user feedback (i.e., asterisks *****). Please see additional information on
the vending machine’s display usage for Data Entry in the DATA ENTRY REQUEST
Response (12H) description in the 7.4.4 POLL section.

The DATA ENTRY RESPONSE key entries are sent to the reader as they are pressed.
Depending on the user’s speed of entry and vending machine controller cycle time, the data
may be sent either as a digit at a time, a sub group of digits, or the entire length of digits as
specified in the Z2 Data Entry Length byte in the DATA ENTRY REQUEST response. For
example, if the Data Entry Length is 6 digits, but only 2 are initially (and quickly) entered, the
vending machine controller will send the 2 that are available via the DATA ENTRY

RESPONSE Y2-Y9 command. The balance will be sent via other DATA ENTRY RESPONSE
Y2-Y9 commands when available.

It is up to the reader to merge the received DATA ENTRY RESPONSE data and optionally
update the display as required. The session is ended after the VMC sends the final DATA
ENTRY RESPONSE data (no SESSION COMPLETE command is required). Note that the
VMC display will remain available to the reader for the amount of time requested in the
previous DISPLAY REQUEST response.

If the data entry process is cancelled by the VMC for any reason, the VMC will send the DATA
ENTRY RESPONSE with all data bytes (Y2-Y9) set to `FFh`. This will terminate the DATA
ENTRY REQUEST and return the reader to the Enabled state.

For ease of command message processing, the Data Entry Data has been fixed at 8
characters (Y2-Y9). Unused bytes must be sent as `00h` to pad out the entire command to byte
Y9.

            Data Entry Data Entry
| Reader | Response | Data |
|---|---|---|

## (14H / 64H) (03H)         Y2-Y9

            Y1
Level 03 Readers (if option enabled)

## Y1 :     Data Entry Response

                The VMC is providing a DATA ENTRY RESPONSE to the reader.

## Y2-Y9 : Data Entry Data

               Data should be in ASCII, one character per byte. Data should be left
               justified (first character / key in Y2, second in Y3, etc.). The number of
               data bytes must equal eight (8) and unused data bytes must be sent as
               `00h`.

                If the data entry process is cancelled by the VMC for any reason, the
                VMC will send this message with all DATA ENTRY data bytes set to `FFh`.

| Note: | The | reader | must | translate | the | VMC | key | information | into |
|---|---|---|---|---|---|---|---|---|---|

                              the appropriate key needed for the application

Reader response:

No Data response

      Note: If the reader has additional display information to send to the VMC following the
      DATA ENTRY RESPONSE, it should send it via a DISPLAY REQUEST response to
      one of the next POLL commands from the VMC.

#### 7.4.16 REVALUE - Request (Level 02 / 03 Readers)

|  | Revalue | Revalue |
|---|---|---|
| Revalue | Request | Amount |

## (15H / 65H)   (00H)

## Y1         Y2-Y3

Level 02 / 03 Readers

| Y1 | :       REVALUE | REQUEST | (Level | 02 | Readers) |
|---|---|---|---|---|---|

                  A balance in the VMC account because coins or bills were accepted or
                  some balance is left after a vend. With this command the VMC tries to
                  transfer the balance to the payment media.
| Y2-Y3 | :    Revalue | amount | - scaled. |
|---|---|---|---|

                  The revalue amount should not exceed the revalue limit value given by
                  the command REVALUE LIMIT REQUEST.

             Revalue Revalue
| Revalue | Request | Amount |
|---|---|---|

## (15H / 65H)  (00H)

## Y1      Y2-Y5

Level 03 (EXPANDED CURRENCY MODE) Readers
| Y1 | :       REVALUE | REQUEST | (Level | 03 | Readers) |
|---|---|---|---|---|---|

                  A balance in the VMC account because coins or bills were accepted or
                  some balance is left after a vend. With this command the VMC tries to
                  transfer the balance to the payment media.
| Y2-Y5 | :    Revalue | Amount | - scaled. |
|---|---|---|---|

                  The revalue amount should not exceed the revalue limit value given by
                  the command REVALUE LIMIT REQUEST.

Reader response:

Revalue
Approved

## (0Dh)

Z1
Level 02 / 03 Readers

| Z1 | :      REVALUE | APPROVED | (Level | 02 | / 03 | Readers) |
|---|---|---|---|---|---|---|

                 A balance is in the VMC account because coins or bills were accepted or
                 some balance is left after a vend. The VMC has issued a REVALUE
                 REQUEST to the payment media reader to transfer the balance to the
                 payment media. The payment media reader accepted the request and
                 added its value to the payment media balance. The reader then responds
                 with a REVALUE APPROVED, so the VMC may clear the account.

Revalue
Denied

## (0Eh)

Z1
Level 02 Readers

| Z1 | :     REVALUE | DENIED | (Level | 02 | / 03 | Readers) |
|---|---|---|---|---|---|---|

                A balance is in the VMC account because coins or bills were accepted or
                some balance is left after a vend. The VMC has issued a REVALUE
                REQUEST to the payment media reader to transfer the balance to the
                payment media. The payment media reader does not accept the request
                and responds with a REVALUE DENIED, so the VMC has to pay out
                change. It is a quite common situation if there is no payment media
                inserted at this moment.

#### 7.4.17 REVALUE - Limit Request (Level 02 / 03 Readers)

             Revalue
| Revalue | Limit | Request |
|---|---|---|

## (15H / 65H) (01H)

             Y1
Level 02 / 03 Readers

Note: If revaluing, follow the BEGIN SESSION with this command.

| Y1 | :     REVALUE | LIMIT | REQUEST | (Level | 02 | Readers) |
|---|---|---|---|---|---|---|

                In a configuration with a bill and/or coin acceptor and payment media
                reader connected to a VMC, the VMC must know the maximum amount
                the payment media reader eventually will accept by a REVALUE
                REQUEST. Especially if the bill acceptor accepts a wide range of bills.
                Otherwise the VMC may be confronted by the situation where it accepted
                a high value bill and is unable to pay back cash or revalue it to a payment
                media. (see also below)

Reader response:

Revalue Revalue
| Limit | Limit |
|---|---|

Amount Amount

## (0Fh)

## Z1         Z2-Z3

Level 02 / 03 (EXPANDED CURRENCY MODE disabled) Readers

| Z1 | :     REVALUE | LIMIT | AMOUNT | (Level | 02 | / 03 | Readers) |
|---|---|---|---|---|---|---|---|

                 The patron intends to revalue the payment media with a bill of some
                 value. The VMC must know what kind of bills to accept, so it will issue a
                 REVALUE LIMIT REQUEST to get the amount the payment media reader
                 will accept. The payment media reader will respond with the scaled value,
                 calculated with the maximum allowed payment media balance minus the
                 current balance of the payment media. The payment media reader
                 responds with REVALUE DENIED if there is no payment media available
                 upon this request.
       Z2-Z3 : Revalue limit value - scaled.

Reader response:

Revalue Revalue
| Limit | Limit |
|---|---|

Amount Amount

## (0Fh)

## Z1        Z2-Z5

Level 03 (EXPANDED CURRENCY MODE) Readers

| Z1 | :      REVALUE | LIMIT | AMOUNT | (Level | 03 | Readers) |
|---|---|---|---|---|---|---|

                 The patron intends to revalue the payment media with a bill of some
                 value. The VMC must know what kind of bills to accept, so it will issue a
                 REVALUE LIMIT REQUEST to get the amount the payment media reader
                 will accept. The payment media reader will respond with the scaled value,
                 calculated with the maximum allowed payment media balance minus the
                 current balance of the payment media. The payment media reader
                 responds with REVALUE DENIED if there is no payment media available
                 upon this request.
       Z2-Z5 : Revalue Limit Value - scaled.

#### 7.4.18 EXPANSION - Request ID

|  | Request | Manufacturer | Serial | Model | Software |
|---|---|---|---|---|---|
| Expansion | ID | Code | Number | Number | Version |

## (17H / 67H) (00H)

## Y1          Y2-Y4           Y5-Y16       Y17-Y28 Y29-Y30

## Y1 :          Request Id

                     The VMC is requesting payment media reader identification
                     information. The information included above (Y2-Y30) provides the
                     payment media reader with VMC identification information.
| Y2-Y4 | :       Manufacturer | Code | - ASCII |
|---|---|---|---|

                     Identification code for the equipment supplier. Currently defined

                      codes are listed in the EVA document entitled “The Data Transfer
                      Standard EVA-DTS" document, the Audit Data Dictionary section,
                      chapter 4, "Manufacturer Codes".
| Y5-Y16 | :       Serial | Number | - ASCII |
|---|---|---|---|

                      Factory assigned serial number.
| Y17-Y28 | :      Model | Number | - ASCII |
|---|---|---|---|

                      Manufacturer assigned model number.
| Y29-Y30 | :      Software | Version | - packed | BCD |
|---|---|---|---|---|

                      Current software version.

Reader response:

| Peripheral | Manufacture | Serial | Model      Software |
|---|---|---|---|
| ID | Code | Number | Number Version |

## (09H)

## Z1          Z2-Z4         Z5-Z16 Z17-Z28 Z29-Z30

Level 01 / 02 / 03 Readers (If VMC indicates Level 01 or 02)

| Peripheral | Manufacture | Serial | Model | Software | Optional |
|---|---|---|---|---|---|
| ID | Code | Number | Number | Version | Feature Bits |

## (09H)

## Z1           Z2-Z4           Z5-Z16     Z17-Z28      Z29-Z30    Z31-Z34

Level 03 Readers (If VMC indicates Level 03)

See paragraph 7.4.4 for a detailed explanation of this response.

#### 7.4.19 EXPANSION - Read User File (Level 02 Readers)

Obsolete Command – Do not use for new designs!! (Use EXPANSION - Diagnostics)

|  | Read | Number |
|---|---|---|
| Expansion | User | of User |
| (17H / 67H) | File | File |

## (01H)

## Y1          Y2

Level 02 Readers

## Y1=        Read User File

                  The VMC request’s the user file. The length of the file is variable with a

                  maximum length of 32 bytes. The contents of the data are defined by the
                  VMC manufacturer. If the payment media reader does support this
                  command it will respond with USER FILE DATA.
| Y2= | Number | of | User | File. |
|---|---|---|---|---|

                  The File identification number. The number and size of the data files are
                  defined by the payment media reader manufacturer. The maximum
                  number of user files are `FFh`.

Reader response:

| User | Number | Length | User |
|---|---|---|---|
| Data | of User | of User | Data |
| File | File | File |  |

## (10H)

| Z1      Z2 | Z3 | Z4-Zn |
|---|---|---|

| Z1 | :      USER | FILE | DATA | (only | level | 02 | readers) |
|---|---|---|---|---|---|---|---|

                  The VMC requires user data and has issued a EXPANSION - READ
                  USER FILE to the payment media reader.
| Z2 | :      Number | of | User | File. |
|---|---|---|---|---|

                  The File identification number. The number and size of data files are
                  defined by the payment media reader manufacturer. The maximum
                  number of user files are `FFh`.
| Z3 | :      Length | of | user | file |
|---|---|---|---|---|

                  The length of the user file. The maximum length of the user file is 32
                  bytes. If the user file don’t exists the length will be set to `00h`.
        Z4-Zn : Data defined by the VMC manufacturer.

#### 7.4.20 EXPANSION - Write User File (Level 02 Readers)

Obsolete Command – Do not use for new designs!! (Use EXPANSION - Diagnostics)

|  | Write | Number | Length User |
|---|---|---|---|
| Expansion | User | of User | of User Data |
| (17H / 67H) | File | File | File |

## (02H)

| Y1 | Y2 | Y3 | Y4-Yn |
|---|---|---|---|

## Y1 :      Write User File

                  The VMC request’s to write the user file. The length of the file is variable
                  with a maximum length of 32 bytes. The contents of the data are defined
                  by the VMC manufacturer. If the command is supported but the payment
                  media reader is unable to write the payment media (writing problem or
                  data too long) it will respond with MALFUNCTION/ERROR.

| Y2 | :     Number | of | User | File. |
|---|---|---|---|---|

                The File identification number. The number and size of data files are
                defined by the payment media reader manufacturer. The maximum
                number of user files are `FFh`.
| Y3 | :     Length | of | user | file |
|---|---|---|---|---|

                The length of the user file. The maximum length of the user file is 32
                bytes.
       Y4-Yn : Data defined by the VMC manufacturer.

Reader response:

 No Data response

#### 7.4.21 EXPANSION - Write Time/Date File (Level 02/03 readers)

| Expansion | Write Time/ | Time |
|---|---|---|
| (17H / 67H) | Date File | Date |

## (03H)

## Y1             Y2-Y11

## Y1 :       Write Time/Date File

                  The VMC requests to write the Time/Date file.
       Y2- Y11: Time/Date to synchronize the card reader real time clock. The date
                bytes are BCD encoded.

                  Y2 = Years (Range: 00..99)
                  Y3 = Months (Range: 01..12)
                  Y4 = Days (Range: 01..31)
                  Y5 = Hours (Range: 00..23)
                  Y6 = Minutes (Range: 00..59)
                  Y7 = Seconds (Range: 00..59)
                  Y8 = Day of Week (Range: 01..07, Monday = 1..Sunday = 7)
                  Y9 = Week Number (Range: 01..53)
                  Y10 = Summertime (Range: 00..01, Summertime = 1)
                  Y11 = Holiday (Range: 00..01, Holiday = 1)
                  If any item of the time/date is not supported use FFH instead.

#### 7.4.22 EXPANSION – Enable Options (Level 03 readers)

| Expansion | Optional | Feature | Bit | Enable | Optional | Feature | Bits |
|---|---|---|---|---|---|---|---|

## (17H / 67H)   (04H)

## Y1                              Y2-Y5

Level 03 Readers

## Y1 :        Optional Feature Bit Enable

                   The VMC can enable which level 3 features it desires.
| Y2 | - Y5: | Individual | expanded | feature | bits | as | sent | by | reader | in | response | to | the |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                   17H-00H EXPANSION REQUEST ID command. To enable a feature, a
                   bit is set to one. Bits should be sent in descending order, i.e. bit 31 is
                   sent first and bit 0 is sent last. All features are disabled after a reset.
                   b0 - File Transport Layer supported
                   b1 - 0 = 16 bit monetary format, 1 = 32 bit monetary format
                   b2 – Enable multi currency / multi lingual
                   b3 – Enable negative vend
                   b4 - Enabledata entry
                   b5 – Enable “Always Idle” state
                   b6 to b31 not used (should be set to 0)
                   Note: If 32 bit monetary format (b1) and or multi currency / multi lingual
                   (b2) options are enabled, this condition will be known as EXPANDED
                   CURRENCY MODE in the rest of the document.

#### 7.4.23 EXPANSION – FTL REQ TO RCV

| Expansion | FTL | REQ | TO | RCV |
|---|---|---|---|---|

## (17H / 67H) (Fah)

## Y1            Y2-Y6

Level 03 Readers (if File Transport Layer option enabled)

The VMC is requesting to receive data from the reader whose destination address will always
be 10H or 60H. Note that all FTL Commands / Responses are defined in Section 2.6.

## Y1 :       Ftl Req To Rcv

                  The VMC is requesting to receive data from the reader.
| Y2 | :       FTL | Destination Address | (Reader | = 10H | / 60H | as | defined | in | Section | 2.6. |
|---|---|---|---|---|---|---|---|---|---|---|
| Y3 | :       FTL | Source Address |  |  |  |  |  |  |  |  |

                  The source address of the command as defined in Section 2.6.
| Y4 | :       FTL | File | ID |
|---|---|---|---|

                  The type of information desired as defined in Section 2.6.
| Y5 | :       FTL | Maximum | Length |
|---|---|---|---|

                  The total number of blocks in the file as defined in Section 2.6.
| Y6 | :       FTL | Control |
|---|---|---|

                  Data transfer control information as defined in Section 2.6.

Reader response:

Two responses are possible from the reader, either the SEND BLOCK (1DH) which transmits
the initial (or only) part of the data or the RETRY / DENY (1CH). Note that the response can
either be immediate or delayed.

## Ftl (1Dh)         Send Block

| SEND | BLOCK | Information |
|---|---|---|

## Z1                Z2-Z34

| Z1 | :     1DH response which indicates SEND BLOCK |  |  |
|---|---|---|---|
| Z2 | :     Destination address of data as defined in | Section | 2.6 |
| Z3 | :     Block # of data as defined in Section 2.6 |  |  |

       Z4-Z34: Data (maximum of 31 bytes)

                                                or

## Ftl (1Ch)         Retry / Deny

| RETRY | / DENY | Information |
|---|---|---|

## Z1                Z2-Z4

| Z1 | :     1CH response which indicates RETRY / DENY |  |
|---|---|---|
| Z2 | :     Destination address of response as defined in Section 2.6 |  |
| Z3 | :     Source address of response (10H / 60H) as defined in Section | 2.6 |
| Z4 | :     Retry delay |  |

#### 7.4.24 EXPANSION – FTL RETRY / DENY

| Expansion | FTL | RETRY | / DENY |
|---|---|---|---|

## (17H)      (Fbh)

## Y1             Y2-Y4

Level 03 Readers (if File Transport Layer option enabled)

The VMC is retrying, denying, or aborting a data transfer to/from the reader whose destination
address will always be 10H or 60H. Note that all FTL Commands / Responses are defined in
Section 2.6.

## Y1 :     Ftl Retry / Deny

                The VMC is requesting to retry, deny, or abort a data transfer.
| Y2 | :     FTL | Destination | Address | (Reader | = 10H | / 60H) |
|---|---|---|---|---|---|---|

                The destination address of the command as defined in Section 2.6.
| Y3 | :     FTL | Source | Address |
|---|---|---|---|

                 The source address of the command as defined in Section 2.6.
| Y4 | :      FTL | Retry | Delay |
|---|---|---|---|

                 The time delay required of the sender as defined in Section 2.6.

Reader response:

None

#### 7.4.25 EXPANSION – FTL SEND BLOCK

| Expansion | FTL | SEND | BLOCK |
|---|---|---|---|

## (17H / 67H) (Fch)

## Y1            Y2-Y34

Level 03 Readers (if File Transport Layer option enabled)

The VMC is sending data to the reader whose destination address will always be 10H or 60H.
Note that all FTL Commands / Responses are defined in Section 2.6.

## Y1 :      Ftl Send Block

                 The VMC is requesting to send data.
| Y2 | :      FTL | Destination | Address | (Reader | = 10H | / 60H) |
|---|---|---|---|---|---|---|

                 The destination address of the command / data as defined in Section 2.6.
| Y3 | :      FTL | Block |
|---|---|---|

                 The block # of data as defined in Section 2.6
       Y4-Y34 FTL Data (maximum of 31 bytes)
              The actual data block as defined in Section 2.6.

Reader response:

None

#### 7.4.26 EXPANSION – FTL OK TO SEND

| Expansion | FTL | OK | TO | SEND |
|---|---|---|---|---|

## (17H / 67H) (Fdh)

## Y1            Y2-Y3

Level 03 Readers (if File Transport Layer option enabled)

The VMC is indicating that it is OK for the reader to transfer data. The destination address will
always be the reader 10H or 60H. Note that all FTL Commands / Responses are defined in
Section 2.6.

## Y1 :     Ftl Ok To Send

                The VMC is indicating it is OK to send data.

| Y2 | :      FTL | Destination | Address | (Reader | = 10H | / 60H) |
|---|---|---|---|---|---|---|

                 The destination address of the command / data as defined in Section 2.6.
| Y3 | :      FTL | Source | Address |
|---|---|---|---|

                 The source address of the command as defined in Section 2.6.
Reader response:

One response is possible from the reader which transmits the initial (or only) part of the data.
Note that the response can either be immediate or delayed.

## Ftl (1Dh)     Send Block

| SEND | Information |
|---|---|

## Block

## Z1            Z2-Z34

| Z1 | :      1DH response which indicates SEND BLOCK |  |  |
|---|---|---|---|
| Z2 | :      Destination address of data as defined in | Section | 2.6 |
| Z3 | :      Block # of data as defined in Section 2.6 |  |  |

       Z4-Z34: Data (maximum of 31 bytes)

#### 7.4.27 EXPANSION – FTL REQ TO SEND

| Expansion | FTL | REQ | TO | SEND |
|---|---|---|---|---|

## (17H / 67H) (Feh)

## Y1            Y2-Y6

Level 03 Readers (if File Transport Layer option enabled)

The VMC is requesting to send data to the reader whose destination address will always be
10H or 60H. Note that all FTL Commands / Responses are defined in Section 2.6.

## Y1 :      Ftl Req To Send

                 The VMC is requesting to send data to the reader.
| Y2 | :      FTL | Destination | Address | (Reader | = 10H | / 60H) |
|---|---|---|---|---|---|---|

                 The destination address of the command as defined in Section 2.6.
| Y3 | :      FTL | Source | Address |
|---|---|---|---|

                 The source address of the command as defined in Section 2.6.
| Y4 | :      FTL | File | ID |
|---|---|---|---|

                 The type of information desired as defined in Section 2.6.
| Y5 | :      FTL | Maximum | Length |
|---|---|---|---|

                 The total number of blocks in the file as defined in Section 2.6.

| Y6 | :     FTL | Control |
|---|---|---|

                Data transfer control information as defined in Section 2.6.

Reader response:

Two responses are possible from the reader, either the OK TO SEND (1EH) which allows the
data transfer to start or the RETRY / DENY (1CH). Note that the response can either be
immediate or delayed.

## Ftl (1Eh)          Ok To Send

| OK TO | SEND | Information |
|---|---|---|

## Z1                 Z2-Z3

| Z1 | :     1EH response which indicates OK | TO SEND |  |
|---|---|---|---|
| Z2 | :     Destination address of response | as defined in Section 2.6 |  |
| Z3 | :     Source address of response (10H | / 60H) as defined in Section | 2.6 |

                                                or

## Ftl (1Ch)          Retry / Deny

| RETRY | / DENY | Information |
|---|---|---|

## Z1                 Z2-Z4

| Z1 | :     1CH response which indicates RETRY / DENY |  |
|---|---|---|
| Z2 | :     Destination address of response as defined in Section 2.6 |  |
| Z3 | :     Source address of response (10H / 60H) as defined in Section | 2.6 |
| Z4 | :     Retry delay |  |

#### 7.4.28 EXPANSION - Diagnostics

| Expansion | Diagnostics | User |
|---|---|---|
| (17H / 67H) | (FFH) | Defined |

                              Data
| Y1 | Y2-Yn |
|---|---|

## Y1 :     Diagnostics.

                Device manufacturer specific instruction for implementing various
                manufacturing or test modes.

     Y2-Yn : User Defined Data.

                 The data portion of this command is defined by the manufacturer and is
                 not part of this document.

Reader response:

| Diagnostics | User |
|---|---|
| Response | Defined |

## (Ffh)

| Z1            Z2-Zn |
|---|

## Z1 :      Diagnostics Response

       Z2-Zn : User Defined Data.
               The data portion of this response is defined by the manufacturer and is
               not part of this document.

#### 7.5 Cashless Device Non-Response Time

The default maximum non-response time for a cashless device is 5 seconds. This is the
maximum time for which a cashless device will not respond to a command or a POLL with
ACK, NAK or a message. The “Application Maximum Response Time” reported in byte Z7 of
the Reader Configuration Data (7.4.2) supersedes this default value if Z7 is greater.

Unless otherwise specified, a VMC should also use this value as a timeout for a response to
commands that require data to be returned. (See Section 7.3.)

#### 7.6 Cashless Device Power Requirements

The current draw for any cashless device must fall within the following limits. All
measurements are at the minimum VMC Voltage Output.

Idle mode = 300 mA. (avg.) continuous

Transport or Read/Write cycle = 1.5 A @ 50% maximum duty cycle up to 5 seconds.

#### 7.7 Example Vend Sessions

## Example Vend Session #1

                                    (Valid Single Vend)

| Controller | Cashless | Device | State |
|---|---|---|---|

## Poll                   

|  | BEGIN | SESSION | (Session | Idle) |
|---|---|---|---|---|

## Ack                    

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

## Poll                   

##         Vend Approved

## Ack                    

## Vend Success           

|  | ACK | (Session | Idle) |
|---|---|---|---|

## Session                

## Complete

##         Ack

## Poll                   

|  | END | SESSION | (Enabled) |
|---|---|---|---|

## Ack                    

## Example Vend Session #2

                                   (Valid Multiple Vend)

| Controller | Cashless | Device | State |
|---|---|---|---|

## Poll                   

|  | BEGIN | SESSION | (Session | Idle) |
|---|---|---|---|---|

## Ack                    

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

## Poll                   

##         Vend Approved

## Ack                    

## Vend Success           

|  | ACK | (Session | Idle) |
|---|---|---|---|

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

## Poll                   

##         Vend Approved

## Ack                    

## Vend Success           

|  | ACK | (Session | Idle) |
|---|---|---|---|

## Session                

## Complete

##         Ack

## Poll                   

|  | END | SESSION | (Enabled) |
|---|---|---|---|

## Ack                    

## Example Vend Session #3

                   (Session cancelled by user with reader return button)

| Controller | Cashless | Device | State |
|---|---|---|---|

## Poll                   

|  | BEGIN | SESSION | (Session | Idle) |
|---|---|---|---|---|

## Ack                    

                User pushes reader RETURN button

## Poll                   

##         Session Cancel

## Ack                    

## Session                

## Complete

##         Ack

## Poll                   

|  | END | SESSION | (Enabled) |
|---|---|---|---|

## Ack                    

                             EXAMPLE VEND SESSION #4a
                     (Session cancelled by user via coin mechanism
                    escrow return button before product was selected)

| Controller | Cashless | Device | State |
|---|---|---|---|

## Poll                   

|  | BEGIN | SESSION | (Session | Idle) |
|---|---|---|---|---|

## Ack                    

                User pushes coin mech. escrow return

## Session                

## Complete

##         Ack

## Poll                   

|  | END | SESSION | (Enabled) |
|---|---|---|---|

## Ack                    

                              EXAMPLE VEND SESSION #4b
                      (Session cancelled by user via coin mechanism
                     escrow return button after product was selected)

| Controller | Cashless | Device | State |
|---|---|---|---|

## Poll                   

|  | BEGIN | SESSION | (Session | Idle) |
|---|---|---|---|---|

## Ack                    

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

                User pushes coin mech. escrow return

## Cancel Vend            

##         Ack

## Poll                   

|  | VEND | DENIED | (Session | Idle) |
|---|---|---|---|---|

## Session                

## Complete

##         Ack

## Poll                   

|  | END | SESSION | (Enabled) |
|---|---|---|---|

## Ack                    

## Example Vend Session #5

                            (VMC Failure/product not dispensed
                                     Refund positive)

| Controller | Cashless | Device | State |
|---|---|---|---|

## Poll                   

|  | BEGIN | SESSION | (Session | Idle) |
|---|---|---|---|---|

## Ack                    

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

                Reader deducts purchase price from payment media

## Poll                   

##         Vend Approved

                VMC fails to dispense product

## Vend Failure           

##         Ack

## Poll                   

|  | Silence | during | the |
|---|---|---|---|

                                refund operation

## Poll                   

##         Ack                    C

## Session                

## Complete

##         Ack

## Poll                   

|  | END | SESSION | (Enabled) |
|---|---|---|---|

## Ack                    

## Example Vend Session #5A

                            (VMC Failure/product not dispensed
                                        Refund fail)

| Controller | Cashless | Device | State |
|---|---|---|---|

## Poll                   

|  | BEGIN | SESSION | (Session | Idle) |
|---|---|---|---|---|

## Ack                    

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

                Reader deducts purchase price from payment media

## Poll                   

##         Vend Approved

                VMC fails to dispense product

## Vend Failure           

##         Ack

## Poll                   

|  | Silence | during | the |
|---|---|---|---|

                                refund operation

## Poll                   

##         Malfunction

                                ERROR code
| 1100yyyy=refund | fail | (Level | 02 / | 03) |
|---|---|---|---|---|
| ACK |  | (Level | 01) |  |

## Session                

## Complete

##         Ack

## Poll                   

|  | END | SESSION | (Enabled) |
|---|---|---|---|

## Ack                    

## Example Vend Session #6

                                  (Vend denied by reader)

| Controller | Cashless | Device | State |
|---|---|---|---|

## Poll                   

|  | BEGIN | SESSION | (Session | Idle) |
|---|---|---|---|---|

## Ack                    

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

                Insufficient funds or payment media/account error

## Poll                   

|  | VEND | DENIED | (Session | Idle) |
|---|---|---|---|---|

                VMC makes no attempt to dispense product

## Session                

## Complete

##         Ack

## Poll                   

|  | END | SESSION | (Enabled) |
|---|---|---|---|

## Ack                    

## Example Vend Session #7

                             (Command Out of Sequence Error)

| Controller | Cashless | Device | State |
|---|---|---|---|

## Poll                   

|  | BEGIN | SESSION | (Session | Idle) |
|---|---|---|---|---|

## Ack                    

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

## Expansion

## Id Request             

##         Ack

## Poll                   

##         Command Out

| OF | SEQUENCE | (Session | Idle) |
|---|---|---|---|

## Ack                    

| RESET |  | {Mandatory} |
|---|---|---|

##         Ack

                                                       (Inactive)

                             EXAMPLE VEND SESSION #8a
                  (Reader busy for longer than max. non response time)

| Controller | Cashless | Device | State |
|---|---|---|---|

## Poll                   

|  | BEGIN | SESSION | (Session | Idle) |
|---|---|---|---|---|

## Ack                    

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

## Poll                   

|  |  |  | [silence…] | (Reader busy) |  |  |  |
|---|---|---|---|---|---|---|---|
| POLLs | (numerous) |  |  |  |  |  |  |
|  |  |  | [silence…] | (continued POLLs | w/ | no | response) |

## Poll                   

|  |  |  | ACK | (restart Non-Response timer) |
|---|---|---|---|---|
| POLLs | (numerous) |  |  |  |
|  |  |  | [silence…] | (continued POLLs w/ no response) |

## Poll                   

|  | [silence…] | (Reader | almost | finished) |
|---|---|---|---|---|

## Poll                   

|  | VEND | APPROVED | (Reader | ready) |
|---|---|---|---|---|

## Ack                    

## Vend Success           

|  | ACK | (Session | Idle) |
|---|---|---|---|

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

## Poll                   

##         Vend Approved

## Ack                    

## Vend Success           

|  | ACK | (Session | Idle) |
|---|---|---|---|

## Session                

## Complete

##         Ack

## Poll                   

|  | END | SESSION | (Enabled) |
|---|---|---|---|

## Ack                    

                             EXAMPLE VEND SESSION #8b
                  (Reader busy for shorter than max. non response time)

| Controller | Cashless | Device | State |
|---|---|---|---|

## Poll                   

|  | BEGIN | SESSION | (Session | Idle) |
|---|---|---|---|---|

## Ack                    

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

## Poll                   

|  |  |  | [silence...] | (Reader busy) |  |  |  |
|---|---|---|---|---|---|---|---|
| POLLs | (numerous) |  |  |  |  |  |  |
|  |  |  | [silence...] | (Continued POLLs | w/ | no | response) |

## Poll                   

|  | [silence...] | (Reader | almost | finished) |
|---|---|---|---|---|

## Poll                   

|  | VEND | APPROVED | (Reader | ready) |
|---|---|---|---|---|

## Ack                    

## Vend Success           

|  | ACK | (Session | Idle) |
|---|---|---|---|

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

## Poll                   

##         Vend Approved

## Ack                    

## Vend Success           

|  | ACK | (Session | Idle) |
|---|---|---|---|

## Session                

## Complete

##         Ack

## Poll                   

|  | END | SESSION | (Enabled) |
|---|---|---|---|

## Ack                    

NOTE
If the peripheral omits to respond within the maximum non-response time, it is considered to
be off-line.

                             EXAMPLE VEND SESSION #8c
                      (No Response, Reader busy at Vend Request.)

| Controller | Cashless | State/ | Comment |
|---|---|---|---|

                                Device

## Poll                   

##         Begin

## Session

## Ack                    

## Vend Request           

|  | [silence…] | Reader | busy. | The | reader | may | not | send |
|---|---|---|---|---|---|---|---|---|

                                                     the response within the t-response(max)
                                                     timeout or hasn’t received the command
                                                     completely due to line breakdown
| VEND | REQUEST |  | VMC | repeats | the | command: | As | the | VMC |
|---|---|---|---|---|---|---|---|---|---|

                                                     isn’t sure, that the slave has received the
                                                     command free of errors it repeats it. The
                                                     command itself is not yet performed by
                                                     the reader as long the ACK hasn’t been
                                                     sent.
|  | [silence…] | Reader | busy |
|---|---|---|---|

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

                                                     The reader will now perform the
                                                     command. The response isn’t available at
                                                     the moment, thus the VEND REQUEST
                                                     is only acked

| POLL | (numerous) |  | VMC | polls | the | reader | to | obtain | the | data | in |
|---|---|---|---|---|---|---|---|---|---|---|---|

## Vend Approved

|  | ACK | The | reader | may | send | a ACK | or | [silence] |
|---|---|---|---|---|---|---|---|---|

                                                     to each POLL

## Poll                   

|  | VEND | The | response to the VEND REQUEST is |  |
|---|---|---|---|---|
|  | APPROVED | now | available. It must be sent within | the |

                                                     time defined by the APPLICATION
                                                     MAXIMUM RESPONSE TIME. This is
                                                     measured from the ACK following the

## Vend Request.

## Ack                    

## Example Vend Session #9

                     (Pre-approved authorization aborted by coin
                mechanism escrow return button before BEGIN SESSION)

| Controller | Cashless | Device | State |
|---|---|---|---|

                User swipes payment media
                                                       (Enabled)

## Poll                   

##         Ack

## Reader Cancel          

##         Ack

                (If applicable, reader aborts HOST communications, ejects payment
                media, etc...)

## Poll                   

##         Cancelled

## Ack                    

## Example Vend Session #10

                                    (Single Negative Vend)
| Controller | Cashless | Device | State |
|---|---|---|---|

## Poll                  

|  | BEGIN | SESSION | (Session | Idle) |
|---|---|---|---|---|

## Ack                   

                      User inserted a payment media, and inserted then a product, which
                      was detected valid, or pressed a selection button to identify the
                      desired product which will be inserted later on

## Negative         Vend 

## Request

|  | ACK | (Vend) |
|---|---|---|

## Poll                     

##           Vend Approved

                         The payment reader is able to add the desired value to the credit

## Ack                      

                         The product is now fully accepted from the machine or the user has
                         finally finished insertion of a valid product

## Vend Success             

|  | ACK | (Session | Idle) |
|---|---|---|---|

                         The payment media reader has added the credit

## Session                  

## Complete

##         Ack

## Poll                     

|  | END | SESSION | (Enabled) |
|---|---|---|---|

## Ack                      

Normally, can or bottle return-vendors may check the product first, before the patron inserts
his card. It is up to the VMC, to delay the negative vend request, until the session idle state is
reached. In many return-vendors, from this state, the product is already fully accepted.
Therefore, there is no need for the further sequences, this means, vend accepted, vend
success will follow each other immediately.
If the payment media reader is not able to update the credit, there will be two conditions:
- The return vendor is able to escrow the product after the vend denied. In this case the
    session complete is sent, the product is return and the credit remains unchanged.
- The return vendor is not able to escrow the product after vend denied. In this case, session
    complete should be sent and there should be an update credit within the system (VMC),
    which could be returned by other means (i.e. return coins, tokens, etc).
If a return vendor is able to escrow the product again, this vendor normally accepts the product
finally only a vend accepted was sent. In this case there may happen some fault condition
which allows no final acceptance of the product. The return vendor then closes the session
with vend failed instead of vend success, indicating to the reader not to update the system
credit, or, if the payment media is no longer present, request re-insertion of the media.

## Example Vend Session #11

                                (Always Idle state option set)

| Controller | Cashless | Device | State |
|---|---|---|---|

## Poll                   

|  | ACK | (Enabled) |
|---|---|---|

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

## Poll                   

|  | ACK | (repeated | until | User | presents |
|---|---|---|---|---|---|

                                                       cashless media or timeout)

## Poll                   

##         Vend Approved

## Ack                    

## Vend Success           

|  | ACK | (Session | Idle) |
|---|---|---|---|

## Session                

## Complete

##         Ack

## Poll                   

|  | END | SESSION | (Enabled) |
|---|---|---|---|

## Ack                    

## Example Vend Session Cancelled #12

                             (Always Idle state option set)

| Controller | Cashless | Device | State |
|---|---|---|---|

## Poll                   

|  | ACK | (Enabled) |
|---|---|---|

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

## Poll                   

|  | ACK | (repeated | until | User | presents |
|---|---|---|---|---|---|

                                                       cashless media ), but instead of
                                                       this, cash is inserted

## Vend Cancel            

|  | ACK | (Session | Idle) |
|---|---|---|---|

## Poll                   

|  | VEND | DENIED | (Session | Idle) |
|---|---|---|---|---|

## Session                

## Complete

##         Ack

## Poll                   

|  | END | SESSION | (Enabled) |
|---|---|---|---|

## Ack                    

## Example Vend Session Timeout#13

                               (Always Idle state option set)

| Controller | Cashless | Device | State |
|---|---|---|---|

## Poll                   

|  | ACK | (Enabled) |
|---|---|---|

## Vend Request           

|  | ACK | (Vend) |
|---|---|---|

## Poll                   

|  | ACK | (repeated | until | User | presents |
|---|---|---|---|---|---|

                                                       cashless media or timeout), timeout
                                                       occurs

## Poll                   

##         Vend Denied

## Ack                    

## Session                

## Complete

##         Ack

## Poll                   

|  | END | SESSION | (Enabled) |
|---|---|---|---|

## Ack                    

## Example Data Entry Session #1

                    (Three key Data Entry w/ Prompt & Asterisks for Entries)

| Controller | Cashless | Device | State |
|---|---|---|---|

| Previously | Enabled | Enabled |
|---|---|---|

## Poll                   

##         Data Entry Request +

                                DISPLAY REQUEST (prompt)

## Ack                    

                        User pushes Selection Key 1

## Data Entry             

RESPONSE (Key 1)

##         Ack

## Poll                   

|  | DISPLAY | REQUEST | (prompt | + *) |
|---|---|---|---|---|

## Ack                    

                        User pushes Selection Key 2

## Data Entry             

RESPONSE (Key 2)

##         Ack

## Poll                   

|  | DISPLAY | REQUEST | (prompt | + **) |
|---|---|---|---|---|

## Ack                    

                        User pushes Selection Key 3

## Data Entry             

RESPONSE (Key 3)
|  | ACK | (Enabled) |
|---|---|---|

## Poll                   

|  | DISPLAY | REQUEST | (prompt | + *** |
|---|---|---|---|---|

                                                or “Entry OK”)

## Ack                    

                        Note: After Display Request Time
                              expires, VMC regains control of
                              display

## Poll                   

|  | BEGIN | SESSION | (Session | Idle) |
|---|---|---|---|---|

## Ack                    

## Example Data Entry Session #2

                              (Data Entry with Reader Cancel)

| Controller | Cashless | Device | State |
|---|---|---|---|

| Previously | Enabled | Enabled |
|---|---|---|

## Poll                   

##         Data Entry Request +

                                DISPLAY REQUEST (prompt)

## Ack                    

                        User pushes (valid) Selection Key

## Data Entry             

RESPONSE (Key 1)

##         Ack

## Poll                   

|  | DISPLAY | REQUEST | (prompt | + *) |
|---|---|---|---|---|

## Ack                    

                        User pushes (invalid) Selection Key

## Data Entry             

RESPONSE (Key 2)

##         Ack

## Poll                   

##         Data Entry Cancel

| ACK |  | (Enabled) |
|---|---|---|

## Poll                   

|  | DISPLAY | REQUEST | (“Error”) |
|---|---|---|---|

## Ack                    

                         After Display Request Time expires,
                         VMC regains control of display

Note that the above scenario is only an example and it may not be prudent to cancel a session
after the first wrong entry. (Someone could fraudulently obtain a password by trying the
maximum of selection keys at each position.)

## Example Data Entry Session #3

                               (Data Entry with VMC Cancel)

| Controller | Cashless | Device | State |
|---|---|---|---|

| Previously | Enabled | Enabled |
|---|---|---|

## Poll                   

##         Data Entry Request +

                                DISPLAY REQUEST (prompt)

## Ack                    

                        User pushes Selection Key

## Data Entry             

RESPONSE (Key 1)

##         Ack

## Poll                   

|  | DISPLAY | REQUEST | (prompt | + *) |
|---|---|---|---|---|

## Ack                    

                        User walks away & VMC times out

## Data Entry             

RESPONSE (FF’s)
|  | ACK | (Enabled) |
|---|---|---|

## Poll                   

|  | DISPLAY | REQUEST | (“Try | Again”) |
|---|---|---|---|---|

## Ack                    

                         After Display Request Time expires,
                         VMC regains control of display

Section 8
  Communications Gateway
  VMC/Peripheral Communication Specifications

#### 8.1 Introduction

This section defines the communications bytes sent and received between a Communications
Gateway (Comms Gateway) and the VMC. The Comms Gateway address is 00011xxxB

## (18H).

Unless otherwise stated, all information is assumed to be in a binary format.

After the VMC has issued a command, the Comms Gateway must respond with a reply. The
reply may be an ACK or a detailed message response. If the command format expects a
response, the Comms Gateway may: 1) respond with an ACK, to acknowledge receiving the
command, and send the response later as a response to a POLL, or 2) immediately respond
with the expected message.

The Comms Gateway response to a command from the VMC may be an ACK, a single
message, or if there is more data to send it may be a multi message reply, up to the MDB
maximum of 36 bytes.

The following command / response set has been defined to provide a means to transfer
vending information system data from the VMC to the Comms Gateway in one of two ways;

1) Entire DTS files (including DXS, ST, SD1, G85, SE, and DXE records) are transferred
   using the file transport layer (FTL) of MDB.

2) Activity “Reports” are sent from the VMC to the Comms Gateway every time something
   happens in the vending system, it is then the Comms Gateways responsibility to store and
   assemble the DTS file. (DXS, ST, SD1, G85, SE and DXE data are not sent.) Obviously, a
   combination of these two methods can be designed to meet specific needs also.

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•1 |
|---|---|---|---|---|---|

#### 8.2 VMC Commands

| VMC Cmd | Code | VMC Data |  | Comm Gateway response |  |  |
|---|---|---|---|---|---|---|
| RESET | 18H |  |  | 00H - Just RESET |  | (1) |
| SETUP | 19H | Feature level | (1) | 01H - Comms Gateway Config | (1) |  |
|  |  | Scale factor | (1) | Feature level |  | (1) |
|  |  | Decimal places | (1) | Max. App. Resp. |  | (2) |
| POLL | 1AH |  |  | 00H - Just RESET |  | (1) |

                                                         01H - Comms Gateway Config (1)
|  | Feature level | (1) |
|---|---|---|
|  | Max. App. Resp. | (2) |
| 02H | - Request transmit | (1) |
| 03H | - Data transmitted | (1) |
| 04H | - Error | (1) |
|  | Error code | (n) |

                                                         05H - DTS Event Acknowledge (1)
| 06H | - Peripheral ID:             (1) |
|---|---|
|  | Mfg. code                  (3) |
|  | Serial number            (12) |
|  | Model number             (12) |
|  | Software ver.              (2) |
|  | Opt. features              (4) |
| 07H | - Radio Signal Strength      (2) |
| 1BH | - FTL REQ to RCV       (option) (1) |

                                                         1CH - FTL RETRY / DENY (option) (1)
                                                         1DH - FTL SEND BLOCK (option) (1)
| 1EH | - FTL | OK | to | SEND | (option) | (1) |
|---|---|---|---|---|---|---|

                                                         1FH - FTL REQ to SEND (option) (1)
|  |  |  |  | FFH | - Diagnostics | (n) |
|---|---|---|---|---|---|---|
| REPORT | 1BH | Type = 01, Transaction | (1) |  |  |  |
|  |  | Transaction Type | (1) |  |  |  |
|  |  | Selection (Row/Col.) | (2) |  |  |  |
|  |  | Price | (2) |  |  |  |
|  |  | Cash in, Coin tubes | (2) |  |  |  |
|  |  | Cash in, Cashbox | (2) |  |  |  |
|  |  | Cash in, Bills | (2) |  |  |  |
|  |  | Value in, Cashless #1 | (2) |  |  |  |
|  |  | Value in, Cashless #2 | (2) |  |  |  |
|  |  | Revalue to Cashless #1 | (2) |  |  |  |
|  |  | Revalue to Cashless #2 | (2) |  |  |  |
|  |  | Cash out | (2) |  |  |  |
|  |  | Discount Amount | (2) |  |  |  |
|  |  | Surcharge Amount | (2) |  |  |  |
|  |  | User Group # | (1) |  |  |  |
|  |  | Price List | (1) |  |  |  |
|  |  | Date | (4) |  |  |  |
|  |  | Time | (2) |  |  |  |

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•2 |
|---|---|---|---|---|---|

| Type = 02, DTS Event | (1) | 05-DTS | Event | Acknowledge | (1) |
|---|---|---|---|---|---|
| DTS Event Code | (10) |  |  |  |  |
| Date | (4) |  |  |  |  |
| Time | (2) |  |  |  |  |
| Duration | (4) |  |  |  |  |
| Activity | (1) |  |  |  |  |
| Terminal ID | (12) |  |  |  |  |
| Type = 03, Asset ID | (1) |  |  |  |  |
| Asset Type = 0n | (1) |  |  |  |  |
| Manufacture Code | (3) |  |  |  |  |
| Serial Number | (12) |  |  |  |  |
| Model Number | (12) |  |  |  |  |
| Software Version | (2) |  |  |  |  |

|  |  | Type = 03, Asset ID | (1) |  |
|---|---|---|---|---|
|  |  | Asset Type = 8n | (1) |  |
|  |  | Asset Number | (20) |  |
|  |  | Type = 04, Currency ID | (1) |  |
|  |  | VMC Currency Code | (2) |  |
|  |  | VMC Currency | (1) |  |
|  |  | VMC Decimal Point | (1) |  |
|  |  | Type = 05, Product ID | (1) |  |
|  |  | Product Identification | (20) |  |
|  |  | Selection Presence | (1) |  |
| CONTROL | 1CH | 00H - Disable | (1) |  |
|  |  | 01H - Enable | (1) |  |
|  |  | 02H - Transmit | (1) |  |
| EXPANSION | 1FH | 00H - Identification | 06H - Peripheral ID: | (1) |
|  |  |  | Mfg. code | (3) |
|  |  |  | Serial number | (12) |
|  |  |  | Model number | (12) |
|  |  |  | Software ver. | (2) |
|  |  |  | Opt. features | (4) |
|  |  | 01H - Feature enable | (1) |  |
|  |  | Features enabled | (4) |  |
|  |  | 02H – Time/Date Request | (1) 07H – CG Time/Date | (1) |
|  |  | Time/Date | (1)       Years | (1) |
|  |  |  | Months | (1) |
|  |  |  | Days | (1) |
|  |  |  | Hours | (1) |
|  |  |  | Minutes | (1) |
|  |  |  | Seconds | (1) |
|  |  |  | Day of Week | (1) |
|  |  |  | Summertime | (1) |
|  |  |  | Holiday | (1) |
|  |  | FAH - FTL   (option) | 1DH - SEND BLOCK |  |

## Req To Rcv                         1Ch - Retry / Deny

| FBH | - FTL | (option) | No | Data |
|---|---|---|---|---|

## Retry / Deny

| FCH | - FTL | (option) | No | Data |
|---|---|---|---|---|

## Send Block

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•3 |
|---|---|---|---|---|---|

| FDH | - FTL | (option) | 1DH | - SEND | BLOCK |
|---|---|---|---|---|---|

## Ok To Send

| FEH | - FTL | (option) | 1EH | - OK | TO | SEND |
|---|---|---|---|---|---|---|

## Req To Send                        1Ch - Retry/Deny

| FFH | - Diagnostics | (n) | FFH | - Diagnostics | (n) |
|---|---|---|---|---|---|

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•4 |
|---|---|---|---|---|---|

#### 8.3 Communications Gateway Command Format

| VMC | Command | Code/Sub-code | VMC | Data | Comms | Gateway | Response |
|---|---|---|---|---|---|---|---|

| RESET | 18H | No | data | None |
|---|---|---|---|---|

This command is the vehicle that the VMC should use to tell the Comms Gateway that it
should perform its initialization procedure. With the exception of the ACK response, it should
abort all communication and revert to the internally stored operational parameters.

The following initialization sequence is recommended. It should be used after “power up”, after
issuing the RESET command, or after issuing the Bus Reset (pulling the transmit line “active”
for a minimum of 100 mS).

## Poll – 18H

            To obtain “JUST RESET” response

## Setup – 19H

           To obtain Comms Gateway level and configuration information

## Expansion Identification – 1F 00H

           To obtain additional identification information and options

## Expansion Feature Enable – 1F 01H

           To enable desired options

## Control / Enable – 1Ch / 01H

           To enable / alert the Comms Gateway to start collecting data and / or monitoring
           for REPORT commands situations.

| VMC | Command | Code/Sub-code | VMC | Data | Comms | Gateway | Response |
|---|---|---|---|---|---|---|---|

## Setup               19H                  Y1 - Y3         Z1 - Z4

| Y1 = | VMC | feature | level |
|---|---|---|---|

             Indicates the highest Comms Gateway feature level that the VMC supports.
             Currently the highest feature level is 03, with no requirement to support previous
             (obsolete) levels 1 and 2.)

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•5 |
|---|---|---|---|---|---|

| Y2 | =          Scale | factor |
|---|---|---|

                           The multiplier used to scale all monetary values transferred
                           between the VMC and the Comms Gateway.

| Y3 | =          Decimal | places |
|---|---|---|

                           The number of decimal places used to communicate monetary
                           values between the VMC and the Comms Gateway.

## Z1 = 01      Comms Gateway Configuration

             The Comms Gateway is responding to a SETUP command. This response
             includes the following data;

| Z2 | =          Comms | Gateway | feature | level |
|---|---|---|---|---|

                           The feature level of the Comms Gateway. Currently the highest
                           feature level is 03, with no requirement to support previous
                           (obsolete) levels 1 and 2.)

| Z3 | - Z4 | =     Application | maximum | response | time |
|---|---|---|---|---|---|

                           The maximum length of time, in seconds, that an Comms Gateway
                           may be unable to respond to any commands. This includes the time
                           communicating over an external network. The VMC should
                           continue POLLing the Comms Gateway during this time in an
                           attempt to re-synchronize communications earlier. When the
                           Comms Gateway is ready to communicate over the bus again, it
                           should respond to the next POLL with COMPLETE (if
                           communicating externally) or ACK. This time essentially replaces
                           the standard MDB non-response time, as such it’s default value is
                           equal to the defined non-response time (5 seconds).

| VMC | Command | Code/Sub-code | VMC | Data | Comms | Gateway | Response |
|---|---|---|---|---|---|---|---|

| POLL | 1AH | No | data | Z1 | - Zn |
|---|---|---|---|---|---|

The POLL command is used by the VMC to obtain information from the Comms Gateway. This
information may include setup information, activity requests, or error conditions. An ACK
response indicates that no error states exist and either no information request is pending or
pending information is not yet ready for transmission.

In addition to an ACK, the VMC may receive the following POLL responses from the Comms
Gateway.

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•6 |
|---|---|---|---|---|---|

## Z1 = 00      Just Reset

             Indicates the Comms Gateway has been reset internally or on command from the
             VMC.

## Z1 = 01      Comms Gateway Configuration

             The Comms Gateway is responding to a SETUP command. This response
             includes the following data;

| Z2 | =          Comms | Gateway | feature | level |
|---|---|---|---|---|

                           The feature level of the Comms Gateway. Currently the highest
                           feature level is 03, with no requirement to support previous
                           (obsolete) levels 1 and 2.)

| Z3 | - Z4 | =     Application | maximum | response | time |
|---|---|---|---|---|---|

                           The maximum length of time, in seconds, that an Comms Gateway
                           may be unable to respond to any commands. This includes the time
                           communicating over an external network. The VMC should
                           continue POLLing the Comms Gateway during this time in an
                           attempt to re-synchronize communications earlier. When the
                           Comms Gateway is ready to communicate over the bus again, it
                           should respond to the next POLL with COMPLETE (if
                           communicating externally) or ACK. This time essentially replaces
                           the standard MDB non-response time, as such it’s default value is
                           equal to the defined non-response time (5 seconds).

## Z1 = 02      Request To Transmit

             The Comms Gateway is requesting permission to transmit data to an external
             collection device. This is done to control the bus power supply. The Comms
             Gateway should continue sending this response to each POLL until permission to
             transmit has been granted or the need to transmit goes away.

## Z1 = 03      Data Transmitted

             The Comms Gateway is finished transmitting to an external collect device.

## Z1 = 04      Error

             The Comms Gateway has developed some type of detectable error. The error
             codes will be sent continuously, or until the error is resolved.

| Z2 | – Zn | =     Error | code |
|---|---|---|---|

                           The error codes are ASCII strings taken from the EVA DTS
                           Communications fault list.

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•7 |
|---|---|---|---|---|---|

## Z1 = 05      Dts Event Acknowledge

             The Comms Gateway has recognized that a DTS Event has occurred and must
             act accordingly. The specific actions will be defined by the Comms Gateway
             operational specifications.

## Z1 = 06H     Peripheral Id

             Comms Gateway is sending peripheral ID information. This response includes
             the following data;

| Z2 | - Z4 | =     Manufacturer | code |
|---|---|---|---|

                           Identification code for the equipment supplier. Sent as ASCII
                           characters. Blanks (20H) are acceptable.

| Z5 | - Z16 | =    Serial | number |
|---|---|---|---|

                           Factory assigned serial number sent as numeric ASCII characters.
                           All bytes must be sent. Zeros (30H) and blanks (20H) are
                           acceptable.

             Z17 - Z28 = Model number ASCII.

                           Manufacturer assigned model number sent as ASCII characters. All
                           bytes must be sent. Zeros (30H) and blanks (20H) are acceptable.

             Z29 - Z30 = Software version

                           Current software version sent as packed BCD.

             Z31 - Z34 = Optional Features

                           Each of the 32 bits indicate an optional features availability. If the
                           bit is set the feature is available. Currently defined options are:

| b0: | File transport layer support |
|---|---|
| b1: | Verbose mode: See REPORT command |

                           b2 : Expansion Time/Date Request command
                           b3- b31: Future use, must be set to 0.

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•8 |
|---|---|---|---|---|---|

## Z1 = 07H     Radio Signal Strength

             The Comms Gateway is reporting its signal strength from the network. This
             response includes the following data;
| Z2 | =          Signal | Strength |
|---|---|---|

                           The level of radio signal strength detected by the Comms Gateway.
                           This is a binary number from 00H to 64H (100%) representing the
                           percentage of expected signal. This can be sent after every POLL,
                           or as needed due to changes in the signal.

Note that all FTL responses below are defined in Section 2.6. For the Comms Gateway, the
source address will always be the Comms Gateway (18H) as defined in Section 2.3.

| Z1 = | 1BH | REQ | TO | RCV | (File | Transport | Layer) |
|---|---|---|---|---|---|---|---|

             The Comms Gateway is requesting to receive data from a device or VMC.
                           Z2 = Destination address of response
                           Z3 = Source address of response (18H)
                           Z4 = File ID
                           Z5 = Maximum length
                           Z6 = Control

| Z1 = | 1CH | RETRY/DENY | (File | Transport | Layer) |
|---|---|---|---|---|---|

             The Comms Gateway is requesting a device or VMC to retry or deny the last FTL
             command.
                           Z2 = Destination address of response
                           Z3 = Source address of response (18H)
                           Z4 = Retry delay

| Z1 = | 1DH | SEND | BLOCK | (File | Transport | Layer) |
|---|---|---|---|---|---|---|

             The Comms Gateway is sending a block of data (maximum of 31 bytes) to a
             device or VMC.
                           Z2 = Destination address of data
                           Z3 = Block #
                           Z4-Z34 = Data (maximum of 31 bytes)

| Z1 = | 1EH | OK | TO | SEND | (File | Transport | Layer) |
|---|---|---|---|---|---|---|---|

             The Comms Gateway is indicating that it is OK for a device or VMC to send it
             data.
                       Z2 = Destination address of response
                       Z3 = Source address of response (18H)

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•9 |
|---|---|---|---|---|---|

| Z1 = | 1F | REQ | TO | SEND | (File | Transport | Layer) |
|---|---|---|---|---|---|---|---|

             The Comms Gateway is requesting to send data to a device or VMC.
                           Z2 = Destination address of response
                           Z3 = Source address of response (18H)
                           Z4 = File ID
                           Z5 = Maximum length
                           Z6 = Control

## Z1 = Ffh     Diagnostics

             The Comms Gateway is responding to a EXPANSION/DIAGNOSTICS
             command. This response includes the following data;

| Z2 | - Zn | User | defined | data |
|---|---|---|---|---|

                           Device manufacturer specific responses after receiving
                           manufacturing or test instructions. Z1 - Zn implies that any number
                           of bytes may be used for the response data from the Comms
                           Gateway.

| VMC | Command | Code/Sub-code | VMC | Data | Comms | Gateway | Response |
|---|---|---|---|---|---|---|---|

| REPORT | 1BH | Y1 | – Ynn | No | data |
|---|---|---|---|---|---|

The REPORT command is used by the VMC to pass activity information to the Comms
Gateway. If the “Verbose mode” is enabled via the EXPANSION / FEATURE ENABLE
command, this command must be sent immediately following the completion of any activity it is
describing. The activities may include; a transaction, a DTS defined event, an asset
identification, currency identification, or product identification.

The intent of this command is to provide information so that the Comms Gateway can create a
Data Transfer Standard file. All of the following fields show their corresponding DTS fields for
reference, for further detail refer to the Data Transfer Standard.

If the “Verbose mode” is disabled, only the “DTS Event” report type records must be sent. This
mode uses the FTL to transfer the complete DTS files and the DTS Event report types to alert
the VMC of any alarm conditions.

Since reports data may vary, any field that is not relevant, or not known, should be populated
with 00H’s. All cash values are scaled and decimal adjusted using the data provided in the
SETUP command.

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•10 |
|---|---|---|---|---|---|

| Y1 = | Type: | The | type | of | activity | that | is | being | reported, | includes | one | of | the | following: |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

| 01H | Transaction |
|---|---|
| 02H | DTS Event |
| 03H | Asset ID |
| 04H | Currency ID |
| 05H | Product ID |

If Y1 = 01H then the following “Transaction” data fields have been identified to be included:

| Y2 | =          Transaction | Type |
|---|---|---|

                     This field defines the type of transaction that the following data describes.
                     The defined transaction types include;

| 01H | Paid Vend |
|---|---|
| 02H | Token Vend |
| 03H | Free Vend |
| 04H | Test Vend |
| 05H | Revalue |
| 06H | Negative Vend |
| 07H | Vendless* |
| 08H | Manual / Service |

      - The end of a “Vendless” transaction is defined by the VMC manufacturer, for example
       an escrow request, a failed vend, etc.

| Y3 | – Y4 | =     Item | Number |
|---|---|---|---|

                     This is the binary field used to link REPORT type 01 to REPORT type 05.
                     It is an item number, 0000H through FFFFH of the selected product
                     involved in the most recent transaction. This number is defined by the
                     manufacturer.

| Y5 | – Y6 | =     Price | (PA102) |
|---|---|---|---|

                     The established price of the product involved in the most recent
                     transaction. The established price is the price before any adjustments i.e.
                     discounts surcharges, etc.

| Y7 | – Y8 | =     Cash | in, | Coin | Tubes | (CA303/CA307 | or | CA1001/CA1002) |
|---|---|---|---|---|---|---|---|---|

                     The value of cash deposited into the coin tubes since the completion of
                     the previous transaction.

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•11 |
|---|---|---|---|---|---|

| Y9 | – Y10 | =    Cash | in, | Cashbox | (CA302/CA306) |
|---|---|---|---|---|---|

                    The value of cash deposited into the cashbox since the completion of the
                    previous transaction.

| Y11 | – Y12 | = Cash | in, | Bills | (CA304/CA308) |
|---|---|---|---|---|---|

                    The value of cash deposited into the bill stacker since the completion of
                    the previous transactions.

| Y13 | – Y14 | = Value | in, | Cashless | Device | #1 | (DA201/DA203) |
|---|---|---|---|---|---|---|---|

                    The value removed from the media in cashless device #1 since the
                    completion of the previous transaction.

| Y15 | – Y16 | = Value | in, | Cashless | Device | #2 | (DB201/DB203) |
|---|---|---|---|---|---|---|---|

                    The value removed from the media in cashless device #2 since the
                    completion of the previous transaction.

| Y17 | – Y18 | = Revalue | to | Cashless | Device | #1 | (DA401/DA402) |
|---|---|---|---|---|---|---|---|

                    The value returned to the media in cashless device #1 since the
                    completion of the previous transaction.

| Y19 | – Y20 | = Revalue | to | Cashless | Device | #2 | (DB401/DB402) |
|---|---|---|---|---|---|---|---|

                    The value returned to the media in cashless device #2 since the
                    completion of the previous transaction.

| Y21 | – Y22 | = Cash | out | (CA401/CA403 | or | CA402/CA404) |
|---|---|---|---|---|---|---|

                    The total value of the cash dispensed from the system since the
                    completion of the previous transaction.

| Y23 | – Y24 | = Discount | Amount | (CA701/CA702) |
|---|---|---|---|---|

                    The value of any discounts awarded since the completion of the previous
                    vend.

| Y25 | – Y26 | = Surcharge | Amount | (CA705/CA706) |
|---|---|---|---|---|

                    The value of any surcharges collected since the completion of the
                    previous vend.

| Y27 | =         User | Group | #                                             (DA701 | or | DB701) |
|---|---|---|---|---|---|

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•12 |
|---|---|---|---|---|---|

                    The user group number that the transaction is associated with.

| Y28 | =         Price | List | (LA101) |
|---|---|---|---|

                    The price list that the transaction is associated with

| Y29 | – Y32 | = Date | (PA501) |
|---|---|---|---|

                    The date of the transaction. This data is sent as BCD in the following
                    sequence YYYY/MM/DD. For example, 17 March 2002 would be 20H 02H
                    03H 17H. If the date is not known these bytes are filled with 99Hs.

| Y33 | – Y34 | = Time | (PA502) |
|---|---|---|---|

                    The time of the transaction. This data is sent as BCD , 24 hour format, in
                    the following sequence HHMM. For example, 6:30 PM would be 18H 30H.
                    If the time is not known these bytes are filled with 99Hs.

If Y1 = 02H then the following “DTS Event” data fields have been identified to be included:

| Y2 | – Y11 | =    DTS | Event | Code | (EA101 | or | EA201 | or | EA701) |
|---|---|---|---|---|---|---|---|---|---|

                    This is an alpha-numeric ASCII code defining the event being reported.
                    The codes are list in the EVA DTS manual. In addition to the standard
                    DTS event codes, an interrogation event is reported as “EA3” and a power
                    outage event is reported as “EA7”.

| Y12 | – Y15 | = Date | (EA102) |
|---|---|---|---|

                    The date of the event. This data is sent as BCD in the following sequence
                    YYYY/MM/DD. For example, 17 March 2002 would be 20H 02H 03H 17H.
                    If the date is not known these bytes are filled with 99Hs.

| Y16 | – Y17 | = Time | (EA103) |
|---|---|---|---|

                    The time of the event. This data is sent as BCD in the following sequence
                    HH/MM. For example, 6:30 PM would be 18H 30H. If the time is not
                    known these bytes are filled with 99Hs.

| Y18 | – Y21 | = Duration | (EA206) |
|---|---|---|---|

                    The duration of the event in total minutes. This data is sent as binary. For
                    example, 4 hours and 15 minutes would be 00H 00H 00H FFH.

| Y22 | =         Activity | (EA205) |
|---|---|---|

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•13 |
|---|---|---|---|---|---|

                    The current status of the events activity. This field is equal to 00H if the
                    event is inactive (or not reset for “EA3”) or 01H if the event is active (or
                    reset for “EA3”).

## Z1 = 05      Dts Event Acknowledge

             The Comms Gateway has recognized that a possible alarm situation has
             occurred and must act accordingly. The specific actions will be defined by the
             Comms Gateway operational specifications.

If Y1 = 03H then the following “Asset ID” data fields have been identified to be included:

| Y2 | =          Asset | Type |
|---|---|---|

                    The following code pairs have been defined to represent the type of
                    equipment asset that is being communicated.

| Code | Equipment | type | DTS |
|---|---|---|---|

                                                                                       header
                                                                                         (αα)
| 01H | / 81H | Audit Module / Data Carrier (DC) | Identification | AM1 |
|---|---|---|---|---|
| 02H | / 82H | Bill Validator Identification |  | BA1 |
| 03H | / 83H | Changer Identification |  | CA1 |
| 04H | / 84H | Control Board Identification |  | CB1 |
| 05H | / 85H | Cashless #1 Identification |  | DA1 |
| 06H | / 86H | Cashless #2 Identification |  | DB1 |
| 07H | / 87H | Machine Identification |  | ID1 |

             If Y2 has the MSB = 0 (i.e. Y2 = 01H) then the following asset data fields have
             been identified to be included:

| Y3 | – Y5 | =     Manufacturer | code | (αα101, | first | 3 characters) |
|---|---|---|---|---|---|---|

                                  Identification code for the equipment supplier. Sent as ASCII
                                  characters. Blanks (20H) are acceptable.

| Y6 | - Y17 | =    Serial | number | (αα101, | 4th | through | 15th | characters) |
|---|---|---|---|---|---|---|---|---|

                                  Factory assigned serial number sent as numeric ASCII
                                  characters. All bytes must be sent. Zeros (30H) and blanks
                                  (20H) are acceptable.

| Y18 | - Y29 | = Model | number | (αα102) |
|---|---|---|---|---|

                                  Manufacturer assigned model number sent as ASCII
                                  characters. All bytes must be sent. Zeros (30H) and blanks
                                  (20H) are acceptable.

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•14 |
|---|---|---|---|---|---|

| Y30 | - Y31 | = Software | version | (or | Build | Standard) | (αα103) |
|---|---|---|---|---|---|---|---|

                                  Current software version sent as packed BCD.

             If Y2 has the MSB = 1 (i.e. Y2 = 81H) then the following asset data fields have
             been identified to be included:

| Y2 | – Y21 | =    Asset | Number | (αα105 | or | αα106) |
|---|---|---|---|---|---|---|

                                  The asset number of the equipment. This is a reference
                                  number used for tracking purposes, separate from the serial
                                  number. It is usually programmed by the equipment
                                  operator.

If Y1 = 04H then the following “Currency ID” data fields have been identified to be included:

| Y2 | – Y3 | =     VMC’s | Country | / Currency | Code | (ID402) |
|---|---|---|---|---|---|---|

                    The packed BCD Country / Currency code of the VMC can be sent in two
                    different forms depending on the value of the left most BCD digit.

                    If the left most digit is a 0, the International Telephone Code is used to
                    indicate the country that the changer is set-up for. For example, the USA
                    code is 00 01H (Z2 = 00 and Z3 = 01).

                    If the left most digit is a 1, the latest version of the ISO 4217 numeric
                    currency code is used. For example, the code for the US dollar is 18 40H
                    (Z2 = 18 and Z3 = 40) and for the Euro is 1978 (Z2 = 19 and Z3 = 78).

                    All new designs after July, 2000 must use the ISO 4217 numeric currency
                    codes.

| Y4 | =          VMC’s | Coin | Scaling | Factor | / Currency | Description | (ID403) |
|---|---|---|---|---|---|---|---|

                    The multiplier used to scale all monetary values transferred between the
                    VMC and the vending machines monetary system.

| Y5 | =          VMC’s | Decimal | Point | (ID401) |
|---|---|---|---|---|

                    The number of digits to the right of the decimal point. This field is used in
                    countries whose currency requires a number of digits to the right of the
                    decimal point other than 2.

If Y1 = 05H then the following “Product ID” data fields have been identified to be included:

| Y2 | – Y3 | =     Item | Number |
|---|---|---|---|

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•15 |
|---|---|---|---|---|---|

                    This is the binary field used to link REPORT type 01 to REPORT type 05.
                    This number is defined by the manufacturer.

| Y4 | – Y9 | =     Product | Number | (PA101) |
|---|---|---|---|---|

                    This is the ASCII representation of the Item Number that should be
                    included in the DTS file. All bytes must be sent, leading blanks (20H) are
                    acceptable.

| Y10 | – Y29 | = Product | Identification | (PA103) |
|---|---|---|---|---|

                    The ASCII product identification that should identify the product itself, as in
                    a name (chips/crisps) or an ID number / bar code. All bytes must be sent,
                    leading blanks (20H) are acceptable.

| Y30 | =         Selection | Presence | Status | (PA107) |
|---|---|---|---|---|

                    This field is set to 00H if a vend mechanism (motor, solenoid, etc.) is
                    present for this selection. This field is set to 01H if a vend mechanism is
                    not present.

                    An example of a 01H being sent would be if the vend mechanism was
                    present previously, and something occurred so that it is not being currently
                    detected (i.e., removed, broken wire, etc.). It is not intended to indicate
                    that a product is not available for vending (i.e., sold out).

| VMC | Command | Code/Sub-code | VMC | Data | Comms | Gateway | Response |
|---|---|---|---|---|---|---|---|

| CONTROL | 1CH | Y1 | No | data |
|---|---|---|---|---|

This command is the vehicle that the VMC uses to control the Comms Gateway’s use of an
external collection device. For example when it should, or should not, transmit through the
external collection device. The information is identified by one of the following subcommands;

| Y1 = | 00 | Disabled |
|---|---|---|

              No external transmissions will be granted and no REPORT commands will be
              sent.

| Y1 = | 01 | Enabled |
|---|---|---|

              External transmissions may be requested and REPORT commands will be sent.

| Y1 = | 02 | Transmit |
|---|---|---|

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•16 |
|---|---|---|---|---|---|

             Permission to transmit and / or receive data is granted, or a transmission session
             is requested. A DATA TRANSMITTED response to a POLL must be sent when
             the transmission session is complete.

| VMC | Command | Code/Sub-code | VMC | Data | Comms | Gateway | Response |
|---|---|---|---|---|---|---|---|

## Expansion/          1Fh/00H              Y1              Z1 - Z34

## Identification

| Y1 = | 00H | IDENTIFICATION | subcommand |
|---|---|---|---|

The VMC is requesting Comms Gateway identification information for asset tracking and
optional feature purposes.

## Z1 = 06H     Peripheral Id

             Comms Gateway is sending peripheral ID information. This response includes
             the following data;

| Z2 | - Z4 | =     Manufacturer | code |
|---|---|---|---|

                           Identification code for the equipment supplier. Sent as ASCII
                           characters. Blanks (20H) are acceptable.

| Z5 | - Z16 | =    Serial | number |
|---|---|---|---|

                           Factory assigned serial number sent as numeric ASCII characters.
                           All bytes must be sent. Zeros (30H) and blanks (20H) are
                           acceptable.

             Z17 - Z28 = Model number ASCII.

                           Manufacturer assigned model number sent as ASCII characters. All
                           bytes must be sent. Zeros (30H) and blanks (20H) are acceptable.

             Z29 - Z30 = Software version

                           Current software version sent as packed BCD.

             Z31 - Z34 = Optional Features

                           Each of the 32 bits indicate an optional features availability. If the
                           bit is set the feature is available. Currently defined options include:

| b0: |  | File transport layer support. |
|---|---|---|
| b1: |  | Verbose mode: See REPORT command |
| b2 - | b31: | Future use, must be set to 0. |

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•17 |
|---|---|---|---|---|---|

| VMC | Command | Code/Sub-code | VMC | Data | Comms | Gateway | Response |
|---|---|---|---|---|---|---|---|

| EXPANSION/ | 1FH/01H | Y1 | - Y5 | No | data |
|---|---|---|---|---|---|

## Feature Enable

| Y1 = | 01H | FEATURE | ENABLE | subcommand |
|---|---|---|---|---|

This command is used to enable each of the optional features defined in Z32-Z35 of the
PERIPHERAL ID response. The VMC should send the EXPANSION /IDENTIFICATION
command, receive the PERIPHERAL ID response, perform a logical OR with the optional
features it wants to enable, and return the resulting enabled features back to the Comms
Gateway by setting a bit to 1 for each respective optional feature enabled. All optional features
are disabled after reset.

| Y2 | - Y5 | =     Optional | features | enabled |
|---|---|---|---|---|

      Each of the 32 bits indicates an optional features state. If the bit is set the feature is
      enabled.

| VMC | Command | Code/Sub-code | VMC | Data | Comms | Gateway | Response |
|---|---|---|---|---|---|---|---|

## Expansion/     1Fh/02H                    Y1               Z1-Z11

## Time/Date Request

| Y1 = | 01H | TIME/DATE | subcommand |
|---|---|---|---|

Normally the Comms Gateway is a networked device, and therefore capable of asking the
actual time from a server if required. This command is used to synchronize the VMC’s real
time clock from the Comms Gateway.

To be able to use the command it must be enabled via the EXPANSION / FEATURE ENABLE
command.

| Z1 = | 01H | CG | Time/Date |
|---|---|---|---|

      The date bytes are BCD encoded
      Z2 = Years (Range: 00..99)
      Z3 = Months (Range: 01..12)
      Z4 = Days (Range: 01..31)
      Z5 = Hours (Range: 00..23)
      Z6 = Minutes (Range: 00..59)
      Z7 = Seconds (Range: 00..59)
      Z8 = Day of Week (Range: 01..07, Monday = 1..Sunday = 7)

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•18 |
|---|---|---|---|---|---|

      Z9 = Week Number (Range: 01..53)
      Z10 = Summertime (Range: 00..01, Summertime = 1)
      Z11 = Holiday (Range: 00..01, Holiday = 1)

      If any item of the time/date is not supported use FFH instead

| VMC | Command | Code/Sub-code | VMC | Data | Comms | Gateway | Response |
|---|---|---|---|---|---|---|---|

| EXPANSION | 0FH | FAH | Y1-Y5 | Z1 | - Zn | (immediate | or | POLLed) |
|---|---|---|---|---|---|---|---|---|

## Command             Ftl Req To Rcv

The VMC is requesting to receive data from the Comms Gateway whose destination address
will always be (18H). Note that all FTL Commands / Responses are defined in Section 2.6.

| Y1 | = | Destination address of command | (18H) |
|---|---|---|---|
| Y2 | = | Source address of command |  |
| Y3 | = | File ID |  |
| Y4 | = | Maximum length |  |
| Y5 | = | Control |  |

| Z1 | = | 1DH which indicates | SEND BLOCK |
|---|---|---|---|
| Z2 | = | Destination address | of data |
| Z3 | = | Block # |  |
| Z4 | - Z34 | =    Data (maximum of 31 | bytes) |

                                 or
| Z1 | =          1CH which indicates RETRY / DENY |
|---|---|
| Z2 | =          Destination address of response |
| Z3 | =          Source address of response (18H) |
| Z4 | =          Retry delay |

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•19 |
|---|---|---|---|---|---|

| VMC | Command | Code/Sub-code | VMC | Data | Comms | Gateway | Response |
|---|---|---|---|---|---|---|---|

| EXPANSION | 0FH | FBH | Y1-Y3 | None |
|---|---|---|---|---|

## Command             Ftl Retry / Deny

The VMC is retrying, denying, or aborting a data transfer to/from the Comms Gateway whose
destination address will always be (18H). Note that all FTL Commands / Responses are
defined in Section 2.6.

| Y1 | =          Destination address of command | (18H) |
|---|---|---|
| Y2 | =          Source address of command |  |
| Y3 | =          Retry delay |  |

| VMC | Command | Code/Sub-code | VMC | Data | Comms | Gateway | Response |
|---|---|---|---|---|---|---|---|

| EXPANSION | 0FH | FCH | Y1-Y33 | None |
|---|---|---|---|---|

## Command             Ftl Send Block

The VMC is sending data to the Comms Gateway whose destination address will always be
(18H). Note that all FTL Commands / Responses are defined in Section 2.6.

| Y1 | =       Destination | address | of | command | & data | (18H) |
|---|---|---|---|---|---|---|
| Y2 | =       Block # |  |  |  |  |  |

      Y3 - Y33 = Data (maximum of 31 bytes)

| VMC | Command | Code/Sub-code | VMC | Data | Comms | Gateway | Response |
|---|---|---|---|---|---|---|---|

| EXPANSION | 0FH | FDH | Y1-Y2 | Z1-Z34 | (immediate | or | POLLed) |
|---|---|---|---|---|---|---|---|

## Command             Ftl Ok To Send

The VMC is indicating that it is OK for the Comms Gateway to transfer data. The destination
address will always be the Comms Gateway (18H). Note that all FTL Commands / Responses
are defined in Section 2.6.

| Y1 | =          Destination address of command | (18H) |
|---|---|---|
| Y2 | =          Source address of command |  |

| Z1 | = | 1DH which indicates SEND BLOCK |
|---|---|---|
| Z2 | = | Destination address of data |
| Z3 | = | Source address of data |
| Z4 | - Z34 | =    Data (maximum of 31 bytes) |

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•20 |
|---|---|---|---|---|---|

| VMC | Command | Code/Sub-code | VMC | Data | Comms | Gateway | Response |
|---|---|---|---|---|---|---|---|

| EXPANSION | 0FH | FEH | Y1-Y5 | Z1 | - Zn | (immediate | or | POLLed) |
|---|---|---|---|---|---|---|---|---|

## Command               Ftl Req To Send

The VMC is requesting to send data to the Comms Gateway whose destination address will
always be (18H). Note that all FTL Commands / Responses are defined in Section 2.6.

| Y1 | = | Destination address of command | (18H) |
|---|---|---|---|
| Y2 | = | Source address of command |  |
| Y3 | = | File ID |  |
| Y4 | = | Maximum length |  |
| Y5 | = | Control |  |

| Z1 | =            1EH which indicates OK TO SEND |
|---|---|
| Z2 | =            Destination address of response |
| Z3 | =            Source address of response (18H) |

                                   or
| Z1 | = | 1CH which indicates RETRY / DENY |
|---|---|---|
| Z2 | = | Destination address of response |
| Z3 | = | Source address of response (18H) |
| Z4 | = | Retry delay |

| VMC | Command | Code/Sub-code | VMC | Data | Comms | Gateway | Response |
|---|---|---|---|---|---|---|---|

| EXPANSION/ | 1FH/FFH | Y1 | - Yn | Z1 | - Zn |
|---|---|---|---|---|---|

## Diagnostics

| Y1 = | FFH | DIAGNOSTICS | subcommand |
|---|---|---|---|

                Device manufacturer specific instruction for implementing various manufacturing
                or test modes.

| Y2 - | Yn | =       User | defined | data |
|---|---|---|---|---|

                The data portion of this command is defined by the manufacturer and is not part
                of this document.

## Z1 = Ffh        Diagnostics

                The Comms Gateway is responding to a EXPANSION/DIAGNOSTICS
                command. This response includes the following data;

| Z2 | - Zn | =    User | defined | data |
|---|---|---|---|---|

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•21 |
|---|---|---|---|---|---|

                           Device manufacturer specific responses after receiving
                           manufacturing or test instructions. Z1 - Zn implies that any number
                           of bytes may be used for the response data from the Comms
                           Gateway.

#### 8.4 Communications Gateway Non-Response Time

The maximum non-response time for a Comms Gateway is 5 seconds. This is the maximum
time for which a Comms Gateway will not respond to a command with ACK, NAK, or a data
message.

#### 8.5 Communications Gateway Power Requirements

The current draw for any Comms Gateway must fall within the following limits. All
measurements are at the minimum VMC Voltage Output.

| Idle | mode | = | 300 | mA. | (avg.) | continuous |
|---|---|---|---|---|---|---|

| Active | mode | =       1.8 | A continuous | and | up | to | 2.5 | A (max) | for | an | accumulated | maximum | of |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                    10 seconds. The active power mode must be initiated by the REQUEST
                    TO TRANSMIT followed by the CONTROL/TRANSMIT. The active power
                    mode must be closed by sending the DATA TRANSMITTED. During this
                    time the VMC will make its own decisions about which other peripherals
                    will be disabled or not. This may result in the entire machine being
                    disabled for normal vending.

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•22 |
|---|---|---|---|---|---|

#### 8.6 Communications Gateway Examples

|  | Event |  | Exchange |
|---|---|---|---|
| Power on Reset | at VMC or JUST RESET | received by VMC | Reset sequence |
| any other time |  |  | Enable sequence |
| Communications | Gateway is triggered | to send a file | Request sequence |

                                                            Transmit sequence
| VMC | is | triggered | to | send | a file | Dump | sequence |
|---|---|---|---|---|---|---|---|

                                                            Transmit sequence
| DTS | Event | situation | occurs | at | VMC | DTS | Event | sequence |
|---|---|---|---|---|---|---|---|---|

                                                            Request sequence
                                                            Transmit sequence
| Error | situation is detected | at | Comms | Gateway | Error sequence |
|---|---|---|---|---|---|
| Every | vend completion |  |  |  | Vend sequence |

Reset sequence
| VMC |  |  | Comms | Gateway | Comments |
|---|---|---|---|---|---|
| RESET | (18) |  |  |  | Reset command |

##       Ack

| POLL (1A) |  |  | Must be sent once |
|---|---|---|---|
|  |  | JUST RESET (00) | reset, internal or |
| ACK |  |  | external |
| SETUP (19…) |  |  | Establish operation |
|  |  | CONFIG. (01…) | configuration |

## Ack                        

| EXPANSION/ID |  | Send | asset | information |
|---|---|---|---|---|

## (1F/00…)

|  | PERIPHERAL | ID | (06…) | Get | asset | information |
|---|---|---|---|---|---|---|

## Ack                        

| EXPANSION/FEATURE |  | Enable additional | feature | if |
|---|---|---|---|---|
| ENABLE (1F/01…) |  | necessary |  |  |

##       Ack

Enable sequence
| VMC |  | Comms | Gateway | Comments |
|---|---|---|---|---|
| CONTROL/ENABLE |  |  |  | Enable command |

## (1C01)

##       Ack

Disable sequence
| VMC |  | Comms | Gateway | Comments |
|---|---|---|---|---|
| CONTROL/DISABLE |  |  |  | Disable command |

## (1C00)

##       Ack

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•23 |
|---|---|---|---|---|---|

Request sequence
| VMC | Comms | Gateway | Comments |
|---|---|---|---|

| File | transfer | done | using | the | MDB | file | transport | layer |
|---|---|---|---|---|---|---|---|---|

Dump sequence
| VMC | Comms | Gateway | Comments |
|---|---|---|---|

| File | transfer | done | using | the | MDB | file | transport | layer |
|---|---|---|---|---|---|---|---|---|

Transmit sequence
| VMC | Comms | Gateway | Comments |
|---|---|---|---|

## Poll (1A)                  

|  | Request | to | transmit | (02) |
|---|---|---|---|---|

## Ack                        

## Control/ Transmit          

## (1C/02)

##     Ack

## Poll (1A)

                                ACK
| . | Continue | POLLing | until |
|---|---|---|---|

                                .

## Poll (1A)                  

|  | Data | transmitted | (03) |
|---|---|---|---|

## Ack                        

DTS Event sequence
| VMC | Comms | Gateway | Comments |
|---|---|---|---|

## Report (1B / 02…)          

##     Ack

| . | Repeat | until | recognized |
|---|---|---|---|

                                .

## Report (1B /02…)           

##     Dts Event

## Acknowledge (05)

Error sequence
| VMC |  |  | Comms | Gateway | Comments |  |
|---|---|---|---|---|---|---|
| POLL | (1A) |  |  |  | Sent continuously, or | until |
|  |  |  | ERROR | (06) | the error is resolved |  |

## Ack                        

Activity sequence
| VMC |  |  | Comms | Gateway | Comments |  |
|---|---|---|---|---|---|---|
| REPORT | (1B…) |  |  |  | Sent every | activity |

##     Ack

| MDB/ICB | Version | 4.2 | February, | 2011 | 8•24 |
|---|---|---|---|---|---|

Section 9
  Universal Satellite Device (USD)
  VMC/Peripheral Communication Specifications

#### 9.1 Introduction

      An MDB Universal Satellite Device (USD) is a vending device which lacks
      customary credit acceptance peripherals. As such, a USD must rely on a
      host vending machine controller (VMC) to establish credit sufficient to
      perform a vend. The specification herein describes a protocol by which a
      USD and a VMC exchange messages and credit via the MDB bus.

#### 9.1.1 Definitions

      This section defines the non-response and application response time, base
      addresses, and the communication bytes sent by the MDB Universal Satellite
      Device (USD) and a Vending Machine Controller.

      - The default maximum non-response time of the USD is 5 seconds.
      - The default maximum application response time of the USD is 5 seconds.
      - Three consecutive USD base addresses are defined to allow multiple
          USDs to operate simultaneously from a single VMC
      - As defined in Section 2.3, the USD Base addresses are as follows:
          01000xxxB (40H), 01001xxxB (48H), and 01010xxxB (50H).
      - The specification defined herein assumes a USD base address of 40H in
          all examples. It should be understood that differing USD base addresses
          (48H and 50H) will follow the same command format.
      - Multi-message responses to a single command are supported. Message
          length is subject to the 36 byte limit imposed by the MDB standard.
      - Unless stated otherwise, all byte information contained herein is assumed
          to be in a binary format.
      - Yn represents bytes transmitted by the VMC, and Zn are bytes transmitted
          by the USD.
      - When words are referenced, they consist of two bytes with the higher
          order byte first.
|  |  | High |  |  | Low |  |
|---|---|---|---|---|---|---|
| word | =       b15 | ... | b8 | b7 | ... | b0 |

#### 9.2 USD Summary

        This section is a summary of the USD command set and an overview of the
        modes of operation.

#### 9.2.1 Command Summary

| Command | Hex | Description |
|---|---|---|

                             Code
| RESET | 40 | Command | for USD to self-reset. |
|---|---|---|---|
| SETUP | 41 | Command | to configure USD to VMC requirements. |
| POLL | 42 | Command | to request for USD activity status. |
| VEND | 43 | Command | for vend approve / deny. |
| FUNDS | 44 | Command | to send funds available or to set prices. |
| CONTROL | 45 | Command | to enable/disable USD. |
| EXPANSION | 47 | Command | to allow addition of features and |

                                        enhancements.

#### 9.2.2 Overview

        The USD Command set described herein allows USDs’ to be controlled
        under the following three modes of operation. The USD’s mode of operation
        is determined by the USD’s configuration byte1 and the sequence of
        commands the VMC uses.

| Mode | One | VMC | is | used | to | select | items | to | be | vended | from | the | USD | and |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                         the VMC contains all pricing information. The USD receives
                         vend requests from the VMC and reports vend success or
                         failure.
| Mode | Two | The | USD | or | the | VMC | may | select | items | to | be | vended. | The |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                         USD may have special requirements for price and/or selection
                         ID display. In this case, the USD may issue a FUNDS request
                         to retrieve this information. The USD must then issue a VEND
                         request to gain approval from the VMC before a vend can take
                         place.
| Mode | Three | The | USD | selects | items | to | be | vended | and | has | its | own | pricing |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                         information. The USD must issue an vend request to the VMC
                         and gain approval before a vend can take place.

1
  Configuration byte refers to byte Z31 of the sequence Z31 through Z34 of the expansion 07
command. Please refer to page 9.12 for more information on how this byte influences the USD’s
mode of operation.

#### 9.3 Command Protocol

      This section contains the complete command set relating to the USD.

#### 9.3.1 RESET

| Command | Code | VMC Data | USD | Response | data |
|---|---|---|---|---|---|
| RESET | 40 | No data bytes. | ACK |  |  |

      The RESET command is the vehicle that the VMC should use to instruct the
      USD to return to its default (power on) operating mode. The USD should
      respond to a reset command with an ACK to acknowledge receipt of the reset
      command. The USD must not accept any vend requests until the VMC
      issued setup command sequence has been completed.
      The USD must also respond to the VMC issued “master reset” which resets
      all MDB peripheral devices. The VMC causes a master reset by transmitting
      a continuous break condition for a minimum of 100 milliseconds.
      To ensure proper initialization, the USD should issue a “just reset” (see POLL
      response 00) whenever it’s pricing or configuration has changed.

#### 9.3.2 SETUP

| Command | Code | VMC Data |  | USD Response Data |  |
|---|---|---|---|---|---|
| SETUP | 41 | 5 bytes: | Y1-Y5 | 7 bytes: 04 + Z1 - | Z6 |

      The SETUP command is the vehicle that the VMC should use to configure
      the USD for feature level, credit scaling factor, display decimal place, and
      maximum vend approve/deny time. The USD responds to this command by
      returning it’s feature level, highest vend price (divided by the scaling factor),
      selection configuration, and maximum application response time.
      Alternatively, if the USD is not prepared to render a full response to the
      SETUP command, it may reply with an ACK. If this occurs, the USD must
      transmit it’s setup data later, in response to a POLL command (see POLL
      command, response 04). Until the SETUP command has been received by
      the USD, and the USD has correspondingly returned it’s own setup data to
      the VMC, all vend requests will be disallowed.

      Data sequence transmitted by the VMC to the USD during SETUP
| VMC | Data | Meaning | or | interpretation |
|---|---|---|---|---|

| Y1 | =                VMC | Feature | level, | Indicates | current | feature | level | of | the | VMC. |
|---|---|---|---|---|---|---|---|---|---|---|

                             Currently defined level is one.2
| Y2 | - Y3 | =           Scaling | factor | 2 bytes | (word). | All | transactions | with | the | USD |
|---|---|---|---|---|---|---|---|---|---|---|

                             must be evenly divisible by this number.
| Y4 | =                Decimal | place | (02=US). | Indicates | the | position | of | the | decimal |
|---|---|---|---|---|---|---|---|---|---|

                             place on the USD’s optional credit display
| Y5 | =                VMC | maximum | approve | / deny | time | in | seconds, | FF | = 255 |
|---|---|---|---|---|---|---|---|---|---|

                             seconds.

        Data sequence transmitted by the USD to the VMC during SETUP
| USD | Meaning | or | interpretation |
|---|---|---|---|

         Response
| 04 | + Z1 | =           USD | Feature | level, | indicates | current | feature | level | of | the | USD. |
|---|---|---|---|---|---|---|---|---|---|---|---|

                                                             3
                             Currently defined level is one.
| Z2 | - Z3 | =           Maximum | price | on | USD | in | 2 bytes | (word). | Indicates | the |
|---|---|---|---|---|---|---|---|---|---|---|

                                                               4
                             highest priced item on the USD. USD should return FF `FFh` if
                             it does not have internal pricing capability.
| Z4 | - Z5 | =           Item | number, | defined | by | the | manufacturer | configuration |
|---|---|---|---|---|---|---|---|---|

                             (Binary).
| Z6 | =                USD | maximum | application | response | time | in | seconds, | FF |
|---|---|---|---|---|---|---|---|---|

                             255 seconds.

2
  Feature level of the VMC is sent to allow the USD to arbitrate command compatibility with the VMC.
3
  Feature level of the USD is sent to allow the VMC to arbitrate command compatibility with the USD.
The USD may opt to send this data later in response to a POLL.
4
  The maximum price on the USD is returned to the VMC so this price can be used in the computation
of maximum credit acceptance.

#### 9.3.3 POLL

| Command | Code | USD | response | USD | Response | Description |
|---|---|---|---|---|---|---|

                                       Data
| POLL | 42 | 00 | USD | has | just | been | reset, | or |
|---|---|---|---|---|---|---|---|---|

                                                     wishes to be reset by the VMC.
| 01 | + 4 | bytes | Z1- | Z4 | Vend | request, | USD | requests |
|---|---|---|---|---|---|---|---|---|

                                                     approval to vend a specified item
                                                     from VMC.
| 02 | Vend | or | home | success, | requested |
|---|---|---|---|---|---|

                                                     vend or home was successful.
| 03 | + 4 | bytes | Z1 | - Z4 | Vend | or | home | fail, | requested | vend |
|---|---|---|---|---|---|---|---|---|---|---|

                                                     or home has failed. Reason for
                                                     failure is returned.
| 04 | + 6 bytes Z1 - Z6 | USD | configuration and setup | data. |
|---|---|---|---|---|
| 05 | + 2 bytes Z1 - Z2 | USD | item price request. |  |
| 06 | + 2 bytes Z1 - Z2 | USD | Error codes. |  |
| 07 | + 34 bytes Z1 - | USD | Peripheral ID string. |  |

                              Z34
| 08 | + 4 | bytes | Z1 | - Z4 | USD | Status response. |  |
|---|---|---|---|---|---|---|---|
| 09 | + n | bytes | Z1 | - Zn | USD | multiple data block | transfer |

                                                     response.
| 0A | + n bytes | Z1 | - Zn | USD | single data block response |
|---|---|---|---|---|---|
| 1B | + 5 bytes | Z2 | - Z6 | FTL | REQ TO RCV response |
| 1C | + 3 bytes | Z2 | - Z4 | FTL | RETRY / DENY response |
| 1D | + n bytes | Z2 | - Zn | FTL | SEND BLOCK response |
| 1E | + 2 bytes | Z2 | - Z3 | FTL | OK TO SEND response |
| 1F | + 5 bytes | Z2 | - Z6 | FTL | REQ TO SEND response |
| FF | + Z1 - Zn |  |  | USD | Diagnostic response. |

      The POLL command is used by the VMC to obtain status information from
      the USD. The same command is used by the USD to indicate a reset,
      request a vend, indicate vend success, indicate the reason for a vend failure,
      request the price of an item, send configuration and/or error data, return the
      USD’s peripheral identification string, control the transmission and reception
      of data blocks, return a status and/or diagnostic response.
      The USD responds to the POLL command with either an ACK, or a multi-byte
      response if there is more information to convey.

      Data sequence transmitted by the USD to the VMC after a Reset Request
| USD | Meaning | or | interpretation |
|---|---|---|---|

          Response
| 00 | The | 00 | response | indicates | that | the | USD | has | just | been | reset |
|---|---|---|---|---|---|---|---|---|---|---|---|

                            or wishes to be reset5.

      Data sequence transmitted by the USD to the VMC for a Vend Request
| USD | Meaning | or | interpretation |
|---|---|---|---|

          Response
| 01 | + Z1- | Z2 | =     Selection | in | 2 bytes. | Indicates | the | product | to | be | vended | by |
|---|---|---|---|---|---|---|---|---|---|---|---|---|

                            item number, defined by the manufacturer, as part of a vend
                            request.
| Z3 | - Z4 | =         Scaled | product | price | in | 2 bytes | (word). | Indicates | the | price | of |
|---|---|---|---|---|---|---|---|---|---|---|---|

                            the product to be vended divided by the scaling factor. A price
                            of FFFF is transmitted if the USD does not contain price
                            information.

      Data sequence transmitted by the USD to the VMC after a Vend or Home
      success
| USD | Meaning | or | interpretation |
|---|---|---|---|

          Response
| 02 | Indicates | that | the | requested | vend | or | home | was | successful. |
|---|---|---|---|---|---|---|---|---|---|

      Data sequence transmitted by the USD to the VMC after a Vend or Home
      Fail
| USD | Meaning | or | interpretation |
|---|---|---|---|

          Response
| 03 | + Z1 | - Z2 | =    USD item | number, defined by the | manufacturer. |
|---|---|---|---|---|---|
| Z3 | - Z4 | = | Bits: b0 | = Selection sold out. |  |

                                  b1 = Selection motor / actuator jam.
                                  b2 = Non-existent motor / actuator.
                                  b3 = Invalid selection range6.
                                  b4 = Health safety error.
                                  b5 - b15 = Not defined.

      5
       The VMC is expected to reconcile whether the USD is transmitting a 00 in confirmation of a
      VMC issued reset that has just occurred, or as an unsolicited request to be reset. The
      context of the VMC’s prior communication activity should be used in making this assessment.

      Data sequence transmitted by the USD to the VMC if SETUP response
      delayed
| USD | Meaning | or | interpretation |
|---|---|---|---|

          Response
| 04 | + Z1 | =           USD | Feature | level, | Indicates | current | feature | level | of | the | USD. |
|---|---|---|---|---|---|---|---|---|---|---|---|

                                                                  7
                              The currently defined level is one.
| Z2 | - Z3 | =           Maximum | price | on | USD | 2 bytes | (word). | Indicates | the | highest |
|---|---|---|---|---|---|---|---|---|---|---|

                              priced item on the USD.8 USD should return FF `FFh` if it does
                              not have internal pricing capability.
| Z4 | - Z5 | =           Item number, defined by | the manufacturer. |  |
|---|---|---|---|---|
| Z6 | = | USD maximum application | response time in seconds, | FF |

                              255 seconds.

      Data sequence transmitted by the USD if the USD needs pricing
      information
| USD | Meaning | or | interpretation |
|---|---|---|---|

          Response
| 05 | + Z1 | - Z2 | =      Item | number, | defined | by | the | manufacturer. |
|---|---|---|---|---|---|---|---|---|

      Data sequence transmitted by the USD if the USD has a failure to report
      to VMC
| USD | Meaning | or | Interpretation |
|---|---|---|---|

          Response
| 06 | + Z1 | - Z2 | =      Bits: | b0 | = Health | Safety | violation. |
|---|---|---|---|---|---|---|---|

                                    b1 = Home or Chute sensor failure
                                    b2 = Keypad or Selection switch failure
                                    b3 - b15 = Not defined.

      Data sequence transmitted by the USD for peripheral ID

      6
        This error code is included to identify actuators that may not be present within the initially
      defined row and column configuration. See bytes Z4 and Z5 of the USD’s setup response.
      This is typical in a snack machine implementation where some trays may not be populated
      with a full complement of motors and/or actuators.
      7
        Feature level of the USD is sent to allow the VMC to arbitrate command compatibility with
      the USD. The USD may have elected to transmit this setup data in fulfillment of an earlier
      SETUP command.
      8
        The maximum price on the USD is returned to the VMC so this price can be used in the
      computation of maximum credit acceptance.

| USD | Meaning | or | Interpretation |
|---|---|---|---|

       Response
| 07 + Z1 - Z3 | =     Manufacturer ID Code. |
|---|---|
| Z4 – Z15 = | USD Serial Number. |
| Z16 – Z27 = | USD Model Number. |
| Z28 – Z29 = | USD Software Version. |
| Z30 – Z33 = | Optional feature bits. |

      Data sequence transmitted by the USD to the VMC after a Status request
| USD | Meaning | or | interpretation |
|---|---|---|---|

       Response
| 08 | + Z1 | - Z2 | =     Item number, defined | by the manufacturer. |
|---|---|---|---|---|
| Z3 | - Z4 | = | Bits: b0 = Selection | sold out. |

                                b1 = Selection motor / actuator jam.
                                b2 = Non-existent motor / actuator.
                                b3 = Invalid selection range.
                                b4 = Health safety error.
                                b5 - b15 = Not defined.

      Data sequence transmitted by the USD to the VMC after a USD data
      transfer command
| USD | Meaning | or | interpretation |
|---|---|---|---|

       Response
| 09 | + Z1 | =          Z1 | = 00 | USD | requests | to | receive | data | block | Z2 | from | VMC |
|---|---|---|---|---|---|---|---|---|---|---|---|---|

                          Z1 = 01 USD requests to send Z2 data block(s) to VMC
                          Z1 = 02 USD data block response where:
                               Z2 = data block number
                               Z3 - Zn = contents of data block

| Z2 | =               Z2 | = Block | number | USD | requests | to | receive | if | Z1 | = 00 |
|---|---|---|---|---|---|---|---|---|---|---|

                          Z2 = Number of blocks the USD requests to send if Z1 = 01
                          Z2 = Block number the USD is sending if Z1 = 02.
| Z3 | - Zn | =          Contents | of | data | block | sent | by | USD | to | VMC | if | Z1 | = 02 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

      Data sequence transmitted by the USD to the VMC to send a single
      block of data
| USD | Meaning | or | interpretation |
|---|---|---|---|

       Response
| 0A | + Z1 | - Zn= | Z1 | -Zn | = Arbitrary | data | to | be | received | by | the | VMC. | The |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                          number “n” must be less than 35 per MDB standards

      Data sequence transmitted by the USD to the VMC after an File
      Transport Layer (FTL) REQ TO RCV command
| USD | Meaning | or | interpretation |
|---|---|---|---|

       Response
| Z1=1B | +            The | USD | is | requesting | to | receive | data | from | a device | or | VMC |
|---|---|---|---|---|---|---|---|---|---|---|---|

                          Z2 = Destination address of response

## Z2 - Z6

                          Z3 = Source address of response (40H, 48H, 50H)
                          Z4 = File ID
                          Z5 = Maximum length
                          Z6 = Control

      Data sequence transmitted by the USD to the VMC after an File
      Transport Layer (FTL) RETRY / DENY command
| USD | Meaning | or | interpretation |
|---|---|---|---|

       Response
| Z1=1C | +            The | USD | is | requesting | a device | or | VMC | to | retry | or | deny | the |
|---|---|---|---|---|---|---|---|---|---|---|---|---|

                          last FTL command.

## Z2 - Z4

                          Z2 = Destination address of response
                          Z3 = Source address of response (40H, 48H, 50H)
                          Z4 = Retry delay

      Data sequence transmitted by the USD to the VMC after an File
      Transport Layer (FTL) SEND BLOCK command
| USD | Meaning | or | interpretation |
|---|---|---|---|

       Response
| Z1=1D | +            The | USD | is | sending | a block | of | data | (maximum | of | 31 | bytes) |
|---|---|---|---|---|---|---|---|---|---|---|---|

                          to a device or VMC.

## Z2 - Z34

                          Z2 = Destination address of response
                          Z3 = Block #
                          Z4 - Z34 = Data (maximum of 31 bytes)

      Data sequence transmitted by the USD to the VMC after an File
      Transport Layer (FTL) OK TO SEND command
| USD | Meaning | or | interpretation |
|---|---|---|---|

       Response
| Z1=1E | +            The | USD | is | indicating | that | it | is | OK | for | the | device | or | VMC | to |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                          send it data.

## Z2 - Z3

                          Z2 = Destination address of response
                          Z3 = Source address of response (40H, 48H, 50H)

      Data sequence transmitted by the USD to the VMC after an File
      Transport Layer (FTL) REQ TO SEND command
| USD | Meaning | or | interpretation |
|---|---|---|---|

       Response
| Z1=1F | +            The | USD | is | requesting | to | send | data | to | a device | or | VMC. |
|---|---|---|---|---|---|---|---|---|---|---|---|

                          Z2 = Destination address of response

## Z2 - Z6

                          Z3 = Source address of response (40H, 48H, 50H)
                          Z4 = File ID
                          Z5 = Maximum length
                          Z6 = Control

      Data sequence transmitted by the USD to the VMC after a diagnostic
      command
| USD | Meaning | or | interpretation |
|---|---|---|---|

       Response
| FF | + Z1 | - Zn | Diagnostic | response. |
|---|---|---|---|---|

       =

#### 9.3.4 VEND

| Command | Code | Sub- | VMC | Data | Response | Data |
|---|---|---|---|---|---|---|

                                Cmd
| VEND | 43 | 00 | none |  | none |  |  |  |
|---|---|---|---|---|---|---|---|---|
|  | 43 | 01 | none |  | none |  |  |  |
|  | 43 | 02 | 2 bytes | Y1-Y2 | none |  |  |  |
|  | 43 | 03 | 2 bytes | Y1-Y2 | none |  |  |  |
|  | 43 | 04 | 2 bytes | Y1-Y2 | 5 bytes: | 08 | + Z1 | - Z4 |

The VEND command is the vehicle that the VMC uses to signal vend approval or
disapproval in response to a USD issued vend request (POLL response 01). The

VEND command can also be used by the VMC to initiate a vend, home a selection,
or query the status of a selection on the USD.

| Sub | Cmd: |  | Meaning or interpretation |
|---|---|---|---|
|  | 00 = | Requested vend | approved. |
|  | 01 = | Requested vend | disapproved. |
|  | 02 = | Vend specified | Item number, defined by the manufacturer. |
|  | 03 = | Home specified | Item number, defined by the manufacturer. |
|  | 04 = | Request status | of specified Item number, defined by the |

                        manufacturer.

      Data sequence transmitted by the USD to the VMC after a Status request
| USD | Meaning | or | interpretation |
|---|---|---|---|

       Response
| 08 | + Z1 | - Z2 | =     Item number, defined | by the manufacturer. |
|---|---|---|---|---|
| Z3 | - Z4 | = | Bits: b0 = Selection | sold out. |

                                b1 = Selection motor / actuator jam.
                                b2 = Non-existent motor / actuator.
                                b3 = Invalid selection range.
                                b4 = Health safety error.
                                b5 - b15 = Not defined.

#### 9.3.5 FUNDS

| Command | Code | Sub- | VMC | Data | Response | Data |
|---|---|---|---|---|---|---|

                                Cmd
| FUNDS | 44 | 00 | 2 | bytes: | Y1-Y2 | none |
|---|---|---|---|---|---|---|
|  | 44 | 01 | 6 | bytes: | Y1-Y6 | none |

      The FUNDS command is the vehicle the VMC should use to specify the funds
      available for vending. The FUNDS 00 command is issued by the VMC
      whenever the level of credit changes. Typically, the USD would display the
      credit information returned by a FUNDS 00 command on a credit display.
      The FUNDS 01 is issued by the VMC in response to an item price request
      (POLL response 05) by the USD.

| Sub-Cmd |  | Meaning or interpretation |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|
| 00 + Y1 | - Y2 | =    Funds available in 2 bytes | (word), | scaled | by | the | coin | scaling |

                         factor.

| Sub Cmd |  | Meaning or interpretation |
|---|---|---|
| 01 + Y1 | - Y2 | =      Item number, defined by the manufacturer. |
| Y3 - Y4 | = | Selection price in 2 bytes (word) scaled by coin scaling factor. |
| Y5 - Y6 | = | Alphanumeric selection identifier 2 bytes (word), or FFFF if not |

                                           9
                                available.

#### 9.3.6 CONTROL

| Command | Code | Sub- | VMC | Data | Response | Data |
|---|---|---|---|---|---|---|

                                             Cmd
| CONTROL | 45 | 00 | none | none |
|---|---|---|---|---|
|  | 45 | 01 | none | none |

          This command is the vehicle the VMC should use to enable or disable the
          USD.

| Sub-Cmd | Meaning or interpretation |
|---|---|
| 00 | Disable USD. |
| 01 | Enable USD. |

#### 9.3.7 EXPANSION

| Command | Code | Sub- | VMC | Data | Response | Data |
|---|---|---|---|---|---|---|

                                            Cmd
| EXPANSION | 47 | 00 | None | 07 | + Z1 | - Z34 | Peripheral |
|---|---|---|---|---|---|---|---|

                                                                             ID string and feature bits.
| 47 | 01 | Y1 | – Y4 | none |  |  |
|---|---|---|---|---|---|---|
| 47 | 02 | Y1 |  | none |  |  |
| 47 | 03 | Y1 | - Yn | none |  |  |
| 47 | 04 | Y1 |  | 09 + | Z1 | + Z2 - Zn |
| 47 | 05 | Y1 | - Yn | none |  |  |
| 47 | FA | Y1 | - Y5 | 1D + | Z2 | - Z34 or |

## 1C + Z2 - Z4

| 47 | FB | Y1 | - Y3 | none |
|---|---|---|---|---|
| 47 | FC | Y1 | - Y33 | none |

## 47          Fd         Y1 - Y2              1D + Z2 - Z34

9
    Alpha-numeric selection identifier is provided to the USD for display purposes only.

| 47 | FE | Y1 | - Y5 | 1E | + Z2 | - Z3 | or |
|---|---|---|---|---|---|---|---|

## 1C + Z2 - Z4

| 47 | FF | Diagnostics | Diagnostic | response. |
|---|---|---|---|---|

      Data sequence transmitted by the USD to the VMC after an expansion 00
      sub-command
| USD Response | Meaning or Interpretation |
|---|---|
| 07 + Z1 - Z3 | =         Manufacturer ID Code. |
| Z4 - Z15 = | USD Serial Number. |
| Z16 - Z27 = | USD Model Number. |
| Z28 – Z29 = | USD Software Version. |
| Z30 – Z33 = | Optional feature bits: |

                                  b0 = USD is capable of storing and controlling pricing.
                                  b1 = USD is capable of selecting items to vend.
                                  b2 = USD is capable of supporting the File Transport
                                        Layer. This support is defined in Section 2.6.
                                  b3 - b31 = Available for future use.

      Sub-Command used by the VMC to enable optional feature bits on the
      USD
| Sub-Cmd |  | Meaning or interpretation |  |  |  |  |
|---|---|---|---|---|---|---|
| 01 + Y1 | - Y4 | Enable optional feature bits | defined | in | Z31-Z34 | above. |

                              Feature is enabled if bit is set to 1, all features are disabled
                              after a reset.

      Sub-Command used by the VMC to identify the number of data blocks it
      wishes to send to the USD
| Sub-Cmd | Meaning or interpretation |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|
| 02 + Y1 | Number of data blocks the | VMC | has | to | send | to | the | USD |

                              (Binary)

      Sub-Command used by the VMC to transmit a data block to the USD
      (Y2-Yn) and to identify the current block number being transmitted (Y1)
| Sub-Cmd | Meaning | or | interpretation |
|---|---|---|---|

| 03 | + Y1 | Block | number | the | VMC | is | transmitting | to | the | USD |
|---|---|---|---|---|---|---|---|---|---|---|

                  10
| Y2 | - Yn | Data | the | VMC | is | transmitting | to | the | USD |
|---|---|---|---|---|---|---|---|---|---|

      Sub-Command used by the VMC to request that the USD send or re-
      send data block number (Y1)
| Sub-Cmd | Meaning or interpretation |  |
|---|---|---|
| 04 + Y1 | VMC requests USD to send block | Y1 |

      Sub-Command used by the VMC to send a single block of data to the
      USD
| Sub-Cmd |  | Meaning or interpretation |  |  |  |  |
|---|---|---|---|---|---|---|
| 05 + Y1 | - Yn | VMC sends a single block of | data | consisting | of | Y1..Yn |

      Sub-Command used by the VMC for an FTL REQ TO RCV. The Z1- Zn
      response can be either immediate or delayed (POLLed).
| Sub-Cmd |  | Meaning or interpretation |  |  |  |  |  |
|---|---|---|---|---|---|---|---|
| FA + Y1 | - Y5 | The VMC is requesting to | receive | data | from | the | USD |

                                 whose destination address will always be (40H, 48H,
                                 50H). Note that all FTL Commands / Responses are
                                 defined in Section 2.6.
                                  Y1 = Destination address of command (40H,48H,50H)
                                  Y2 = Source address of command
                                  Y3 = File ID
                                  Y4 = Maximum length
                                  Y5 = Control
| USD Response | Meaning or interpretation |  |
|---|---|---|
| Z1 - Z34 | Z1 = 1DH which indicates SEND | BLOCK |

                                  Z2 = Destination address of data
                                  Z3 = Block #
                                  Z4 - Z34 = Data (maximum of 31 bytes)
|  |  | or |  |  |  | or |  |  |
|---|---|---|---|---|---|---|---|---|
| Z1 | - Z4 |  | Z1 | = 1CH | which | indicates | RETRY | / DENY |

                                  Z2 = Destination address of response
                                  Z3 = Source address of response (40H,48H,50H)
                                  Z4 = Retry delay

      10
           The number “n” is limited by the MDB maximum message length of 36 bytes.

      Sub-Command used by the VMC for an FTL RETRY / DENY.
| Sub-Cmd |  | Meaning or interpretation |  |  |  |  |
|---|---|---|---|---|---|---|
| FB + Y1 | - Y3 | The VMC is retrying, denying, | or | aborting | a data | transfer |

                             to/from the USD whose destination address will always
                             be (40H, 48H, 50H). Note that all FTL Commands /
                             Responses are defined in Section 2.6.
                              Y1 = Destination address of command (40H,48H,50H)
                              Y2 = Source address of command
                              Y3 = Retry delay

      Sub-Command used by the VMC for an FTL SEND BLOCK.
| Sub-Cmd |  | Meaning or interpretation |  |  |  |  |
|---|---|---|---|---|---|---|
| FC + Y1 | - Y33 | The VMC is sending data to | the | USD | whose | destination |

                             address will always be (40H, 48H, 50H). Note that all
                             FTL Commands / Responses are defined in Section 2.6.
                              Y1 = Destination address of command (40H,48H,50H)
                              Y2 = Block #
                              Y3 - Y33 = Data (maximum of 31 bytes)

      Sub-Command used by the VMC for an FTL OK TO SEND. The Z1 to Z33
      response can be either immediate or delayed (POLLed).
| Sub-Cmd |  | Meaning or interpretation |  |  |  |  |  |
|---|---|---|---|---|---|---|---|
| FD + Y1 | - Y2 | The VMC is requesting to | receive | data | from | the | USD |

                             whose destination address will always be (40H, 48H,
                             50H). Note that all FTL Commands / Responses are
                             defined in Section 2.6.
                              Y1 = Destination address of command (40H,48H,50H)
                              Y2 = Source address of command
| USD Response | Meaning or Interpretation |  |
|---|---|---|
| Z1 - Z34 | Z1 = 1DH which indicates SEND | BLOCK |

                              Z2 = Destination address of data
                              Z3 = Source address of data
                              Z4 - Z34 = Data (maximum of 31 bytes)

      Sub-Command used by the VMC for an FTL REQ TO SEND. The Z1 - Zn
      response can be either immediate or delayed (POLLed).
| Sub-Cmd |  | Meaning or interpretation |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|
| FE + Y1 | - Y5 | The VMC is requesting to | send | data | to | the | USD | whose |

                             destination address will always be (40H, 48H, 50H).
                             Note that all FTL Commands / Responses are defined
                             in Section 2.6.
|  | Y1    = Destination address of command | (40H,48H,50H) |
|---|---|---|
|  | Y2    = Source address of command |  |
|  | Y3    = File ID |  |
|  | Y4    = Maximum length |  |
|  | Y5    = Control |  |
| USD Response | Meaning or Interpretation |  |
| Z1 - Z34 | Z1 = 1EH which indicates OK TO SEND |  |

                              Z2 = Destination address of response
                              Z3 = Source address of response (40H,48H,50H)
|  |  | or |  |  |  | or |  |  |
|---|---|---|---|---|---|---|---|---|
| Z1 | - Z4 |  | Z1 | = 1CH | which | indicates | RETRY | / DENY |

                              Z2 = Destination address of response
                              Z3 = Source address of response (40H,48H,50H)
                              Z4 = Retry delay

      Data sequence transmitted by the USD to the VMC after a diagnostic
      command
| USD Response | Meaning or | interpretation |
|---|---|---|
| FF + Z1 - Zn | =      Diagnostic | response. |

#### 9.4 USD Power Requirements

      This section defines the maximum power requirements for a USD.

      USD peripherals may draw power from the MDB bus or from an integral
      power supply. In such cases where the USD will require power from the MDB
      bus, the current draw must remain within the following limits:
| USD Mode | Current draw |
|---|---|
| Idle | 200 mA ( maximum continuous) |
| Vending/Homing | 1.75 A (for up to 10 seconds) |

#### 9.5 Examples – Mode 1 / 2 / 3 Sessions

      This section contains three examples of USD sessions in which each of the
      three modes of USD operation are demonstrated operation respectively.

#### 9.5.1 MODE ONE

      In this example session the VMC selects the item to vend and knows the
      vend price. The USD receives the vend command, attempts the vend, and
      reports if the attempted vend failed or was successful.

| VMC | MDB Data |  |  | Explanation |  | USD |
|---|---|---|---|---|---|---|
| ⇒ | 43+02+01+03 | VMC | requests | to vend item from | the |  |

                                      USD.
|  | <ACK> | USD | acks vend request. | ⇐ |
|---|---|---|---|---|
| ⇒ | 42 | VMC | polls the USD. |  |
|  | <ACK> | USD | acks receipt of poll. | ⇐ |
| ⇒ | 42 | VMC | polls the USD again . |  |
|  | 02 | USD | responds: vend complete | ⇐ |
| ⇒ | <ACK> | VMC | acks vend outcome. |  |

#### 9.5.2 MODE TWO

      In this example session the USD or the VMC can select items to vend but the
      USD may not be aware of the vend price of the item selected. If the USD
      needs the selected item price, it may request the item price from the VMC.
      The USD must then issue a VEND request, and wait for approval from the
      VMC before a vend is attempted. The VMC then approves or denies the
      requested vend and polls the USD for vend success or vend fail.

| VMC | MDB Data |  | Explanation |  |  | USD |
|---|---|---|---|---|---|---|
| ⇒ | 42 | VMC | polls the USD. |  |  |  |
|  | 05+02+06 | USD | responds with pricing | request | for | ⇐ |

                                         item in USD.
| ⇒ | <ACK> | VMC acks the USD price request. |  |  |
|---|---|---|---|---|
| ⇒ | 44+01+02+06+00+1 | Using the Funds command the VMC |  |  |
|  | 4 | sends a price of 20 coin factors | for | item |
|  | +FF+FF | in USD. |  |  |

|  | <ACK> | USD | acks receipt of | VMC price data. | ⇐ |
|---|---|---|---|---|---|
| ⇒ | 42 | VMC | polls the USD. |  |  |
|  | 01+02+06+FF+FF | USD | responds with a | request to vend | ⇐ |

                                         item in USD at the VMC selected price.
| ⇒ | <ACK> | VMC | acks receipt of vend request. |  |
|---|---|---|---|---|
| ⇒ | 43 + 00 or 01 | VMC | approves or denies vend request. |  |
|  | <ACK> | USD | acks receipt of approval or denial. | ⇐ |
| ⇒ | 42 | VMC | polls the USD. |  |
|  | 03+02+06+00+01 | USD | responds: vend fail, sold out. | ⇐ |
| ⇒ | <ACK> | VMC | acks vend outcome. |  |

      - The FUNDS command can be used by USD’s which do not have internal
          prices but need pricing information for display purposes or for other
          reasons that are not required to complete a transaction.

#### 9.5.3 MODE THREE

      In this example session the USD selects the item to vend and is aware of the
      vend price of the item. The USD must issue a vend request and the VMC
      then approves or denies the requested vend. The VMC then polls the USD
      for vend success or vend fail.

| VMC | MDB Data |  | Explanation |  |  |  | USD |
|---|---|---|---|---|---|---|---|
| ⇒ | 42 | VMC | polls the USD. |  |  |  |  |
|  | 01+03+02+00+1E | USD | requests vend for item | at | in | USD | ⇐ |

                                         with price of 30 coin factors.
| ⇒ | <ACK> |  | VMC | acks the USD vend request. |  |
|---|---|---|---|---|---|
| ⇒ | 43+ 00 or | 01 | VMC | approves or denies vend request. |  |
|  | <ACK> |  | USD | acks receipt of approval or denial. | ⇐ |
| ⇒ | 42 |  | VMC | polls the USD. |  |
|  | 02 |  | USD | responds: vend complete | ⇐ |
| ⇒ | <ACK> |  | VMC | acks vend outcome. |  |

#### 9.6 Examples - Data Block Transfers

      This section contains two examples in which data blocks are transferred
      between the VMC and the USD and vice versa.

#### 9.6.1 Data Block Transfer from VMC to USD

      In this example the VMC wishes to send two data blocks to the USD. To do
      this, the VMC uses the expansion 02 command to advise the USD of it’s
      request to send data and also to identify the number of data blocks it wishes
      to send. In response, the USD uses a poll 09 to request the transmission of
      a data block with the block number enumerated as part of it’s poll response.
      The VMC then uses a different expansion command (03) to send the data to
      the USD.

| VMC | MDB Data |  |  | Explanation |  |  | USD |
|---|---|---|---|---|---|---|---|
| ⇒ | 47+02+02 | VMC | issues | a request to send | two | data |  |

                                         blocks to the USD
|  | <ACK> | USD | acks receipt of | the request | ⇐ |
|---|---|---|---|---|---|
| ⇒ | 42 | VMC | polls the USD |  |  |
|  | 09+00+01 | USD | responds with a | request to receive | ⇐ |

                                         data block number 01 from the VMC
| ⇒ | <ACK> | VMC acks receipt of block number |  |
|---|---|---|---|
| ⇒ | 47+03+01+21+22+2 | VMC transmits block number 01 |  |
|  | 3 | containing data: 21, 22, and 23. |  |
|  | <ACK> | USD acks receipt of the data block | ⇐ |
| ⇒ | 42 | VMC polls the USD. |  |
|  | 09+00+02 | USD responds with a request to receive | ⇐ |

                                         data block number 02 from the VMC.
| ⇒ | <ACK> | VMC acks receipt of the block number. |  |
|---|---|---|---|
| ⇒ | 47+03+02+24+25+2 | VMC transmits block number 02 |  |
|  | 6 | containing data: 24, 25, and 26. |  |
|  | <ACK> | USD acks receipt of the data block | ⇐ |

#### 9.6.2 Data Block Transfer from USD to VMC

      In this example the USD wishes to send two data blocks to the VMC. To do
      this, the USD makes use of the Poll 09 command to inform the VMC of it’s
      request to send data and also to identify the number of data blocks it wishes
      to send. In response, the VMC uses expansion 04 command to request the
      transmission of a data block by the individual block number. The USD then
      uses the poll 09 response to send the data blocks to the VMC.

| VMC | MDB Data |  | Explanation |  |  | USD |
|---|---|---|---|---|---|---|
| ⇒ | 42 | VMC | polls the USD |  |  |  |
|  | 09+01+02 | USD | responds with a request | to | send | 2        ⇐ |

                                         data blocks to the VMC
| ⇒ | <ACK> | VMC | acks request to | send data |  |
|---|---|---|---|---|---|
| ⇒ | 47+04+01 | VMC | responds with a | request to | receive |

                                         data block number 01 from the USD
| <ACK> | USD | acks | receipt | of | block | number | ⇐ |
|---|---|---|---|---|---|---|---|

                                         request
| ⇒ | 42 | VMC polls the USD |  |
|---|---|---|---|
|  | 09+02+01+55+56+5 | USD responds by transmitting block | ⇐ |
|  | 7 | number 01 containing data 55, 56, and |  |

                                         57.
| ⇒ | <ACK> | VMC | acks receipt of | data |  |  |
|---|---|---|---|---|---|---|
| ⇒ | 47+04+02 | VMC | responds with a | request | to | receive |

                                         data block number 02 from the USD
| <ACK> | USD | acks | receipt | of | block | number | ⇐ |
|---|---|---|---|---|---|---|---|

                                         request
| ⇒ | 42 | VMC polls the USD |  |
|---|---|---|---|
|  | 09+02+02+58+59+6 | USD responds by transmitting block | ⇐ |
|  | 0 | number 02 containing data 58, 59, and |  |

                                         60.
| ⇒ | <ACK> | VMC | acks | receipt | of | data |
|---|---|---|---|---|---|---|

#### 9.7 Universal Satellite Device Examples

Reset Sequence
|  | Controller |  | USD |  | Comments |
|---|---|---|---|---|---|
| RESET | (40) |  |  | Reset | command |

##     Ack

## Poll (42)                   

|  | JUST | RESET | (00) | Must | be | sent | once |
|---|---|---|---|---|---|---|---|

## Ack                         

| SETUP | (41) |  |  |  | Establish operation |
|---|---|---|---|---|---|
|  |  |  | CONFIG. | (04…) | configuration |

## Ack                         

| EXPANSION/ID | (47/00…) |  |  |  |  | Send asset information |
|---|---|---|---|---|---|---|
|  |  |  | PERIPHERAL | ID | (07…) | Get asset information |

## Ack                         

| EXPANSION/FEATURE |  | Enable additional | feature | if |
|---|---|---|---|---|
| ENABLE (47/01…) |  | necessary |  |  |

##     Ack

| VEND/STATUS |  | Check | the | status | of | column |
|---|---|---|---|---|---|---|

## Request

(43/04 01 01)

##     Ack

## Poll (42)                   

|  | STATUS | (08…) | Status | of | column |
|---|---|---|---|---|---|

## Ack                         

                                 .
                                 .
                                 .
| CONTROL/ENABLE |  | Enable | command |
|---|---|---|---|

(45/01)

##     Ack

| VEND/HOME | REQUEST |  | Home | column |
|---|---|---|---|---|

(43/03 01 01)

##     Ack

## Poll (42)                   

|  | VEND | COMPLETE | (02…) | Homing | of | column | 1 completed |
|---|---|---|---|---|---|---|---|

## Ack                         

                                 .
                                 .
                                 .
Enable Sequence
| Controller |  | USD |  | Comments |
|---|---|---|---|---|
| CONTROL/ENABLE |  |  | Enable | command |

(45/01)

##     Ack

Disable Sequence
| Controller |  | USD |  | Comments |
|---|---|---|---|---|
| CONTROL/DISABLE |  |  | Disable | command |

(45/00)

##     Ack

Vend Sequence
| Controller |  |  | USD | Comments |  |  |
|---|---|---|---|---|---|---|
| FUNDS/FUNDS AVAIL |  |  |  | Post funds available | to | alert |
| (43…) |  |  |  | device of pending |  |  |
|  |  | ACK |  | activity |  |  |
| POLL |  |  |  | Waiting for activity |  |  |

##     Ack

| VEND/VEND | REQUEST |  | Vend | from | row | 1, | col. |
|---|---|---|---|---|---|---|---|

(43/02 01 03)

##     Ack

## Poll (42)                   

|  | ACK | Nothing | to report |  |
|---|---|---|---|---|
| . |  | waiting | for vend to | complete |

                             .
                             .

## Poll (42)                   

|  | VEND | COMPLETE | (02) | or | VEND | FAIL | (03…) |
|---|---|---|---|---|---|---|---|

## Ack                         

Error Sequence
| Controller | USD | Comments |
|---|---|---|

## Poll (42)                   

|  |  | ERROR | (06…) | Sent once | for | each |
|---|---|---|---|---|---|---|
| ACK |  |  |  | error |  |  |

                          (this page intentionally left blank)

Section 10
   Coin Hopper or Tube - Dispenser
   VMC/Peripheral Communication Specifications

#### 10.1 Introduction

This section defines the communication bytes sent and received by a coin dispensing device, which
may be in the form of a hopper or tube device. As defined in Section 2.3, there are two dispenser
device addresses; Dispenser #1, 01011xxxB (58H) and Dispenser #2, 01110xxxB (70H). The second
address has been assigned to allow for two unique forms of dispenser devices to be resident in the
vending machine simultaneously. Everything defined in this section will be common to the two
dispenser devices – only the addresses will be different.

       Unless stated otherwise, all information is assumed to be in a binary format

#### 10.2 VMC Commands

| Command | Hex | Code | Description |
|---|---|---|---|

| RESET | 58H | / 70H | Command | for | dispenser | to | self-reset |
|---|---|---|---|---|---|---|---|

| SETUP | 59H | / 71H | Request | for | dispenser | setup. |
|---|---|---|---|---|---|---|

| DISPENSER | STATUS | 5AH | / 72H | Request | for | dispenser | tube | / hopper | status | and |
|---|---|---|---|---|---|---|---|---|---|---|

                                                coin count.

| POLL | 5BH | / 73H | Request | for | dispenser | activity | status. |
|---|---|---|---|---|---|---|---|

| MANUAL | DISPENSE | 5CH | / 74H | Signifies coin types allowable for coin | dispensing. |
|---|---|---|---|---|---|
| ENABLE |  |  |  | This command is followed by setup data. |  |

                                                See command format section.

| DISPENSE | *              5DH | / 75H | Command | to | dispense | coins. |
|---|---|---|---|---|---|---|

                                                Followed by coin type or value to dispense.
                                                See command format section.

| PAYOUT | *                5EH | / 76H | Command | to | determine | value | of | coins | dispensed. |
|---|---|---|---|---|---|---|---|---|---|

                                                Followed by payout status or value poll.
                                                See command format section.

| EXPANSION | *             5FH | / 77H | Command | to | allow | addition | of | features, | File |
|---|---|---|---|---|---|---|---|---|---|

                                                Transport Layer, and future enhancements.
                                                See command format section.

      - NOTE:         DISPENSE, PAYOUT, and EXPANSION commands are always followed by
                       a “sub-command.”

#### 10.3 VMC Command Format

| VMC Command | Code |  | VMC Data |
|---|---|---|---|
| RESET | 58H / | 70H | No data bytes |

      This command is the vehicle that the VMC should use to tell the dispenser that it should
      return to its default operating mode and initialize internal hardware systems. With the
      exception of the ACK response, it should abort all communication until otherwise instructed
      by the VMC.

      The following initialization sequence is recommended. It should be used after “power up” or
      after issuing the Bus Reset (pulling the transmit line “active” for a minimum of 100 mS).

      RESET – `58h` / `70h`
      POLL – `5Bh` / `73h`
            To obtain “JUST RESET” response
      SETUP – `59h` / `71h`
            To obtain dispenser level and configuration information
      EXPANSION IDENTIFICATION – 5F `00h` / 77 `00h`
           To obtain additional dispenser information and options
      EXPANSION FEATURE ENABLE – 5F `01h` / 77 `01h`
           To enable desired options
      DISPENSER STATUS – `5Ah` / `72h` (Note 1)
            To obtain dispenser status / change information
      MANUAL DISPENSE ENABLE – `5Ch` / `74h`
           To enable and disable manual coin pay-out if desired

      No power above idle current can be drawn until after the first POLL following the RESET
      command. Also, the JUST RESET response to the POLL command must be delayed until
      any high current usage has been completed.

      The dispenser must hold its response of the DISPENSER status until a valid current reading
      from the sensor system is achieved.

| VMC Command | Code |  | Dispenser | Response | Data |
|---|---|---|---|---|---|
| SETUP | 59H / | 71H | 26 bytes: | Z1 - Z26 |  |

| Z1 | =          Dispenser | Feature | Level | - 1 | byte |
|---|---|---|---|---|---|

                    Indicates the feature level of the dispenser. This will distinguish the
                    dispensers feature level to the VMC. Currently only level 1 is supported.

| Z2 | - Z3 | =     Country | / Currency | Code | - 2 | bytes |
|---|---|---|---|---|---|---|

                    The packed BCD currency code of the dispenser is sent with the left most
                    digit a 1. See Appendix A1 for the latest version of the ISO 4217 numeric
                    currency code. For example, the code for the US dollar is 18 40H (Z2 = 18
                    and Z3 = 40) and for the Euro is 1978 (Z2 = 19 and Z3 = 78).

| Z4 | =          Coin | Scaling | Factor | - 1 | byte |
|---|---|---|---|---|---|

                    All dispensed coin values must be evenly divisible by this number. For
                    example, this could be set to 05H for the USA nickel.

| Z5 | =          Decimal | Places | - 1 | byte |
|---|---|---|---|---|

                    Indicates the number of decimal places on a credit display. For example, this
                    could be set to 02H in the USA.

| Z6 | =          Application | Maximum | Response | Time | (seconds) | – 1 | byte |
|---|---|---|---|---|---|---|---|

                    The maximum length of time a dispenser will require to provide a response to
                    any command from the VMC. The value reported here supercedes the
                    dispenser’s default NON-RESPONSE time defined in section 10.4 if the
                    value reported here is greater.

| Z7 | – Z8 | =     Bit | set, | if | coin | disabled | by | dispenser | (i.e. | switch). |
|---|---|---|---|---|---|---|---|---|---|---|

| Z9 | – Z10 | =    Bit | set, | if | coin | is | self | filling. |
|---|---|---|---|---|---|---|---|---|

| Z11 | - Z26 | =   Coin | Type | Credit | - 16 | bytes |
|---|---|---|---|---|---|---|

                    Indicates the value of coin types 0 to 15. Values must be sent in ascending
                    order. This number is the coin's monetary value divided by the coin scaling
                    factor. Unused coin types are sent as 00H. Unsent coin types are assumed
                    to be zero. It is not necessary to send all coin types. Coin type credits sent
                    as FFH are assumed to be vend tokens. That is, their value is assumed to
                    be worth one vend.

                    The byte position in the 16 byte string indicates the coin type(s). For
                    example, the first byte sent would indicate the value of coin type 0, the
                    second byte sent would indicate the value of coin type 1, and so on. For
                    example, the USA coin types may be; Coin type 0 = nickel, Coin type 1 =
                    dime, Coin type 2 = quarter, Coin type 3 = dollar.

| VMC Command | Code |  | Dispenser | Response | Data |
|---|---|---|---|---|---|
| DISPENSER STATUS | 5AH / | 72H | 34 bytes: | Z1 – Z34 |  |

| Z1 | - Z2 | =       Dispenser | Full | Status | - 2 | bytes |
|---|---|---|---|---|---|---|

                      Indicates status of coin tube / hopper for coin types 0 to 15.

                      b15 b14 b13 b12 b11 b10 b9 b8 | b7 b6 b5 b4 b3 b2 b1 b0

## Z1                              Z2

                      A bit is set to indicate a full dispenser. For example, bit 7 = set would indicate the
                      dispenser for coin type 7 is full.

| Z3 | – Z34 | =      Coin | Count | - 32 | bytes |
|---|---|---|---|---|---|

                      Indicates the greatest number of coins that the dispenser “knows” definitely
                      are present in the coin tube / hopper. A word (2 bytes) position in the 32 byte
                      string indicates the number of coins in a tube / hopper for a particular coin
                      type. For example, the first 2 bytes sent indicate the number of coins in a
                      tube / hopper for coin type 0. Unsent bytes are assumed to be zero. For
                      tube / hopper counts greater than 65535, counts should remain at 65535.

      NOTE: If a dispenser can detect a tube or hopper jam, defective tube or hopper sensor, or
      other malfunction, it will indicate the tube / hopper is "bad" by sending a tube / hopper full
      status and a count of zero for the malfunctioning coin type.

| VMC Command | Code |  | Dispenser | Response | Data |
|---|---|---|---|---|---|
| POLL | 5BH / | 73H | 32 bytes: | Z1 – Z32 |  |

| Z1 | - Z32 | =      Dispenser | Activity | - 32 | bytes |
|---|---|---|---|---|---|

                      Indicates the dispenser activity. If there is nothing to report, the dispenser
                      should send only an ACK. Otherwise, the only valid responses are:

      Coins Dispensed:

                      This response should be sent once at the end of a payout cycle.

| Z1 | (10yzxxxx) |
|---|---|

| z | z | =1 | for | manual | dispense |
|---|---|---|---|---|---|

                                       z =0 to report a non manual (automatic) dispense
| y | y | =1 | for | payout | completed | successfully |
|---|---|---|---|---|---|---|

                                       y =0 for payout completed unsuccessfully (aborted)

| xxxx | The | coin | type | dispensed | (0 | to | 15) |
|---|---|---|---|---|---|---|---|

| Z2 | - Z3 | The | number | of | coins | dispensed. |
|---|---|---|---|---|---|---|

| Z4 | – Z5 | The | number | of | coins | in | the | dispenser. |
|---|---|---|---|---|---|---|---|---|

      Status:
| (00000001) | =            Escrow | request1 | - An | escrow | lever | activation | has |
|---|---|---|---|---|---|---|---|

                                            been detected. If a button is present and activated.
| (00000010) | =            Dispenser | Payout | Busy2 | - The | dispenser | is | busy |
|---|---|---|---|---|---|---|---|

                                            activating payout devices.
| (00000011) | =            Not Used |  |  |  |  |  |
|---|---|---|---|---|---|---|
| (00000100) | =            Defective | Dispenser | Sensor1 | - The | dispenser | has |

                                            detected one of the dispenser sensors behaving
                                            abnormally.
| (00000101) | =            Not Used |  |  |  |  |
|---|---|---|---|---|---|
| (00000110) | =            Dispenser | did not start1. |  |  |  |
| (00000111) | =            Dispenser | Jam1 - A dispenser | payout | attempt | has |

                                            resulted in jammed condition.
| (00001000) | =            ROM | checksum | error1 | - The | dispensers | internal |
|---|---|---|---|---|---|---|

                                            checksum does not match the calculated checksum.
| (00001001) | =            Not Used |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|
| (00001010) | =            Not Used |  |  |  |  |  |  |
| (00001011) | =            Dispenser | was | “Just | Reset”1 | - The | dispenser | has |

                                            detected a Reset condition and has returned to its
                                            power-on idle condition.
| (00001100) | =            Not Used |  |  |  |  |  |
|---|---|---|---|---|---|---|
| (00001101) | =            Not Used |  |  |  |  |  |
| (00001110) | =            Not Used |  |  |  |  |  |
| (00001111) | =            Filled key | pressed1 | – The | VMC | should | request |

                                            new DISPENSER STATUS.

| NOTES: | The | dispenser | may | send | several | of | one | type | activity, | up | to | 16 | bytes | total. |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                    This will permit zeroing counters such as inventory and status.

| 1 | Sent | once | each | occurrence. |
|---|---|---|---|---|
| 2 | Sent | once | each | POLL |

      File Transport Layer POLLed responses:

      Note that all FTL responses are defined in Section 2.6. For the coin dispenser, the source
      address will always be the dispenser (58H/70H) as defined in Section 2.3.

              Z1

| 1B | REQ | TO | RCV | The | coin | dispenser | is | requesting | to |
|---|---|---|---|---|---|---|---|---|---|

                                              receive data from a device or VMC.

                                              Z2 = Destination address of response
                                              Z3 = Source address of response (58H/70H)
                                              Z4 = File ID
                                              Z5 = Maximum length
                                              Z6 = Control

| 1C | RETRY/DENY | The | coin | dispenser | is | requesting | a device | or |
|---|---|---|---|---|---|---|---|---|

                                              VMC to retry or deny the last FTL command.

                                              Z2 = Destination address of response
                                              Z3 = Source address of response (58H/70H)
                                              Z4 = Retry delay

| 1D | SEND | BLOCK | The | coin | dispenser | is | sending | a block | of | data |
|---|---|---|---|---|---|---|---|---|---|---|

                                              (maximum of 31 bytes) to a device or VMC.

                                              Z2 = Destination address of data
                                              Z3 = Block #
                                              Z4-Z34 = Data (maximum of 31 bytes)

| 1E | OK | TO | SEND | The | coin | dispenser | is | indicating | that | it |
|---|---|---|---|---|---|---|---|---|---|---|

                                              is OK for a device or VMC to send it data.

                                              Z2 = Destination address of response
                                              Z3 = Source address of response (58H/70H)

| 1F | REQ | TO | SEND | The | coin | dispenser | is | requesting | to |
|---|---|---|---|---|---|---|---|---|---|

                                              send data to a device or VMC.

                                              Z2 = Destination address of response
                                              Z3 = Source address of response (58H/70H)
                                              Z4 = File ID
                                              Z5 = Maximum length
                                              Z6 = Control

| VMC Command | Code |  | VMC Data |  |  |
|---|---|---|---|---|---|
| MANUAL DISPENSE | 5CH / | 74H | 2 bytes: | Y1 | – Y2 |

## Enable

| Y1 | - Y2 | =       Manual | Dispense | Enable | - 2 | bytes |
|---|---|---|---|---|---|---|

      b15 b14 b13 b12 b11 b10 b9 b8 | b7 b6 b5 b4 b3 b2 b1 b0

## Y1                              Y2

      A bit is set to indicate dispense enable. For example, bit 2 is set to enable dispensing of coin
      type 2. This command enables/disables manual dispensing using optional inventory
      switches. All manual dispensing switches are automatically disabled upon reset.

| VMC Command | Code |  | Sub-command |  | VMC Data |  |
|---|---|---|---|---|---|---|
| DISPENSE COINS | 5DH / | 75H | 00H | 3 | bytes: Y1 | – Y3 |

      b7 b6 b5 b4 b3 b2 b1 b0
      Y1

      Bits b3, b2, b1, b0 indicate coin type to be dispensed. Valid codes are 0H to FH to indicate
      coin types 0 to 15.

      Bits b7, b6, b5, b4 = 0

| Y2 | - Y3 | =       Number | of | coins | to | be | dispensed | of | coin | type | defined | in | Y1 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                      There is no defined limit on how long the actual dispense takes since the
                      command allows for up to 65535 coins to be paid out. The payout cycle
                      begins when the dispenser ACKs the VMC’s DISPENSE (5DH/75H)
                      command. This cycle typically lasts a minimum of 100 mS and ends when
                      the dispenser stops dispensing the desired number of coins. VMCs should
                      monitor the Dispenser Payout Busy and Dispenser Activity response to the
                      POLL (5BH/73H) command to determine when the entire payout cycle is
                      completed.

| VMC Command | Code |  | Sub-command |  | VMC Data |  |
|---|---|---|---|---|---|---|
| DISPENSE VALUE | 5DH / | 75H | 01H | 2 | bytes: Y1, | Y2 |

| Y1 | – Y2 | =       Value | of | coins | to | be | paid | out. |
|---|---|---|---|---|---|---|---|---|

                      Y1 and Y2 are defined as the value of coins and this value is expressed as
                      the number of coin scaling factors that would sum to the value. For example,
                      in a USA system using a scaling factor of 05, if the change to be paid out is
                      75 cents, then Y1 will equal fifteen. That is, the sum of fifteen nickels equal
                      75 cents. The coin dispenser will determine which actual denominations of
                      coins will be paid out. In the 75 cent example, the coins may be 3 quarters;
                      or, 7 dimes & 1 nickel; or, 2 quarters & 2 dimes & 1 nickel, etc. The actual
                      coins dispensed and if the dispense is finished can be acquired via the
                      PAYOUT STATUS (5EH/76H, 00) and PAYOUT VALUE POLL (5EH/76H,
                      01).

| VMC Command | Code |  | Sub-command | VMC Data | Dispenser Response |
|---|---|---|---|---|---|
| PAYOUT | 5E / | 76H | 00H | None | 32 bytes: Z1-Z32 |

## Status

| Z1 | – Z32 | =       Number | of | each | coin | type | paid | out | - 32 | bytes | (2 | bytes | per | coin | type). |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                       This is the dispenser's response to the last VMC DISPENSE VALUE
                       command (5DH sub command 01H). Bytes are sent in ascending order of
                       coin types. A bytes position in the string indicates the coin type. That is,
                       bytes one and two are the number of coins for coin type 1, bytes three and
                       four are the number of coins for coin type two, and so on. Unsent bytes
                       above the coin types dispensed are assumed to be zero.

                       The dispenser clears payout data after an ACK response from the VMC.

                       The VMC should compare the value of the coins paid out to the (5DH/75H)
                       DISPENSE VALUE command’s Y2-Y3.

| NOTES: | 1) | If | the | dispenser’s | payout | is | busy | it | will | respond | to | the |
|---|---|---|---|---|---|---|---|---|---|---|---|---|

                          PAYOUT STATUS command with an ACK only.

                       2) If no coins have been paid out, at least one zero valued data byte must
                          be sent.

                       3) There is no defined limit on how long the actual payout
                         takes. See dispense command (5DH/75H) for further details

| VMC Command Code |  | Sub-command | VMC Data | Dispenser Response | Data |
|---|---|---|---|---|---|
| PAYOUT VALUE 5EH | /76H | 01H | None | 2 bytes: Z1-Z2 |  |

      POLL

| Z1 | – Z2 | = | Dispenser | Payout | Activity | - 2 | bytes |
|---|---|---|---|---|---|---|---|

                               An interval value (scaled) which indicates the amount of paid out
                               change since the previous PAYOUT VALUE POLL (or between the
                               initial DISPENSE VALUE command (5DH/75H sub command 01H)
                               and the first PAYOUT VALUE POLL).

                               A 00H response indicates no coins were paid out since the previous
                               PAYOUT VALUE POLL (or the initial DISPENSE VALUE command
                               (5DH/75H sub command 01H)).

                               An ACK only indicates that the change payout is finished. This
                               should be followed by the PAYOUT STATUS command (5EH/76H-
                               00H) to obtain the complete payout data.

      NOTE: The initial intent of this command is to determine the amount of change paid out so
      that the credit display can be decremented as coins are dispensed.

| VMC Command | Code |  | Sub-Command | Dispenser | Response | Data |
|---|---|---|---|---|---|---|
| EXPANSION | 5FH / | 77H | 00H | 33 bytes: | Z1 - Z33 |  |

## Command                Identification

| Z1 | - Z3 | =      Manufacturer | Code | - 3 | bytes |
|---|---|---|---|---|---|

                     Identification code for the equipment supplier. Sent as ASCII characters.
                     Currently defined codes are listed in the EVA document entitled "European
                     Vending Association Data Transfer Standard" (EVA-DTS), the Audit Data
                     Lists section, sub-section 2, "Manufacturer Codes".

| Z4 | - Z15 | =     Serial | Number | - 12 | bytes |
|---|---|---|---|---|---|

                     Factory assigned serial number. All bytes must be sent as ASCII characters,
                     zeros (30H) and blanks (20H) are acceptable.

| Z16 | - Z27 | =    Model | Number | - 12 | bytes |
|---|---|---|---|---|---|

                     Manufacturer assigned model number. All bytes must be sent as ASCII
                     characters, zeros (30H) and blanks (20H) are acceptable.

| Z28 | - Z29 | =    Software | Version | - 2 | bytes |
|---|---|---|---|---|---|

                     Current software version. Must be sent in packed BCD.

| Z30 | - Z33 | =    Optional | Features | - 4 | bytes |
|---|---|---|---|---|---|

                     Each of the 32 bits indicate an optional features availability. If the bit is set
                     the feature is available. Bits should be sent in descending order, i.e. bit 31 is
                     sent first and bit 0 is sent last. Currently defined options are:

| b0 | -             File | Transport | Layer | (FTL) | supported | as | defined | in | Section |
|---|---|---|---|---|---|---|---|---|---|

                                      2.6.

| b1 | - b31 | Available | for | future | use |
|---|---|---|---|---|---|

| VMC Command | Code |  | Sub-Command | VMC Data |  |  |
|---|---|---|---|---|---|---|
| EXPANSION | 5FH / | 77H | 01H | 4 bytes: | Y1 | - Y4 |

## Command                Feature Enable

      This command is used to enable each of the optional features defined in Z30-Z33 above. To
      enable a feature a bit is set to one. All optional features are disabled after reset.

| VMC Command | Code      Sub-command | VMC Data | Dispenser Response |  |
|---|---|---|---|---|
| EXPANSION | 5FH / 77H FAH | Y1-Y5 | Z1 - Zn (immediate | or |
| COMMAND | FTL REQ TO RCV |  | POLLed) |  |

      The VMC is requesting to receive data from the dispenser whose destination address will
      always be (58H/70H). Note that all FTL Commands / Responses are defined in Section 2.6.

| Y1 | = | Destination address of command | (58H/70H) |
|---|---|---|---|
| Y2 | = | Source address of command |  |
| Y3 | = | File ID |  |
| Y4 | = | Maximum length |  |
| Y5 | = | Control |  |

| Z1 | = | 1DH which indicates | SEND BLOCK |
|---|---|---|---|
| Z2 | = | Destination address | of data |
| Z3 | = | Block # |  |
| Z4 | - Z34 | =     Data (maximum of 31 | bytes) |

                                     or
| Z1 | =           1CH which indicates RETRY / DENY |
|---|---|
| Z2 | =           Destination address of response |
| Z3 | =           Source address of response (58H/70H) |
| Z4 | =           Retry delay |

| VMC Command | Code |  | Sub-command | VMC Data | Dispenser Response |
|---|---|---|---|---|---|
| EXPANSION | 5FH / | 77H | FBH | Y1-Y3 | None |

## Command     Ftl Retry / Deny

      The VMC is retrying, denying, or aborting a data transfer to/from the dispenser whose
      destination address will always be (58H/70H). Note that all FTL Commands / Responses are
      defined in Section 2.6.

| Y1 | =           Destination address of command | (58H/70H) |
|---|---|---|
| Y2 | =           Source address of command |  |
| Y3 | =           Retry delay |  |

| VMC Command | Code |  | Sub-command | VMC Data | Dispenser Response |
|---|---|---|---|---|---|
| EXPANSION | 5FH / | 77H | FCH | Y1-Y33 | None |

## Command     Ftl Send Block

      The VMC is sending data to the dispenser whose destination address will always be
      (58H/70H). Note that all FTL Commands / Responses are defined in Section 2.6.

| Y1 | = | Destination address | of command | & data | (58H/70H) |
|---|---|---|---|---|---|
| Y2 | = | Block # |  |  |  |
| Y3 | - Y33 | =     Data (maximum of 31 | bytes) |  |  |

| VMC Command | Code | Sub-command | VMC Data | Dispenser | Response |  |
|---|---|---|---|---|---|---|
| EXPANSION | 5FH / 77H | FDH | Y1-Y2 | Z1-Z34 | (immediate | or |
| COMMAND | FTL OK TO | SEND |  |  | POLLed) |  |

      The VMC is indicating that it is OK for the dispenser to transfer data. The destination
      address will always be the dispenser (58H/70H). Note that all FTL Commands / Responses
      are defined in Section 2.6.

| Y1 | =           Destination address of command | (58H/70H) |
|---|---|---|
| Y2 | =           Source address of command |  |

| Z1 | = | 1DH which indicates SEND BLOCK |
|---|---|---|
| Z2 | = | Destination address of data |
| Z3 | = | Source address of data |
| Z4 | - Z34 | =     Data (maximum of 31 bytes) |

| VMC Command | Code      Sub-command | VMC Data | Dispenser Response |
|---|---|---|---|
| EXPANSION | 5FH / 77H FEH | Y1-Y5 | Z1 (immediate or |
| COMMAND | FTL REQ TO SEND |  | POLLed) |

      The VMC is requesting to send data to the dispenser whose destination address will always
      be (58H/70H). Note that all FTL Commands / Responses are defined in Section 2.6.

| Y1 | = | Destination address of command | (58H/70H) |
|---|---|---|---|
| Y2 | = | Source address of command |  |
| Y3 | = | File ID |  |
| Y4 | = | Maximum length |  |
| Y5 | = | Control |  |

| Z1 | =           1EH which indicates OK TO SEND |
|---|---|
| Z2 | =           Destination address of response |
| Z3 | =           Source address of response (58H/70H) |

                                     or
| Z1 | = | 1CH which indicates RETRY / DENY |
|---|---|---|
| Z2 | = | Destination address of response |
| Z3 | = | Source address of response (58H/70H) |
| Z4 | = | Retry delay |

| VMC Command | Code |  | Sub-command | VMC Data | Dispenser | Response |
|---|---|---|---|---|---|---|
| EXPANSION | 5FH / | 77H | FFH | Y1-Yn | Z1-Zn |  |

## Command     Diagnostics

| Y1 | - Yn | =      Device | manufacturer | specific | instruction | for | implementing | various |
|---|---|---|---|---|---|---|---|---|

                     manufacturing or test modes. Y1 - Yn implies that any number of bytes can
                     be used for the VMC data to the peripheral.

| Z1 | - Zn | =      Device | manufacturer | specific | responses | after | receiving | manufacturing | or | test |
|---|---|---|---|---|---|---|---|---|---|---|

                     instructions. Z1 - Zn implies that any number of bytes can be used for the
                     Dispenser response data from the peripheral.

#### 10.4 Dispenser Non-Response Time

      The default maximum non-response time for the dispenser is 5 seconds. This is the
      maximum time for which a dispenser will not respond to a command or a POLL with ACK,
      NAK or a message. The “Application Maximum Response Time” reported in byte Z6 of the
      SETUP (10.3) supersedes this default value if Z6 is greater.

#### 10.5 Dispenser Power Requirements

      The current draw for any dispenser must fall within the following limits. All measurements are
      at the minimum VMC voltage output.

| Idle | mode | = | 200 | mA. | (max.) | continuous |
|---|---|---|---|---|---|---|

                                      Coin payout = 2.5 A. (max.) for up to 15 seconds per coin
                                      dispensed. This is the maximum for all dispensers operating
                                      simultaneously in this unit.

Section 11
   Age Verification Device
   VMC/Peripheral Communication Specifications

#### 11.1 Introduction

Due to legal restrictions, a variety of products are only allowed to be vended via vending machines by
checking the customers age. The age and the rules vary from country to country.

This is i.e. related in some countries to cigarettes or alcoholic products. Some services or product
contents may restrict a different age, related to the vending machine, this needs different ages to be
checked within the same machine.

Age verification may be done with different electronic means, i.e. public cashless systems, which
know the card users age, i.e. biometric systems, i.e. ID-card-readers or driving license readers, etc.

A common and state of the art usage in some countries is a public cashless system working as an
Age Verification Device. Therefore it is good practice to define first an interface of commands as an
addition to the cashless devices.

Second as MDB describes two cashless devices, which in some machines may be both only cashless
readers, it is necessary to define an Age Verification Device only as an additional device, allowing the
two readers within the machine working as before. The cashless readers which run as a multi-
function device may choose to run the additional set of commands or respond as slaves on two
peripheral addresses – the cashless 1 or 2 and the Age Verification Device address.

Therefore this paper describes two additional diagnostic commands for the cashless systems, to work
as age verification devices. Second this paper describes a command set for an age verification
device, which uses only two commands for age verification purpose -- the structure of these two
commands is similar to the cashless diagnostic commands, therefore allowing any VMC, to use the
same command interface for cashless and Age Verification Device as well.

These command are not bound to a cashless-transaction and may be therefore be used, if verification
is done by other cards (i.e. without payment functions.) These command are independent of the
cashless function (i.e. payment out of order, transaction memory full, ...) and do not interfere with the
payment sequences. Sequences at MDB are changed slightly only.

Observing the age verification is done by the VMC. Only the VMC knows, what type of products it
sells. The cashless device delivers the only information to VMC, whether the cashless media finds a
valid age. The cashless device will approve a payment always, when the VMC requests this (MDB
command request vend). The cashless device will not deny a payment, even if the age verification is
not found. This allows simultaneous vend of age protected and free products from a vending
machine.

After each power on or after reception of MDB-Reset the cashless device or Age Verification
Device will ignore age verification. First after the VMC switches on age verification with the
MDB-command “DRAVP“ (Diagnostic Request Age Verification On) and Y4>0, verification
cards will be checked. Only in this case the cashless device or Age Verification Device sends
responses to the second new command “DRAVS” (Diagnostic Response Age Verification
Status) to the VMC.

#### 11.2 VMC Commands

The Age Verification Device uses the MDB address

        `0x68` (the next address after the second cashless device)

It implements a command set similar to a cashless device with a reduced command dictionary. All the
not used commands are reserved for further use to hold the software functions compatible to a
cashless subdevice.

The following describes the age verification commands common to the standalone Age Verification
Device as well as a subdevice within the cashless device, whereas chapter 4 describes the additional
setup commands for the standalone age verification device. Note, that these commands are the same
commands as for a cashless device.

#### 11.2.1 General Format EXPANSION Diagnostic

The MDB command EXPANSION Diagnostic allows transfer of manufacturer specific information
between cashless reader and VMC. For transmission of the age verification information, the
EXPANSION diagnostic command will be used. While implemented in a cashless device, this is
similar to a virtual subdevice within the reader, whereas, when used with a separate address, these
may be treated as normal standardized commands.

General format:

| expansion | Diagnostics | User |
|---|---|---|
| (17H) | (FFH) | Defined |
| (67H) |  | Data |
| (6FH) | Y1 | Y2-Yn |

## Y1 :           Diagnostics.

                              Device manufacturer specific instruction for implementing various
                              manufacturing or test modes.

| Y2-Yn | :        User | Defined | Data. |
|---|---|---|---|

                              The data portion of this command is defined by the manufacturer and
                              is not part of this document.

      Reader response:

| Diagnostics | User |
|---|---|
| Response | Defined |

## (Ffh)

| Z1 | Z2-Zn |
|---|---|

## Z1 :        Diagnostics Response

| Z2-Zn | :     User | Defined | Data. |
|---|---|---|---|

                          The data portion of this response is defined by the manufacturer and
                          is not part of this document.

#### 11.2.2 Switch On / Off of Age Verification

Diagnostic Request Age Verification On/Off (DRAVP)

This command is used to switch On or Off the age verification and to setup the minimum testing age
within the device. While in state “on“ each inserted media is checked and the result is messaged to
the VMC.

After the VMC is powered on, the command DRAVP will be sent at least with Y4 = `0x00` or Y4 = `0xff`
to the age verification device.

| Expansion | Diagnostics | Age verifi- | Length | Age | Ident |
|---|---|---|---|---|---|
|  | Request | cation On/Off |  |  |  |
| (17H) | (FFH) | (0x05) |  |  |  |
| (67H) | Y1 | Y2 | Y3 | Y4 | Y5-Y9 |

## (6Fh)

| Diagnostics | Age verifi- | Length | Feature | byte | Ident |
|---|---|---|---|---|---|
| Response | cation On/Off |  |  |  |  |
| (FFH) | (0x05) |  |  |  |  |

## Z1               Z2               Z3              Z4               Z5-Z9

| Y1 | :       DIAGNOSTICS Request |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|
| Y2 | :       Age verification on/off |  |  |  |  |  |  |
| Y3 | :       Length, the number of bytes | of | this | command, | not | including | Y1-Y3, |

                            therefore set to 6.
| Y4 | Age |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|
|  | Y4 = | 0x00 | Switch | off | age | verification. | Additionally | informs | the |

                                         card reader, that the VMC software supports age
                                         verification, but age verification is not necessary for
                                         any product
                            `0x00`<Y4<`0x64` Level for age verification (`0x01` - `0x63` = 1..99
                                         years). Additionally informs the card reader, that the
                                         VMC software supports age verification and age
                                         verification is necessary
                            `0x63`<Y4<`0xFF` Reserved for future use
| Y4 | = 0xFF | Informs | the | card | reader, | that | the | VMC | software |
|---|---|---|---|---|---|---|---|---|---|

                                              supports age verification and that age verification
                                              will be switched on at xx.xx.xxxx automatically and
                                              the level of age will be changed to the default
                                              checking.
| Y5-Y9 | Ident | “DRAVP” | (hex | 0x44 | 0x52 | 0x41 | 0x56 | 0x50) |
|---|---|---|---|---|---|---|---|---|

                            Used to prevent misinterpretation of this command and to separate it
                            against possible other manufacturer defined 17 FF 05 commands.

The Age Verification Device takes the given age and responses with the diagnostic response. The
VMC will detect, that an Age Verification Device is connected (or built in as a subdevice in cashless),
which is doing age verification.

As the verification of the requested minimum age is depending of the (later) inserted media, the
requested minimum age is only set to the age verification device. Whether a verification is really
possible, will be messaged later within the DRAVS command.

The DRAVP command will be sent by VMC always after power up and after each RESET within the
known initializing sequence to the Age Verification Device (cashless or stand alone). If the VMC is
aware of a necessary age, the minimum age will be set to a value > 0, i.e. for today’s cigarette vendor
to `0x12` = 18.

If different products with different age levels are sold, the VMC may send this command before each
vend transaction and temporarily change age due to selected product minimum age. Switch off of the
age verification is only allowed, if all selections of the vendor do not require a verification.

The age verification device responds with:

| Z1 | :       DIAGNOSTICS Response |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|
| Z2 | :       Age verification on/off |  |  |  |  |  |  |
| Z3 | :       Length, the number of bytes | of | this | command, | not | including | Z1-Z3, |

                            therefore set to 6.
| Z4 | Feature | Byte |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  | b0 = 0 |  | A | customer | card | is | not | in | reading | position, | but | may |

                                              be inserted (refer to b7)
| b0 = 1 | A customer card is in reading position. |  |  |
|---|---|---|---|
| b1...b6 | Reserved, should be set to 0 |  |  |
| b7= 0 | A customer card is not inserted |  |  |
| b7= 1 | A customer card is inserted, but may not | be | in |

                                              reading position (refer to b0)

| Z5-Z9 | Ident | “DRAVP” | (hex | 0x44 | 0x52 | 0x41 | 0x56 | 0x50) |
|---|---|---|---|---|---|---|---|---|

#### 11.2.3 Check of Age Verification

Diagnostic Request Age Verification Status (DRAVS)

If the VMC activated the age verification with DRAVP, the Age Verification Device is checking each
inserted media for age information and sends after insertion the DRAVS response to the VMC. The
VMC may send the command itself to the age verification device, to get an actualisation of the status.
The verification device answers with the actual response. The command may be sent in all MDB
states (especially within cashless devices).

| expansion | Diagnostics | Age verifi- | length | Features | Ident |
|---|---|---|---|---|---|
|  | Request | cation Status |  |  |  |
| (17H) | (FFH) | (0x06) |  |  |  |
| (67H) | Y1 | Y2 | Y3 | Y4 | Y5-Y9 |

## (6Fh)

| Y1 | :     DIAGNOSTICS Request |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|
| Y2 | :     Age Information |  |  |  |  |  |  |  |  |
| Y3 | :     length, the number of | bytes | of | this | command, | not | including | Y1-Y3, | therefore |

                set to 6
| Y4 | Feature | bits |  |  |  |  |
|---|---|---|---|---|---|---|
|  | b0..b7: | Reserved, | should | be | set | to |

| Y5-Y9 | Ident | “DRAVS” | (hex | 0x44 | 0x52 | 0x41 | 0x56 | 0x53) |
|---|---|---|---|---|---|---|---|---|

If the VMC has activated the age verification with the DRAVP, each inserted media will be checked
for age information and after insertion, the DRAVS response will be sent to the VMC.

| Diagnostics | Age | length | feature | byte | 1 feature | byte | 2 Ident |
|---|---|---|---|---|---|---|---|
| Response | (0x06) |  |  |  |  |  |  |

## (Ffh)

| Z1 | Z2 | Z3 | Z4 | Z5 | Z6-Z10 |
|---|---|---|---|---|---|

| Z1 | :     DIAGNOSTICS Response |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|
| Z2 | :     Age verification status |  |  |  |  |  |  |  |
| Z3 | :     length, the number of bytes | of | this | command, | not | including | Z1-Z3, | therefore |

               set to 7

| b0=0: | A customer card is not in reading position, but may be |
|---|---|
| b0=1: | A customer card is in reading position |
| b1=0: | Age information is not available on the customer card |
| b1=1: | Age information is available on the customer card |
| b2=0: | Age verification is not possible (MSAM error or no MSAM) |
| b2=1: | Age verification is possible (MSAM ok and present) |
| b3=0: | The age level from DRAVP command can’t be checked |
| b3=1: | The age level from DRAVP command (or a higher value) can |

                             be checked
| b4=0: | The | customer | is | not | allowed | to | buy | the | product, | because | the |
|---|---|---|---|---|---|---|---|---|---|---|---|

                             age information on the card is less than the value in DRAVP
| b4=1: | The | customer | is | allowed | to | buy | the | product, | because | the | age |
|---|---|---|---|---|---|---|---|---|---|---|---|

                             information on the customer card is equal or greater than the
                             value in DRAVP
| b5=0: | reserved, should | be set to zero |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|
| b6=0: | Age verification | information *) | is | valid |  |  |  |  |  |
| b6=1: | Age verification | information *) | is | invalid | and | set | to | 0, | because |

                             age verification is under progress (busy)
| b7=0: | A | customer | card | is | not inserted |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|
| b7=1: | A | customer | card | is | inserted, but | may | not | be | in | reading |

                             position (refer to b0)

| b0…b3: | Reserved, | should | be | set | to |
|---|---|---|---|---|---|

| b4=1: | Age | verification | done | by | private | ident | media |
|---|---|---|---|---|---|---|---|

| b5=1: | Age | verification | done | by | private ident media 2 |
|---|---|---|---|---|---|
| b6=1: | Age | verification | done | by | driving license reader |
| b7=1: | Age | verification | done | by | public cash card |

| Z6- | Ident | “DRAVS” | (hex | 0x44 | 0x52 | 0x41 | 0x56 | 0x53) |
|---|---|---|---|---|---|---|---|---|

        Z10

*) Age verification information refers to feature byte 1 (b1…b4) and feature byte 2 (all bits)

**) must be valid only, if age verification is positively checked (b4=1 of feature byte 1)

If a DRAVS response with positive checked age information sent from the age verification device, the
VMC will enable the vend for selected product for typically 30 seconds. This duration should be
programmable.

#### 11.3 MDB Interface

#### 11.3.1 MDB initializing

The general MDB-session consists of the known init-sequence as well as the polling sequence. The
init sequence is extended with the DRAVP command.

RESET – `10h`

POLL – `12h`
      To obtain “JUST RESET” response

SETUP CONFIGURATION DATA – 11 `00h`
      To send the VMC’s configuration data and obtain the reader’s data

SETUP MAX/MIN PRICE – 11 `01h`
      To send the maximum and minimum prices in the VMC. (Reader Level 01/02 syntax, 16 bit
      credit).

EXPANSION REQUEST ID – 17 `00h`
     To obtain additional reader information and options (options in Level 03+ only)

EXPANSION ENABLE OPTIONS – 17 `04h` (Level 03+ only)
     To enable desired options

SETUP MAX/MIN PRICE – 11 `01h` (Level 03+ and option bits 1 & 2 only)
      To send the maximum and minimum prices in the VMC. (Reader Level 03+, 32 bit credit).

| DRAVP | – 17 | ff | 05 | 06 | Age | ‘D’ | ‘R’ | ‘A’ | ‘V’ | ‘P’ | *) |
|---|---|---|---|---|---|---|---|---|---|---|---|

     switch on or off youth protection, set age level to be checked
POLL – `12h`
      To obtain “DRAVP” response
**)

READER ENABLE – 14 `01h`
     To enable reader (if desired)

POLL – `12h`
      To obtain further responses, loop it.

*) the DRAVP may be sent in the following contents as often as needed, to switch on or off the verification or to
change the verification age.

**) the cashless reader as well as the Age Verification Device are required to check the actual date and it is
suggested for the VMC, to send an expansion diagnostic date/time command to actualize the date within the age
verification device.

#### 11.3.2 MDB Polling Loop, Vend Sequence

The polling loop will lead to a vend following the known sequence and is extended with an optional

## Dravs.

Customer inserts card

POLL – `12h`
      DRAVS, card present, age verification status
POLL – `12h`
| Begin | Session | (value | = 0, | > 0 | or | –1). | *) |
|---|---|---|---|---|---|---|---|

Customer presses selection and/or inserts money.

| VEND | REQUEST | – 13 | 00 | xx | xx | xx | xx | yy | yyh | **) |
|---|---|---|---|---|---|---|---|---|---|---|

      ACK (xx = vend price, yy = selection number)

POLL – `12h`
      looped until vend approved or denied is sent. During this loop, display messages should be
      shown on the vending machines display

| VEND | SUCCESS/FAILED | – 13 | 02 | yy | yyh | or | 13 | 03h | **) |
|---|---|---|---|---|---|---|---|---|---|

      vend is completed

## Session Complete – 13 04

      close session

POLL – `12h`
      End session

*) only if cashless is used, independent of cashless credit

**) only if cashless payment is done

All answer will be seen in the known format, the new command DRAVS is enabling a cash vend, if
the "age valid" (b4 = 1) is set.

#### 11.4 Age Verification Device Command/Response Formats

#### 11.4.1 Reset

## Reset

## (68H)

Reader response:

 No Data response

#### 11.4.2 Setup

|  | Config | VMC | Columns | Rows | Display |
|---|---|---|---|---|---|
| SETUP | Data | Feature | on | On | Info |
| (69H) | (00H) | Level | Display | Display |  |

## Y1                 Y2            Y3               Y4                Y5

| Y1 | :         Configuration | data. |
|---|---|---|

                      VMC is sending its configuration data to reader.
| Y2 | :         VMC | Feature | Level. |
|---|---|---|---|

                      Indicates the feature level of the VMC. The available feature levels are:
                        01 – the actual used level is 1
| Y3 | :         Columns | on | Display. | The | number | of | columns | on | the | display. | Set | to | 00H | if | the | display | is |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                      not available to the reader.
| Y4 | :         Rows | on | Display. |
|---|---|---|---|

                      The number of rows on the display
| Y5 | :         Display Information - xxxxxyyy |  |  |  |  |  |
|---|---|---|---|---|---|---|
|  | xxxxx =      Unused |  |  |  |  |  |
|  | yyy =        Display type |  |  |  |  |  |
|  | 000 :        Numbers, upper case | letters, | blank | and | decimal | point. |
|  | 001 :        Full ASCII |  |  |  |  |  |
|  | 010-111:     Unassigned |  |  |  |  |  |

Reader Response:

| Reader | Reader | Country | Country | Scale | Decimal | Application | Miscellaneous |
|---|---|---|---|---|---|---|---|
| Config | Feature | Code | Code | Factor | Places | Maximum | Options |
| Data | Level | High | Low |  |  | Response |  |
| (01H) |  |  |  |  |  | Time |  |
| Z1 | Z2 | Z3 | Z4 | Z5 | Z6 | Z7 | Z8 |

| Z1 | :         READER | - Configuration | data. |
|---|---|---|---|

                      Indicates the Age Verification Device is responding to a SETUP – Configuration data
                      request from the VMC.

| Z2 : | 01 – the | actual used level |  |
|---|---|---|---|
| Z3-Z4 | :   Country / | Currency Code - packed | BCD. |

                 The packed BCD country / currency code of the reader can be sent in two different forms
                 depending on the value of the left most BCD digit.
                 If the left most digit is a 0, the International Telephone Code is used to indicate the
                 country that the reader is set-up for. For example, the USA code is 00 01H (Z3 = 00 and

## Z4 = 01).

                 If the left most digit is a 1, the latest version of the ISO 4217 numeric currency code is
                 used (see Appendix A1). For example, the code for the US dollar is 18 40H (Z2 = 18
                 and Z3 = 40) and for the Euro is 1978 (Z3 = 19 and Z4 = 78). Use FFFFh if the country
                 code in unknown.
                 For level 3 cashless readers, it is mandatory to use the ISO 4217 numeric currency code
                 (see Appendix A1).

| Z5 | :      Scale | Factor. |
|---|---|---|

                 The multiplier used to scale all monetary values transferred between the VMC and the
                 reader.
| Z6 | :      Decimal | Places. |
|---|---|---|

                 The number of decimal places used to communicate monetary values between the VMC
                 and the age verification device.

                 All pricing information sent between the VMC and the Age Verification Device is scaled
                 using the scale factor and decimal places. This corresponds to:
                                          ActualPrice = P ⋅ X ⋅ 10 − Y
                 where P is the scaled value send in the price bytes, and X is the scale factor, and Y is
                 the number of decimal places. For example if there are 2 decimal places and the scale
                 factor is 5, then a scaled price of 7 will mean an actual of 0.35.
| Z7 | :      Application | Maximum | Response | Time | - seconds. |
|---|---|---|---|---|---|

                 The maximum length of time a reader will require to provide a response to any command
                 from the VMC. The value reported here supersedes the payment reader’s default NON-
                 RESPONSE time defined in section 7.5 if the value reported here is greater.
| Z8 | :      Miscellaneous | Options | – xxxxyyyy |
|---|---|---|---|

#### 11.4.3 Poll

   POLL

## (6Ah)

The POLL command is used by the VMC to obtain information from the verification device. In addition
to an ACK, the VMC may receive the following POLL responses from the verification device.

Reader responses:

Just
Reset

## (00H)

Z1

## Z1 :              Just Reset

                            Indicates the device has been reset.
                            Note: the difference between ACK and JUST RESET responses is:

## 00H 00H*       =Just Reset

## 00H*           =Ack

                                                                 *mode bit=1

| Reader | Reader | Country | Country | Scale | Decimal | Application | Miscellaneous |
|---|---|---|---|---|---|---|---|
| Config | Feature | Code | Code | Factor | Places | Maximum | Options |
| Info | Level | High | Low |  |  | Response |  |
| (01H) |  |  |  |  |  | Time |  |
| Z1 | Z2 | Z3 | Z4 | Z5 | Z6 | Z7 | Z8 |

| Display | Display | Display |
|---|---|---|
| Request | Time | Data |

## (02H)

## Z1               Z2           Z3-Z34

## Z1 :             Display Request

                           The Age Verification Device is requesting a message to be displayed on the VMC’s
                           display.
| Z2 | :             Display | Time | - 0.1 | second | units |
|---|---|---|---|---|---|

                           The requested display time. Either the VMC or the Age Verification Device may
                           overwrite the message before the time has expired.

| Peripheral | Manufacturer | Serial | Model | Software | Optional |
|---|---|---|---|---|---|
| ID | Code | Number | Number | Version | Feature bits |

## (09H)

| Z1                 Z2-Z4 | Z5-Z16 | Z17-Z28 | Z29-Z30 | Z31 | - Z34 |
|---|---|---|---|---|---|

## Z1 :           Peripheral Id

                         Age Verification Device is sending peripheral ID information.
| Z2 | - Z4 | :      Manufacturer | Code | - ASCII |
|---|---|---|---|---|

                         Identification code for the equipment supplier. Currently defined codes are listed in
                         the EVA document entitled "European Vending Association Data Transfer
                         Standard" (EVA-DTS), the Audit Data
                         Lists section, sub-section 2, "Manufacturer Codes".
| Z5-Z16 | :       Serial | Number | – ASCII |
|---|---|---|---|

                         Factory assigned serial number.
| Z17-Z28 | :      Model | Number | - ASCII |
|---|---|---|---|

                         Manufacturer assigned model number.
| Z29-Z30 | :      Software | Version | - packed | BCD |
|---|---|---|---|---|

                         Current software version.
| Z31- | Z34 | Optional | Feature | Bits. | Each | of | the | 32 | bits | indicate | an | optional | feature | availability. |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                         Bits should be sent in descending order, i.e. bit 31 is sent first and bit 0 is sent last.
                         Options must be enabled by the VMC using the Expansion Optional Feature Bit
                         Enable (17H-04H) command and all features are disabled after a reset. Currently
                         defined options are:
                         b0 - File Transport Layer supported

                         b1 to b31 not used (should be set to 0)

| Malfunction | / Error | Error | Code |
|---|---|---|---|

## (0Ah)

## Z1                         Z2

## Z1 :        Malfunction/Error

                      The Age Verification Device is reporting a malfunction or error.

| Z2 | :        Error | Code | - xxxxyyyy |
|---|---|---|---|

        Transient Error Handling
        The error will be reported to the VMC until it has been ACKnowledged. The error state will be
        cleared in the age verification device, and normal operations will continue.

        Non-transient Error Handling
        The error will be reported to the VMC at each POLL as long as it exists. If the Age Verification
        Device is still functional, multi-message responses will allow normal responses in addition to
        the error report.

Time/Date
Request

## (11H)

Z1

## Z1 :           Time Date Request

                         In certain circumstances it will be necessary to synchronize the real time clock of the
                         Age Verification Device with real time clock of the VMC. The Age Verification Device
                         will respond with TIME/DATE REQUEST to a POLL command of the VMC. The VMC
                         will follow with the EXPANSION-WRITE TIME/DATE FILE to the age verification
                         device.

#### 11.4.4 Expansion commands (request ID)

|  | Request | Manufacturer | Serial | Model | Software |
|---|---|---|---|---|---|
| Expansion | ID | Code | Number | Number | Version |

## (6Fh)            (00H)

## Y1            Y2-Y4             Y5-Y16      Y17-Y28        Y29-Y30

## Y1 :             Request Id

                           The VMC is requesting Age Verification Device identification information. The
                           information included above (Y2-Y30) provides the Age Verification Device with VMC
                           identification information.
| Y2-Y4 | :          Manufacturer | Code | - ASCII |
|---|---|---|---|

                           Identification code for the equipment supplier. Currently defined codes are listed in
                           the EVA document entitled “The Data Transfer Standard EVA-DTS" document, the
                           Audit Data Dictionary section, chapter 4, "Manufacturer Codes".
| Y5-Y16 | :         Serial | Number | - ASCII |
|---|---|---|---|

                           Factory assigned serial number.
| Y17-Y28 | :        Model | Number | - ASCII |
|---|---|---|---|

                           Manufacturer assigned model number.
| Y29-Y30 | :        Software | Version | - packed | BCD |
|---|---|---|---|---|

                           Current software version.

Age Verification Device response:

| Peripheral | Manufacture | Serial | Model | Software | Optional |
|---|---|---|---|---|---|
| ID | Code | Number | Number | Version | Feature Bits |

## (09H)

| Z1               Z2-Z4 | Z5-Z16 | Z17-Z28 | Z29-Z30 | Z31-Z34 |
|---|---|---|---|---|

#### 11.4.5 EXPANSION - Write Time/Date File

| Expansion | Write Time/ | Time |
|---|---|---|
| (6FH) | Date File | Date |

## (03H)

## Y1                Y2-Y11

## Y1 :          Write Time/Date File

                      The VMC requests to write the Time/Date file.
| Y2- | Y11: | Time/Date | to | synchronize | the | Age | Verification | Device | real | time | clock. | The | date | bytes |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                      are BCD encoded.

                      Y2 = Years (Range: 00..99)
                      Y3 = Months (Range: 01..12)
                      Y4 = Days (Range: 01..31)
                      Y5 = Hours (Range: 00..23)
                      Y6 = Minutes (Range: 00..59)
                      Y7 = Seconds (Range: 00..59)
                      Y8 = Day of Week (Range: 01..07, Monday = 1..Sunday = 7)
                      Y9 = Week Number (Range: 01..53)
                      Y10 = Summertime (Range: 00..01, Summertime = 1)
                      Y11 = Holiday (Range: 00..01, Holiday = 1)
                      If any item of the time/date is not supported use FFH instead.

#### 11.4.6 EXPANSION - Diagnostics

| Expansion | Diagnostics | User |
|---|---|---|
| (6FH) | (FFH) | Defined |

                                 Data
| Y1 | Y2-Yn |
|---|---|

## Y1 :        Diagnostics.

                    Device manufacturer specific instruction for implementing various manufacturing or test
                    modes.
| Y2-Yn | :     User | Defined | Data. |
|---|---|---|---|

                    The data portion of this command is defined by the manufacturer and is not part of this
                    document.

Age Verification Device response:

| Diagnostics | User |
|---|---|
| Response | Defined |

## (Ffh)

| Z1                Z2-Zn |
|---|

## Z1 :        Diagnostics Response.

| Z2-Zn | :     User | Defined | Data. |
|---|---|---|---|

                    The data portion of this response is defined by the manufacturer and is not part of this
                    document.

#### 11.5 Age Verification Device Non-Response Time

      The default maximum non-response time for the Age Verification Device is 5 seconds. This
      is the maximum time for which an Age Verification Device will not respond to a command or a
      POLL with ACK, NAK or a message. The “Application Maximum Response Time” reported in
      byte Z7 of the Age Verification Device Configuration Data supersedes this default value if Z7
      is greater.
      .

#### 11.6 Age Verification Device Power Requirements

      The current draw for any Age Verification Device must fall within the following limits. All
      measurements are at the minimum VMC Voltage Output.

      Idle mode = 300 mA. (avg.) continuous

      Transport or Read/Write cycle = 1.5 A @ 50% maximum duty cycle up to 5 seconds.

 Appendix 1
Currency Codes

A1.1 Information

The following Tables of Codes for the Representation of Currencies and Funds are
provided by the Secretariat of ISO 4217 MA. It is provided here to be used for the MDB
currency code information sent between the credit peripherals and the VMC.

       Table A.1 Currency and Funds Code List (English alphabetical order by entity)

       Table A.2 Funds Codes Registered with the Maintenance Agency

       Table A.3 Codes for Historic Denominations of Currencies and Funds

A1.2 MDB/ICP Use

As stated in the individual credit device sections, the two byte, packed BCD country / currency
code of the coin changer, bill validator, and card reader devices can be sent in two different
forms depending on the value of the left most BCD digit.

If the left most digit is a 0, the International Telephone Code is used to indicate the country
that the reader is set-up for.

       For example, the USA telephone code is 001 which translates into the
       MDB code as 00 `01h` (Zx = `00h` and Zy = `01h`).

If the left most digit is a 1, the latest version of the ISO 4217 numeric currency code is used as
listed in this Appendix.

       For example, the code for the US dollar is 840 which translates into the
       MDB code as 18 `40h` (Zx = `18h` and Zy = `40h`).
       The code for the Euro is 978 which translates into the MDB code
       as 1978h (Zx = `19h` and Zy = `78h`).
       FFFFh should be used if the country code in unknown (Zx = `FFh` and Zy = `FFh`).

Note that for level 3 cashless readers, it is mandatory to use the the ISO 4217 numeric
currency code.

Table A.1 Currency and Funds Code List (English alphabetical order by
     entity)

| ENTITY | Currency | Code |  | Decimal |
|---|---|---|---|---|
|  |  | Alphabetic | Numeric | Position |

__________________________________________________________________________________

| AFGHANISTAN | Afghani | AFA | 004 | 2 |
|---|---|---|---|---|
| ALBANIA | Lek | ALL | 008 | 2 |
| ALGERIA | Algerian Dinar | DZD | 012 | 2 |
| AMERICAN SAMOA | US Dollar | USD | 840 | 2 |
| ANDORRA | Spanish Peseta | ESP | 724 | 0 |
|  | French Franc | FRF | 250 | 2 |
|  | Andorran Peseta | ADP | 020 | 0 |
| ANGOLA | New Kwanza | AON | 024 | 2 |
|  | Kwanza Reajustado | AOR | 982 | 2 |
| ANGUILLA | East Caribbean | XCD | 951 | 2 |

                                  Dollar
| ANTARCTICA | No | universal |
|---|---|---|

                                  currency
| ANTIGUA AND | East Caribbean | XCD | 951 | 2 |
|---|---|---|---|---|
| BARBUDA | Dollar |  |  |  |
| ARGENTINA | Argentine Peso | ARS | 032 | 2 |
| ARMENIA | Armenian Dram | AMD | 051 | 2 |
| ARUBA | Aruban Guilder | AWG | 533 | 2 |
| AUSTRALIA | Australian Dollar | AUD | 036 | 2 |
| AUSTRIA | Schilling | ATS | 040 | 2 |
| AZERBAIJAN | Azerbaijanian Manat | AZM | 031 | 2 |
| BAHAMAS | Bahamian Dollar | BSD | 044 | 2 |
| BAHRAIN | Bahraini Dinar | BHD | 048 | 3 |
| BANGLADESH | Taka | BDT | 050 | 2 |
| BARBADOS | Barbados Dollar | BBD | 052 | 2 |
| BELARUS | Belarussian Ruble | BYB | 112 | 0 |
|  | Belarussian Ruble | BYR | 974 | 0 |
| BELGIUM | Belgian Franc | BEF | 056 | 0 |
| BELIZE | Belize Dollar | BZD | 084 | 2 |
| BENIN | CFA Franc BCEAO+ | XOF | 952 | 0 |
| BERMUDA | Bermudian Dollar | BMD | 060 | 2 |

                                  (customarily known
                                   as Bermuda Dollar)
| BHUTAN | Indian Rupee | INR | 356 | 2 |
|---|---|---|---|---|
|  | Ngultrum | BTN | 064 | 2 |

__________________________________________________________________________________

+ CFA Franc BCEAO; Responsible authority: Banque Centrale des Etats de
  l'Afrique de l'Ouest.

Table A.1 (Continued)
_________________________________________________________________________________

| ENTITY | Currency | Code |  | Decimal |
|---|---|---|---|---|
|  |  | Alphabetic | Numeric | Position |

__________________________________________________________________________________

| BOLIVIA | Boliviano | BOB | 068 | 2 |
|---|---|---|---|---|
|  | Mvdol* | BOV | 984 | 2 |
| BOSNIA & HERZEGOVINA | Convertible Marks | BAM | 977 | 2 |
| BOTSWANA | Pula | BWP | 072 | 2 |
| BOUVET ISLAND | Norwegian Krone | NOK | 578 | 2 |
| BRAZIL | Brazilian Real | BRL | 986 | 2 |
| BRITISH INDIAN | US Dollar | USD | 840 | 2 |

## Ocean Territory

| BRUNEI DARUSSALAM | Brunei Dollar | BND | 096 | 2 |
|---|---|---|---|---|
| BULGARIA | Lev | BGL | 100 | 2 |
|  | Bulgarian LEV | BGN | 975 | 2 |
| BURKINA FASO | CFA Franc BCEAO+ | XOF | 952 | 0 |
| BURUNDI | Burundi Franc | BIF | 108 | 0 |
| CAMBODIA | Riel | KHR | 116 | 2 |

| CAMEROON | CFA Franc BEAC# | XAF | 950 | 0 |
|---|---|---|---|---|
| CANADA | Canadian Dollar | CAD | 124 | 2 |
| CAPE VERDE | Cape Verde Escudo | CVE | 132 | 2 |
| CAYMAN ISLANDS | Cayman Islands | KYD | 136 | 2 |

                                     Dollar
| CENTRAL | AFRICAN | CFA | Franc | BEAC# | XAF | 950 | 0 |
|---|---|---|---|---|---|---|---|

## Republic

| CHAD | CFA Franc BEAC# | XAF | 950 | 0 |
|---|---|---|---|---|
| CHILE | Chilean Peso | CLP | 152 | 0 |
|  | Unidades de | CLF | 990 | 0 |

                                     fomento*
| CHINA | Yuan Renminbi | CNY | 156 | 2 |
|---|---|---|---|---|
| CHRISTMAS ISLAND | Australian Dollar | AUD | 036 | 2 |
| COCOS (KEELING) | Australian Dollar | AUD | 036 | 2 |

## Islands

| COLOMBIA | Colombian Peso | COP | 170 | 2 |
|---|---|---|---|---|
| COMOROS | Comoro Franc | KMF | 174 | 0 |

_____________________________________________________________________________
+ CFA Franc BCEAO; Responsible authority: Banque Centrale des Etats de
  l'Afrique de l'Ouest.

# CFA Franc BEAC; Responsible authority: Banque des Etats de l'Afrique
  Centrale.

- Funds code [See table A.2(E) for definitions of funds types].

Table A.1 (Continued)
_________________________________________________________________________________

| ENTITY | Currency | Code |  | Decimal |
|---|---|---|---|---|
|  |  | Alphabetic | Numeric | Position |

_________________________________________________________________________________

| CONGO |  |  | CFA Franc BEAC# | XAF | 950 | 0 |
|---|---|---|---|---|---|---|
| CONGO, | THE | DEMOCRATIC | Franc Congolais | CDF | 976 | 2 |

## Republic Of

| COOK ISLANDS | New Zealand Dollar | NZD | 554 | 2 |
|---|---|---|---|---|
| COSTA RICA | Costa Rican Colon | CRC | 188 | 2 |
| COTE D'IVOIRE | CFA Franc BCEAO+ | XOF | 952 | 0 |
| CROATIA | Kuna | HRK | 191 | 2 |
| CUBA | Cuban Peso | CUP | 192 | 2 |
| CYPRUS | Cyprus Pound | CYP | 196 | 2 |
| CZECH REPUBLIC | Czech Koruna | CZK | 203 | 2 |
| DENMARK | Danish Krone | DKK | 208 | 2 |
| DJIBOUTI | Djibouti Franc | DJF | 262 | 0 |
| DOMINICA | East Caribbean | XCD | 951 | 2 |

                                Dollar
| DOMINICAN REPUBLIC | Dominican Peso | DOP | 214 | 2 |
|---|---|---|---|---|
| EAST TIMOR | Timor Escudo | TPE | 626 | 0 |
|  | Rupiah | IDR | 360 | 2 |
| ECUADOR | US Dollar | ESD | 840 | 2 |
| EGYPT | Egyptian Pound | EGP | 818 | 2 |
| EL SALVADOR | El Salvador Colon | SVC | 222 | 2 |
| EQUATORIAL GUINEA | CFA Franc BEAC# | XAF | 950 | 0 |
| ESTONIA | Kroon | EEK | 233 | 2 |
| ERITREA | Nakfa | ERN | 232 | 2 |
| ETHIOPIA | Ethiopian Birr | ETB | 230 | 2 |
| FAEROE ISLANDS | Danish Krone | DKK | 208 | 2 |
| FALKLAND ISLANDS | Falkland Islands |  |  |  |
| (MALVINAS) | Pound | FKP | 238 | 2 |

_____________________________________________________________________________
# CFA Franc BEAC; Responsible authority: Banque des Etats de l'Afrique
  Centrale.

+ CFA Franc BCEAO; Responsible authority: Banque Centrale des Etats de
  l'Afrique de l'Ouest.

- Funds code [see Table A.2 (E) for definitions of funds types].

Table A.1 (Continued)
________________________________________________________________________________

| ENTITY | Currency | Code |  | Decimal |
|---|---|---|---|---|
|  |  | Alphabetic | Numeric | Position |

________________________________________________________________________________

| FIJI | Fiji Dollar | FJD | 242 | 2 |
|---|---|---|---|---|
| FINLAND | Markka | FIM | 246 | 2 |
| FRANCE | French Franc | FRF | 250 | 2 |
| FRENCH GUIANA | French Franc | FRF | 250 | 2 |
| FRENCH POLYNESIA | CFP Franc | XPF | 953 | 0 |
| FRENCH SOUTHERN | French Franc | FRF | 250 | 2 |

## Territories

| GABON | CFA Franc BEAC# | XAF | 950 | 0 |
|---|---|---|---|---|
| GAMBIA | Dalasi | GMD | 270 | 2 |
| GEORGIA | Lari | GEL | 981 | 2 |
| GERMANY | Deutsche Mark | DEM | 276 | 2 |
| GHANA | Cedi | GHC | 288 | 2 |
| GIBRALTAR | Gibraltar Pound | GIP | 292 | 2 |
| GREECE | Drachma | GRD | 300 | 2 |
| GREENLAND | Danish Krone | DKK | 208 | 2 |
| GRENADA | East Caribbean | XCD | 951 | 2 |

                                 Dollar
| GUADELOUPE | French Franc | FRF | 250 | 2 |
|---|---|---|---|---|
| GUAM | US Dollar | USD | 840 | 2 |
| GUATEMALA | Quetzal | GTQ | 320 | 2 |
| GUINEA | Guinea Franc | GNF | 324 | 0 |
| GUINEA-BISSAU | Guinea-Bissau Peso | GWP | 624 | 2 |
|  | CFA Franc BCEAO+ | XOF | 952 | 0 |
| GUYANA | Guyana Dollar | GYD | 328 | 2 |
| HAITI | Gourde | HTG | 332 | 2 |
|  | US Dollar | USD | 840 | 2 |
| HEARD AND | Australian Dollar | AUD | 036 | 2 |

## Mcdonald Islands

| HONDURAS | Lempira | HNL | 340 | 2 |
|---|---|---|---|---|

_____________________________________________________________________________

# CFA Franc BEAC; Responsible authority: Banque des Etats de l'Afrique
  Centrale.
+ CFA Franc BCEAO; Responsible authority: Banque Centrale des Etats de
  l'Afrique de l'Ouest.

Table A.1 (Continued)
_______________________________________________________________________________

| ENTITY | Currency | Code |  | Decimal |
|---|---|---|---|---|
|  |  | Alphabetic | Numeric | Point |

________________________________________________________________________________

| HONG KONG | Hong Kong Dollar | HKD | 344 | 2 |
|---|---|---|---|---|
| HUNGARY | Forint | HUF | 348 | 2 |
| ICELAND | Iceland Krona | ISK | 352 | 2 |
| INDIA | Indian Rupee | INR | 356 | 2 |
| INDONESIA | Rupiah | IDR | 360 | 2 |
| INTERNATIONAL | SDR | XDR | 960 | N.A. |

## Monetary Fund

## (Imf)**

| IRAN | (ISLAMIC | Iranian | Rial | IRR | 364 | 2 |
|---|---|---|---|---|---|---|

## Republic Of)

| IRAQ | Iraqi Dinar | IQD | 368 | 3 |
|---|---|---|---|---|
| IRELAND | Irish Pound | IEP | 372 | 2 |
| ISRAEL | New Israeli Sheqel* | ILS | 376 | 2 |
| ITALY | Italian Lira | ITL | 380 | 0 |
| JAMAICA | Jamaican Dollar | JMD | 388 | 2 |
| JAPAN | Yen | JPY | 392 | 0 |
| JORDAN | Jordanian Dinar | JOD | 400 | 3 |
| KAZAKHSTAN | Tenge | KZT | 398 | 2 |
| KENYA | Kenyan Shilling | KES | 404 | 2 |
| KIRIBATI | Australian Dollar | AUD | 036 | 2 |
| KOREA, DEMOCRATIC | North Korean Won | KPW | 408 | 2 |

## People'S Republic Of

| KOREA, | REPUBLIC | OF | Won | KRW | 410 | 0 |
|---|---|---|---|---|---|---|

_____________________________________________________________________________
- Currency name was effective 4th September 1985

** This entry is not derived fron ISO 3166, but is included here in alphabetic
  sequence for convenience.

Table A.1 (Continued)
________________________________________________________________________________

| ENTITY | Currency | Code |  | Decimal |
|---|---|---|---|---|
|  |  | Alphabetic | Numeric | Point |

________________________________________________________________________________

| KUWAIT | Kuwaiti | Dinar | KWD | 414 | 3 |
|---|---|---|---|---|---|
| KYRGYZSTAN | Som |  | KGS | 417 | 2 |
| LAO PEOPLE'S | Kip |  | LAK | 418 | 2 |

## Democratic

## Republic

| LATVIA | Latvian Lats | LVL | 428 | 2 |
|---|---|---|---|---|
| LEBANON | Lebanese Pound | LBP | 422 | 2 |
| LESOTHO | Rand | ZAR | 710 | 2 |
|  | (financial Rand)* | ZAL | 991 | 2 |
|  | Loti | LSL | 426 | 2 |
| LIBERIA | Liberian Dollar | LRD | 430 | 2 |
| LIBYAN ARAB | Libyan Dinar | LYD | 434 | 3 |

## Jamahiriya

| LIECHTENSTEIN | Swiss Franc | CHF | 756 | 2 |
|---|---|---|---|---|
| LITHUANIA | Lithuanian Litas | LTL | 440 | 2 |
| LUXEMBOURG | Luxembourg Franc | LUF | 442 | 0 |
| MACAU | Pataca | MOP | 446 | 2 |
| MACEDONIA, THE | Denar | MKD | 807 | 2 |

## Former Yugoslav

## Republic Of

| MADAGASCAR | Malagasy Franc | MGF | 450 | 0 |
|---|---|---|---|---|
| MALAWI | Kwacha | MWK | 454 | 2 |
| MALAYSIA | Malaysian Ringgit | MYR | 458 | 2 |
| MALDIVES | Rufiyaa | MVR | 462 | 2 |
| MALI | CFA Franc BCEAO+ | XOF | 952 | 0 |
| MALTA | Maltese Lira | MTL | 470 | 2 |
| MARSHALL ISLANDS | US Dollar | USD | 840 | 2 |
| MARTINIQUE | French Franc | FRF | 250 | 2 |
| MAURITANIA | Ouguiya | MRO | 478 | 2 |
| MAURITIUS | Mauritius Rupee | MUR | 480 | 2 |
| MEXICO | Mexican Peso | MXN | 484 | 2 |
|  | Mexican Unidad de | MXV | 979 | 2 |

                                   Inversion (UDI)*
| MICRONESIA |  | US Dollar | USD | 840 | 2 |
|---|---|---|---|---|---|
| MOLDOVA, REPUBLIC | OF | Moldovan Leu | MDL | 498 | 2 |
| MONACO |  | French Franc | FRF | 250 | 2 |

_____________________________________________________________________________
- Funds code [ See table A.2(E) for definitions of funds types].
+ CFA Franc BCEAO; Responsible authority: Banque Centrale des Etats de
  l'Afrique de l'Ouest.

Table A.1 (Continued)
________________________________________________________________________________

| ENTITY | Currency | Code |  | Decimal |
|---|---|---|---|---|
|  |  | Alphabetic | Numeric | Point |

________________________________________________________________________________

| MONGOLIA | Tugrik | MNT | 496 | 2 |
|---|---|---|---|---|
| MONTSERRAT | East Caribbean | XCD | 951 | 2 |

                                    Dollar
| MOROCCO | Moroccan Dirham | MAD | 504 | 2 |
|---|---|---|---|---|
| MOZAMBIQUE | Metical | MZM | 508 | 2 |
| MYANMAR | Kyat | MMK | 104 | 2 |
| NAMIBIA | Rand | ZAR | 710 | 2 |
|  | Namibia Dollar** | NAD | 516 | 2 |
| NAURU | Australian Dollar | AUD | 036 | 2 |
| NEPAL | Nepalese Rupee | NPR | 524 | 2 |
| NETHERLANDS | Netherlands Guilder | NLG | 528 | 2 |
| NETHERLANDS | Netherlands | ANG | 532 | 2 |
| ANTILLES | Antillian Guilder |  |  |  |
| NEW CALEDONIA | CFP Franc | XPF | 953 | 0 |
| NEW ZEALAND | New Zealand Dollar | NZD | 554 | 2 |
| NICARAGUA | Cordoba Oro | NIO | 558 | 2 |
| NIGER | CFA Franc BCEAO+ | XOF | 952 | 0 |
| NIGERIA | Naira | NGN | 566 | 2 |
| NIUE | New Zealand Dollar | NZD | 554 | 2 |
| NORFOLK ISLAND | Australian Dollar | AUD | 036 | 2 |
| NORTHERN MARIANA | US Dollar | USD | 840 | 2 |

## Islands

| NORWAY | Norwegian Krone | NOK | 578 | 2 |
|---|---|---|---|---|
| OMAN | Rial Omani | OMR | 512 | 3 |
| PAKISTAN | Pakistan Rupee | PKR | 586 | 2 |
| PALAU | US Dollar | USD | 840 | 2 |

_____________________________________________________________________________

+ CFA Franc BCEAO; Responsible authority: Banque Centrale des Etats de
  l'Afrique de l'Ouest.

# The lowest unit of recorded value for the Iraqi Dinar is the Dirham
  (1 Iraqi Dinar = 20 Dirhams).

** The Namibia Dollar becomes effective September 15th 1993

Table A.1 (Continued)
______________________________________________________________________________

| ENTITY | Currency | Code |  | Decimal |
|---|---|---|---|---|
|  |  | Alphabetic | Numeric | Point |

________________________________________________________________________________

| PANAMA | Balboa | PAB | 590 | 2 |
|---|---|---|---|---|
|  | US Dollar | USD | 840 | 2 |
| PAPUA NEW GUINEA | Kina | PGK | 598 | 2 |
| PARAGUAY | Guarani | PYG | 600 | 0 |
| PERU | Nuevo Sol | PEN | 604 | 2 |
| PHILIPPINES | Philippine Peso | PHP | 608 | 2 |
| PITCAIRN | New Zealand Dollar | NZD | 554 | 2 |
| POLAND | Zloty | PLN | 985 | 2 |
| PORTUGAL | Portuguese Escudo | PTE | 620 | 0 |
| PUERTO RICO | US Dollar | USD | 840 | 2 |
| QATAR | Qatari Rial | QAR | 634 | 2 |
| REUNION | French Franc | FRF | 250 | 2 |
| ROMANIA | Leu | ROL | 642 | 2 |
| RUSSIAN FEDERATION | Russian Ruble | RUR | 810 | 2 |
|  | Russian Ruble | RUB | 643 | 2 |
| RWANDA | Rwanda Franc | RWF | 646 | 0 |
| ST HELENA | St Helena Pound | SHP | 654 | 2 |
| ST KITTS - NEVIS | East Caribbean | XCD | 951 | 2 |

                              Dollar
| SAINT | LUCIA | East | Caribbean | XCD | 951 | 2 |
|---|---|---|---|---|---|---|

                              Dollar
| ST PIERRE | AND | French | Franc | FRF | 250 | 2 |
|---|---|---|---|---|---|---|

## Miquelon

| SAINT VINCENT | East Caribbean | XCD | 951 | 2 |
|---|---|---|---|---|
| AND THE | Dollar |  |  |  |

## Grenadines

| SAMOA | Tala |  | WST | 882 | 2 |
|---|---|---|---|---|---|
| SAN MARINO | Italian | Lira | ITL | 380 | 0 |
| SAO TOME AND | Dobra |  | STD | 678 | 2 |

## Principe

| SAUDI | ARABIA | Saudi | Riyal | SAR | 682 | 2 |
|---|---|---|---|---|---|---|

_____________________________________________________________________________

Table A.1 (Continued)
________________________________________________________________________________

| ENTITY | Currency | Code |  | Decimal |
|---|---|---|---|---|
|  |  | Alphabetic | Numeric | Point |

________________________________________________________________________________

| SENEGAL | CFA Franc BCEAO+ | XOF | 952 | 0 |
|---|---|---|---|---|
| SEYCHELLES | Seychelles Rupee | SCR | 690 | 2 |
| SIERRA LEONE | Leone | SLL | 694 | 2 |
| SINGAPORE | Singapore Dollar | SGD | 702 | 2 |
| SLOVAKIA | Slovak Koruna | SKK | 703 | 2 |
| SLOVENIA | Tolar | SIT | 705 | 2 |
| SOLOMON ISLANDS | Solomon Islands | SBD | 090 | 2 |

                                 Dollar
| SOMALIA | Somali Shilling | SOS | 706 | 2 |
|---|---|---|---|---|
| SOUTH AFRICA | Rand | ZAR | 710 | 2 |
| SPAIN | Spanish Peseta | ESP | 724 | 0 |
| SRI LANKA | Sri Lanka Rupee | LKR | 144 | 2 |
| SUDAN | Sudanese Dinar | SDD | 736 | 2 |
| SURINAME | Surinam Guilder | SRG | 740 | 2 |
| SVALBARD AND | Norwegian Krone | NOK | 578 | 2 |

## Jan Mayen

## Islands

| SWAZILAND | Lilangeni | SZL | 748 | 2 |
|---|---|---|---|---|
| SWEDEN | Swedish Krona | SEK | 752 | 2 |
| SWITZERLAND | Swiss Franc | CHF | 756 | 2 |
| SYRIAN ARAB | Syrian Pound | SYP | 760 | 2 |

## Republic

| TAIWAN, | PROVINCE | New | Taiwan | Dollar | TWD | 901 | 2 |
|---|---|---|---|---|---|---|---|

## Of China

| TAJIKISTAN | Tajik | Ruble | TJR | 762 | 0 |
|---|---|---|---|---|---|

__________________________________________________________________________________

+ CFA Franc BCEAO; Responsible authority: Banque Centrale des Etats de
  l'Afrique de l'Ouest.

Table A.1 (Continued)
_______________________________________________________________________________

| ENTITY | Currency | Code |  | Decimal |
|---|---|---|---|---|
|  |  | Alphabetic | Numeric | Point |

________________________________________________________________________________

| TANZANIA, | UNITED | Tanzanian | Shilling | TZS | 834 | 2 |
|---|---|---|---|---|---|---|

## Republic Of

| THAILAND | Baht | THB | 764 | 2 |
|---|---|---|---|---|
| TOGO | CFA Franc BCEAO+ | XOF | 952 | 0 |
| TOKELAU | New Zealand Dollar | NZD | 554 | 2 |
| TONGA | Pa'anga | TOP | 776 | 2 |
| TRINIDAD AND | Trinidad and Tobago | TTD | 780 | 2 |
| TOBAGO | Dollar |  |  |  |
| TUNISIA | Tunisian Dinar | TND | 788 | 3 |
| TURKEY | Turkish Lira | TRL | 792 | 0 |
| TURKMENISTAN | Manat | TMM | 795 | 2 |
| TURKS AND CAICOS | US Dollar | USD | 840 | 2 |

## Islands

| TUVALU | Australian Dollar | AUD | 036 | 2 |
|---|---|---|---|---|
| UGANDA | Uganda Shilling ++ | UGX | 800 | 0 |
| UKRAINE | Hryvnia | UAH | 980 | 2 |
| UNITED ARAB | UAE Dirham | AED | 784 | 2 |

## Emirates

| UNITED | KINGDOM | Pound Sterling | GBP | 826 | 2 |
|---|---|---|---|---|---|
| UNITED | STATES | US Dollar | USD | 840 | 2 |
|  |  | (Same day)* | USS | 998 | 2 |
|  |  | (Next day)* | USN | 997 | 2 |
| UNITED | STATES | US Dollar | USD | 840 | 2 |

## Minor Outlaying

## Islands

_____________________________________________________________________________

+ CFA Franc BCEAO; Responsible authority: Banque Centrale des Etats de
  l'Afrique de l'Ouest.

++ The Uganda Shilling was denominated as from 18 May 1987.

- Funds code [ See table A.2(E) for definitions of funds types].

Table A.1 (Continued)
________________________________________________________________________________

| ENTITY | Currency | Code |  | Decimal |
|---|---|---|---|---|
|  |  | Alphabetic | Numeric | Point |

________________________________________________________________________________

| URUGUAY |  | Peso Uruguayo | UYU | 858 | 2 |
|---|---|---|---|---|---|
| UZBEKISTAN |  | Uzbekistan Sum | UZS | 860 | 2 |
| VANUATU |  | Vatu | VUV | 548 | 0 |
| VATICAN CITY | STATE | Italian Lira | ITL | 380 | 0 |

## (Holy See)

| VENEZUELA | Bolivar | VEB | 862 | 2 |
|---|---|---|---|---|
| VIETNAM | Dong | VND | 704 | 2 |
| VIRGIN ISLANDS | US Dollar | USD | 840 | 2 |

## (British)

| VIRGIN | ISLANDS (U.S.) | US Dollar | USD | 840 | 2 |
|---|---|---|---|---|---|
| WALLIS | AND FUTUNA | CFP Franc | XPF | 953 | 0 |

## Islands

| WESTERN SAHARA | Moroccan Dirham | MAD | 504 | 2 |
|---|---|---|---|---|
| YEMEN | Yemeni Rial | YER | 886 | 2 |
| YUGOSLAVIA | New Dinar | YUM | 891 | 2 |
| ZAMBIA | Kwacha | ZMK | 894 | 2 |
| ZIMBABWE | Zimbabwe Dollar | ZWD | 716 | 2 |

_________________________________________________________________________________

Table A.1 (Continued)
______________________________________________________________________________

| ENTITY | Currency | Code |  | Decimal |
|---|---|---|---|---|
|  |  | Alphabetic | Numeric | Position |

________________________________________________________________________________

| Entity | not | applicable | Gold | XAU | 959 | N.A. |
|---|---|---|---|---|---|---|

                                   Bond Markets Units

| European | Composite | XBA | 955 | N.A. |
|---|---|---|---|---|

                                    Unit (EURCO)

| European | Monetary | XBB | 956 | N.A. |
|---|---|---|---|---|

                                    Unit (E.M.U.-6)***

| European | Unit | of | XBC | 957 | N.A. |
|---|---|---|---|---|---|

                                    Account 9

## (E.U.A.- 9)

| European | Unit | of | XBD | 958 | N.A. |
|---|---|---|---|---|---|

                                    Account 17

## (E.U.A.- 17)

| Palladium | XPD | 964 | N.A. |
|---|---|---|---|

| Platinum | XPT | 962 | N.A. |
|---|---|---|---|

| Silver | XAG | 961 | N.A. |
|---|---|---|---|

_____________________________________________________________________________

| *** | E.M.U.-6 | is | sometimes | known | as | the | European | Currency | Unit. | This | should | not | be | confused |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

       with the settlement unit of the European Monetary Cooperation Fund (E.M.C.F.) which has
       the same name (see entry for 'European Monetary Cooperation Fund' in this table).

Table A.1 (Continued)

________________________________________________________________________________

| ENTITY | Currency | Code |  | Decimal |
|---|---|---|---|---|
|  |  | Alphabetic | Numeric | Position |

________________________________________________________________________________

| Entity | not | applicable | Special | settlement | currencies |
|---|---|---|---|---|---|

| UIC-Franc | XFU | Nil | N.A. |
|---|---|---|---|
| Gold-Franc | XFO | Nil | N.A. |

| Codes | specifically | XTS | 963 | N.A. |
|---|---|---|---|---|

                                  reserved for testing
                                  purposes

| The | codes | assigned | for | XXX | 999 | N.A. |
|---|---|---|---|---|---|---|

                                  transactions where no
                                  currency is involved
                                  are:

| euro* | EUR* | 978 | 2 |
|---|---|---|---|

__________________________________________________________________________________

- On 1 January 1999, the euro will become the currency of those Member States of the European Union which
        adopt the single currency in accordance with the Treaty establishing the European Community. This
        code has been issued now so that technical preparations can be started. The code element “EU” has been
        reserved by the ISO 3166 Maintenance Agency for use within ISO 4217 where “R” has been appended to
        make an acceptable mnemonic code.

Table A.2 Funds Codes Registered with the Maintenance Agency

| CURRENCY | Currency | Fund | Type | Code | Decimal |
|---|---|---|---|---|---|
| AUTHORITY |  |  |  | Alphabetic Numeric | Position |

_________________________________________________________________________________

| BOLIVIA | Mvdol | BOV | 984 | 2 |
|---|---|---|---|---|

| CHILE | Unidades | de | CLF | 990 | 0 |
|---|---|---|---|---|---|

                                              Fomento

| MEXICO | Mexican | Unidad | MXV | 979 | 2 |
|---|---|---|---|---|---|

                                              de Inversion (UDI)

| UNITED | STATES | US | Dollar | Same | day | USS | 998 | 2 |
|---|---|---|---|---|---|---|---|---|
|  |  |  |  | Next | day | USN | 997 | 2 |

_________________________________________________________________________________

Definitions of the fund types listed above

BOV: For indexation purposes and denomination of certain finacial instruments (ex. treasury bills). The Mvdol is
set daily by the Central Bank of Bolivia based upon the official USD/BOB rate.

CLF: This development unit has been approved by the Chilean government for use in insurance transactions (with
effect from 10 April 1980).

ECV: A daily indexation mechanism set by the Ecuadorian Central Bank. The UVC is set according to the
variation of the Consumer price Index (Urban), as compiled by the National Census and Statistics Institute (INEC).

MXV : The UDI is an inflation adjusted mechanism set by the Central Bank of Mexico according to the variation in
the Mexican Consumer Price Index. The value of the UDI is expressed in terms of Mexican Pesos per UDI. It is used
to denominate mortgage loans, some bank deposits with maturities of 3 month or more and Government bonds

## (Udibonos).

USN: "Next day" funds are immediately available for transfer in like funds, and subject to
     settlement, available the next business day for same day funds transfer or withdrawal in cash.

USS: "Same day" funds are immediately available for transfer today or for withdrawal in cash,
      subject to the settlement of the transaction through the payment mechanism used.

(USD designates the US Dollar, the currency designator when an accumlation of amounts contains more than one
funds type.)
______________________________________________________________________

Table A.3 Codes for Historic Denomination of Currencies and Funds

| ENTITY | Historic |  |  |  |
|---|---|---|---|---|
|  | Currencies | Code | Numeric | WD |

________________________________________________________________________________

| ALBANIA | Old | Lek | ALK | *     - | 12/89 |
|---|---|---|---|---|---|

| ANGOLA | Kwanza | AOK | - | 03/91 |
|---|---|---|---|---|

| ARGENTINA | Peso Argentino | ARP | - | 07/85 |
|---|---|---|---|---|
|  | Austral | ARA | - | 01/92 |
|  | Peso | ARY* | - | 1989/1990 |

| BELGIUM | Convertible Franc | BEC | 993 | 03/90 |
|---|---|---|---|---|
|  | Financial Franc | BEL | 992 | 03/90 |

| BOLIVIA | Peso | BOP | - | 02/87 |
|---|---|---|---|---|

| BOSNIA | & HERZEGOVINA | Dinar | BAD | 070 | 09/97 |
|---|---|---|---|---|---|

| BRAZIL | Cruzeiro | BRB | - | 03/86 |
|---|---|---|---|---|
|  | Cruzado | BRC | - | 02/89 |
|  | New Cruzado | BRN | - | 03/90 |
|  | Cruzeiro | BRE | 076 | 08/93 |
|  | Cruzeiro Real | BRR | 987 | 07/94 |

| BULGARIA | Lev | A/62 | BGK* | - | 1989/1990 |
|---|---|---|---|---|---|
|  | Lev | A/52 | BGJ* | - | 1989/1990 |

| BURMA# | N/A | BUK | - | 02/90 |
|---|---|---|---|---|

| CHINA | Peoples | Bank |  |  |  |
|---|---|---|---|---|---|
|  | Dollar |  | CNX* | - | 12/89 |

| CROATIA | Dinar | HRD | - | 01/95 |
|---|---|---|---|---|

| CZECHOSLOVAKIA | Krona A/53 | CSJ* | - | 1989/1990 |
|---|---|---|---|---|
|  | Koruna | CSK | 200 | 03/93 |

| ECUADOR | Sucre |  |  |  | ECS | 218 | 9/00 |
|---|---|---|---|---|---|---|---|
|  | Unidad | del | Valor | constante | ECV | 983 | 9/00 |

## (Uvc)*

| EQUATORIAL | GUINEA | Ekwele | GQE | 226 | 06/86 |
|---|---|---|---|---|---|
|  |  | Ekwele | EQE* | - | 12/89 |

_________________________________________________________________________
- Non ISO code
# Change in country name

Table 3 (Continued)
____________________________________________________________________________

| ENTITY | Historic |  |  |  |
|---|---|---|---|---|
|  | Currencies | Code | Numeric | WD |

________________________________________________________________________________
| EUROPEAN MONETARY | European Currency | XEU | 954 | 01/99 |
|---|---|---|---|---|
| COOPERATION FUND | Unit (E.C.U) |  |  |  |

## (Emcf)**

| GERMAN DEMOCRATIC | Mark | der | DDR | DDM | 278 | 07/90 | to |
|---|---|---|---|---|---|---|---|
| REPUBLIC |  |  |  |  |  | 09/90 |  |

| GEORGIA | Georgian | Coupon | GEK | 268 | 10/95 |
|---|---|---|---|---|---|

| GUINEA | Syli | GNS | - | 02/86 |
|---|---|---|---|---|
|  | Syli | GNE* | - | 12/89 |

| GUINEA | BISSAU | Guinea | Escudo | GWE | - | Between | 1978- |
|---|---|---|---|---|---|---|---|

                                                                               1981

| ICELAND | Old | Krona | ISJ* | - | 1989/1990 |
|---|---|---|---|---|---|

| ISRAEL | Old Shekel | ILR* | - | 1989/1990 |
|---|---|---|---|---|
|  | Pound | ILP | - | Between 1978- |

                                                                               1981

| LESOTHO | Maloti | LSM | - | 05/85 |
|---|---|---|---|---|

| LAO | Kip | Pot | Pol | LAJ* | - | 12/89 |
|---|---|---|---|---|---|---|

| LATVIA | Latvian | Ruble | LVR | - | 12/94 |
|---|---|---|---|---|---|

| LITHUANIA | Talonas | LTT | - | 07/93 |
|---|---|---|---|---|

| LUXEMBOURG | Convertible Franc | LUC | 989 | 03/90 |
|---|---|---|---|---|
|  | Financial Franc | LUL | 988 | 03/90 |

| MALDIVES | Maldive | Rupee | MVQ* | - | 12/89 |
|---|---|---|---|---|---|

| MALI | Mali | Franc | MAF* | - | 12/89 |
|---|---|---|---|---|---|
|  |  |  | MLF | 446 | 11/84 |

| MALTA | Maltese | Pound | MTP | - | 06/83 |
|---|---|---|---|---|---|

| MEXICO | Mexican | Peso | MXP | - | 01/93 |
|---|---|---|---|---|---|

_______________________________________________________________________

- Non ISO code

Table 3 (Continued)
________________________________________________________________________________

| ENTITY | Historic |  |  |  |
|---|---|---|---|---|
|  | Currencies | Code | Numeric | WD |

________________________________________________________________________________
| MOZAMBIQUE | Mozambique | Escudo | MZE | - | Between | 1978- |
|---|---|---|---|---|---|---|

                                                                                1981

| NICARAGUA | Cordoba | NIC | - | 10/90 |
|---|---|---|---|---|

| PERU | Sol | PES | - | 02/86 |
|---|---|---|---|---|
|  | Inti | PEI | - | 07.91 |
|  | Sol | PEH* | - | 1989/1990 |

| POLAND | Zloty | PLZ | 616 | 01/97 |
|---|---|---|---|---|

| ROMANIA | Leu | A/52 | ROK* | - | 1989/1990 |
|---|---|---|---|---|---|

| SOUTH | AFRICA | Financial | Rand | ZAL | 991 | 03/95 |
|---|---|---|---|---|---|---|

| SOUTHERN | RHODESIA# | Rhodesian | Dollar | RHD | - | Between | 1978- |
|---|---|---|---|---|---|---|---|

                                                                                1981

| SPAIN | Spanish Peseta | ESA | 996 | Between | 1981- |
|---|---|---|---|---|---|
|  | ("A" Account) |  |  | 1983 |  |

| (convertible | Peseta | ESB | 995 | 12/94 |
|---|---|---|---|---|

                           Accounts)

| SUDAN | Sudanese | Pound | SDP | - | 06/98 |
|---|---|---|---|---|---|

| UNION | OF | SOVIET | Rouble | SUR | - | 12/90 |
|---|---|---|---|---|---|---|

## Socialist Republics#

| YEMEN, | Yemeni | Dinar | YDD | 720 | 09/91 |
|---|---|---|---|---|---|

## Democratic Of

| UGANDA | Uganda Shilling | UGS | - | 05/87 |
|---|---|---|---|---|
|  | Old Shilling | UGW* | - | 1989/1990 |

| UKRAINE | Karbovanet | UAK | 804 | 09/96 |
|---|---|---|---|---|

___________________________________________________________
- Non ISO code
# Change in country name.

Table 3 (Continued)
________________________________________________________________________________

| ENTITY | Historic |  |  |  |
|---|---|---|---|---|
|  | Currencies | Code | Numeric | WD |

________________________________________________________________________________
| URUGUAY | Old | Uruguay | Peso | UYN* | - | 12/89 |
|---|---|---|---|---|---|---|

| Uruguayan | Peso | UYP | - | 03/93 |
|---|---|---|---|---|

| VIETNAM | Old | Dong | VNC* | - | 1989/1990 |
|---|---|---|---|---|---|

| YUGOSLAVIA | New | Yugoslavian | YUD | - | 01/90 |
|---|---|---|---|---|---|

                           Dinar
| Yugoslavian | Dinar | YUN | 890 | 11/95 |
|---|---|---|---|---|

| ZAIRE | Zaire | ZRZ | - | 02/94 |
|---|---|---|---|---|
|  | New Zaire | ZRN | 180 | 06/99 |

| ZIMBABWE | Rhodesian | Dollar | ZWC* | - | 12/89 |
|---|---|---|---|---|---|

| ENTITY AND | RINET | XRE | N/A | 11/99 |
|---|---|---|---|---|
| CURRENCY NOT | Funds Code |  |  |  |

## Applicable

___________________________________________________________
- Non ISO code

## Annex

## Information To Be Provided By Those Making Application For The Issue

## Of New Codes, Amendments And Deletions.

Applications for additions or changes to the code lists are acceptable from any source. However, on
order to ensure rapid processing by the Secretaries, the information required from applicants has been
laid down as follows:

                         (a) Name of entity

                         (b) Name of currency

                         (c) The institution responsible for the currency (name and place of
                            operation).

                         (d) Requirements:

                            (1) Whether currency or funds code: if funds code, give
                               definition and proposed use;

                            (2) If new code, make proposal;

                            (3) If revision, state existing code and make proposal;

                            (4) If deletion, indicate code to be deleted;

                         (e) Reason for application;

                         (f) Evidence of support (currency code only);

                         (g) Date of implementation (indicate if special conditions of urgency apply);

                         (h) Application submitted by (name, address, telephone, telex numbers, etc,
                            of applicant);

                         (i) Date of application.

Applications should be addressed to

 Miss A M Wadsworth Tel. (0181) 996 7466 National
| Secretariat | for | ISO4217MA | +44 | 181 | 996 | 7466 | International |
|---|---|---|---|---|---|---|---|

 BSI
| 389 Chiswick | High | Road | Fax (0181) | 996 | 7466 | National |
|---|---|---|---|---|---|---|
| London |  |  | +44 181 | 996 | 7466 | International |

 W4 4AL United Kingdom

 Appendix 2
Battery Operated Card Reader

A2.1 Special Application

The Battery Operated Card Reader described below is a special application of the MDB/ICP
specification (non-standard) and is not sanctioned by NAMA. It is provided here to document
an application that exists in use today.

A2.2 Extension to MDB/ICP – Card Reader Using Standby Feature

Some Vending machines use battery operated equipment. According to this feature, these
machines and all devices used within these machines must provide a standby operating
mode.

During standby operation - necessary for saving battery power while the machine is not in use
- all devices shall consume a minimum standby current. Any device is equipped with some
hardware wake-up mechanism. Both standby current and wake-up mechanism is to be
defined in the device related hardware specification.

After wake-up, a device uses normal operating current, until a defined shutdown sequence is
established and the device enters standby mode again.

The following specification shows the extensions and procedures for a normal MDB/ICP card
reader and VMC-controller necessary to do wake-up and shut down sequences. The hardware
specification related to wake-up is a separate BDTA-document. To understand the following
details, it is necessary to know, that a separate bi-directional wake-up pin is applied to the
card-reader. Pulling the wake-up line (from the card-reader while a card is inserted), both card-
reader and VMC will be brought to normal operation mode.

A2.3 Extension to MDB/ICP – SETUP Config Data

|  | Config | VMC | Columns | Rows | Display |
|---|---|---|---|---|---|
| SETUP | Data | Feature | on | on | Info |
| (11H) | (00H) | Level | Display | Display |  |

## Y1           Y2            Y3           Y4            Y5

| Y1 | :      Configuration | data. |
|---|---|---|

                 VMC is sending its configuration data to reader.
| Y2 | :      VMC | Feature | Level. |
|---|---|---|---|

                 Indicates the feature level of the VMC. The available feature levels are:

                  01 - The VMC is not capable or will not perform the advanced features
                       as specified in Table 1: COMMANDS & RESPONSES following
                       Section 7.3.2. The reader will not provide advanced information to
                       the VMC, but can do the advanced features internally (transparently
                       to the VMC). The reader has no revaluation capability.
                  02 - The VMC is capable and willing to perform the advanced features as
                       specified in Table 1: COMMANDS & RESPONSES following
                       Section 7.3.2. The reader will provide advanced information to the
                       VMC (if possible) and will not do the advanced features internally.
                  03 - The VMC is able to support level 02, but also supports some or all of
                       the optional features listed in the EXPANSION ID command (i.e., file
                       transfer, 32 bit credit, multi-currency / language features, negative
                       vend, and / or data entry).

                 81H: VMC is Level 01, but battery operated.
                 82H: VMC is Level 02, but battery operated.
                 83H: VMC is Level 03, but battery operated.
| Y3 | :      Columns | on | Display. | The | number | of | columns | on | the | display. | Set | to | 00H | if |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|

                 the display is not available to the reader.
| Y4 | :      Rows | on | Display. |
|---|---|---|---|

                 The number of rows on the display.
| Y5 | :      Display | Information | - xxxxxyyy |
|---|---|---|---|

                 xxxxx = Unused
| yyy | =      Display type |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|
| 000 | :      Numbers, upper | case | letters, | blank | and | decimal | point. |
| 001 | :      Full ASCII |  |  |  |  |  |  |

                 010-111: Unassigned

| Reader | Reader | Country / | Country / | Scale Decimal | Application Miscellaneous |
|---|---|---|---|---|---|
| Config | Feature | Currency | Currency | Factor Places | Maximum Options |
| Data | Level | Code | Code |  | Response |
| (01H) |  | High | Low |  | Time |

## Z1       Z2          Z3          Z4          Z5     Z6     Z7          Z8

| Z1 | :     READER | - Configuration | data. |
|---|---|---|---|

                Indicates the payment media reader is responding to a SETUP -
                Configuration data request from the VMC.
| Z2 | :     Reader | Feature | Level. |
|---|---|---|---|

                Indicates the feature level of the reader. Currently feature levels are:

                   01 - The reader is not capable or will not perform the advanced features
                        as specified in Table 1: COMMANDS & RESPONSES following
                        Section 7.3.2. The reader will not provide advanced information to
                        the VMC, but can do the advanced features internally (transparently
                        to the VMC). The reader has no revaluation capability.
                   02 - The reader is capable and willing to perform the advanced features
                        as specified in Table 1: COMMANDS & RESPONSES following
                        Section 7.3.2. The reader will provide advanced information to the
                        VMC (if possible) and will not do the advanced features internally.
                   03 - The reader is able to support level 02, but also supports some or all
                        of the optional features listed in the EXPANSION ID command (i.e.,
                        file transfer, 32 bit credit, multi-currency / language features,
                        negative vend, and / or data entry).
                80H: This bit is additionally set, if the reader is capable to work in battery
                operation mode and should be compared with the VMC against its own
                working mode. This is also done from the reader against the VMCs
                request in Y2.
       Z3-Z4 : Country / Currency Code - packed BCD.
               The packed BCD country / currency code of the changer can be sent in
               two different forms depending on the value of the left most BCD digit.

                If the left most digit is a 0, the International Telephone Code is used to
                indicate the country that the changer is set-up for. For example, the USA
                code is 00 01H (Z3 = 00 and Z4 = 01).

                If the left most digit is a 1, the latest version of the ISO 4217 numeric
                currency code is used (see Appendix A1). For example, the code for the
                US dollar is 18 40H (Z2 = 18 and Z3 = 40) and for the Euro is 1978 (Z3 =
                19 and Z4 = 78). Use FFFFh if the country code in unknown.

                For level 3 cashless readers, it is mandatory to use the ISO 4217 numeric
                currency code (see Appendix A1).
| Z5 | :     Scale | Factor. |
|---|---|---|

                The multiplier used to scale all monetary values transferred between the
                VMC and the reader.
| Z6 | :     Decimal | Places. |
|---|---|---|

                The number of decimal places used to communicate monetary values
                between the VMC and the payment media reader.

                All pricing information sent between the VMC and the payment media
                reader is scaled using the scale factor and decimal places. This
                corresponds to:
                                           ActualPrice = P ⋅ X ⋅ 10 − Y
                where P is the scaled value send in the price bytes, and X is the scale
                factor, and Y is the number of decimal places. For example if there are 2
                decimal places and the scale factor is 5, then a scaled price of 7 will
                mean an actual of 0.35.
| Z7 | :     Application | Maximum | Response | Time | - seconds. |
|---|---|---|---|---|---|

                The maximum length of time a reader will require to provide a response
                to any command from the VMC. The value reported here supercedes the
                payment reader’s default NON-RESPONSE time defined in section 7.5 if
                the value reported here is greater.
| Z8 | :     Miscellaneous Options - xxxxyyyy |  |  |  |  |  |
|---|---|---|---|---|---|---|
|  | xxxx:     Unused (must be set to 0) |  |  |  |  |  |
|  | yyyy:     Option bits |  |  |  |  |  |
|  | b0=0:     The payment media reader is | NOT | capable | of | restoring | funds |

                          to the user’s payment media or account. Do not request
                          refunds.
| b0=1: | The | payment | media | reader | is | capable | of | restoring | funds | to | the |
|---|---|---|---|---|---|---|---|---|---|---|---|

                          user’s payment media or account. Refunds may be requested.
| b1=0: | The | payment | media | reader | is | NOT | multivend | capable. |
|---|---|---|---|---|---|---|---|---|

                          Terminate session after each vend.
| b1=1: | The | payment | media | reader | is | multivend | capable. | Multiple |
|---|---|---|---|---|---|---|---|---|

                          items may be purchased within a single session.
| b2=0: | The | payment | media | reader | does | NOT have a display. |
|---|---|---|---|---|---|---|
| b2=1: | The | payment | media | reader | does | have its own display. |
| b3=0: | The | payment | media | reader | does | NOT support the |

                          VEND/CASH SALE subcommand.
| b3=1: | The | payment | media | reader | does | support | the | VEND/CASH |
|---|---|---|---|---|---|---|---|---|

                          SALE subcommand.
                b4-b7=0 Any future options must be covered by the EXPANSION
                          COMMAND option bits.

Note: The following changes are the only changes to upgrade to battery operated
readers:

If a VMC is battery operated, it signals the card reader with the flag 80H to work in battery
operation mode. Within byte Z2 the reader also sets the flag to 80H to signal standby feature
capability.

If only one of both is in standby capability, this results in an configuration error and the
manufacturers should deal with handling of this condition. Assume that at least one device will
not enter standby mode and therefore battery lifetime is dramatically reduced!

A2.4 VMC-Reader Operation Sequences

The VMC and the Reader should operate during battery mode in the following way:

After wake-up, the VMC starts with the normal sequences:

Reset
Setup/Config
MAX/MIN-price
Identify
Enable
Poll

During these sequences, the VMC has two possibilities to signal the Card-Reader, not to enter
standby-mode again:

Pulling the wake-up pin to low level
Running poll sequences in continuos timing.

If neither the wake-up pin is driven low, nor any command is further sent to the card reader,
the reader enters standby state after its Application Maximum Response Time (normally
defined to 5 sec in ICP, but sent in byte Z7 of status response)

During card operation, the sequences continue normally with

Begin Session
Vend Request
Vend Accepted
Vend Success
Cancel Session/Session Complete

Whenever a cancel session or session complete command is received, the reader should stop
all internal work after a defined timeout period (Application Maximum Response Time) is
finished after the last command sequence and after the wake-up pin is not pulled low.

The VMC should stop polling after the cancel session or session complete command and
additionally should no longer pull wake-up pin.

If even the reader or the VMC may wish any further communication (i.e. for additionally trailing
display messages or multi vend purposes or etc.) the reader can use any non idle answer to
the poll command (i.e. the display message) whereas the VMC can continue polling or pulling
the wake-up pin.

Note that the wake-up pin may not be used from the reader to hold on operation, cause
dynamic system consideration and of course holding more devices within the system in normal
operation mode is not a good job.

The reader should be in a power saving mode after this timeout period where power
consumption is less than 10 uA.

To allow the reader holding VMC operating, at least 5 poll have to be sent, after the cancel
session or session complete. If any one of these polls is answered different with only a ACK, 5
polls have to be sent again. Note, that if a display message is sent, display time is added!

If the reader entered standby state, and a new card is inserted, the procedure starts a again.

Whenever during this next session, the reader should avoid all unnecessary work, i.e. display
messages like „reader xyz, Software version 99.4711“ or „checking RAM“ and so on should be
avoided. While in battery operation, the user has inserted a card and is waiting for display of
his fund, to continue with a vend and is not interested in service related messages.

A2.5 Session Example

| Card | inserted | Reader | pulls | wake- |
|---|---|---|---|---|

                      up pin

| Card reader runs | VMC is entering | VMC is pulling |
|---|---|---|
| Reset procedure | normal operation | wake-up pin low |
| and waits for VMC | mode and running | and/or starting |
| command | internal reset | command |
|  | procedure | sequence. |

                                                                 This has to be done
                                                                 within the ICP
                                                                 default max. appl.
                                                                 Response time, in
                                                                 any other case the
                                                                 reader may enter
                                                                 standby mode
                                                                 again.

                      Reader answers
                      commands, checks
                      card and monitors
                      wake-up line
| If the reader will | be | VMC displays credit |
|---|---|---|
| enabled, begin |  | and waits for user |
| session is sent |  | action |

                                                                 If a vend is
                                                                 requested, vend
                                                                 request will be sent
| Normal vend | VMC signals | vend |
|---|---|---|
| sequence will | success |  |

                      continue
                                                                 VMC sends session
                                                                 complete
                      The reader waits for
                      poll and starts
                      standby timeout
                      with it's own max.
                      appl. Response
                      time

                                                     VMC sends at least
                                                     five polls and stops
                                                     pulling the wake-up
                                                     line
                      The reader sends a
                      display request with
                      a duration of 10 sec
                      for a finishing thank
                      you message.
                                                     VMC displays
                                                     messages for 10
                                                     sec, and polls
                                                     during these 10
                                                     sec. After the 10
                                                     sec have elapsed,
                                                     additionally 5 poll
                                                     will be sent

A2.6 Hardware Considerations

Hardware Considerations

Within this special battery operation, the pin 3 of MDB/ICP connector is used as a wake-up
signal. Refer to special BDTA-hardware specification.

To show an example of the timing for this pin, refer to the following diagram, which gives an
example of all special timing problems related to more than one wake-up condition.

                             C
                                              D

              A

                       B

| Position | A: | mechanical switch on VMC is pulling pin 3 low (i.e. door switch) |
|---|---|---|
| Position | B: | mechanical switch is released |
| Position | C: | card reader has finished reset routines and pulls pin 3 low |
| Position | D: | VMC has finished reset routines and pulls pin 3 low too. |

If a card is inserted first, pin 3 may be pulled low first at position B.
If VMC is waked up via other means, maybe card reader is waked up at position D first.

In any case, this is a good example to clarify different waveform conditions on pin 3. Please
note that any device may release pin 3 after a short duration (<1ms) cause pin 3 should work
as dynamically wake-up. Holding pin 3 permanently low may prevent other devices from wake-
up, i.e. after all devices ran into timeout and one is still holding pin 3, the other can no longer
enter ready state (Note i.e. to door-switches etc.)

                               (this page intentionally left blank)

Appendix 3
MDB Recommended “Best Practices”

The following sections make recommendations that are intended to help reduce
compatibility issues. Note that when developing a device you should not assume
other devices or VMCs will follow these recommendations. Your device or VMC
must meet the full MDB specifications!

   1. Physical Connections (Power/Voltage/Connection)

   2. Timing Considerations (Lowest Level/Time-out)

   3. Commands, Repetition, ACK, NAK

   4. Logical Level, Processing

| 1.      Physical | Connections | (Power/Voltage/Connection) |
|---|---|---|

       Voltage specification (General)

       Verify that the VMC meets the min MDB voltage at max load with the min input line
       voltage.

| 2.      Timing | Considerations | (Lowest | Level/Time-out) |
|---|---|---|---|

       Timing Considerations (General)

       To avoid timing issue (Section 3.1 Timing Definitions) it is recommended that you
       allow for some margin in your design. See table below:

| Item |  |  | MDB Specification | Tolerated values |
|---|---|---|---|---|
| Communication | startup |  | 200ms | 500ms |
| Communication | response | time | 5ms max | 20ms* |

        (when waiting for a response)
| Communication | response | time | 5ms | max | 4ms |
|---|---|---|---|---|---|

        (when sending a response)
| Interbyte time (when receiving data) | 1ms max | 5ms* |
|---|---|---|
| Interbyte time (when sending data) | 1ms max | 0.8ms |
| Non-Response time (the time the | Varies per device | Plus the time |
| device may be busy performing |  | between polls |

        other processes. I.e., validating
        coins)
| Application Non-Response time |  | Varies | per | device | Plus the time |
|---|---|---|---|---|---|
| (time that can be reprogrammed | to |  |  |  | between polls |

        be different from the default Non-
        Response time.

       *Using the tolerated values will provide compatibility with older equipment
       manufactured under the EVMMA version of the MDB specification that had the
       Communication response time at 20ms and Interbyte time at 5ms. The transmitting
       device must always use the values of the MDB specification.

                                                                        VMC

                                                                        Peripheral

                                            Byte time
                                                 Inter-byte Time
                                                   Response Time

                     A

## B        C

       Please note, that the receiving device at the bus (master or slave) will get a receive
       interrupt (using standard UART devices) only after the byte is fully transmitted.
       These are the positions A, B, and C in the above diagram.

       Therefore, the receiving device needs to set a higher value for the interbyte timeout,
       because it needs to add at least the transmission time for one byte (which is 1 start
       bit + 9 data bits + 1 stop bit at a rate of 9600 baud equal 1.2 ms). The same happens

       for the response timeout, because the response is first detected, while the first byte
       is fully received.

       Another common implementation error is checking the response timeout after the
       whole response message is received. This will never work because if, for example,
       the response is more than 5 bytes, the transmission time for 5 bytes will be more
       than 5 ms and will always timeout.

       POLL Frequency (General)
       Section 2.4.3 states, “Each peripheral should be polled every 25-200 milliseconds.”
       However, the VMC is likely to stop communication during a vend or at other times
       when it does not need to communicate with the peripherals. Note that this may
       cause the peripheral(s) to RESET, see "Non-communication Time-out"-section in
       this document.

       Because of this, poll frequency is not as important as many people think it is.

       While not specifically prohibited, polling at a high rate while waiting for a response
       will usually delay the response, as the peripheral will have to service the POLL.
       Polling at a very low frequency, however may decrease coin or bill acceptance rate.

       For all devices, the recommended VMC POLL frequency is 125ms - 200ms.

       Example for a cashless device card acceptance:
                                                                      Polls to cashless

                                                                      Response from cashless

                                                                      VMC has received the
| Card inserted, reader |  |  |  |  | begin session! |
|---|---|---|---|---|---|
| begins checking it and | is | no | Card | validated, | reader is |
| longer able to respond |  |  | able | to respond | with begin |

                                                    session, but has to wait for
                                                    the next poll.

       As shown in the above diagram, the time from card insertion to credit being
       displayed on the vending machine is not specifically related to the polling rate. After
       the card is inserted, the card reader validates the card. During this time, some card
       readers are no longer able to answer the poll, others answer with an ACK only.

       When card validation is finished, the reader is ready to send the begin session,
       which will result in the balance of the card being displayed on the VMC. Obviously,
       this and only this depends on polling frequency. The time to the next poll has to be
       added to the validation time to get the maximum time before the credit is displayed.

    Please note that some readers may need significant processing time to answer the
    polls. If a developer increases the polling frequency, this would extend the validation
    time instead of getting a faster reaction with begin session.

    Example for a coin acceptor:

                                                                  Polls to coin mech

                                                                  Response from coin
                                                                  mech

| Coin | inserted | Coin | validated |
|---|---|---|---|

                               Coin Accepted message
                               sent to VMC, coin mech
                               re-enables acceptance.

    Note that some coin acceptors can send more than one coin message in response to
    a poll. The VMC must be able to parse multiple coin messages from one poll
    response.

    General Data Response Timeout

    Unless otherwise specified, a VMC should wait at least 30 seconds for a response to
    commands that require data to be returned. This does not infer that the device is not
    ACKing POLL commands, but rather the VMC is waiting for data pertaining to the
    command. I.e., for a PAYOUT VALUE command, the coin mech should respond to
    each PAYOUT VALUE POLL within 30 seconds.

    Non-communication Timeout (General)
    If a peripheral does not communicate with the VMC for an extended period of time,
    that peripheral should take care of any relevant house-keeping and then RESET.
    This time should be of sufficient length to guarantee that communications with the
    VMC have been completely lost. The recommendation is to wait at least 10 times the
    max response time for a device.

    If the VMC does not successfully communicate with a peripheral for the ‘application
    maximum response time’, it should attempt to RESET that peripheral once every 10
    seconds (Section 2.4.3 POLLing) and continue operations (if possible) with the other
    MDB peripheral(s) that are still responsive.

    Poll Responses covered by note 1 -Sent once each occurrence (Coin Mech)
    Some devices send this response each time the changer detects the condition. For
    example, the changer sees the gate open so it sends the escrow request, if the next
    time it checks it see the gate open it will send the escrow request again. Other
    devices will only send it once until the gate returns to the normal position.

    It is recommended to send it only once.

| 3.      3. | Commands, | Repetition, | ACK, | NAK |
|---|---|---|---|---|

       NAK and RET (Section 2.2 Block Format)
       The purpose of a NAK is ONLY to indicate a message has been received with a bad
       checksum. NAK is never intended to be used for a command that is understood, but
       not executable.

       Since the error may be caused by the corruption of the address byte (shown in the
       following example), it is not recommended to use the NAK, but rather to not
       response. The 5ms non-response timeout will be treated as if it were a NAK (Section

#### 2.2 Block Format/Master-to-Peripheral, Peripheral-to-Master and Response Codes).

       RET is a VMC-only response that is sent to a peripheral to force it to retransmit its
       previous (and presumably good) response. (Section 2.2 Block Format/Response
       Codes).

       Example of NAK or ‘no NAK’ with an error in the address byte:

       The following example shows how you can get in trouble with a simple RESET
       COMMAND sent to a cashless device. Whereas the cashless device itself receives
       the command without error, the bill validator in the system sees a voltage transient
       (corruption) of the address byte.

| VMC sends | Cashless | Billval | Cashless | Bill validator |
|---|---|---|---|---|
|  | received | received | response | response |
| POLL to | POLL valid | command to |  |  |
| cashless | CRC | other address |  |  |
|  |  |  | Sends a JUST | Sends nothing |

## Reset

| Sends | ACK | to | ACK | ACK |
|---|---|---|---|---|

   previous
   received just
   reset
|  |  |  |  |  | Nothing | Nothing |
|---|---|---|---|---|---|---|
| RESET to | RESET valid | Instead | of |  |  |  |
| cashless | Checksum | command | to | its |  |  |

                                        address,
                                        receives
                                        command to
                                        address 30H
                                        with Checksum
                                        10H (because
                                        the destination
                                        10H address
                                        byte was
                                        modified by
                                        transient
                                        voltage)
| Sends | ACK | Sends | NAK | * |
|---|---|---|---|---|
| after | 4ms | after | 1 ms |  |
| Sends | ACK | Sends | NAK | ** |
| after | 1ms | after | 4 ms |  |
| Sends | ACK | Sends | nothing | *** |

                                                            after 3ms

    As is shown, with only a single bit toggled (`10h` is modified to `30h`). Three different
    reactions are possible:

    - 1st Example (shown in Blue):
    The VMC receives a NAK first, but 3ms later, an ACK would arrive. If the VMC
    immediately sends a different command after the NAK the further answer of the next
    device would collide with the ACK of the cashless and cause a second failure.

    ** 2nd Example (shown in Red):
    The VMC receives the correct ACK first and continues immediately (if it is using a
    very fast polling rate). The NAK of the bill validator will collide in any case with the
    next message and cause further errors!

    *** Last example (shown in Green):
    The VMC receives the correct ACK first and continues immediately (if it is using a
    very fast polling rate). The bill validator will not cause any further errors, because it
    sends nothing. In this, and only this case, if the cashless device has a checksum

    error too, both devices would not answer. The VMC would then repeat the command
    after 5 ms, because it would interpret the timeout as an NAK.

    Recommendations from here:

    Newer peripherals should never send a NAK, to avoid further handling errors.

    Newer VMCs should never try to increase the polling rate if they receive a NAK from
    a peripherals, instead they should wait for the full timeout period to expire (and skip)
    further ACK’s and NAK’s from other peripherals. Please note that if you have four
    peripherals on the bus, the VMC may receive at least four ACK’s and/or NAK’s in or
    out of sequence!

    To improve system reliability you should implement the bit counting method defined
    in the note of page 2-4 of the MDB specification.

    Command Repetition (General)
    VMC commands which are not ACKed should be repeated for the duration of the
    non-response time-out. If the command is not a POLL it is recommended that the
    command should alternate with a POLL. This does not mean that the VMC cannot
    communicate with other peripherals on the bus, but it should continue to
    communication with any non-responsive peripheral until it can reliably conclude that
    it is offline. At that point, it should start trying to RESET that peripheral once every 10
    seconds. (Section 2.4.3 POLLing). When it receives a response to the RESET the
    VMC will need to re-initialize the peripheral.

    Command Repetition (special commands)
    VMC commands which are not ACKed should be repeated for the duration of the
    non-response time-out. Please note, that this is a general guideline, which in some
    circumstances may not be a “successful” implementation.

    Condition 1 (coin mech dispense)
    If a dispense command is not ACKed, this may be
    a) a misunderstanding by the peripheral
    b) a corrupted bus signal
    c) another peripheral corrupting the bus

    If the command itself did not arrive at the coin mech, repetition is ok. If the command
    arrived at the coin mech, but the VMC did not see the ACK, repetition obviously
    leads into multiple coin dispense!!!

    In this situation, it is recommended not to re-send the command multiple times,
    although the choice is ultimately down to the system designer, and to wait for a while
    before restarting communications. This will allow any noise on the bus to dissipate.

    Condition 2 (bill validator or coin mech acceptance)
    If a bill validator accepts a bill or a coin mech accepts a coin, this is reported during
    the next poll to the VMC. This message is then ACK’ed by the VMC.
    If this ACK is not detected by the bill validator or coin mech, for whatever reason, the
    peripheral repeats the message (this means, the same coin or bill value is sent
    again).

    If the bill or coin value message did not arrive at VMC, repetition is ok. However, if
    the command arrived at the VMC, but the bill validator or coin mech did not see the
    ACK, repetition obviously leads into increasing credit!!!

    Recommendation to minimize this effect especially for bill validators with high
    denomination values:
    Whenever a VMC receives a bill (or coin) message, it should send the ACK, process
    the bill (or coin), wait for the recommended maximum response timeout (20ms) and
    send an additional poll.
    If the VMC receives the same bill (or coin) message again after 20ms, (instead of
    receiving an ACK only) this can be assumed to be a repetition due to non-received
    ACK. If nothing is reported or a different value is sent, the ACK was understood or a
    new bill (or coin) has arrived.
    This solution assumes, that bill (or coin) insertion is much slower than 20ms (which
    obviously is true especially for bill vals)

    Command Order (General)
    In most cases the VMC can send any command at any time in any order. Note the
    Cashless device spec is the only peripheral that defines the sequence of commands.

    Command Out-Of-Sequence (Cashless Payment Device)
    If the VMC receives a Command Out-Of-Sequence from a cashless payment device,
    it is a clear indication that the state of the cashless payment device is no longer in
    synch with the VMC. The VMC should take care of any relevant house-keeping and
    then issue a RESET to the cashless payment device. This will put both parties in a
    known state of operation.

| 4.     Logical | Level, | Processing |
|---|---|---|

       Maintaining MDB Level Compatibility (General)
       In a system where the peripheral supports a higher level MDB protocol than the
       VMC, the peripheral should revert to the lower level MDB protocol to communicate
       with the VMC. (Section 1.3.1 Levels and Section 2.4.4 Levels)
       In a system where the VMC supports a higher level MDB protocol than a peripheral,
       it is the responsibility of the VMC to revert to the lower level MDB protocol when
       communicating with the peripheral. (Section 1.3.1 Levels and Section 2.4.4 Levels)

       Response data length (General)
       Note that some responses for peripherals can be variable length (tube status, poll,
       etc.). For example, a peripheral can send multiple messages in response to a poll
       command. Note that the 9th mode bit should be set on the last byte of the data being
       received (see section 2.5 Typical Session Examples)

       Scale Factors (General)
       The VMC needs to be able to handle devices with different scaling factors. The
       VMC needs to determine the least common dominator and adjust the values from
       each device.

       Decimal point (General)
       The decimal point information is only used to set the position on a credit display (it
       doesn’t adjust the values).

       Country Codes (General)
       Do not require devices to have the same country code. In July 2000 the spec
       changed to use the ISO4217 numeric currency codes. Devices before that date
       used the international telephone codes.

       Just Reset (General)
       If a device sends a just reset response, the VMC should re-initialize the device
       (request setup information, re-enable the device, etc.). Don’t send a reset
       command.

       Multiple Coin Reporting
       The VMC must take into account that coin mechs can send the value of more than
       one coin in one poll response.

       Multiple Bill Reporting
       The VMC must take into account that bill validators can send the value of more than
       one bill in one poll response.

    Power-Up Sequence (Cashless Payment Device)
    The following sequence is recommended as the power-up process for cashless
    payment devices. Post-RESET ACKs are not explicitly listed and are implied.

    Send RESET until ACKed.
    POLL until JUST RESET response.
    Send SETUP/CONFIG command.
    POLL until READER CONFIG response.
    Send MAX/MIN PRICE command.
    Send EXPANSION ID REQUEST.
    POLL until PERIPHERAL ID response.

    Send READER ENABLE command when ready.

    Cashless Payment Device Enable/Disable (Cashless Payment Device)
    While it is specifically allowed for “grandfather” reasons, a VMC should never need
    to disable a cashless payment device during a session. However, if this does occur,
    the cashless payment system should complete the session-in-progress normally
    (Section 7.4.12 READER – Disable), and subsequently refuse to start any new
    sessions with the VMC until enabled.

    Level 2 BEGIN SESSION Command (Cashless Payment Device)
    The description of Byte Z8 of the Level 02/03 BEGIN SESSION message (Section

#### 7.4.4 POLL) appears to match the EVA-DTS Standard v.5.0, App. A.1 Definitions. All

    NAMA MDB specification references in this document are based on Version 3.0
    (Draft 1), dated March 26, 2003, always refer to the latest EVA-DTS version.

    Cashless Payment Device Discounting (Cashless Payment Device)
    The VMC should not make any financial decision(s) based on the BEGIN SESSION
    balance. Some cashless peripherals support various types of discounting.
    Consequently, the VMC should not terminate a session if the reported balance is
    less than the minimum price or refuse to issue a VEND REQUEST when the list
    price of a selected item exceeds the reported balance of funds.

    Similarly, if a cashless payment device reports a starting balance of `0xFFFF` in the
    BEGIN SESSION message, the VMC should proceed normally i.e., permit a product
    selection. A BEGIN SESSION balance of `0xFFFF` means that the available fund
    balance is not currently known and/or should not be displayed. It is not meant to
    suggest that the balance is insufficient for operation. An appropriate message for the
    customer should be displayed instead of the balance – i.e. “Please make a
    selection”.

    Revalue Limit Requests (Cashless Payment Device)
    Similar to discounting, some cashless devices are capable of granting “bonus” credit
    to users (i.e., giving $6.00 credit for a $5.00 bill). There may also be cases where a
    cashless device pre-deducts sales tax resulting in a credit that is less than the
    amount in the REVALUE command. Finally, most cashless devices that store credit
    on the media have a maximum allowable credit.

    Consequently, the VMC should issue a REVALUE LIMIT REQUEST prior to
    determining which fund sources (e.g. note values) are applicable to a user. In a
    multivend environment, this means the VMC must issue multiple REVALUE LIMIT
    REQUESTs.

    If a cashless device cannot accept credit, either because the operation is not
    acceptable at this time or because the current media has reached its maximum
    credit limit, the device should respond to a REVALUE LIMIT REQUEST with a
    REVALUE DENIED not a REVALUE LIMIT of $0.00. The REVALUE DENIED
    response clearly signals that revalue is not an acceptable operation.

    Balance Display (Cashless Payment Device)
    For VMCs that opt to show the available funds, it is important to consider the
    following:
    Cashless payment devices with active discounts will deduct less than the VEND
    REQUEST amount. The displayed balance in the VMC must reflect the difference
    between starting balance and the amount in the VEND APPROVED message (not
    the VEND REQUEST). This assures that the displayed balance on the VMC is
    correct, and (where applicable) matches the cashless payment device’s display.

    Because the REVALUE APPROVED message does not contain an amount field like
    VEND APPROVED, the VMC is not capable of tracking card balance correctly in a
    “bonusing” environment.

    Multi-Vend (Cashless Payment Device)
    Multi-vending is the practice of vending multiple products within a single session.
    While multi-vending is a function of the VMC, it should only be attempted when the
    multivend bit (b1) of the Miscellaneous Options byte (Section 7.4.2 Setup- Config
    Data/ Byte Z8) of the cashless device’s configuration data is set (b1=1).

    If a VEND DENIED scenario occurs during a multi-vend session, the VMC has the
    option to terminate or continue the vend session. It may be that the user tried to buy
    something that cost more than his balance. If the VMC has less expensive goods to
    vend, continuing the session would give the user an opportunity to select something
    affordable.

    If a VEND FAILURE scenario occurs during a multi-vend session, the VMC should
    always issue a VEND FAILURE to the cashless payment device. The VMC has the
    option to terminate or continue the vend session. It may be that the user selected an
    empty column, and another selection will be successfully vended.

    Display Messages (Cashless Payment Device)
    If Byte Y3 (Columns) and/or Y4 (Rows) of the SETUP/CONFIG message are zero,
    VMC display is not available for use by the cashless payment device (Section 7.4.2
    SETUP – Config Data).
    If the display is available, a Display Request message can be sent anytime after the
    power-up sequence has been completed. In practice, there are only a few
    conditions under which the cashless payment device should make a Display
    Request:

    1. Immediately after the power-up sequence is completed to display the cashless
       payment system’s software revision number. This should not create significant
       problems because it only happens at power-up.
    2. Anytime the cashless device is out of service.
    3. In the enabled state to indicate an error accessing the media (e.g. busy signal for
       a credit card reader). This should not create a conflict because a) it is transient,
       and b) the user should be concentrating on the purchase process.
    4. In the enabled state to prompt the user (e.g. for a PIN). This should not create a
       conflict because a) it is transient, and b) the user should be concentrating on the
       purchase process.
    5. In the enabled state to inform the user of the funds available for purchase. This
       should not create a conflict because a) it is transient, and b) the user should be
       concentrating on the purchase process.
    6. During session idle (e.g. after a VEND DENIED to indicate the reason for the
       refusal). This should not create a conflict because a) it is transient, and b) the
       user should be concentrating on the purchase process.

    If the VMC reports itself to support Full ASCII (Y5 = xxxx001b) then it will support all
    printable ASCII characters (`0x20` thru `0x7F`). If values outside this range are used,
    the results are dependent upon the actual display controller chip. This is strongly
    discouraged.

    Selected Number (Item Number or Product Code?) (Cashless Payment Device)
    The selected number should be the vending machines selection number, which is
    normally the product key index. If the VMC i.e. has a two digit input, where one is
    alphanumerical, (“A-1” or “C-6” or ..), it has to convert it in a appropriate way to a
    number. To be compatible to all versions of card-readers and DTS-versions, ensure
    the number is in the range of 1-n. The maximum of n depends on the level used and
    options (1-255 or 1-65535).

    The conversion method and the maximum selection number should be published by
    the VMC vendor to ensure the correct settings of the cashless device. Vice-versa,
    the cashless device vendor should publish the maximum usable numbers of
    selection, and the default action, if a selection number out of this range is sent.

    Normally, this default action should result in a simple conversion to the maximum
    number and accepting the price from the vending machine, skipping all internal
    discounts etc.

    Combining a VMC and a cashless device which do not have compatible maximum
    selection numbers is not an issue MDB has to solve, but is an application setup
    error.

    Bill Stacking/Escrowing (Cashless Payment Device)
    As a general practice, the VMC should escrow any bills tendered for credit to a
    cashless payment device until it has verified that the cashless payment medium can
    accept the full credit amount. This is done via the REVALUE LIMIT REQUEST
    command/response sequence. Once the value has been deemed acceptable, the
    VMC should stack/secure the bill prior to issuing the REVALUE REQUEST to the
    cashless payment device. This provides maximum protection against theft attempts.
    (Section 7.4.16 Revalue)

    Mixed Tender Transactions (Cashless Payment Device)
    Historically, this practice has been avoided by the VMC disabling the other
    peripherals when one becomes active (i.e., if someone inserts a bill into the
    validator, the VMC will disable the cashless payment device). If mixed tender
    transactions are to be supported, we must determine which fund source has priority
    for purchases, as well as for dispensing change.

    There are two issues here:
    1. If revalue is permitted, always revalue first, and then any purchase(s) should be
       from the card.
    2. If revalue is not allowed, use cash first, and then deduct remaining funds from
       card.

    Example: A mixed-tender VMC accepts $1.00 bill and a user inserts a $5.00 card.

    Revalue Permitted: The $1.00 bill is stacked and a REVALUE REQUEST for $1.00 is
    sent to the cashless payment device. Once approved, any purchases should come
    from the $6.00 card balance.

    Revalue Not Permitted: The $1.00 remains in escrow. The user selects a $1.50 item.
    The VMC sends a VEND REQUEST for $0.50 to the cashless payment device. If
    and only if it gets a ‘vend approved’, it will use/stack the $1.00 in escrow and sell the
    product. If it cannot stack it, the vend will be aborted and a vend failure will be sent.
    (Note: The cashless payment device will assume a $0.50 product was sold even
    though the Item Number may have been sold previously for $1.50.)

    Obviously, this combination of settings causes more problems than the “non
    stacking” combination.

    First: if the cashless gives a discount, the discount may reduce the price to a value
    less than the vend request (because the calculation uses the $1.50 value). This
    would result in stacking less than the whole bill, which is not possible! In this case, a
    vend denied should be sent. This method would temporarily disable the mixed
    payment.

    Second: if refund is not possible, aborting of a vend will result in a credit loss
    situation. The VMC should use the opposite vend procedure – i.e. first stack the bill
    and then send the vend request. But, if in this case a ‘vend denied’ is received, the
    VMC needs to give change for at least the bill value!

    MDB does not specify handling procedures for all these combinations – the operator
    needs to check the VMC and/or cashless capabilities as this is not an issue with the
    standards but a “market feature” problem.

    Fund handling with a VEND FAILURE (Cashless Payment Device)
    Normally funds are the responsibility of the fund source, (i.e., the cashless payment
    device). If a VEND FAILURE occurs the funds in question can be handled as
    follows:

    NOTE: To prevent double refunds where the cashless payment device
    provides a process for refunds, the cashless device must indicate that the
    media supports refunds, regardless of whether or not it can actually transfer
    the lost funds back to the payment media.

    The correct handling for vend failure is always, that no credit should be converted i.e.
    cash credit is escrowed, card credit is refunded. Card credit will never be
    transformed to cash!!

    If the cashless device is not capable of refunding, for whatever reason, the VMC,
    and maybe the cashless device, may produce a log file or a statistic to ensure this is
    recorded. However, the credit balance in this case is always lost and may only be
    refunded to the customer by manual intervention (hotline, etc.)

    If the cashless device is capable of refunding, nothing else is necessary. Sometimes,
    if a special card is used or the card is no longer present, refunding is not possible. In
    this case the same procedure as described above must be followed.

    If the system allows the card refund amount to be transformed to cash, the following
    should be taken into account:

    a. The VMC can make a record of the lost funds and remove them from escrow.
    b. The VMC can retain the credit and allow it to be used as part of a cash purchase.
    c. The VMC CANNOT dispense the funds as change. In the case of a credit card
       charge or where the original source of funds was a credit card transaction, this
       constitutes a cash advance, all be it small.
    d. Please note further, that the VMC may have problems dealing with a discount
       amount.
    e. Please note further, that the cashless payment scheme may not allow this
       behaviour.

    Fund Handling with a Negative Vend Failure
    After a vend is approved, it is up to the cashless device how it handles the negative
    vend value

    State Machine (Cashless Payment Device)
    The defined state machine within the standard is information for both VMC and
    cashless programmers of the logical steps required to run the device.

    In any case, the state machine should never be used as medium to swap the
    Master-/Slave device functions. In MDB, the VMC is always the Master device. This
    results in a unspecified sequence of commands for the VMC (as for all other
    devices). i.e. even if the device has reached the begin session state, the VMC is
    allowed to send, for example, an FTL command. If the cashless is not able to
    support this command in the current state, it may send the applicable response (i.e.
    FTL denied), but will continue in the reached state!!

    Further examples of this are multiple “Vend Session Complete” or similar
    commands. Because the cashless device enters the inactive state with the first vend
    session complete, further repeated commands will never produce any problems and
    may simply be ignored.

    A lot of cashless devices use the “out of sequence” message in this case. This may
    be appropriate in terms of “educating the VMC programmer”, but will never solve the
    issue. The “out of sequence” message usually causes the VMC to send a reset
    command to re-sync the devices. This is not a problem for the VMC, but can cause
    the cashless device to run into problems - mainly because the reset sequence of a
    lot of cashless devices can take many seconds, during which the customer is unable
    to use their cards. This obviously can lead to complaints.

    The “Out of sequence” message should be the last resort for a cashless device, to
    be used only if it is unable to solve state machine problems any other way.
    Unfortunately, due to the polling mechanism with a finite polling frequency, the loss
    of synchronisation between the VMC and the cashless state is unavoidable.

    An example of this is as follows:
    After a card insertion we get a begin session.
    Both devices enter the session idle state.
    The customer presses the escrow lever and takes the card out simultaneously.
    The VMC would send a Reader Cancel command, whereas the cashless would like
    to transmit an end session (because its session ended when the card was taken
    out).

    The situation then arises that the cashless device is in the inactive state (no card
    present), but cannot send the message to the VMC (no poll available, instead a
    wrong command for this state).

    The VMC, on the other hand, believes it is sending the correct command, as it is still
    in the session idle state. Hence, it would repeat the cancel session, until it is
    answered. It would then get a totally unnecessary “out of sequence”, and maybe an
    additional "end session".

