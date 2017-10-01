#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define E 0.001
#define N 6
#define y0 1
#define y1 0.5
/*-------------------------------Functions------------------------------------*/

void double_recalc(double k1,double Y[2]);
void RK_II_t(double xi,double h,double Y[2]);
/*------------------------------Variables-------------------------------------*/
double X[N]={0.0, 0.2, 0.4, 0.6, 0.8, 1.0},Z[2],table_nyton[N][N];
int i=0,j=0;
double k,k1,H;
/*----------------------------------------------------------------------------*/
/*===============================Zadannie funkcii=============================*/
double Gfunc(double x,double y,double yl,double yll)
{
      return (yll-sin(yll)-(x*x+y)-k*yl-cos(yl));
}
double Kfunc(double x)
              {
        return (2*x-sin(x)-1.2);
}
/*----------------------------------------------------------------------------*/
/*====================Interpolyaciya po Nytonu=============================*/
float nuton(float x)
 {
  float s=0,q0,q,fac;
  s=table_nyton[0][0];
  fac=1;
  q0=x/0.2;
  q=q0;
  int j=0;
  for(j=1;j<N;j+=1)
  {
    s=s+(table_nyton[0][j]*q)/fac;
    q=q*(q0-j);
    fac=fac*(j+1);
  }
  return(s);
}

void nt_table()
{
  int i=0,j=0;
  for (i=1;i<N;i++)
  {
    for (j=N-i-1;j>=0;j--)
   {
      table_nyton[j][i]=table_nyton[j+1][i-1]-table_nyton[j][i-1];
   }
  }
}

/*----------------------------------------------------------------------------*/
/*============================================================================*/
double koren_k()
{
  double c,h=1,x=0,y=0,a,b;
  printf("\n\n1)    Koren' yravneniya  2*x-sin(x)-1.2=0:\n\n");
  while(Kfunc(a)*Kfunc(b)>0)          /*po MPD*/
    {
      y++;
      h=1/y;
      a=x;
      b=a+h;
      while((a!=y)&&(Kfunc(a)*Kfunc(b)>=0))
	{
	 a=a+h;
	 b=b+h;
	}
    }
  do
    {
      c=(a+b)/2;
      if (Kfunc(b)*Kfunc(c)<0) a=c;
      else b=c;
    }
  while ((fabs(b-a))/2>E);
 return (a+b)/2;
}

/*================================Metod strelb================================*/
void strelb()
{
  double a=-2,b=-1.5,h=0.5;
  double ya[2],yb[2],yc[2];
  double t;
  double c;
  double_recalc(a,ya);
  if (ya[0]<y1) t=1;
  else t=0;
  while(t==(ya[0]<y1))
    {
        if(ya[0]<y1)
        {
	      t=1; a=b; b=b+h;
        }
        else
        {
       	  t=0; b=a; a=a-h;
         }
        double_recalc(a,ya);
    }
  b=a;
  a=a-h;
  double_recalc(a,ya);
  double_recalc(b,yb);
  do
   {
    c=(a+b)/2;
    double_recalc(c,yc);
    if((ya[0]-y1)*(yc[0]-y1)<0)
     {
       b=c;
       yb[0]=yc[0];
       yb[1]=yc[1];
     }
    else
     {
       a=c;
       ya[0]=yc[0];
       ya[1]=yc[1];
      }
   }
  while(fabs(y1-yc[0])>E);
  k1=c;
  printf("\ny'(0)=%lf \n",k1);
}

/*----Double recalculation----*/

void double_recalc(double k1,double Y[2])
{
  double h=0.05, xi=0;
  double Yh[2],Yh2[2];
  Yh[0]=Yh2[0]=y0;
  Yh[1]=Yh2[1]=k1;
  while(xi<1)
   {
    RK_II_t(xi,h,Yh);
    RK_II_t(xi,h/2,Yh2);
    RK_II_t(xi+h/2,h/2,Yh2);
    if(fabs(Yh[0]-Yh2[0])>3*E)
     {
      h=h/2;
      xi=0;
      Yh[0]=Yh2[0]=y0;
      Yh[1]=Yh2[1]=k1;
     }
    else xi=xi+h;
    }
  H=h;
  Y[0]=Yh2[0];
  Y[1]=Yh2[1];
}
/*============================================================================*/

/*===========================Naxodim y"=======================================*/
double diff(double x,double y,double yl)
{
  double a,b,c,fb,fc,fa,d;
  int i;
  fa=fb=d=1;
  a=1;
  b=0;
  while(fa*fb>0)
    {
      a--;
      b++;
      fa=Gfunc(x,y,yl,a);
      fb=Gfunc(x,y,yl,b);
    }
  c=0;
  d=(fb*a-fa*b)/(fb-fa);
  while(fabs(d-c)>E)
    {
        c=d;
        fc=Gfunc(x,y,yl,c);
        if(fa*fc<0)
	    {
	        b=c;
            fb=fc;
	    }
        else
        {
	        a=c;
            fa=fc;
	    }
        d=(fb*a-fa*b)/(fb-fa);
    }
  return d;
}
/*=============================R-K II no t====================================*/
void RK_II_t(double xi,double h,double Y[2])
{
  double Y_[2];

  Y_[0]=Y[0]+h*Y[1];
  Y_[1]=Y[1]+h*diff(xi,Y[0],Y[1]);

  Y[0]=Y[0]+(h/2)*(Y[1]+Y_[1]);
  Y[1]=Y[1]+(h/2)*(diff(xi,Y[0],Y[1])+diff(xi+h,Y_[0],Y_[1]));

}
/*=================================Haxodum I==================================*/
double findI(double xi)
{
  H=0.05;
  double yy[2];
  double x=0;

  yy[0]=y0;
  yy[1]=k1;
  while(x<xi)
    {
     RK_II_t(x,H,yy);
     x=x+H;
    }
  return(yy[1]);
}
/*----------------------------------------------------------------------------*/
/*================================BbIBOD grafika==============================*/
void init()
{
 int gd=DETECT, gm=VGAHI;
 initgraph(&gd,&gm,"c:\\temp\\bc31\\bgi\\");
 setcolor(7);
 line(50+(-0.1)*500,460-0*300,50+1.5*500,460-0*300);
 line(50+0*500,460-(-0.1)*300,50+0*500,460-1.5*300);
 outtextxy(50+0.01*500,460-(-0.015)*300,"0");
}
/*-----koordinati po x-------*/
int kx(double x)
{
  return(50+x*500);
}
/*-----koordinati po y-------*/
int ky(double x)
{
  return(460-x*200);
}
void grf(double k, double fk, int clr)
{
        lineto(kx(k), ky(fk));
}
void grf_pt()
{
        int i;
        for(setcolor(7), i=0; i<N; i++) circle(kx(X[i]), ky(table_nyton[i][0]), 3);
}
/*Grafic*/
void graphic()
{
  init();
  table_nyton[0][0]=y0;
  Z[0]=y0;
  Z[1]=k1;
  float i=0;
  int j=1,ind=0;
  setcolor(6);
  moveto(kx(0),ky(Z[0]));
  while(i<=1){
    RK_II_t(i,H,Z);
    i=i+H;
    ind++;
    lineto(kx(i),ky(Z[0]));
    if(ind==int(0.2/H))
    {
      ind=0;
      table_nyton[j][0]=Z[0];
      circle(kx(i),ky(table_nyton[j][0]),4);
      j=j+1;
    }
  }
  outtextxy(400,90,"Function");
  getch();
  nt_table();
  setcolor(2);
  outtextxy(390,160,"Nuton");
  i=0;
  moveto(kx(i),ky(nuton(i)));
  while(i<=1){
    delay (5);
    i=i+H;
    lineto(kx(i),ky(nuton(i)));
  }
  getch();
  closegraph();
}

/*=============================================================================
==============================================================================*/
void result()
{
  int i=0;
  H=0.2;
  double yy[2];
  double x=0;
  yy[0]=y0;
  yy[1]=k1;
  printf("|    y(x)          |     y'(x)         |        N(x)      |\n");
  printf("+==================+===================+===================+\n");
  printf("| y(%.2lf)=%lf | y'(%.2lf)=%lf | N(%.2lf)=%lf |\n",x,yy[0],x,yy[1],x,nuton(x));
  while (x<1)
  {
  RK_II_t(x,0.05,yy);
  x=x+0.05;
  printf("| y(%.2lf)=%lf | y'(%.2lf)=%lf | N(%.2lf)=%lf |\n",x,yy[0],x,yy[1],x,nuton(x));
  }
  getch();
}

int main ()
{
   double x=0,h=0.05;
   for(i=0;i<N;i++)
   for(j=0;j<N;j++)
   table_nyton[i][j]=0;
   clrscr();
    puts("===============================================================================");
 puts("||          Kyrsovaya pabota po vu4islitel'noy matematike                    ||");
 puts("||                                                                           ||");
 puts("||           Vipolnil: Loshkarev A.V., gr.VM-57                              ||");
 puts("||                      variant-11                                           ||");
 puts("||    Dano: y11-sin(y11)-(x*x+y)-k*y1-cos(y1)=0                              ||");
 puts("||          y(0)=1                                                           ||");
 puts("||          y(1)=0.5                                                         ||");
 puts("===============================================================================");
 getch();
 k=koren_k();
 printf("   k=%2.4f\n\n",k);
 getch();
 printf("2)    Ishem y'(0):\n");
 strelb();
 printf("\n\n3)    Vivod grafika:");
 getch();
   graphic();
   getch();
   printf("4)    Sravnenie znachenii:\n");
   result();
   clrscr();
   printf("5)    Vichislenie sili toka:\n");
   while (x<=1.05)
   {
    printf("|   I(%.2lf)=%lf   | \n",x,findI(x));
    x=x+h;
   }
   getch();
   return (0);
}
