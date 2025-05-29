/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:35:01 by sbat              #+#    #+#             */
/*   Updated: 2025/05/29 03:48:53 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>

# define WORD 0
# define OPERATOR 1
# define RED_OUT_APPEND 2
# define RED_OUT_TRUNC 3
# define RED_IN 4

typedef struct s_string
{
	char			*c;
	int				type;
	struct s_string	*next;
}					t_string;

typedef struct s_tree
{
	t_string		*command;
	t_string		*input_red;
	t_string		*output_red;
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

typedef struct s_lexvars
{
	int				i;
	t_string		*ret;
	int				s;
	int				d;
}					t_lexvars;

typedef struct s_env
{
	char			*name;
	char			*value;
	int unset;
	struct s_env	*next;
}					t_env;

typedef struct s_redirections
{
	char *file;
	int redtype;
	struct s_redirections *next;
} t_redirections;

typedef struct s_line
{
	char **command;
	t_redirections *reds;
	struct s_line *next;
} t_line;

typedef struct s_exec
{
	int pipefd[2];
	int oldpipefd[2];
	int *child;
	int npipes;
} t_exec;

t_string			*clean_line(const char *c, t_env *env);

// env utils
char				*getmyenv(char *var, t_env *env);
t_env				*getenvlst(char **env);
char **convertenv(t_env *env);

char				*ft_strjoin(char *s1, char *s2, int fn);
int					ft_strlen(char *c);
int					mywhitespace(char c);
char				*ft_append(char *c1, char c2, int fn);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					mywhitespace(char c);
int					mycmp(char c1, char c2);
size_t				ft_strlcat(char *dst, char *src, size_t size);
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
void				*mymalloc(size_t size, int fn);
char				*ft_strdup(char *s, int fn);
int					ft_atoi(const char *nptr);
char				*ft_itoa(int n, int fn);
char	**ft_split(char *s, char c);
// parse utils
int					isoperator(char c);
int					filllist(t_lexvars *vars, const char *c, t_env *env);

// clean line utils
t_string			*news_string(void);
void				nexts_string(t_string **ret);
int					foundquote(const char *c, int *i, t_string **ret, t_env *env);
char				*foundvar(int *i, const char *c, t_env *env);
int					doheredoc(int *i, t_string **ret, const char *c);

char	*getcmd(char *cmd, t_env *env);

//breakdown
t_line *breakdown(t_string *elems);

void ft_execute(t_line *line, t_env *env);

//bultins
int ft_echo(char **command);
void openredirsnodup(t_redirections *reds);
int execbuiltin(t_line *line, t_env *env);
int isbuiltin(char *command);

void cleanfds(int *fd, int end);
#endif