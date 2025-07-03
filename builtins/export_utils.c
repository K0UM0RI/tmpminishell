/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 08:08:40 by sbat              #+#    #+#             */
/*   Updated: 2025/07/03 08:08:54 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_export(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->name, "?", 2) && ft_strncmp(env->name, "1", 1)
			&& ft_strncmp(env->name, "_", 2))
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
