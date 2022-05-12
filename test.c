#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test.h"


int main() {
	t_list	*head = NULL;
	t_list	*new = NULL;
	t_node	*node = NULL;

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

	// main_logic(head);
	// print_list(head);
}