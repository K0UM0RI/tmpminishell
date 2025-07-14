/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:16:38 by sbat              #+#    #+#             */
/*   Updated: 2025/07/14 10:00:49 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	doexecve(t_line *line, t_env **env)
{
	int		exit_status;
	char	*cmd;

	exit_status = -1;
	cmd = NULL;
	cmd = getcmd(line->command[0], *env);
	if (!cmd)
		exit_status = 127;
	else if (is_directory(cmd))
	{
		(write(2, cmd, ft_strlen(cmd)), write(2, ": Is a directory\n", 18));
		exit_status = 126;
	}
	else if (access(cmd, X_OK))
	{
		(write(2, cmd, ft_strlen(cmd)), write(2, ": Permission denied\n", 21));
		exit_status = 126;
	}
	if (exit_status != -1)
		exitandfree(exit_status);
	execve(cmd, line->command, convertenv(*env));
	perror("execv");
	exitandfree(127);
}

void	birth(int i, t_exec exec, t_line *line, t_env **env)
{
	int	exit_status;

	exit_status = -1;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	piping(i, exec, line);
	if (handleredirections(line->reds, 0))
		exitandfree(1);
	if (!line->command || !line->command[0])
		exit_status = 0;
	else if (isbuiltin(line->command[0]))
		exit_status = execbuiltin(line, env);
	else if (!ft_strncmp(line->command[0], "echo", 5))
		exit_status = ft_echo(line->command);
	else if (!ft_strncmp(line->command[0], "env", 5))
		exit_status = ft_env(*env);
	else if (!ft_strncmp(line->command[0], "export", 7))
		exit_status = ft_export(line->command, env);
	else if (!ft_strncmp(line->command[0], "pwd", 4))
		exit_status = ft_pwd(line->command, *env);
	if (exit_status != -1)
		exitandfree(exit_status);
	doexecve(line, env);
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

int	hastobeparent(t_line *line, int i, t_env **env, t_exec exec)
{
	int	exit;
	int	j;

	if (!env)
		return (line->command && (isbuiltin(line->command[0])
				|| (!ft_strncmp(line->command[0], "export", 7)
					&& line->command[1])) && !line->next && !i);
	cleanfds(exec.pipefd, 2);
	if (handleredirections(line->reds, 1))
		return (1);
	exit = execbuiltin(line, env);
	sigaction(SIGINT, &exec.old, NULL);
	j = 1;
	while (!access(ft_strjoin("/tmp/.tmp", ft_itoa(j, 0), 0), F_OK))
		unlink(ft_strjoin("/tmp/.tmp", ft_itoa(j++, 0), 0));
	return (exit);
}

int	ft_execute(t_line *line, t_env **env)
{
	t_exec				exec;
	int					i;

	exec.old = ignoreparentsigint();
	i = 0;
	initexecstruct(&exec, line);
	cmdnum();
	*cmdnum() = exec.npipes;
	while (line)
	{
		if (pipe(exec.pipefd) < 0)
			perror("pipe");
		if (hastobeparent(line, i, NULL, exec))
			return (hastobeparent(line, i, env, exec));
		else
			exec.child[i] = entersubprocess(exec, line, env, i);
		if (exec.child[i] < 0)
			return (1);
		resetoldpipe(exec.oldpipefd, exec.pipefd);
		i++;
		line = line->next;
	}
	cleanfds(exec.oldpipefd, 2);
	return (finishexec(exec, i, exec.old));
}
