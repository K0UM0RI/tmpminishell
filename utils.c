/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:35:16 by sbat              #+#    #+#             */
/*   Updated: 2025/05/02 21:35:17 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (i < n)
	{
		if (s1[i] != s2[i] || !s1[i] || !s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dl;
	size_t	sl;

	if (!src)
		return (size);
	sl = ft_strlen(src);
	if (!dst)
		return (sl);
	dl = ft_strlen(dst);
	j = 0;
	i = dl;
	if (i >= size)
		return (sl + size);
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (dl + sl);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t i;
	size_t slen;

	if (!src)
		return (0);
	slen = ft_strlen(src);
	i = 0;
	if (dstsize == 0 || !dst)
		return (slen);
	while (i + 1 < dstsize && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (slen);
}