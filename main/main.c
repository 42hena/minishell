#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includehena/test.h"
#include "../includehena/main_logic.h"

extern t_minishell g_minishell;

int main() 
{
	t_list	*head = NULL;
	t_list	*new = NULL;
	t_node	*node = NULL;
	t_exec	*exec = NULL;

	g_minishell.is_ended = 0;
	g_minishell.envp = NULL;
	g_minishell.exec = NULL;


	// g_minishell.exec;
	new = calloc(1, sizeof(t_list));
	exec = calloc(1, sizeof(t_exec));
	create_s_ll(strdup("cat"), strdup("/bin/cat"));
	
	new->data = exec;
	create_s_ll(strdup("cat"), strdup("/bin/cat"));
	add_list_back(&g_minishell.exec, new);

	new = calloc(1, sizeof(t_list));
	node = create_node(strdup("cat"));
	node->type = TYPE_CMD;
	new->data = node;
	add_list_back(&head, new);

	new = calloc(1, sizeof(t_list));
	node = create_node(strdup("ls"));
	node->type = TYPE_CMD;
	new->data = node;
	add_list_back(&head, new);

	main_logic(head);
	// print_list(head);
}