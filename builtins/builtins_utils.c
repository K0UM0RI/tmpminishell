/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:15:48 by sbat              #+#    #+#             */
/*   Updated: 2025/06/18 23:50:23 by sbat             ###   ########.fr       */
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

int	ft_sstrlen(char *str)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] == '0')
		i++;
	while (str[i + l])
		l++;
	return (l + (*str == '-'));
}

int	isnumber(char *c)
{
	int	i;
	int longmax;

	i = 0;
	if (!c || !*c)
		return (write(2, "numeric argument required\n", 27), 0);
	if (c[i] && (c[i] == '-' || c[i] == '+'))
		i++;
	while (c[i] && (c[i] >= '0' && c[i] <= '9'))
		i++;
	if (c[i])
		return (write(2, "numeric argument required\n", 27), 0);
	if (*c == '+')
		c++;
	i = ft_sstrlen(c);
	if (*c == '-')
	{
		longmax = ft_sstrlen("-9223372036854775808");
		if (longmax < i)
			return (write(2, "numeric argument required\n", 27), 0);
		if (longmax == i && ft_strncmp("-9223372036854775808", c, i) < 0)
			return (write(2, "numeric argument required\n", 27), 0);
	}
	else
	{
		longmax = ft_sstrlen("9223372036854775807");
		if (longmax < i)
			return (write(2, "numeric argument required\n", 27), 0);
		if (longmax == i && ft_strncmp("9223372036854775807", c, i) < 0)
			return (write(2, "numeric argument required\n", 27), 0);
	}
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
