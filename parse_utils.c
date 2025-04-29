#include "minishell.h"

int	isoperator(char c)
{
	return (mycmp(c, '|') || mycmp(c, '&') || mycmp(c, '<') || mycmp(c, '>') || mycmp(c, '(') || mycmp(c, ')'));
}