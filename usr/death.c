#ifndef lint
static char rcsid[] = "$Header$";
#endif

#include <curses.h>
#include <math.h>
#include "../h/defs.h"
#include "../h/struct.h"
#include "../h/extern.h"

#ifdef sun
# include "../h/sunscreen.h"
#endif

draw_my_death()
{
#ifdef sun
	if (onsun)
		sun_death();
	else
#endif sun
		ascii_death();
	
}


static
ascii_death()
{
	extern WINDOW	*w_birdv;

#define RADIUS		10
	wclear(w_birdv);
	ascii_explosion(w_birdv, me->u_y, me->u_x * 2, RADIUS, '*');

	sleep(2);

	draw_maze();
	touchwin(w_birdv);
	wrefresh(w_birdv);
}


static
ascii_explosion(w, r, c, maxr, ch)
	WINDOW		*w;
	register	r, c, maxr, ch;
{
	register	i;

	for (i = 0; i < maxr; i++) {
		mvwaddch(w, r + i, c, ch);
		mvwaddch(w, r + i, c - i * 2, ch);
		mvwaddch(w, r, c - i * 2, ch);
		mvwaddch(w, r - i, c - i * 2, ch);
		mvwaddch(w, r - i, c, ch);
		mvwaddch(w, r - i, c + i * 2, ch);
		mvwaddch(w, r, c + i * 2, ch);
		mvwaddch(w, r + i, c + i * 2, ch);
		wrefresh(w);
		(void) cos((double)0);
	}

#define SPACE	' '
	for (i = 0; i < maxr; i++) {
		mvwaddch(w, r + i, c, SPACE);
		mvwaddch(w, r + i, c - i * 2, SPACE);
		mvwaddch(w, r, c - i * 2, SPACE);
		mvwaddch(w, r - i, c - i * 2, SPACE);
		mvwaddch(w, r - i, c, SPACE);
		mvwaddch(w, r - i, c + i * 2, SPACE);
		mvwaddch(w, r, c + i * 2, SPACE);
		mvwaddch(w, r + i, c + i * 2, SPACE);
		wrefresh(w);
		(void) cos((double)0);
	}
}

#ifdef sun

#include "expl.h"
#define BLOCK		8
#define UNDRAW		200

extern struct pixrect	*px_viewwin;

/*
 *  Draw an explosion with the sun graphics.
 */

static
sun_death()
{
	register	bx, by;
	register	d, u;

	bx = VIEWX + VIEWW / 2;
	by = VIEWY + VIEWH / 2;
	for (d = 0; d < MAXIMAGES; d++) {
		rect(px_screen, bx + xlist[d], by + ylist[d], 
		    BLOCK, BLOCK, OP_CLEAR);
		(void) cos((double) 0);	/* waste some time */
		if ( (u = d - UNDRAW) >= 0)
			rect(px_screen, bx + xlist[u], by + ylist[u], BLOCK,
			    BLOCK, OP_SET);
	}

	for ( u++; u < MAXIMAGES; u++) {
		rect(px_screen, bx + xlist[u], by + ylist[u], 
		    BLOCK, BLOCK, OP_SET);
		(void) cos((double) 0);	/* waste some time */
	}
	prclear(px_viewwin);
	copyat(px_viewwin, VIEWX, VIEWY, OP_WRITE);

	sleep(2);

	screen_redraw();
}
#endif sun
