/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:15:54 by sbat              #+#    #+#             */
/*   Updated: 2025/06/16 23:46:20 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../minishell.h"

int		isbuiltin(char *command);
int		isnumber(char *c);
int		foundchar(char f, char *c);
void	add_env(t_env *env, char *tmp);

int		ft_export(char **command, t_env **env);
int		ft_echo(char **command);
int		ft_cd(char **command, t_env **env);
int		ft_unset(char **command, t_env **env);
// clean
void	cleanfds(int *fd, int end);

// exec
void	handleredirections(t_redirections *reds);
#endif