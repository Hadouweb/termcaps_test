CC = gcc -Werror -Wextra -Wall -g

SRCPATH = ./srcs
OPTION_L = $(SRCPATH)/option_l

INCPATH = ./includes

LIBFTPATH = ./libft

HEADER = -I $(LIBFTPATH)/includes -I $(INCPATH)

LIB = -L$(LIBFTPATH) -lft -ltermcap
LIBNAME = $(LIBFTPATH)/libft.a

SRC = 	$(SRCPATH)/main.c\
    	$(SRCPATH)/error.c\
    	$(SRCPATH)/debug.c\
    	$(SRCPATH)/key_func.c\
    	$(SRCPATH)/util.c\
    	$(SRCPATH)/init.c\

OBJ = $(SRC:.c=.o)

NAME = tc

all: $(NAME)

$(NAME): $(LIBNAME) $(OBJ)
	@$(CC) -o $@ $(LIB) $^
	@echo "\n\033[39mCompilation done.\033[0m"

$(LIBNAME):
	@make -C $(LIBFTPATH) -j8

%.o: %.c
	@$(CC) -o $@ -c $< $(HEADER)
	@echo "\033[34m█\033[0m\c"

clean:
	@make -C $(LIBFTPATH) clean
	@rm -rf $(OBJ)

fclean: clean
	@make -C $(LIBFTPATH) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re