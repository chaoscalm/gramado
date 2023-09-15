# Makefile in the ama/ folder.
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
# Build the images and put them all into ../zz/omega3/base/ folder.
PHONY := install
install: do_install
do_install: \
build-gramado-os  


# --------------------------------------
# build: Developer comand 2.
# image
# Copy all the files from ../zz/omega3/base/ to the VHD.
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
	sudo cp MBR0.BIN  ../zz/omega3/base/

# ::Build BM.BIN. (legacy, no dialog)
	$(Q)$(MAKE) -C boot/x86/bm/ 
# Copy to the target folder.
	sudo cp boot/x86/bin/BM.BIN  ../zz/omega3/base/

# #BUGBUG 
# Suspended!!!!
# Something is affecting the window server,
# if we enter in the graphics mode without entering
# the shell first. There are two routines 
# to initialize the gui mode. Only one is good.
# ::Build BM2.BIN. (Interface with dialog)
	$(Q)$(MAKE) -C boot/x86/bm2/ 
# Copy to the target folder.
	sudo cp boot/x86/bin/BM2.BIN  ../zz/omega3/base/

# ::Build BL.BIN.
	$(Q)$(MAKE) -C boot/x86/bl/ 
# Copy to the target folder.
	sudo cp boot/x86/bin/BL.BIN  ../zz/omega3/base/


#----------------------------------
# ::Build the ring0 module image.
	$(Q)$(MAKE) -C ../aa/mods/newm0/
# Copy the ring0 module image.
	sudo cp ../aa/mods/newm0/MOD0.BIN  ../zz/omega3/base/

# ::Build the ring0 module image.
	$(Q)$(MAKE) -C ../aa/mods/newm1/
# Copy the ring0 module image.
	sudo cp ../aa/mods/newm1/MOD1.BIN  ../zz/omega3/base/

#----------------------------------
# ::Build kernel image.
	$(Q)$(MAKE) -C kernel/
# Copy to the target folder.
	sudo cp kernel/KERNEL.BIN  ../zz/omega3/base/GRAMADO

#----------------------------------
#Copy the init process
	sudo cp ../zing/graminit/init/bin/INIT.BIN  ../zz/omega3/base/

#----------------------------------
# Install BMPs
#	sudo cp ../zz/omega3/assets/themes/amazing/*.BMP  ../zz/omega3/base/
	sudo cp ../zz/omega3/assets/themes/honey/*.BMP    ../zz/omega3/base/

	@echo "~build-gramado-os end?"

# --------------------------------------
PHONY := copy-extras
copy-extras:
# Let's copy some images from zing/ and zz/

	@echo "copy-extras"

#-----------------------------
# zing
# Copying every image from zing/.
	@echo ":: Copying every image from zing"

#graminit : Already did right above.
#	sudo cp ../zing/graminit/init/bin/INIT.BIN  ../zz/omega3/base/
# Graphics engine
	-sudo cp ../zing/gramlan0/eng/bin/ENG.BIN  ../zz/omega3/base/
# Display server.
	-sudo cp ../zing/gramlan0/gramland/bin/GRAMLAND.BIN  ../zz/omega3/base/
# c3
	-sudo cp ../zing/netd/bin/NETCTL.BIN   ../zz/omega3/base/
	-sudo cp ../zing/netd/bin/NETCTLD.BIN  ../zz/omega3/base/

#-----------------------------
# zz
# Copying every image from zz/.
	@echo ":: Copying every image from zz"

# winapps (Students)

# winapps: Unit 3
	-sudo cp ../zz/omega2/apps/bin/GWS.BIN   ../zz/omega3/base/
	-sudo cp ../zz/omega2/apps/bin/GDM.BIN   ../zz/omega3/base/
	-sudo cp ../zz/omega2/apps/bin/GDM2.BIN  ../zz/omega3/base/
# winapps: Unit 2
	-sudo cp ../zz/omega2/apps/bin/TERMINAL.BIN  ../zz/omega3/base/
# winapps: Unit 1
	-sudo cp ../zz/omega2/apps/bin/EDITOR.BIN   ../zz/omega3/base/
	-sudo cp ../zz/omega2/apps/bin/FILEMAN.BIN  ../zz/omega3/base/
	-sudo cp ../zz/omega2/apps/bin/CMDLINE.BIN  ../zz/omega3/base/PROGRAMS/
	-sudo cp ../zz/omega2/apps/bin/BROWSER.BIN  ../zz/omega3/base/
	-sudo cp ../zz/omega2/apps/bin/DOCV.BIN     ../zz/omega3/base/PROGRAMS/


# Copy to the target folder.
	-sudo cp ../zz/omega2/commands/bin/SHELL.BIN     ../zz/omega3/base/
	-sudo cp ../zz/omega2/commands/bin/SHUTDOWN.BIN  ../zz/omega3/base/
	-sudo cp ../zz/omega2/commands/bin/REBOOT.BIN    ../zz/omega3/base/
	-sudo cp ../zz/omega2/commands/bin/CAT.BIN       ../zz/omega3/base/
	-sudo cp ../zz/omega2/commands/bin/UNAME.BIN     ../zz/omega3/base/

	-sudo cp ../zz/omega2/commands/bin/VGA1.BIN      ../zz/omega3/base/PROGRAMS/
	-sudo cp ../zz/omega2/commands/bin/TPRINTF.BIN   ../zz/omega3/base/PROGRAMS/
	-sudo cp ../zz/omega2/commands/bin/SHOWFUN.BIN   ../zz/omega3/base/PROGRAMS/
	-sudo cp ../zz/omega2/commands/bin/CMP.BIN       ../zz/omega3/base/PROGRAMS/
	-sudo cp ../zz/omega2/commands/bin/SUM.BIN       ../zz/omega3/base/PROGRAMS/
	-sudo cp ../zz/omega2/commands/bin/TASCII.BIN    ../zz/omega3/base/PROGRAMS/
	-sudo cp ../zz/omega2/commands/bin/FALSE.BIN     ../zz/omega3/base/PROGRAMS/
	-sudo cp ../zz/omega2/commands/bin/TRUE.BIN      ../zz/omega3/base/PROGRAMS/
	-sudo cp ../zz/omega2/commands/bin/GRAMCNF.BIN   ../zz/omega3/base/PROGRAMS/
	#...

	-sudo cp ../zz/omega2/commands/bin/N9.BIN   ../zz/omega3/base/PROGRAMS/
	-sudo cp ../zz/omega2/commands/bin/N10.BIN  ../zz/omega3/base/PROGRAMS/
	-sudo cp ../zz/omega2/commands/bin/N11.BIN  ../zz/omega3/base/PROGRAMS/

# c2
	-sudo cp ../zz/omega2/drivers/nicd/bin/NICCTL.BIN   ../zz/omega3/base/
	-sudo cp ../zz/omega2/drivers/nicd/bin/NICCTLD.BIN  ../zz/omega3/base/

	-sudo cp ../zz/omega2/drivers/bin/VGA1.BIN  ../zz/omega3/base/

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
# Copying the ../zz/omega3/base/ folder into the mounted VHD.
vhd-copy-files:
	@echo "========================="
	@echo "Build: Copying files into the mounted VHD ..."
	# Copy ../zz/omega3/base/
	# sends everything from disk/ to root.
	sudo cp -r ../zz/omega3/base/*  /mnt/gramadoxvhd

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
	-rm -rf ../aa/mods/newm0/MOD0.BIN
	-rm -rf ../aa/mods/newm1/MOD1.BIN

# ==================
# Clear the init process.
	-rm ../zing/gramlan0/init/bin/*.BIN
	-rm ../zing/gramlan0/init/*.o

# ==================
# Clear the disk cache
	-rm -rf ../zz/omega3/base/*.BIN 
	-rm -rf ../zz/omega3/base/*.BMP
	-rm -rf ../zz/omega3/base/EFI/BOOT/*.EFI 
	-rm -rf ../zz/omega3/base/GRAMADO/*.BIN 
	-rm -rf ../zz/omega3/base/PROGRAMS/*.BIN 
	-rm -rf ../zz/omega3/base/USERS/*.BIN 

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

