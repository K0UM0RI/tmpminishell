/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:50 by sbat              #+#    #+#             */
/*   Updated: 2025/05/15 15:36:55 by marvin           ###   ########.fr       */
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
	if (mywhitespace(c[*i]) && !var)
		return (var);
	else if (!var)
		return ((char *)69);
	return (var);
}

char *foundvar(int *i, char *c, char **ret, t_env *env)
{
	char	*var;

	(*i)++;
	var = getvarname(c, i);
	if (!var)
	{
		*ret = ft_append(*ret, '$');
		return NULL;
	}
	else if (var == (char *)69)
		return NULL;
	var = getmyenv(var, env);
	if (!var)
		return NULL;
	return (var);
}

int	foundquote(char *c, int *i, t_string **ret, t_env *env)
{
	char *tmp;

	
	while (c[*i] && c[*i] != '"')
	{
		if (c[*i] == '$')
		{
			tmp = foundvar(i, c, &(*ret)->c, env);
			while (tmp && *tmp)
			{
				(*ret)->c = ft_append((*ret)->c, *tmp);
				tmp++;
			}
		}
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
