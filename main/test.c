#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includehena/test.h"

t_exec	*create_s_ll(char *data, char *path)
{
	t_exec	*tmp;

	tmp = calloc(sizeof(t_exec), 1);
	tmp->cmd = data;
	tmp->cmd_address = path;
	tmp->root = NULL;
	return (tmp);
}

t_node	*create_node(char *data)
{
	t_node	*tmp;

	tmp = calloc(sizeof(t_node), 1);
	tmp->file_name = data;
	return (tmp);
}

t_list	*get_last_list(t_list *list)
{
	t_list	*last;

	if (list == NULL)
		return (NULL);
	last = list;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	add_list_back(t_list **list, t_list *new)
{
	t_list	*last;

	if (list == NULL || new == NULL)
		return ;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	last = get_last_list(*list);
	last->next = new;
}

void	echoctl_on(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	echoctl_off(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}