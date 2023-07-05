#A - Facility II
#desktop
# Gramado DE

PRODUCT_NAME  = Gramado DE
EDITION_NAME  = GUI

VERSION_MAJOR = ?
VERSION_MINOR = ?
VERSION_BUILD = ?

all:

# libs
	make -C libs/rtl/
	make -C libs/libgws/
	make -C libs/libdisp/
	make -C libs/libgr/
	make -C libs/libgr3d/

# ----------------
# Gramland window server.
	make -C services/gramland/

# ----------------
# Shell

# apps: Unit 3
	make -C apps/client
	make -C apps/gdm
	make -C apps/setup
# apps: Unit 2
	make -C apps/terminal  
# apps: Unit 1
	make -C apps/cmdline
	make -C apps/editor
	make -C apps/browser
	make -C apps/docv

# ----------------
# demos/

# Graphics engine. (3D demos)
	make -C demos/eng/

clean-all:

	-rm -f apps/bin/*.BIN

	-rm -f demos/eng/bin/*.BIN

	-rm -f libs/libgws/obj/*.o
	-rm -f libs/libgr/obj/*.o
	-rm -f libs/libgr3d/obj/*.o
	-rm -f libs/libdisp/obj/*.o
	-rm -f libs/rtl/obj/*.o
	
	-rm -f services/gramland/bin/*.BIN
	
