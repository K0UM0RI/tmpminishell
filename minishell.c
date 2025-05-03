/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <sbat@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:34:56 by sbat              #+#    #+#             */
/*   Updated: 2025/05/03 16:50:00 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_strcmp(char *s1, char *s2)
// {
// 	while (*s1 && *s2 && *s1 == *s2)
// 	{
// 		s1++;
// 		s2++;
// 	}
// 	return (*s1 - *s2);
// }

// int	ft_lstsize(t_string *lst)
// {
// 	int		n;
// 	t_string	*s;

// 	if (!lst)
// 		return (0);
// 	s = lst;
// 	n = 1;
// 	while (1)
// 	{
// 		s = s->next;
// 		if (!s)
// 			return (n);
// 		n++;
// 	}
// 	return (0);
// }

// t_tree	*newt_tree(int type)
// {
// 	t_tree	*node;

// 	node = (t_tree *)mymalloc(sizeof(t_tree), 0);
// 	node->type = type;
// 	node->left = node->right = NULL;
// 	return (node);
// }

// t_string	*findlastopfield(t_string *c)
// {
// 	t_string	*tmp;
// 	t_string	*ret;
// 	t_string	*tmp2;
// 	int s = 0;

// 	tmp = c;
// 	if (!c)
// 		return NULL;
// 	while (c->next)
// 	{
// 		if (c->next->type == OPERATOR && c->next->c[0] == '(')
// 		{
// 			while (!(c->next->type == OPERATOR && c->next->c[0] == ')'))
// 				c = c->next;
// 		}
// 		if (c->next->type == OPERATOR && ((c->next->c[0] == '|'
// 					&& c->next->c[1] == '|') || c->next->c[0] == '&'))
// 		{
// 			tmp = c;
// 			s = 1;
// 		}
// 		c = c->next;
// 	}
// 	if (tmp->next && s == 1)
// 	{
// 		tmp2 = tmp;
// 		tmp = tmp->next;
// 		tmp2->next = NULL;
// 	}		
// 	ret = news_string();
// 	tmp2 = ret;
// 	while (tmp)
// 	{
// 		tmp2->c = ft_strdup(tmp->c);
// 		tmp2->type = tmp->type;
// 		tmp2->append = tmp->append;
// 		tmp = tmp->next;
// 		if (tmp)
// 			nexts_string(&tmp2);
// 	}
// 	return (ret);
// }

// // t_string	*findredirections(void)
// // {
// // }

// t_string	*findlastpipefield(t_string *c)
// {
// 	t_string	*tmp;

// 	tmp = c;
// 	if (!c)
// 		return NULL;
// 	while (c)
// 	{
// 		if (c->type == OPERATOR && c->c[0] == '|')
// 			tmp = c->next;
// 		c = c->next;
// 	}
// 	return (tmp);
// }

// t_tree *handlpipes(t_string *tmpop)
// {
// 	t_string *command;
// 	t_string *input_red;
// 	t_string *output_red;
// 	t_string *tmppipe;
// 	t_tree *current;
// 	t_tree *root;

// 	root = NULL;
// 	int s;
// 	s = 0;
// 	tmppipe = findlastpipefield(tmpop);
// 	if (!tmpop->next || (tmppipe->type == OPERATOR && !tmppipe->c[0] == '|'))
// 		tmpop = NULL;
// 	while (tmppipe)
// 	{ 
// 		if (tmppipe->c[0] == '|' && tmppipe->type == OPERATOR)
// 		{
// 			if (s % 2 == 0)
			
// 			while (tmppipe)
// 			{
// 				if (ft_strcmp(tmppipe->c, ">"))
// 				{
// 					news_string;
// 				}
// 			}
// 		}
// 	}
// }

// t_tree	*maketree(t_string *c)
// {
// 	t_tree	*root;
// 	t_tree	*current;
// 	t_tree	*left;
// 	t_tree	*right;
// 	t_string *tmpop; 
// 	char **command;
// 	int i = 0;
// 	int s = 0;
// 	int j = 0;

// 	root = NULL;
// 	current = NULL;
// 	left = NULL;
// 	right = NULL;
// 	tmpop = findlastopfield(c);
// 	if (!c->next || (tmpop->type == OPERATOR && !((tmpop->c[0] == '|'
// 					&& tmpop->c[1] == '|') || tmpop->c[0] == '&')))
// 			c = NULL;
// 	// while (tmpop)
// 	// {
		
// 	// }
// 	while (tmpop)
// 	{
// 		printf("%s\n", tmpop->c);
// 		tmpop = tmpop->next;
// 	}
// 	printf("------------\n");
// 	while (c)
// 	{
// 		printf("%s\n", c->c);
// 		c = c->next;
// 	}
// 	// return ( head);
// }

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
			break ;
		tmp = clean_line(c, env);
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