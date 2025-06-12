/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:11:30 by sbat              #+#    #+#             */
/*   Updated: 2025/06/12 17:42:04 by sbat             ###   ########.fr       */
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

void ft_SIGINThere_doc(int sig)
{
	(void)sig;
	mymalloc(0, 1);
	mymalloc(0, 3);
	write(1, "\n", 1);
	exit(69);
}

void	redirectcontent(char *eof, t_env *env, int fd)
{
	char	*tmp;
	char	*line;
	int		i;

	i = 0;
	signal(SIGINT, ft_SIGINThere_doc);
	line = NULL;
	line = readline(">");
	if (!line)
    {
        write(2, "\nwarning: here-document delimited by end-of-file (wanted '", 59);
        write(2, eof, ft_strlen(eof)); 
        write(2, "')\n", 4);
        return;
    }
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
		if (!line)
    	{
    	    write(2, "\nwarning: here-document delimited by end-of-file (wanted '", 59);
    	    write(2, eof, ft_strlen(eof) - 1); 
    	    write(2, "')\n", 4);
    	    return;
    	}
		line = ft_append(line, '\n', 0);
	}
}

char	*makeheredoc(char *eof, t_env *env)
{
	static int	order = 0;
	char		*file;
	int			fd;
	int child;
	int exit;

	child = 0;
	if (access(ft_strjoin(".tmp", "1", 0), F_OK))
		order = 0;
	order++;
	file = ft_strjoin(".tmp", ft_itoa(order, 0), 0);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
	{
		perror("here_doc open");
		return (NULL);
	}
	if (!eof)
		return (file);
	child = fork();
	if (!child)
		redirectcontent(eof, env, fd);
	waitpid(child, &exit, 0);
	if(WEXITSTATUS(exit) == 69)
	{
		unlink(file);
		file = NULL;
	}
	close(fd);
	return (file);
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
	if (!file)
		return (130);
	(*ret)->c = ft_strjoin((*ret)->c, file, 0);
	(*i)++;
	return (0);
}
