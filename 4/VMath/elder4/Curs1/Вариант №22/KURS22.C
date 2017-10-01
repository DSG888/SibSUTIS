#include <graphics.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
typedef float typeY   [2];
typedef float typeD   [5][5];
typedef float typeMix [5];

float k,eps=0.0001,H,
   y0=1,y1=0.5, kkk;
typeY yyy;
typeD ddd;
typeMix xxx,uuu;

/*--ищем коэфф. k ---------------------------------------------------------*/
float fk(float x)
{
  return(x*x*x*x*x-sin(x)-1);
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
  return(yll-(x*x+y)-k*yl+sin(yll)-2*yl);
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
  float kk [4][2];
  kk[0][0]=Y[1];
  kk[0][1]=diffur(xi,Y[0],Y[1]);
  kk[1][0]=Y[1]+(h/2)*kk[0][1];
  kk[1][1]=diffur(xi+h/2,Y[0]+(h/2)*kk[0][0],Y[1]+(h/2)*kk[0][1]);
  kk[2][0]=Y[1]+(h/2)*kk[1][1];
  kk[2][1]=diffur(xi+h/2,Y[0]+(h/2)*kk[1][0],Y[1]+(h/2)*kk[1][1]);
  kk[3][0]=Y[1]+h*kk[2][1];
  kk[3][1]=diffur(xi+h,Y[0]+h*kk[2][0],Y[1]+h*kk[2][1]);
  Y[0]=Y[0]+(h/6)*(kk[0][0]+2*kk[1][0]+2*kk[2][0]+kk[3][0]);
  Y[1]=Y[1]+(h/6)*(kk[1][0]+2*kk[1][1]+2*kk[2][1]+kk[3][1]);
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
  printf("     y1(1)=%f\n",Y[1]);
}
void strelba()
{
  printf("search int:\n");
  float a=-2,b=-1.5,h=0.5;
  typeY ya,yb,yc;
  dp(a,ya);
  float t;
  if(ya[0]<y1)t=1;else t=0;
  while(t==(ya[0]<y1)){
    if(ya[0]<y1){ t=1; a=b; b=b+h;}else{t=0; b=a; a=a-h;}
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
    if((ya[0]-y1)*(yc[0]-y1)<0){ b=c; yb[0]=yc[0]; yb[1]=yc[1];}
    else { a=c; ya[0]=yc[0]; ya[1]=yc[1];}
  }while(fabs(y1-yc[0])>eps);
  kkk=c;
  printf("k=y1(0)=%f \n",kkk);
}
/*----nuton----------------------------------------------------------------*/
void znach()
{
  int i,j;
  for(i=0;i<6;i++){xxx[i]=0.2*i;}
  for (i=0;i<5;i++){ddd[i][0]=uuu[i+1]-uuu[i];
  }
  for (i=1;i<5;i++){
    for(j=0;j<4;j++){
      ddd[j][i]=ddd[j+1][i-1]-ddd[j][i-1];
    }
  }
}
float pn(float x)
{
  float s,q0,q,fac;
  s=uuu[0];
  fac=1;
  q0=(x-xxx[0])/0.2;
  q=q0;
  int j;
  for(j=1;j<6;j++){
    fac=fac*j;
    s=s+(ddd[0][j-1]*q)/fac;
    q=q*(q0-j);
  }
  return(s);
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
  initgraph(&gd,&gm,"c:\\lang\\bgi");
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
  setcolor(13);
  outtextxy(450,60,"- pn");
  i=0;
  moveto(kx(i),ky(pn(i)));
  while(i<=1){
    i=i+H;
    lineto(kx(i),ky(pn(i)));
  }
  getch();
  closegraph();
}
/*---integral-------------------------------------------------------------*/
void findq()
{ float h=0.01,x,Q,a=0,b=1;
  x=0.01;
  Q=0;
  while(x<0.98){
    Q=(pn(x)*pn(x)*2)/3+(pn(x+h)*pn(x+h))/3;
    x=x+2*h;
  }
  Q=(pn(x)*pn(x)*2)/3+(pn(a)*pn(a)+pn(b)*pn(b))/6;
  Q=Q*2*h;
  printf("Q = %f\n\n",Q);
}
void printrez()
{
  int i=0;
  typeY yy;
  float x=0;
  yy[0]=y0;
  yy[1]=kkk;
  printf("y(%f)=%f    y1(%f)=%f    pn(%f)=%f\n",
          x,yy[0],x,yy[1],x,pn(x));
  while(x<0.95){
    rongekutt(x,H,yy);
    x=x+H;
    i++;
    if(i==int(0.1/H)){
      printf("y(%f)=%f    y1(%f)=%f    pn(%f)=%f\n",
              x,yy[0],x,yy[1],x,pn(x));
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
   findq();
   getch();
   printrez();
}