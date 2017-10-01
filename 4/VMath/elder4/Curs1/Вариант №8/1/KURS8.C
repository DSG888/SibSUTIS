#include <graphics.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
typedef float typeY   [2];
typedef float typeC   [4][4];
typedef float typeD   [4];
typedef float typeMix [6];
typedef float typeH   [5];

float k,eps=0.0001,H,
   y0=1,y1=0.5, kkk;
typeY yyy;
typeC ccc;
typeD ddd;
typeMix xxx,mmm,uuu,uuul;
typeH hhh;

/*--ищем коэфф. k ---------------------------------------------------------*/
float fk(float x)
{
  return(2*x*x*x-sin(x)-3);
}
float find_k()
{
  float h=1,x=0,y=0,c,a,b;
  while(fk(a)*fk(b)>0){
    y++;
    h=1/y;
    a=x;
    b=a+h;
    while((a!=y)&&(fk(a)*fk(b)>=0)){
      a=a+h;
      b=b+h;
    }
  }
  while(fabs(b-a)/2>=eps){
    c=(b+a)/2;
    if(fk(a)*fk(c)<0)b=c; else a=c;
  }
  return (b+a)/2;
}
/*--решаем ду---------------------------------------------------------------*/
float fy(float x,float y,float yl,float yll)
{
  return(yll-cos(yll)-(x*x+y)-k*yl);
}
float diffur(float x, float y, float yl)
{
  float a,c,fa,fb,d,h,b;
  fa=fb=d=h=1;
  c=0;
  a=1;
  b=0;
  while(fa*fb>0){
    a--;
    b++;
    fa=fy(x,y,yl,a);
    fb=fy(x,y,yl,b);
  }
  float fc;
  c=0;
  d=(fb*a-fa*b)/(fb-fa);
  while(fabs(d-c)>eps){
    c=d;
    fc=fy(x,y,yl,c);
    if(fa*fc<0){b=c; fb=fc;}else{a=c; fa=fc;};
    d=(fb*a-fa*b)/(fb-fa);
  }
//rez = d.
  return(d);
}
void rongekutt(float xi, float h,typeY Y)
{
  typeY Y_;
  Y_[0]=Y[0]+h*Y[1];
  Y_[1]=Y[1]+h*diffur(xi,Y[0],Y[1]);
  Y[0]=Y[0]+(h/2)*Y_[1];
  Y[1]=Y[1]+(h/2)*diffur(xi+h,Y_[0],Y_[1]);
}
void dp(float kr,typeY Y)
{
  float h=0.05, xi=0;
  typeY Yh, Yh2;
  Yh[0]=Yh2[0]=y0;
  Yh[1]=Yh2[1]=kr;
  while(xi<1){
    rongekutt(xi,h,Yh);
    rongekutt(xi,h/2,Yh2);
    rongekutt(xi+h/2,h/2,Yh2);
    if(fabs(Yh[0]-Yh2[0])>3*eps){
      h=h/2;
      xi=0;
      Yh[0]=Yh2[0]=y0;
      Yh[1]=Yh2[1]=kr;
    }else xi=xi+h;
  }
  H=h;
  Y[0]=Yh2[0];
  Y[1]=Yh2[1];
  printf("y(1)=%f",Y[0]);
  printf("     y'(1)=%f\n",Y[1]);
}
void strelba()
{
  printf("search int:\n");
  float a=-2,b=-1.5,h=0.5;
  typeY ya,yb,yc;
  dp(a,ya);
  float t;
  if(ya[1]<y1)t=1;else t=0;
  while(t==(ya[1]<y1)){
    if(ya[1]<y1){ t=1; a=b; b=b+h;}else{t=0; b=a; a=a-h;}
    dp(a,ya);
  }
  b=a; a=a-h;

  printf("a=%f",a);
  printf("   b=%f\n",b);
  dp(a,ya);
  dp(b,yb);
  float c;
  do{
    c=(a+b)/2;
    dp(c,yc);
    if((ya[1]-y1)*(yc[1]-y1)<0){ b=c; yb[0]=yc[0]; yb[1]=yc[1];}
    else { a=c; ya[0]=yc[0]; ya[1]=yc[1];}
  }while(fabs(y1-yc[1])>eps);
  kkk=c;
  printf("k=y'(0)=%f \n",kkk);
}
/*----spline---------------------------------------------------------------*/
void znach()
{
  int i;
  for(i=0;i<6;i++){xxx[i]=0.2*i;}
  for(i=0;i<5;i++){hhh[i]=fabs(xxx[i+1]-xxx[i]);}
  for(i=0;i<4;i++){
    ccc[i][i]=(hhh[i]+hhh[i+1])/3;
    if(i>0)ccc[i][i-1]=hhh[i]/6;
    if(i<4)ccc[i][i+1]=hhh[i+1]/6;
    ddd[i]=((uuu[i+2]-uuu[i+1])/hhh[i+1])-((uuu[i+1]-uuu[i])/hhh[i]);
  }
}
void prhod(typeC c, typeD d)
{
  float b;
  int i,j,l;
  for(i=0;i<3;i++){
    for(j=i+1;j<4;j++){
      b=c[j][i]/c[i][i];
      for(l=i;l<4;l++){c[j][l]=c[j][l]-c[i][j]*b;}
      d[j]=d[j]-d[i]*b;
    }
  }
}
void obrhod(typeC c, typeD d, typeMix m)
{
  int i,j;
  for(i=4;i>0;i--){
    m[i]=d[i-1];
    for(j=4;j>i;j--){m[i]=m[i]-c[i-1][j-1]*m[j];}
    m[i]=m[i]/c[i-1][i-1];
  }
  m[0]=0;
  m[5]=0;
}
float spline(float x)
{
  int i;
  for(i=1;i<6;i++){if((x>=xxx[i-1])&&(x<=xxx[i]))break;}
  return(mmm[i-1]*(xxx[i]-x)*(xxx[i]-x)*(xxx[i]-x)/(6*hhh[i-1])
        +mmm[i]*(x-xxx[i-1])*(x-xxx[i-1])*(x-xxx[i-1])/(6*hhh[i-1])
        +(uuu[i-1]-mmm[i-1]*hhh[i-1]*hhh[i-1]/6)*((xxx[i]-x)/hhh[i-1])
        +(uuu[i]-mmm[i]*hhh[i-1]*hhh[i-1]/6)*((x-xxx[i-1])/hhh[i-1])
  );
}
/*-------------------------------------------------------------------------*/
int kx(float x)
{
  return(50+x*500);
}
int ky(float x)
{
  return(460-x*300);
}
void graphik()
{
  int gd=0, gm;
  initgraph(&gd,&gm,"l:\\bgi");
  cleardevice();
  uuu[0]=y0;
  yyy[0]=y0;
  yyy[1]=kkk;
  line(kx(-0.1),ky(0),kx(1.5),ky(0));
  line(kx(0),ky(-0.1),kx(0),ky(1.5));
  outtextxy(kx(0.01),ky(-0.01),"0");
  circle(kx(0),ky(1),1);
  circle(kx(1),ky(0),1);
  outtextxy(kx(-0.02),ky(1),"1");
  outtextxy(kx(1.01),ky(-0.01),"1");
  float i=0;
  int j=1,ind=0;
  setcolor(11);
  circle(kx(0),ky(uuu[0]),2);
  moveto(kx(0),ky(yyy[0]));
  while(i<=1){
    rongekutt(i,H,yyy);
    i=i+H;
    ind++;
    lineto(kx(i),ky(yyy[0]));
    if(ind==int(0.2/H+1)){
      ind=0;
      uuu[j]=yyy[0];
      circle(kx(i),ky(uuu[j]),2);
      j=j+1;
    }
  }
  outtextxy(450,50,"- graphik");
  getch();
  znach();
  prhod(ccc, ddd);
  obrhod(ccc, ddd, mmm);
  setcolor(13);
  outtextxy(450,60,"- spline");
  i=0;
  moveto(kx(i),ky(spline(i)));
  while(i<0.99){
    i=i+H;
    lineto(kx(i),ky(spline(i)));
  }
  getch();
  closegraph();
}
/*---integral-------------------------------------------------------------*/
float findI(float xi)
{
  typeY yy;
  float x=0;
  yy[0]=y0;
  yy[1]=kkk;
  while(x<xi){
    rongekutt(x,H,yy);
    x=x+H;
  }
  return(yy[1]);
}
void printrez()
{
  int i=0;
  typeY yy;
  float x=0;
  yy[0]=y0;
  yy[1]=kkk;
  printf("y(%f)=%f    y'(%f)=%f    spline(%f)=%f\n",
          x,yy[0],x,yy[1],x,spline(x));
  while(x<1){
    rongekutt(x,H,yy);
    x=x+H;
    i++;
    if(i==int(0.05/H+1)){
      printf("y(%f)=%f    y'(%f)=%f    spline(%f)=%f\n",
              x,yy[0],x,yy[1],x,spline(x));
      i=0;
    }
  }
  getch();
}
/*-------------------------------------------------------------------------*/
void main ()
{
   clrscr();
   k=find_k();
   printf("koren yravneniya : %f\n",k);
   getch();
   printf("Strelba:\n");
   strelba();
   getch();
   graphik();
   clrscr();
   float x=0.05, h=0.05;
   while(x<1){
     printf("  I(%f)=%f \n",x,findI(x));
     x=x+h;
   }
   getch();
   clrscr();
   printrez();
}