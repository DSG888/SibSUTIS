//---------------------------------------------------------------------------
#pragma hdrstop
#include <stdio.h>
#include <conio.h>

#include <vcl.h>
#include <string.h>

#define n 7
#define besk 65000

#pragma argsused

int A[n][n];          // n*n-n/2+1 число элементов в диагонале треугольника
int R[(n*n-n)/2][2];
int P[(n*n-n)/2];
int ves=0;
AnsiString S[(n*n-n)/2+1],c;
char C[(n*n-n)/2+1];


//---------------------------------------------------------------------------

//-----------SelectSort------------
void SelectSort(int N)
{
 int i,j,k,temp;
 for(i=0; i < N-1; i++)
 {
  k=i;
  for(j=i+1; j<N; j++) if(R[j][1]<R[k][1]) k=j;

  temp=R[k][1];
  R[k][1]=R[i][1];
  R[i][1]=temp;

  temp=R[k][0];
  R[k][0]=R[i][0];
  R[i][0]=temp;
 }
}
//-----------------------------------
int Poisk(int x)
{
 printf("Poisk x=%d\n",x);
 getch();

 int i;
 for(i=0;R[i][1]<besk;i++)
 {

                printf("S[i+1].Pos(IntToStr(x))=%d\n",S[i+1].Pos(IntToStr(x)));
                getch();
         if( S[i+1].Pos(IntToStr(x)))
         {

           return i;
         }
     }
  return -1;
}









//===========================================================================

int main(int argc, char* argv[])
{
 int i,j,z;
 int m=(n*n-n)/2;
 int nom1,nom2;
 FILE *f=fopen("arr.txt","r");


//----------------------------------------------------
  for(i=0; i<n; i++)                                               // считываем в массив
  {
   for(j=0; j<n; j++)
   {
    fscanf(f,"%d",&A[i][j]);

    if(A[i][j] < 0)
    {
     A[i][j]=besk;
     printf(" - ");
    }
    else printf("%4d ",A[i][j]);
   }
   printf("\n");
  }
//---------------------------------------------------


 z=0;
 printf("\n1-Right \n2-Left\n");
 scanf("%d",&z);

 switch(z)
 {
  case 1:
  {
   z=0;
   for(i=0;i<n;i++)
   {
    for(j=i+1;j<n;j++)
    {
     R[z][0]=i*10+j;
     R[z][1]=A[i][j];
     printf("R[z][0]=R[%d][0]=%d, R[z][1]=R[%d][1]=%d, \n",z,R[z][0],z,R[z][1]);   // z0 index, z1 num in triangle
     getch();
     z++;
    }
   }
  }
  break;

  case 2:
  {
   z=0;
   for(i=1; i < n; i++)
   {
    for(j=0;j < i;j++)
    {
     R[z][0]=i*10+j;
     R[z][1]=A[i][j];
     z++;
    }

   }
  }
  break;
  default : return 0;
}

 SelectSort(m);

 for(i=0; i < m; i++)
 {
  if(R[i][1]==besk) break;
  S[i+1]=IntToStr(i);
 // printf("S[i+1]=%d\n",S[i+1]);
  //getch();
  C[i]=i+1;
 // printf("C[i]=%d\n",C[i]);
 // getch();
  P[i]=0;
 }

 m=n;

printf("\n\n  - | ");
for(j=0; j<m; j++){ printf("{{%d}} ",StrToInt(S[j+1])); } // список компонент связности

//-----------------------------------------------------
                                          // ребра на данной точке отсортированы по возрастанию
   printf("R[i][1]=%d\n",R[i][1]);
   getch();
   for(i=0,z=0;R[i][1]<besk;i++)
   {
     printf("R[i][0]=%d\n",R[i][0]);
     getch();

     nom1=Poisk(R[i][0]/10);       // Делаем поиск склейки концов ребра среди компонентов связности
     nom2=Poisk(R[i][0]%10);

     printf("nom1=%d, nom2=%d\n",nom1,nom2);
     getch();

     printf("if S[nom1+1]==%s && S[nom2+1]==%s ",S[nom1+1],S[nom2+1]);
     getch();

     if(S[nom1+1]!=-1 && S[nom2+1]!=-1)        // если были найдены симвулы, ненулевые -> относятся к компоненте связности
     {

        if(nom1!=nom2) // если компоненты связности не повторяются, чтобы не допустить склеивания одинаковых
        {
             //printf("S[nom1+1]=%s ++ S[nom1+2]=%s, nom+1=%d, nom1+2=%d\n",S[nom1+1],S[nom1+2],nom1+1,nom2+2); // складываем позиции по которым
             // находятся компоненты связности
             S[nom1+1]=S[nom1+1]+S[nom2+1];
             printf("S[nom1+1]=%s\n",S[nom1+1]); // склеили 2 компоненты в одну!!!!
             getch();
             S[nom2+1]=IntToStr(-1);

             //printf("C[nom1]%d=C[nom2]%d\n",C[nom1],C[nom2]);
             //C[nom1]=C[nom2];

             getch();

            P[z]=R[i][0];
            printf("R[i][0]=%d\n",R[i][0]);
                    getch();

           printf("R[i][0]=%d\n",R[i][0]);
           getch();
           ves+=R[i][1]; // добавляем полученное в в  вес
           z++;

           printf("\n\n%d-%d | ",P[z-1]/10,P[z-1]%10);
           getch();


          for(j=0; j<m; j++)
          {
              if(StrToInt(S[j+1])!=-1){

                  printf("[[%s]] ",S[j+1].c_str());
              getch();
              }
          }
         // getch();
        }
        printf("strlen( S[nom1+1].c_str()=%d\n",strlen( S[nom1+1].c_str()));
      getch();
      if(strlen( S[nom1+1].c_str() )==n) break; //пока длина строки не станет равна компоненте связности
     }
   }
 printf("\n");
 printf("\n\nweight = %d",ves);

 getch();
 return 0;
}
//---------------------------------------------------------------------------


