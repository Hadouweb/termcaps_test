#include "mytermcaps.h"

void	update_cur_c_node(t_term *tc, int x)
{
	if (x == -1 && tc->line.cur_c_node) {
		//PRINT_DEBUG("SWITCH C_NODE 2\n");
		tc->line.cur_c_node = (t_char *) tc->line.cur_c_node->link.prev;
	}
	else if (x == 1 && tc->line.cur_c_node) {
		//PRINT_DEBUG("SWITCH C_NODE 3\n");
		tc->line.cur_c_node = (t_char *) tc->line.cur_c_node->link.next;
	}
}

void	update_cursor_pos(t_term *tc, int x, int y)
{
	update_cur_c_node(tc, x);
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
	ft_list_print(tc->line.list_str->head, debug_print_t_char);
	debug_print_cursor_pos(tc);
	debug_term_size(tc);
	dprintf(fd_debug, "\n");
}

void	insert_new_char(t_term *tc, t_char *new_node)
{

	ft_list_push_before_node(&tc->line.list_str,
	&tc->line.cur_c_node->link, &new_node->link);
	tc->line.cur_c_node = new_node;
}

void	write_and_new_line(t_term *tc, char c)
{
	t_link	*l;
	t_char	*c_node;
	t_char	*c_new_line;

	if (c)
		;
	l = tc->line.list_str->head;
	c_new_line = make_char('\n');
	while (l)
	{
		c_node = (t_char*)l;
		if (c_node->index % tc->term_size.ws_col == 0)
			ft_list_push_before_node(&tc->line.list_str, l, &c_new_line->link);
		l = l->next;
	}
	dprintf(fd_debug, "||||\n");
	tputs(tgetstr("ce", NULL), 0, output_func);
}

void	write_on_output(t_term *tc, char buffer[5])
{
	int 	i;
	t_char	*c_node;

	i = 0;
	while (buffer[i])
	{
		c_node = make_char(buffer[i]);
		insert_new_char(tc, c_node);
		ft_putchar(buffer[i]);
		update_list_index(tc->line.list_str->head);
		update_cursor_pos(tc, 1, 0);
		i++;
	}
}

void	init_list_str(t_term *tc)
{
	t_char	*cursor_end;

	cursor_end = make_char('\0');
	ft_list_push_back(&tc->line.list_str, &cursor_end->link);
	tc->line.cur_c_node = cursor_end;
}

int     read_key(t_term *tc)
{
	char    buffer[6];
	int 	ret;

	init_list_str(tc);

	while (1)
	{
		update_term_size(tc);
		ft_memset(buffer, 0, 6);
		read(0, buffer, 5);
		ret = exec_key(tc, buffer);
		if (ret == 0)
			write_on_output(tc, buffer);
		if (ret == -1)
			return (-1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_term		tc;

	init_term(&tc);
	if (ac > 1)
		debug_init_tty(av[1]);
	//debug_termios(&tc.term);

	read_key(&tc);

	reset_term(&tc);
	return (0);
}