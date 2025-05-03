/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:50 by sbat              #+#    #+#             */
/*   Updated: 2025/05/03 16:58:24 by sbat             ###   ########.fr       */
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
	(*ret)->append = 1;
}

char	*getvarname(char *c, int *i)
{
	char	*var;

	var = NULL;
	while (c[*i] && !mywhitespace(c[(*i)]) && c[(*i)] != '"'
		&& !isoperator(c[*i]) && c[(*i)] != '\'' && c[(*i)] != '$')
	{
		var = ft_append(var, c[(*i)]);
		(*i)++;
	}
	return (var);
}

int	foundvar(int *i, char *c, char **ret, char **env)
{
	char	*var;

	(*i)++;
	var = getvarname(c, i);
	if (!var)
		*ret = ft_append(*ret, '$');
	var = getmyenv(var, env);
	if (!var)
		return 0;
	else
		*ret = ft_strjoin(*ret, var);
	return (0);
}

int	foundquote(char *c, int *i, t_string **ret, char **env)
{
	while (c[*i] && c[*i] != '"')
	{
		if (c[*i] == '$')
			foundvar(i, c, &(*ret)->c, env);
		else
		{
			(*ret)->c = ft_append((*ret)->c, c[*i]);
			(*i)++;
		}
	}
	if (c[(*i)++] != '"')
		return (-1);
	return 0;
}
