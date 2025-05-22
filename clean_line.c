/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:47 by sbat              #+#    #+#             */
/*   Updated: 2025/05/17 10:50:29 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handlequotes(t_lexvars *vars, const char *c, t_env *env)
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
			(vars->ret)->c = ft_append((vars->ret)->c, c[(vars->i)++], 0);
		if (c[(vars->i)++] != '\'')
			return (printf("error: no quote\n"), 1);
	}
	return (0);
}

int	handleoperators(int *i, int *s, t_string **ret, const char *c)
{
	char	tmp;

	if (*i && (*ret)->c)
		nexts_string(ret);
	(*ret)->type = OPERATOR;
	tmp = c[*i];
	(*ret)->c = ft_append((*ret)->c, c[(*i)++], 0);
	if (tmp == c[*i] && tmp == '|')
		return (printf("syntax error\n"), 1);
	else if (tmp == c[*i] && tmp == '&')
		return (printf("syntax error\n"), 1);
	else if (tmp == c[*i] && c[*i] == '<')
	{
		*s = 1;
		return (doheredoc(i, ret, c));
	}
	else if (tmp == c[*i])
		(*ret)->c = ft_append((*ret)->c, c[(*i)++], 0);
	if (isoperator(c[*i]))
		return (printf("syntax error\n"), 1);
	*s = 1;
	return (0);
}

void	founddollar(t_lexvars *vars, const char *c, t_env *env)
{
	char	*tmp;
	int		j;

	if (vars->s && (vars->ret)->c)
		nexts_string(&vars->ret);
	tmp = foundvar(&(vars->i), c, env);
	if (tmp == (char *)-1)
	{
		vars->ret->c = ft_append(vars->ret->c, '$', 0);
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

int	filllist(t_lexvars *vars, const char *c, t_env *env)
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
		(vars->ret)->c = ft_append((vars->ret)->c, c[(vars->i)++], 0);
	}
	while (mywhitespace(c[(vars->i)]))
	{
		(vars->i)++;
		vars->s = 1;
	}
	return (d);
}

t_string	*clean_line(const char *c, t_env *env)
{
	t_string	*head;
	t_lexvars	vars;

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
	return (head);
}
