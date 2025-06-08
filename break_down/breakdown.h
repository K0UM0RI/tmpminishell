
#ifndef BREAKDOWN_H
#define BREAKDOWN_H
#include "../minishell.h"

t_redirections	*red_new(char *file, int type);
void	red_addback(t_redirections **head, t_redirections *new);

#endif