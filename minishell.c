#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i] || !s1[i] || !s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	doublecharlen(char **c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

void	freed(char **c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		free(c[i]);
		i++;
	}
	free(c);
}

void exitcommand(char **tmp)
{
    int i = 0;

    ft_putstr_fd("exit\n", 2);
    if (doublecharlen(tmp) == 1)
        (freed(tmp), exit(0));
    if (doublecharlen(tmp) > 2)
        (freed(tmp), ft_putstr_fd("exit: too many arguments\n", 2));
    else
    {
        if (tmp[1][i] == '-' || tmp[1][i] == '+')
            i++;
        while (tmp[1][i])
        {
            if (!ft_isdigit(tmp[1][i]))
            {
                ft_putstr_fd("exit: ", 2);
                ft_putstr_fd(tmp[1], 2);
                ft_putstr_fd(" : numeric argument required\n", 2);
                freed(tmp);
                exit(2);
            }
            i++;
        }
        i = ft_atoi(tmp[1]);
        freed(tmp);
        exit(i);
    }


}

int main(int ac, char **av, char **env)
{
    char *c;
    char **tmp;
   // t_list *data;
    ac++;
    av++;
    while (1)
    {
        c = readline("myshell:%>");
        tmp = ft_split(c, ' ');
        if (!ft_strcmp("exit", tmp[0]))
            (free(c), exitcommand(tmp));
    }
}