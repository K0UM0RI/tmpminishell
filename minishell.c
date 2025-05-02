#include "minishell.h"

t_tree *maketree(t_string *c)
{
	t_string *tmp;
	t_tree *tree;

	tree = mymalloc(sizeof(t_tree), 0);
	tree->right = NULL;
	tree->left = NULL;
	tmp = c;
	while (c)
	{
		if (c->type)
		 ;;
	}
}

int	main(int ac, char **av, char **env)
{
	char *c;
	t_string *tmp;
	t_tree *tmp1;
	int i = 0;
	ac++;
	av++;
    env++;
	while (1)
	{
		c = readline("myshell:%>");
		i = 0;
		if (!c)
			break;
		tmp = clean_line(c);
		// tmp1 = maketree(tmp);
		while (tmp)
		{
			if (tmp->type == WORD)
			{
				printf("%d:WORD:", i);
			}
			if (tmp->type == OPERATOR)
				printf("%d:OPERATOR:", i);
            if (tmp->type == VARIABLE)
				printf("%d:VARIABLE:", i);
			printf("%s", tmp->c);
			if (tmp->append)
					printf("->\n");
			else 
				printf("\n");
			tmp = tmp->next;
			i++;
		}

		mymalloc(0, 1);
		add_history(c);
	}
	mymalloc(0, 1);
}