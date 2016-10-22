/*
Входные данные: целые числа x и y.
Выходные данные: таблица сравнений x и y в следующем виде:
$ ./task1
Input x & y: 10 15
x	y	x>y	x<y	x>=y	x<=y	x==y	x!=y
10	15	0	1	0		1		0		1
15	10	1	0	1		0		0		1
*/

#include <stdio.h>

int main()
{
	int a = 0, b = 0;
	printf("Введите A и B: ");
	scanf("%d %d", &a, &b);
	printf("A\tB\tA>B\tA<B\tA>=B\tA<=B\tA==B\tA!=B\n");
	printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", a, b, a > b, a < b, a >= b, a <= b, a==b, a != b);
	printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", b, a, b > a, b < a, b >= a, b <= a, b == a, b != a);
	return 0;
}

