#ifndef HERE_DOC_H
#define HERE_DOC_H

#include "../minishell.h"

char	*here_docexpand(int *i, const char *c, t_env *env);
char	*here_docvarname(const char *c, int *i);

//clean_line
void	nexts_string(t_string **ret);
#endif