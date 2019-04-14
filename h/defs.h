/* RCS Information: $Header: defs.h,v 1.1 84/08/25 17:24:54 lai Exp $ */

#define MAZEWIDTH 32
#define MAXDEPTH 30
#define MAZELENGTH 16
#define MAXPLAYER  16
#define HITPOINTS  1
#define KEYOK 			1000000
#define GHOSTCHECK		10000000
#define GHOST_TIMEOUT		45
#define CD_TIMEOUT		10		/* calldaemon timeout */

#define HOSTNAMLEN		16
#define NAMELEN			8

#ifdef sun
#define DEFAULT_HOST 		"xcssun"
#else
#define DEFAULT_HOST 		"ucbcory"
#endif

#define DEFAULT_PORT 		1666
#define SERV_PORT 		1666

#define V_MAGIC			92387983L	/* magic number for security */

#define LOGFILE			"logfile"	/* put it in current dir */

#define inmaze(A,B)		((((A) << 4) | (B)) & 0x1ff)
#define addplayer(P,X,Y)	(bitmaze[inmaze(X,Y)] |= (1 << (P)))
#define delplayer(P,X,Y)	(bitmaze[inmaze(X,Y)] &= ~(1 << (P)))

/* flags for the direction in which another player is pointing */
#define DIR_LEFT	1
#define DIR_RIGHT	2
#define DIR_FRONT	3
#define DIR_BACK	4

/* mouse keys */
#define NUMBER_ASCII	128
#define MOUSE_LEFT	(NUMBER_ASCII)
#define MOUSE_MIDDLE	(NUMBER_ASCII + 1)
#define MOUSE_RIGHT	(NUMBER_ASCII + 2)
