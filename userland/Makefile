# Makefile in the userland/ folder.
# Gramado DE

PRODUCT_NAME  = Gramado DE
EDITION_NAME  = GUI

VERSION_MAJOR = ?
VERSION_MINOR = ?
VERSION_BUILD = ?

all:

# ----------------
# libs
# First of all :)
	make -C libs/

# ----------------
# Client-side GUI applications.
	make -C apps/

# ----------------
# Ring 3 posix-like commands.
	make -C commands/

# ----------------
# demos/
# Graphics engine. (3D demos)
	make -C demos/

# ----------------
# games

# ----------------
# netd
	make -C netd/ 

# ----------------
# Services
	make -C services/

# ----------------
# The shell command.
	make -C shell/

clean-all:
	-rm -f apps/bin/*.BIN
	-rm -f commands/bin/*.BIN
	-rm -f demos/eng/bin/*.BIN
	-rm -f libs/libdisp/obj/*.o
	-rm -f libs/libgr/obj/*.o
	-rm -f libs/libgr3d/obj/*.o
	-rm -f libs/libgws/obj/*.o
	-rm -f libs/libio01/obj/*.o
	-rm -f libs/rtl/obj/*.o
	-rm -f netd/bin/*.BIN
	-rm -f services/gramland/bin/*.BIN
	
