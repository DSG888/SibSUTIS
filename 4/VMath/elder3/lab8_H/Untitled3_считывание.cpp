#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define br putchar('\n');

///////////////////////////////////////////////////////////////////////////////

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

void print_mas(int count,int *N)
{
 int i;
  
 for(i=0; i < count; i++) 
 { 
   printf("%d ",N[i]);
 } 
 br;
}

void fill_hand(int count,int *N, char *s)
{
 int i;
 printf("%s ",s); for(i=0; i < count; i++) scanf("%d",&N[i]);
 br;
}

void fill_drand(int count,int **N)
{
 int i,j;
 //int t=(int)sqrt(count);
 
 for(i=0; i < count; i++) 
 { 
  for(j=0; j < count; j++)
  {
   N[i][j]=rand()%90+10;
  }         
 }  
 
}

void print_dmas(int count,int **N)
{
 int i,j;
 //int t=(int)sqrt(count);
 
 for(i=0; i < count; i++) 
 { 
  for(j=0; j < count; j++)
  {
   printf("%d ",N[i][j]);
  }         
  br;
 } 
  
}

int main()
{
 int ii,i,j,k,**A,**B,v,w,n,*r,*c,*rou,n_cross,n_rou;
 FILE *f;    
 
 f=fopen("n1.txt","w");
 
 printf("num, row/col, route: ");
 scanf("%d %d %d",&n,&n_cross,&n_rou);
  
 //scanf("%d %d %d %d",&n);
 
 br;
 
 A=new int *[n];
 r=new int [n_cross];
 c=new int [n_cross];
 rou=new int [n_rou];
 
 for(i=0; i < n; i++)
 {
  A[i]=new int [n];
 } 
 
 fill_drand(n,A);
 print_dmas(n,A);
 
 
 ///////////
 fill_hand(n_cross,r,"crossed lines");
 fill_hand(n_cross,c,"crossed columns");
 fill_hand(n_rou,rou,"prohibited routes"); 
 
 asc(r,n_cross);
 asc(c,n_cross);
 asc(rou,n_rou);  
 
 br;
 
 print_mas(n_cross,r);
 print_mas(n_cross,c);
 print_mas(n_rou,rou);  
 
 br;
 
 ///////////// 
 
 v=-1;
 w=-1;
     
 for(ii=0; ii < n_cross; ii++) // 1 s tep
 {
           
  ///////         
  for(i=v+1; i < r[ii]; i++) // 1 d
  {
   for(j=w+1; j < c[ii]; j++) // 1 p
   {
     fprintf(f,"%d " ,A[i][j]);                  
   }                
          
  w=c[ii];                                               // 2p
   
   for(j=w+1; j < n; j++)
   {
     fprintf(f,"%d " ,A[i][j]);                  
   }                   
   
    fprintf(f,"\n" ,A[i][j]);
 
  v=r[ii];
  w=-1;
  }        
  
  //** realloc memory of A
  // обратно считываем из файла полученный массив
  
  
   
 }
 
 //***********************// last iteration
 
 v=r[ii-1];
 w=-1;
 
 ///////         
  for(i=v+1; i < n; i++) // 1 d
  {
   for(j=w+1; j < c[ii-1]; j++) // 1 p
   {
     fprintf(f,"%d " ,A[i][j]);                  
   }                
          
   w=c[ii-1];                                               // 2p
   
   for(j=w+1; j < n; j++)
   {
     fprintf(f,"%d " ,A[i][j]);                  
   }                   
   
    fprintf(f,"\n" ,A[i][j]);
 
  //v=r[ii];
  //w=-1;
  } 
 
 
       
 
 fclose(f);
     
 getch();
 return 0;
} 
