/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breakdown.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:15:41 by sbat              #+#    #+#             */
/*   Updated: 2025/06/10 12:15:42 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "breakdown.h"

char	**gridjoin(char **command, char *elem, int i)
{
	char	**ret;
	int		j;

	j = 0;
	ret = mymalloc(sizeof(char *) * (i + 1), 0);
	if (!command)
	{
		*ret = elem;
		ret[1] = NULL;
		return (ret);
	}
	while (command[j])
	{
		ret[j] = command[j];
		j++;
	}
	ret[j] = elem;
	j++;
	ret[j] = NULL;
	return (ret);
}

int	linenew(t_line **line)
{
	t_line	*tmp;

	if (!line)
		return (1);
	tmp = mymalloc(sizeof(t_line), 0);
	tmp->command = NULL;
	tmp->reds = NULL;
	tmp->next = NULL;
	if (!*line)
		*line = tmp;
	else
	{
		(*line)->next = tmp;
		*line = (*line)->next;
	}
	return (1);
}

int	doops(t_string **elems, t_line **line)
{
	char	*tmp;

	tmp = (*elems)->c;
	(*elems) = (*elems)->next;
	if (!ft_strncmp(tmp, ">", 2))
		red_addback(&(*line)->reds, red_new(ft_strdup((*elems)->c, 0),
				RED_OUT_TRUNC));
	if (!ft_strncmp(tmp, ">>", 3))
		red_addback(&(*line)->reds, red_new(ft_strdup((*elems)->c, 0),
				RED_OUT_APPEND));
	if (!ft_strncmp(tmp, "<", 2))
		red_addback(&(*line)->reds, red_new(ft_strdup((*elems)->c, 0), RED_IN));
	if (!ft_strncmp(tmp, "|", 2))
		return (linenew(line));
	if (ft_strncmp(tmp, "|", 2))
		(*elems) = (*elems)->next;
	return (0);
}

t_line	*breakdown(t_string *elems)
{
	t_line	*line;
	t_line	*head;
	int		i;

	line = NULL;
	i = linenew(&line);
	head = line;
	while (elems)
	{
		if (elems->type == OPERATOR)
		{
			if (doops(&elems, &line))
				i = 1;
		}
		else
		{
			line->command = gridjoin(line->command, ft_strdup(elems->c, 0), i);
			elems = elems->next;
			i++;
		}
	}
	return (head);
}
