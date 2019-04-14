#
#  Makefile for mazewar.
#

CFILES =	actions.c calldaemon.c comm.c death.c getsocket.c init.c \
		initpix.c initplayer.c ioctls.c main.c packet.c player.c \
		redraw.c send.c service.c setkeyok.c ualarm.c \
		util.c viewwin.c wintext.c work.c

OFILES =	actions.o calldaemon.o comm.o death.o getsocket.o init.o \
		initplayer.o ioctls.o main.o packet.o send.o \
		service.o setkeyok.o ualarm.o util.o work.o \
		../daemon/syserr.o ../daemon/vers.o

SUNFILES =	initpix.o player.o redraw.o viewwin.o wintext.o

HFILES =	../h/defs.h ../h/struct.h ../h/extern.h ../h/sunscreen.h \
		../h/hallmap.h ../h/arrows.h ../h/wall_image.h ../h/data.h \
		../h/corners.h

LIBS =		-lm -lcurses -ltermlib
SUNLIBS	= 	$(LIBS) -lpixrect

CFLAGS =	-O

vax:		$(OFILES)
		$(CC) $(CFLAGS) $(OFILES) $(LIBS) -o mazewar

vax.ingres:	$(OFILES)
		$(CC) $(CFLAGS) $(OFILES) $(LIBS) libc.ingres -o mazewar.ingres

vax.ic:		$(OFILES)
		$(CC) $(CFLAGS) $(OFILES) $(LIBS) libc.ic -o mazewar.ic

sun:		$(OFILES) $(SUNFILES)
		$(CC) $(CFLAGS) $(OFILES) $(SUNFILES) $(SUNLIBS)  -o mazewar

prmaze:		prmaze.o
		$(CC) $(CFLAGS) prmaze.o -o prmaze

dist:
		rcp mazewar ucbarpa.chris:bin/mazewar
		rcp mazewar ucbcad.chris:bin/mazewar
		rcp mazewar ucbcory.chris:bin/mazewar
#		rcp mazewar ucbdali.chris:bin/mazewar
		rcp mazewar ucbernie.chris:bin/mazewar
		rcp mazewar ucbesvax.chris:bin/mazewar
		rcp mazewar.ic ucbic.chris:bin/mazewar
		rcp mazewar.ingres ucbingres.chris:bin/mazewar
#		rcp mazewar ucbmatisse.chris:bin/mazewar
		rcp mazewar.ic ucbmedea.chris:bin/mazewar
		rcp mazewar.ic ucbmerlin.chris:bin/mazewar
		rcp mazewar ucbmiro.chris:bin/mazewar
		rcp mazewar ucbmonet.chris:bin/mazewar
		rcp mazewar.ic ucboz.chris:bin/mazewar
		rcp mazewar ucbshadow.chris:bin/mazewar
		rcp mazewar ucbvax.chris:bin/mazewar

ctags:
		ctags $(CFILES) $(HFILES)

clean:
		rm -f *.o mazewar core *.out

actions.o:       ../h/defs.h
calldaemon.o:    ../h/defs.h ../h/struct.h ../h/extern.h
comm.o:          ../h/defs.h ../h/struct.h ../h/extern.h
getsocket.o:     ../h/defs.h ../h/struct.h ../h/extern.h
init.o:          ../h/defs.h ../h/struct.h ../h/extern.h ../h/hallmap.h \
		../h/sunscreen.h ../h/sunscreen.h ../h/arrows.h \
		../h/wall_image.h
initplayer.o:    ../h/defs.h ../h/struct.h ../h/extern.h
ioctls.o:        ../h/defs.h ../h/struct.h ../h/extern.h
main.o:          ../h/defs.h ../h/struct.h ../h/data.h
packet.o:        ../h/defs.h ../h/struct.h ../h/extern.h
player.o:        ../h/defs.h ../h/sunscreen.h
prmaze.o:        ../h/defs.h ../h/struct.h
redraw.o:        ../h/sunscreen.h
send.o:          ../h/defs.h ../h/struct.h ../h/extern.h
service.o:       ../h/defs.h ../h/struct.h ../h/extern.h
setkeyok.o:      ../h/defs.h ../h/struct.h ../h/extern.h
statwin.o:       ../h/sunscreen.h
ualarm.o:        ../h/defs.h ../h/struct.h ../h/extern.h
viewwin.o:       ../h/sunscreen.h ../h/hallmap.h ../h/corners.h
wintext.o:       ../h/sunscreen.h
work.o:          ../h/defs.h ../h/struct.h ../h/extern.h
