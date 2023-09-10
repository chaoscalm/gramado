all:

	make -C libs/
# The Gramado Network Server
	make -C server/
# First client for GNS.
	make -C client/ 
	
clean:
	-rm -f libs/libgns/obj/*.o
	-rm -f libs/rtl/obj/*.o

	-rm -f bin/*.BIN

