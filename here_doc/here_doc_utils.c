/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:14:26 by sbat              #+#    #+#             */
/*   Updated: 2025/07/20 10:56:26 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

t_here_doc	initfile(void)
{
	static int	order = 0;
	t_here_doc	hdoc;

	if (access(ft_strjoin("/tmp/.tmp", "1", MALLOC_TMP), F_OK))
		order = 0;
	order++;
	hdoc.file = ft_strjoin("/tmp/.tmp", ft_itoa(order, MALLOC_TMP), MALLOC_TMP);
	hdoc.fd = open(hdoc.file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (hdoc.fd < 0)
		perror("here_doc open");
	return (hdoc);
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
