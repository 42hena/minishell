#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#define READ 0
#define WRITE 1
int main()
{
	int		fd[2];
	int		pid;
	char	buf[256];
	if (pipe(fd) == -1)
		printf("tq");
	pid = fork();
	if (pid > 0)	// parent
	{
		close(fd[READ]);	//close child
		printf("fd[WRITE] %d\n", fd[WRITE]);
		int a = dup2(fd[WRITE], STDOUT_FILENO);
		write(fd[WRITE], "test", 4);

		sleep(5);
	}
	else if (pid == 0)
	{
		close(fd[WRITE]);
		printf("fd[READ] %d\n", fd[READ]);
		int n = read(fd[READ], buf, 255);
		printf("n:%d\n", n);
		buf[n] = 0;
		printf("%s", buf);
	}
}
