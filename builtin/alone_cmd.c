void	excute_cmd(char **argv)
{
	int	pid;

	pid = fork();
	if (pid < 0) // error
		printf("error\n");
	else if (pid == 0)
		execve(cmd, argv, envpa);
}

void	alone_cmd(char **argv)
{
	if (!strcmp(*argv, "cd"))
		ft_cd(argv);
	else if (!strcmp(*argv, "echo"))
		ft_echo(argv);
	else if (!strcmp(*argv, "pwd"))
		ft_pwd(argv);
	else if (!strcmp(*argv, "exit"))
		ft_exit(argv);
	else if (!strcmp(*argv, "env"))
		ft_env(argv);
	else if (!strcmp(*argv, "export"))
		ft_export(argv);
	else if (!strcmp(*argv, "unset"))
		ft_unset(argv);
	else
		excute_cmd(argv);
}
