/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:45 by sbat              #+#    #+#             */
/*   Updated: 2025/05/15 17:14:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getmyenv(char *var, t_env *env)
{
	int	l;

	if (!var)
		return NULL;
	l = ft_strlen(var);
	if (!l)
		return NULL;
	// if (!ft_strncmp(var, "?", 1))
	while (env)
	{
		if (!ft_strncmp(env->name, var, l))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

void newenv(t_env **lstenv, char *name, char *value)
{
	t_env *env;

	if (!ft_strncmp(name, "SHLVL", 5))
		value = ft_itoa(ft_atoi(value) + 1);
	env = mymalloc(sizeof(t_env), 0);
	env->name = ft_strdup(name);
	env->value = ft_strdup(value);
	env->next = NULL;
	(*lstenv)->next = env;
	*lstenv = (*lstenv)->next;
}

t_env *getenvlst(char **env)
{
	t_env *lstenv;
	t_env *head;

	int (i), (j) = 0;
	if (!env)
		return NULL;
	newenv(&lstenv, NULL, NULL);
	head = lstenv;
	while (env[j])
	{
		i = 0;
		while (env[j][i])
		{
			if (env[j][i] == '=')
			{
				env[j][i] = '\0';
			 	newenv(&lstenv, env[j], env[j] + i + 1);
				break;
			}
			i++;
		}
		j++;
	}
	return (head->next);
}
