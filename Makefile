# Makefile in the root folder.
# Build Gramado OS.

BASE = aa/base

# This is the default target
PHONY := all
all: userland-domain core-domain
# Warning: Respect the order!
	@echo "Done"
	@echo "Go to ama/ and type ./run or ./runkvm"

# Step 1
PHONY := userland-domain
userland-domain:
#warning: Respect the order
	make -C  zing/
	make -C  prezing/
	make -C  preamble/

# Step 2
PHONY := core-domain
core-domain:
#warning: Respect the order
	make -C  preama/
	make -C  ama/


# ------------------------

PHONY := clean
clean: clean-all

PHONY := clean-all
clean-all: clean-userland clean-core clean-base clean-cancun

PHONY := clean-userland
clean-userland:
# Clear the userland domain.

# ------------
# zing/

# gramland and eng
	-rm -f zing/gramado/eng/bin/*.BIN
	-rm -f zing/gramado/server/bin/*.BIN
# NETCTL
	-rm -f zing/netd/bin/*.BIN

# ------------
# prezing/

# omega1
	-rm -f prezing/omega1/libs/libdisp/obj/*.o
	-rm -f prezing/omega1/libs/libgr/obj/*.o
	-rm -f prezing/omega1/libs/libgr3d/obj/*.o
	-rm -f prezing/omega1/libs/libgws/obj/*.o

# omega2
	-rm -f prezing/omega2/drivers/bin/*.BIN
	-rm -f prezing/omega2/servers/bin/*.BIN

# omega3
	-rm -f prezing/omega3/apps/bin/*.BIN


PHONY := clean-core
clean-core:

# Clear the core domain.
	-rm ama/GRAMADO.VHD
	-rm ama/MBR0.BIN
	-rm ama/kernel/KERNEL.BIN

	-rm kmods/newm0/MOD0.BIN

PHONY := clean-base
clean-base:
# Clear the base domain.
# Clear the disk cache
	-rm -rf $(BASE)/*.BIN 
	-rm -rf $(BASE)/*.BMP
	-rm -rf $(BASE)/EFI/BOOT/*.EFI 
	-rm -rf $(BASE)/GRAMADO/*.BIN 
	-rm -rf $(BASE)/PROGRAMS/*.BIN 
	-rm -rf $(BASE)/USERS/*.BIN 

PHONY := clean-cancun 
clean-cancun:
#todo

PHONY := help
help:
	@echo "Help stuff"


