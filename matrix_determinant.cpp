/*
File:
1 2 3
4 -2 6
7 8 9
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void error(int type)
{
	switch (type) {
		case 0:
			printf("Error opening file!\n");
			break;
		case 1:
			printf("Matrix could not be allocated!\n");
			break;
		case 2:
			printf("Only square matrix is allowed! n >= 2\n");
			break;
		default:
			printf("An error occured!\n");
			break;
	}

	exit(1);
}

void parse_file(FILE *fp, double **matrix, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (!fscanf(fp, "%lf", &matrix[i][j]))
				break;
			//printf("%lf ", matrix[i][j]);
		}

		//printf("\n");
	}
}

void print_matrix(double **matrix, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%lf ", matrix[i][j]);
		}

		printf("\n");
	}
}

double **alloc_matrix(int n, int m)
{
	double **ptr = (double **)malloc(n * sizeof(double *));
	for (int i = 0; i < n; i++) {
		ptr[i] = (double *)malloc(m * sizeof(double));
		if (!ptr[i])
			error(1);
	}

	if (!ptr)
		error(1);

	return ptr;
}

void dealloc_matrix(double **matrix, int n)
{
	for (int i = 0; i < n; i++)
		free(matrix[i]);

	free(matrix);
}

double compute_det(double **matrix, int n)
{
	int i;
	int j;
	int whole_matrix;
	int submatrix;
	double det = 0;
	double **minor;

	if (n == 2) {
		//sarrus
		det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	} else {
		det = 0;

		for (whole_matrix = 0; whole_matrix < n; whole_matrix++) {
			minor = (double **)malloc((n - 1) * sizeof(double *));

			for (i = 0; i < n - 1; i++)
				minor[i] = (double *)malloc((n - 1) * sizeof(double));

			for (i = 0; i < n - 1; i++) {
				submatrix = 0;

				for (j = 0; j < n; j++) {
					if (j == whole_matrix)
						continue;

					minor[i][submatrix] = matrix[i + 1][j];
					submatrix++;
				}
			}

			det += pow(-1.0, 1.0 + whole_matrix + 1.0) * matrix[0][whole_matrix] * compute_det(minor, n - 1);

			for (i = 0; i < n - 1; i++)
				free(minor[i]);

			free(minor);
		}
	}

	return det;
}


int main(int argc, char *argv[])
{
	int n = 3; //rows
	int m = 3; //cols
	double **matrix;
	FILE *fp;

	//Det could be computed only from square matrix
	if (n != m && n > 1)
		error(2);

	fp = fopen("matrix.txt", "r");
	if (!fp)
		error(0);

	matrix = alloc_matrix(n, m);
	parse_file(fp, matrix, n, m);
	print_matrix(matrix, n, m);
	printf("Det: %f\n", compute_det(matrix, n));

	dealloc_matrix(matrix, n);
	fclose(fp);

	getchar();

	return 0;
}