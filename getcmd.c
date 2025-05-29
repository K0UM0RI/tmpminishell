#include "minishell.h"

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
			return (NULL);
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