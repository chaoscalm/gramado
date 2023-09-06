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
# Ring 3 posix-like commands.
	make -C commands/

# ----------------
# netd
	make -C netd/

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
	-rm -f commands/bin/*.BIN


	-rm -f libs/libgns/obj/*.o
	-rm -f libs/libio01/obj/*.o
	-rm -f libs/rtl/obj/*.o

	-rm -f netd/bin/*.BIN
	-rm -f services/bin/*.BIN

#	-rm -f wdemos/eng/bin/*.BIN
#	-rm -f winapps/bin/*.BIN
