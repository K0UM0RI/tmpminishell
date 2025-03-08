#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i] || !s1[i] || !s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	doublecharlen(char **c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

void	freed(char **c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		free(c[i]);
		i++;
	}
	free(c);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0)
		return ;
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}