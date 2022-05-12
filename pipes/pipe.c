#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int status;
struct link
{
	struct link *next;
	char *cmd;
	char **argv;
	int pid;
	int prev_readpipe_fd;
	//tree 필요
};

void	change_connection_pipe_parent(struct link *cmd, int *p)
{
	close(p[1]); // write close
	if (cmd->prev_readpipe_fd != 0)
	{
		dup2(p[0], 3);
		close(p[0]);
	}
}

void	change_connection_pipe_child(struct link *cmd, int *p)
{
	close(p[0]); // read close 현재꺼 닫기	
	if (cmd->next)
		dup2(p[1], 1);
	close(p[1]);
	if (cmd->prev_readpipe_fd)
	{
		dup2(cmd->prev_readpipe_fd, 0);
		close(cmd->prev_readpipe_fd);
	}
}

/*
 * 다시 생각해야할 듯
 */
void	wait_all_child(struct link *head)
{
	int	pid;
	int	wpid;
	struct link *copy;
	int	cnt;
	int tmp;
	/*printf("pid[%d]\n", head->next->pid);	
	waitpid(head->next->pid, &status, 0);
	printf("[%d]\n", status);
*/
	cnt = 0;
	copy = head;
	while (copy->next)
	{
		cnt++;
		copy = copy->next;
		wpid = copy->pid;
	}
	while (head)
	{
		pid = wait(&status);
		if (pid == wpid)
			tmp = status;
		head = head->next;
	}
	printf("%d %d %d\n", pid, wpid, status);
}

void	fork_pipe(t_list *link, char **envp)
{
	int	p[2];
	t_list	*head;

	head = link;
	if (!link->next)
	{
		alone_cmd(link);
		return ;
	}
	while (link)
	{
		pipe(p);
		link->pid = fork();
		if (link->pid < 0)
			exit(0);
		else if (link->pid > 0)
			change_connection_pipe_parent(link, p);
		else
		{
			change_connection_pipe_child(link, p);
			execve(link->cmd, link->argv, envp);
		}
		if (link->next)
			link->next->prev_readpipe_fd = 3;
		link = link->next;
	}
	close(3);
	wait_all_child(head);
}

/* test 로직
struct link *init_link()
{
	struct link *cmd;
	
	cmd = (struct link*)malloc(sizeof(struct link));
	cmd->next = NULL;
	cmd->cmd = NULL;
	cmd->argv = 0;
	cmd->prev_readpipe_fd = 0;
	
	return cmd;
}

int main(int argc, char **argv, char **envp)
{
	struct link *new;
	struct link *head;
	
	new = init_link();
	
	head = new;
	new->cmd =(char *)malloc(sizeof(char) * 12);
	new->cmd = strcpy(new->cmd, "/bin/cat");
	
	//printf("%s", new->cmd);
	
	new->argv = (char **)malloc(sizeof(char *) * 3);
	new->argv[0] = (char *)malloc(sizeof(char) * 4);
	strcpy(new->argv[0], "cat");
	//printf("%s", new->argv[0]);

	//new->argv[1] = (char *)malloc(sizeof(char) * 4);
	//strcpy(new->argv[1], "100");
	new->argv[1] = NULL;

	new = init_link();

	head->next = new;
	new->cmd =(char *)malloc(sizeof(char) * 8);
	new->cmd = strcpy(new->cmd, "/bin/ls");
	new->argv = (char **)malloc(sizeof(char*) * 3);
	new->argv[0] = (char *)malloc(sizeof(char) * 5);
	strcpy(new->argv[0], "ls");
	//new->argv[1] = (char *)malloc(sizeof(char) * 5);
	//strcpy(new->argv[1], "HOME");
	/*new->argv[2] = (char *)malloc(sizeof(char) * 6);
	strcpy(new->argv[2], "hello");
	new->argv[1] = NULL;

	fork_pipe(head, envp);
}*/
