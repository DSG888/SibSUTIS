#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include<graphics.h>
#include<string.h>

#define e 0.01
#define N 5

float k,k1,y1=2,y0=1,H,rez[2][20];
float yyy[2],ccc[4][4],ddd[4],xxx[6],mmm[6],uuu[6],uuul[6],hhh[5];

/******************Naxodim__naimenwiy__koren__k*****************************/

float fk(float x)
{
 return 2*x*x*x-sin(x)-3;
}

float koren_k()
{
  float c,h=1,x=0,y=0,a,b;
  printf("\n\n1. Naxodim koren' yravneniya  2*x*x*x-sin(x)-3=0:\n\n");
  while(fk(a)*fk(b)>0)          /*po MPD*/
    {
      y++;
      h=1/y;
      a=x;
      b=a+h;
      while((a!=y)&&(fk(a)*fk(b)>=0))
	{
	 a=a+h;
	 b=b+h;
	}
    }

  do
    {
      c=(a+b)/2;
      if (fk(b)*fk(c)<0) a=c;
      else b=c;
    }
  while ((fabs(b-a))/2>e);
 return (a+b)/2;
}

/*******************Reweniye DY**********************************************/
float fy(float x,float y,float yl,float yll)
{
  return yll+sin(yll)-sin(yl)-k*yl+y+x*x;  /*yravneniye*/
}

float diffyr(float x,float y,float yl)
{
  float a,b,c,fb,fc,fa,d;
  int i;
  fa=fb=d=1;
  a=1;
  b=0;
  while(fa*fb>0)
    {                      /*iwem interval dlya diffyra otn-no yll*/
     a--;
     b++;
     fa=fy(x,y,yl,a);
     fb=fy(x,y,yl,b);
    }

  c=0;
  d=(fb*a-fa*b)/(fb-fa);
  while(fabs(d-c)>e)
    {
     c=d;
     fc=fy(x,y,yl,c);
     if(fa*fc<0)
	{
	     b=c; fb=fc;
	}
     else
	   {
	    a=c; fa=fc;
	   }
     d=(fb*a-fa*b)/(fb-fa);
    }
  return d;
}


void rungekutt(float xi,float h,float Y[2])
{
  float Y_[2];       /*Runge-kutte s ysredneniyem po proizvodnoy*/

  Y_[0]=Y[0]+h*Y[1];
  Y_[1]=Y[1]+h*diffyr(xi,Y[0],Y[1]);

  Y[0]=Y[0]+(h/2)*(Y[1]+Y_[1]);
  Y[1]=Y[1]+(h/2)*(diffyr(xi,Y[0],Y[1])+diffyr(xi+h,Y_[0],Y_[1]));

}

void peres4et(float k1,float Y[2])
{
  float h=0.01, xi=0;
  float Yh[2],Yh2[2];               /*dvoynoy peres4et*/
  Yh[0]=Yh2[0]=y0;
  Yh[1]=Yh2[1]=k1;
  while(xi<1)
   {
    rungekutt(xi,h,Yh);
    rungekutt(xi,h/2,Yh2);
    rungekutt(xi+h/2,h/2,Yh2);
    if(fabs(Yh[0]-Yh2[0])>15*e)
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
  printf("y(1)=%2.4f",Y[0]);
  printf("   y(1)=%2.4f\n",Y[1]);
}


void strelb()
{
  float a=-2,b=-1.5,h=0.5;
  float ya[2],yb[2],yc[2];
  float t;
  float c;
  printf("\n\n2. Iwem yl(0):\n");
  peres4et(a,ya);

  if (ya[0]<y1) t=1; else t=0;
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
     peres4et(a,ya);
    }
  b=a; a=a-h;

  //printf("[ %2.4f;",a);
  //printf("%2.4f ]\n",b);
  peres4et(a,ya);
  peres4et(b,yb);
  do
   {
    c=(a+b)/2;
    peres4et(c,yc);
    if((ya[0]-y1)*(yc[0]-y1)<0)
     {
       b=c; yb[0]=yc[0]; yb[1]=yc[1];
     }
    else
     {
       a=c; ya[0]=yc[0]; ya[1]=yc[1];
      }
   }
  while(fabs(y1-yc[0])>e);
  k1=c;
  printf("\n   k1=yl(0)=%f \n",k1);
}


/**********************SPlain***********************************************/

void znach()
{
  int i;
  for(i=0;i<6;i++)
    {
      xxx[i]=0.2*i;
    }
  for(i=0;i<5;i++)
    {
      hhh[i]=fabs(xxx[i+1]-xxx[i]);
    }
  for(i=0;i<4;i++)
    {
    ccc[i][i]=(hhh[i]+hhh[i+1])/3;
    if(i>0)ccc[i][i-1]=hhh[i]/6;
    if(i<4)ccc[i][i+1]=hhh[i+1]/6;
    ddd[i]=((uuu[i+2]-uuu[i+1])/hhh[i+1])-((uuu[i+1]-uuu[i])/hhh[i]);
    }
}

void pryamoy(float c[4][4],float d[4])
{
  float b;
  int i,j,l;
  for(i=0;i<3;i++)
   {
    for(j=i+1;j<4;j++)
     {
      b=c[j][i]/c[i][i];
      for(l=i;l<4;l++)
       {
	 c[j][l]=c[j][l]-c[i][j]*b;
       }
      d[j]=d[j]-d[i]*b;
     }
   }
}

void obrat(float c[4][4],float d[4], float m[6])
{
  int i,j;
  for(i=4;i>0;i--)
   {
    m[i]=d[i-1];
    for(j=4;j>i;j--)
      {
	m[i]=m[i]-c[i-1][j-1]*m[j];
      }
    m[i]=m[i]/c[i-1][i-1];
   }
  m[0]=0;
  m[5]=0;
}

float spline(float x)
{
  int i;
  for(i=1;i<6;i++)
     {
      if((x>=xxx[i-1])&&(x<=xxx[i]))
	 break;
     }
  return(mmm[i-1]*(xxx[i]-x)*(xxx[i]-x)*(xxx[i]-x)/(6*hhh[i-1])
	+mmm[i]*(x-xxx[i-1])*(x-xxx[i-1])*(x-xxx[i-1])/(6*hhh[i-1])
	+(uuu[i-1]-mmm[i-1]*hhh[i-1]*hhh[i-1]/6)*((xxx[i]-x)/hhh[i-1])
	+(uuu[i]-mmm[i]*hhh[i-1]*hhh[i-1]/6)*((x-xxx[i-1])/hhh[i-1]));
}



/*******************************GRafic***************************************/
void init()
{
 int gd=0, gm;
 initgraph(&gd,&gm,"d:\\work\\cpp\\bgi");
 cleardevice();
 setlinestyle(SOLID_LINE,3,THICK_WIDTH);
 setcolor(7);
 line(50+(-0.1)*500,460-0*300,50+1.5*500,460-0*300);
 line(50+0*500,460-(-0.1)*300,50+0*500,460-1.5*300);
 outtextxy(50+0.01*500,460-(-0.015)*300,"0");
 outtextxy(50+(-0.02)*500,460-1*300,"1");
  //line(45,460-60,55,460-1*300);
 outtextxy(50+(1.01)*500,460-(-0.01)*300,"1");
  //line(50+1*500,395-1*300,50+1*500,405-300);
 return;
}


void graphik()
{
  float i;
  int j=1,ind=0,t;
  init();
  uuu[0]=y0;
  yyy[0]=y0; rez[0][0]=yyy[0];
  yyy[1]=k1; rez[1][0]=yyy[1];
  H=0.05;
 // cleardevice();
 //setlinestyle(SOLID_LINE,3,THICK_WIDTH);
  setcolor(14);
  moveto(50+0*500,460-yyy[0]*300);
  while(i<=1)
       {
	rungekutt(i,H,yyy);
	i=i+H;
	ind++;
	lineto(50+i*500,460-yyy[0]*300);
	t=0.2/H+1.0;
	if(ind==t)
	  {
	   ind=0;
	   uuu[j]=yyy[0];  //rez[0][j]=yyy[0];
	   //uuul[j]=yyy[1]; rez[1][j]=yyy[1];
	   circle(50+i*500,460-uuu[j]*300,3);
	   j=j+1;
	  }
	}
  outtextxy(450,50,"- GrAphik");
  getch();
  znach();
  pryamoy(ccc,ddd);
  obrat(ccc,ddd,mmm);
  setcolor(13);
  outtextxy(450,60,"- Spline");
  i=0;
  moveto(50+i*500,460-spline(i)*300);
  while(i<=1)
    {
    lineto(50+i*500,460-spline(i)*300);
    i=i+H;
    }
    lineto(50+1*500,460-spline(1)*300);
  getch();
  closegraph();
}

/***********************Sila_Toka*******************************************/
float findI(float xi)
{
  float yy[2];
  float x=0;

  yy[0]=y0;
  yy[1]=k1;
  while(x<xi)
    {
     rungekutt(x,H,yy);
     x=x+H;
    }
  return(yy[1]);
}

void printrez()
{
  float yy[2];
  double x=0;
  int i=0,t;
  yy[0]=y0;
  yy[1]=k1;
  printf("y(%f)=%f    y'(%f)=%f    spline(%f)=%f\n", x,yy[0],x,yy[1],x,spline(x));
  while(x<1){
    rungekutt(x,H,yy);
    x=x+H;
    t=0.1/H;
    i++;
  if (i==t)
    {
     printf("y(%f)=%f    y'(%f)=%f   spline(%f)=%f\n",
	   x,yy[0], x,yy[1],x,spline(x));
   i=0;
    }
 }
 getch();
}

/*************************BoSs**********************************************/
void main()
{
 float x=0, h=0.01;
 clrscr();
 //textbackground(5);
 puts("===============================================================================");
 puts("||          Kyrsovaya pabota po vu4islitel'noy matematike                    ||");
 puts("||                                                                           ||");
 puts("||                Nestroyevoy E.I., gr.VM-46                                 ||");
 puts("||                      variant-12                                           ||");
 puts("||    Dano: yll+sin(yll)+x*x+y+k*y'-sin(y')=0                                ||");
 puts("||          y(0)=1                                                           ||");
 puts("||          y(1)=0.5                                                         ||");
 puts("===============================================================================");
 getch();
 k=koren_k();
 printf("   k=%2.4f\n",k);
 getch();
 strelb();
 getch();
 puts("\n\n3. Grafiki v to4kax xE[0;1] s wagom h=0.2:\n");
 getch();
 graphik();
 puts("\n   4. Sila toka pri tE(0;1) s wagom h=0.05\n");
 while(x<=1)
 {
  printf("             I ( %f ) = %f  \n",x,findI(x));
  x=x+h;
 }
 getch();
 clrscr();
 puts("\n      5. Rezultatu vu4isleniya v to4kax xE[0;1] s wagom h=0.05\n");
 printrez();
// getch();
}





