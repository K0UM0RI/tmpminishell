/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:15:57 by sbat              #+#    #+#             */
/*   Updated: 2025/06/13 16:38:41 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_export(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->name, "?", 2) && ft_strncmp(env->name, "1", 1))
		{
			printf("declare -x %s", env->name);
			if (env->value)
				printf("=\"%s\"", env->value);
			printf("\n");
		}
		env = env->next;
	}
}

int	getvalue(char *tmp)
{
	int	j;

	j = 0;
	if (*tmp == '=')
		return (0);
	while (tmp[j] && tmp[j] != '=')
		j++;
	if (!tmp[j])
		return (-1);
	else
		tmp[j] = '\0';
	return (j);
}

int	isvalididentifier(char *tmp)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*tmp) && *tmp != '_')
		return (0);
	while (tmp[i])
	{
		if (!ft_isalpha(tmp[i]) && !ft_isnum(tmp[i]) && tmp[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	getnewvar(char *tmp, t_env **env)
{
	int		s;
	t_env	*tmpenv;

	tmpenv = *env;
	s = getvalue(tmp);
	if (!isvalididentifier(tmp))
	{
		if (s >= 0)
			tmp[s] = '=';
		write(2, "export: \'", 10);
		write(2, tmp, ft_strlen(tmp));
		write(2, "\' not a valid identifier\n", 26);
		return (1);
	}
	if (!*env)
	{
		(*env) = mymalloc(sizeof(t_env), 2);
		(*env)->name = ft_strdup(tmp, 2);
		if (s > 0)
			(*env)->value = ft_strdup(tmp + s + 1, 2);
		(*env)->next = NULL;
		return (0);
	}
	if (ft_strncmp(tmpenv->name, tmp, ft_strlen(tmp)))
	{
		while (tmpenv->next && ft_strncmp(tmpenv->next->name, tmp,
				ft_strlen(tmp)))
			tmpenv = tmpenv->next;
	}
	if (!tmpenv->next)
		add_env(tmpenv, tmp);
	if (s > 0)
		tmpenv->next->value = ft_strdup(tmp + s + 1, 2);
	return (0);
}

int	ft_export(char **command, t_env **env)
{
	int i;
	int r;

	r = 0;
	i = 1;
	if (!command[i])
		print_export(*env);
	while (command[i])
	{
		if (getnewvar(ft_strdup(command[i], 2), env))
			r = 1;
		i++;
	}
	return (r);
}