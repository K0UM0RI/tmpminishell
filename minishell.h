#ifndef MINISHELL_H

# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_tree
{
    char *elem;
    int type;
    struct s_tree *left;
    struct s_tree *right;
}t_tree;

char	*ft_strjoin(char *s1, char *s2);
int ft_strlen(char *c);
#endif