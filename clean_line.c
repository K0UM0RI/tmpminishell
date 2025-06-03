/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:47 by sbat              #+#    #+#             */
/*   Updated: 2025/06/03 17:58:21 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handlequotes(t_lexvars *vars, const char *c, t_env *env)
{
	if (vars->s && (vars->ret)->c)
		nexts_string(&vars->ret);
	(vars->ret)->c = ft_append((vars->ret)->c, '\0', 0);
	vars->s = 0;
	if (c[vars->i] == '"')
	{
		(vars->i)++;
		vars->s = foundquote(c, &vars->i, &vars->ret, env);
		if (vars->s == -1)
			return (write(2, "error:no double quote\n", 23), 1);
	}
	else if (c[vars->i] == '\'')
	{
		(vars->i)++;
		while (c[vars->i] && c[vars->i] != '\'')
			(vars->ret)->c = ft_append((vars->ret)->c, c[(vars->i)++], 0);
		if (c[(vars->i)++] != '\'')
			return (write(2, "error: no quote\n", 17), 1);
	}
	return (0);
}

int	handleoperators(t_lexvars *vars, const char *c, t_env *env)
{
	char	tmp;

	if (vars->i && vars->ret->c)
		nexts_string(&vars->ret);
	vars->ret->type = OPERATOR;
	tmp = c[vars->i];
	vars->ret->c = ft_append(vars->ret->c, c[vars->i++], 0);
	if (tmp == c[vars->i] && tmp == '|')
		return (write(2, "syntax error\n", 14), 1);
	else if (tmp == c[vars->i] && tmp == '&')
		return (write(2, "syntax error\n", 14), 1);
	else if (tmp == c[vars->i] && c[vars->i] == '<')
	{
		vars->s = 1;
		return (doheredoc(&vars->i, &vars->ret, c, env));
	}
	else if (tmp == '>')
	{
		if (c[vars->i] == '|' && c[vars->i + 1] && !isoperator(c[vars->i + 1]))
		{
			vars->i++;
			return (0);
		}
		else if (tmp == c[vars->i])
			vars->ret->c = ft_append(vars->ret->c, c[vars->i++], 0);
	}
	if (isoperator(c[vars->i]))
		return (write(2, "syntax error\n", 14), 1);
	vars->s = 1;
	return (0);
}

void	founddollar(t_lexvars *vars, const char *c, t_env *env)
{
	char	*tmp;
	int		j;
	
	if (vars->s && (vars->ret)->c)
		nexts_string(&vars->ret);
	if (c[vars->i] == '~' && (mywhitespace(c[vars->i + 1]) || !c[vars->i + 1] || c[vars->i + 1] == '/') && (vars->s || !vars->i))
	{
		vars->s = 0;
		j = vars->i;
		vars->i = 0;
		founddollar(vars, "$HOME", env);
		vars->i = j + 1;
		return ;
	}
	else if (c[vars->i] == '~')
	{
		vars->ret->c = ft_append(vars->ret->c, '~', 0);
		vars->i++;
		return;
	}
	tmp = foundvar(&(vars->i), c, env);
	if (tmp == (char *)-1)
	{
		vars->ret->c = ft_append(vars->ret->c, '$', 0);
		tmp = NULL;
	}
	else if (tmp == (char *)-2)
		tmp = NULL;
	j = vars->i;
	vars->i = 0;
	vars->d = 1;
	vars->s = 0;
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
	else if (isoperator(c[vars->i]) && !vars->d )
		d = handleoperators(vars, c, env);
	else if ((c[vars->i] == '$' || c[vars->i] == '~') && !vars->d)
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
