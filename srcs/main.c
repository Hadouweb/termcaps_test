#include "mytermcaps.h"

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

	read_key(&tc);

	reset_term(&tc);
	return (0);
}