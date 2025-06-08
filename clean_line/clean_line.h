#ifndef CLEAN_LINE_H
#define CLEAN_LINE_H

#include "../minishell.h"

int	foundquote(const char *c, int *i, t_string **ret, t_env *env);
char	*foundvar(int *i, const char *c, t_env *env);
void	nexts_string(t_string **ret);
t_string	*news_string(void);
int	mywhitespace(char c);

int	filllist(t_lexvars *vars, const char *c, t_env *env);

//here_doc
int	doheredoc(int *i, t_string **ret, const char *c, t_env *env);

#endif