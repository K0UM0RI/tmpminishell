/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:14:20 by sbat              #+#    #+#             */
/*   Updated: 2025/07/03 08:07:23 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	checkforoption(char **command, int *i)
{
	int	j;
	int	n;

	n = 0;
	while (!ft_strncmp(command[*i], "-n", 2))
	{
		j = 1;
		while (command[*i][j] == 'n')
			j++;
		if (command[*i] && !command[*i][j])
		{
			(*i)++;
			n = 1;
		}
		else
			break ;
	}
	return (n);
}

int	ft_echo(char **command)
{
	int	i;
	int	n;

	i = 1;
	n = checkforoption(command, &i);
	while (command[i])
	{
		write(1, command[i], ft_strlen(command[i]));
		if (command[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n)
		write(1, "\n", 1);
	return (0);
}
