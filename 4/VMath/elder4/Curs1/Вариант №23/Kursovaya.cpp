#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <graphics.h>

#define EPS 0.0001 /*Tochnost*/
#define STEP 0.022 /*parametri dlya grafika*/
#define DX STEP*10 /*koeficient rastyazheniya po X*/
#define DY STEP*6 /* po  Y*/
#define iStep 0.2 /*shag*/
#define iMin 0 /*granici interpolyacii*/
#define iMax 1
#define N (int)((iMax-iMin)/iStep)+2 /*tochki interpol*/

 int gd,gm;
 int i,j;
 double IntX[N+1],IntY[N+1]; /*Setka interpol*/
 double X,X0;
 double K;
 double dK;
 double L,R,C;
 double dH;
/*funk nelineynogo uravneniya*/
double F(double X)
{
 return 4*X-asin(X)-1;
}
/*dif uravnenie*/
double nF(double X, double Y,double dY,double d2Y)
{
 return dY-(X*X+Y)-K*d2Y+cos(d2Y);
}

/*reshenie neliynogo dlya metoda rungekutta*/
double solveNE(double X, double Y,double dY)
{
 double L,R,C;

 L=-10;R=10;
 do
 {
  C=(L+R)/2;

  if((nF(X,Y,dY,C)*nF(X,Y,dY,L))<0) R=C;
   else if((nF(X,Y,dY,C)*nF(X,Y,dY,R))<0) L=C;
  else break;
 }
 while(fabs(((R-L)/2))>=EPS);
 return C;
}

/*metod rungekutta4, vozvrash znach funkcii v X
pri znachenie funk i ee proizvod v X0*/
double getY(double X,double X0,double Y0,double dY0)
{
 int i;
 double wX;
 double Y[2],Z[2],Ys[2],K1[2],K2[2],K3[2],K4[2];

 Y[0]=Y0;Y[1]=dY0;
 wX=X0;

 while(fabs(X-wX)>=EPS)
  {
   Z[0]=Y[0];Z[1]=Y[1];
   K1[0]=Z[1];
   K1[1]=solveNE(wX, Z[0], Z[1]);
   K2[0]=Z[1]+(dH/2)*K1[1];
   K2[1]=solveNE(wX+dH/2,Z[0]+(dH/2)*K1[1],K2[0]);
   K3[0]=Z[1]+(dH/2)*K2[1];
   K3[1]=solveNE(wX+dH/2,Z[0]+(dH/2)*K2[1],K3[0]);
   K4[0]=Z[1]+dH*K3[1];
   K4[1]=solveNE(wX+dH,Z[0]+dH*K3[1],K4[0]);

   Y[0]=Z[0]+(dH/6)*(K1[0]+2*K2[0]+2*K3[0]+K4[0]);
   Y[1]=Z[1]+(dH/6)*(K1[1]+2*K2[1]+2*K3[1]+K4[1]);
   wX=wX+dH;
  }
 return Y[0];
}

/*dvoinoi pereschet� getY*/
double doubleF(double X, double X0,double Y0,double dY0)
{
 double res,res2;

 do
 {
  res=getY(X,X0,Y0,dY0);
  dH=dH/2;
  res2=getY(X,X0,Y0,dY0);
 }
 while(fabs(res-res2)>=15*EPS);

 dH=0.01;
 return res2;
}

/*Metod RK4, vozvrashaet znachenie proizvod funk v X, pri
izvestnih znach funk i ee proiz X0*/
double getdY(double X,double X0,double Y0,double dY0)
{
 int i;
 double wX;
 double Y[2],Z[2],Ys[2],K1[2],K2[2],K3[2],K4[2];

 Y[0]=Y0;Y[1]=dY0;
 wX=X0;

 while(fabs(X-wX)>=EPS)
  {
   Z[0]=Y[0];Z[1]=Y[1];
   K1[0]=Z[1];
   K1[1]=solveNE(wX, Y[0], K1[0]);
   K2[0]=Z[1]+(dH/2)*K1[1];
   K2[1]=solveNE(wX+dH/2,Z[0]+(dH/2)*K1[1],K2[0]);
   K3[0]=Z[1]+(dH/2)*K2[1];
   K3[1]=solveNE(wX+dH/2,Z[0]+(dH/2)*K2[1],K3[0]);
   K4[0]=Z[1]+dH*K3[1];
   K4[1]=solveNE(wX+dH,Z[0]+dH*K3[1],K4[0]);

   Y[0]=Z[0]+(dH/6)*(K1[0]+2*K2[0]+2*K3[0]+K4[0]);
   Y[1]=Z[1]+(dH/6)*(K1[1]+2*K2[1]+2*K3[1]+K4[1]);
   wX=wX+dH;
  }
 return Y[1];
}

/*dvoinoy pereschet dlya� getdY*/
double doubledF(double X, double X0,double Y0,double dY0)
{
 double res,res2;

 do
 {
  res=getdY(X,X0,Y0,dY0);
  dH=dH/2;
  res2=getdY(X,X0,Y0,dY0);
 }
 while(fabs(res-res2)>=15*EPS);

 dH=0.01;
 return res2;
}

/*vizov getY*/
double inF(double X)
{
 return getY(X,0,1,dK);
}


/*interpol splainom X*/
double splain(double X)
{
 int i,j,k;
 double h[N];
 double d[N-1],m[N-1];
 double c[N-1][N],b[N-1][N];
 double t;

 for(i=0;i<N;i++) h[i]=IntX[i+1]-IntX[i];

 for(i=0;i<N-1;i++) d[i]=(IntY[i+2]-IntY[i+1])/h[i+1]-(IntY[i+1]-IntY[i])/h[i];

 for(i=0;i<N-1;i++)
  for(j=0;j<N;j++) c[i][j]=0;

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

  for(i=0;i<N-1;i++)
   if((X>=IntX[i])&&(X<=IntX[i+1])) break;
  i++;

  return m[i-1]*(IntX[i]-X)*(IntX[i]-X)*(IntX[i]-X)/(6*h[i-1])+
      m[i-2]*(X-IntX[i-1])*(X-IntX[i-1])*(X-IntX[i-1])/(6*h[i-1])+
      (IntY[i-1]-m[i-1]*h[i-1]*h[i-1]/6)*(IntX[i]-X)/h[i-1]+
      (IntY[i]-m[i-2]*h[i-1]*h[i-1]/6)*(X-IntX[i-1])/h[i-1];
}


/*integral simpsona*/
double Integr()
{
 double R;
 double i;

 R=(inF(0)+inF(1))/6;

 i=dH;
 while(i<=1)
  {
   R=R+(inF(i))*2/3;
   i=i+2*dH;
  }
 i=2*dH;
 while(i<=1)
  {
   R=R+2*inF(i)/6;
   i=i+2*dH;
  }

 R=R*2*dH;
 return R;
}


void main()
{
 clrscr();
 dH=0.01;

/*reshenie nelineynogo urav metodom Nutona*/
 textcolor(GREEN);
 cprintf("Disciplina: Vychislitel'naja Matematika\r\n\r\n");
 textcolor(1501);
 cprintf("=================================================made by D>|<im=================");
 textcolor(GREEN);
 cprintf("Vypolnil: Ferdinandov V.V.\r\nGruppa: VM 57\r\n\r\nVariant 23\r\n\r\nProveril: Ruban A.A.\r\n");
 textcolor(1501);
 cprintf("=================================================made by D>|<im=================\r\n\r\n\r\n");
 textcolor(WHITE);
 cprintf("1. Reshenie ne lineynogo uravneniya\r\n");
 textcolor(LIGHTBLUE);
 cprintf("4X-arcsin(X)-1=0\r\n\r\n");
 textcolor(WHITE);
 double XX=0.5;
 double aa=0;
 double bb=1;
 X0=1;
 while(fabs(XX-X0)>=EPS)
 {
	X0=XX;
	if (F(aa)*F(XX)<0)
		bb=XX;
	else
		aa=XX;
	XX=(aa+bb)/2;
 }
 X=XX;
 cprintf("X=%10.10f\r\n\r\n",X);
 getch();
 K=X;
 cprintf;cprintf;textcolor(WHITE);
 cprintf("\n2. Reshenie differ uravneniya\r\n");
 cprintf;textcolor(LIGHTBLUE);cprintf("y'-(x*x+k*y)-y''+sin(y'')=0\r\n\n");
 cprintf;cprintf;
 textcolor(WHITE);


/*metod strelb*/
 L=-10;R=10;
 do
 {
  C=(L+R)/2;
  if (((getY(1,0,1,C)-0.5)*(getY(1,0,1,L)-0.5))<0) R=C;
   else if(((getY(1,0,1,C)-0.5)*(getY(1,0,1,R)-0.5))<0) L=C;
    else break;
    float t2t=getY(1,0,1,L);
    float t2t2=getY(1,0,1,R);
	asm nop;
 }
 while(fabs((getY(1,0,1,L)-getY(1,0,1,R))/2)>=EPS*1000);
 dK=C;
//getch();


/*Vivod rez na ekran*/
 X=0;
 while(X<1.05)
 {
  cprintf("F(%3.2f)=%5.9f   F'(%3.2f)=%5.9f\r\n",X,inF(X),X,getdY(X,0,1,dK));
  X += 0.05;//shag
 }
 getch();


/*integrirovanie*/
 textcolor(WHITE);
 cprintf("\r\n3. Integral\r\n");
 textcolor(LIGHTBLUE);
 cprintf("int(0,1,y^2dt)\r\n");
 textcolor(WHITE);
 cprintf("\nInt=%5.5f\r\n",Integr());
 getch();


/*zapolnenie setki interpol*/
 for(i=0;i<=N;i++)
  {
   IntX[i]=iMin+i*iStep;
   IntY[i]=inF(IntX[i]);
  }

/*obrisovka ekrana*/
 gd=DETECT;
 initgraph(&gd,&gm,"");

 setcolor(WHITE);
 line(20,460,640,460);
 line(20,460,20,0);
 outtextxy(10,0,"y");
 outtextxy(630,465,"x");
 setcolor(LIGHTBLUE);
 outtextxy(400,10,"Runge-Kutt");
 setcolor(LIGHTBLUE);
 line(500,13,550,13);
 setcolor(1501);
 outtextxy(400,20,"Spline    ");
 setcolor(1501);
 line(500,23,550,23);

/*tochki interpol*/
 setcolor(CYAN);
 X=0;
 do
 {
  circle(20+(int)(X/DX),480-37-(int)(inF(X)/DY),2);
  X+=iStep;

 }
 while(X<=1);

/*sam grafik*/
 setcolor(LIGHTBLUE);
 X=0;
 moveto(20+X/DX,480-37-inF(X)/DY);
 while(X<iMax+0.01)
  {
   lineto(20+X/DX,480-37-inF(X)/DY);
   X+=0.05;
  }
 getch();

/*grafik splaina*/
 setcolor(1501);
 X=0;
 moveto(20+X/DX,480-37-splain(X)/DY);
 while(X<iMax+0.1)
  {
   lineto(20+X/DX,480-37-splain(X)/DY);
   X+=0.03;
  }
 getch();
 closegraph();


 clrscr();
 cprintf("Tablica\n\r\n");

/*vivodim sravneniya funk funk' splaina*/
 X=0;
 do
 {
  cprintf("X=%2.2f   F(%3.2f)=%5.9f  F'(%3.2f)=%5.9f   Spline(%3.2f)=%5.9f\r\n",X,X,inF(X),X,getdY(X,0,1,dK),X,splain(X));
  X+=0.05;
 }
 while(X<=1.05);
 getch();
}