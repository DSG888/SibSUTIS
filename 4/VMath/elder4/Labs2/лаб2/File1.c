//---------------------------------------------------------------------------

#include <stdio.h>
#include <math.h>
#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused
FILE *f2;

/*Очистка массива*/
void clr(float *a, int sz)
{   int i;
	for(i=0;i<sz;i++)a[i]=0;
}

void printm(float *a, int sz, char p)
{   int i;

	for(i=0;i<sz;i++){
		printf("\n   x[%d]: %f",i+1,a[i]);
		if(p=='f')fprintf(f2,"\n   x[%d]: %f",i+1,a[i]);
	}
	printf("\n");
}

int main(int argc, char* argv[])
{   FILE *f1;
	float c[15][15],b[15],x1[15],x2[15],koof,cn,cb;
	int i,j,n,N,g,sz;
	f2=fopen("matr.txt","w");

	/*Открытие файла с матрицей*/
	if((f1=fopen("mat.txt","r"))==NULL)
	{
		printf("\nNe udalos otkrit file: mat.txt");
		getchar();
		return -1;
	}

	/*Чтение матрицы из файла*/
	fscanf(f1,"%d",&sz);/*Чтение размерности*/
	for(i=0;i<sz;i++)
	{
		for(j=0;j<sz;j++)
			fscanf(f1,"%f",&c[i][j]);
		/*Чтение вектора*/
		fscanf(f1,"%f",&b[i]);
	} 

	clr(x1,sz);
	clr(x2,sz);

	/*Вывод исходного массива*/
	for(i=0;i<sz;i++)
	{
		for(j=0;j<sz;j++)
			printf("%13f",c[i][j]);
		printf("|%13f\n",b[i]);
	}

	/*Делаем нулипо гл. диагонали*/
	for(i=0;i<sz;i++)
	{
		koof=c[i][i];
		c[i][i]=0;
		for(j=0;j<sz;j++)c[i][j]=c[i][j]/koof;
		b[i]=b[i]/koof;
	}

	/*Нахождение ||c||*/
	for(i=0;i<sz;i++)
	{
		for(j=0;j<sz;j++)if(c[i][j]>0)x1[i]+=c[i][j];
		else x1[i]-=c[i][j];
	}
	cn=x1[0];
	for(i=1;i<sz;i++)if(x1[i]>cn)cn=x1[i];
	/*Нахождение ||b||*/
	cb=b[0];
	for(i=1;i<sz;i++)if(b[i]>cb)cb=b[i];
	/*Расчет N*/
	N=log10(0.00001*(1-cn)/cb)/log10(cn);
    printf("\n   N=%d\n",N);

	/*Решение матрицы методом простых итераций*/
	clr(x1,sz);
	for (n=1;n<=N;n++)
	{	clr(x2,sz);
		for(i=0;i<sz;i++)
			for(j=0;j<sz;j++)x2[i]+=c[i][j]*x1[j];

		for(i=0;i<sz;i++)x1[i]=b[i]-x2[i];
		printf("\n   Shag N%d",n);
		printm(x1,sz,'n');
	}

	/*Вывод и запись в файл решенной матрицы*/
	printf("\nReshonnaia matrixa:");
	printm(x1,sz,'f');

	fclose(f1);
	fclose(f2);
	getchar();
	return 0;
}
//---------------------------------------------------------------------------
