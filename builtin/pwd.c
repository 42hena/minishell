#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
* getcwd free  file 크기 알아내야 함 size값 필요
* 뒤에 뭐가 오던 무시할 예정
*/
#define TRUE 1
#define FALSE 0

static size_t ft_strlen(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	write(fd, s, len);
	write(fd, "\n", 1);
}

/*
 *	option 무시이므로 뒤에 와도 무시할 예정
 */

void	ft_pwd(char **argv)
{
	char	*now_path;
	int		ret;

	now_path = NULL;
	argv++;
	now_path = getcwd(NULL, 256);
	if (now_path == NULL) // 실패시인데 이친구 어케 처리해야할까...
	{
		ft_putendl_fd("fail getcwd()\n", 2);
		exit(1);
	}
	ft_putendl_fd(now_path, 1);
	g_minishell.status = 0; //확인하기
	free(now_path);
}

int main()
{
	char * str[] = {"test", NULL};
	ft_pwd(str);
}
