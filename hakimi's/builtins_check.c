#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

int is_builtin(char *cmd)
{
    if (!cmd)
        return 0;
    return (!ft_strncmp(cmd, "cd", 3)
        || !ft_strncmp(cmd, "pwd", 4)
        || !ft_strncmp(cmd, "export", 7)
        || !ft_strncmp(cmd, "unset", 6)
        || !ft_strncmp(cmd, "exit", 5)
        || !ft_strncmp(cmd, "echo", 5)
        || !ft_strncmp(cmd, "env", 4));
}

int run_builtin(t_string *args, t_env **env)
{
    if (!args)
    return 0;
    printf("Running builtin: %s\n", args->c);
    if (!ft_strncmp(args->c, "env", 4))
        return builtin_env(*env);
    if (!ft_strncmp(args->c, "echo", 5))
        return builtin_echo(args);
    if (!ft_strncmp(args->c, "pwd", 4))
        return builtin_pwd(args);
    if (!ft_strncmp(args->c, "exit", 5))
        return builtin_exit(args);
    if (!ft_strncmp(args->c, "unset", 6))
            return builtin_unset(args, env);
    if (!ft_strncmp(args->c, "cd", 3))
        return builtin_cd(args, env);
    // if (!ft_strncmp(args->c, "export", 7))
    //     return builtin_export(args, *env);
    return 1;
}

int check_cmd(t_string *tmp, t_env **lstenv)
{
    if (tmp && tmp->type == WORD && is_builtin(tmp->c))
        return run_builtin(tmp, lstenv);
    else
    {
        // fork + exec external commands
        return -1;
    }
}
