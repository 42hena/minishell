#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
*	exit 1 2 3 exit: too many arguments exit 출력
*	exit 1 a b exit: too many arguments exit 출력
*	exit a b c : numeric argument required
*
*/

void	ft_exit_execute(char **argv, int pipeflag)
{
	int	ret;
	// 숫자라면
	if (check_all_integer(*argv))
	{
		if (pipe_flag)
			write(1, "exit\n", 5);
		ret = ft_atoi(*argv);
		argv++;
		if (*argv)
			print_exit_error(*argv, 0);
		// 번호 담아줘야할듯
	}
	else
	{
		print_exit_error(*argv, 1);
		// 번호 담아줘야할듯
	}
	exit(0);
}

void	ft_exit(char **argv, int pipeflag)
{
	int	i;

	argv++;
	if (*argv == NULL)
	{
		if (pipeflag)
			write(1, "exit\n", 5);
		// 번호도 삽입해야함
		exit(0);
	}
	else
		ft_exit_execute(argv, pipeflag);
}
