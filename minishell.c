/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:56 by sbat              #+#    #+#             */
/*   Updated: 2025/05/15 17:49:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char *c;
	t_string *tmp;
	int i = 0;
	ac++;
	av++;
	t_env *lstenv = getenvlst(env);
	while (1)
	{
		c = readline("myshell:%>");
		i = 0;
		if (!c)
			break ;
		tmp = clean_line(c, lstenv);
		while (tmp)
		{
			if (tmp->type == WORD)
			{
				printf("%d:WORD:", i);
			}
			if (tmp->type == OPERATOR)
				printf("%d:OPERATOR:", i);
		    if (tmp->type == VARIABLE)
				printf("%d:VARIABLE:", i);
			printf("%s", tmp->c);
			printf("\n");
			tmp = tmp->next;
			i++;
		}
		add_history(c);
	}
	mymalloc(0, 1);
}