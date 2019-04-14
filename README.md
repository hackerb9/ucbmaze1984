# Mazewar
Three folks at U.C. Berkeley, Chris Guthrie, Nick Lai, and John Coker created a re-implementation of [Maze War](https://wikipedia.org/wiki/mazewar) — the first first-person shooter video game — that ran on both Sun using Sunview graphics and VAX (supporting VT100 ASCII graphics). People could play across the net on both graphical terminals and text terminals simultaneously. Originally written in 1984 and "advertised" on the Usenet in comp.sources, it spread quickly on the Internet. It was possibly the first version of Maze War which could be easily played using common hardware. Souped-up versions of this code, including a hack to add 3-D graphics rendered in ASCII, remained quite popular at universities for over a decade.  

This repository is exactly the code as received from Nick Lai, with some minor redactions. While this repository will never change, the authors have released it under the BSD license, so you may fork it for your own project. 

Credits: *Chris Guthrie* started the project and wrote most of the code. *Nick Lai* added to the game, including all of the networking code. *John Coker* handled the Sun graphics. 

____

# The original documentation

# MAZEWAR
Mazewar is a multi-player maze game with 3-D graphics displays on machines which support the
graphics (currently only SUNs). The game can be played in two modes, the ’ascii mode’ and the ’sun
mode.’ The sun mode has the addition of a three-dimensional dungeon view.

## Ascii Mode
The ascii mode is the only mode available if compiled off of a sun. It can also be forced by giving
the -a (for ascii) flag when on a SUN.

In this mode, the screen is dominated by a top view of the maze, which takes up 3/4 of a 24x80 character
screen. Below the maze, is a list of the players and their stats.

On the maze, you appear as a ’pair of eyes’ (composed of the characters ’ˆˆ’, ’>>’, ’vv’, or ’<<’), and
all the other players appear as small numbers, when you can see them.

## SUN Mode
You will see three display areas on your screen, a 3-D maze, a top view of the maze, and a list of 
current players and their stats.

The top-left 3-D maze view shows you what you can see from your current position in the maze.
Other players show up as tall triangles. If the player is facing you, you will se him as a wide triangle with
an eye, if you see his back you will see the same figure without the eye. From the side, the player will look
like a thin triangle, with an eye pointing in the direction he is facing.

The map view shows you your absolute position in the maze, and any player you can see in the upper
view. This helps you orient yourself in the maze, since it is easy to get lost in the 3-D view.
The side stats display shows the list of active players and their vital statistics. Your player is marked
with an asterisk. The player numbers on the stats display correspond with the numbers on the lower top
maze view.

## Movement
The default keys to move around in the maze are:

    w     move forward
    space move backward
    Q     quit
    a     turn left
    d     turn right
    x     turn around
    s     shoot
    j     peek around the corner to the left
    l     peek around the corner to the right
    k     look straight ahead (if you move this will happen)

All of the keys can be remapped to any action by setting the environment variable `MAZEWAR_KEYS`
to a string composed of `’<char>=action,<char>=action,...’` Remapping keys does NOT
unmap the default configuration, if you want to unmap a key, use ’<char>=undef.’
The available (and hopefully self-explanatory) actions are:

* redraw
* forward
* quit
* turn-back
* turn-right
* peek-left
* peek-right
* back-up
* shoot
* turn-left
* stop-peek
* undef

The environment variable `MAZEWAR_BEEP` should be set to the string ’yes’, if you want Mazewar
to beep when you press an unmapped key. Since this beep is rather annoying, this is NOT the default
action.

## Game Strategy
Other players will appear in front of you only if you are facing them. When you see someone, it is
best to start shooting.

It takes only one shot to kill a player (bazookas?). Killing someone automatically gains you a few
generic score points. Getting killed is accompanied with minus points. Once you are killed, you will be
quickly resurrected in another part of the maze.

## Authors
This game was written by Chris Guthrie and Nick Lai, and the SUN graphics done by John Coker; all
of University of California, Berkeley.

chris@BERKELEY [...!ucbvax!chris],

lai@BERKELEY [...!ucbvax!lai],

jcoker@BERKELEY [...!ucbvax!jcoker].
