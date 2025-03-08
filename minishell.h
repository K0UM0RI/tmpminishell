#ifndef MINISHELL_H

# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_tree
{
    char *elem;
    int type;
    struct s_tree *left;
    struct s_tree *right;
}t_tree;

void	freed(char **c);
int	doublecharlen(char **c);
int	ft_strcmp(const char *s1, const char *s2);
void	ft_putstr_fd(char *s, int fd);

#endif