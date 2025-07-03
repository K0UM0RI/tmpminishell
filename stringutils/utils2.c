/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:35:19 by sbat              #+#    #+#             */
/*   Updated: 2025/07/03 08:13:27 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	isoperator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_strlen(char *c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

int	ft_intlen(int n)
{
	int	len;

	len = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int	is_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0)
	{
		if ((sb.st_mode & S_IFMT) == S_IFDIR)
			return (1);
	}
	return (0);
}

void	exitandfree(int exit_status)
{
	mymalloc(0, 1);
	mymalloc(0, 3);
	exit(exit_status);
}
