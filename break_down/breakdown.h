/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breakdown.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:15:44 by sbat              #+#    #+#             */
/*   Updated: 2025/06/10 12:18:30 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BREAKDOWN_H
# define BREAKDOWN_H
# include "../minishell.h"

t_redirections	*red_new(char *file, int type);
void			red_addback(t_redirections **head, t_redirections *new);

#endif