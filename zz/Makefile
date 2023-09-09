
# zz/ depends on zing/libs/.

all:
	make -C libs/
	make -C c1/
#	make -C games
	make -C winapps

clean-all:

	-rm -f libs/libdisp/obj/*.o
	-rm -f libs/libgr/obj/*.o
	-rm -f libs/libgr3d/obj/*.o
	-rm -f libs/libgws/obj/*.o

	-rm c1/eng/bin/*.BIN
	-rm c1/gramland/bin/*.BIN
#	-rm games/game1/bin/*.BIN
	-rm winapps/bin/*.BIN


