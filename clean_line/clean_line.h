#ifndef CLEAN_LINE_H
#define CLEAN_LINE_H

#include "../minishell.h"

int	handlequotes(t_lexvars *vars, const char *c, t_env *env);
char	*foundvar(int *i, const char *c, t_env *env);
void	foundexpandable(t_lexvars *vars, const char *c, t_env *env);
int	filllist(t_lexvars *vars, const char *c, t_env *env);
int	handlerrors(t_string *clean);

//utilsutils
t_string	*news_string(void);
void	nexts_string(t_string **ret);
int	mywhitespace(char c);

//here_doc
int	doheredoc(int *i, t_string **ret, const char *c, t_env *env);

#endif