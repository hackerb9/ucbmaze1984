#ifndef lint
static char rcsid[] = "$Header$";
#endif

#include <stdio.h>
#include <sys/param.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../h/defs.h"
#include "../h/struct.h"
#include "../h/extern.h"

extern struct sockaddr_in earsin;

/*
** Send a status packet.
*/
sendstat(flags)
int flags;
{
	struct packet p;

	if (nodaemon)
	    return;
	p.p_flag = P_STATE;
	p.p_slot = me->u_slot;

	me->u_state.s_flag = flags;
#ifdef	NOASGNSTRUCT
	bcopy(&me->u_state, &p.p_data.pu_state, sizeof(struct state));
#else
	p.p_data.pu_state = me->u_state;
#endif

	if (sendto(ear, (char *) &p, sizeof(p), 0,
		(struct sockaddr *) &earsin, sizeof(struct sockaddr_in)) < 0) {
		perror("sendto");
		exit(1);
	}
}

/*
** Send an action packet.
*/
sendaction(flag, slot, from)
int flag, slot, from;
{
	struct packet p;

	if (nodaemon)
		return;

	p.p_flag = P_ACTION;
	p.p_slot = me->u_slot;

	p.p_data.pu_action.a_flag = flag;
	p.p_data.pu_action.a_victem = slot;
	p.p_data.pu_action.a_killer = from;

	p.p_data.pu_action.a_incarnation = players[slot].u_state.s_incarnation;

	if (sendto(ear, (char *) &p, sizeof(p), 0,
		(struct sockaddr *) &earsin, sizeof(struct sockaddr_in)) < 0) {
		perror("sendto");
		exit(1);
	}
}

/*
** Inform the daemon that the current player is quitting
*/
sendquit()
{
	struct packet p;

	if (nodaemon)
		return;

	p.p_flag = P_USER;
	p.p_slot = me->u_slot;

	me->u_flag = U_DEAD;				/* I'm dead */

#ifdef	NOASGNSTRUCT
	bcopy(me, &p.p_data.pu_user, sizeof(struct user));
#else
	p.p_data.pu_user = *me;
#endif

	if (sendto(ear, (char *) &p, sizeof(p), 0,
		(struct sockaddr *) &earsin, sizeof(struct sockaddr_in)) < 0) {
		perror("sendto");
		exit(1);
	}
}
