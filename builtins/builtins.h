#ifndef BUILTINS_H
#define BUILTINS_H
#include "../minishell.h"

int	isbuiltin(char *command);
int	isnumber(char *c);

void	openredirsnodup(t_redirections *reds);

//clean
void	cleanfds(int *fd, int end);
#endif