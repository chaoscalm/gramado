
# ring 3 libs.

all:

# Display support (Server-side?)
	#make -C libdisp/

# Gramado Network Server (Client-side)
# Client-side lib for netctld.
	make -C libgns/

# Gramado Network Server (Client-side)
# Client-side lib for nicctld.
	make -C libgns2/


# Graphics support (Server-side?)
#	make -C libgr/
# 3D Graphics support (Server-side?)
#	make -C libgr3d/

# Gramado Window System
# Client-side library for the Display server.
#	make -C libgws/

# I/O ports in ring3.
	make -C libio01/
# libc and more.
	make -C rtl/
	
clean:

	-rm -f libgns/*.o
	-rm -f libgns2/*.o

	-rm -f libio01/*.o
	-rm -f rtl/*.o

	-rm -f libgns/obj/*.o
	-rm -f libio01/obj/*.o
	-rm -f rtl/obj/*.o




