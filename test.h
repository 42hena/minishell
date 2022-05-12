#ifndef TEST_H
# define TEST_H

typedef enum e_node_type
{
	TYPE_IN_OVERWRITE,
	TYPE_OUT_OVERWRITE,
	TYPE_HEREDOC,
	TYPE_OUT_APPEND,
	TYPE_CMD,
	TYPE_ETC
}	t_node_type;

typedef struct s_node
{
	t_node_type		type;
	char			*str;
	int				heredoc_idx;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}	t_list;

t_node	*create_node(char *data)
{
	t_node	*tmp;

	tmp = calloc(sizeof(t_node), 1);
	tmp->str = data;
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

t_list	*create_list(void *data)
{
	t_list	*new;

	new = calloc(sizeof(t_list), 1);
	new->data = data;
	new->next = NULL;
	return (new);
}

void	print_list(t_list *head)
{
	t_node	*node;

	while (head != NULL)
	{
		node = head->data;
		printf("type[%d] str[%s]\n", node->type, node->str);
		head = head->next;
	}
}
#endif
