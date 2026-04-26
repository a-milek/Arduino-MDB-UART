#!/usr/bin/env python3
"""Verify BV accepts BILL TYPE (`2*4` disable) while a bill sits in escrow.

Sequence:
  1. SYS reset (`10*99`) — full firmware re-init incl. BV reset/setup/security
  2. SYS ping — confirm bridge is responsive after boot
  3. BV enable acceptance (`2*3`)
  4. Operator inserts a bill → wait for `BV*BILLACTION*<type>*<value>*ESCROW`
  5. Stress: N alternating `2*4` / `2*3` cycles while the bill stays in escrow
  6. Final `2*4` disable, then `2*5*1` to stack (consume) the bill

Background: per MDB 4.3 §6 there is no precondition forbidding BILL TYPE
(0x34) during escrow. Only DISPENSE commands require pre-clearing escrow.
This test exercises the boundary.
"""

import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from mdb_client import MDBBusManager, MDBTimeout, MDBFail

SERIAL_URL = os.environ.get("MDB_URL", "rfc2217://192.168.21.179:2005")
INSERT_TIMEOUT_S = 90
STRESS_CYCLES = 30


class NullHandler:
    def on_response_received(self, data):
        pass


def fire_and_classify(bus, cmd, expect_prefix, timeout=2.5):
    """Send cmd, return (status, line) where status is 'OK' / 'FAIL' / 'TIMEOUT'."""
    bus.waitq_discard()
    bus.send(cmd)
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        try:
            remaining = max(deadline - time.monotonic(), 0.05)
            line = bus.wait_queue.get(timeout=remaining)
        except Exception:
            continue
        if line.startswith(expect_prefix + "OK"):
            return ("OK", line)
        if line.startswith(expect_prefix + "FAIL") or line.startswith(expect_prefix + "NAK"):
            return ("FAIL", line)
    return ("TIMEOUT", None)


def wait_for_escrow(bus, timeout_s):
    """Block until a BILLACTION ESCROW line is observed or timeout."""
    deadline = time.monotonic() + timeout_s
    while time.monotonic() < deadline:
        try:
            line = bus.wait_queue.get(timeout=max(deadline - time.monotonic(), 0.05))
        except Exception:
            continue
        if line.startswith("BV*BILLACTION*"):
            print(f"  [bill] {line}")
            if line.endswith("*ESCROW"):
                return line
    return None


def main():
    bus = MDBBusManager(SERIAL_URL, NullHandler())
    bus.start()
    rc = 1
    try:
        print("=== Phase 1: SYS reset ===")
        bus.mdb_sys_reset()
        print("waiting 6s for boot init to settle...")
        time.sleep(6)
        bus.waitq_discard()

        print("\n=== Phase 2: ping ===")
        bus.mdb_sys_ping()

        print("\n=== Phase 3: enable BV acceptance ===")
        bus.mdb_bv_enable()

        print(f"\n=== Phase 4: insert bill ({INSERT_TIMEOUT_S}s window) ===")
        bus.waitq_discard()
        escrow_line = wait_for_escrow(bus, INSERT_TIMEOUT_S)
        if not escrow_line:
            print("FAIL: no BV*BILLACTION*...*ESCROW seen within window")
            return 2
        print(f"bill in escrow: {escrow_line}")

        print(f"\n=== Phase 5: stress {STRESS_CYCLES} disable/enable cycles ===")
        ok = fail = 0
        first_fail = None
        for i in range(STRESS_CYCLES):
            for cmd, prefix in (("2*4*+", "BV*DISABLE*"), ("2*3*+", "BV*ENABLE*")):
                status, line = fire_and_classify(bus, cmd, prefix)
                if status == "OK":
                    ok += 1
                else:
                    fail += 1
                    if first_fail is None:
                        first_fail = (i, cmd, status, line)
                    print(f"  cycle {i}: {cmd} -> {status} ({line})")
        print(f"stress result: OK={ok} FAIL={fail}")

        print("\n=== Phase 6: final disable + stack bill ===")
        status, line = fire_and_classify(bus, "2*4*+", "BV*DISABLE*")
        print(f"final disable: {status} ({line})")
        try:
            bus.mdb_bv_escrow_stack()
            print("escrow stacked OK (bill consumed)")
        except (MDBTimeout, MDBFail) as e:
            print(f"escrow stack failed: {e}")

        print("\n=== Summary ===")
        print(f"stress OK={ok}/{ok+fail}, first failure: {first_fail}")
        rc = 0 if fail == 0 else 3
    except (MDBTimeout, MDBFail) as e:
        print(f"protocol error: {type(e).__name__}: {e}")
        rc = 4
    finally:
        bus.stop()
    return rc


if __name__ == "__main__":
    sys.exit(main())