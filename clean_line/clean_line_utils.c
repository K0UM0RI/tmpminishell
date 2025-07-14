/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:50 by sbat              #+#    #+#             */
/*   Updated: 2025/07/14 08:39:52 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean_line.h"

char	*foundvar(int *i, const char *c, t_env *env)
{
	char	*var;

	(*i)++;
	var = getvarname(c, i);
	if (var == (char *)-1)
		return ((char *)-1);
	else if (var == (char *)-2)
		return ((char *)-2);
	if (var && !ft_strncmp(var, "1PWD", 5))
		return (NULL);
	var = getmyenv(var, env);
	if (!var)
		return (NULL);
	return (var);
}

int	foundquote(const char *c, int *i, t_string **ret, t_env *env)
{
	char	*tmp;

	while (c[*i] && c[*i] != '"')
	{
		if (c[*i] == '$')
		{
			tmp = foundvar(i, c, env);
			if (tmp == (char *)-2 || tmp == (char *)-1)
			{
				(*ret)->c = ft_append((*ret)->c, '$', 0);
				tmp = NULL;
			}
			while (tmp && *tmp)
			{
				(*ret)->c = ft_append((*ret)->c, *tmp, 0);
				tmp++;
			}
		}
		else
			(*ret)->c = ft_append((*ret)->c, c[(*i)++], 0);
	}
	if (c[(*i)] != '"')
		return (-1);
	return (0);
}

int	handlequotes(t_lexvars *vars, const char *c, t_env *env)
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
		(vars->i)++;
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

int	checkopsorder(int *r, int *p, t_string *clean)
{
	if ((*r || *p) && !ft_strncmp(clean->c, "|", 1) && clean->type == OPERATOR)
		return (write(2, "syntax error\n", 14), 1);
	else if (clean->type == OPERATOR && ft_strncmp(clean->c, "|", 1))
	{
		*r = 1;
		*p = 0;
	}
	else if (!ft_strncmp(clean->c, "|", 1) && clean->type == OPERATOR)
	{
		*p = 1;
	}
	else
	{
		*p = 0;
		*r = 0;
	}
	return (0);
}

int	handlerrors(t_string *clean)
{
	int			p;
	int			r;
	t_string	*prev;

	p = 0;
	r = 0;
	prev = NULL;
	if (!clean)
		return (1);
	if (!ft_strncmp(clean->c, "|", 1) && clean->type == OPERATOR)
		return (write(2, "syntax error\n", 14), 1);
	while (clean)
	{
		if (is_redirection(prev) && is_redirection(clean))
			return (write(2, "syntax error\n", 14), 1);
		if (checkopsorder(&r, &p, clean))
			return (1);
		prev = clean;
		clean = clean->next;
	}
	if (p || r)
		return (write(2, "syntax error\n", 14), 1);
	return (0);
}
