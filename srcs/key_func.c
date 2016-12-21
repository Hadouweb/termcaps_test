#include "mytermcaps.h"

int 	arrow_up(t_term *tc, char buffer[5])
{
	if (ft_memcmp(buffer, KEY_UP, 5) == 0)
	{
		if (tc->line.cursor_y > 0 || tc->line.cursor_x > 0)
		{
			tputs(debug_tgetstr("le", NULL), 0, output_func);
			update_cursor_pos(tc, -1);
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
		update_cursor_pos(tc, 1);
		return (1);
	}
	return (0);
}

int 	arrow_right(t_term *tc, char buffer[5])
{
	if (ft_memcmp(buffer, KEY_RIGHT, 5) == 0)
	{
		move_right(tc);
		return (1);
	}
	return (0);
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