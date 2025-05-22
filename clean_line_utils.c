/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:50 by sbat              #+#    #+#             */
/*   Updated: 2025/05/17 10:49:35 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_string	*news_string(void)
{
	t_string	*c;

	c = (t_string *)mymalloc(sizeof(t_string), 0);
	c->c = NULL;
	c->next = NULL;
	c->type = 0;
	return (c);
}

void	nexts_string(t_string **ret)
{
	(*ret)->next = news_string();
	(*ret) = (*ret)->next;
	(*ret)->type = 0;
}

char	*getvarname(const char *c, int *i)
{
	char	*var;

	var = NULL;
	while (c[*i] && !mywhitespace(c[(*i)]) && c[(*i)] != '"'
		&& !isoperator(c[*i]) && c[(*i)] != '\'' && c[(*i)] != '$')
	{
		var = ft_append(var, c[(*i)], 0);
		(*i)++;
	}
	if ((mywhitespace(c[*i]) || !c[*i]) && !var)
		return ((char *)-1);
	else if (!var && c[*i] == '"')
		return ((char *)-2);
	return (var);
}

char	*foundvar(int *i, const char *c, t_env *env)
{
	char	*var;

	(*i)++;
	var = getvarname(c, i);
	if (var == (char *)-1)
		return ((char *)-1);
	else if (var == (char *)-2)
		return ((char *)-2);
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
	if (c[(*i)++] != '"')
		return (-1);
	return (0);
}
