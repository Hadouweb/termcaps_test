#include "mytermcaps.h"

void	print_line(t_term *tc)
{
	t_char	*cur_c_node;
	t_char	*c_node;
	t_link	*l;

	cur_c_node = tc->line.cur_c_node;
	l = &cur_c_node->link;
	while (l->next)
	{
		c_node = (t_char*)l;
		ft_putchar(c_node->c);
		update_cursor_pos(tc, 1);
		l = l->next;
	}
	if ((c_node->index + 1) % tc->term_size.ws_col == 0)
		tputs(debug_tgetstr("do", NULL), 0, output_func);
}

void	insert_before_char(t_term *tc, t_char *c_node)
{
	t_char	*orig_c_node;

	orig_c_node = tc->line.cur_c_node;
	ft_list_push_before_node(&tc->line.list_str,
							 &tc->line.cur_c_node->link, &c_node->link);
	tc->line.cur_c_node = c_node;
	update_list_index(tc->line.list_str->head);
	tputs(debug_tgetstr("cd", NULL), 0, output_func);
	print_line(tc);
	replace_cursor(tc, orig_c_node);
}

void	write_on_output(t_term *tc, char buffer[5])
{
	int 	i;
	t_char	*c_node;

	i = 0;
	while (buffer[i])
	{
		c_node = make_char(buffer[i]);
		if (tc->line.cursor_x + 1 >= tc->line.list_str->size)
		{
			ft_list_push_before_node(&tc->line.list_str,
									 &tc->line.cur_c_node->link, &c_node->link);
			update_list_index(tc->line.list_str->head);
			ft_putchar(c_node->c);
			update_cursor_pos(tc, 1);
		}
		else
			insert_before_char(tc, c_node);
		i++;
	}
}
