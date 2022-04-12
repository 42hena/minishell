#include <stdio.h> // test
#include <stdlib.h>
#include <string.h>
// strcmp함수 만들어야 함

#define TRUE 1
#define FALSE 0

static void	print_echo(char *argv[], int index, int flag)
{
	while (argv[index])
	{
		printf("%s", argv[index]);
		index++;
	}
	if (!flag)
		printf("\n");
}

/*
 *	전부 해석되서 왔다는 전재로 함
 *	NULL로 끝내야 될거 같습니다. ㅠㅠ 죄송합니다.
 */


// -n까지는 찾음
static int	check_option(char *str)
{
	int	i;

	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		++i;
	}
	return (TRUE);
}

static void	ft_echo(char *argv[])
{
	int		opt_flag;
	int		index;

	if (argv[0] == NULL)
	{
		printf("\n");
		return ;
	}
	index = 0;
	opt_flag = 0;
	if (!strncmp(argv[0], "-n", 2))// NULL일 경우 한번 생각해보기
	{
		if (check_option(argv[0]))
		{
			opt_flag = 1;
			index++;
		}
	}
	print_echo(argv, index, opt_flag);
}

// echo NULL이거 어케 처리 할거임?
// test시 여기에 해보심 될 듯
int main()
{
	char *str[] = { NULL};
	ft_echo(str);
}
