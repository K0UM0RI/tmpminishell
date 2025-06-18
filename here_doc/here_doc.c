/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:11:30 by sbat              #+#    #+#             */
/*   Updated: 2025/06/18 01:18:32 by sbat             ###   ########.fr       */
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
	return (write(2, "parsing error\n", 15), NULL);
	while (c[*i] && !isoperator(c[*i]) && !mywhitespace(c[*i]))
	{
		if (c[*i] == '"' || c[*i] == '\'')
		{
			quote = c[(*i)++];
			while (c[*i] && c[*i] != '"' && c[*i] != '\'')
				eof = ft_append(eof, c[(*i)++], 0);
			if (c[*i] != quote)
				return (write(2, "no matchine quote\n", 19), NULL);
			(*i)++;
		}
		else
			eof = ft_append(eof, c[(*i)++], 0);
	}
	if (!eof && quote)
		eof = (char *)-1;
	if (!eof)
		return (write(2, "parsing error\n", 15), NULL);
	return (eof);
}

void	writeonfile(char *line, t_env *env, int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i])
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
}

void	redirectcontent(char *eof, t_env *env, int fd)
{
	char	*line;

	signal(SIGINT, ft_siginthere_subprocess);
	line = readline(">");
	here_doceof(line, eof, ft_strlen(eof));
	eof = ft_append(eof, '\n', 0);
	line = ft_append(line, '\n', 0);
	while (line && ft_strncmp(line, eof, ft_strlen(line) + 1))
	{
		writeonfile(line, env, fd);
		line = readline(">");
		here_doceof(line, eof, ft_strlen(eof) - 1);
		line = ft_append(line, '\n', 0);
	}
	exitandfree(0);
}

char	*makeheredoc(char *eof, t_env *env)
{
	t_here_doc			hdoc;
	int					child;
	int					exit;
	struct sigaction	old;

	old = ignoreparentsigint();
	child = 0;
	hdoc = initfile();
	if (hdoc.fd < 0)
		return (NULL);
	child = fork();
	if (!child)
		redirectcontent(eof, env, hdoc.fd);
	waitpid(child, &exit, 0);
	sigaction(SIGINT, &old, NULL);
	if (WEXITSTATUS(exit) == 130)
	{
		unlink(hdoc.file);
		hdoc.file = (char *)130;
	}
	close(hdoc.fd);
	return (hdoc.file);
}

int	doheredoc(int *i, t_string **ret, const char *c, t_env *env)
{
	char	*eof;
	char	*file;

	(*i)++;
	while (c[*i] && mywhitespace(c[*i]))
		(*i)++;
	eof = getendoffile(c, i);
	if (!eof)
		return (1);
	if (eof == (char *)-1)
		eof = ft_strdup("\0", 0);
	nexts_string(ret);
	file = makeheredoc(eof, env);
	if (file == (char *)130)
		return (130);
	if (!file)
		return (1);
	(*ret)->c = ft_strjoin((*ret)->c, file, 0);
	return (0);
}
