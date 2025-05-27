/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:56 by sbat              #+#    #+#             */
/*   Updated: 2025/05/27 23:27:20 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define STDIN 100
# define STDOUT 101

void printbreakdown(t_line *line)
{
	int i = 0;

	while (line)
	{
		printf("{");
		if (line->command && line->command[i])
			printf("%s", line->command[i++]);
		while (line->command && line->command[i])
		{
			printf(", %s", line->command[i]);
			i++;
		}
		printf("}\n");
		i = 0;
		while (line->reds)
		{
			if (line->reds->redtype == RED_OUT_APPEND)
				printf("RED_OUT_APPEND:");
			if (line->reds->redtype == RED_OUT_TRUNC)
				printf("RED_OUT_TRUNC:");
			if (line->reds->redtype == RED_IN)
				printf("RED_IN:");
			if (line->reds->file)
				printf("%s\n", line->reds->file);
			line->reds = line->reds->next;
		}
		line = line->next;
	}
}

void printcleanline(t_string *clean)
{
	int i = 0;

	while (clean)
	{
		if (clean->type == WORD)
			printf("%d:WORD:", i);
		if (clean->type == OPERATOR)
			printf("%d:OPERATOR:", i);
		printf("%s", clean->c);
		printf("\n");
		clean = clean->next;
		i++;
	}
}

int handlerrors(t_string *clean)
{
	int p = 0;
	int r = 0;

	if (!clean)
		return 1;
	if (!ft_strncmp(clean->c, "|", 1) && clean->type == OPERATOR)
		return (printf("syntax error\n"), 1);
	while (clean)
	{
		if ((r || p) && !ft_strncmp(clean->c, "|", 1) && clean->type == OPERATOR)
			return (printf("syntax error\n"), 1);
		else if (clean->type == OPERATOR && ft_strncmp(clean->c, "|", 1))
		{
			r = 1;
			p = 0;
		}
		else if (!ft_strncmp(clean->c, "|", 1) && clean->type == OPERATOR)
			p = 1;
		else if(!(!ft_strncmp(clean->c, "|", 1) && clean->type == OPERATOR))
		{
			p = 0;
			r = 0;
		}
		clean = clean->next;
	}
	if (p || r)
		return (printf("syntax error\n"), 1);
	return 0;
}

typedef struct s_exec
{
	int pipefd[2];
	int oldpipefd;
	int *child;
	int npipes;
	int file[2];
} t_exec;

int ft_lstsizeline(t_line *line)
{
	int size;

	while(line)
	{
		size++;
		line = line->next;
	}
	return size;
}

int ft_lstsizeenv(t_env *env)
{
	int size;

	while(env)
	{
		size++;
		env = env->next;
	}
	return size;
}

char **convertenv(t_env *env)
{
	int size;
	char **ret;
	int i = 0;
	
	size = ft_lstsizeenv(env);
	ret = mymalloc(sizeof(char *) * (size + 1), 0);
	while (env)
	{
		ret[i] = ft_append(env->name, '=', 0);
		ret[i] = ft_strjoin(ret[0], env->value, 0);
		i++;
		env = env->next;
	}
	ret[i] = NULL;
	return ret;
}

void ft_execute(t_line *line, t_env *env)
{
	t_exec exec;
	t_redirections *reds;

	int i = 0;
	char *cmd;
	int j;

	reds = NULL;
	exec.npipes = ft_lstsizeline(line);
	exec.child = mymalloc(sizeof(int) * exec.npipes, 0);
	while (line)
	{
		if (line->command && *line->command)
		{
			pipe(exec.pipefd);
			exec.child[i] = fork();
			exec.oldpipefd = exec.pipefd[0];
			if (!exec.child[i])
			{
				exec.file[0] = -1;
				exec.file[1] = -1;
				if (i)
					dup2(exec.oldpipefd, 0);
				if (line->next)
					dup2(exec.pipefd[1], 1);
				reds = line->reds;
				while(reds)
				{
					if (reds->redtype == RED_OUT_APPEND)
					{
						if (exec.file[1] != -1)
							close(exec.file[1]);
						exec.file[1] = open(reds->file, O_CREAT | O_APPEND | O_WRONLY, 0777);
						dup2(exec.file[1], 1);
					}
					else if (reds->redtype == RED_OUT_TRUNC)
					{
						if (exec.file[1] != -1)
							close(exec.file[1]);
						exec.file[1] = open(reds->file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
						dup2(exec.file[1], 1);
					}
					else if (reds->redtype == RED_IN)
					{
						if (exec.file[0] != -1)
							close(exec.file[0]);
						exec.file[0] = open(reds->file, O_RDONLY);
						dup2(exec.file[0], 0);
					}
					reds = reds->next;
					i++;
				}
				cmd = getcmd(line->command[0], env);
				if (!cmd)
					exit(127);
				execve(cmd, line->command, convertenv(env));
			}
		}
		exec.oldpipefd = exec.pipefd[0];
		line = line->next;
	}
	j = 0;
	while (j < i)
	{
		waitpid(exec.child[j], NULL, 0);
		j++;
	}
}

int	main(int ac, char **av, char **env)
{
	const char		*c;
	t_string	*clean;
	t_env		*lstenv;
	t_line *line;

	ac++;
	av++;
	lstenv = getenvlst(env);
	while (1)
	{
		c = readline(NULL);
		if (!c)
			break ;
		clean = clean_line(c, lstenv);
		if (!handlerrors(clean))
		{
			line = breakdown(clean);
			// printbreakdown(line);
			ft_execute(line, lstenv);
		}
		add_history(c);
		mymalloc(0, 1);
	}
	mymalloc(0, 1);
	mymalloc(0, 3);
}
