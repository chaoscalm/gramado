# Makefile in the core/ folder.
# Gramado Kernel
# License: BSD License
# Compiling on gcc 9.4.0
# Linking on ld 2.34

# ama/ depends on ama/libs/


# Make variables (CC, etc...)
AS      = as
LD      = ld
CC      = gcc
AR      = ar
MAKE    = make
NASM    = nasm
PYTHON  = python
PYTHON2 = python2
PYTHON3 = python3

#
# Config
#

# verbose
# Quiet compilation or not.
ifndef CONFIG_USE_VERBOSE
	CONFIG_USE_VERBOSE = 1
endif

ifeq ($(CONFIG_USE_VERBOSE),1)
	Q =
else
	Q = @
endif

# --------------------------------------
# == Start ====
# build: User command.
PHONY := all
all:  \
build-gramado-os \
copy-extras \
/mnt/gramadoxvhd \
vhd-mount \
vhd-copy-files \
vhd-unmount \
clean    

# Giving permitions to run.
	chmod 755 ./run
	chmod 755 ./runkvm
# tests
	chmod 755 ./run2
	chmod 755 ./runkvm2
	@echo "Done?"

# --------------------------------------
# build: Developer comand 1.
# install
# Build the images and put them all into ../aa/base/ folder.
PHONY := install
install: do_install
do_install: \
build-gramado-os  


# --------------------------------------
# build: Developer comand 2.
# image
# Copy all the files from ../aa/base/ to the VHD.
PHONY := image
image: do_image
do_image: \
/mnt/gramadoxvhd    \
vhd-mount          \
vhd-copy-files     \
vhd-unmount        \

# --------------------------------------
#::0
# ~ Step 0: gramado files.
PHONY := build-gramado-os  
build-gramado-os:     
	@echo ":: [] Building VHD, bootloaders and kernel image."
# options: 
# main.asm and main2.asm
# O mbr só consegue ler o root dir para pegar o BM.BIN
# See: stage1.asm
# O BM.BIN só consegue ler o root dir pra pegar o BL.BIN
# See: main.asm
# the kernel image
# O BL.BIN procura o kernel no diretorio GRAMADO/
# See: fs/loader.c

#----------------------------------
# Create the virtual disk 0.
	$(Q)$(NASM) boot/vd/fat/main.asm \
	-I boot/vd/fat/ \
	-o GRAMADO.VHD 
# Create backup for MBR 0.
	$(Q)$(NASM) boot/vd/fat/stage1.asm \
	-I boot/vd/fat/ \
	-o MBR0.BIN
	sudo cp MBR0.BIN  ../aa/base/

# ::Build BM.BIN. (legacy, no dialog)
	$(Q)$(MAKE) -C boot/x86/bm/ 
# Copy to the target folder.
	sudo cp boot/x86/bin/BM.BIN  ../aa/base/

# #BUGBUG 
# Suspended!!!!
# Something is affecting the window server,
# if we enter in the graphics mode without entering
# the shell first. There are two routines 
# to initialize the gui mode. Only one is good.
# ::Build BM2.BIN. (Interface with dialog)
	$(Q)$(MAKE) -C boot/x86/bm2/ 
# Copy to the target folder.
	sudo cp boot/x86/bin/BM2.BIN  ../aa/base/

# ::Build BL.BIN.
	$(Q)$(MAKE) -C boot/x86/bl/ 
# Copy to the target folder.
	sudo cp boot/x86/bin/BL.BIN  ../aa/base/

# ::Build kernel image.
	$(Q)$(MAKE) -C kernel/
# Copy to the target folder.
	sudo cp kernel/KERNEL.BIN  ../aa/base/GRAMADO

# ::Build the ring0 module image.
	$(Q)$(MAKE) -C hals/newm0/
# Copy the ring0 module image.
	sudo cp hals/newm0/MOD0.BIN  ../aa/base/

# ::Build the ring0 module image.
	$(Q)$(MAKE) -C hals/newm1/
# Copy the ring0 module image.
	sudo cp hals/newm1/MOD1.BIN  ../aa/base/

#todo
# ::Build the ring0 module image.
#	$(Q)$(MAKE) -C newm1/
# Copy the ring0 module image.
#	sudo cp newm1/MOD1.BIN  ../aa/base/

# Install BMPs
	sudo cp ../aa/assets/themes/537/*.BMP  ../aa/base/
#	sudo cp ../aa/assets/themes/537/*.BMP  ../aa/base/

# ::Build libraries.
	$(Q) $(MAKE) -C libs/
# Don't copy to the disk.

# :: init.bin 
# Building init process.
	$(Q) $(MAKE) -C init/
# Copy to the target folder.
	-sudo cp init/bin/INIT.BIN  ../aa/base/ 

	@echo "~build-gramado-os end?"

# --------------------------------------
PHONY := copy-extras
copy-extras:
# Let's copy some images from zing/ and zz/

	@echo "copy-extras"

# zing
# Copying every image from zing/.
	@echo ":: Copying every image from zing"

	-sudo cp ../zing/barnsh/bin/SHELL.BIN     ../aa/base/PROGRAMS/

# Copy to the target folder.
	-sudo cp ../zing/commands/bin/SHUTDOWN.BIN  ../aa/base/
	-sudo cp ../zing/commands/bin/REBOOT.BIN    ../aa/base/
	-sudo cp ../zing/commands/bin/CAT.BIN       ../aa/base/
	-sudo cp ../zing/commands/bin/UNAME.BIN     ../aa/base/

	-sudo cp ../zing/commands/bin/VGA1.BIN      ../aa/base/PROGRAMS/
	-sudo cp ../zing/commands/bin/TPRINTF.BIN   ../aa/base/PROGRAMS/
	-sudo cp ../zing/commands/bin/SHOWFUN.BIN   ../aa/base/PROGRAMS/
	-sudo cp ../zing/commands/bin/CMP.BIN       ../aa/base/PROGRAMS/
	-sudo cp ../zing/commands/bin/SUM.BIN       ../aa/base/PROGRAMS/
	-sudo cp ../zing/commands/bin/TASCII.BIN    ../aa/base/PROGRAMS/
	-sudo cp ../zing/commands/bin/FALSE.BIN     ../aa/base/PROGRAMS/
	-sudo cp ../zing/commands/bin/TRUE.BIN      ../aa/base/PROGRAMS/
	-sudo cp ../zing/commands/bin/GRAMCNF.BIN   ../aa/base/PROGRAMS/
	#...

	-sudo cp ../zing/commands/bin/N9.BIN   ../aa/base/PROGRAMS/
	-sudo cp ../zing/commands/bin/N10.BIN  ../aa/base/PROGRAMS/
	-sudo cp ../zing/commands/bin/N11.BIN  ../aa/base/PROGRAMS/

# netd
	-sudo cp ../zing/netd/bin/GNS.BIN     ../aa/base/
	-sudo cp ../zing/netd/bin/GNSSRV.BIN  ../aa/base/

# zz
# Copying every image from zz/.
	@echo ":: Copying every image from zz"

# Graphics engine
	-sudo cp ../zz/demos/eng/bin/ENG.BIN  ../aa/base/

# Display server.
	-sudo cp ../zz/gramland/bin/GRAMLAND.BIN  ../aa/base/

# winapps (Students)

# winapps: Unit 3
	-sudo cp ../zz/winapps/bin/GWS.BIN   ../aa/base/
	-sudo cp ../zz/winapps/bin/GDM.BIN   ../aa/base/
	-sudo cp ../zz/winapps/bin/GDM2.BIN  ../aa/base/
# winapps: Unit 2
	-sudo cp ../zz/winapps/bin/TERMINAL.BIN  ../aa/base/
# winapps: Unit 1
	-sudo cp ../zz/winapps/bin/EDITOR.BIN   ../aa/base/
	-sudo cp ../zz/winapps/bin/FILEMAN.BIN  ../aa/base/
	-sudo cp ../zz/winapps/bin/CMDLINE.BIN  ../aa/base/PROGRAMS/
	-sudo cp ../zz/winapps/bin/BROWSER.BIN  ../aa/base/
	-sudo cp ../zz/winapps/bin/DOCV.BIN     ../aa/base/PROGRAMS/

	@echo "~ copy-extras"

# --------------------------------------
#::2
# Step 2: /mnt/gramadoxvhd  - Creating the directory to mount the VHD.
/mnt/gramadoxvhd:
	@echo "========================="
	@echo "Build: Creating the directory to mount the VHD ..."
	sudo mkdir /mnt/gramadoxvhd

# --------------------------------------
#::3
# ~ Step 3: vhd-mount - Mounting the VHD.
vhd-mount:
	@echo "=========================="
	@echo "Build: Mounting the VHD ..."
	-sudo umount /mnt/gramadoxvhd
	sudo mount -t vfat -o loop,offset=32256 GRAMADO.VHD /mnt/gramadoxvhd/

# --------------------------------------
#::4
# ~ Step 4 vhd-copy-files - Copying files into the mounted VHD.
# Copying the ../aa/base/ folder into the mounted VHD.
vhd-copy-files:
	@echo "========================="
	@echo "Build: Copying files into the mounted VHD ..."
	# Copy ../aa/base/
	# sends everything from disk/ to root.
	sudo cp -r ../aa/base/*  /mnt/gramadoxvhd

# --------------------------------------
#:::5
# ~ Step 5 vhd-unmount  - Unmounting the VHD.
vhd-unmount:
	@echo "======================"
	@echo "Build: Unmounting the VHD ..."
	sudo umount /mnt/gramadoxvhd

# --------------------------------------
# Run on qemu.
PHONY := run
run: do_run
do_run:
	sh ./run

# --------------------------------------
# Run on qemu using kvm.
PHONY := runkvm
runkvm: do_runkvm
do_runkvm:
	sh ./runkvm

# --------------------------------------
# Basic clean.
clean:
	-rm *.o
	@echo "~clean"

# --------------------------------------
# Clean up all the mess.
clean-all: clean

	-rm *.VHD
	-rm *.ISO

# ==================

# Clear boot images
	-rm -rf boot/x86/bin/*.BIN
# Clear newos kernel image
	-rm -rf kernel/KERNEL.BIN
# Clear the ring0 module images
	-rm -rf hals/newm0/MOD0.BIN
	-rm -rf hals/newm1/MOD1.BIN
# ==================
# Clear the disk cache
	-rm -rf ../aa/base/*.BIN 
	-rm -rf ../aa/base/*.BMP
	-rm -rf ../aa/base/EFI/BOOT/*.EFI 
	-rm -rf ../aa/base/GRAMADO/*.BIN 
	-rm -rf ../aa/base/PROGRAMS/*.BIN 
	-rm -rf ../aa/base/USERS/*.BIN 
# ==================
# Clear the init process.
	-rm init/bin/*.BIN
	-rm init/*.o
# ==================
# Clear the dependencies.
	-rm libs/fonts/bin/*.FON
	-rm libs/libio01/obj/*.o
	-rm libs/rtl/obj/*.o

	@echo "~clean-all"

# --------------------------------------
# Usage instructions.
usage:
	@echo "Building everything:"
	@echo "make all"
	@echo "Clear the mess to restart:"
	@echo "make clean-all"
	@echo "Testing on qemu:"
	@echo "./run"
	@echo "./runkvm"

# --------------------------------------
# Danger zone!
# This is gonna copy th image into the real HD.
# My host is running on sdb and i copy the image into sda.
# It is because the sda is in primary master IDE.
# Gramado has been tested on sda
# and the Fred's Linux host machine is on sdb.
danger-install-sda:
	sudo dd if=./GRAMADO.VHD of=/dev/sda
danger-install-sdb:
	sudo dd if=./GRAMADO.VHD of=/dev/sdb

# End.

