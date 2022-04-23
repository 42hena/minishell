#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

static void	check_file_exist(char **filename)
{
	int	count = 0;
	char *tmpfile;

	while (!access(*filename, F_OK))
	{
		int size = ft_strlen(*filename);
		free(*filename);
		*filename = (char *)malloc(sizeof(char) * size + 2);
		filename[size + 1] = 0;
		strcat(*filename, "0");
	}
	printf("now file name: %s\n", *filename);
}

//임시 파일 이름좀 파싱해주셈 ㅠㅠ
void redirect_heredoc(char *end_string, char **filename)
{
	int fd;
	// 파일 이름 하나씩 넣어줘야할 듯
	check_file_exist(filename);
	fd = open(*filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	printf("now fd%d\n", fd);
	// fd 에러 필요해 보임
	if (fd < 0)
		exit(0);
	/*
	while (!strcmp(end_string, readline))
		write(fd, buf, strlen(buf));
	*/
	close(fd);
}

int main()
{
	char *filename;
	
	filename = (char *)malloc(sizeof(char) * 9);
	filename[8] = 0;
	strcpy(filename, "donghyki");
	
	redirect_heredoc("end", &filename);
}

