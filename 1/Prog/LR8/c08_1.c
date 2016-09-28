#include <stdio.h>

int main()
{
	int a, b;
	printf("Input dividend: ");
	scanf("%d", &a);
	printf("Input divisor: ");
	scanf("%d", &b);
	printf("(%d/%d) = %d\n", a, b, a / b);
	printf("(%d%%%d) = %d\n", a, b, a % b);
	return 0;
}
