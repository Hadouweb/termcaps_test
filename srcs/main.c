#include "mytermcaps.h"

int     voir_touche()
{
	char     buffer[3];

	while (1)
	{
		read(0, buffer, 3);
		if (buffer[0] == 27) {
			TERM_FONT_BOLD;
			printf("C'est une fleche !\n");
			TERM_FONT_NORMAL;
		}
		else if (buffer[0] == 4)
		{
			printf("Ctlr+d, on quitte !\n");
			return (0);
		}
	}
	return (0);
}

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
	ft_putchar(c);
	return (1);
}

void	print_term_size(void)
{
	struct winsize size;

	if (ioctl(STDIN_FILENO,TIOCGWINSZ, (char*) &size)<0)
		printf ("Erreur TIOCGEWINSZ\n");

	printf ("votre terminal comporte %d lignes et %d colones\n",
			size.ws_row,size.ws_col);
}

int		main(int ac, char **av, char **env)
{
	char           *name_term;
	struct termios term;
	struct termios old_term;
	char    		*res;
	char    		*res2;

	if (ac && av && env)
		;
	//print_term_size();
	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	printf("%s\n", name_term);
	if (tgetent(NULL,  name_term) == -1)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	memcpy(&old_term, &term, sizeof(struct termios));
	debug_termios(&term);
	term.c_lflag &= ~(ICANON); // Met le terminal en mode canonique.
	term.c_lflag &= ~(ECHO); // les touches tapées ne s'inscriront plus dans le terminal
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	// On applique les changements :
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	debug_termios(&term);

	if ((res = tgetstr("cl", NULL)) == NULL)
		return (-1);
	//tputs(res, 0, my_outc);

	res2 = tgetstr("cm", NULL);
	//tputs(tgoto(res2, 0, 0), 1, my_outc);
	voir_touche();
	if (tcsetattr(0, TCSADRAIN, &old_term) == -1)
		return (-1);
	return (0);
}