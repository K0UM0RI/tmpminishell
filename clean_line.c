/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:47 by sbat              #+#    #+#             */
/*   Updated: 2025/05/14 10:01:37 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handlequotes(int *i, int *s, t_string **ret, char *c, char **env)
{
	if (*s && (*ret)->c)
		nexts_string(ret);
	*s = 0;
	if (c[*i] == '"')
	{
		(*i)++;
		*s = foundquote(c, i, ret, env);
		if (*s == -1)
			return (printf("error:no double quote\n"), 1);
	}
	else if (c[*i] == '\'')
	{
		(*i)++;
		while (c[*i] && c[*i] != '\'')
			(*ret)->c = ft_append((*ret)->c, c[(*i)++]);
		if (c[(*i)++] != '\'')
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



static int	filllist(int *i, int *s, t_string **ret, char *c, char **env)
{
	int	d;
	char *tmp;
	int j;
	d = 0;
	if (c[*i] == '"' || c[*i] == '\'')
		d = handlequotes(i, s, ret, c, env);
	else if (isoperator(c[*i]))
		d = handleoperators(i, s, ret, c);
	else if (c[*i] == '$')
	{
		if (*s && (*ret)->c)
			nexts_string(ret);
		tmp = foundvar(i, c, &((*ret)->c), env);
		*s = 0;
		j = 0;
		if (!tmp)
			return d;
		while (tmp[j])
			filllist(&j, s, ret, tmp, env);
	}
	else if (!mywhitespace(c[*i]))
	{
		if (*s && (*ret)->c)
			nexts_string(ret);
		*s = 0;
		(*ret)->c = ft_append((*ret)->c, c[(*i)++]);
	}
	while (mywhitespace(c[(*i)]))
	{
		(*ret)->append = 0;
		(*i)++;
		*s = 1;
	}
	return (d);
}

t_string	*clean_line(char *c, char **env)
{
	int			i;
	t_string	*ret;
	t_string	*head;
	int			s;

	s = 0;
	i = 0;
	ret = news_string();
	head = ret;
	if (mywhitespace(c[i]))
		i++;
	while (c[i])
	{
		if (filllist(&i, &s, &ret, c, env))
			return (NULL);
	}
	if (mywhitespace(c[i]))
		i++;
	ret->append = 0;
	return (head);
}
