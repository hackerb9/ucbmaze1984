#ifndef lint
static char rcsid[] = "$Header$";
#endif

#include <stdio.h>
#include <curses.h>
#include "../h/defs.h"
#include "../h/struct.h"
#include "../h/extern.h"

#ifndef CTRL
#define CTRL(c)		('c' & 037)
#endif

/*
 *  Read and parse keyboard input.  All possible functions
 *  are stored in an array of function pointers which is
 *  accessed by the routine input_action();
 */

service()
{
	char 		buf[BUFSIZ];
	register int	count;
	register char 	*cp;
	extern 		(*input_action())();
	register	(*action)();

	/*
	 * We have to remember to read all the characters currently
	 * on the input queue.  The select in work assures us that
	 * there is at least on character on the queue so that it
	 * won't block.
	 */
	
	count = read(fileno(stdin), buf, sizeof buf);
	if (count < 0) {
		perror("Read error on stdin");
		return(-1);
	}

	buf[count] = '\0';

	for (cp = buf; *cp; cp++) {
		action = input_action(*cp);
#ifdef DEBUG_2
		fprintf(stderr, "service: input_action('%c') = 0x%x\n",
		    *cp, action);
#endif
		if ((int)action != NULL)
			action(*cp);
	}
	return(count);
}

action_beep()
{
	putc(CTRL(g), stderr);
}

action_redraw(input)
{
	if (ascii)
		(void) wrefresh(curscr);
#ifdef sun
	else
		screen_redraw();
#endif
	return(0);
}

action_forward(input)
{
	peek = 0;
	forward();
	return(0);
}

action_shoot(input)
{
	if (keyok <= 0) {
		keyok = 1;
		fire();
	}
	
	return(0);
}

action_quit(input)
{
	quit(0);
}

action_180turn(input)
{
	peek = 0;
	bturn();

	return(0);
}

action_left(input)
{
	peek = 0;
	lturn();
	return(0);
}

action_right(input)
{
	peek = 0;
	rturn();

	return(0);
}

action_left_peek(input)
{
	peek = 3;

	return(0);
}

action_stop_peek(input)
{
	peek = 0;

	return(0);
}

action_right_peek(input)
{
	peek = 1;

	return(0);
}

action_back_up(input)
{
	peek = 0;
	back();

	return(0);
}

/* Clean up and quit */
quit(status)
{

	unsetioctls();
	sendquit();

#ifdef sun
	if (onsun) {
		endpix();
	} else {
#else
	{
#endif
		move(LINES - 1, 0);
		clrtoeol();
		refresh();

		endwin();
	}

	exit(0);
}
