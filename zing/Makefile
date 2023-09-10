# Makefile in the userland/ folder.
# Gramado DE

# zing/ depends on zing/libs/.

PRODUCT_NAME  = Gramado DE
EDITION_NAME  = GUI

VERSION_MAJOR = ?
VERSION_MINOR = ?
VERSION_BUILD = ?

all:

# init
	make -C graminit/
# gramland
	make -C gramlan0/
# c3 - NETCTL
	make -C netd/

clean-all:

# init
	-rm graminit/init/bin/*.BIN

# gramland and eng
	-rm gramlan0/eng/bin/*.BIN
	-rm gramlan0/gramland/bin/*.BIN

# NETCTL
	-rm -f netd/bin/*.BIN

