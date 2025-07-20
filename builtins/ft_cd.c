/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:14:22 by sbat              #+#    #+#             */
/*   Updated: 2025/07/20 11:06:13 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	getrelativepath(char *command, char *pwd)
{
	char	*tmp;

	tmp = ft_strjoin("/", command, MALLOC_TMP);
	tmp = ft_strjoin(pwd, tmp, MALLOC_TMP);
	if (chdir(tmp) && chdir(command))
		return (perror("chdir"), MALLOC_TMP);
	return (1);
}

int	updatepwd(t_env **env, char *tmp, int s)
{
	if (!s)
	{
		if (chdir(tmp))
			return (perror("chdir"), 1);
	}
	tmp = mymalloc(sizeof(char) * 4096, MALLOC_TMP);
	if (!getcwd(tmp, 4096))
		return (perror("getcwd"), 1);
	unprotectedgetnewvar(*env, ft_strdup("PWD", MALLOC_LASTING), ft_strdup(tmp, MALLOC_LASTING));
	unprotectedgetnewvar(*env, ft_strdup("1PWD", MALLOC_LASTING), ft_strdup(tmp, MALLOC_LASTING));
	return (0);
}

int	ft_cd(char **command, t_env **env)
{
	char	*pwd;
	char	*tmp;
	int		s;

	s = 0;
	pwd = getmyenv("1PWD", *env);
	tmp = NULL;
	if (!command[1])
	{
		tmp = getmyenv("HOME", *env);
		if (!tmp)
			return (write(2, "HOME not set\n", 14), 1);
	}
	else if (command[2])
		write(2, "cd: too many arguments\n", 24);
	else if (*command[1] == '/')
		tmp = command[1];
	else
	{
		if (!getrelativepath(command[1], pwd))
			return (1);
		s = 1;
	}
	return (updatepwd(env, tmp, s));
}
