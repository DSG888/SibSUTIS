#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#define p 3.1495

#define br putchar('\n');

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

void print_mas(int count,int *N)
{
 int i;
 for(i=1; i < count+1; i++) 
 { printf(" %d ",N[i-1]);
 }  

} 


int main()
{
 srand(time(NULL));
 
 int *f,i,k,n,c,s,T=0; // c,s - sum parameters
 int p1,p2,k1,k2,j1,j2;
 float ***A1,***A2,***A0,arg;
 
 scanf("%d",&n);
 f=new int [n];
 p1=p2=(int)sqrt(n);
 
 printf("%d %d\n\n",p1,p2);
 
 A1=(float***)malloc(sizeof(float**)*2); // 1 step mas
 A1[0]=(float**)malloc(sizeof(float*)*p1); 
 A1[1]=(float**)malloc(sizeof(float*)*p2);
 
 A2=(float***)malloc(sizeof(float**)*2); // 1 step mas
 A2[0]=(float**)malloc(sizeof(float*)*p1); 
 A2[1]=(float**)malloc(sizeof(float*)*p2); 

 A0=(float***)malloc(sizeof(float**)*2); // 1 step mas
 A0[0]=(float**)malloc(sizeof(float*)*p1); 
 A0[1]=(float**)malloc(sizeof(float*)*p2); 
 

 
 for(i=0; i < p1; i++)
 {
  A0[0][i]=(float*)malloc(sizeof(float)*p1);
  A0[1][i]=(float*)malloc(sizeof(float)*p1);
            
          
  A1[0][i]=(float*)malloc(sizeof(float)*p1);
  A1[1][i]=(float*)malloc(sizeof(float)*p1);
  
  A2[0][i]=(float*)malloc(sizeof(float)*p1);
  A2[1][i]=(float*)malloc(sizeof(float)*p1);  
 } 
 
 fill_rand(n,f);
 print_mas(n,f);
 
 br; br;
 
 
 for(k1=0; k1 < p1; k1++)     // step 1
 {
  for(j2=0; j2 < p2; j2++)
  {
   A1[0][k1][j2]=0;
   A1[1][k1][j2]=0;
   for(j1=0; j1 < p1; j1++)
   {
    arg=-2*p*(j1*k1/p1);         
    A1[0][k1][j2]+=f[j2+j1*p2]*cos(arg);
    A1[1][k1][j2]+=f[j2+j1*p2]*sin(arg);
    T++;
   }
   A1[0][k1][j2]/=p1;
   A1[1][k1][j2]/=p1;          
  }  
 }
 
putchar('\n'); putchar('\n');
 for(k1=0; k1 < p1; k1++)
 {
  for(j2=0; j2 < p2; j2++)
  {
   printf("%.2f + i(%.2f)\n",A1[0][k1][j2],A1[1][k1][j2]);
  }
 }  
 
 putchar('\n');
 
                           // step 2
 
 for(k=0; k < n; k++)
 {
  for(k1=0; k1 < p2; k1++)
  {
   A2[0][k][k2]=0;
   A2[1][k][k2]=0;
   for(j2=0; j2 < p2; j2++)
   {
    T++;         
    arg=-2*p*(j2/(p1*p2)*(k1+p1*k2));
    A2[0][k][k2]+=A1[0][k][j2]*cos(arg)-A1[1][k][j2]*sin(arg);
    A2[1][k][k2]+=A1[0][k][j2]*cos(arg)+A1[1][k][j2]*sin(arg);
    
   }          
   A2[0][k][k2]/=p2;
   A2[1][k][k2]/=p2;       

   A0[0][k][k2]= A2[0][k][k2];
   A0[1][k][k2]= A2[1][k][k2];
  }
 }
 
 putchar('\n');
 for(k1=0; k1 < p1; k1++)
 {
  for(k2=0; k2 < p2; k2++)
  {
   printf("%.2f + i(%.2f)\n",A2[0][k1][k2],A2[1][k1][k2]);
  }
 }
 
 
 printf("\ncomplexity %d\n",T);
 
 putchar('\n');
 
 

 getch(); return 0;
}
