#include "mytermcaps.h"

int		exec_key(t_term *tc, char buffer[5])
{
	int 	i;
	int 	ret;

	i = 0;
	while (i < KEY_COUNT)
	{
		ret = tc->f[i](tc, buffer);
		if (ret == 1)
			return (1);
		else if (ret == -1)
			return (-1);
		i++;
	}
	return (0);
}

t_char	*make_char(char c)
{
	t_char	*c_node;

	c_node = (t_char*)ft_memalloc(sizeof(t_char));
	if (c_node == NULL)
		error("ft_memalloc", __LINE__);
	c_node->c = c;
	return (c_node);
}

void	update_list_index(t_link *l)
{
	int 	i;

	i = 0;
	while (l)
	{
		((t_char*)l)->index = i;
		l = l->next;
		i++;
	}
}

void	insert_between_char(t_term *tc, t_char *new_node)
{
	ft_list_push_before_node(&tc->line.list_str,
	&tc->line.cur_c_node->link, &new_node->link);
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
	t_char	*cur_c_node;

	i = 0;
	cur_c_node = tc->line.cur_c_node;
	while (buffer[i])
	{
		c_node = make_char(buffer[i]);
		if (cur_c_node && cur_c_node->index + 1 < tc->line.list_str->size)
			insert_between_char(tc, c_node);
		else
			ft_list_push_back(&tc->line.list_str, &c_node->link);
		if (tc->line.cursor_x + 1 >= tc->term_size.ws_col &&
			cur_c_node->index + 1 < tc->line.list_str->size)
			write_and_new_line(tc, buffer[i]);
		else
			ft_putchar(buffer[i]);
		update_list_index(tc->line.list_str->head);
		i++;
	}
	ft_list_print(tc->line.list_str->head, debug_print_t_char);
	dprintf(fd_debug, "\n");
	update_cursor_pos(tc, 1, 0);
}

int     read_key(t_term *tc)
{
	char    buffer[6];
	int 	ret;

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

void	init_key(t_term *tc)
{
	tc->f[0] = arrow_up;
	tc->f[1] = arrow_down;
	tc->f[2] = arrow_right;
	tc->f[3] = arrow_left;
	tc->f[4] = ctrl_d;
}

void	init_term(t_term *tc)
{
	ft_bzero(tc, sizeof(t_term));
	init_key(tc);
	if ((tc->name_term = getenv("TERM")) == NULL)
		error("getenv", __LINE__);
	if (tgetent(NULL,  tc->name_term) == -1)
		error("tgetent", __LINE__);
	if (tcgetattr(STDIN_FILENO, &tc->term) == -1)
		error("tcgetattr", __LINE__);
	ft_memcpy(&tc->old_term, &tc->term, sizeof(struct termios));
	tc->term.c_lflag &= ~(ICANON);
	tc->term.c_lflag &= ~(ECHO);
	tc->term.c_cc[VMIN] = 1;
	tc->term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tc->term) == -1)
		error("tcsetattr", __LINE__);
	tputs(tgetstr("im", NULL), 0, output_func);
}

void	reset_term(t_term *tc)
{
	tputs(tgetstr("ei", NULL), 1, output_func);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tc->old_term) == -1)
		error("tcsetattr", __LINE__);
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