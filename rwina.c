#include "minishell.h"

void	exitcommand(char **tmp)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 2);
	if (doublecharlen(tmp) == 1)
		(freed(tmp), exit(0));
	if (doublecharlen(tmp) > 2)
		(freed(tmp), ft_putstr_fd("exit: too many arguments\n", 2));
	else
	{
		if (tmp[1][i] == '-' || tmp[1][i] == '+')
			i++;
		while (tmp[1][i])
		{
			if (!ft_isdigit(tmp[1][i]))
			{
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd(tmp[1], 2);
				ft_putstr_fd(" : numeric argument required\n", 2);
				freed(tmp);
				exit(2);
			}
			i++;
		}
		i = ft_atoi(tmp[1]);
		freed(tmp);
		exit(i);
	}
}

int	main(int ac, char **av, char **env)
{
	char *c;
	char **tmp;
	ac++;
	av++;
	env++;
	while (1)
	{
		c = readline("myshell:%>");
		add_history(c);
	tmp = ft_split(c, ' ');
		if (!ft_strcmp("exit", tmp[0]))
			(free(c), exitcommand(tmp));
	}
}