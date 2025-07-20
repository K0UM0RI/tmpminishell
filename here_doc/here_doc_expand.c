/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:16:43 by sbat              #+#    #+#             */
/*   Updated: 2025/07/20 10:55:55 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

char	*here_docvarname(const char *c, int *i)
{
	char	*var;

	var = NULL;
	while (c[*i] && !mywhitespace(c[(*i)]) && c[(*i)] != '"'
		&& !isoperator(c[*i]) && c[(*i)] != '\'' && c[(*i)] != '$')
	{
		var = ft_append(var, c[(*i)], MALLOC_TMP);
		(*i)++;
	}
	return (var);
}

char	*here_docexpand(int *i, const char *c, t_env *env)
{
	char	*var;

	(*i)++;
	var = here_docvarname(c, i);
	if (!var)
		return (ft_strdup("$", MALLOC_TMP));
	var = getmyenv(var, env);
	return (var);
}
