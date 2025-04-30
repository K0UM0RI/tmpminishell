#include "minishell.h"

static int	handlequotes(int *i, int *s, t_string **ret, char *c)
{
    if (*s)
		nexts_string(ret);
    *s = 0;
	if (c[*i] == '"')
	{
		(*i)++;
		*s = foundquote(c, i, ret);
		if (!(*ret)->c)
			return (printf("error:no double quote\n"), 1);
	}
	else if (c[*i] == '\'')
	{
		(*i)++;
		while (c[*i] && c[*i] != '\'')
			(*ret)->c = ft_append((*ret)->c, c[(*i)++]);
		if (c[(*i)++] != '\'')
			return (printf("error: no quote\n"), 1);
	}
	return (0);
}

static int	filllist(int *i, int *s, t_string **ret, char *c)
{
	int	d;
	char tmp;

	d = 0;
	if (c[*i] == '"' || c[*i] == '\'')
		d = handlequotes(i, s, ret, c);
	else if (isoperator(c[*i]))
	{
        if (*i)
		{
			(*ret)->append = 0;
		    nexts_string(ret);
		}
		(*ret)->type = OPERATOR;
		(*ret)->append = 0;
		tmp = c[*i];
		while (tmp == c[*i])
			(*ret)->c = ft_append((*ret)->c, c[(*i)++]);
		*s = 1;
	}
	else if (c[*i] == '$')
    {
		if (!s)
			(*ret)->append = 1;
        if (*i)
		    nexts_string(ret);
        (*ret)->type = VARIABLE;
		*s = foundvar(i, c, &((*ret)->c));
        *s = 1;
    }
	else if (!mywhitespace(c[*i]))
	{
        if (*s)
		    nexts_string(ret);
		*s = 0;
		(*ret)->c = ft_append((*ret)->c, c[(*i)++]);
	}
	while (mywhitespace(c[(*i)]))
    {
		(*ret)->append = 0;
        (*i)++;
		*s = 1;
    }
	return (d);
}

t_string	*clean_line(char *c)
{
	int i;
	t_string *ret;
	t_string *head;
	int s;

	s = 0;
	i = 0;
	ret = news_string();
	head = ret;
	if (mywhitespace(c[i]))
		i++;
	while (c[i])
	{
		if (filllist(&i, &s, &ret, c))
			return (NULL);
	}
	if (mywhitespace(c[i]))
		i++;
	ret->append = 0;
	return (head);
}
