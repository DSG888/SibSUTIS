#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void fill_rand(int count,int *N)
{
 int i;
 for(i=0; i < count; i++) N[i]=rand()%90+10;
}

void fill_back(int count,int *N)
{
 int i;
 for(i=count-1; i >= 0; i--) N[i]=i;
} 

void fill_front(int count, int*N)
{
 int i;
 for(i=0; i < count; i++) N[i]=i;
}      

void print_mas(int count,int *N, int sc)
{
 int i;
 for(i=1; i < count+1; i++) 
 { printf(" %d ",N[i-1]);
 }  

} 


int main()
{
 srand(time(NULL));
 
 int *f,*A,i,j,k,n;
 
 scanf("%d",&n);
 f=new int [n];
 fill_rand(n,f);
 
    
    
    
 getch();
 return 0;
}
