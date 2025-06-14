/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:16:34 by sbat              #+#    #+#             */
/*   Updated: 2025/06/14 05:31:16 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	openredirs(t_redirections *reds, int *file)
{
	if (reds->redtype == RED_OUT_APPEND)
	{
		file[1] = open(reds->file, O_CREAT | O_APPEND | O_WRONLY, 0777);
		if (file[1] < 0)
			return (perror("open"), 1);
	}
	else if (reds->redtype == RED_OUT_TRUNC)
	{
		file[1] = open(reds->file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		if (file[1] < 0)
			return (perror("open"), 1);
	}
	else if (reds->redtype == RED_IN)
	{
		file[0] = open(reds->file, O_RDONLY);
		if (file[0] < 0)
			return (perror("open"), 1);
	}
	if (file[0] != -1)
		dup2(file[0], 0);
	if (file[1] != -1)
		dup2(file[1], 1);
	return (0);
}

int	openredirsnodup(t_redirections *reds, int *file)
{
	if (reds->redtype == RED_OUT_APPEND)
	{
		file[1] = open(reds->file, O_CREAT | O_APPEND | O_WRONLY, 0777);
		if (file[1] < 0)
			return (perror("open"), 1);
	}
	else if (reds->redtype == RED_OUT_TRUNC)
	{
		file[1] = open(reds->file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		if (file[1] < 0)
			return (perror("open"), 1);
	}
	else if (reds->redtype == RED_IN)
	{
		file[0] = open(reds->file, O_RDONLY);
		if (file[0] < 0)
			return (perror("open"), 1);
	}
	cleanfds(file, 2);
	reds = reds->next;
	return (0);
}

int	finishexec(t_exec exec, int i, struct sigaction old)
{
	int(j),(sig), (status), (exit) = 0;
	j = 0;
	status = 0;
	while (j < i)
	{
		waitpid(exec.child[j++], &status, 0);
		if ((status & 0x7f) != 0 && (status & 0x7f) != 0x7f)
        {
            sig = status & 0x7f;
            if (sig == SIGINT || sig == SIGQUIT)
                write(1, "\n", 1);
            exit = 128 + sig;
        }
        else
        {
            exit = (status >> 8) & 0xff;
        }
	}
	sigaction(SIGINT, &old, NULL);
	j = 1;
	while (!access(ft_strjoin(".tmp", ft_itoa(j, 0), 0), F_OK))
	{
		unlink(ft_strjoin(".tmp", ft_itoa(j, 0), 0));
		j++;
	}
	return (exit);
}
