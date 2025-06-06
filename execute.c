#include "minishell.h"

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

void	openredirs(t_redirections *reds)
{
	int	file[2];

	file[0] = -1;
	file[1] = -1;
	while (reds)
	{
		if (reds->redtype == RED_OUT_APPEND)
		{
			file[1] = open(reds->file, O_CREAT | O_APPEND | O_WRONLY, 0777);
			if (file[1] < 0)
				(perror("open"), exit(1));
			dup2(file[1], 1);
		}
		else if (reds->redtype == RED_OUT_TRUNC)
		{
			file[1] = open(reds->file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
			if (file[1] < 0)
				(perror("open"), exit(1));
			dup2(file[1], 1);
		}
		else if (reds->redtype == RED_IN)
		{
			file[0] = open(reds->file, O_RDONLY);
			if (file[0] < 0)
				(perror("open"), exit(1));
			dup2(file[0], 0);
		}
		cleanfds(file, 2);
		reds = reds->next;
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

void	birth(int i, t_exec exec, t_line *line, t_env **env)
{
	char	*cmd;

	cmd = NULL;
	piping(i, exec, line);
	openredirs(line->reds);
	if (!line->command || !line->command[0])
		exit(0);
	if (isbuiltin(line->command[0]))
		exit(execbuiltin(line, env));
	if (!ft_strncmp(line->command[0], "echo", 5))
		exit(ft_echo(line->command));
	cmd = getcmd(line->command[0], *env);
	if (!cmd)
		exit(127);
	execve(cmd, line->command, convertenv(*env));
	mymalloc(0, 1);
	mymalloc(0, 3);
	perror("execv");
	exit(127);
}

int	initexecstruct(t_exec *exec, t_line *line)
{
	exec->npipes = ft_lstsizeline(line);
	exec->child = mymalloc(sizeof(int) * exec->npipes, 0);
	exec->oldpipefd[0] = -1;
	exec->oldpipefd[1] = -1;
	return (0);
}

int	entersubprocess(t_exec exec, t_line *line, t_env **env, int i)
{
	int	ret;

	ret = fork();
	if (ret < 0)
		return (perror("fork"), cleanfds(exec.pipefd, 2),
			cleanfds(exec.oldpipefd, 2), -1);
	if (!ret)
		birth(i, exec, line, env);
	return (ret);
}

int	ft_execute(t_line *line, t_env **env)
{
	t_exec	exec;

	int(exit), (j), (i) = 0;
	exit = initexecstruct(&exec, line);
	while (line)
	{
		if (pipe(exec.pipefd) < 0)
			perror("pipe");
		if (line->command && isbuiltin(line->command[0]) && !line->next && !i)
			return (cleanfds(exec.pipefd, 2), openredirsnodup(line->reds),
				execbuiltin(line, env));
		else
			exec.child[i] = entersubprocess(exec, line, env, i);
		if (exec.child[i] < 0)
			return (1);
		resetoldpipe(exec.oldpipefd, exec.pipefd);
		i++;
		line = line->next;
	}
	cleanfds(exec.oldpipefd, 2);
	j = 0;
	while (j < i)
		waitpid(exec.child[j++], &exit, 0);
	i = 1;
	while (!access(ft_strjoin("here_doc_history/.tmp", ft_itoa(i, 0), 0), F_OK))
	{
		unlink(ft_strjoin("here_doc_history/.tmp", ft_itoa(i, 0), 0));
		i++;
	}
	return (WEXITSTATUS(exit));
}
