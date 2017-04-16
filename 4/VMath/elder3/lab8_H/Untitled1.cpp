#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define br putchar('\n');

void asc(int *mas, int n)
{
 int i,j,tmp;

 for(i=0; i < n; i++)
 {
  for(j=i+1; j < n; j++)
  {
   if(mas[i] >= mas[j])
   {
    tmp=mas[i];
    mas[i]=mas[j];
    mas[j]=tmp;
   }
   
  }
 }
}

void fill_hand(int count,int *N, char *s)
{
 int i;
 printf("%s ",s); for(i=0; i < count; i++) scanf("%d",&N[i]);
 br;
}

void fill_num(int count,int *N, int num)
{
 int i,j;
 int t=(int)sqrt(count);
 
 for(i=0; i < count; i++) 
 { 
  for(j=0; j < count; j++)
  {
   N[t*i+j]=num;
  }         
 }   
}

void fill_drand(int count,int *N)
{
 int i,j;
 int t=(int)sqrt(count);
 
 for(i=0; i < count; i++) 
 { 
  for(j=0; j < count; j++)
  {
   N[t*i+j]=rand()%90+10;
  }         
 }  
 
}

void print_dmas(int count,int *N)
{
 int i,j;
 int t=(int)sqrt(count);
 
 for(i=0; i < count; i++) 
 { 
  for(j=0; j < count; j++)
  {
   printf("%d ",N[t*i+j]);
  }         
  br;
 } 
  
}

void print_mas(int count,int *N)
{
 int i;
  
 for(i=0; i < count; i++) 
 { 
   printf("%d ",N[i]);
 } 
 br;
}

/////////////////////////////////////////////////////////////// 

int main()
{
 srand(time(NULL));   
    
 int ii,q,i,j,k,*A,*B,n,*r,*c,*ro,v,w;
 
 printf("num, row/col, route: ");
 scanf("%d %d %d",&n,&i,&k);
 
 A=new int [n*n];
 B=new int [n*n];
 r=new int [i];
 ro=new int [k];
 c=new int [i];
 
 fill_drand(n,A);
 print_dmas(n,A);

 fill_hand(i,r,"crossed lines");
 fill_hand(i,c,"crossed columns");
 fill_hand(k,ro,"prohibited routes"); 
 
 asc(r,i);
 asc(c,i);
 asc(ro,k);  
 
 br;
 
 print_mas(i,r);
 print_mas(i,c);
 print_mas(k,ro);  
 
 br;
 
 fill_num(n,B,-1);
 print_dmas(n,B);
 
 
 

 //q=i;
 
 v=-1;
 w=-1;
 
  // первая шаг [0; a0]
  
  ii=0;
  
  printf("%d %d\n",r[ii],c[ii]);
           
  for(i=v+1; i < r[ii]; i++)
  {
             
   for(j=w+1; j < c[ii]; j++)
   {
    B[i*n+j]=A[i*n+j];
   }
   
   w=c[ii];
   
   for(j=w+1; j < n; j++)
   {
    B[i*n+(j-1)]=A[i*n+j];
   }
   
  }
  
  br;
  
  print_dmas(n,B);

/*  
                             // второй шаг   
  
 for(ii=1; ii < q; ii++) 
 {
           
  for(i=v+1; i < r[ii]; i++)
  {
   for(j=w+1; j < c[ii]; j++)
   {
    B[(i-1)*n+(j-1)]=A[i*n+j];
   }
  }
  v=r[ii];
  w=c[ii];
  
}     
                             // третий шаг
  for(i=v+1; i < n; i++)
  {
   for(j=w+1; j < n; j++)
   {
    B[(i-1)*n+(j-1)]=A[i*n+j];
   }
  }                            

  print_dmas(n,B);
*/
 getch();
 return 0;
} 
