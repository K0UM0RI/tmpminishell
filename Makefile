NAME = minishell
CC = clang
CFLAGS = -Wall -Wextra #-Werror
SRC = minishell.c \
	ft_strjoins.c \
	

lib = minishell.h

all: $(NAME)

$(NAME): $(SRC) $(lib)
	$(CC) $(CFLAGS) $(SRC) -lreadline -o $@

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re