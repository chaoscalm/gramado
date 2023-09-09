# Makefile in the userland/ folder.
# Gramado DE

# zing/ depends on zing/libs/.

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
# The shell command.
	make -C barnsh/

# ----------------
# c2 - NICCTL
	make -C c2/
# c3 - NETCTL
	make -C c3/

# ----------------
# Ring 3 posix-like commands.
	make -C commands/


# ----------------
# Services
	make -C services/

# ----------------
# wdemos/
# Graphics engine. (3D demos)
# zz
#	make -C wdemos/

# ----------------
# wgames

# ----------------
# Client-side GUI applications.
# zz
#	make -C winapps/

clean-all:

	-rm -f barnsh/bin/*.BIN

	-rm -f c2/bin/*.BIN
	-rm -f c3/bin/*.BIN

	-rm -f commands/bin/*.BIN

	-rm -f libs/libgns/obj/*.o
	-rm -f libs/libgns2/obj/*.o
	-rm -f libs/libio01/obj/*.o
	-rm -f libs/rtl/obj/*.o

	-rm -f services/bin/*.BIN

