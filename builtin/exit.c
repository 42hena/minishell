#include <stdio.h>
/*
*	exit 1 2 3 exit: too many arguments
*	exit 1 a b exit: too many arguments
*	exit a b c : numeric argument required
*/

void	ft_exit(char **str, int flag)
{
	if (str == NULL)
		printf("exit\n");


	exit(0);
}
