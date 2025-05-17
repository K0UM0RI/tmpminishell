/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:35 by sbat              #+#    #+#             */
/*   Updated: 2025/05/17 10:52:01 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst(t_truck **allocated)
{
	t_truck	*tmp;

	if (!*allocated)
		return ;
	tmp = *allocated;
	while (tmp)
	{
		free(tmp->ptr);
		tmp = tmp->next;
		free(*allocated);
		*allocated = tmp;
	}
}

void	*mymalloc(size_t size, int fn)
{
	static t_truck	*allocatedtmp = NULL;
	static t_truck	*allocatedlasting = NULL;
	t_truck			*new;

	if (fn == 1)
		return (free_lst(&allocatedtmp), NULL);
	if (fn == 3)
		return (free_lst(&allocatedlasting), NULL);
	new = malloc(sizeof(t_truck));
	if (!new)
	{
		write(2, "malloc failed!\n", 15);
		free_lst(&allocatedtmp);
		free_lst(&allocatedlasting);
		exit(1);
	}
	new->ptr = malloc(size);
	if (!new)
	{
		write(2, "malloc failed!\n", 15);
		free(new);
		free_lst(&allocatedtmp);
		free_lst(&allocatedlasting);
		exit(1);
	}
	if (fn == 0)
	{
		new->next = allocatedtmp;
		allocatedtmp = new;
	}
	if (fn == 2)
	{
		new->next = allocatedlasting;
		allocatedlasting = new;
	}
	return (new->ptr);
}
