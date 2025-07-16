/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:56 by sbat              #+#    #+#             */
/*   Updated: 2025/07/16 14:16:58 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*save_env(t_env *env)
{
	static t_env	*envs;

	if (env)
		envs = env;
	return (envs);
}

void	ft_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	unprotectedgetnewvar(save_env(NULL), "?", "130");
}

char	*getprompt(t_env *lstenv)
{
	char	*c;

	c = NULL;
	c = ft_strjoin(GREEN "minishell>" COLOR_RESET YELLOW, getmyenv("1PWD",
				lstenv), 0);
	c = ft_strjoin(c, COLOR_RESET BLUE "$" COLOR_RESET, 0);
	c = readline(c);
	return (c);
}

void	exec(t_env **lstenv, int *exit)
{
	char		*c;
	t_string	*clean;
	t_line		*line;

	c = getprompt(*lstenv);
	if (!c)
		(write(1, "\nexit\n", 6), exitandfree(*exit));
	if (!*c)
	{
		*exit = ft_atoi(getmyenv("?", *lstenv));
		return ;
	}
	clean = clean_line(c, *lstenv);
	if (clean == (t_string *)130)
		*exit = 130;
	else if (clean)
	{
		line = breakdown(clean);
		*exit = ft_execute(line, lstenv);
	}
	else
		*exit = 2;
	if (c && *c)
		add_history(c);
	free(c);
}

int	main(int ac, char **av, char **env)
{
	t_env	*lstenv;
	int		exit;

	ac++;
	av++;
	if (!env || !*env)
		return (write(2, "error: env unset\n", 18));
	lstenv = getenvlst(env);
	save_env(lstenv);
	(signal(SIGINT, ft_sigint), signal(SIGQUIT, SIG_IGN));
	while (1)
	{
		exec(&lstenv, &exit);
		unprotectedgetnewvar(lstenv, "?", ft_itoa(exit, 0));
		mymalloc(0, 1);
	}
	exitandfree(exit);
}
