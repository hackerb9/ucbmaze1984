#ifndef lint
static char rcsid[] = "$Header: ualarm.c,v 1.1 84/08/24 02:36:48 jcoker Exp $";
#endif

#include <sys/time.h>
#include <stdio.h>
#include "../h/defs.h"
#include "../h/struct.h"
#include "../h/extern.h"

/*
 * Generate a SIGALRM signal in ``usecs'' microseconds
 * If ``reload'' is non-zero, keep generating SIGALRM
 * every ``reload'' microseconds.
 */
unsigned
ualarm(usecs, reload)
	register unsigned usecs;
	register unsigned reload;
{
	struct itimerval new, old;

	timerclear(&old.it_interval);
	timerclear(&old.it_value);

	new.it_interval.tv_usec = reload % 1000000;
	new.it_interval.tv_sec = reload / 1000000;
	
	new.it_value.tv_usec = usecs % 1000000;
	new.it_value.tv_sec = usecs / 1000000;

	(void) setitimer(ITIMER_REAL, &new, &old);
}

ghostbuster()
{
	register int i;
	long now, time();
	struct action a;
	extern char *curtime();

	now = time((char *)0);

	for (i = 0; i < MAXPLAYER; i++) {
		if ((players[i].u_flag & U_ALIVE) == 0)
			continue;
		if (now > lastup[i] + GHOST_TIMEOUT) {
			players[i].u_flag = 0;		/* you lose */
			syslog("ghostbuster(): zapped %s@%s (%d): %ld sc: %s\n",
					players[i].u_name, 
					players[i].u_hostname,
					i,
					now - lastup[i],
					curtime());
			send_user(i);
		} else {
			a.a_flag = A_QUERY;
			a.a_victem = i;
			send_action(&a);
		}
	}
}
