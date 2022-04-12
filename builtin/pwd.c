#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
* getcwd free  file 크기 알아내야 함 size값 필요
*/
#define TRUE 1
#define FALSE 0
static int check_option(char *str)
{
	if (!strcmp(str, "-P") || !strcmp(str, "-L"))
		return (TRUE);
	return (FALSE);
}

void	ft_pwd(char **argv)
{
	char	*now_path;
	int		ret;

	ret = 0;
	if (argv[0] != NULL)
		ret = check_option(argv[0]);
	if (ret)
	{
		printf("option ERROR\n");
		return ;
	}
	now_path = getcwd(NULL, 256);
	if (now_path == NULL)
		return ;
	printf("%s", now_path);
	free(now_path);
}

int main()
{
	char * str[] = {"test", NULL};
	ft_pwd(str);
}
