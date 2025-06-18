/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:15:48 by sbat              #+#    #+#             */
/*   Updated: 2025/06/18 01:37:36 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	isbuiltin(char *command)
{
	if (!command)
		return (-1);
	if (!ft_strncmp(command, "cd", 3) || !ft_strncmp(command, "unset", 6)
		|| !ft_strncmp(command, "exit", 5))
		return (1);
	return (0);
}

int	isnumber(char *c)
{
	int	i;

	i = 0;
	if (!c || !*c || (ft_strlen(c) > 20 && ft_isnum(*c)) || (ft_strlen(c) > 21 && !ft_isnum(*c)) )
		return (write(2, "numeric argument required\n", 27), 0);
	if (c[i] && (c[i] == '-' || c[i] == '+'))
		i++;
	while (c[i] && (c[i] >= '0' && c[i] <= '9'))
		i++;
	if (c[i])
		return (write(2, "numeric argument required\n", 27), 0);
	return (1);
}

int	foundchar(char f, char *c)
{
	while (*c)
	{
		if (*c == f)
			return (1);
		c++;
	}
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
