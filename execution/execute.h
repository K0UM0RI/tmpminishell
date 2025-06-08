#ifndef EXECUTE_H
#define EXECUTE_H
#include "../minishell.h"

int	ft_lstsizeline(t_line *line);
void	cleanfds(int *fd, int end);
void	piping(int i, t_exec exec, t_line *line);
void	resetoldpipe(int *oldpipefd, int *pipefd);

//builtins
int	execbuiltin(t_line *line, t_env **env);
int	isbuiltin(char *command);
int	ft_export(char **command, t_env *env);
int	ft_env(t_env *env);
int	ft_echo(char **command);
void	openredirsnodup(t_redirections *reds);

//env
char	**convertenv(t_env *env);
char	*getcmd(char *cmd, t_env *env);
#endif