#include "mytermcaps.h"

void	debug_termios(struct termios *term)
{
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

void	debug_term_size(t_term *tc)
{
	dprintf (fd_debug, "nb_line: [%d] nb_col: [%d]\n",
			tc->term_size.ws_row, tc->term_size.ws_col);
}

void	debug_init_tty(char *tty_name)
{
	int fd = open(tty_name, O_RDWR);
	if (fd == -1)
		error("debug_init_tty", __LINE__);
	dprintf(fd, "\n\033[035m*************** INIT DEBUG ***************\033[0m\n");
	fd_debug = fd;
	printf("%d\n", fd_debug);
}

void	debug_print_cursor_pos(t_term *tc)
{
	dprintf(fd_debug,
			C_YELLOW("\nx: [%d] y: [%d] cur_index_node: [%d] cur_char [%c]\n"),
			tc->line.cursor_x, tc->line.cursor_y,
			tc->line.cur_c_node->index, tc->line.cur_c_node->c);
}

void	debug_print_t_char(void *content)
{
	t_char	*c_node;

	c_node = (t_char*)content;
	dprintf(fd_debug, C_GREEN("|%c|%d| "), c_node->c, c_node->index);
}