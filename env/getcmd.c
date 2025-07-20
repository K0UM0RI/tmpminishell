/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:16:15 by sbat              #+#    #+#             */
/*   Updated: 2025/07/20 11:01:15 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	joinwithslash(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/", MALLOC_TMP);
		i++;
	}
}

char	**getpaths(t_env *env)
{
	char	**paths;

	paths = NULL;
	while (env)
	{
		if (!ft_strncmp("PATH", env->name, 6))
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	paths = ft_split(env->value, ':');
	if (!paths)
		return (NULL);
	joinwithslash(paths);
	return (paths);
}

int	ifslash(char *av)
{
	while (*av)
	{
		if (*av == '/')
			return (1);
		av++;
	}
	return (0);
}

char	*checkpaths(char *cmd, char **paths)
{
	int		i;
	char	*c;

	i = 0;
	c = NULL;
	if (!paths || !*paths)
		return (NULL);
	while (paths[i])
	{
		c = ft_strjoin(paths[i], cmd, MALLOC_TMP);
		if (!c)
			return (NULL);
		if (!access(c, F_OK | X_OK))
			return (c);
		c = NULL;
		i++;
	}
	return (c);
}

char	*getcmd(char *cmd, t_env *env)
{
	char	*c;
	char	*error;
	char	**paths;

	c = NULL;
	error = "command not found\n";
	if (!cmd)
		return (NULL);
	if (!*cmd)
		return (write(2, error, ft_strlen(error)), NULL);
	if (ifslash(cmd))
	{
		if (!access(cmd, F_OK))
			return (ft_strdup(cmd, MALLOC_TMP));
		else
			return (write(2, error, ft_strlen(error)), NULL);
	}
	paths = getpaths(env);
	if (paths)
		c = checkpaths(cmd, paths);
	else if (!access(cmd, F_OK))
		return (ft_strdup(cmd, MALLOC_TMP));
	if (c)
		return (c);
	return (write(2, error, ft_strlen(error)), NULL);
}
