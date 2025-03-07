NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra #-Werror
SRC = minishell.c \

lib = minishell.h

all: $(NAME)

$(NAME): $(SRC) $(lib)
	$(CC) $(CFLAGS) $< libft.a -lreadline -o $@

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re