
#include "builtins.h"

int	ft_echo(char **command)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (!ft_strncmp(command[i], "-n", 2))
	{
		n = 1;
		while (command[i][n] == 'n')
			n++;
		if (command[i][n])
		{
			n = 0;
			break ;
		}
		i++;
	}
	while (command[i])
	{
		write(1, command[i], ft_strlen(command[i]));
		if (command[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n)
		write(1, "\n", 1);
	return (0);
}

int	ft_export(char **command, t_env *env)
{
	char	*tmp;
	int		i;
	int		j;
	int		s;

	i = 1;
	tmp = NULL;
	if (!command[1])
	{
		while (env)
		{
			if (ft_strncmp(env->name, "?", 2))
			{
				printf("declare -x %s", env->name);
				if (env->value)
					printf("=\"%s\"", env->value);
				printf("\n");
			}
			env = env->next;
		}
		return (0);
	}
	while (command[i])
	{
		j = 0;
		s = 0;
		tmp = ft_strdup(command[i], 0);
		while (tmp[j] && tmp[j] != '=')
			j++;
		if (!tmp[j])
			s = 1;
		else
			tmp[j] = '\0';
		if (ft_strncmp(env->name, tmp, ft_strlen(tmp)))
		{
			while (env->next && ft_strncmp(env->next->name, tmp,
					ft_strlen(tmp)))
				env = env->next;
		}
		if (!ft_strncmp(tmp, "?", 2))
			return (write(2, "export: not a valid identifier\n", 32), 1);
		if (!env->next)
		{
			env->next = mymalloc(sizeof(t_env), 2);
			env->next->name = ft_strdup(tmp, 2);
			env->next->value = NULL;
			env->next->next = NULL;
		}
		if (!s)
			env->next->value = ft_strdup(tmp + j + 1, 2);
		i++;
	}
	return (0);
}

int	ft_env(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->name, "?", 2) && env->value)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}

int	ft_exit(char **command, t_env *env)
{
	int	e;

	write(2, "exit\n", 5);
	if (!command[1])
	{
		e = ft_atoi(getmyenv("?", env)) & 0xFF;
		(mymalloc(0, 1), mymalloc(0, 3), exit(e));
	}
	if (command[2])
		return (write(2, "too many arguments\n", 20), 1);
	if (isnumber(command[1]))
		e = ft_atoi(command[1]) & 0xFF;
	else
		e = 2;
	mymalloc(0, 1);
	mymalloc(0, 3);
	exit(e);
}

int	ft_unset(char **command, t_env **env)
{
	int	i;

	t_env(*tmp), (*previous);
	i = 1;
	while (command[i])
	{
		tmp = *env;
		previous = NULL;
		while (tmp)
		{
			if (!ft_strncmp(tmp->name, command[i], ft_strlen(command[i]))
				&& ft_strncmp(command[i], "?", 2))
			{
				if (previous)
					previous->next = tmp->next;
				else
					*env = (*env)->next;
				break ;
			}
			previous = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
int	execbuiltin(t_line *line, t_env **env)
{
	// if (!ft_strncmp(command[0], "cd", 3))
	//     return (ft_cd(command, env));
	// if (!ft_strncmp(command[0], "pwd", 4))
	//     return (ft_pwd());
	if (!ft_strncmp(line->command[0], "export", 7))
		return (ft_export(line->command, *env));
	if (!ft_strncmp(line->command[0], "unset", 6))
		return (ft_unset(line->command, env));
	if (!ft_strncmp(line->command[0], "exit", 5))
		return (ft_exit(line->command, *env));
	return (0);
}