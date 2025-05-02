#include "minishell.h"

void free_lst(t_truck **allocated)
{
    t_truck *tmp;
    if (!*allocated)
        return;
    tmp = *allocated;
    while (tmp)
    {
        free(tmp->ptr);
        tmp = tmp->next;
        free(*allocated);
        *allocated = tmp;
    }
}

void *mymalloc(size_t size, int fn)
{
    static t_truck *allocated = NULL;
    t_truck *new;
    if (fn)
        return(free_lst(&allocated), NULL);
    new = malloc(sizeof(t_truck));
    if (!new)
    {
        write(2, "malloc failed!\n", 15);
        free_lst(&allocated);
        exit(1);
    }
    new->ptr = malloc(size);
    if (!new)
    {
        write(2, "malloc failed!\n", 15);
        free(new);
        free_lst(&allocated);
        exit(1);
    }
    new->next = allocated;
	allocated = new;
    return (new->ptr);
}
