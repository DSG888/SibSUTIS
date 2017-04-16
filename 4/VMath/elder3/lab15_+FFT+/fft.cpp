#include "fft.h"
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

#define hr puts("================================================================");

#include "tab.cpp"
#include "w2n.cpp"

void fft(ShortComplex *x, int T, bool complement)
{
  //  printf("aa"); 
     
    unsigned int I, J, N, Nd2, k, m, mpNd2, Skew;
    unsigned long int Nmax;
    unsigned char *Ic = (unsigned char*) &I;
    unsigned char *Jc = (unsigned char*) &J;
    ShortComplex S;
    ShortComplex *Wstore, *Warray;
    Complex WN, W, Temp, *pWN;
    
    int tt=0;

    Nmax = 1 << T;
    //printf("Nmax=%d",Nmax);
    

    for(I = 1; I < Nmax - 1; I++)
    {
        Jc[0] = reverse256[Ic[3]];
        Jc[1] = reverse256[Ic[2]];
        Jc[2] = reverse256[Ic[1]];
        Jc[3] = reverse256[Ic[0]];
        J >>= (32 - T);
        
        if (I < J)
        {
            S = x[I];
            x[I] = x[J];
            x[J] = S;
        }
    }

    Wstore = new ShortComplex[Nmax / 2];
    Wstore[0].re = 1.0;
    Wstore[0].im = 0.0;

    for(N = 2, Nd2 = 1, pWN = W2n, Skew = Nmax >> 1; N <= Nmax; Nd2 = N, N += N, pWN++, Skew >>= 1)
    {
       	WN= *pWN; 
        if (complement) WN.im = -WN.im;
        
        for(Warray = Wstore, k = 0; k < Nd2; k++, Warray += Skew)
        {
            //printf("Nd2=%d\n",Nd2);       
            if (k & 1)
            {
                W *= WN;
                *Warray = W;
            }
            else W = *Warray;

            for(m = k; m < Nmax; m += N)
            {
                //printf("m=%d N=%d Nmax=%d\n",m,N,Nmax);
                mpNd2 = m + Nd2;
                Temp = W;
                Temp *= x[mpNd2];
                x[mpNd2] = x[m];
                x[mpNd2] -=Temp;
                x[m] += Temp;
               // printf("%d) %f %f\n",tt,x[mpNd2],x[m]);
                tt++;
            }
            
        }
    }

    delete [] Wstore;

    if (complement)
    {
        for( I = 0; I < Nmax; I++ )
            x[I] /= Nmax;
    }
    
    // output
    
 /*   for(I=0; I < Nmax; I++)
    {
     printf("%f %f\n",x[I].re,x[I].im);
    } */
}

int main()
{
                // for logs
                // set VARS
 int p;
 int i;
 ShortComplex *arr;
 long int NUM;
 
 int b;
 int a; 
  
 ///////////////////////////////////////////////////
 
 printf("Enter pow: ");
 scanf("%d",&p);
 
 NUM=(int)pow(2,p);
 
 printf("number of element is %d ",NUM);
 printf("step - %d, press key to start\n\n",p);
 //////////////////////////////////////////////////               
    
 getch();
 
 printf("< malloc of memory and flowing elements... \n");
 arr=(ShortComplex*)malloc(sizeof(ShortComplex)*NUM);

 
 for(i = 0; i < NUM; ++i)
 {
  arr[i].re=rand()%99;
  arr[i].im=0.0;
 // printf("%f %f\n",arr[i].re,arr[i].im);
                                                                      // printf("%f %f\n",arr[i].re,arr[i].im);
 }
 printf (">");
 printf("> FFT beginning at %d sec\n",a=clock()/CLOCKS_PER_SEC);
 fft(arr, p, false);
// putchar('\n'); hr;
 fft(arr, p, true);
 printf("< end at %d sec\n",b=clock()/CLOCKS_PER_SEC);
 printf("\n");
 
 printf("res = %d sec",b-a);

   
 getch(); return 0;
} 

