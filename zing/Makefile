# Makefile in the userland/ folder.
# Gramado DE

# zing/ depends on zing/libs/.

PRODUCT_NAME  = Gramado DE
EDITION_NAME  = GUI

VERSION_MAJOR = ?
VERSION_MINOR = ?
VERSION_BUILD = ?

all:
# gramland
	make -C gramado/
# c3 - NETCTL
	make -C netd/
clean-all:

# gramland and eng
	-rm -f gramado/eng/bin/*.BIN
	-rm -f gramado/swamp/bin/*.BIN
	#-rm -f gramado/libs/libgns/obj/*.o
	-rm -f gramado/libs/rtl/obj/*.o

# NETCTL
	-rm -f netd/bin/*.BIN
	-rm -f netd/libs/libgns/obj/*.o
	-rm -f netd/libs/rtl/obj/*.o

