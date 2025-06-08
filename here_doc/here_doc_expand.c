#include "here_doc.h"

char	*here_docvarname(const char *c, int *i)
{
	char	*var;

	var = NULL;
	while (c[*i] && !mywhitespace(c[(*i)]) && c[(*i)] != '"'
		&& !isoperator(c[*i]) && c[(*i)] != '\'' && c[(*i)] != '$')
	{
		var = ft_append(var, c[(*i)], 0);
		(*i)++;
	}
	return (var);
}

char	*here_docexpand(int *i, const char *c, t_env *env)
{
	char	*var;

	(*i)++;
	var = here_docvarname(c, i);
	if (!var)
		return (ft_strdup("$", 0));
	var = getmyenv(var, env);
	return (var);
}