#include "minishell.h"

#define WORD 0
#define OPERATOR 1
#define REDIR 2
#define SUB_OPEN 3
#define SUB_CLOSE 4

// typedef struct s_token
// {
//     char *tok;
//     int type;
//     struct s_stoken *next;
// }t_token;

// t_token *next_token(char *c)
// {
    
// }
//' ' ,  '\t' ,  '\r' ,  '\n' ,  '\v'  '\f'

typedef struct s_string
{
    char *c;
    struct s_string *next;
}t_string;

int  mywhitespace(char c)
{
    return (c ==  ' ' ||  c ==  '\t' ||  
        c ==  '\r' ||  c ==  '\n'||  c ==  '\v'|| c ==  '\f');
}

int ft_strlen(char *c)
{
    int i;

    i = 0;
    while (c[i])
        i++;
    return (i);
}

char *ft_append(char *c1, char c2)
{
    char *c;
    int i;
    int l;

    i = 0;
    l = 0;
    if (c1)
        l = ft_strlen(c1);
    c = malloc(sizeof(char) * (l + 2));
    while (c1 && *c1)
    {
        c[i] = *c1;
        c1++;
        i++;
    }
    c[i] = c2;
    i++;
    c[i] = '\0';
    // if (c1)
    //    free(c1);
    return (c);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (i < n)
	{
		if (s1[i] != s2[i] || !s1[i] || !s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char *getvarname(char *c, int *i)
{
    char *var;

    var = NULL;
    while (c[*i] && !mywhitespace(c[(*i)]) && c[(*i)] != '"') 
    {
        var = ft_append(var, c[(*i)]);
        (*i)++;
    }
    return var;
}

char *getmyenv(char *var, char **env)
{
    int l;
    int j = 0;
    l = ft_strlen(var);
    while (env[j])
    {
        if (!ft_strncmp(env[j], var, l) && env[j][l] == '=')
            return (env[j] + l + 1);
        j++;
    }
    return NULL;
}

char *foundvar(int *i, char *c, char *ret, char **env)
{
    char *var;

    (*i)++;
    var = getvarname(c, i);
    if (!var)
        ret = ft_append(ret, '$');
    else
    {
        var = getmyenv(var, env);
        if (!var)
            ret = ft_append(ret, '$');
        else
        {
           ret = ft_strjoin(ret, var);
           // printf("var:%s\n", var);
        }
    }
    return ret;
}

char *foundquote(char **env, char *c,  int *i, char *ret)
{
    while (c[*i] && c[*i] != '"')
    {
        if (c[*i] == '$')
            ret = foundvar(i, c, ret, env);
        else
        {
            ret = ft_append(ret, c[*i]);
            (*i)++;
        }
    }
    return ret;
}

t_string *news_string()
{
    t_string *c;

    c = malloc(sizeof(t_string));
    c->c = NULL;
    c->next = NULL;
    return (c);
}

t_string *clean_line(char *c, char **env)
{
    int i;
    t_string *ret;
    t_string *head;

    i = 0;
    ret = news_string();
    head = ret;
    if (c[i] && mywhitespace(c[i]))
            i++;
    while (c[i])
    {
        if (c[i] == '"')
        {
            i++;
            ret->next = news_string();
            ret = ret->next;
            ret->c = foundquote(env, c, &i, ret->c);
            if (c[i] != '"')
                (printf("error\n"), exit(1));
            i++;
        }
        if (c[i] && c[i] == '\'')
        {
            i++;
            ret->next = news_string();
            ret = ret->next;
            while (c[i] && c[i] != '\'')
                ret->c = ft_append(ret->c, c[i++]);
            if (c[i] != '\'')
                return (printf("error\n"),NULL);
            i++;
        }
        else if (c[i] == '$')
        {
            if (i && (mywhitespace(c[i - 1]) || c[i - 1] =='\'' || c[i - 1] == '"'))
            {
                ret->next = news_string();
                ret = ret->next;
            }
            ret->c = foundvar(&i, c, ret->c, env);
        }
        else if (c[i] && !mywhitespace(c[i]))
        {
            if (i && (mywhitespace(c[i - 1]) || c[i - 1] =='\'' || c[i - 1] == '"'))
            {
                ret->next = news_string();
                ret = ret->next;
            }
            ret->c = ft_append(ret->c, c[i]);
        }
        i++;
        while (mywhitespace(c[i]))
            i++;
    }
    if (c[i] && mywhitespace(c[i]))
            i++;
    return head;
}

int main(int ac, char **av, char **env)
{
    char *c;
    t_string *tmp;
    int i = 0;

    while (1)
    {
        c = readline("myshell:%>");
        i = 0;
        tmp = clean_line(c, env);
        while (tmp)
        {
            printf("%d:%s\n", i,tmp->c);
            tmp = tmp->next;
            i++;
        }
        // free(tmp);
        // tmp = next_token(c);
        // while (tmp){
        //     printf("%s\n", tmp);
        //     tmp = next_token(c);
        // }
        add_history(c);
    }
}