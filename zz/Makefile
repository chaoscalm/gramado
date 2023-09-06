
# zz/ depends on zing/libs/.

all:
	make -C libs/
	make -C demos
#	make -C games
	make -C gramland
	make -C winapps

clean-all:

	-rm -f libs/libdisp/obj/*.o
	-rm -f libs/libgr/obj/*.o
	-rm -f libs/libgr3d/obj/*.o
	-rm -f libs/libgws/obj/*.o

	-rm demos/eng/bin/*.BIN
#	-rm games/game1/bin/*.BIN
	-rm gramland/bin/*.BIN
	-rm winapps/bin/*.BIN


