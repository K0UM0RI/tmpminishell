/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:47 by sbat              #+#    #+#             */
/*   Updated: 2025/05/16 20:41:36 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handlequotes(t_lexvars *vars, char *c, t_env *env)
{
	if (vars->s && (vars->ret)->c)
		nexts_string(&vars->ret);
	vars->s = 0;
	if (c[vars->i] == '"')
	{
		(vars->i)++;
		vars->s = foundquote(c, &vars->i, &vars->ret, env);
		if (vars->s == -1)
			return (printf("error:no double quote\n"), 1);
	}
	else if (c[vars->i] == '\'')
	{
		(vars->i)++;
		while (c[vars->i] && c[vars->i] != '\'')
			(vars->ret)->c = ft_append((vars->ret)->c, c[(vars->i)++]);
		if (c[(vars->i)++] != '\'')
			return (printf("error: no quote\n"), 1);
	}
	return (0);
}

int doheredoc(int *i, t_string **ret, char *c)
{
	char *eof;
	static int order;
	char *file;
	int fd;
	char *gnl;
	char quote;

	order++;
	file = ft_strjoin(".tmp", ft_itoa(order));
	(*i)++;
	while (c[*i] && mywhitespace(c[*i]))
		(*i)++;
	if (isoperator(c[*i]))
		return (printf("parsing error near <\n"), 1);
	while (c[*i] && !isoperator(c[*i]) && !mywhitespace(c[*i]))
	{
		if (c[*i] == '"' || c[*i] == '\'')
		{
			quote = c[*i];
			(*i)++;
			while (c[*i] && c[*i] != '"' && c[*i] != '\'')
				eof = ft_append(eof, c[(*i)++]);
			if (c[(*i)++] != quote)
				return (printf("no matchine quote\n"), 1);
		}
		else
			eof = ft_append(eof, c[(*i)++]);
	}
	if (!eof)
		return (printf("parsing error near < 1\n"), 1);
	fd = open(file, O_CREAT | O_WRONLY, 0777);
	write (1, ">", 1);
	gnl = get_next_line(0, eof);
	while (gnl)
	{
		write (1, ">", 1);
		write(fd, gnl, ft_strlen(gnl));
		free(gnl);
		gnl = get_next_line(0, eof);
	}
	close(fd);
	nexts_string(ret);
	(*ret)->c = ft_strjoin((*ret)->c, file);
	(*i)++;
	return 0;
}

int	handleoperators(int *i, int *s, t_string **ret, char *c)
{
	char	tmp;

	if (*i && (*ret)->c)
		nexts_string(ret);
	(*ret)->type = OPERATOR;
	tmp = c[*i];
	(*ret)->c = ft_append((*ret)->c, c[(*i)++]);
	if (tmp == c[*i] && tmp == '|')
		return (printf("parsing error near %c\n", tmp), 1);
	else if (tmp == c[*i] && c[*i] == '<')
	{
		*s = 1;
		return (doheredoc(i, ret, c));
	}
	else if (tmp == c[*i])
		(*ret)->c = ft_append((*ret)->c, c[(*i)++]);
	if (isoperator(c[*i]))
		return (printf("parsing error near %c\n", tmp), 1);
	*s = 1;
	return (0);
}

void founddollar(t_lexvars *vars, char *c, t_env *env)
{
	char *tmp;
	int j;

	if (vars->s && (vars->ret)->c)
		nexts_string(&vars->ret);
	tmp = foundvar(&(vars->i), c, env);
	if (tmp == (char *)-1)
	{
		vars->ret->c = ft_append(vars->ret->c, '$');
		tmp = NULL;
	}
	else if (tmp == (char *)-2)
		tmp = NULL;
	vars->s = 0;
	j = vars->i;
	vars->i = 0;
	vars->d = 1;
	while (tmp && tmp[vars->i])
		filllist(vars, tmp, env);
	vars->d = 0;
	vars->i = j;
}

int	filllist(t_lexvars *vars, char *c, t_env *env)
{
	int	d;
	d = 0;
	if ((c[vars->i] == '"' || c[vars->i] == '\'') && !vars->d)
		d = handlequotes(vars, c, env);
	else if (isoperator(c[vars->i]) && !vars->d)
		d = handleoperators(&vars->i, &vars->s, &vars->ret, c);
	else if (c[vars->i] == '$' && !vars->d)
		founddollar(vars, c, env);
	else if (!mywhitespace(c[vars->i]))
	{
		if (vars->s && (vars->ret)->c)
			nexts_string(&vars->ret);
		vars->s = 0;
		(vars->ret)->c = ft_append((vars->ret)->c, c[(vars->i)++]);
	}
	while (mywhitespace(c[(vars->i)]))
	{
		(vars->i)++;
		vars->s = 1;
	}
	return (d);
}

t_string	*clean_line(char *c, t_env *env)
{
	t_string	*head;
	t_lexvars vars;

	
	vars.s = 0;
	vars.i = 0;
	vars.d = 0;
	vars.ret = news_string();
	head = vars.ret;
	if (mywhitespace(c[vars.i]))
		vars.i++;
	while (c[vars.i])
	{
		if (filllist(&vars, c, env))
			return (NULL);
	}
	if (mywhitespace(c[vars.i]))
		vars.i++;
	return (head);
}
