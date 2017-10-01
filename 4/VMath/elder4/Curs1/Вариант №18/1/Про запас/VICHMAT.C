#include<math.h>
#include<conio.h>
#include<graphics.h>
#include<stdio.h>

#define E 0.0001    // tochnost' dlya itercaioonih metodov
double F[2],Y[2];   // (sm. lekcii)
double Y0[2];       //  y(x=0) i (dy/dx)(x=0)
int printing=0;     /* opredelyaet, budut li pechatatca promejutochnie
		       rezultati pri dvoinom pereschete */

	    /* zdes opredelyaetca nashe uravnenie : */
#define difur(f2) ( f2+Y[0]+Y[1]+Y[1]-sin(f2)-3*x*x )

	    /* zapolnenie vectora F(x,Y) (sm.lekcii) */
void fillF(double x, double *Y)
{
  double a,b,c=0,fc=difur(c),delta;
  int dir=2;
  F[0]=Y[1];          // pervaya proizvodnaya
	  // naidem vtoruyu proizvodnuyu v dva shaga:
		  // 1 - opredelenie diapazona
  if(fc>0)  dir=-dir;
  do
  {
    c+=dir;
    fc=difur(c);
  }while((dir*fc)<0);
		  // 2 - metod polovinnogo deleniya
  a=(dir>0) ? (c-dir) : c;
  b=a+( (dir>0) ? dir: -dir );
  do
  {
    c=(a+b)/2; fc=difur(c);
    if(fc<0)  {a=c; delta=-fc;}
    else      {b=c; delta=fc;}
  }while(delta>E*100);
  F[1]=c;
}

	     /* metod Runge-Kutta 4-go poryadka */
void rungekutt(double x, long int n)
{
  double Ytemp[2],K1[2],K2[2],K3[2],K4[2],h=x/n,xi;
  long int i;
  Y[0]=Y0[0];  Y[1]=Y0[1];
  for(i=0;i<n;i++)
  {
    xi=i*h;
    fillF(xi,Y);          K1[0]=F[0];  K1[1]=F[1];
    Ytemp[0]=Y[0]+h*K1[0]/2;  Ytemp[1]=Y[1]+h*K1[1]/2;
    fillF(x+h/2,Ytemp);   K2[0]=F[0];  K2[1]=F[1];
    Ytemp[0]=Y[0]+h*K2[0]/2;  Ytemp[1]=Y[1]+h*K2[1]/2;
    fillF(x+h/2,Ytemp);   K3[0]=F[0];  K3[1]=F[1];
    Ytemp[0]=Y[0]+h*K3[0];  Ytemp[1]=Y[1]+h*K3[1];
    fillF(x+h,Ytemp);     K4[0]=F[0];  K4[1]=F[1];
    Y[0]+=(h/6)*(K1[0]+2*K2[0]+2*K3[0]+K4[0]);
    Y[1]+=(h/6)*(K1[1]+2*K2[1]+2*K3[1]+K4[1]);
  }
  if(printing)  printf("h=%f -> y=%f, dy/dx=%f\n",h,Y[0],Y[1]);
}

	      /* reshenie difura v tochke 'x' s dvoinim pereschetom */
void doublecount(double x)
{
  long int n=1;
  double Ytemp[2],delta[2];
  rungekutt(x,n);
  do
  {
    Ytemp[0]=Y[0]; Ytemp[1]=Y[1];
    n*=2;
    rungekutt(x,n);
    delta[0]=(Ytemp[0]>Y[0]) ? (Ytemp[0]-Y[0]) : (Y[0]-Ytemp[0]);
    delta[1]=(Ytemp[1]>Y[1])?(Ytemp[1]-Y[1]):(Y[1]-Ytemp[1]);
  }while( (delta[0]>=E) || (delta[1]>=E) );
}

	     /* odin 'vistrel' v metode strelb */
void singleshot()
{
  printf("esli dy/dx(0)=%f, to:\n",Y0[1]);
  doublecount(1);
  printf("y(1)=%f, dy/dx(1)=%f\n",Y[0],Y[1]);
  getch();
}

	   /* nahojdenie dy/dx v tochke x=0 metodom strelb */
void shooting()
{
  int dir=1;
  double a,b,c,delta;
  printf("naidem dy/dx v tochke x=0 metodom strelb:\n\n");
	    // 1 - opredelenie diapazona
  Y0[1]=0;
  singleshot();
  if(Y[0]>0.3)  dir=-1;
  do
  {
    Y0[1]+=dir;
    singleshot();
  }while((dir*(Y[0]-0.3))<0);
	    // 2 - metod polovinnogo deleniya
  a=(dir>0) ? (Y0[1]-dir) : Y0[1];
  b=a+( (dir>0) ? dir : -dir );
  do
  {
    c=(a+b)/2; Y0[1]=c;
    singleshot();
    if(Y[0]<0.3)  {a=c; delta=0.3-Y[0];}
    else          {b=c; delta=Y[0]-0.3;}
  }while(delta>E);
  printf("\n itogo: dy/dx(0)=%f\n",Y0[1]);
}

#define N 6  /* kolichestvo uzlov interpolyacii */
      /* massivi, ispolzuemie pri interpolyacii: */
float xi[N+1],y[N+1],d[N-1],hi[N],Mi[N+1],m[N-1][N];

/*-------------funkcii, ispolzuemie pri interpolyacii:--------------------*/

float Spline(float xx)
{
   int i;
   float s;
   for(i=1;i<N+1;i++)
	if((xx>=xi[i-1])&&(xx<=xi[i])) break;
   if(i==6) i--;
   s=Mi[i-1]*(xi[i]-xx)*(xi[i]-xx)*(xi[i]-xx)/(6*hi[i-1])
	+Mi[i]*(xx-xi[i-1])*(xx-xi[i-1])*(xx-xi[i-1])/(6*hi[i-1])
	+(y[i-1]-(Mi[i-1]*hi[i-1]*hi[i-1]/6))*((xi[i]-xx)/hi[i-1])
	+(y[i]-(Mi[i]*hi[i-1]*hi[i-1]/6))*((xx-xi[i-1])/hi[i-1]);
   return s;
}

void p_H()
{
   int i;
   for(i=1;i<=N;i++) hi[i-1]=fabs(xi[i]-xi[i-1]);
}

void z_C()
{
   int i,j;
   for(i=0;i<N-1;i++)
   {
	 if(i>=1) m[i][i-1]=hi[i]/6;
	 m[i][i]=(hi[i]+hi[i+1])/3;
	 if(i!=3) m[i][i+1]=hi[i+1]/6;
   }
}

void z_D()
{
   int i;
   for(i=1;i<N;i++) d[i-1]=((y[i+1]-y[i])/hi[i])-((y[i]-y[i-1])/hi[i-1]);
}

void hod_pr()
{
   float b;
   int l,i,j;
   for(i=0;i<N-2;i++)
   {
	 for(j=i+1;j<N-1;j++)
	 {
	    b=m[j][i]/m[i][i];
	    for(l=i;l<N-1;l++) m[j][l]=m[j][l]-m[i][l]*b;
	    d[j]=d[j]-d[i]*b;
	 }
   }
}

void back()
{
   int i,j;
   for(i=N-2;i>=0;i--)
   {
	 Mi[i+1]=d[i];
	 for(j=3;j>=i+1;j--) Mi[i+1]=Mi[i+1]-m[i][j]*Mi[j+1];
	 Mi[i+1]=Mi[i+1]/m[i][i];
   }
   Mi[0]=0; Mi[N]=0;
}

/*---------glavnaya funkciya dlya interpolyacii i postroeniya grafika------*/

void splain_grafik()
{
    float y1,hx,hy,x1,f,s;
    int i,gd=DETECT,gm;
    p_H();
    z_C();
    z_D();
    hod_pr();
    back();
    initgraph(&gd, &gm, "");
    line(0,240,640,240);
    line(320,480,320,0);
    outtextxy(300,20,"1");
    outtextxy(620,250,"1");
    hx=300;
    hy=220;
    setcolor(13);
    x1=320; y1=240;
    for(i=0;i<N;i++) pieslice(x1+floor(hx*xi[i]),y1-floor(hy*y[i]),0,360,2);
    setcolor(10);
    moveto(x1+floor(hx*xi[0]),y1-floor(hy*y[0]));
    s=0.001;
    for(i=1;i<N;i++)
	for(f=xi[i-1]+s;f<xi[i];f+=s)
	    lineto(x1+floor(hx*f),y1-floor(hy*Spline(f)));
    getch();
    closegraph();
}


void main()
{
  int i;
  double x;
  clrscr();
  Y0[0]=1;
  shooting();
  printf("\n naidem moshnost (P=y*y) v zadannih tochkah: \n\n");
  for(x=0.12;x<1;x+=0.1)
  {
    doublecount(x);
    printf("v tochke x=%.2f P=%f \n",x,Y[0]*Y[0]);
  }
  printing=1;
  printf("\n reshim dif. ur. dlya uzlov interpolyacii:\n\n");
  for(i=0;i<6;i++)
  {
    xi[i]=i*0.2;
    if(i>=1) hi[i-1]=xi[i]-xi[i-1];
    doublecount(xi[i]);
    y[i]=Y[0];
    printf("pri x=%f,  y=%f, dy/dx=%f \n\n",xi[i],y[i],Y[1]);
    getch();
  }
  splain_grafik();
}