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

int min_row(int num_row, int **A, int count)
{
 int i,j,min=32768;
 
 for(j=0; j < count; j++)
 {
  if(A[num_row][j] <= min) min=A[num_row][j];        
 }
 
 return min; 
}

int min_col(int num_col, int **A, int count)
{
 int i,j,min=32768;
 
 for(i=0; i < count; i++)
 {
  if(A[i][num_col] <= min) min=A[i][num_col];        
 }
 
 return min; 
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

void fill_from_file(FILE *f, int count, int **N)
{
 int i,j;
 
 rewind(f);
 
 for(i=0; i < count; i++) 
 { 
  for(j=0; j < count; j++)
  {
   fscanf(f,"%d",&N[i][j]); 
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
 int t,ii,i,j,k,**A,**B,*alp,*bet,*per,v,w,n,*r,*c,*rou,n_cross,n_rou,H;
 FILE *f;    
 
 
 printf("num, row/col, route: ");
 scanf("%d %d %d",&n,&n_cross,&n_rou);
 
 br;
 
 A=new int *[n];
 r=new int [n_cross];
 c=new int [n_cross];
 per=new int [n_cross];
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
 
 //print_mas(n_cross,r);
 //print_mas(n_cross,c);
 //print_mas(n_rou,rou);  
 
 br;
 
 ///////////// Массив пересечений
 for(i=0; i < n_cross; i++) per[i]=A[r[i]][c[i]];
 
 //print_mas(n_cross,per);
 
 
 //////////////////
 
 v=-1;
 w=-1;
 t=0;
     
 r[-1]=434;
 c[-1]=434;    
     
 for(ii=0; ii < n_cross; ii++)
 {
  if(r[ii] == r[ii-1] || c[ii] == c[ii-1]) break;         
           
  if(r[ii] !=0) r[ii]-=t;
  if(c[ii] !=0) c[ii]-=t;
  
 //print_mas(n_cross,r);
 //print_mas(n_cross,c);  
          
  br;
           
  f=fopen("n1.txt","w");          
         
  for(i=v+1; i < r[ii]; i++) 
  { 
   for(j=w+1; j < c[ii]; j++) {fprintf(f,"%d " ,A[i][j]);}                    
   w=c[ii];
   
   for(j=w+1; j < n; j++) {fprintf(f,"%d " ,A[i][j]);}                   
   
   fprintf(f,"\n");
   
   w=-1;
  }
  
   v=r[ii];
   w=-1;

  // printf("[ r[ii]=%d , c[ii]=%d ]",r[ii],c[ii]);

  //***********************//
         
  for(i=v+1; i < n; i++)
  {
   for(j=w+1; j < c[ii]; j++) {fprintf(f,"%d " ,A[i][j]);}                        
   w=c[ii];                                        

   for(j=w+1; j < n; j++) {fprintf(f,"%d " ,A[i][j]);}                   
  
   fprintf(f,"\n");
   
  // v=r[ii];
   w=-1;
  } 

  //** realloc memory of A
  
  fclose(f);
  free(A);
  f=fopen("n1.txt","r");
  n--; 
  
  A=new int *[n]; 
  for(i=0; i < n; i++) {A[i]=new int [n];} 
  
  fill_from_file(f,n,A);
  br;
  print_dmas(n,A);

                        // уменьшаем удаляемые элементы
 v=-1;
 w=-1;                                             
 t++;
  // -3-
}        
  
 // Запрещенный маршрут
                                                   // уменьшение из-за отрезания матрицы
 for(i=0; i < n_rou; i++) rou[i]--;
 
 for(i=0; i < n_rou; i++) {A[0][rou[i]]=754;}
 print_dmas(n,A); 
 
 // альфа
 
 alp=new int[n];
 
 for(i=0; i < n; i++)
 {
  alp[i]=min_row(i,A,n);
 }
 
 br;
 
 print_mas(n,alp);
 
 br;
 
 // вычитаем альфа
 
 for(i=0; i < n; i++) 
 { 
  for(j=0; j < n; j++)
  {
   A[i][j]-=alp[i];        
   printf("%d ",A[i][j]);
  }         
  br;
 }
   
 // бета

 for(i=0; i < n; i++)
 {
  bet[i]=min_col(i,A,n);
 }
 
 br;
 
 print_mas(n,bet);
 
 
 
 ////// +++++ считаем оценку //////  
 
 H=0;
 
 for(i=0; i < n; i++)
 {
  H+=alp[i]; 
  H+=bet[i];
 } 
 
 for(i=0; i < n_cross; i++)
 {
  H+=per[i];
 }
 
 //////////////////////////////////
 
 br;
 
 printf(" >>> H=%d",H); 
 
 fclose(f);
     
 getch();
 return 0;
} 
