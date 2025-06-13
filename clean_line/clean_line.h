/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:16:08 by sbat              #+#    #+#             */
/*   Updated: 2025/06/13 22:13:20 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_LINE_H
# define CLEAN_LINE_H

# include "../minishell.h"

int			handlequotes(t_lexvars *vars, const char *c, t_env *env);
char		*foundvar(int *i, const char *c, t_env *env);
void		foundexpandable(t_lexvars *vars, const char *c, t_env *env);
int			filllist(t_lexvars *vars, const char *c, t_env *env);
int			handlerrors(t_string *clean);

// utilsutils
t_string	*news_string(void);
void		nexts_string(t_string **ret);
int			mywhitespace(char c);
int			is_redirection(const t_string *node);
char		*getvarname(const char *c, int *i);

// here_doc
int			doheredoc(int *i, t_string **ret, const char *c, t_env *env);

#endif