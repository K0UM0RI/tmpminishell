#include "minishell.h"


int builtin_echo(t_string *args)
{
    args = args->next;
    int no_newline = 0;

    while(args && !ft_strncmp(args->c, "-n", 3))
    {
        no_newline = 1;
        args = args->next;
    }
    while (args)
    {
        if (args->c)
            write(1, args->c, ft_strlen(args->c));
        if (args->next)
            write(1, " ", 1);
        args = args->next;
    }
    if(!no_newline)
        write(1,"\n",1);
    return(0);

    
}

int builtin_env(t_env *env)
{
    while(env)
    {
        if(env->value)
        {
            write(1,env->name,ft_strlen(env->name));
            write(1,"=",1);
            write(1, env->value,ft_strlen(env->value));
            write(1,"\n",1);
        }
        env = env->next;
    }
    return 0;
}
int builtin_pwd(t_string *args)
{
    char *cwd;
    if(!(cwd = getcwd(NULL,0)))
        {
            write(1,"error\n",6);
            return -1;
        }
    else
    {
        write(1,cwd,ft_strlen(cwd));
        write(1, "\n", 1);
    }
    free(cwd);
    return 0;
}

int builtin_exit(t_string *args)
{
    (void)args;
    write(1, "exit\n", 5);
    exit(0);
}

int builtin_unset(t_string *args, t_env **env)
{
    t_env *prev;
    t_env *curr;
    t_env *tmp;

    args = args->next;
    while(args)
    {
        prev = NULL;
        curr = *env;
        while(curr)
        {
            if(!ft_strncmp(curr->name, args->c, ft_strlen(args->c) + 1))
            {
                if(prev == NULL)
                    *env = curr->next;
                else
                    prev->next = curr->next;
                tmp = curr->next;
                free(curr->name);
                free(curr->value);
                free(curr);
                curr = tmp;
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
        args = args->next;
    }
    return 0;
}

int builtin_cd(t_string *args, t_env **env)
{
    char *home;

    args = args->next;
    if (args) 
    {
        write(2, "cd with path not yet supported\n", 31);
        return 1;
    }

    home = getmyenv("HOME", *env);
    if (!home || !*home)
    {
        write(2, "cd: HOME not set\n", 17);
        free(home);
        return 1;
    }

    if (chdir(home) != 0)
    {
        perror("cd");
        free(home);
        return 1;
    }
    free(home);
    return 0;
}


int builtin_export(t_string *args, t_env *env);