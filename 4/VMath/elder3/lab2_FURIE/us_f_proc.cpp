#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#define p 3.1415

int T=0; // gvars

void fill_hands(float *x, int n) // ручной ввод 
{
 for(int i=0;i<n;i++){scanf("%d",&x[i]);}
}

void fill_rand(int count,int *N) // случайными числами автоматически
{
 int i;
 for(i=0; i < count; i++) N[i]=rand()%90+10;
}

void fill_back(int count,int *N) // заполняем в обратном порядке
{
 int i;
 for(i=count-1; i >= 0; i--) N[i]=i;
} 

void fill_front(int count, int*N) // в прямом
{
 int i;
 for(i=0; i < count; i++) N[i]=i;
}      

void print_mas(int count,int *N) // вывод массивов на экран
{
 int i;
 for(i=1; i < count+1; i++) 
 { printf(" %d ",N[i-1]);
 }

}

void front_(float** mas, int *f, int n)
{
 int j,k;
 double arg;

 for(k=0; k <= n-1; k++) // front переходим от исходного целочисленного массива, к массиву с комплексными числами
 {
  mas[0][k]=0; // зануляем элемента для суммирования в них косинусов или синусов
  mas[1][k]=0;
  for(j=0; j <= n-1; j++)
  {
   T++;
   arg=(-2*p*k*j)/n;   // АРГУМЕНТ НА КОТОРЫЙ МЫ УМНОЖАЕМ КОСИНУС ИЛИ СИНУС
   mas[0][k]+=cos(arg)*f[j];
   mas[1][k]+=sin(arg)*f[j];
  }
  mas[0][k]/=n;
  mas[1][k]/=n;

  printf("%.2f+i(%.2f)\n",mas[0][k],mas[1][k]);
 }

}

void back_()
{

}


int main()
{
 srand(time(NULL));

 int *f,i,j,k,n,c,s; // c,s - sum parameters
 float **A,**B,arg;

 scanf("%d",&n); // количество элементов массива
 f=new int [n]; // выделяем память под это количество
 A=(float**)malloc(sizeof(float*)*2);
 A[0]=new float [n]; // cos
 A[1]=new float [n]; // sin

 B=(float**)malloc(sizeof(float*)*2);
 B[0]=new float [n]; // cos
 B[1]=new float [n]; // sin

 fill_rand(n,f);
 print_mas(n,f);

 putchar('\n');
 putchar('\n');

 printf("f{0,1...n} -> A{0,1...n}");

putchar('\n');
putchar('\n');

 front_(A,f,n);// (float** mas, int n)

 /*
 for(k=0; k <= n-1; k++) // front переходим от исходного целочисленного массива, к массиву с комплексными числами
 {
  A[0][k]=0; // зануляем элемента для суммирования в них косинусов или синусов
  A[1][k]=0;
  for(j=0; j <= n-1; j++)
  {
   T++;
   arg=(-2*p*k*j)/n;   // АРГУМЕНТ НА КОТОРЫЙ МЫ УМНОЖАЕМ КОСИНУС ИЛИ СИНУС
   A[0][k]+=cos(arg)*f[j];
   A[1][k]+=sin(arg)*f[j];
  }
  A[0][k]/=n;
  A[1][k]/=n;

  printf("%.2f+i(%.2f)\n",A[0][k],A[1][k]);
 } */
 
 putchar('\n');
 
printf("A{0,1...n} -> f{0,1...n}");   
 putchar('\n');
 putchar('\n');
                          // obr
 for(k=0; k <= n-1; k++)
 {
  B[0][k]=0;
  B[1][k]=0;        
  for(j=0; j <= n-1; j++)
  {
   arg=(2*p*k*j)/n; 
   B[0][k]+=A[0][j]*cos(arg)-A[1][j]*sin(arg);
   B[1][k]+=A[1][j]*cos(arg)+A[0][j]*sin(arg);
 }
  printf("%.2f+i(%.2f)\n",B[0][k],B[1][k]);
}  

 printf("\n\n>>> Complexity: %d",T);
 
 getch();
 return 0;
}
