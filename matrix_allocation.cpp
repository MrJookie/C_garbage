#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Greatest Common Divisor - release x64 slow_gcd(11111184467, 11111184468) : 11.6s
unsigned slow_gcd(unsigned a, unsigned b)
{
	if (a == 0)
		return b;

	while (b != 0) {
		(a > b) ? a -= b : b -= a;
	}

	return a;
}

//Greatest Common Divisor - release x64 gcd(11111184467, 11111184468) : 0.00013s
unsigned gcd(unsigned a, unsigned b)
{
	while (b != 0) {
		unsigned r = a % b;
		a = b;
		b = r;
	}

	return a;
}

//Least Common Multiple
int lcm(int a, int b)
{
	int divider = gcd(a, b);
	if (divider == 0)
		return (a * b);

	return (a * b) / divider;
}

int **allocate_matrix(int n, int m)
{
	int **ptr = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++) {
		ptr[i] = (int *)malloc(m * sizeof(int));
		if (!ptr[i])
			exit(1)
	}
	
	if (!ptr)
		exit(1);

	return ptr;
}

/*
void insert(int **ptr, int n, int m, int num)
{
	int *p = ptr[n] + m;
	*p = num;
}
*/

void matrix_calculation(int **ptr, int n, int m, int(*gcd_or_lcm)(int, int))
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int *p = ptr[i] + j;
			*p = (*gcd_or_lcm)(i + 1, j + 1);
		}
	}
}

void print_matrix(FILE *fp, int **ptr, int n, int m)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!fp)
				printf("%4d ", *(ptr[i] + j));
			else
				fprintf(fp, "%4d ", *(ptr[i] + j));
		}
		if (!fp)
			printf("\n");
		else
			fprintf(fp, "\n");
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf("Usage: %s {-nsn | -nsd } [-f output] n [m]", argv[0]);
		exit(1);
	}

	FILE *fp = NULL;
	int n = 0; //rows
	int m = 0; //cols

	if (strcmp(argv[2], "-f") == 0) {
		fp = fopen(argv[3], "w");
		if (!fp)
			exit(1);

		n = atoi(argv[4]);

		if (argv[5] > 0)
			m = atoi(argv[5]);
		else
			m = atoi(argv[4]);
	} else {
		n = atoi(argv[2]);

		if (argv[3] > 0)
			m = atoi(argv[3]);
		else
			m = atoi(argv[2]);
	}

	int **matrix = allocate_matrix(n, m);

	if (strcmp(argv[1], "-lcm") == 0) {
		matrix_calculation(matrix, n, m, lcm);
	} else if (strcmp(argv[1], "-gcd") == 0) {
		matrix_calculation(matrix, n, m, gcd);
	}

	print_matrix(fp, matrix, n, m);

	for (int i = 0; i < n; i++)
		free(matrix[i]);

	free(matrix);

	if (fp)
		fclose(fp);

	return 0;
}
