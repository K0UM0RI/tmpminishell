/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:35:16 by sbat              #+#    #+#             */
/*   Updated: 2025/06/08 18:08:08 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
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
	size_t	i;
	size_t	slen;

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

int	ft_atoi(const char *nptr)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		if (res > 2147483647 || res < -2147483648)
			return (0);
		i++;
	}
	return (res * sign);
}

char	*ft_itoa(int n, int fn)
{
	char	*str;
	int		len;
	int		tmp;
	int		neg;

	len = 1;
	tmp = n;
	neg = n < 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648", fn));
	while (tmp /= 10)
		len++;
	str = mymalloc(sizeof(char) * (len + neg + 1), fn);
	str[len + neg] = '\0';
	if (neg)
	{
		str[0] = '-';
		n = -n;
	}
	for (int i = len + neg - 1; i >= neg; i--)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
