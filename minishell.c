#include "minishell.h"

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

int	main(int ac, char **av, char **env)
{
	char *c;
	t_string *tmp;
	int i = 0;
	ac++;
	av++;
    env++;
	while (1)
	{
		c = readline("myshell:%>");
		i = 0;
		tmp = clean_line(c);
		while (tmp)
		{
			if (tmp->type == WORD)
				printf("%d:WORD:", i);
			if (tmp->type == OPERATOR)
				printf("%d:OPERATOR:", i);
            if (tmp->type == VARIABLE)
				printf("%d:VARIABLE:", i);
			printf("%s\n", tmp->c);
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