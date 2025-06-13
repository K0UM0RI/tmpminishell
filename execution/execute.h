/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:16:40 by sbat              #+#    #+#             */
/*   Updated: 2025/06/13 16:47:35 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../minishell.h"

int		ft_lstsizeline(t_line *line);
void	cleanfds(int *fd, int end);
void	piping(int i, t_exec exec, t_line *line);
void	resetoldpipe(int *oldpipefd, int *pipefd);
void	initexecstruct(t_exec *exec, t_line *line);

// utils2
int		openredirs(t_redirections *reds, int *file);
int		openredirsnodup(t_redirections *reds, int *file);
int		finishexec(t_exec exec, int i);

// builtins
int		execbuiltin(t_line *line, t_env **env);
int		isbuiltin(char *command);
int		ft_export(char **command, t_env **env);
int		ft_env(t_env *env);
int		ft_echo(char **command);
int		ft_pwd(t_env *env);

// env
char	**convertenv(t_env *env);
char	*getcmd(char *cmd, t_env *env);
#endif