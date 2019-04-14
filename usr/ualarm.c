#ifndef lint
static char rcsid[] = "$Header: ualarm.c,v 1.1 84/08/25 17:11:32 chris Exp $";
#endif

#include <sys/time.h>
#include "../h/defs.h"
#include "../h/struct.h"
#include "../h/extern.h"

/*
 * Generate a SIGALRM signal in ``usecs'' microseconds
 * If ``reload'' is non-zero, keep generating SIGALRM
 * every ``reload'' microseconds.
 */
ualarm(usecs, reload)
	register unsigned long usecs;
	register unsigned long reload;
{
	struct itimerval new, old;

	timerclear(&old.it_interval);
	timerclear(&old.it_value);

	new.it_interval.tv_usec = reload % 1000000;
	new.it_interval.tv_sec = reload / 1000000;
	
	new.it_value.tv_usec = usecs % KEYOK;
	new.it_value.tv_sec = usecs / KEYOK;

	if (setitimer(ITIMER_REAL, &new, &old) == 0)
		return;
/*
		return (old.it_value.tv_sec * KEYOK + old.it_value.tv_usec);
*/
	/* else */
	return;
/*
		return (-1);
*/
}
