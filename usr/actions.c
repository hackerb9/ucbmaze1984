#ifndef lint
static rcsid[] = "$Header$";
#endif

#include <stdio.h>
#include "../h/defs.h"

extern int	action_beep(),
		action_redraw(),
		action_forward(),
		action_shoot(),
		action_quit(),
		action_180turn(),
		action_left(),
		action_right(),
		action_left_peek(),
		action_stop_peek(),
		action_right_peek(),
		action_back_up();

#undef CTRL
#define CTRL(c)		('c' & 037)

#define ASCII_MASK	0177
#ifdef sun
#define NUMBER_ACTIONS	(NUMBER_ASCII + 3)
#else
#define NUMBER_ACTIONS	NUMBER_ASCII
#endif

static int	(*player_actions[NUMBER_ACTIONS])();

/*
 *  Set up the default key mappings.
 *  We are hended the flag dobeep to tell us what the
 *  default actions are for the unused keys.
 *  We also set the undef type to the proper thing.
 */

static int	dobeep = 0;

set_default_actions(beep)
{
	int	i;

	dobeep = beep;

	if (dobeep) {
		for (i = 0; i < NUMBER_ASCII; i++)
			player_actions[i] = action_beep;
	} else {
		for (i = 0; i < NUMBER_ASCII; i++)
			player_actions[i] = NULL;
	}

	player_actions[CTRL(l)]	= action_redraw;
	player_actions[CTRL(r)]	= action_redraw;
	player_actions['w']	= action_forward;
	player_actions['s']	= action_shoot;
	player_actions['Q']	= action_quit;
	player_actions['x']	= action_180turn;
	player_actions['a']	= action_left;
	player_actions['d']	= action_right;
	player_actions['j']	= action_left_peek;
	player_actions['l']	= action_right_peek;
	player_actions['k']	= action_stop_peek;
	player_actions[' ']	= action_back_up;

	return(0);
}


/*
 *  Set the action for the given character to the
 *  function represented by the given string.
 */

struct action_list {
	char	*act_name;
	int	(*act_funct)();
};
static struct action_list	action_list[] = {
	{ "redraw",	action_redraw },
	{ "forward",	action_forward },
	{ "shoot",	action_shoot },
	{ "quit",	action_quit },
	{ "turn-back",	action_180turn },
	{ "turn-left",	action_left },
	{ "turn-right",	action_right },
	{ "peek-left",	action_left_peek },
	{ "stop-peek",	action_stop_peek },
	{ "peek-right",	action_right_peek },
	{ "back-up",	action_back_up },
	{ NULL,		NULL }
};

set_action(key, action)
	char	*action;
{
	struct action_list	*act;

	if (key >= NUMBER_ACTIONS || key < 0) {
		fprintf(stderr, "%d (0%o): Illegal character!\n", key, key);
		return(-1);
	}

	if (!strcmp(action, "undef")) {
		if (dobeep)
			player_actions[key] = action_beep;
		else
			player_actions[key] = NULL;

		return(0);
	}

	for (act = action_list; act->act_name; act++)
		if (!strcmp(act->act_name, action)) {
			player_actions[key] = act->act_funct;
			return(0);
		}

	fprintf(stderr, "action \"%s\" not found.\n", action);
	return(-1);
}


/*
 *  Set the actions based on the input string.
 */

parse_action_string(string)
	char	*string;
{
	char	action[BUFSIZ], *ap, *sp;
	char	key[10], *kp;

	if (string == NULL || *string == '\0') {
		fprintf(stderr, "Null action string!\n");
		return(-1);
	}

	for (sp = string; *sp; sp++) {
		kp = key;
		do
			*kp++ = *sp++;
		while (*sp && *sp != '=');
		*kp = '\0';
		if (strlen(key) != 1) {
#ifdef sun
			if (*key == 'M') {
				switch (key[1]) {
				case '1':	/* left key */
					*key = MOUSE_LEFT;
					break;

				case '2':	/* middle key */
					*key = MOUSE_MIDDLE;
					break;

				case '3':	/* right key */
					*key = MOUSE_RIGHT;
					break;

				default:	/* what?!? */
					fputs(
				"Bad mouse key specification; use M1 - M3.\n",
					    stderr);
					return(-1);
				}
			}
#else
			fputs("Bad format in action, use <char>=action.\n",
			    stderr);
			return(-1);
#endif
		}
		if (*sp != '=') {
			fputs("Bad format in action, use <char>=action.\n",
			    stderr);
			return(-1);
		} else
			sp++;
		ap = action;
		do
			*ap++ = *sp++;
		while (*sp && *sp != ',');
		*ap = '\0';
		if (set_action(*key, action) < 0) {
			/* set_action will bitch on error */
			return(-1);
		}
	}
}


/*
 *  Return an action from the given character.
 */

int (*input_action(ch))()
{
	if (ch > NUMBER_ACTIONS || ch < 0) {
		fprintf(stderr, 
		    "input_action: %d (0%o): Illegal action character!\n", 
		    ch, ch);
		return(NULL);
	}

	return player_actions[ch];
}
