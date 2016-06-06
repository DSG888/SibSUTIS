#include <stdio.h>

int main()
{
	int a=0, b=0, index=0;
	int c=1,d=0;
	printf("Введите целое число: ");
	scanf("%d",&a);
	printf("Введите номер разряда числа (c 0я): ");
	scanf("%d",&index);
	b=index;
	if (b)
	{
		while (index>0)
		{
			c = c*10;
			index--;
		}
	}
	else
		c = 1;
	d = a / c;
	printf("Число находящееся под разрядом %d = %d\n", b, d%10);
	return 0;
}
