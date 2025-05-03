/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:45 by sbat              #+#    #+#             */
/*   Updated: 2025/05/03 16:50:55 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getmyenv(char *var, char **env)
{
	int	l;
	int	j;

	j = 0;
	l = ft_strlen(var);
	if (!var)
		return NULL;
	while (env[j])
	{
		if (!ft_strncmp(env[j], var, l) && env[j][l] == '=')
			return (env[j] + l + 1);
		j++;
	}
	return (NULL);
}
