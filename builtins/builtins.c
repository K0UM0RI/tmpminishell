
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
		i++;
	}
	if (command[i][n] && n)
		n = 0;
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