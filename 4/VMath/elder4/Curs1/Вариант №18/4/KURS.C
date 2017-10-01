#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define Min 0
#define Max 1
#define ishag 0.2

const float EPS=0.0001;
const float shag=0.01;
const N=(Max-Min)/ishag+1;

int gd,gm;
int i,j;
float setkaX[N+1],setkaY[N+1];
float X,X0;
float dK;
float L,R,C;

float nF(float X,float Y,float dY,float d2Y)
{
 return(dY-(X*X+1.38*Y)-d2Y+sin(d2Y));
}

float ndF(float X, float Y, float dY)
{
float L=0,R=10,C;

 while(fabs(((R-L)/2))>=EPS)
  {
   C=(L+R)/2;
   if(nF(X,Y,dY,C)*nF(X,Y,dY,L)<0) R=C;
    else if(nF(X,Y,dY,C)*nF(X,Y,dY,R)<0) L=C;
     else break;
  }

 return(C);
}

float ur_func(float X,float X0,float Y0,float dY0)
{
int i;
float wX;
float Y[2],Z[2],Ys[2],K1[2],K2[2],K3[2],K4[2];

 Y[0]=Y0;Y[1]=dY0;
 wX=X0;

 while(fabs(X-wX)>=EPS)
  {
   Z[0]=Y[0];Z[1]=Y[1];
   K1[0]=Z[1];
   K1[1]=ndF(wX, Z[0], Z[1]);
   K2[0]=Z[1]+(shag/2)*K1[1];
   K2[1]=ndF(wX+shag/2,Z[0]+(shag/2)*K1[1],K2[0]);
   K3[0]=Z[1]+(shag/2)*K2[1];
   K3[1]=ndF(wX+shag/2,Z[0]+(shag/2)*K2[1],K3[0]);
   K4[0]=Z[1]+shag*K3[1];
   K4[1]=ndF(wX+shag,Z[0]+shag*K3[1],K4[0]);

   Y[0]=Z[0]+(shag/6)*(K1[0]+2*K2[0]+2*K3[0]+K4[0]);
   Y[1]=Z[1]+(shag/6)*(K1[1]+2*K2[1]+2*K3[1]+K4[1]);
   wX+=shag;
  }
 return(Y[0]);
}


float ur_proizv(float X,float X0,float Y0,float dY0)
{
int i;
float wX;
float Y[2],Z[2],Ys[2],K1[2],K2[2],K3[2],K4[2];

 Y[0]=Y0;Y[1]=dY0;
 wX=X0;

 while(fabs(X-wX)>=EPS)
  {
   Z[0]=Y[0];Z[1]=Y[1];
   K1[0]=Z[1];
   K1[1]=ndF(wX, Z[0], Z[1]);
   K2[0]=Z[1]+(shag/2)*K1[1];
   K2[1]=ndF(wX+shag/2,Z[0]+(shag/2)*K1[1],K2[0]);
   K3[0]=Z[1]+(shag/2)*K2[1];
   K3[1]=ndF(wX+shag/2,Z[0]+(shag/2)*K2[1],K3[0]);
   K4[0]=Z[1]+shag*K3[1];
   K4[1]=ndF(wX+shag,Z[0]+shag*K3[1],K4[0]);

   Y[0]=Z[0]+(shag/6)*(K1[0]+2*K2[0]+2*K3[0]+K4[0]);
   Y[1]=Z[1]+(shag/6)*(K1[1]+2*K2[1]+2*K3[1]+K4[1]);
   wX+=shag;
  }
 return(Y[1]);
}

void shoot()
{
 L=-5;R=5;
 while(fabs((ur_func(1,0,1,L)-ur_func(1,0,1,R))/2)>=EPS)
  {
   C=(L+R)/2;
   if((ur_func(1,0,1,C)-0.5)*(ur_func(1,0,1,L)-0.5)<0) R=C;
    else if((ur_func(1,0,1,C)-0.5)*(ur_func(1,0,1,R)-0.5)<0) L=C;
     else break;
  }
 dK=C;
}


float spline(float x)
{
float h[N], d[N-1], m[N-1],c[N-1][N],b[N-1][N];
int i,j,k;
float t;

 for(i=0;i<N;i++) h[i]=setkaX[i+1]-setkaX[i];

 for(i=0;i<N-1;i++) d[i]=(setkaY[i+2]-setkaY[i+1])/h[i+1]-(setkaY[i+1]-setkaY[i])/h[i];

 for(i=0;i<N-1;i++)
  for(j=0;j<N;j++)
  c[i][j]=0;

 for(i=0;i<N-1;i++)
  {
   c[i][i]=(h[i]+h[i+1])/3;
   c[i][i+1]=h[i+1]/6;
   c[i+1][i]=h[i+1]/6;
   c[i][N-1]=d[i];
  }

 for(k=0;k<N-2;k++)
  for(i=k+1;i<N-1;i++)
   {
    b[i][k]=-c[i][k]/c[k][k];
    for(j=k;j<N;j++) c[i][j]=c[i][j]+b[i][k]*c[k][j];
   }

 for(i=N-2;i>=0;i--)
  {
   t=c[i][N-1];
   for(j=i+1;j<N;j++) t=t-c[i][j]*m[j];
   m[i]=t/c[i][i];
  }

  for(i=0;i<N;i++)
   if((x>=setkaX[i])&&(x<=setkaX[i+1])) break;
  i++;

  return(m[i-2]*(setkaX[i]-X)*(setkaX[i]-X)*(setkaX[i]-X)/(6*h[i-1])+
	 m[i-1]*(X-setkaX[i-1])*(X-setkaX[i-1])*(X-setkaX[i-1])/(6*h[i-1])+
	 (setkaY[i-1]-m[i-2]*h[i-1]*h[i-1]/6)*(setkaX[i]-X)/h[i-1]+
	 (setkaY[i]-m[i-1]*h[i-1]*h[i-1]/6)*(X-setkaX[i-1])/h[i-1]);
}

void main()
{
 clrscr();

 shoot();

 printf("X=0  F=%5.5f  dF=%5.5f   F^2=%5.5f\n",ur_func(0,0,1,dK),ur_proizv(0,0,1,dK),ur_func(0,0,1,dK)*ur_func(0,0,1,dK));
 for(X=0.12;X<1;X+=0.1) printf("X=%3.2f  F=%5.5f  dF=%5.5f   F^2=%5.5f\n",X,ur_func(X,0,1,dK),ur_proizv(X,0,1,dK),ur_func(X,0,1,dK)*ur_func(X,0,1,dK));
 printf("X=1  F=%5.5f  dF=%5.5f   F^2=%5.5f\n",ur_func(1,0,1,dK),ur_proizv(1,0,1,dK),ur_func(1,0,1,dK)*ur_func(1,0,1,dK));
 getch();

 for(i=0;i<=N;i++){
  setkaX[i]=Min+i*ishag;
  setkaY[i]=ur_func(setkaX[i],0,1,dK);
 }

 gd=DETECT;
 initgraph(&gd,&gm,"");

 line(0,240,640,240);line(320,0,320,480);

 X=Min;
 moveto(320+X*200,240-ur_func(X,0,1,dK)*200);
 while(X<=Max+0.1)
  {lineto(320+X*200,240-ur_func(X,0,1,dK)*200);X+=0.01;}
 getch();

 setcolor(LIGHTRED);
 X=Min	;
 moveto(320+X*200,240-spline(X)*200);
 while(X<=Max)
  { lineto(320+X*200,240-spline(X)*200);X+=0.01;}

 getch();
 closegraph();
}