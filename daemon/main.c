#ifndef lint
static char rcsid[] = "$Header: main.c,v 1.1 84/08/24 02:36:44 jcoker Exp $";
#endif

#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../h/defs.h"
#include "../h/struct.h"
#include "../h/data.h"

struct sockaddr_in sins[MAXPLAYER];		/* sockets of players */
long lastup[MAXPLAYER];				/* last update from user */

/*ARGSUSED*/
main(argc, argv)
	char *argv[];
{

	init(argc, argv);

	work();

	/*NOTREACHED*/
}
