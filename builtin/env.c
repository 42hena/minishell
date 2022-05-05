#include <unistd.h>

static int ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	ft_print_env(char *key, char *value)
{
	write(1, key, ft_strlen(key));
	write(1, "=", 1);
	write(1, value, ft_strlen(value));
	write(1, "\n", 1);
}

/*
 * flag 및 다른게 들어오면 어떻게 처리할지 고민하기
 */

void	ft_env(char **argv)
{
	int	i;
	t_list	*envpl;
	t_envp	*envp;

	argv++;
	if (*argv)
	{
		write(2, "env is only read one argument\n", 30);
		exit(0); /// ? 뭘로 처리하냐 ㅋㅋㅋㅋㅋㅠ.ㅠ
	}
	// g_state.envpl; 연결리스트
	envpl = g_minishell.envp;
	while (envpl)
	{
		envp = (t_envp *)envpl->data;
		if (envp->value)
			ft_print_env(envp->key, envp->value);
		envpl++;
	}
	g_state.exit_status = 0;
}
