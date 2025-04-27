NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra #-Werror
SRC = ft_strjoins.c \
	clean_line_utils.c \
	clean_line.c \
	env_utils.c \
	parse_utils.c \
	utils.c \
	utils2.c \
	minishell.c \
	

lib = minishell.h

all: $(NAME)

$(NAME): $(SRC) $(lib)
	$(CC) $(CFLAGS) $(SRC) -lreadline -o $@

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re