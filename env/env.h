/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:15:32 by sbat              #+#    #+#             */
/*   Updated: 2025/06/13 22:16:33 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../minishell.h"

void	add_env(t_env *env, char *name);
void	newenv(t_env **lstenv, char *name, char *value);

#endif