#ifndef lint
static char rcsid[] = "$Header: init.c,v 1.1 84/08/25 17:04:52 lai Exp $";
#endif

#include <sys/param.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <signal.h>

#include "../h/defs.h"
#include "../h/struct.h"
#include "../h/extern.h"

/*ARGSUSED*/
init(argc, argv)
	int argc;
	char **argv;
{	

	program = *argv;

	for(argc--, argv++; argc > 0; argc--, argv++) {
		if (**argv == '-') {
			(*argv)++;
			switch (**argv) {
#ifdef DEBUG
			case 'd':
				debug++;
				break;
#endif
			case 'u':
			default:
				printf("usage: %s [ -d ]\n", program);
				exit(0);
			}
		}
	}

#ifdef DEBUG
	if (!debug)
#endif
		background();

	closefds();

	initfds();

#ifdef DEBUG
	if (!debug)
#endif
		voidtty();

	ear = getsocket(SERV_PORT);

	initsigs();

	login(program);

	initstructs();

	ualarm(GHOSTCHECK, GHOSTCHECK);
}

/* 
 * Background the server
 */
background()
{
	switch(fork()) {
		case 0:
			break;
		case -1:
			perror("fork");
			exit(1);
		default:
			exit(0);
	}
}

/*
 * Close *ALL* available file descriptors.
 */
closefds()
{
	register int fd;

	for (fd = 0; fd < NOFILE; fd++)
		(void) close(fd);
}

/*
 * Initialize new file descriptors / pointers.
 */
initfds()
{
	extern FILE *errfp;

	errfp = fopen(LOGFILE, "a");
	if (errfp != NULL)
		setbuf(errfp, (char *)0);
	else
		exit(1);
}

/*
 * Void all tty associations.
 */
voidtty()
{
	register int tty;

	tty = open("/dev/tty", O_RDWR);
	if (tty >= 0) {
		(void) ioctl(tty, TIOCNOTTY, (char *)0);
		(void) close(tty);
	}
}

initsigs()
{
	extern int nice_exit();
	extern int ghostbuster();
	register int sig;

#ifdef DEBUG
	if (!debug)
#endif
		for (sig = 1; sig < NSIG; sig++)
			(void) signal(sig, SIG_IGN);

	(void) signal(SIGALRM, ghostbuster);
	(void) signal(SIGHUP, nice_exit);
	(void) signal(SIGINT, nice_exit);
}


initstructs()
{
	register int i;

	/*
	 * initially, all slots are free
	 */
	for (i = 0; i < MAXPLAYER; i++) {
		players[i].u_flag = 0;
	}
}

login(daemon)
	char *daemon;
{

	syslog("%s(%d): starting up at %s\n", daemon, getpid(), curtime());
}
