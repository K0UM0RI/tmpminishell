#include "minishell.h"

char	*ft_append(char *c1, char c2)
{
	char	*c;
	int		i;
	int		l;

	i = 0;
	l = 0;
	if (c1)
		l = ft_strlen(c1);
	c = malloc(sizeof(char) * (l + 2));
	while (c1 && *c1)
	{
		c[i] = *c1;
		c1++;
		i++;
	}
	c[i] = c2;
	i++;
	c[i] = '\0';
	// if (c1)
	//    free(c1);
	return (c);
}

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

char	*ft_strjoin(char *s1, char *s2)
{
	size_t len1;
	size_t len2;
	char *c;

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