#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
char *OLDPWD;

int check_option(char *str)
{
	if (!strncmp(str, "-P", 2) || !strcmp(str, "-L", 2))
		return (TRUE);
	return (FALSE);
}

void cd(char *argv[])
{
	int state;

	if (check_option(argv[0]))
	{
		printf("option HI\n");
		return ;
	}
	// -
	if (!strcmp(argv[0], "-"))
		printf("OLD PATH");
		

	// --
	state = chdir(str);
	if (!state)
		printf("success");
	else
		printf("-bash: cd: directory: No such file or directory\n");
	printf("\n%s\n", getcwd(NULL, 100));
}

// - --어떻게 처리할건지 juhur님이랑 의견 나누기
//
int main(int argc, char *argv[])
{
	char * str[] = {"--", NULL};
	cd(str);
}
