#include "clean_line.h"

int	mywhitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v'
		|| c == '\f');
}

t_string	*news_string(void)
{
	t_string	*c;

	c = (t_string *)mymalloc(sizeof(t_string), 0);
	c->c = NULL;
	c->next = NULL;
	c->type = 0;
	return (c);
}

void	nexts_string(t_string **ret)
{
	(*ret)->next = news_string();
	(*ret) = (*ret)->next;
	(*ret)->type = 0;
}