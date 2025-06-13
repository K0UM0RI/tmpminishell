/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:16:48 by sbat              #+#    #+#             */
/*   Updated: 2025/06/13 22:07:55 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "../minishell.h"

char				*here_docexpand(int *i, const char *c, t_env *env);
char				*here_docvarname(const char *c, int *i);

void				here_doceof(char *line, char *eof, int size);
void				ft_siginthere_doc(int sig);
t_here_doc			initfile(void);
struct sigaction	ignoreparentsigint(void);

// clean_line
void				nexts_string(t_string **ret);
#endif