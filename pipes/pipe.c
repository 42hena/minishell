#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
struct link{
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
		dup2(cmd->prev_readpipe_fd, 0);
		close(cmd->prev_readpipe_fd);
	}
}

void	change_connection_pipe_child(struct link *cmd, int *p)
{
	close(p[0]); // read close
	if (cmd->next)
	{
		dup2(p[1], 1);
		close(p[1]);
	}
}

void	wait_all_child(struct link *head)
{
	while (head)
	{
		waitpid(head->pid, NULL, 0);
		head = head->next;
	}
}

void	fork_pipe(struct link *link)
{
	int p[2];
	int read_fd = 0;
	struct link *head;

	head = link;
	

	while (link)
	{
		pipe(p);
		link->pid = fork();
		if (link->next)
			link->next->prev_readpipe_fd = p[0];
		if (link->pid < 0)
			exit(0);
		else if (link->pid > 0){
			change_connection_pipe_parent(link, p);
		}
		else
		{
			change_connection_pipe_child(link, p);
			execve(link->cmd, link->argv, NULL);
			exit(0);
		}
		if (link->prev_readpipe_fd)
		{
			dup2(p[0], link->prev_readpipe_fd);
			close(p[0]);
		}
		link = link->next;
	}
	printf("end\n");
	//close(link->prev_readpipe_fd);
	wait_all_child(head);
	
}

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

int main()
{
	struct link *new;
	struct link *head;
	
	new = init_link();
	
	head = new;
	new->cmd =(char *)malloc(sizeof(char) * 8);
	new->cmd = strcpy(new->cmd, "/bin/ls");
	
	//printf("%s", new->cmd);
	
	new->argv = (char **)malloc(sizeof(char *) * 3);
	new->argv[0] = (char *)malloc(sizeof(char) * 3);
	strcpy(new->argv[0], "ls");
	//printf("%s", new->argv[0]);
	
	new->argv[1] = (char *)malloc(sizeof(char) * 4);
	strcpy(new->argv[1], "-al");
	new->argv[2] = NULL;

	new = init_link();

	head->next = new;
	new->cmd =(char *)malloc(sizeof(char) * 10);
	new->cmd = strcpy(new->cmd, "/bin/echo");
	new->argv = (char **)malloc(sizeof(char*) * 4);
	new->argv[0] = (char *)malloc(sizeof(char) * 5);
	strcpy(new->argv[0], "echo");
	new->argv[1] = (char *)malloc(sizeof(char) * 5);
	strcpy(new->argv[1], "test");
	new->argv[2] = (char *)malloc(sizeof(char) * 6);
	strcpy(new->argv[1], "hello");
	new->argv[3] = NULL;
	
	fork_pipe(head);	
}
