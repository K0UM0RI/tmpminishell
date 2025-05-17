/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:11:30 by sbat              #+#    #+#             */
/*   Updated: 2025/05/17 10:29:41 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getendoffile(char *c, int *i)
{
	char	*eof;
	char	quote;

	eof = NULL;
	quote = 0;
	if (isoperator(c[*i]))
		return (printf("parsing error near <\n"), NULL);
	while (c[*i] && !isoperator(c[*i]) && !mywhitespace(c[*i]))
	{
		if (c[*i] == '"' || c[*i] == '\'')
		{
			quote = c[(*i)++];
			while (c[*i] && c[*i] != '"' && c[*i] != '\'')
				eof = ft_append(eof, c[(*i)++]);
			if (c[(*i)++] != quote)
				return (printf("no matchine quote\n"), NULL);
		}
		else
			eof = ft_append(eof, c[(*i)++]);
	}
	if (!eof && quote)
		eof = (char *)-1;
	if (!eof)
		return (printf("parsing error near < 1\n"), NULL);
	return (eof);
}

char	*makeheredoc(char *eof)
{
	static int	order;
	char		*file;
	int			fd;
	char		*line;

	order++;
	file = ft_strjoin(".tmp", ft_itoa(order));
	fd = open(file, O_CREAT | O_WRONLY, 0777);
	line = readline(">");
	eof = ft_append(eof, '\n');
	while (ft_strncmp(line, eof, ft_strlen(line)))
	{
		line = ft_append(line, '\n');
		write(fd, line, ft_strlen(line));
		line = readline(">");
	}
	close(fd);
	return (file);
}

int	doheredoc(int *i, t_string **ret, char *c)
{
	char    *eof;

	(*i)++;
	while (c[*i] && mywhitespace(c[*i]))
		(*i)++;
	eof = getendoffile(c, i);
	if (!eof)
		return (1);
	if (eof == (char *)-1)
		eof = ft_strdup("");
	nexts_string(ret);
	(*ret)->c = ft_strjoin((*ret)->c, makeheredoc(eof));
	(*i)++;
	return (0);
}
