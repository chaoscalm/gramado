# Makefile in the root folder.
# Build Gramado OS.

BASE = ama/base

# This is the default target
PHONY := all
all: cloud-domain edge-domain base-domain
# Warning: Respect the order!
	@echo "Done"
	@echo "Go to ama/ and type ./run or ./runkvm"

# Step 3
PHONY := base-domain
base-domain:
#warning: Respect the order
	make -C  zing/
	make -C  ama/

# Step 1
PHONY := cloud-domain
cloud-domain:
#warning: Respect the order
	make -C  prezing/
	make -C  preama/

# Step 2
PHONY := edge-domain
edge-domain:
	make -C  preamble/

# ------------------------

PHONY := clean
clean: clean-all

PHONY := clean-all
clean-all: \
clean-base-domain clean-cloud-domain clean-edge-domain \
clean-base clean-cancun  


PHONY := clean-base-domain
clean-base-domain:
# Clear the base domain.

# ------------
# ama/
	-rm ama/GRAMADO.VHD
	-rm ama/MBR0.BIN
	-rm ama/kernel/KERNEL.BIN
	-rm ama/kmods/newm0/MOD0.BIN
# ------------
# zing/
# gramland and eng
	-rm -f zing/gramado/eng/bin/*.BIN
	-rm -f zing/gramado/server/bin/*.BIN
# NETCTL
	-rm -f zing/netd/bin/*.BIN


PHONY := clean-cloud-domain
clean-cloud-domain:

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

PHONY := clean-edge-domain
clean-edge-domain:


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


