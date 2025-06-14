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