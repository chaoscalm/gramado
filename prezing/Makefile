
all:
# Libs and assets.
	make -C omega1/
# Drivers and servers.
	make -C omega2/
# Client-side GUI applications.
	make -C omega3/
clean-all:
# omega1
	-rm -f omega1/libs/libdisp/obj/*.o
	-rm -f omega1/libs/libgr/obj/*.o
	-rm -f omega1/libs/libgr3d/obj/*.o
	-rm -f omega1/libs/libgws/obj/*.o
	-rm -f omega1/libs/rtl/obj/*.o
# omega2
	-rm -f omega2/drivers/bin/*.BIN
	-rm -f omega2/servers/bin/*.BIN
# omega3
	-rm -f omega3/apps/bin/*.BIN


