/*

Prints 4 most common words from text file.
Linked list one-directional, if word is printed, set count to zero, so it doesnt print anymore.
TODO: Linked list bi-directional, possibility to simply dispose most common word node after printout (node_to_dispose->previous->next = node_to_dispose->next)

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int count;
	char *word;
	node *next;
};

void error(int type)
{
	switch (type) {
		case 0:
			printf("Error opening file!\n");
			break;
		case 1:
			printf("Error allocating memory!\n");
			break;
		default:
			printf("An error occured!\n");
			break;
	}

	exit(1);
}

node *add_word(node *word_list, char *word)
{
	node *iterator = word_list;

	if (strcmp(word, "") == 0)
		return word_list;

	while (iterator != NULL) {
		if (strcmp(iterator->word, word) == 0) {
			iterator->count++;

			return word_list;
		}

		iterator = iterator->next;
	}

	node *new_word = (struct node *)malloc(sizeof(node));
	if (!new_word)
		error(1);

	new_word->word = (char *)malloc(strlen(word) + 1);
	if (!new_word->word)
		error(1);

	strcpy(new_word->word, word);

	new_word->count = 1;
	new_word->next = word_list;

	word_list = new_word;

	return word_list;
}

node *find_words(FILE *fp, node *word_list)
{
	char c;
	size_t len = 0;
	size_t buf = 255;
	char *word = (char *)malloc(sizeof(char) * buf);
	if (!word)
		error(1);

	while ((c = getc(fp)) != EOF) {
		if (c == ' ' || c == '\n' || c == '.' || c == ',' || c == '!' || c == '?') {
			word[len] = '\0';
			len = 0;

			word_list = add_word(word_list, word);
		} else {
			word[len++] = c;
			
			if (len == buf) {
				word = (char *)realloc(word, sizeof(char)* (buf *= 2));
				if (!word)
					error(1);
			}
		} 
	}

	if (len > 0) {
		word[len] = '\0';
		len = 0;

		word_list = add_word(word_list, word);
	}

	free(word);

	return word_list;
}

void print_list(node *word_list)
{
	node *iterator = word_list;
	node *current = NULL;

	for (int i = 0; i < 4; i++) {
		int highest = 0;

		while (iterator != NULL) {
			if (iterator->count > highest) {
				highest = iterator->count;
				current = iterator;
			}

			if (iterator->next == NULL) {
				printf("Words found: %d | %s \n", current->count, current->word);
				current->count = 0;
			}

			iterator = iterator->next;
		}

		iterator = word_list;
	}
}

void free_list(node *word_list)
{
	node *tmp;

	while (word_list != NULL)
	{
		tmp = word_list;
		word_list = word_list->next;
		free(tmp->word);
		free(tmp);
	}

}

int main(int argc, char *argv[])
{
	FILE *fp;
	node *word_list = NULL;

	fp = fopen("words.txt", "r");
	if (!fp)
		error(1);

	word_list = find_words(fp, word_list);

	print_list(word_list);
	free_list(word_list);

	fclose(fp);
	getchar();

	return 0;
}