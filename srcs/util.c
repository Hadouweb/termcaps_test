#include "mytermcaps.h"

int		output_func(int c)
{
	return (write(2, &c, 1));
}

void	update_term_size(t_term *tc)
{
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, (char*) &tc->term_size) < 0)
		error("ioctl", __LINE__);
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

void	reset_term(t_term *tc)
{
	tputs(debug_tgetstr("ei", NULL), 1, output_func);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tc->old_term) == -1)
		error("tcsetattr", __LINE__);
}
