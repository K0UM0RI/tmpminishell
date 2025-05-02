#include "minishell.h"

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
	(*ret)->append = 1;
}

char	*getvarname(char *c, int *i)
{
	char	*var;

	var = NULL;
	if (c[*i] == '(')
		(*i)++;
	while (c[*i] && !mywhitespace(c[(*i)]) && c[(*i)] != '"'
		&& !isoperator(c[*i]) && c[(*i)] != '\'' && c[(*i)] != '$')
	{
		var = ft_append(var, c[(*i)]);
		(*i)++;
	}
	return (var);
}

int	foundvar(int *i, char *c, char **ret)
{
	char	*var;

	(*i)++;
	var = getvarname(c, i);
	if (!var)
		*ret = ft_append(*ret, '$');
    else 
    {
        *ret = ft_strjoin(*ret, var);
    }
	return (0);
}

int	foundquote(char *c, int *i, t_string **ret)
{
    int s;

    s = 0;
	while (c[*i] && c[*i] != '"')
	{
		if (c[*i] == '$')
        {
            if (*i && c[(*i) - 1] != '"')
                nexts_string(ret);
            (*ret)->type = VARIABLE;
			foundvar(i, c, &(*ret)->c);
            s = 1;
        }
		else
		{
            if (s)
            {
                nexts_string(ret);
				(*ret)->append = 1;
                s = 0;
            }
			(*ret)->c = ft_append((*ret)->c, c[*i]);
			(*i)++;
		} 
	}
	if (c[(*i)++] != '"')
        return -1;
	return (s);
}
