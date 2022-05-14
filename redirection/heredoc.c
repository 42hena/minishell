#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../includehena/test.h"
/*
임시 파일을 이용한 here_doc 처리
	1.	O_WRONLY, O_CREAT, O_TRUNC 모드 및 0644 권한으로 임시 파일 생성
	2.	limiter가 나오기 전까지 임시 파일에 기록
	3.	limiter를 만나면 기록을 중지하고 임시 파일을 닫기
	4.	O_RDONLY 모드로 임시 파일 다시 열기
	5.	dup2를 통해 표준 입력을 임시 파일로 돌리기
	6.	임시 파일 닫기
*/


/*
 * file 유무 확인
 */

extern t_minishell g_minishell;

/*
static void	check_file_exist(char **filename)
{
	char *tmpfile;
	int	size;

	size = ft_strlen(filename);
	tmpfile = (char *)malloc(sizeof(char) * size + 1);
	strcpy(tmpfile, filename);
	while (!access(*filename, F_OK))
	{
		size = ft_strlen(*filename);
		free(*filename);// 부가적인거
		realloc(*filename, sizeof(char) * size + 1);
		filename[size] = 0;
		strcat(*filename, "");
	}
	printf("now file name: %s\n", *filename);
}*/

//임시 파일 이름좀 파싱해주셈 ㅠㅠ
/*
void redirect_heredoc(char *end_string, char **filename)
{
	int fd;
	// 파일 이름 하나씩 넣어줘야할 듯
	check_file_exist(filename);
	fd = open(*filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	printf("now fd%d\n", fd);
	// fd 에러 필요해 보임
	if (fd < 0)
		exit(1);
	close(fd);
}*/

void	here_doc(int index, int count)
{
	t_heredoc	*iter;
	int			fd;
	int			i;

	i = -1;
	iter = g_minishell.heredoc;
	while (++i < index)
		iter = iter->next;
	fd = open(iter->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		exit(1);
	dup2(fd, 0);
	close(fd);
}
