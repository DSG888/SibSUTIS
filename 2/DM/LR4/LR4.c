#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int A[256];
int B[256];

void GGen (int n, int A[])
{
	int i, j, p, q = 0, w = 0;
	for (i = 0; i < n; i++)
	{
		A[i] = 0;
	}
	i = 0;
	do
	{
		for (j = 0; j < n; j++)
		{
			B[q] = A[j];
			q++;
		}
		i++;
		p = 0;
		j = i;
		while ((j & 1) == 0)
		{
			j = j / 2;
			p++; 
		}
		if (p < n)
			A[p] = !A[p];
	} 
	while (p < n);
 	for (i = 0; i < q; )
	{
		i = i + n;
		for (j = i - 1; j >= w; j--)
		{
			printf("%2d", B[j]);
		}
		w = w + n;
		printf("\n");
	} 
}

void newElement()
{
	int n;
	scanf("%d", &n);
	if (n < 0)
	{
		printf("Element mnogestva ne moget bit otrecatelen ili raven 0\n");
		newElement();
	}
	else
	{
		GGen(n, A);
	}
}

int main()
{
	printf("Введите n: ");
	newElement();
}
