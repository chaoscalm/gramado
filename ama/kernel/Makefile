
# Makefile for the gramado kernel.

linkTarget = KERNEL.BIN

# See: https://linux.die.net/man/1/ld
# -s --strip-all:   Omit all symbol information from the output file.
# -x --discard-all: Delete all local symbols.
# -static: Do not link against shared libraries. 
# -M --print-map:   Print a link map to the standard output.
# LDFLAGS := -m elf_x86_64 -static
# LDFLAGS := -m elf_x86_64 -s -x -static  
linkFlags := -m elf_x86_64 \
-s -x -static -T arch/x86_64/startup/link.ld

# Make variables (CC, etc...)
AS	= as
LD	= ld
CC	= gcc
AR	= ar
MAKE	= make
NASM	= nasm
OBJCOPY	= objcopy
OBJDUMP	= objdump
LEX	= flex
YACC	= bison
PERL	= perl
PYTHON	= python
PYTHON2	= python2
PYTHON3	= python3
RUBY	= ruby


#
# Config
#

# Quit mode?
ifndef CONFIG_USE_VERBOSE
	CONFIG_USE_VERBOSE = 0
endif

# ' ' = Print
# '@' = Do not print.
ifeq ($(CONFIG_USE_VERBOSE),1)
	Q =
else
	Q = @
endif

# test: gramado 64bit
# See: https://gcc.gnu.org/onlinedocs/gcc/Code-Gen-Options.html
CFLAGS := \
	-Wall \
	-Wundef \
	-Wmissing-prototypes \
	-Wno-uninitialized \
	-Wno-format-security \
	-Wno-trigraphs \
	-Werror=strict-prototypes \
	-Werror=implicit-function-declaration \
	-Werror=implicit-int \
	-Werror=return-type \
	-std=gnu89 \
	-m64 \
	-s \
	-static \
	-fcommon \
	-fgnu89-inline \
	-finline-functions \
	-fshort-wchar \
	-ffreestanding \
	-fleading-underscore \
	-fstrict-overflow \
	-nostdlib \
	-nodefaultlibs \
	-nostdinc \
	-fno-builtin \
	-fno-stack-protector \
	-fno-strict-aliasing \
	-fno-PIE \
	-fno-pie \
	-fno-omit-frame-pointer \
	-fno-optimize-sibling-calls    


# ========================
# Config

#test
#CONFIG_MAIN=y
# ...

# ========================
# Objects
# Classes: Head | Body 
# ========================

# ========================
# :: Head
# See: k4_boot/
objects-y := head_64.o 

# ========================
# :: Body 
# (Kernel subsystems)
objects-y += ar_mm.o  
objects-y += ar_crt.o  
objects-y += ar_dev.o  
objects-y += ar_user.o    
objects-y += ar_ke.o  
objects-y += ar_net.o  
objects-y += ar_fs.o  
objects-y += ar_zcall.o
    
# ========================
PHONY := all
all: k1 k2 k3 \
link-kernel \
clean    

	@echo "Done?"
#----------------
# The head.
k1:
	@echo "Compiling: Compiling k1/"
	$(MAKE) -C arch/

#----------------
# Legacy - The Unix Engine.
k2:
	@echo "Compiling: Compiling k2/"
	$(MAKE) -C crt/
	$(MAKE) -C dev/
	$(MAKE) -C mm/
	$(MAKE) -C fs/
	$(MAKE) -C net/

#----------------
# Originals - Cali.
k3:
	@echo "Compiling: Compiling k3/"
	$(MAKE) -C ke/
	$(MAKE) -C user/
	$(MAKE) -C zcall/

#----------------
link-kernel:
	@echo "Linking: Linking the kernel image ..."
	$(LD) $(linkFlags) -o $(linkTarget) $(objects-y)    
clean:
	rm -rf *.o   
	@echo "~clean"

