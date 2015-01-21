#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	node *left;
	node *right;
};

node *new_node(int data)
{
	node *new_node = (struct node *)malloc(sizeof(node));
	if (!new_node)
		exit(1);

	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

node *insert(node *root, int data)
{
	if (root == NULL) {
		root = new_node(data);
		return root;
	} else if (data <= root->data) {
		root->left = insert(root->left, data);
	} else {
		root->right = insert(root->right, data);
	}

	return root;
}

node *search(node *root, int data) {
	if (root == NULL) {
		return 0;
	} else if (root->data == data) {
		return root;
	} else if (data <= root->data) {
		return search(root->left, data);
	} else {
		return search(root->right, data);
	}
}

int deallocate_tree(node *root)
{
	if (root == NULL)
		return 0;

	deallocate_tree(root->left);
	deallocate_tree(root->right);

	free(root);
}

node *find_min(node *root)
{
	if (root == NULL)
		return 0;

	while (root->left != NULL)
		root = root->left;

	return root;
}

//same logic as find_min written recursively
node *find_max(node *root)
{
	if (root == NULL)
		return 0;
	else if (root->right == NULL)
		return root;

	return find_max(root->right);
}

node *remove_node(node *root, int data)
{
	if (root == NULL)
		return root;
	else if (data < root->data)
		root->left = remove_node(root->left, data);
	else if (data > root->data)
		root->right = remove_node(root->right, data);
	else {
		//case 1, 2, 3, 4: leaf node (no child), only right child, only left child, two children
		if (root->left == NULL && root->right == NULL) {
			free(root);
			root = NULL;
		} else if (root->left == NULL) {
			node *tmp = root;
			root = root->right;
			free(tmp);
		} else if (root->right == NULL) {
			node *tmp = root;
			root = root->left;
			free(tmp);
		} else {
			node *tmp = find_min(root->right);
			root->data = tmp->data;
			root->right = remove_node(root->right, tmp->data);
		}
	}

	return root;
}

int main(int agrc, char *argv[])
{
	node *root = NULL;
	node *found;

	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 5);
	root = insert(root, 40);

	root = remove_node(root, 20);

	found = search(root, 20);
	if (found)
		printf("Found: %d, left: %p, right: %p\n", found->data, found->left, found->right);


	printf("Minimum: %d\n", find_min(root)->data);
	printf("Maximum: %d\n", find_max(root)->data);

	deallocate_tree(root);

	getchar();

	return 0;
}
