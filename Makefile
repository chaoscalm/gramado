
# Build Gramado OS.

PHONY := step1-all
step1-all: step2-userland step3-core
	@echo "Done"
	@echo "Go to core/ and type ./run or ./runkvm"

PHONY := step2-userland
step2-userland:
	make -C  userland

PHONY := step3-core
step3-core:
	make -C  core

PHONY := clean
clean: clean-all

PHONY := clean-all
clean-all: clean-userland clean-core

PHONY := clean-userland
clean-userland:
# In userland/
	-rm userland/gramland/bin/*.BIN
	#-rm userland/burgundy/bin/*.BIN
	#-rm userland/blue/bin/*.BIN
	#-rm userland/beige/bin/*.BIN

PHONY := clean-core
clean-core:
# In core/
	-rm core/GRAMADO.VHD
	-rm core/MBR0.BIN
	-rm core/kernel/KERNEL.BIN
	-rm core/newm0/MOD0.BIN
# Clear the disk cache
	-rm -rf base/*.BIN 
	-rm -rf base/*.BMP
	-rm -rf base/EFI/BOOT/*.EFI 
	-rm -rf base/GRAMADO/*.BIN 
	-rm -rf base/PROGRAMS/*.BIN 
	-rm -rf base/USERS/*.BIN 


