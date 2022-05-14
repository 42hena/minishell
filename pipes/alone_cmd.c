#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> //// TODO:: 헤더 삭제 해야함.
#include "../includehena/test.h"
#include "../includehena/built_in.h"
#include "../includehena/redirect.h"

extern t_minishell g_minishell;

static void	excute_cmd(t_exec *data)
{
	int	pid;
	int state;

	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
		execve(data->cmd_address, data->argv, NULL); // TODO:: envp 2차원 배열로 넣어줘야하므로 NULL로 일단 대체
	else
	{
		wait(&state);
		g_minishell.state = state;
	}
}

//TODO:: 나중에 strcmp를 ft_strcmp로 고치고 헤더 추가해야 함
static void	select_cmd(t_exec *data)
{
	// if (!ft_strcmp(data->argv[0], "cd"))
	// 	ft_cd(data);
	// else if (!ft_strcmp(data->argv[0], "cd"))
	// 	ft_cd(data);
	// else if (!ft_strcmp(data->argv[0], "cd"))
	// 	ft_cd(data, 0);
	// else if (!ft_strcmp(data->argv[0], "cd"))
	// 	ft_cd(data, 0);
	// else if (!ft_strcmp(data->argv[0], "cd"))
	// 	ft_cd(data, 0);
	
	if (!strcmp(data->argv[0], "pwd"))
		ft_pwd(data, 0);
	else if (!strcmp(data->argv[0], "unset"))
		ft_unset(data, 0);
	else
		excute_cmd(data);
}

void	tree_traversal_alone(t_node *tree, t_exec *data)
{
	if (!tree)
		return ;
	if (tree->type == TYPE_IN_OVERWRITE) //  <
		input(tree->right->file_name, 0);
	else if (tree->type == TYPE_OUT_OVERWRITE) // >
		output(tree->right->file_name, 1);
	else if (tree->type == TYPE_HEREDOC) // <<
		here_doc(tree->right->heredoc_idx, 0);
	else if (tree->type == TYPE_OUT_APPEND) // >>
		output_append(tree->right->file_name, 1);
	// else if (tree->type == TYPE_CMD)
	// 	select_cmd(data);
	tree_traversal_alone(tree->left, data);
}
