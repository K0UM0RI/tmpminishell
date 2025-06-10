/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:35:19 by sbat              #+#    #+#             */
/*   Updated: 2025/06/10 12:29:12 by sbat             ###   ########.fr       */
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
