#include "builtins.h"

int	isbuiltin(char *command)
{
	if (!command)
		return (-1);
	if (!ft_strncmp(command, "cd", 3) || !ft_strncmp(command, "pwd", 4) || !ft_strncmp(command, "unset", 6) || !ft_strncmp(command, "exit", 5))
		return (1);
	return (0);
}

int	isnumber(char *c)
{
	int	i;

	i = 0;
	if (!c || !*c)
		return (write(2, "numeric argument required\n", 27), 0);
	if (c[i] && (c[i] == '-' || c[i] == '+'))
		i++;
	while (c[i] && (c[i] >= '0' && c[i] <= '9'))
		i++;
	if (c[i])
		return (write(2, "numeric argument required\n", 27), 0);
	return (1);
}

void	openredirsnodup(t_redirections *reds)
{
	int	file[2];

	file[0] = -1;
	file[1] = -1;
	while (reds)
	{
		if (reds->redtype == RED_OUT_APPEND)
			file[1] = open(reds->file, O_CREAT | O_APPEND | O_WRONLY, 0777);
		else if (reds->redtype == RED_OUT_TRUNC)
			file[1] = open(reds->file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		else if (reds->redtype == RED_IN)
		{
			file[0] = open(reds->file, O_RDONLY);
			if (file[0] < 0)
				(perror("open"), exit(1));
		}
		cleanfds(file, 2);
		reds = reds->next;
	}
}