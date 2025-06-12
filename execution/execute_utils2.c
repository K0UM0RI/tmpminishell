/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:16:34 by sbat              #+#    #+#             */
/*   Updated: 2025/06/12 22:37:42 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	openredirs(t_redirections *reds, int *file)
{
	if (reds->redtype == RED_OUT_APPEND)
	{
		file[1] = open(reds->file, O_CREAT | O_APPEND | O_WRONLY, 0777);
		if (file[1] < 0)
			(perror("open"), exit(1));
	}
	else if (reds->redtype == RED_OUT_TRUNC)
	{
		file[1] = open(reds->file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		if (file[1] < 0)
			(perror("open"), exit(1));
	}
	else if (reds->redtype == RED_IN)
	{
		file[0] = open(reds->file, O_RDONLY);
		if (file[0] < 0)
			(perror("open"), exit(1));
	}
	if (file[0] != -1)
		dup2(file[0], 0);
	if (file[1] != -1)
		dup2(file[1], 1);
}

void	openredirsnodup(t_redirections *reds, int *file)
{
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

int	finishexec(t_exec exec, int i)
{
	int	(j), (exit) = 0;
	j = 0;
	while (j < i)
		waitpid(exec.child[j++], &exit, 0);
	j = 1;
	while (!access(ft_strjoin(".tmp", ft_itoa(j, 0), 0), F_OK))
	{
		unlink(ft_strjoin(".tmp", ft_itoa(j, 0), 0));
		j++;
	}
	return (WEXITSTATUS(exit));
}
