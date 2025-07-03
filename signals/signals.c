/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 08:12:13 by sbat              #+#    #+#             */
/*   Updated: 2025/07/03 10:12:56 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_siginthere_subprocess(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exitandfree(130);
}

struct sigaction	ignoreparentsigint(void)
{
	struct sigaction	ignore;
	struct sigaction	old;

	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	sigaction(SIGINT, &ignore, &old);
	return (old);
}
