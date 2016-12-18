#ifndef TERMCAPS_H
# define TERMCAPS_H

#include "libft.h"
#include <stdio.h>
#include <termios.h>
#include <term.h>
#include <sys/ioctl.h>

# define KEY_UP				"\x1b\x5b\x41\x0\x0\x0"
# define KEY_DOWN			"\x1b\x5b\x42\x0\x0\x0"
# define KEY_RIGHT			"\x1b\x5b\x43\x0\x0\x0"
# define KEY_LEFT			"\x1b\x5b\x44\x0\x0\x0"

enum e_key
{
	k_up,
	k_down,
	k_right,
	k_left,
	k_count,
};

typedef struct 		s_term
{
	char 			*name_term;
	struct termios 	term;
	struct termios 	old_term;
	int				(*f[k_count])(char buffer[5]);
}					t_term;

int 	move_up(char buffer[5]);
int 	move_down(char buffer[5]);
int 	move_right(char buffer[5]);
int 	move_left(char buffer[5]);

#endif