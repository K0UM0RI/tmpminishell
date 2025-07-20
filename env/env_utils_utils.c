/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 08:09:27 by sbat              #+#    #+#             */
/*   Updated: 2025/07/20 10:59:31 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	add_env(t_env *env, char *name)
{
	env->next = mymalloc(sizeof(t_env), MALLOC_LASTING);
	env->next->name = ft_strdup(name, MALLOC_LASTING);
	env->next->value = NULL;
	env->next->next = NULL;
}

void	newenv(t_env **lstenv, char *name, char *value)
{
	t_env	*env;

	if (!ft_strncmp(name, "SHLVL", 5))
		value = ft_itoa(ft_atoi(value) + 1, MALLOC_LASTING);
	env = mymalloc(sizeof(t_env), MALLOC_LASTING);
	env->name = ft_strdup(name, MALLOC_LASTING);
	env->value = ft_strdup(value, MALLOC_LASTING);
	env->next = NULL;
	if (!*lstenv)
		(*lstenv) = env;
	(*lstenv)->next = env;
	*lstenv = (*lstenv)->next;
}
