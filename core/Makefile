#E - Facility I
#core
# Gramado Kernel
# License: BSD License
# Compiling on gcc 9.4.0
# Linking on ld 2.34


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
	@echo "Done?"

# --------------------------------------
# build: Developer comand 1.
# install
# Build the images and put them all into ../base/ folder.
PHONY := install
install: do_install
do_install: \
build-gramado-os  


# --------------------------------------
# build: Developer comand 2.
# image
# Copy all the files from ../base/ to the VHD.
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
	sudo cp MBR0.BIN  ../base/

# ::Build BM.BIN. (legacy, no dialog)
	$(Q)$(MAKE) -C boot/x86/bm/ 
# Copy to the target folder.
	sudo cp boot/x86/bin/BM.BIN  ../base/

# #BUGBUG 
# Suspended!!!!
# Something is affecting the window server,
# if we enter in the graphics mode without entering
# the shell first. There are two routines 
# to initialize the gui mode. Only one is good.
# ::Build BM2.BIN. (Interface with dialog)
	$(Q)$(MAKE) -C boot/x86/bm2/ 
# Copy to the target folder.
	sudo cp boot/x86/bin/BM2.BIN  ../base/

# ::Build BL.BIN.
	$(Q)$(MAKE) -C boot/x86/bl/ 
# Copy to the target folder.
	sudo cp boot/x86/bin/BL.BIN  ../base/

# ::Build kernel image.
	$(Q)$(MAKE) -C kernel/
# Copy to the target folder.
	sudo cp kernel/KERNEL.BIN  ../base/GRAMADO

# ::Build the ring0 module image.
	$(Q)$(MAKE) -C newm0/
# Copy the ring0 module image.
	sudo cp newm0/MOD0.BIN  ../base/

#todo
# ::Build the ring0 module image.
#	$(Q)$(MAKE) -C newm1/
# Copy the ring0 module image.
#	sudo cp newm1/MOD1.BIN  ../base/


# Install BMPs
	sudo cp ../meta/assets/themes/537/*.BMP  ../base/

# ::Build libraries.
	$(Q) $(MAKE) -C libs/
# Don't copy to the disk.

# :: init.bin 
# Building init process.
	$(Q) $(MAKE) -C init/
# Copy to the target folder.
	-sudo cp init/bin/INIT.BIN  ../base/ 

	@echo "~build-gramado-os end?"

# --------------------------------------
PHONY := copy-extras
copy-extras:
# Let's copy some images from userland/

	@echo "copy-extras"

# :: userland
# Copying every image from userland/.

	@echo ":: Copying Window server and clients."

# Copy to the target folder.
	-sudo cp ../userland/commands/bin/SHUTDOWN.BIN  ../base/
	-sudo cp ../userland/commands/bin/REBOOT.BIN    ../base/
	-sudo cp ../userland/commands/bin/CAT.BIN       ../base/
	-sudo cp ../userland/commands/bin/UNAME.BIN     ../base/

	-sudo cp ../userland/commands/bin/VGA1.BIN      ../base/PROGRAMS/
	-sudo cp ../userland/commands/bin/SHELL.BIN     ../base/PROGRAMS/
	-sudo cp ../userland/commands/bin/TPRINTF.BIN   ../base/PROGRAMS/
	-sudo cp ../userland/commands/bin/SHOWFUN.BIN   ../base/PROGRAMS/
	-sudo cp ../userland/commands/bin/CMP.BIN       ../base/PROGRAMS/
	-sudo cp ../userland/commands/bin/SUM.BIN       ../base/PROGRAMS/
	-sudo cp ../userland/commands/bin/TASCII.BIN    ../base/PROGRAMS/
	-sudo cp ../userland/commands/bin/FALSE.BIN     ../base/PROGRAMS/
	-sudo cp ../userland/commands/bin/TRUE.BIN      ../base/PROGRAMS/
	-sudo cp ../userland/commands/bin/GRAMCNF.BIN   ../base/PROGRAMS/
	#...

	-sudo cp ../userland/commands/bin/N9.BIN   ../base/PROGRAMS/
	-sudo cp ../userland/commands/bin/N10.BIN  ../base/PROGRAMS/
	-sudo cp ../userland/commands/bin/N11.BIN  ../base/PROGRAMS/

# Graphics engine
	-sudo cp ../userland/demos/eng/bin/ENG.BIN  ../base/
# Window server
	-sudo cp ../userland/services/gramland/bin/GRAMLAND.BIN  ../base/

# netd
	-sudo cp ../userland/netd/bin/GNSSRV.BIN  ../base/
	-sudo cp ../userland/netd/bin/GNS.BIN     ../base/

#
# Shell
#

# apps, apps and apps: (Students)

# apps: Unit 3
	-sudo cp ../userland/apps/bin/GWS.BIN   ../base/
	-sudo cp ../userland/apps/bin/GDM.BIN   ../base/
	-sudo cp ../userland/apps/bin/GDM2.BIN  ../base/
# apps: Unit 2
	-sudo cp ../userland/apps/bin/TERMINAL.BIN  ../base/
# apps: Unit 1
	-sudo cp ../userland/apps/bin/EDITOR.BIN   ../base/
	-sudo cp ../userland/apps/bin/FILEMAN.BIN  ../base/
	-sudo cp ../userland/apps/bin/CMDLINE.BIN  ../base/PROGRAMS/
	-sudo cp ../userland/apps/bin/BROWSER.BIN  ../base/
	-sudo cp ../userland/apps/bin/DOCV.BIN     ../base/PROGRAMS/

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
# Copying the ../base/ folder into the mounted VHD.
vhd-copy-files:
	@echo "========================="
	@echo "Build: Copying files into the mounted VHD ..."
	# Copy ../base/
	# sends everything from disk/ to root.
	sudo cp -r ../base/*  /mnt/gramadoxvhd

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
# os tier.

# Clear boot images
	-rm -rf boot/x86/bin/*.BIN
# Clear newos kernel image
	-rm -rf kernel/KERNEL.BIN
# Clear the ring0 module image
	-rm -rf newm0/MOD0.BIN
# Clear the disk cache
	-rm -rf ../base/*.BIN 
	-rm -rf ../base/*.BMP
	-rm -rf ../base/EFI/BOOT/*.EFI 
	-rm -rf ../base/GRAMADO/*.BIN 
	-rm -rf ../base/PROGRAMS/*.BIN 
	-rm -rf ../base/USERS/*.BIN 

# ==================
# exposed tier.

	-rm init/bin/*.BIN
	-rm init/init/*.o
	-rm indigo/bin/*.BIN
	-rm libs/fonts/bin/*.FON
	-rm libs/libgns/obj/*.o
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

