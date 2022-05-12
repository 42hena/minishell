#ifndef ERASE
# define ERASE

typedef enum e_node_type
{
	TYPE_IN_OVERWRITE,
	TYPE_OUT_OVERWRITE,
	TYPE_HEREDOC,
	TYPE_OUT_APPEND,
	TYPE_CMD,
	TYPE_ETC
}				t_node_type;

typedef struct s_node
{
	struct s_node	*left;
	struct s_node	*right;
	t_node_type		type;
	char			*data;
}				t_node;

typedef struct s_ast
{
	struct s_node	*root;
}				t_ast;
#endif

void	excute_cmd(char **argv)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		printf("error\n");
	else if (pid == 0)
		execve(cmd, argv, envpa);
}

static void	tree_traversal(t_node *tree, int *input_cnt)
{
	if (!tree)
		return ;
	if (tree->type == TYPE_IN_OVERWRITE) //  <
	{
		input(tree->right->data, 3);
		*input_cnt--;
	}
	else if (tree->type == TYPE_OUT_OVERWRITE) // >
		output(tree->right->data, 4);
	else if (tree->type == TYPE_HEREDOC) // <<
	{	
		
		*input_cnt--;
	}
	else if (tree->type == TYPE_OUT_APPEND) // >>
		output_append(tree->right->data, 4);
	else if (tree->type == TYPE_CMD)
	{
		close(255);
		
		close(3);
		close(4);
	}
	tree_traversal(tree->left);
}

int	get_input_count(t_node *iter)
{
	int	cnt;

	cnt = 0;
	while (iter)
	{
		if (iter->data == TYPE_IN_OVERWRITE
			|| iter->data == TYPE_HEREDOC)
			cnt++;
	}
	return (cnt);
}

void	alone_cmd(t_list *link)
{
	int cnt;

	cnt = get_input_count(((t_node)link->data)->root);
	tree_traversal(((t_node)link->data)->root, &cnt);
}
