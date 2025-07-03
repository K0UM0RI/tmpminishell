NAME     = minishell
CC       = cc
CFLAGS   = -Wall -Wextra -Werror
SRC      = break_down/breakdown.c \
           break_down/breakdown_utils.c \
           builtins/builtins.c \
           builtins/builtins_utils.c \
           builtins/export.c \
           builtins/export_utils.c \
           builtins/echo.c \
           builtins/ft_cd.c \
           builtins/ft_unset.c \
           clean_line/clean_line_utils.c \
           clean_line/clean_line.c \
           clean_line/clean_line_utils2.c \
           env/env_utils.c \
           env/getcmd.c \
           env/env_utils_utils.c \
           execution/execute.c \
           execution/execute_utils.c \
           execution/execute_utils2.c \
           here_doc/here_doc.c \
           here_doc/here_doc_expand.c \
           here_doc/here_doc_utils.c \
           malloc-free/garbage_collector.c \
           stringutils/ft_split.c \
           stringutils/ft_strjoins.c \
           stringutils/utils.c \
           stringutils/utils2.c \
           stringutils/utils3.c \
           minishell.c \
           signals/signals.c

OBJDIR   = obj

OBJS     = $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(SRC) | $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re