/* RCS Information: $Header$ */

extern char maze[MAZEWIDTH][MAZELENGTH];

#ifdef sun
extern short	down_arrow[10];

extern short	up_arrow[10];

extern short	left_arrow[10];

extern short	right_arrow[10];
#endif

extern struct user *me;
extern struct user players[MAXPLAYER];
extern long lastup[MAXPLAYER];
extern int keyok;
extern int ear;
#ifdef DEBUG
extern int debug;
#endif
extern int nodaemon;
extern int ascii;
extern int onsun;
extern char *program;
extern int peek;
