/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:15:57 by sbat              #+#    #+#             */
/*   Updated: 2025/07/20 11:05:27 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	isvalididentifier(char *tmp, int p)
{
	int	i;

	i = 1;
	if ((!ft_isalpha(*tmp) && *tmp != '_') || !*tmp)
		return (0);
	while (tmp[i])
	{
		if (!ft_isalpha(tmp[i]) && !ft_isnum(tmp[i]) && tmp[i] != '_')
		{
			if (p >= 0 && i == p - 1 && tmp[p - 1] == '+')
				return (2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	attachnewvar(char *tmp, t_env **env, int s, int v)
{
	t_env	*tmpenv;
	t_env	*previous;

	tmpenv = *env;
	previous = NULL;
	while (tmpenv && ft_strncmp(tmpenv->name, tmp, ft_strlen(tmp)))
	{
		previous = tmpenv;
		tmpenv = tmpenv->next;
	}
	if (!tmpenv && previous)
	{
		add_env(previous, tmp);
		tmpenv = previous->next;
	}
	if (s > 0 && v == 1)
		tmpenv->value = ft_strdup(tmp + s + 1, MALLOC_LASTING);
	else if (s > 0 && v == 2)
		tmpenv->value = ft_strjoin(tmpenv->value, tmp + s + 1, MALLOC_LASTING);
}

int	getnewvar(char *tmp, t_env **env)
{
	int	s;
	int	v;

	s = getvalue(tmp);
	v = isvalididentifier(tmp, s);
	if (!v)
	{
		if (s >= 0)
			tmp[s] = '=';
		return (write(2, "export: \'", 10), write(2, tmp, ft_strlen(tmp)),
			write(2, "\' not a valid identifier\n", 26), 2);
	}
	if (v == 2)
		tmp[s - 1] = '\0';
	if (!*env)
	{
		(*env) = mymalloc(sizeof(t_env), MALLOC_LASTING);
		(*env)->name = ft_strdup(tmp, MALLOC_LASTING);
		if (s > 0)
			(*env)->value = ft_strdup(tmp + s + 1, MALLOC_LASTING);
		(*env)->next = NULL;
		return (0);
	}
	attachnewvar(tmp, env, s, v);
	return (0);
}

int	ft_export(char **command, t_env **env)
{
	int	i;
	int	r;

	r = 0;
	i = 1;
	if (!command[i])
		print_export(*env);
	while (command[i])
	{
		if (getnewvar(ft_strdup(command[i], MALLOC_TMP), env))
			r = 2;
		i++;
	}
	return (r);
}
