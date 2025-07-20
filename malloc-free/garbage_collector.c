/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:35 by sbat              #+#    #+#             */
/*   Updated: 2025/07/20 10:53:52 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	mallocfail(t_truck **allocatedtmp, t_truck **allocatedlasting)
{
	write(2, "malloc failed!\n", 15);
	free_lst(allocatedtmp);
	free_lst(allocatedlasting);
	exit(1);
}

void	*mymalloc(size_t size, int fn)
{
	static t_truck	*allocatedtmp = NULL;
	static t_truck	*allocatedlasting = NULL;
	t_truck			*new;

	if (fn == FREE_TMP)
		return (free_lst(&allocatedtmp), NULL);
	if (fn == FREE_LASTING)
		return (free_lst(&allocatedlasting), NULL);
	new = malloc(sizeof(t_truck));
	if (!new)
		mallocfail(&allocatedtmp, &allocatedlasting);
	new->ptr = malloc(size);
	if (!new)
		(free(new), mallocfail(&allocatedtmp, &allocatedlasting));
	if (fn == MALLOC_TMP)
	{
		new->next = allocatedtmp;
		allocatedtmp = new;
	}
	if (fn == MALLOC_LASTING)
	{
		new->next = allocatedlasting;
		allocatedlasting = new;
	}
	return (new->ptr);
}
