//---------------------------------------------------------------------------

#define N 256
#define pi 3.1415
#pragma hdrstop

#include "Unit2.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

int main()
{

float A[2][N];
float signal[N];
int trud=0;
int k,p1,p2,k1,j1,j2,pos;
float arg;
float *A_j2_d, *A_j2_m;
p1=(int)sqrt(N);
for (;p1>1;p1--) if (N%p1==0) break;
p2=N/p1;
A_j2_d=(float *)malloc(p1*p2*sizeof(float));
A_j2_m=(float *)malloc(p1*p2*sizeof(float));


for (k1=0; k1<p1; k1++)
        for (j2=0; j2<p2; j2++){
                *(A_j2_d+k1*p2+j2)=0.0;
                *(A_j2_m+k1*p2+j2)=0.0;
                for (j1=0; j1<p1; j1++){
                        trud++;
                        arg=(-2)*pi*k1*j1/p1;
                        *(A_j2_d+k1*p2+j2)+=signal[j2+j1*p2]*cos(arg);
                        *(A_j2_m+k1*p2+j2)+=signal[j2+j1*p2]*sin(arg);
                        }
                *(A_j2_d+k1*p2+j2)/=p1;
                *(A_j2_m+k1*p2+j2)/=p1;
                }

for (k=0; k<N; k++){
        A[0][k]=0.0;
        A[1][k]=0.0;
        k1=k%p1;

        for (j2=0; j2<p2; j2++){
                trud++;
                arg=(-2)*pi*k*j2/N;
                A[0][k]+=*(A_j2_d+k1*p2+j2)*cos(arg)-*(A_j2_m+k1*p2+j2)*sin(arg);
                A[1][k]+=*(A_j2_m+k1*p2+j2)*cos(arg)+*(A_j2_d+k1*p2+j2)*sin(arg);
                }
        A[0][k]/=p2;
        A[1][k]/=p2;
        printf("%5.5f+%5.5f*i",A[0][k],A[1][k]);

        }




for (k1=0; k1<p1; k1++)
        for (j2=0; j2<p2; j2++){
                *(A_j2_d+k1*p2+j2)=0.0;
                *(A_j2_m+k1*p2+j2)=0.0;
                for (j1=0; j1<p1; j1++){
                        arg=2*pi*k1*j1/p1;
                        *(A_j2_d+k1*p2+j2)+=A[0][j2+j1*p2]*cos(arg)-A[1][j2+j1*p2]*sin(arg);
                        *(A_j2_m+k1*p2+j2)+=A[1][j2+j1*p2]*cos(arg)+A[0][j2+j1*p2]*sin(arg);
                        }
                }

for (k=0; k<N; k++){
        A[0][k]=0.0;
        A[1][k]=0.0;
        k1=k%p1;

        for (j2=0; j2<p2; j2++){
                arg=2*pi*k*j2/N;
                A[0][k]+=*(A_j2_d+k1*p2+j2)*cos(arg)-*(A_j2_m+k1*p2+j2)*sin(arg);
                A[1][k]+=*(A_j2_m+k1*p2+j2)*cos(arg)+*(A_j2_d+k1*p2+j2)*sin(arg);
                }

        printf("%5.5f",A[0][k]);
        }

}