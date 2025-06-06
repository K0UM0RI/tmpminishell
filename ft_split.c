#include "minishell.h"

static size_t	countwords(const char *s, char c)
{
	size_t	l;

	l = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			l++;
		while (*s && *s != c)
			s++;
	}
	return (l);
}

static void	wordlen(const char *s, char c, size_t *d, size_t *b)
{
	while (s[*b] == c && s[*b])
		*b = *b + 1;
	*d = *b;
	while (s[*b] != c && s[*b])
		*b = *b + 1;
}

char	**ft_split(char *s, char c)
{
	char **str;
	size_t count;
	size_t j;
	size_t d;
	size_t b;

	if (!s)
		return (NULL);
	count = countwords(s, c);
	str = (char **)mymalloc(sizeof(char *) * (count + 1), 0);
	j = 0;
	b = 0;
	while (j < count)
	{
		wordlen(s, c, &d, &b);
		str[j] = (char *)mymalloc(sizeof(char) * (b - d + 1), 0);
		ft_strlcpy(str[j++], s + d, b - d + 1);
	}
	str[count] = NULL;
	return (str);
}