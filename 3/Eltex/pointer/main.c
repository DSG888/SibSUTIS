#include <stdio.h>

void change1(int c, int* ptr1, int** ptr2)
{
	**(ptr2) = c;
}

void change2(int* ptr1, int** ptr2)
{
	*(ptr2) = &(ptr1);
}

int main(int argc, char *argv[])
{
	int a = 7;
	int b = 9;
	int *x = &a;
	int **y = &x;
	printf(" a:[%p] = %d\n b:[%p] = %d\n\n", &a, a, &b, b);
	printf(" x:[%p] = %p\n y:[%p] = %p\n\n", &x, x, &y, y);
	
	change1(10, x, y);
	printf(" a:[%p] = %d\n b:[%p] = %d\n\n", &a, a, &b, b);
	printf(" x:[%p] = %p\n y:[%p] = %p\n\n", &x, x, &y, y);
	
	change2(b, y);
	printf(" a:[%p] = %d\n b:[%p] = %d\n\n", &a, a, &b, b);
	printf(" x:[%p] = %p\n y:[%p] = %p\n\n", &x, x, &y, y);
	printf(" [%p] = %d\n", x, *x);
//	printf("%p\n", b);
	return 0;
}
