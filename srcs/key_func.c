#include "mytermcaps.h"

int 	arrow_up(t_term *tc, char buffer[5])
{
	if (ft_memcmp(buffer, KEY_UP, 5) == 0)
	{
		if (tc->line.cursor_y > 0 || tc->line.cursor_x > 0)
		{
			tputs(debug_tgetstr("le", NULL), 0, output_func);
			update_cursor_pos(tc, -1, 0);
		}
		return (1);
	}
	return (0);
}

int 	arrow_down(t_term *tc, char buffer[5])
{
	if (ft_memcmp(buffer, KEY_DOWN, 5) == 0)
	{
		tputs(debug_tgetstr("nd", NULL), 0, output_func);
		//tputs(debug_tgetstr("ce", NULL), 0, output_func);
		update_cursor_pos(tc, 1, 0);
		return (1);
	}
	return (0);
}

void	move_right(t_term *tc)
{
	update_cursor_pos(tc, 1, 0);
	if (tc->line.cursor_x % tc->term_size.ws_col == 0)
	{
		tputs(debug_tgetstr("do", NULL), 0, output_func);
		//tputs(debug_tgetstr("cr", NULL), 0, output_func);
	}
	else
	{
		tputs(debug_tgetstr("nd", NULL), 0, output_func);
	}
}

int 	arrow_right(t_term *tc, char buffer[5])
{
	if (ft_memcmp(buffer, KEY_RIGHT, 5) == 0)
	{
<<<<<<< HEAD
		move_right(tc);
=======
		if (tc->line.cursor_x + 1 >= tc->term_size.ws_col)
		{
			tputs(debug_tgetstr("do", NULL), 0, output_func);
			//tputs(debug_tgetstr("cr", NULL), 0, output_func);
			update_cursor_pos(tc, 1, 0);
		}
		else
		{
			tputs(debug_tgetstr("nd", NULL), 0, output_func);
			update_cursor_pos(tc, 1, 0);
		}
>>>>>>> eb748bd0d31f4e806ffb47f36beb3e298c59e12c
		return (1);
	}
	return (0);
}

void	move_left(t_term *tc)
{
	unsigned int	len_line;

<<<<<<< HEAD
	if (tc->line.cursor_x == 0)
		return ;
	if (tc->line.cursor_x % tc->term_size.ws_col == 0)
	{
		len_line = tc->term_size.ws_col;
		tputs(debug_tgetstr("up", NULL), 0, output_func);
		while (len_line--)
			tputs(debug_tgetstr("nd", NULL), 0, output_func);
=======
	len_line = tc->term_size.ws_col;
	if (tc->line.cursor_x == 0 && tc->line.cursor_y > 0)
	{
		tputs(debug_tgetstr("up", NULL), 0, output_func);
		while (len_line--)
			tputs(debug_tgetstr("nd", NULL), 0, output_func);
		update_cursor_pos(tc, -1, 0);
>>>>>>> eb748bd0d31f4e806ffb47f36beb3e298c59e12c
	}
	else
	{
		tputs(debug_tgetstr("le", NULL), 0, output_func);
<<<<<<< HEAD
	}
	update_cursor_pos(tc, -1, 0);
=======
		update_cursor_pos(tc, -1, 0);
	}
>>>>>>> eb748bd0d31f4e806ffb47f36beb3e298c59e12c
}

int 	arrow_left(t_term *tc, char buffer[5])
{
	if (ft_memcmp(buffer, KEY_LEFT, 5) == 0)
	{
		move_left(tc);
		return (1);
	}
	return (0);
}

int 	ctrl_d(t_term *tc, char buffer[5])
{
	if (tc)
		;
	if (ft_memcmp(buffer, KEY_CTRL_D, 5) == 0)
		return (-1);
	return (0);
}