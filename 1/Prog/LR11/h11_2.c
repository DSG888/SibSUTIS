#include<stdio.h>

int main()
{
	double i = 1, a = 0, b = 0;
	int c = 0;
	printf("Введите число из которого надо вычислить корень: ");
	scanf("%lf", &a);

	b = a;
	if(b > 0)
	{
		while(b > 0 && b / i >= 1)
		{
			b = b - i;
			i = i + 2;
			c++;
		}
		printf("\tЦелая часть sqrt(%lf) = %d\n\n", a, c);
	}
	else
	{
		printf("А это уже комплексное число!\n");
	}
	return 0;
}

