#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
char *OLDPWD;

int	check_option(char *str)
{
	if (!strncmp(str, "-P", 2) || !strncmp(str, "-L", 2)) // 함수 만들어서 바꿔야 함
		return (TRUE);
	return (FALSE);
}

void	using_environment_value(void)
{
	int flag;
	t_list	*envpl;
	t_envp	*envp;
	char	*path;

	path = NULL;
	flag = 0;
	envpl = g_minishell.envp->next;
	while (envpl)
	{
		envp = (t_envp *)envpl->data;
		if (!ft_strcmp(envp->key, "HOME"))
		{
			path = envp->value;
			flag = 1;
			break ;
		}
		envpl = envpl->next;
	}
	if (!path && !flag)
		write(2, "bash: cd: HOME not set\n", 23);
}

void	non_using_environment_value(void)
{
	chdir("/Users/hena");
}	//바꿔야할 듯

int home_check(char *argv[])
{
	if (!*argv)
	{
		using_environment_value();
		return (TRUE);
	}
	if (ft_strcmp("~", *argv))
	{
		non_using_environment_value();
		return (TRUE);
	}
	return (FALSE);
}

void old_pwd()
{
	int	flag;
	t_list	*envpl;
	t_envp	*envp;
	char	*path;

	flag = 0;
	envpl = g_minishell.envp->next;
	while (envpl)
	{
		envp = (t_envp *)envpl->data;
		if (!ft_strcmp(envp->key, "OLDPWD") && envp->value)
		{
			path = envpl->value;// 바뀔 위치
			envpl->value = getcwd(NULL, 256);// 현재 위치
			flag = 1;
			chdir(path);
			free(path);
			break ;
		}
		envpl = envpl->next;
	}
	if (!path && !flag)
		write(2, "bash: cd: OLDPWD not set\n", 25);
}

void	ft_cd(t_exec *data)
{
	int state;
	char *prev;
	char **argv;
	// data->/argv++;
	data = argv;
	if (home_check(argv))
		return ;
	if (check_option(*argv))
	{
		printf("option 이 있음\n");
		exit(1);
	}
	if (!strcmp(*argv, "-"))
	{
		printf("OLD PATH 실행\n");
		old_pwd();
		return ;
	}
	prev = getcwd(NULL, 256);
	state = chdir(*argv);
	if (!state)
	{
		printf("success\n");
	}
	else
		printf("-bash: cd: directory: No such file or directory\n");
	printf("\n%s\n", getcwd(NULL, 100));
}

int main()
{
	
}