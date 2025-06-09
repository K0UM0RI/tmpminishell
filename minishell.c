/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:56 by sbat              #+#    #+#             */
/*   Updated: 2025/06/09 12:14:26 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define STDIN 100
#define STDOUT 101

void	printbreakdown(t_line *line)
{
	int	i;

	i = 0;
	while (line)
	{
		printf("{");
		if (line->command && line->command[i])
		{
			if (line->command[i][0] == '\0')
				printf("\\0");
			else
				printf("%s", line->command[i]);
			i++;
		}
		while (line->command && line->command[i])
		{
			if (line->command[i][0] == '\0')
				printf(", \\0");
			else
				printf(", %s", line->command[i]);
			i++;
		}
		printf("}\n");
		i = 0;
		while (line->reds)
		{
			if (line->reds->redtype == RED_OUT_APPEND)
				printf("RED_OUT_APPEND:");
			if (line->reds->redtype == RED_OUT_TRUNC)
				printf("RED_OUT_TRUNC:");
			if (line->reds->redtype == RED_IN)
				printf("RED_IN:");
			if (line->reds->file)
				printf("%s\n", line->reds->file);
			line->reds = line->reds->next;
		}
		line = line->next;
	}
}

void	printcleanline(t_string *clean)
{
	int	i;

	i = 0;
	while (clean)
	{
		if (clean->type == WORD)
			printf("%d:WORD:", i);
		if (clean->type == OPERATOR)
			printf("%d:OPERATOR:", i);
		printf("%s", clean->c);
		printf("\n");
		clean = clean->next;
		i++;
	}
}

void	changeexitstatus(int exit, t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(env->name, "?", 2))
		{
			env->value = ft_itoa(exit, 2);
			return ;
		}
		env = env->next;
	}
}
//handle not expanding when quotes in endoffile
int	main(int ac, char **av, char **env)
{
	const char	*c;
	t_string	*clean;
	t_env		*lstenv;
	int			exit;
	t_line		*line;

	ac++;
	av++;
	lstenv = getenvlst(env);
	exit = 0;
	while (1)
	{
		c = readline("minishell> ");
		if (!c)
			break ;
		clean = clean_line(c, lstenv);
		if (clean)
		{
			line = breakdown(clean);
			// printcleanline(clean);
			// printbreakdown(line);
			exit = ft_execute(line, &lstenv);
		}
		else
			exit = 2;
		changeexitstatus(exit, lstenv);
		add_history(c);
		mymalloc(0, 1);
	}
	mymalloc(0, 1);
	mymalloc(0, 3);
}
