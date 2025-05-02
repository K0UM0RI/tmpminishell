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
# define REDIR 2
# define SUB_OPEN 3
# define SUB_CLOSE 4
# define VARIABLE 5
typedef struct s_tree
{
    char *elem;
    int type;
	int append;
    struct s_tree *left;
    struct s_tree *right;
}t_tree;

typedef struct s_truck
{
	void				*ptr;
	struct s_truck	*next;
}t_truck;

typedef struct s_string
{
	char			*c;
	int				type;
	int append;
	struct s_string	*next;
}					t_string;

t_string			*clean_line(char *c);

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
void *mymalloc(size_t size, int fn);
// parse utils
int					isoperator(char c);

// clean line utils
t_string			*news_string(void);
void				nexts_string(t_string **ret);
int	foundquote(char *c, int *i, t_string **ret);
int					foundvar(int *i, char *c, char **ret);
#endif