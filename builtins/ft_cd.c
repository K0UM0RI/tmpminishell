/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:14:22 by sbat              #+#    #+#             */
/*   Updated: 2025/06/13 22:14:23 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	getrelativepath(char *command, char *pwd)
{
	char	*tmp;

	tmp = ft_strjoin("/", command, 0);
	tmp = ft_strjoin(pwd, tmp, 0);
	if (chdir(tmp) && chdir(command))
		return (perror("chdir"), 0);
	return (1);
}

int	updatepwd(t_env **env, char *tmp, int s)
{
	if (!s)
	{
		if (chdir(tmp))
			return (perror("chdir"), 1);
	}
	tmp = mymalloc(sizeof(char) * 4096, 0);
	if (!getcwd(tmp, 4096))
		return (perror("getcwd"), 1);
	unprotectedgetnewvar(*env, ft_strdup("PWD", 2), ft_strdup(tmp, 2));
	unprotectedgetnewvar(*env, ft_strdup("1PWD", 2), ft_strdup(tmp, 2));
	return (0);
}

int	ft_cd(char **command, t_env **env)
{
	char *pwd;
	char *tmp;
	int s;

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