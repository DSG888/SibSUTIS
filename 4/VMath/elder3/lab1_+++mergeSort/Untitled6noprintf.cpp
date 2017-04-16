#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

#define br putchar('\n');
#define hr puts("________________________________________________________________________________________"); br;


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
 printf("|");
 for(i=1; i < count+1; i++) 
 { printf(" %d ",N[i-1]);
   if(i%sc==0) printf("|");
   printf(" ");
 }  

} 
              
int main()
{
 srand( time(NULL));   
    
 int CMP=0, MOV=0;    
    
 int k=0,n=1,*A,*B,*C,h,i,j,c,num,c_i,b_i,m,q,r,l,e;
 
 while (n%2) scanf("%d",&n);
 
 A=new int [n];
 B=new int [n/2];
 C=new int [n/2];
 
 //fill_rand(n,A);
 fill_rand(n,A);
 //printf("BEGIN -> ");print_mas(n,A,1);
 //br;
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
 
// hr;
// printf("B -> "); print_mas(n/2,B,num);
// br;
// printf("C -> "); print_mas(n/2,C,num);    
 
 //br; br;
 


 b_i=0;
 
                                           // merging
 k=0;
 i=0; 
 l=0;
 
 //printf("(((%d))) ",m);
 for(c_i=0; c_i < m/2; c_i++)
 {
  q=r=num;           
  while(q != 0 && r != 0) // распределение
 {
    
  if(B[i] <= C[k])
  {
             
   CMP++; //printf("{C=%d, Bi=%d Ck=%d} ",CMP,B[i],C[k]);                    
   A[l]=B[i]; MOV++; //printf("{M=%d, Bi=%d} ",MOV,B[i]);
   i++;
   q=q-1;
  }
  
  else
  {
      
   CMP++; //printf("{C=%d, Bi=%d Ck=%d} ",CMP,B[i],C[k]);              
   A[l]=C[k]; MOV++;// printf(" {M=%d, Ck=%d} ",MOV,C[k]);
   k++; 
   r=r-1;
  }
  l++;
 }    
 
 while(q > 0)              // дополнение
 {
  A[l]=B[i]; MOV++; //printf("{M=%d, Bi=%d} ",MOV,B[i]);
  l++;
  i++;
  q--;
 } 
 
 while(r > 0)              // дополнение
 {
  A[l]=C[k]; MOV++;// printf("{M=%d, Ck=%d} ",MOV,C[k]);
  l++;
  k++;
  r--;
 }
 
 //if(c_i != m/2-1)// printf(" :: "); 
 
// printf("{M=%d C=%d},",MOV,CMP);
 
 }
 
 //br;
 
 k=0;
 i=0;
 num*=2;
 c=num; 
 q=num; r=num;
 c_i=0; 
 m/=2;
 
 //br;
 //printf("A -> "); print_mas(n,A,1);
 //br;
} 

 //br;
 
 printf("Complexity M=%d C=%d T=%d",MOV,CMP,MOV+CMP);
    
 getch(); return 0;
}
