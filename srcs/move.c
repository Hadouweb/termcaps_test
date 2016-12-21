#include "mytermcaps.h"

void	move_left(t_term *tc)
{
	unsigned int	len_line;
	if (tc->line.cursor_x == 0)
		return ;
	if (tc->line.cursor_x % tc->term_size.ws_col == 0)
	{
		len_line = tc->term_size.ws_col;
		tputs(debug_tgetstr("up", NULL), 0, output_func);
		while (len_line--)
			tputs(debug_tgetstr("nd", NULL), 0, output_func);
	}
	else
		tputs(debug_tgetstr("le", NULL), 0, output_func);
	update_cursor_pos(tc, -1);
}

void	move_right(t_term *tc)
{
	update_cursor_pos(tc, 1);
	if (tc->line.cursor_x % tc->term_size.ws_col == 0)
		tputs(debug_tgetstr("do", NULL), 0, output_func);
	else
		tputs(debug_tgetstr("nd", NULL), 0, output_func);
}