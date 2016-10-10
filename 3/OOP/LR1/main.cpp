/*
Задание 1. Создать динамический двумерный массив размером 200x200 элементов, заполнить его случайными целыми числами (типа Byte). Переписать элементы матрицы во вновь созданный одномерный динамический массив в следующем порядке
	a) по правым диагоналям, начиная с правого верхнего элемента
	b) по левым диагоналям, начиная с левого верхнего элемента
	c) по спирали, начиная с центрального элемента
	d) по спирали, начиная с левого верхнего элемента
Задание 2. Создать двумерный динамический массив с произвольным количеством элементов в каждой сроке. Заполнить его и распечатать построчно. 
*/


#include <stdio.h>

const int zz = 4;
int main()
{

	int i,j;
	int **ary = new int* [zz];		//Первый массив [][]
	for (i=0; i<zz; i++)
	{
		ary[i] = new int[zz];
		for (j=0; j<zz; j++)
		{
			ary[i][j]=i*zz+j;
			printf("\t%i", ary[i][j]);
		}
		printf("\n");
	}
	int* ary2 = new int[zz*zz];		// Второй массив []
	for (i=0; i<zz*zz; i++)//fixme убрать
		ary2[i] = 0;

	printf("\n");

	printf("\n  a) по правым диагоналям, начиная с правого верхнего элемента\n");
	int x, y, z=0, k=0;
	for (i=zz-1; i>=0; i--, z=0)
	{
		ary2[k] = ary[z][i]; //printf("%i\t",ary[z][i]);
		k++;
		for (j=i+1; j < zz; j++)
		{
			z++;
			ary2[k]=ary[z][j]; k++; //printf("%d\t", ary[z][j]);
		}
	}
	for (i=1; i<=zz-1; i++, z=0)
	{
		ary2[k]=ary[i][z]; k++; //printf("%i\t",ary[i][z]);
		for (j=i+1; j < zz; j++)
		{
			z++;
			ary2[k]=ary[j][z]; k++; //printf("%d\t", ary[j][z]);
		}
	}

	for (i=0; i<zz*zz;i++)
	{
		printf("%d ", ary2[i]);	
	}
	printf("\n");



	printf("\n  b) по левым диагоналям, начиная с левого верхнего элемента\n");
	k=0;
	for (i=0; i<=zz-1; i++, z=0)
	{
		ary2[k]=ary[z][i]; k++; //printf("%ix%d\t",z,i);
		for (j=zz-i; j < zz; j++)
		{
			z++;
			ary2[k]=ary[z][zz-j-1]; k++; //printf("%dx%d\t", z,zz-j-1);
		}
	}
	for (i=1; i<=zz-1; i++)
	{
		z=zz-1;
		ary2[k]=ary[i][z]; k++; //printf("%ix%d\t",i,z);
		for (j=i+1; j < zz; j++)
		{
			z--;
			ary2[k]=ary[j][z]; k++; //printf("%dx%d\t", j,z);
		}
	}
		for (i=0; i<zz*zz;i++)
		{
			printf("%d ", ary2[i]);	
		}
	printf("\n");

	printf("\n  c) по спирали, начиная с центрального элемента\n");
	x = (zz-1)/2;
	y = x;
	int lim = 0, count = 0;
	while (lim <= zz)
	{
		lim++;
		for(i=0; (i<lim) && (y<zz) && (y>=0) && (x<zz) && (x>=0); i++) //вправо
			ary2[count++] = ary[x][y++];	//printf ("%i ", ary[x][y++]);
		for(i=0; (i<lim) && (y<zz) && (y>=0) && (x<zz) && (x>=0); i++) //вниз
			ary2[count++] = ary[x++][y];	//printf ("%i ", ary[x++][y]);
		lim++;
		for(i=0; (i<lim) && (y<zz) && (y>=0) && (x<zz) && (x>=0); i++) //влево
			ary2[count++] = ary[x][y--];	//printf ("%i ", ary[x][y--]);
		for(i=0; (i<lim) && (y<zz) && (y>=0) && (x<zz) && (x>=0); i++) //вверх
			ary2[count++] = ary[x--][y];	//printf ("%i ", ary[x--][y]);
	}
 

	for (i=0; i<zz*zz; i++)
	{
		printf("%d ", ary2[i]);	
	}
	printf("\n");



	printf("\n  d) по спирали, начиная с левого верхнего элемента\n");
	lim=zz/2;
	count=0;
	int tmp;
	for (tmp=0;tmp<lim;tmp++)
	{
		for(i=tmp;i<zz-tmp;i++,count++) //колонка вниз
			ary2[count] = ary[i][tmp];
		for(j=tmp+1;j<zz-tmp;j++,count++) //строка вправо
			ary2[count] = ary[i-1][j];
		for(i=zz-tmp-2;i>=tmp;i--,count++) //колонка вверх
			ary2[count] = ary[i][j-1];
		for(j=zz-tmp-2;j>=tmp+1;j--,count++) //строка влево
			ary2[count] = ary[i+1][j];
	}
 
	if(zz%2!=0)
		ary2[count] = ary[lim][lim];

	for (i=0; i<zz*zz;i++)
	{
		printf("%d ", ary2[i]);	
	}
	printf("\n");

	for (i=0; i<zz; i++)
		delete []ary[i];
	delete []ary2;
	return 0;
}
