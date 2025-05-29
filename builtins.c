#include "minishell.h"

int ft_echo(char **command)
{
    int i;
    int n;

    i = 1;
    n = 0;
    if (!ft_strncmp(command[i], "-n", 3))
    {
        n = 1;
        i++;
    }
    while (command[i])
    {
        write(1, command[i], ft_strlen(command[i]));
        if (command[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (!n)
        write(1, "\n", 1);
    return 0;
}

int isbuiltin(char *command)
{
    if (!command)
        return -1;
    if (!ft_strncmp(command, "cd", 3) ||
        !ft_strncmp(command, "pwd", 4) || !ft_strncmp(command, "export", 7) ||
        !ft_strncmp(command, "unset", 6) || !ft_strncmp(command, "env", 4) ||
        !ft_strncmp(command, "exit", 5))
        return 1;
    return 0;
}

int ft_export(char **command, t_env *env)
{
    char **tmp;

    tmp = NULL;
    if (!command[1])
        return (write(2, "invalid options\n", 17), 1);
    tmp = ft_split(command[1], '=');
    if (ft_strncmp(env->name, tmp[0], ft_strlen(tmp[0])))
    {
        while (env->next && ft_strncmp(env->next->name, tmp[0], ft_strlen(tmp[0])))
            env = env->next;
    }
    if (!tmp || !tmp[0] || !tmp[1])
    {
        write(2, "export: not a valid identifier\n", 32);
        return 1;
    }
    if (tmp[2] || !ft_strncmp(tmp[0], "?", 2))
    {
        write(2, "export: not a valid identifier\n", 32);
        return 1;
    }
    env->next = mymalloc(sizeof(t_env), 2);
    env->next->name = ft_strdup(tmp[0], 2);
    env->next->value = ft_strdup(tmp[1], 2);
    env->next->next = NULL;
    return 0;
}

void openredirsnodup(t_redirections *reds)
{
    int file[2];

    file[0] = -1;
	file[1] = -1;
    while(reds)
	{
		if (reds->redtype == RED_OUT_APPEND)
			file[1] = open(reds->file, O_CREAT | O_APPEND | O_WRONLY, 0777);
		else if (reds->redtype == RED_OUT_TRUNC)
			file[1] = open(reds->file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		else if (reds->redtype == RED_IN)
		{
			file[0] = open(reds->file, O_RDONLY);
			if (file[0] < 0)
			{
				perror("open");
				exit(1);
			}
		}
        cleanfds(file, 2);
		reds = reds->next;
	}
}

int ft_env(t_env *env)
{
    while (env)
    {
        if (ft_strncmp(env->name, "?", 2))
            printf("%s=%s\n", env->name, env->value);
        env = env->next;
    }
    return (0);
}

int isnumber(char *c)
{
    int i;
    
    i = 0;
    if (c[i] == '-' || c[i] == '+')
        i++;
    while (c[i])
    {
        if (!(c[i] >= '0' && c[i] <= '9'))
            return (write(2, "numeric argument required\n", 27), 0);
        i++;
    }
    return 1;
}

int ft_exit(char **command)
{
    write(2, "exit\n", 5);
    if (!command[1])
        exit(0);
    if (command[2])
    {
        write(2, "too many arguments\n", 20);
        return 1;
    }
    if (isnumber(command[1]))
        exit (atoi(command[1]) & 0xFF);
    else
        exit(2);
}

int ft_unset(char **command, t_env **env)
{
    int i;
    t_env *tmp;
    t_env *previous;

    i = 1;
    if (!command[1])
        return 0;
    if (!ft_strncmp(command[1], "?", 2))
        return 0;
    while(command[i])
    {
        tmp = *env;
        previous = NULL;
        while (tmp)
        {
            if (!ft_strncmp(tmp->name, command[i], ft_strlen(command[i])))
            {
                if (previous)
                    previous->next = tmp->next;
                else
                    *env = (*env)->next;
                break;
            }
            previous = tmp;
            tmp = tmp->next;
        }
        i++;
    }
    return 0;
}
int execbuiltin(t_line *line, t_env **env)
{
    // if (!ft_strncmp(command[0], "cd", 3))
    //     return ft_cd(command, env);
    // if (!ft_strncmp(command[0], "pwd", 4))
    //     return ft_pwd();
    if (!ft_strncmp(line->command[0], "export", 7))
        return ft_export(line->command, *env);
    if (!ft_strncmp(line->command[0], "unset", 6))
        return ft_unset(line->command, env);
    if (!ft_strncmp(line->command[0], "env", 4))
        return ft_env(*env);
    if (!ft_strncmp(line->command[0], "exit", 5))
        return ft_exit(line->command);
    return 0;
}