# Makefile in the root folder.
# Build Gramado OS.

# This is the default target
PHONY := all
all: userland-domain core-domain
# Warning: Respect the order!
	@echo "Done"
	@echo "Go to ama/ and type ./run or ./runkvm"

# Step 1
PHONY := userland-domain
userland-domain:
# Warning: Respect the order!
	make -C  zing/
	make -C  zz/

# Step 2
PHONY := core-domain
core-domain:
	make -C  ama/

# ------------------------

PHONY := clean
clean: clean-all

PHONY := clean-all
clean-all: clean-userland clean-core clean-base clean-cancun

PHONY := clean-userland
clean-userland:
# Clear the userland domain.

# zing/
	-rm -f zing/barnsh/bin/*.BIN
	-rm -f zing/c3/bin/*.BIN
	-rm -f zing/c3/bin/*.BIN
	-rm -f zing/commands/bin/*.BIN
	-rm -f zing/services/bin/*.BIN
# zz
	-rm -f zz/c1/eng/bin/*.BIN
	-rm -f zz/c1/gramland/bin/*.BIN
	-rm -f zz/winapps/bin/*.BIN

PHONY := clean-core
clean-core:
# Clear the core domain.
	-rm ama/GRAMADO.VHD
	-rm ama/MBR0.BIN
# Clear the init process.
	-rm ama/c0/init/*.o
	-rm ama/c0/init/bin/*.BIN
	-rm ama/hals/newm0/MOD0.BIN
	-rm ama/hals/newm1/MOD1.BIN
	-rm ama/kernel/KERNEL.BIN

PHONY := clean-base
clean-base:
# Clear the base domain.
# Clear the disk cache
	-rm -rf aa/base/*.BIN 
	-rm -rf aa/base/*.BMP
	-rm -rf aa/base/EFI/BOOT/*.EFI 
	-rm -rf aa/base/GRAMADO/*.BIN 
	-rm -rf aa/base/PROGRAMS/*.BIN 
	-rm -rf aa/base/USERS/*.BIN 

PHONY := clean-cancun 
clean-cancun:
#todo

PHONY := help
help:
	@echo "Help stuff"


