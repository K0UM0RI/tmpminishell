#include "builtins.h"

void print_export(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->name, "?", 2))
		{
			printf("declare -x %s", env->name);
			if (env->value)
				printf("=\"%s\"", env->value);
			printf("\n");
		}
		env = env->next;
	}
}

void add_env(t_env *env, char *tmp)
{
	env->next = mymalloc(sizeof(t_env), 2);
	env->next->name = tmp;
	env->next->value = NULL;
	env->next->next = NULL;
}

int getvalue(char *tmp)
{
	int j;

	j = 0;
	if(*tmp == '=')
		return (0);
	while (tmp[j] && tmp[j] != '=')
		j++;
	if (!tmp[j])
		return (-1);
	else
		tmp[j] = '\0';
	return (j);
}

void getnewvar(char *tmp, t_env *env)
{
	int s;

	s = getvalue(tmp);
	if (!(ft_isalpha(*tmp) || *tmp == '_') || foundchar('?', tmp) || (*tmp >= '0' && *tmp <= '9') || *tmp == '=')
	{
		tmp[s] = '=';
		write(2, "export: \'", 10);
		write(2, tmp, ft_strlen(tmp));
		write(2, "\' not a valid identifier\n", 26);
		return ;
	}
	if (ft_strncmp(env->name, tmp, ft_strlen(tmp)))
	{
		while (env->next && ft_strncmp(env->next->name, tmp,
				ft_strlen(tmp)))
			env = env->next;
	}
	if (!env->next)
		add_env(env, tmp);
	if (s > 0)
		env->next->value = ft_strdup(tmp + s + 1, 2);
}

int	ft_export(char **command, t_env *env)
{
	int		i;

	i = 1;
	if (!command[i])
		print_export(env);
	while (command[i])
	{
		getnewvar(ft_strdup(command[i], 2), env);
		i++;
	}
	return (0);
}