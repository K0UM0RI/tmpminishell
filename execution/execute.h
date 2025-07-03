/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:16:40 by sbat              #+#    #+#             */
/*   Updated: 2025/07/03 08:11:16 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../minishell.h"

int					ft_lstsizeline(t_line *line);
void				cleanfds(int *fd, int end);
void				piping(int i, t_exec exec, t_line *line);
void				resetoldpipe(int *oldpipefd, int *pipefd);
void				initexecstruct(t_exec *exec, t_line *line);

// utils2
int					handleredirections(t_redirections *reds, int ft);
int					finishexec(t_exec exec, int i, struct sigaction old);

// builtins
int					execbuiltin(t_line *line, t_env **env);
int					isbuiltin(char *command);
int					ft_export(char **command, t_env **env);
int					ft_env(t_env *env);
int					ft_echo(char **command);
int					ft_pwd(char **command, t_env *env);

// env
char				**convertenv(t_env *env);
char				*getcmd(char *cmd, t_env *env);

struct sigaction	ignoreparentsigint(void);
void				ft_siginthere_subprocess(int sig);
#endif