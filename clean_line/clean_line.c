/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:47 by sbat              #+#    #+#             */
/*   Updated: 2025/06/13 17:02:33 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean_line.h"

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
	else if (tmp == c[vars->i] && c[vars->i] == '<')
	{
		vars->s = 1;
		return (doheredoc(&vars->i, &vars->ret, c, env));
	}
	else if (tmp == '>')
	{
		if (tmp == c[vars->i])
			vars->ret->c = ft_append(vars->ret->c, c[vars->i++], 0);
	}
	if (isoperator(c[vars->i]))
		return (write(2, "syntax error\n", 14), 1);
	vars->s = 1;
	return (0);
}

void	expandhome(t_lexvars *vars, const char *c, t_env *env)
{
	int	j;

	if (c[vars->i] == '~' && (mywhitespace(c[vars->i + 1]) || !c[vars->i + 1]
			|| c[vars->i + 1] == '/') && (vars->s || !vars->i))
	{
		vars->s = 0;
		j = vars->i;
		vars->i = 0;
		foundexpandable(vars, "$HOME", env);
		vars->i = j + 1;
		return ;
	}
	else if (c[vars->i] == '~')
	{
		vars->ret->c = ft_append(vars->ret->c, '~', 0);
		vars->i++;
		return ;
	}
}

void	foundexpandable(t_lexvars *vars, const char *c, t_env *env)
{
	char	*tmp;
	int		j;

	if (vars->s && (vars->ret)->c)
		nexts_string(&vars->ret);
	if (c[vars->i] == '~')
		return (expandhome(vars, c, env));
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
	int	error;

	error = 0;
	if ((c[vars->i] == '"' || c[vars->i] == '\'') && !vars->d)
		error = handlequotes(vars, c, env);
	else if (isoperator(c[vars->i]) && !vars->d)
		error = handleoperators(vars, c, env);
	else if ((c[vars->i] == '$' || c[vars->i] == '~') && !vars->d)
		foundexpandable(vars, c, env);
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
	return (error);
}

t_string	*clean_line(const char *c, t_env *env)
{
	t_string	*head;
	t_lexvars	vars;
	int er;
	
	er = 0;
	vars.s = 0;
	vars.i = 0;
	vars.d = 0;
	vars.ret = news_string();
	head = vars.ret;
	if (mywhitespace(c[vars.i]))
		vars.i++;
	while (c[vars.i])
	{
		er = filllist(&vars, c, env);
		if (er == 130)
			return ((t_string *)130);
		if (er)
			return NULL;
	}
	if (!handlerrors(head))
		return (head);
	else
		return (NULL);
}
