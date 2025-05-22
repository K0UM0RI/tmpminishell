#include "minishell.h"

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
	t_line *tmp;
	if (!line)
		return ;
	tmp = mymalloc(sizeof(line), 0);
	tmp->command = NULL;
	tmp->reds = NULL;
	tmp->next = NULL;
	if (!*line)
		*line = tmp;
	else
	{
		(*line)->next = tmp;
		*line = (*line)->next;
	}
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
			if (ft_strncmp(tmp, "|", 1))
				elems = elems->next;
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