#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *values[] = { "avocado", "apple", "ananas", "orange", "banana", "kiwi" };

int cmpints(const void *a, const void *b)
{
	return ( *(int*)a - *(int*)b );
}

int cmpstrs(const void *a, const void *b)
{
	return strcmp( *(const char**)a, *(const char**)b );
}

int main(int argc, char *argv[])
{
	printf("Before sorting the list is:\n");
	for (int i = 0; i < 5; i++) {
		printf("%s ", values[i]);
	}

	qsort(values, 5, 4, cmpstrs);

	printf("\n\nAfter sorting the list is:\n");
	for (int i = 0; i < 5; i++) {
		printf("%s ", values[i]);
	}

	getchar();

	return(0);
}