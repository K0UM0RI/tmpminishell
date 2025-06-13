/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:56 by sbat              #+#    #+#             */
/*   Updated: 2025/06/13 17:03:51 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	printbreakdown(t_line *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line)
// 	{
// 		printf("{");
// 		if (line->command && line->command[i])
// 		{
// 			if (line->command[i][0] == '\0')
// 				printf("\\0");
// 			else
// 				printf("%s", line->command[i]);
// 			i++;
// 		}
// 		while (line->command && line->command[i])
// 		{
// 			if (line->command[i][0] == '\0')
// 				printf(", \\0");
// 			else
// 				printf(", %s", line->command[i]);
// 			i++;
// 		}
// 		printf("}\n");
// 		i = 0;
// 		while (line->reds)
// 		{
// 			if (line->reds->redtype == RED_OUT_APPEND)
// 				printf("RED_OUT_APPEND:");
// 			if (line->reds->redtype == RED_OUT_TRUNC)
// 				printf("RED_OUT_TRUNC:");
// 			if (line->reds->redtype == RED_IN)
// 				printf("RED_IN:");
// 			if (line->reds->file)
// 				printf("%s\n", line->reds->file);
// 			line->reds = line->reds->next;
// 		}
// 		line = line->next;
// 	}
// }

// void	printcleanline(t_string *clean)
// {
// 	int	i;

// 	i = 0;
// 	while (clean)
// 	{
// 		if (clean->type == WORD)
// 			printf("%d:WORD:", i);
// 		if (clean->type == OPERATOR)
// 			printf("%d:OPERATOR:", i);
// 		printf("%s", clean->c);
// 		printf("\n");
// 		clean = clean->next;
// 		i++;
// 	}
// }

void ft_SIGINT(int sig)
{
    (void)sig;
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}
// handle not expanding when quotes in endoffile
//fixecho -n thing
//some characters stay even when after $
//dont show $_ in export
//make += work in export
//exit with biiiiig number
//9ra any signal functions used
int	main(int ac, char **av, char **env)
{
	char		*c;
	t_string	*clean;
	t_env		*lstenv;
	int			exit;
	t_line		*line;

	ac++;
	av++;
	if (!env || !*env)
		return (write(2, "error: env unset\n", 18));
	lstenv = getenvlst(env);
	exit = 0;
	signal(SIGINT, ft_SIGINT);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		c = NULL;
        c = ft_strjoin("\033[1;32mminishell>\033[0m\033[1;33m", getmyenv("1PWD", lstenv), 0);
        c = ft_strjoin(c, "\033[0m\033[34m$\033[0m", 0);
        c = readline(c);
		if (!c)
		{
        	write(1, "\nexit\n", 6);
        	break;
    	}	
		clean = clean_line(c, lstenv);
		if (clean == (t_string *)130)
			exit = 130;
		else if (clean)
		{
			line = breakdown(clean);
			// printcleanline(clean);
			// printbreakdown(line);
			exit = ft_execute(line, &lstenv);
		}
		else
			exit = 2;
		unprotectedgetnewvar(lstenv, ft_strdup("?", 2), ft_itoa(exit, 2));
		if (c && *c)
			add_history(c);
		free(c);
		mymalloc(0, 1);
	}
	mymalloc(0, 1);
	mymalloc(0, 3);
}
