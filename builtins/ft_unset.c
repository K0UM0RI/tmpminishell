/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:14:25 by sbat              #+#    #+#             */
/*   Updated: 2025/07/03 08:08:19 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	huntforvar(t_env **env, t_env *tmp, char *var)
{
	t_env	*previous;

	previous = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, var, ft_strlen(var)) && ft_strncmp(var, "?",
				2) && ft_strncmp(var, "1PWD", 5))
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
}

int	ft_unset(char **command, t_env **env)
{
	int	i;
	int	r;

	r = 0;
	i = 1;
	while (command[i])
	{
		huntforvar(env, *env, command[i]);
		i++;
	}
	return (r);
}
