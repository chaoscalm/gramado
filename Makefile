# Makefile in the root folder.
# Build Gramado OS.

# This is the default target
PHONY := all
all: userland-domain core-domain
	@echo "Done"
	@echo "Go to core/ and type ./run or ./runkvm"

# Step 1
PHONY := userland-domain
userland-domain:
	make -C  userland

# Step 2
PHONY := core-domain
core-domain:
	make -C  core

# ------------------------

PHONY := clean
clean: clean-all

PHONY := clean-all
clean-all: clean-userland clean-core clean-base clean-cancun

PHONY := clean-userland
clean-userland:
# In userland/
	-rm -f userland/barnsh/bin/*.BIN
	-rm -f userland/commands/bin/*.BIN
	-rm -f userland/netd/bin/*.BIN
	-rm -f userland/services/bin/*.BIN
	-rm -f userland/wdemos/eng/bin/*.BIN
	-rm -f userland/winapps/bin/*.BIN

PHONY := clean-core
clean-core:
# In core/
	-rm core/GRAMADO.VHD
	-rm core/MBR0.BIN
	-rm core/kernel/KERNEL.BIN
	-rm core/hals/newm0/MOD0.BIN
	-rm core/hals/newm1/MOD1.BIN

PHONY := clean-base
clean-base:
# Clear the disk cache
	-rm -rf base/*.BIN 
	-rm -rf base/*.BMP
	-rm -rf base/EFI/BOOT/*.EFI 
	-rm -rf base/GRAMADO/*.BIN 
	-rm -rf base/PROGRAMS/*.BIN 
	-rm -rf base/USERS/*.BIN 

PHONY := clean-cancun 
clean-cancun:
#todo

PHONY := help
help:
	@echo "Help stuff"


