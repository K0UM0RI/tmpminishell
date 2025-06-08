/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:42 by sbat              #+#    #+#             */
/*   Updated: 2025/06/08 18:08:00 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_append(char *c1, char c2, int fn)
{
	char	*c;
	int		i;
	int		l;

	i = 0;
	l = 0;
	if (c1 > (char *)0)
		l = ft_strlen(c1);
	c = mymalloc(sizeof(char) * (l + 2), fn);
	while (c1 > (char *)0 && *c1)
	{
		c[i] = *c1;
		c1++;
		i++;
	}
	c[i] = c2;
	i++;
	c[i] = '\0';
	return (c);
}

char	*ft_strdup(char *s, int fn)
{
	char	*c;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	c = mymalloc(sizeof(char) * ft_strlen(s) + 1, fn);
	while (s[i])
	{
		c[i] = s[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

char	*ft_strjoin(char *s1, char *s2, int fn)
{
	size_t	len1;
	size_t	len2;
	char	*c;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2, fn));
	if (!s2)
		return (ft_strdup(s1, fn));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	c = mymalloc((len1 + len2 + 1) * sizeof(char), fn);
	ft_strlcpy(c, s1, len1 + 1);
	ft_strlcat(c + len1, s2, len1 + len2 + 1);
	return (c);
}
