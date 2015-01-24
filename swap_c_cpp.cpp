#include <stdio.h>

void swap_c(int *x, int *y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

void swap_cpp(int &x, int &y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

int main(int argc, char *argv[])
{
	int x;
	int y;

	x = 5;
	y = 7;
	swap_c(&x, &y);
	printf("C: x: %d, y: %d\n", x, y);

	x = 5;
	y = 7;
	swap_cpp(x, y);
	printf("C++: x: %d, y: %d\n", x, y);

	getchar();

	return 0;
}