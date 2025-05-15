/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:47 by sbat              #+#    #+#             */
/*   Updated: 2025/05/15 15:36:18 by marvin           ###   ########.fr       */
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

int	handleoperators(int *i, int *s, t_string **ret, char *c)
{
	char	tmp;

	if (*i && (*ret)->c)
	{
		(*ret)->append = 0;
		nexts_string(ret);
	}
	(*ret)->type = OPERATOR;
	(*ret)->append = 0;
	tmp = c[*i];
	if (tmp == c[*i])
		(*ret)->c = ft_append((*ret)->c, c[(*i)++]);
	if (tmp != c[*i] && tmp == '&')
		return ((mymalloc(0, 1), 1));
	if (tmp == c[*i] && tmp == '|')
		return ((mymalloc(0, 1), 1));
	else if (tmp == c[*i])
		(*ret)->c = ft_append((*ret)->c, c[(*i)++]);
	if (isoperator(c[*i]))
		return ((mymalloc(0, 1), 1));
	*s = 1;
	return (0);
}



static int	filllist(t_lexvars *vars, char *c, t_env *env)
{
	int	d;
	char *tmp;
	int j;
	d = 0;
	if ((c[vars->i] == '"' || c[vars->i] == '\'') && !vars->d)
		d = handlequotes(vars, c, env);
	else if (isoperator(c[vars->i]) && !vars->d)
		d = handleoperators(&vars->i, &vars->s, &vars->ret, c);
	else if (c[vars->i] == '$' && !vars->d)
	{
		if (vars->s && (vars->ret)->c)
			nexts_string(&vars->ret);
		tmp = foundvar(&(vars->i), c, &vars->ret->c, env);
		vars->s = 0;
		j = vars->i;
		vars->i = 0;
		vars->d = 1;
		while (tmp && tmp[vars->i])
			filllist(vars, tmp, env);
		vars->d = 0;
		vars->i = j;
	}
	else if (!mywhitespace(c[vars->i]))
	{
		if (vars->s && (vars->ret)->c)
			nexts_string(&vars->ret);
		vars->s = 0;
		(vars->ret)->c = ft_append((vars->ret)->c, c[(vars->i)++]);
	}
	while (mywhitespace(c[(vars->i)]))
	{
		(vars->ret)->append = 0;
		(vars->i)++;
		vars->s = 1;
	}
	return (d);
}

t_string	*clean_line(char *c, t_env *env)
{
	// int			i;
	// t_string	*ret;
	t_string	*head;
	// int			s;
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
	vars.ret->append = 0;
	return (head);
}
