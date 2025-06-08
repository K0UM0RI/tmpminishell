#include "execute.h"

void	cleanfds(int *fd, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (fd[i] != -1)
			close(fd[i]);
		fd[i] = -1;
		i++;
	}
}

void	piping(int i, t_exec exec, t_line *line)
{
	close(exec.pipefd[0]);
	if (i)
	{
		dup2(exec.oldpipefd[0], 0);
		cleanfds(exec.oldpipefd, 2);
	}
	if (line->next)
	{
		dup2(exec.pipefd[1], 1);
		close(exec.pipefd[1]);
	}
}

void	resetoldpipe(int *oldpipefd, int *pipefd)
{
	cleanfds(oldpipefd, 2);
	oldpipefd[0] = pipefd[0];
	oldpipefd[1] = pipefd[1];
}

int	ft_lstsizeline(t_line *line)
{
	int	size;

	size = 0;
	while (line)
	{
		size++;
		line = line->next;
	}
	return (size);
}