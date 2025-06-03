/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:45 by sbat              #+#    #+#             */
/*   Updated: 2025/06/03 13:00:14 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_lstsizeenv(t_env *env)
{
	int size;

	size = 0;
	while(env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	*getmyenv(char *var, t_env *env)
{
	int	l;

	if (!var)
		return (NULL);
	l = ft_strlen(var);
	if (!l)
		return (NULL);
	while (env)
	{
		if (!ft_strncmp(env->name, var, l))
			return (ft_strdup(env->value, 2));
		env = env->next;
	}
	return (NULL);
}

void	newenv(t_env **lstenv, char *name, char *value)
{
	t_env	*env;

	if (!ft_strncmp(name, "SHLVL", 5))
		value = ft_itoa(ft_atoi(value) + 1, 2);
	env = mymalloc(sizeof(t_env), 2);
	env->name = ft_strdup(name, 2);
	env->value = ft_strdup(value, 2);
	env->next = NULL;
	(*lstenv)->next = env;
	*lstenv = (*lstenv)->next;
}

t_env	*getenvlst(char **env)
{
	t_env	*lstenv;
	t_env	*head;

	int (i), (j) = 0;
	if (!env)
		return (NULL);
	lstenv = mymalloc(sizeof(t_env), 2);
	lstenv->next = NULL;
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
			}
			i++;
		}
		j++;
	}
	newenv(&lstenv, "?", "0");
	return (head->next);
}

char **convertenv(t_env *env)
{
	int size;
	char **ret;
	int i = 0;
	
	size = ft_lstsizeenv(env);
	ret = mymalloc(sizeof(char *) * (size + 1), 0);
	while (env)
	{
		if (!ft_strncmp(env->name, "?", 2))
			env = env->next;
		else
		{
			ret[i] = ft_append(env->name, '=', 0);
			ret[i] = ft_strjoin(ret[i], env->value, 0);
			i++;
			env = env->next;
		}
	}
	ret[i] = NULL;
	return (ret);
}
