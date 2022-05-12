#include <stdio.h>
#include <unistd.h>

#ifndef BOOL
# define BOOL

# define TRUE 1
# define FALSE 0
#endif

static void	ft_print_export(char *key, char *value)
{
	write(1, "declare -x ", 11);
	write(1, key, ft_strlen(key));
	if (value)
	{
		write(1, "=\"", 2);
		write(1, value, ft_strlen(value));
		write(1, "\"\n", 2);
	}
}

static void	show_export_list(void)
{
	int	i;
	t_list	*envpl;
	t_envp	*envp;

	envpl = g_minishell.envp->next;
	while (envpl)
	{
		envp = (t_envp *)envpl->data;
		ft_print_env(envp->key, envp->value);
		envpl++;
	}
	g_state.status = 0;
}

int	is_in_equal(char *str)
{
	while (*str)
		if (*str == '=')
			return (TRUE);
	return (FALSE);
}

void	find_or_change_envp(char *str)
{
	t_list	*envpl;
	t_envp	*envp;
	int	flag;
	char **array;

	envpl = g_minishell.envp->next;
	flag = 0;
	if (!*str)
		return ;
	//1. = 유무
	flag = is_in_equal(*str);
	array = split(str, '=');
	// if (flag)
	// 	add_key();
	// else
	// 	add_key_value();
	//2. split
	flag = 0;
	while (envpl)
	{
		envp = (t_envp *)envpl->data;
		// split 기준으로
		if (!ft_strcmp(envp->key, array[0]))
		{
			flag = 1;
			if ()
			{

			}	
		}
		envpl++;
	}
}

static int	is_valid_idenfier(char *str, int index)
{
	int i;

	if (!((is_small_alpha(*str) || is_big_alpha(*str) || *str == '_')))
		return (FALSE);
	i = 1;
	while (*str && i < index)
	{
		if (!((is_small_alpha(*str) || is_big_alpha(*str) || \
		is_integer(*str) || *str == '_')))
			return (FALSE);
		str++;
		++i;
	}
	return (TRUE);
}

int	get_equal_index(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		++i;
	}
	if (ft_strlen(str) == i)
		return (-1);
	return (i);
}

int	divide_argv(char **argv)
{
	int err_flag;
	int index;

	err_flag = 0;
	while (*argv)
	{
		index = get_equal_index(*argv);
		// = 전까지만 확인해야함.... split이 먼저
		if (!is_valid_idenfier(*argv, index))
		{
			write(2, "export: `", 9);
			write(2, *argv, ft_strlen(*argv));
			write(2, "': not a valid identifier\n", 26);
			err_flag = 1;
		}
		else
			find_or_change_envp(*argv);
		argv++;
	}
	return (err_flag);
}

void	export(char **argv)
{
	argv++;
	if (!*argv)
		show_export_list();
	else
		divide_argv(argv);
}
