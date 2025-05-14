/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:35:01 by sbat              #+#    #+#             */
/*   Updated: 2025/05/14 09:58:01 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WORD 0
# define OPERATOR 1
# define SUB_OPEN 2
# define SUB_CLOSE 3
# define VARIABLE 4
# define PIPE 5
# define AND 38
# define OR 124
# define SUBSHELL 8
#define COMMAND 69

typedef struct s_string
{
	char			*c;
	int				type;
	int				append;
	struct s_string	*next;
}					t_string;

typedef struct s_tree
{
	t_string *command;
	t_string *input_red;
	t_string *output_red;
	int				type;
	int				append;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct s_truck
{
	void			*ptr;
	struct s_truck	*next;
}					t_truck;

t_string			*clean_line(char *c, char **env);

// env utils
char				*getmyenv(char *var, char **env);

char				*ft_strjoin(char *s1, char *s2);
int					ft_strlen(char *c);
int					mywhitespace(char c);
char				*ft_append(char *c1, char c2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					mywhitespace(char c);
int					mycmp(char c1, char c2);
size_t				ft_strlcat(char *dst, char *src, size_t size);
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
void				*mymalloc(size_t size, int fn);
char				*ft_strdup(char *s);
// parse utils
int					isoperator(char c);

// clean line utils
t_string			*news_string(void);
void				nexts_string(t_string **ret);
int					foundquote(char *c, int *i, t_string **ret, char **env);
char					*foundvar(int *i, char *c, char **ret, char **env);
#endif