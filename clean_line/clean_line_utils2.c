/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:16:03 by sbat              #+#    #+#             */
/*   Updated: 2025/07/20 11:02:22 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean_line.h"

int	mywhitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v'
		|| c == '\f');
}

t_string	*news_string(void)
{
	t_string	*c;

	c = (t_string *)mymalloc(sizeof(t_string), MALLOC_TMP);
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

int	is_redirection(const t_string *node)
{
	return (node && node->type == OPERATOR && (!ft_strncmp(node->c, ">", 1)
			|| !ft_strncmp(node->c, "<", 1)));
}

char	*getvarname(const char *c, int *i)
{
	char	*var;

	var = NULL;
	if (!ft_isalpha(c[*i]) && c[*i] != '_')
	{
		if (c[*i] == '?' || ft_isnum(c[*i]))
		{
			(*i)++;
			if (ft_isnum(c[(*i) - 1]))
				return (NULL);
			return (ft_strdup("?", MALLOC_TMP));
		}
		if ((c[*i] != '"' && c[*i] != '\'') || c[*i] == '$')
			return ((char *)-1);
		return ((char *)-2);
	}
	while (c[*i] && (ft_isalpha(c[(*i)]) || ft_isnum(c[(*i)])
			|| c[(*i)] == '_'))
	{
		var = ft_append(var, c[(*i)], MALLOC_TMP);
		(*i)++;
	}
	return (var);
}
