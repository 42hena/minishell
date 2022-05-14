#include "../includehena/test.h"
#include "../includehena/built_in.h"
#include "../includehena/redirect.h"

extern t_minishell g_minishell;

static void	excute_cmd(t_exec *data)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
		execve(data->cmd_address, data->argv, g_minishell.envp);
	else
		wait(0);
}

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
	// else if (!ft_strcmp(data->argv[0], "cd"))
	// 	ft_cd(data, 0);
	if (!ft_strcmp(data->argv[0], "cd"))
		ft_pwd(data, 0);
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
	else if (tree->type == TYPE_CMD)
		select_cmd(data);
	tree_traversal_alone(tree->left, data);
}

// int	get_input_count(t_node *iter)
// {
// 	int	cnt;

// 	cnt = 0;
// 	while (iter)
// 	{
// 		if (iter->file_name == TYPE_IN_OVERWRITE
// 			|| iter->file_name == TYPE_HEREDOC)
// 			cnt++;
// 		iter = iter->left;
// 	}
// 	return (cnt);
// }

// void	alone_cmd(t_exec *data)
// {
// 	// int cnt;
// 	// cnt = get_input_count(data->root);
// 	tree_traversal_alone(data->root, data);
// }
