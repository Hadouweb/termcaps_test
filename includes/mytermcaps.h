#ifndef TERMCAPS_H
# define TERMCAPS_H

#include "libft.h"
#include <stdio.h>
#include <termios.h>
#include <term.h>
#include <sys/ioctl.h>
#include <fcntl.h>

# define KEY_UP				"\x1b\x5b\x41\x0\x0\x0"
# define KEY_DOWN			"\x1b\x5b\x42\x0\x0\x0"
# define KEY_RIGHT			"\x1b\x5b\x43\x0\x0\x0"
# define KEY_LEFT			"\x1b\x5b\x44\x0\x0\x0"
# define KEY_CTRL_D			"\x4\x0\x0\x0\x0\x0"

# define PROMPT_LEN 0
# define KEY_COUNT 5

static int fd_debug = 3;

# define PRINT_DEBUG(param) dprintf(fd_debug, param);

typedef struct 		s_char
{
	t_link			link;
	char 			c;
	unsigned int 	index;
}					t_char;

typedef struct 		s_line
{
	t_char			*cur_c_node;
	unsigned int 	cursor_x;
	unsigned int	cursor_y;
	t_list 			*list_str;
}					t_line;

typedef struct 		s_term
{
	char 			*name_term;
	struct termios 	term;
	struct termios 	old_term;
	int				(*f[KEY_COUNT])(struct s_term *tc, char buffer[5]);
	t_line			line;
	struct winsize	term_size;
}					t_term;

/*
 * key_func.c
 */
int 	arrow_up(t_term *tc, char buffer[5]);
int 	arrow_down(t_term *tc, char buffer[5]);
int 	arrow_right(t_term *tc, char buffer[5]);
int 	arrow_left(t_term *tc, char buffer[5]);
int 	ctrl_d(t_term *tc, char buffer[5]);

/*
 * error.c
 */
void	error(char *str, int line);

/*
 * debug.c
 */
void	debug_termios(struct termios *term);
void	debug_term_size(t_term *tc);
void	debug_init_tty(char *tty_name);
void	debug_print_cursor_pos(t_term *tc);
void	debug_print_t_char(void *content);
char	*debug_tgetstr(char *code, void *ptr);

/*
 * update_cursor.c
 */
void	update_term_size(t_term *tc);
void	update_cursor_pos(t_term *tc, int x);
void	replace_cursor(t_term *tc, t_char *orig_c_node);

/*
 * util.c
 */
int		output_func(int c);
t_char	*make_char(char c);
void	update_list_index(t_link *l);
int		exec_key(t_term *tc, char buffer[5]);
void	reset_term(t_term *tc);

/*
 * init.c
 */
void	init_key(t_term *tc);
void	init_term(t_term *tc);
void	init_list_str(t_term *tc);

/*
 * move.c
 */
void	move_left(t_term *tc);
void	move_right(t_term *tc);

/*
 * print.c
 */
void	print_line(t_term *tc);
void	insert_before_char(t_term *tc, t_char *c_node);
void	write_on_output(t_term *tc, char buffer[5]);

#endif