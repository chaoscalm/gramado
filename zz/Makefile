
all:

# Libs and assets.
	make -C omega1/

# Drivers and servers.
	make -C omega2/

# Commands
	make -C omega3/

# Client-side GUI applications.
	make -C omega4/

clean-all:

# omega1
	-rm -f omega1/libs/libdisp/obj/*.o
	-rm -f omega1/libs/libgr/obj/*.o
	-rm -f omega1/libs/libgr3d/obj/*.o
	-rm -f omega1/libs/libgws/obj/*.o
	-rm -f omega1/libs/rtl/obj/*.o

	-rm -f omega2/drivers/bin/*.BIN
	-rm -f omega2/servers/bin/*.BIN

	-rm -f omega3/commands/bin/*.BIN

	-rm -f omega4/apps/bin/*.BIN

