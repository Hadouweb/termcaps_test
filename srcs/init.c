#include "mytermcaps.h"

void	init_key(t_term *tc)
{
	tc->f[0] = arrow_up;
	tc->f[1] = arrow_down;
	tc->f[2] = arrow_right;
	tc->f[3] = arrow_left;
	tc->f[4] = ctrl_d;
}

void	init_list_str(t_term *tc)
{
	t_char	*cursor_end;

	cursor_end = make_char('\0');
	ft_list_push_back(&tc->line.list_str, &cursor_end->link);
	update_list_index(tc->line.list_str->head);
	tc->line.cur_c_node = cursor_end;
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
}
