#include "breakdown.h"

void	red_addback(t_redirections **head, t_redirections *new)
{
	t_redirections	*tmp;

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

t_redirections	*red_new(char *file, int type)
{
	t_redirections	*tmp;

	tmp = mymalloc(sizeof(t_redirections), 0);
	tmp->file = file;
	tmp->redtype = type;
	tmp->next = NULL;
	return (tmp);
}

