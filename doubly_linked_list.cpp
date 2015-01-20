#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
	char *name;
	node *next;
	node *prev;
};

node *allocate_node(void)
{
	node *new_node = (struct node *)malloc(sizeof(node));
	if (!new_node)
		exit(1);

	return new_node;
}

void add_node(node *end, node *new_node, char *name)
{
	new_node->name = name;
	new_node->next = NULL;
	new_node->prev = end;
	end->next = new_node;
}

node *find_end(node *ptr)
{
	node *iter = ptr;

	while (iter->next != NULL)
		iter = iter->next;

	return iter;
}

int main(int argc, char *argv[])
{
	node *nodes = NULL;
	node *first;
	node *iter;

	//Allocate first node (head)
	first = (struct node *)malloc(sizeof(node));
	first->name = "Head";
	first->next = NULL;
	first->prev = NULL;
	nodes = first;

	for (int i = 0; i < 10; i++) {
		add_node(find_end(nodes), allocate_node(), "Lucas");
	}

	for (iter = nodes; iter; iter = iter->next) {
		printf("node: %s\n", iter->name);
	}

	getchar();

	return 0;
}