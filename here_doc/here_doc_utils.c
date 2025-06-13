/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:14:26 by sbat              #+#    #+#             */
/*   Updated: 2025/06/13 22:14:27 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

struct sigaction	ignoreparentsigint(void)
{
	struct sigaction	ignore;
	struct sigaction	old;

	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	sigaction(SIGINT, &ignore, &old);
	return (old);
}

t_here_doc	initfile(void)
{
	static int	order = 0;
	t_here_doc	hdoc;

	if (access(ft_strjoin(".tmp", "1", 0), F_OK))
		order = 0;
	order++;
	hdoc.file = ft_strjoin(".tmp", ft_itoa(order, 0), 0);
	hdoc.fd = open(hdoc.file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (hdoc.fd < 0)
		perror("here_doc open");
	return (hdoc);
}

void	ft_siginthere_doc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exitandfree(130);
}

void	here_doceof(char *line, char *eof, int size)
{
	if (!line)
	{
		write(2, "\nwarning: here-document delimited by end-of-file (wanted '",
			59);
		write(2, eof, size);
		write(2, "')\n", 4);
		exitandfree(0);
	}
}