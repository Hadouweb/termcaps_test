#include "mytermcaps.h"

void	update_cur_c_node(t_term *tc, int x, int y)
{
	t_link	*l;
	t_char	*c_node;

	l = &tc->line.cur_c_node->link;
	if (x == -1 || (x == 0 && y == -1))
	{
		l = l->prev;
		while (l)
		{
			c_node = (t_char*)l;
			if (c_node->ignore == 0)
				break;
			l = l->prev;
		}
		tc->line.cur_c_node = c_node;
	}
	else if (x == 1 || (x == 0 && y == 1))
	{
		l = l->next;
		while (l)
		{
			c_node = (t_char*)l;
			if (c_node->ignore == 0)
				break;
			l = l->next;
		}
		tc->line.cur_c_node = c_node;
	}
}

void	update_cursor_pos(t_term *tc, int x, int y)
{
	update_cur_c_node(tc, x, y);
	if (x == 1)
	{
		if ((tc->line.cursor_x + 1) >= tc->term_size.ws_col)
		{
			PRINT_DEBUG("__here 1\n");
			tc->line.cursor_y += 1;
			tc->line.cursor_x = 0;
		}
		else if (tc->line.cursor_x < tc->term_size.ws_col)
		{
			PRINT_DEBUG("__here 2\n");
			tc->line.cursor_x += 1;
		}
	}
	else if (x == -1)
	{
		if (tc->line.cursor_x == 0 && tc->line.cursor_y > 0)
		{
			PRINT_DEBUG("__here 3\n");
			tc->line.cursor_y += -1;
			tc->line.cursor_x = tc->term_size.ws_col - 1;
		}
		else if (tc->line.cursor_x > 0)
		{
			PRINT_DEBUG("__here 4\n");
			tc->line.cursor_x += -1;
		}
	}
	ft_list_print(tc->line.list_str->head, debug_print_t_char);
	debug_print_cursor_pos(tc);
	debug_term_size(tc);
	dprintf(fd_debug, "\n");
}

void	update_new_line(t_term *tc)
{
	t_link	*l;
	t_char	*c_node;
	t_char	*new_line;

	l = tc->line.list_str->head;
	while (l)
	{
		c_node = (t_char*)l;
		if (c_node->index % tc->term_size.ws_col == 0)
		{
			new_line = make_char('\n');
			new_line->ignore = 1;
			ft_list_push_before_node(&tc->line.list_str, &c_node->link, &new_line->link);
			//dprintf(fd_debug, "GO NEW_LINE BEFORE %d %c\n", c_node->index, c_node->c);
		}
		l = l->next;
	}
}

void	move_cursor_to_c_node(t_term *tc, t_char *c_node)
{
	while (tc->line.cur_c_node != c_node)
	{
		move_left(tc);
		//sleep(1);
	}
}

void	print_line(t_term *tc, t_link *l)
{
	t_char	*c_node;
	t_char	*orig_c_node;

	if (tc)
		;
	orig_c_node = tc->line.cur_c_node;
	tputs(debug_tgetstr("cd", NULL), 0, output_func);
	//ft_putchar(tc->line.cur_c_node->c);
	//update_cursor_pos(tc, 1, 0);
	//l = l->next;
	while (l->next)
	{
		c_node = (t_char *)l;
		dprintf(fd_debug, "print_char %c\n", c_node->c);
		ft_putchar(c_node->c);
		update_cursor_pos(tc, 1, 0);
		if (tc->line.cursor_x == 0 && tc->line.cursor_y > 0)
		{
			tputs(debug_tgetstr("do", NULL), 0, output_func);
		}
		//sleep(1);
		l = l->next;
	}
	move_cursor_to_c_node(tc, orig_c_node);
	//tputs(debug_tgetstr("nd", NULL), 0, output_func);
}

void	insert_new_char(t_term *tc, t_char *new_node)
{
	ft_list_push_before_node(&tc->line.list_str, &tc->line.cur_c_node->link, &new_node->link);
	tc->line.cur_c_node = new_node;
	ft_putchar(new_node->c);
	update_cursor_pos(tc, 1, 0);
	if (tc->line.cursor_x == 0 && tc->line.cursor_y > 0)
	{
		tputs(debug_tgetstr("do", NULL), 0, output_func);
	}
	if (tc->line.list_str->size > tc->term_size.ws_col &&
		tc->line.cur_c_node->link.next)
	{
		dprintf(fd_debug, "NEW LINE\n");
		print_line(tc, &tc->line.cur_c_node->link);
	}
	//else
	//{
	//}
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
		update_list_index(tc->line.list_str->head);
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