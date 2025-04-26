#include "minishell.h"


char	*ft_strdup(char *s)
{
	char	*c;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	c = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!c)
		return (perror("ft_strdup malloc fail"), NULL);
	while (s[i])
	{
		c[i] = s[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

char	*freestr(char *str)
{
	if (str)
		free(str);
	return (NULL);
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

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*c;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	c = malloc((len1 + len2 + 1) * sizeof(char));
	if (!c)
		return (NULL);
	ft_strlcpy(c, s1, len1 + 1);
	ft_strlcat(c + len1, s2, len1 + len2 + 1);
	return (free(s1), c);
}