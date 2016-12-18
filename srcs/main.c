#include "mytermcaps.h"

void	debug_termios(struct termios *term) {
	printf("- input flags :   [c_iflag] => %lu\n", term->c_iflag);
	printf("- output flags :  [c_oflag] => %lu\n", term->c_oflag);
	printf("- control flags : [c_cflag] => %lu\n", term->c_cflag);
	printf("- local flags :   [c_lflag] => %lu\n", term->c_lflag);
	printf("- control chars : [c_cc]\n");
	for (int i = 0; i < NCCS; i++)
	{
		ft_putchar('\t');
		ft_printbit(term->c_cc[i]);
		printf(" | index : [%d]\t| value : %d\n", i, term->c_cc[i]);
	}
	printf("- input speed :   [c_ispeed] => %lu\n", term->c_ispeed);
	printf("- output speed :  [c_ospeed] => %lu\n", term->c_ospeed);
	printf("\n");
}

int		my_outc(int c)
{
	return ((int)write(STDIN_FILENO, &c, 1));
}

void	print_term_size(void)
{
	struct winsize size;

	if (ioctl(STDIN_FILENO,TIOCGWINSZ, (char*) &size)<0)
		printf ("Erreur TIOCGEWINSZ\n");

	printf ("votre terminal comporte %d lignes et %d colones\n",
			size.ws_row,size.ws_col);
}

int 	move_up(char buffer[5])
{
	if (ft_memcmp(buffer, KEY_UP, 5) == 0)
	{
		tputs(tgetstr("le", NULL), 0, my_outc);
		return (1);
	}
	return (0);
}

int 	move_down(char buffer[5])
{
	if (ft_memcmp(buffer, KEY_DOWN, 5) == 0)
	{
		tputs(tgetstr("nd", NULL), 0, my_outc);
		return (1);
	}
	return (0);
}

int 	move_right(char buffer[5])
{
	if (ft_memcmp(buffer, KEY_RIGHT, 5) == 0)
	{
		tputs(tgetstr("nd", NULL), 0, my_outc);
		return (1);
	}
	return (0);
}

int 	move_left(char buffer[5])
{
	if (ft_memcmp(buffer, KEY_LEFT, 5) == 0)
	{
		tputs(tgetstr("le", NULL), 0, my_outc);
		return (1);
	}
	return (0);
}

int		exec_key(t_term *tc, char buffer[5])
{
	int 	i;

	i = 0;
	while (i < k_count)
	{
		if (tc->f[i](buffer) == 1)
			return (1);
		i++;
	}
	return (0);
}

int     read_key(t_term *tc)
{
	char    buffer[6];
	int 	ret;
	int 	s;

	while (1)
	{
		s = read(0, buffer, 5);
		buffer[s] = '\0';
		ret = exec_key(tc, buffer);
		if (ret == 0)
			ft_putstr(buffer);
	}
	return (0);
}

void	error(char *str, int line)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("at line : ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	init_key(t_term *tc)
{
	tc->f[0] = move_up;
	tc->f[1] = move_down;
	tc->f[2] = move_right;
	tc->f[3] = move_left;
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
	tputs(tgetstr("im", NULL), 0, my_outc);
}

void	reset_term(t_term *tc)
{
	tputs(tgetstr("ei", NULL), 1, my_outc);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tc->old_term) == -1)
		error("tcsetattr", __LINE__);
}

int		main(void)
{
	t_term		tc;

	init_term(&tc);
	//debug_termios(&tc.term);

	read_key(&tc);

	reset_term(&tc);
	return (0);
}