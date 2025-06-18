/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:15:23 by sbat              #+#    #+#             */
/*   Updated: 2025/06/18 01:43:07 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(char **command, t_env *env)
{
	if (command[1])
		return (write(2, "too many arguments\n", 20), 2);
	printf("%s\n", getmyenv("1PWD", env));
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
		e = ft_atoi(getmyenv("?", env)) & 0xFF;
	else if (command[2])
		return (write(2, "too many arguments\n", 20), 1);
	else if (isnumber(command[1]))
		e = ft_atoi(command[1]) & 0xFF;
	else
		e = 2;
	mymalloc(0, 1);
	mymalloc(0, 3);
	exit(e);
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
