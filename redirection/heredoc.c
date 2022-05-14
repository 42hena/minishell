#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../includehena/test.h"

extern t_minishell g_minishell;

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
