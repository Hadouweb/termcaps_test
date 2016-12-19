#include "mytermcaps.h"

void	update_cursor_pos(t_term *tc, int x, int y)
{
	if (tc->line.cursor_x == 0 && tc->line.cursor_y == 0)
		tc->line.cur_c_node = (t_char*)tc->line.list_str->head;
	else if (x == -1 && tc->line.cur_c_node->link.prev)
		tc->line.cur_c_node = (t_char*)tc->line.cur_c_node->link.prev;
	else if (x == 1 && tc->line.cur_c_node->link.next)
		tc->line.cur_c_node = (t_char*)tc->line.cur_c_node->link.next;
	if (x == 1 && tc->line.cursor_x + 1 >= tc->term_size.ws_col)
	{
		PRINT_DEBUG("__here 1\n");
		tc->line.cursor_y += 1;
		tc->line.cursor_x = 0;
	}
	else if (x == -1 && tc->line.cursor_x == 0 && tc->line.cursor_y > 0)
	{
		PRINT_DEBUG("__here 2\n");
		tc->line.cursor_y -= 1;
		tc->line.cursor_x = tc->term_size.ws_col - 1;
	}
	else if (y == 1)
	{
		PRINT_DEBUG("__here 3\n");
		tc->line.cursor_y += 1;
		tc->line.cursor_x = 0;
	}
	else if (y == -1 && tc->line.cursor_y > 0)
	{
		PRINT_DEBUG("__here 4\n");
		tc->line.cursor_y -= 1;
		tc->line.cursor_x = tc->term_size.ws_col - 1;
	}
	else
	{
		PRINT_DEBUG("__here 10\n");
		tc->line.cursor_x += x;
	}
	debug_print_cursor_pos(tc);
	debug_term_size(tc);
}

int 	arrow_up(t_term *tc, char buffer[5])
{
	if (ft_memcmp(buffer, KEY_UP, 5) == 0)
	{
		if (tc->line.cursor_y > 0 || tc->line.cursor_x > 0)
		{
			tputs(tgetstr("le", NULL), 0, output_func);
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
		tputs(tgetstr("nd", NULL), 0, output_func);
		//tputs(tgetstr("ce", NULL), 0, output_func);
		update_cursor_pos(tc, 1, 0);
		return (1);
	}
	return (0);
}

int 	arrow_right(t_term *tc, char buffer[5])
{
	if (ft_memcmp(buffer, KEY_RIGHT, 5) == 0)
	{
		if (tc->line.cursor_x + 1 >= tc->term_size.ws_col)
		{
			tputs(tgetstr("do", NULL), 0, output_func);
			tputs(tgetstr("cr", NULL), 0, output_func);
			update_cursor_pos(tc, 0, 1);
		}
		else
		{
			tputs(tgetstr("nd", NULL), 0, output_func);
			update_cursor_pos(tc, 1, 0);
		}
		return (1);
	}
	return (0);
}

int 	arrow_left(t_term *tc, char buffer[5])
{
	if (ft_memcmp(buffer, KEY_LEFT, 5) == 0)
	{
		if (tc->line.cursor_y > 0 || tc->line.cursor_x > 0)
		{
			tputs(tgetstr("le", NULL), 0, output_func);
			update_cursor_pos(tc, -1, 0);
		}
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