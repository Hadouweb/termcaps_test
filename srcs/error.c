#include "mytermcaps.h"

void	error(char *str, int line)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("at line : ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}