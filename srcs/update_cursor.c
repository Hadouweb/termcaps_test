#include "mytermcaps.h"

void	update_cur_c_node(t_term *tc, int x)
{
	t_link	*l;

	l = &tc->line.cur_c_node->link;
	if (x == 1 && l->next)
		l = l->next;
	else if (x == -1 && l->prev)
		l = l->prev;
	tc->line.cur_c_node = (t_char*)l;
}

void	update_cursor_pos(t_term *tc, int x)
{
	if (x != 0)
	{
		update_cur_c_node(tc, x);
		tc->line.cursor_x += x;
	}
	ft_list_print(tc->line.list_str->head, debug_print_t_char);
	debug_print_cursor_pos(tc);
	debug_term_size(tc);
}

void	replace_cursor(t_term *tc, t_char *orig_c_node)
{
	t_char	*cur_c_node;
	t_char	*c_node;
	t_link	*l;

	cur_c_node = tc->line.cur_c_node;
	l = &cur_c_node->link;
	while (l)
	{
		c_node = (t_char*)l;
		if (c_node == orig_c_node)
			break ;
		move_left(tc);
		l = l->prev;
	}
}
