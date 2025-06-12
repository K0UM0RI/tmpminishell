/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:15:23 by sbat              #+#    #+#             */
/*   Updated: 2025/06/12 15:15:15 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "builtins.h"

char	*getrelativepath(char *command, char *pwd)
{
	char	*tmp;

	tmp = ft_strjoin("/", command, 0);
	tmp = ft_strjoin(pwd, tmp, 0);
	if (chdir(tmp) && chdir(command) )
		return (perror("chdir"), NULL);
	tmp = mymalloc(sizeof(char) * 4096, 0);
	if (!getcwd(tmp, 4096))
		return (perror("getcwd"), NULL);
	return (tmp);
}

int	updatepwd(t_env **env, char *tmp, int s)
{
	if (!s)
	{
		if (chdir(tmp))
			return (perror("chdir"), 1);
	}
	unprotectedgetnewvar(*env, ft_strdup("PWD", 2), ft_strdup(tmp, 2));
	unprotectedgetnewvar(*env, ft_strdup("1PWD", 2), ft_strdup(tmp, 2));
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
		tmp = getrelativepath(command[1], pwd);
		if (!tmp)
			return (1);
		s = 1;
	}
	return (updatepwd(env, tmp, s));
}

int	ft_pwd(t_env *env)
{
	printf("%s\n", getmyenv("1PWD", env));
	exit(0);
}

int	ft_echo(char **command)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (!ft_strncmp(command[i], "-n", 2))
	{
		n = 1;
		while (command[i][n] == 'n')
			n++;
		i++;
	}
	if (command[i] && command[i][n])
		n = 0;
	while (command[i])
	{
		write(1, command[i], ft_strlen(command[i]));
		if (command[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n)
		write(1, "\n", 1);
	return (0);
}

int	ft_env(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->name, "?", 2) && env->value && ft_strncmp(env->name,
				"1PWD", 5))
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}

int	ft_exit(char **command, t_env *env)
{
	int	e;

	write(2, "exit\n", 5);
	if (!command[1])
	{
		e = ft_atoi(getmyenv("?", env)) & 0xFF;
		(mymalloc(0, 1), mymalloc(0, 3), exit(e));
	}
	if (command[2])
		return (write(2, "too many arguments\n", 20), 1);
	if (isnumber(command[1]))
		e = ft_atoi(command[1]) & 0xFF;
	else
		e = 2;
	mymalloc(0, 1);
	mymalloc(0, 3);
	exit(e);
}

int	ft_unset(char **command, t_env **env)
{
	int	i;

	t_env(*tmp), (*previous);
	i = 1;
	while (command[i])
	{
		tmp = *env;
		previous = NULL;
		while (tmp)
		{
			if (!ft_strncmp(tmp->name, command[i], ft_strlen(command[i]))
				&& ft_strncmp(command[i], "?", 2) && ft_strncmp(command[i],
					"1PWD", 5))
			{
				if (previous)
					previous->next = tmp->next;
				else
					*env = (*env)->next;
				break ;
			}
			previous = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
int	execbuiltin(t_line *line, t_env **env)
{
	if (!ft_strncmp(line->command[0], "cd", 3))
		return (ft_cd(line->command, env));
	if (!ft_strncmp(line->command[0], "export", 7))
		return (ft_export(line->command, env));
	if (!ft_strncmp(line->command[0], "unset", 6))
		return (ft_unset(line->command, env));
	if (!ft_strncmp(line->command[0], "exit", 5))
		return (ft_exit(line->command, *env));
	return (0);
}