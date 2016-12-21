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

void	update_cursor_pos(t_term *tc, int x, int y)
{
	if (y)
		;
	if (x != 0)
	{
		update_cur_c_node(tc, x);
		tc->line.cursor_x += x;
	}
	ft_list_print(tc->line.list_str->head, debug_print_t_char);
	debug_print_cursor_pos(tc);
	debug_term_size(tc);
	//dprintf(fd_debug, "\n");
}

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
		update_cursor_pos(tc, 1, 0);
		l = l->next;
	}
	if ((c_node->index + 1) % tc->term_size.ws_col == 0)
		tputs(debug_tgetstr("do", NULL), 0, output_func);
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
	if (tc)
		;
	while (buffer[i])
	{
		c_node = make_char(buffer[i]);
		if (tc->line.cursor_x + 1 >= tc->line.list_str->size)
		{
			ft_list_push_before_node(&tc->line.list_str,
			&tc->line.cur_c_node->link, &c_node->link);
			update_list_index(tc->line.list_str->head);
			ft_putchar(c_node->c);
			update_cursor_pos(tc, 1, 0);
		}
		else
		{
			insert_before_char(tc, c_node);
		}
		i++;
	}
	//if ((tc->line.cursor_x) % tc->term_size.ws_col == 0)
	//	tputs(debug_tgetstr("do", NULL), 0, output_func);
}

void	init_list_str(t_term *tc)
{
	t_char	*cursor_end;

	cursor_end = make_char('\0');
	ft_list_push_back(&tc->line.list_str, &cursor_end->link);
	update_list_index(tc->line.list_str->head);
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