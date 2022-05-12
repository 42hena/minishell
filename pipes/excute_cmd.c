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

void	execute_cmd(t_node *tree)
{
	if (!tree)
		return ;
	// if (tree->type == TYPE_IN_OVERWRITE)
	// 	tree->right->data;
	if (tree->type == TYPE_OUT_OVERWRITE)
		output(tree->right->data);
	// else if (tree->type == TYPE_HEREDOC)
	// 	output(tree->right->data);
	else if (tree->type == TYPE_OUT_APPEND)
		output_append(tree->right->data);
	// else if (tree->type == TYPE_CMD)
	// 	select_cmd();
	execute_cmd(tree->left);
}
