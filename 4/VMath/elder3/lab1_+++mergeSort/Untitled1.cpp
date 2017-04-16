#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

#define br putchar('\n');

int T=0, C=0, M=0;

void fill_rand(int count,int *N)
{
 int i;
 for(i=0; i < count; i++) N[i]=rand()%100;
} 

void print_mas(int count,int *N)
{
 int i;
 for(i=0; i < count; i++) printf("%d ",N[i]);
} 
              
int main()
{
 int k=0,n=1,*A,*B,*C,h,i,j,c,num,c_i,b_i,m,q,r,l,e;
 
 while (n%2==1) scanf("%d",&n);
 
 A=new int [n];
 B=new int [n/2];
 C=new int [n/2];
 
 fill_rand(n,A);
 print_mas(n,A);
 
                                           // B - odd , C - even
 num=1;
 c=num;
 m=n;
 i=0; j=0; k=0; c_i=0; b_i=0;
 e=1;
 q=e;
 r=e;
 
while(m != 1)
{ 
 while(k < m)
 {
  if(k%2 != 0)           // нечетные 
  {
   for(; i < c; i++)
   {
    C[c_i]=A[i];
    c_i++;
   }
  }
  
  else
  {
   for(; i < c; i++)   // четные
   {
    B[b_i]=A[i];
    b_i++;
   }      
  
  }
  c+=num;
  k++;
 }   
 
 br; 
 print_mas(n/2,B);
 br;
 print_mas(n/2,C);    
 
 br; br;
 
 m/=2;

 b_i=0;
 
                                           // merging
 k=0;
 i=0; 
 l=0;
 
 
 for(c_i=0; c_i < n; c_i++)
 {
  q=r=num;           
  while(q != 0 && r != 0) // распределение
 {     
  if(B[i] <= C[k])
  {
   A[l]=B[i];
   i++;
   q=q-1;
  }
  
  else
  {
   A[l]=C[k];
   k++;
   r=r-1;
  }
  
  l++;
 }    
 
 while(q > 0)              // дополнение
 {
  A[l]=B[i];
  l++;
  i++;
  q--;
 } 
 
 while(r > 0)              // дополнение
 {
  A[l]=C[k];
  l++;
  k++;
  r--;
 } 
 }
 
 k=0;
 i=0;
 num*=2;
 c=num; 
 q=num; r=num;
 c_i=0; 
 
 printf("("); print_mas(n,A); printf(")");
 
} 
    
 getch(); return 0;
}
