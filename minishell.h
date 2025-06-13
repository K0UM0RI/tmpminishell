/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:35:01 by sbat              #+#    #+#             */
/*   Updated: 2025/06/13 23:13:39 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <bits/sigaction.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define WORD 0
# define OPERATOR 1
# define RED_OUT_APPEND 2
# define RED_OUT_TRUNC 3
# define RED_IN 4

typedef struct s_string
{
	char					*c;
	int						type;
	struct s_string			*next;
}							t_string;

typedef struct s_tree
{
	t_string				*command;
	t_string				*input_red;
	t_string				*output_red;
	int						type;
	int						append;
	struct s_tree			*left;
	struct s_tree			*right;
}							t_tree;

typedef struct s_truck
{
	void					*ptr;
	struct s_truck			*next;
}							t_truck;

typedef struct s_lexvars
{
	int						i;
	t_string				*ret;
	int						s;
	int						d;
}							t_lexvars;

typedef struct s_env
{
	char					*name;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct s_redirections
{
	char					*file;
	int						redtype;
	struct s_redirections	*next;
}							t_redirections;

typedef struct s_line
{
	char					**command;
	t_redirections			*reds;
	struct s_line			*next;
}							t_line;

typedef struct s_exec
{
	int						pipefd[2];
	int						oldpipefd[2];
	int						*child;
	int						npipes;
}							t_exec;

typedef struct s_here_doc
{
	char					*file;
	int						fd;
}							t_here_doc;

// malloc-free
void						*mymalloc(size_t size, int fn);

// utils
char						**ft_split(char *s, char c);
char						*ft_strjoin(char *s1, char *s2, int fn);
char						*ft_append(char *c1, char c2, int fn);
char						*ft_strdup(char *s, int fn);
int							mywhitespace(char c);
int							isoperator(char c);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
int							ft_strlen(char *c);
int							ft_atoi(const char *nptr);
char						*ft_itoa(int n, int fn);
int							is_directory(char *path);
int							ft_isnum(int c);
int							ft_isalpha(int c);
void						exitandfree(int exit_status);
// env
char						*getmyenv(char *var, t_env *env);
void						unprotectedgetnewvar(t_env *env, char *name,
								char *value);

t_string					*clean_line(const char *c, t_env *env);
t_line						*breakdown(t_string *elems);
int							ft_execute(t_line *line, t_env **env);
t_env						*getenvlst(char **env);

#endif