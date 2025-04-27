#include "minishell.h"

char	*getmyenv(char *var, char **env)
{
	int l;
	int j = 0;
	l = ft_strlen(var);
	while (env[j])
	{
		if (!ft_strncmp(env[j], var, l) && env[j][l] == '=')
			return (env[j] + l + 1);
		j++;
	}
	return (NULL);
}
