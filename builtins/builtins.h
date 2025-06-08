#ifndef BUILTINS_H
#define BUILTINS_H
#include "../minishell.h"

int	isbuiltin(char *command);
int	isnumber(char *c);
int	ft_isalpha(int c);
int foundchar(char f, char *c);

void	openredirsnodup(t_redirections *reds);

int	ft_export(char **command, t_env *env);

//clean
void	cleanfds(int *fd, int end);
#endif