
CALI = ../cali

NASM = nasm

# Internal files
# Used to build the kernel.
KERNEL_INCLUDE := -I $(CALI)/includes/   

STARTUP_INCLUDE := -I x86_64/startup/  

all:
	$(NASM) x86_64/startup/head_64.asm \
	$(KERNEL_INCLUDE) \
	$(STARTUP_INCLUDE) \
	-f elf64 -o head_64.o    

	cp head_64.o ../
	rm *.o
	
clean:
	rm *.o     


	
