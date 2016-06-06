/*
На вход программы поступает последовательность целых чисел.
Определить НОД всех чисел в последовательности. Например:
	Вход: 21 7 10 5 15
	Выход: (21, 7, 10, 5, 15) = 1.
Указание:
	Для вычисления НОД можно использовать любой из рассмотренных ранее алгоритмов.
	Для вычисления общего НОД использовать соотношение:
	(m, n, k) = ( (m, n), k)
*/

#include <stdio.h>

#include <stdlib.h>
#include <time.h>

long int fNOD (int x, int y)
{
	return (x?fNOD(y%x,x):y); 
}

unsigned long int fNOK (int x, int y)
{
	return x*y/fNOD(x,y);
}

int main ()
{
	srand(time(NULL));
	int a = 0, n=0, k=1000, i=0;
	printf("Введите число элементов массива (1-100): ");
	scanf("%d",&a);
	if ((a > 100)||(a < 1))
	{
		printf("\tЧисло нужно от 1-100\n");
		exit(1);
	}
	int Mas[a];

	printf("\tСлучайный массив: [");
	for(i=0; i < a; i++)
	{
		Mas[i]= (n-1 + rand() % k+2);
		i<a-1?printf("%d,", Mas[i]):printf("%d]\n", Mas[i]);
	}

	long int inod=Mas[0];
	for (i=1; i<a; i++)
		inod=fNOD((inod<Mas[i]?inod:Mas[i]),(inod<Mas[i]?Mas[i]:inod));
	printf ("\tНаибольший общий делитель = %ld\n", inod);

	unsigned long int inok=1;
	for (i=0; i<a; i++)
		inok=fNOK(inok,Mas[i]);
	printf ("\tНаименьшее общее кратное = %ld\n", inok);
	return 0;
}
