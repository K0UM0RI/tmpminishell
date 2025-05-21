/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:56 by sbat              #+#    #+#             */
/*   Updated: 2025/05/17 10:53:50 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// typedef struct s_string
// {
// 	char			*c;
// 	int				type;
// 	struct s_string	*next;
// }					t_string;

void red_addback(t_redirections **head, t_redirections *new)
{
	t_redirections *tmp;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_redirections *red_new(char *file, int type)
{
	t_redirections *tmp;

	tmp = mymalloc(sizeof(t_redirections), 0);
	tmp->file = file;
	tmp->redtype = type;
	tmp->next = NULL;
	return tmp;
}

char **gridjoin(char **command, char *elem, int i)
{
	char **ret;
	int j = 0;

	ret = mymalloc(sizeof(char *) * i + 1, 0);
	if (!command)
	{
		*ret = elem;
		ret[1] = NULL;
		return ret;
	}
	while (command[j])
	{
		ret[j] = command[j];
		j++;
	}
	ret[j] = elem;
	j++;
	ret[j] = NULL;
	return ret;
}

void linenew(t_line **line)
{
	(*line)->next = mymalloc(sizeof(line), 0);
	(*line) = (*line)->next;
	(*line)->command = NULL;
	(*line)->reds = NULL;
	(*line)->next = NULL;
}

t_line *breakdown(t_string *elems)
{
	t_line *line;
	t_line *head;
	int i = 1;
	char *tmp;

	linenew(&line);
	head = line;
	while (elems)
	{
		if (elems->type == OPERATOR)
		{
			tmp = elems->c;
			elems = elems->next;
			if (!ft_strncmp(tmp, ">", 1))
				red_addback(&line->reds, red_new(ft_strdup(elems->c, 0), RED_OUT_APPEND));
			if (!ft_strncmp(tmp, ">>", 2))
				red_addback(&line->reds, red_new(ft_strdup(elems->c, 0), RED_OUT_TRUNC));
			if (!ft_strncmp(tmp, "<", 1))
				red_addback(&line->reds, red_new(ft_strdup(elems->c, 0), RED_IN));
			if (!ft_strncmp(tmp, "|", 1))
			{
				linenew(&line);
				i = 1;
			}
		}
		else
		{
			line->command = gridjoin(line->command, ft_strdup(elems->c, 0), i);
			elems = elems->next;
			i++;
		}
	}
	return head;
}

int	main(int ac, char **av, char **env)
{
	char		*c;
	t_string	*tmp;
	int			i;
	t_env		*lstenv;
	t_line *line;

	ac++;
	av++;
	lstenv = getenvlst(env);
	i = 0;
	while (1)
	{
		c = readline("myshell:%>");
		i = 0;
		if (!c)
			break ;
		tmp = clean_line(c, lstenv);
		line = breakdown(tmp);
		while (line)
		{
			while (line->command && line->command[i])
			{
				printf("%s, ", line->command[i]);
				i++;
			}
			printf("\n");
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
		// while (tmp)
		// {
		// 	if (tmp->type == WORD)
		// 	{
		// 		printf("%d:WORD:", i);
		// 	}
		// 	if (tmp->type == OPERATOR)
		// 		printf("%d:OPERATOR:", i);
		// 	if (tmp->type == VARIABLE)
		// 		printf("%d:VARIABLE:", i);
		// 	printf("%s", tmp->c);
		// 	printf("\n");
		// 	tmp = tmp->next;
		// 	i++;
		// }
		add_history(c);
		mymalloc(0, 1);
	}
	mymalloc(0, 1);
	mymalloc(0, 3);
}
