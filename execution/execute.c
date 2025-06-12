/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:16:38 by sbat              #+#    #+#             */
/*   Updated: 2025/06/12 21:49:06 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	handleredirections(t_redirections *reds, int ft)
{
	int	file[2];

	file[0] = -1;
	file[1] = -1;
	while (reds)
	{
		if (!ft)
			openredirs(reds, file);
		else
			openredirsnodup(reds, file);
		cleanfds(file, 2);
		reds = reds->next;
	}
}

void	birth(int i, t_exec exec, t_line *line, t_env **env)
{
	char	*cmd;

	cmd = NULL;
	piping(i, exec, line);
	handleredirections(line->reds, 0);
	if (!line->command || !line->command[0])
		exit(0);
	if (isbuiltin(line->command[0]))
		exit(execbuiltin(line, env));
	if (!ft_strncmp(line->command[0], "echo", 5))
		exit(ft_echo(line->command));
	if (!ft_strncmp(line->command[0], "env", 5))
		exit(ft_env(*env));
	if (!ft_strncmp(line->command[0], "export", 7))
		exit(ft_export(line->command, env));
	if (!ft_strncmp(line->command[0], "pwd", 4))
		exit(ft_pwd(*env));
	cmd = getcmd(line->command[0], *env);
	if (!cmd)
		exit(127);
	if (is_directory(cmd))
		(write(2, cmd, ft_strlen(cmd)), write(2, ": Is a directory\n", 18), exit(126));
	if (access(cmd, X_OK))
		(write(2, cmd, ft_strlen(cmd)), write(2, ": Permission denied\n", 21), exit(126));
	execve(cmd, line->command, convertenv(*env));
	mymalloc(0, 1);
	mymalloc(0, 3);
	perror("execv");
	exit(127);
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
	int i;

	i = 0;
	initexecstruct(&exec, line);
	while (line)
	{
		if (pipe(exec.pipefd) < 0)
			perror("pipe");
		if (line->command && (isbuiltin(line->command[0])
				|| (!ft_strncmp(line->command[0], "export", 7)
					&& line->command[1])) && !line->next && !i)
			return (cleanfds(exec.pipefd, 2), handleredirections(line->reds, 1),
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
	return (finishexec(exec, i));
}
