#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

typedef struct list{
	struct list *next;
	char *key;
	char *value;
}t_list;
typedef struct test{
	t_list	*envl;
}t_test;

t_test g_stat;

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	get_env_array_count(void)
{
	t_list	*envpl;
	int		count;

	count = 0;
	envpl = g_stat.stat;
	envpl = envpl ->next;
	while (envpl)
	{
		if (envpl->value)
			count++;
		envpl++;
	}
	return (count);
}

char	**dynamic_allocate_double(int count)
{
	char	**envp_array;

	envp_array = (char **)malloc(sizeof(char *) * count + 1);
	if (!envp_array)
		return (NULL);
	envp_array[count] = NULL;
	return (envp_array);
}

void	dynamic_allocate_one(char ***envp_array)
{
	t_list	*envpl;
	int		length;
	int		i;

	envpl = g_stat.stat;
	envpl = envpl ->next;
	i = 0;
	while (envpl)
	{
		length = ft_strlen(envpl->key) + ft_strlen(envpl->value) + 2;
		*envp_array[i] = (char *)malloc(sizeof(char) * length);
		ft_strlcpy(*envp_array[i], envpl->key);
		ft_strlcat(*envp_array[i], "=");
		ft_strlcat(*envp_array[i], envpl->value);
		envpl++;
		++i;
	}
}

char	**make_env_array(void)
{
	char	**envp_array;
	int		envp_array_count;

	envp_array_count = get_envp_array_count();
	envp_array = dynamic_allocate_double(envp_array_count);
	if (!envp_array)
	{
		//free작업 들어가야 할 듯
		exit(0);
	}
	dynamic_allocate_one(&envp_array);
	return (envp_array);
}


t_list	*init_list()
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	new->next = NULL;
	new->key = NULL;
	new->value = NULL;
	return (new);
}

int main()
{
	t_list	*envpl;
	t_list	*new;

	new = init_list();
	envpl = new;

//---
	new = init_list();
	new->key = (char *)malloc(sizeof(char) * 2);
	new->key = strcpy(new->key, "a");
	new->value = (char *)malloc(sizeof(char) * 2);
	new->value = strcpy(new->value, "a");
	envpl->next = new;
//-
	new = init_list();
	new->key = (char *)malloc(sizeof(char) * 2);
	new->key = strcpy(new->key, "b");
	new->value = (char *)malloc(sizeof(char) * 2);
	new->value = strcpy(new->value, "b");
	envpl->next = new;

	g_stat.envl = envpl;
	make_env_array();
}
