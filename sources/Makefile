# Top-level Makefile — builds both firmware projects
# Usage:
#   make              — build both (debug)
#   make release      — build both (release)
#   make master       — build MDB-UART-Master only
#   make slave        — build MDB-SLAVE only
#   make clean        — clean all build dirs

BUILD ?= debug

.PHONY: all master slave debug release clean

all: master slave

master:
	$(MAKE) -C MDB-UART-Master BUILD=$(BUILD)

slave:
	$(MAKE) -C MDB-SLAVE BUILD=$(BUILD)

debug:
	$(MAKE) BUILD=debug all

release:
	$(MAKE) BUILD=release all

clean:
	$(MAKE) -C MDB-UART-Master clean
	$(MAKE) -C MDB-SLAVE clean
