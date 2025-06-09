/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:11:30 by sbat              #+#    #+#             */
/*   Updated: 2025/06/09 12:05:06 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

char	*getendoffile(const char *c, int *i)
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
				eof = ft_append(eof, c[(*i)++], 0);
			if (c[(*i)++] != quote)
				return (printf("no matchine quote\n"), NULL);
		}
		else
			eof = ft_append(eof, c[(*i)++], 0);
	}
	if (!eof && quote)
		eof = (char *)-1;
	if (!eof)
		return (printf("parsing error near < 1\n"), NULL);
	return (eof);
}

void redirectcontent(char *eof, t_env *env, int fd)
{
	char *tmp;
	char *line;
	int i;

	i = 0;
	line = NULL;
	line = readline(">");
	eof = ft_append(eof, '\n', 0);
	line = ft_append(line, '\n', 0);
	while (line && ft_strncmp(line, eof, ft_strlen(line) + 1))
	{
		i = 0;
		while (line && line[i])
		{
			if (line[i] == '$')
			{
				tmp = here_docexpand(&i, line, env);
				if (tmp)
					write(fd, tmp, ft_strlen(tmp));
			}
			else
				write(fd, &line[i++], 1);
		}
		line = readline(">");
		line = ft_append(line, '\n', 0);
	}
}

char	*makeheredoc(char *eof, t_env *env)
{
	static int	order;
	char		*file;
	int			fd;

	if (access(ft_strjoin("here_doc_history/.tmp", ft_itoa(1, 0), 0), F_OK))
		order = 0;
	order++;
	file = ft_strjoin("here_doc_history/.tmp", ft_itoa(order, 0), 0);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (!eof)
		return (file);
	redirectcontent(eof, env, fd);
	close(fd);
	return (file);
}

int	doheredoc(int *i, t_string **ret, const char *c, t_env *env)
{
	char	*eof;

	(*i)++;
	while (c[*i] && mywhitespace(c[*i]))
		(*i)++;
	eof = getendoffile(c, i);
	if (!eof)
		return (1);
	if (eof == (char *)-1)
		eof = ft_strdup("\0", 0);
	nexts_string(ret);
	(*ret)->c = ft_strjoin((*ret)->c, makeheredoc(eof, env), 0);
	(*i)++;
	return (0);
}
