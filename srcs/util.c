#include "mytermcaps.h"

int		output_func(int c)
{
	return ((int)write(STDIN_FILENO, &c, 1));
}

void	update_term_size(t_term *tc)
{
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, (char*) &tc->term_size) < 0)
		error("ioctl", __LINE__);
}