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
	char	**str;
	size_t	count;
	size_t	j;
	size_t	d;
	size_t	b;

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

static void	joinwithslash(char **paths)
{
	int		i;

	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/", 0);
		i++;
	}
}

char	**getpaths(t_env *env)
{
	char	**paths;

	while (env)
	{
		if (!ft_strncmp("PATH", env->name, 6))
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	paths = ft_split(env->value, ':');
	if (!paths)
		return (NULL);
	joinwithslash(paths);
	return (paths);
}

int	ifslash(char *av)
{
	while (*av)
	{
		if (*av == '/')
			return (1);
		av++;
	}
	return (0);
}

char	*checkpaths(char *env, char **paths)
{
	int		i;
	char	*c;

	i = 0;
	c = NULL;
	while (paths[i])
	{
		c = ft_strjoin(paths[i], env, 0);
		if (!c)
			return (perror("join fail"), NULL);
		if (!access(c, F_OK | X_OK))
			return (c);
		c = NULL;
		i++;
	}
	return (c);
}

char	*getcmd(char *cmd, t_env *env)
{
	char	*c;
	char	*error;
    char **paths;
	c = NULL;
	error = "command not found, or isnt executable\n";
	if (!cmd || !*cmd)
		return (NULL);
	if (ifslash(cmd))
	{
		if (!access(cmd, F_OK | X_OK))
			return (ft_strdup(cmd, 0));
		else
			return (write(2, error, ft_strlen(error)), NULL);
	}
    paths = getpaths(env);
	if (env)
		c = checkpaths(cmd, paths);
	if (c)
		return (c);
	return (write(2, error, ft_strlen(error)), NULL);
}