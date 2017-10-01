#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>

#define N 101
#define M 6
#define A 0
#define B 1
#define T 6 // Kolichestvo tochnyh znacheniy
#define R 9 // Kolichestvo iskomyh interpolirovannyh znacheniy

#define DELEN 10

void F(long float x, float y[3], float k[3]);
void rungekutt();
float *Gays(float a[][M+1], int n);
float Intr(float x[], float y[], float h[], int n, float t);
void GraphInit();
void Graphic(float x[], float y[][N], int m, int k);

float yt[N], yp[R], xx[T], xp[R], yy[M], hxx[M], H=0.01, y0=1, y1=0.3, eps = 0.0001;
float MX = 640, MY = 478, NY = 435, NX = 80;

void main()
{
  int i,j;
  float yg[2][N], xxx[N], yyy[N];

  clrscr();

  rungekutt();
  yt[1 / H] = y1;

  xx[0] = 0;   yy[0] = yt[0];
  xx[1] = 0.2; yy[1] = yt[0.2 / H];    //Vichislenie indeksa nygnoi tochki
  xx[2] = 0.4; yy[2] = yt[0.4 / H];
  xx[3] = 0.6; yy[3] = yt[0.6 / H];
  xx[4] = 0.8; yy[4] = yt[0.8 / H];
  xx[5] = 1;   yy[5] = yt[1 / H];

  printf("Metodom runge-kutta 4-go poryadka naydeny znacheniya:\n");
  for (i = 0; i < T; i++)
  {
    printf("y[%0.2f] = %0.5f\n", xx[i], yy[i]);
  }

  getch();

  hxx[0] = xx[0];
  for(i=1;i<M; i++)
   hxx[i]=xx[i]-xx[i-1];

  xp[0] = 0;
  xp[1] = 0.12;
  xp[2] = 0.32;
  xp[3] = 0.42;
  xp[4] = 0.52;
  xp[5] = 0.62;
  xp[6] = 0.72;
  xp[7] = 0.82;
  xp[8] = 0.92;


  for (i = 0; i<R; i++)
  {
    yp[i] = Intr(xx, yy, hxx, M, xp[i]);
  }

  printf("\n\nMetodom kubicheskogo splina naydeny znacheniya:    Mohnost:\n");
  for (i=0; i<R; i++)
  {
    printf("y[%0.2f] = %0.5f                                  ", xp[i], yp[i]);
    printf("y[%0.2f]^2 = %0.5f\n", xp[i], yp[i]*yp[i]);
  }
  getch();


  for (i = 0; i<N-1; i++)            //Dla grafika
  {
    yyy[i] = Intr(xx, yy, hxx, M, i*H);
    xxx[i] = i*H;
  }

  xxx[N-1] = B;
  yyy[N-1] = yt[N-1];


  for (i=0; i<N; i++)
  {
    yg[0][i] = yt[i];
    yg[1][i] = yyy[i];
  }

  Graphic(xxx, yg, N, 2);
  getch();
}

// **************************Функции****************************************

void F(float x, float y[3], float k[3]) //Вычисление коэффициентов
{
  k[0] = (sin(y[2]) + 3*x*x - y[0] - y[2]) / 2;

  k[1] = y[2];
}

void rungekutt()  //Рунге-Кутт 4-го порядка
{
  int i,t;
  float k1[3], k2[3], k3[3], k4[3], y[3], yy[3], a, b, y2, pr, h;

  a=-10; b=23;
  do
  {
    y2 = (a+b) / 2;
    h = H;
    t = 1;
    yt[N-1] = 10000;
    do
    {
      pr = yt[N-1];
      y[0] = y0;
      y[2] = y2;
      y[1] = 0;
      for (i=0; i<=t*(N-1); i++)
      {
	F(i*h, y, k1);
	F(i*h+h/2, y, k2);
	k2[0] = k2[0] + k1[0]*h/2;
	k2[1] = k2[1] + k1[1]*h/2;
	F(i*h+h/2, y, k3);
	k3[0] = k3[0] + k2[0]*h/2;
	k3[1] = k3[1] + k2[1]*h/2;
	F(i*h+h, y, k4);
	k4[0] = k4[0] + k3[0]*h;
	k4[1] = k4[1] + k3[1]*h;

	if ((i % t) == 0) yt[i/t] = y[0];

	y[0] = y[0] + (k1[0]+2*k2[0]+2*k3[0]+k4[0])*h/6;
	y[2] = y[2] + (k1[1]+2*k2[1]+2*k3[1]+k4[1])*h/6;
      }

      h = h/2;
      t = t * 2;
    }
      while (fabs(yt[N-1] - pr) > 15 * eps);

    if (yt[N-1] > y1) a = y2;
      else b = y2;

  }
   while (fabs(yt[N-1] - y1) > eps);
}


float *Gays(float a[][M+1], int n)  //Модифицированный метод Гаусса
{
 float max,buf, coef, *x;
 int i, j, k, t;
 max=a[0][0];
 x=(float*)malloc(sizeof(int)*(n+2));

 for(i=0; i<n-1; i++)
 {
   max=fabs(a[i][i]); t=i;
   for(j=i+1; j<n-1; j++)
   if (fabs(a[j][i])>max)
   {
     max=fabs(a[j][i]); t=j;
   }

   if (t!=i)
   {

     for(k=0;k<n;k++)
     {
       buf=a[i][k];
       a[i][k]=a[t][k];
       a[t][k]=buf;
     }
   }


   for(j=i+1;j<n;j++)
   {
     coef = a[j][i]/a[i][i];
     for(k=0; k<n; k++)
     {
       a[j][k]=a[j][k]-a[i][k]*coef;
     }
   }
 }
 for(i=n-2;i>=0; i--)
 {
  x[i]=a[i][n-1];
  for(j=n-2;j>i;j--)
    x[i]=x[i]-a[i][j]*x[j];
  x[i]=x[i]/a[i][i];
 }
 return x;
}

//Интерполяция кубическими сплайнами
float Intr(float x[], float y[],float h[], int n, float t)
{
  int i,j, k;
  float d[N], c[M][M], s, a3, a2;
  float *m, b[M][M+1];

  for(i=1;i<n-1;i++)
  for(j=1;j<n-1;j++)
  {
     if(i==j)        c[i][j]=(h[i]+h[i+1])/3;
     if(j==i+1)      c[i][j]=(h[i+1]/6);
     if(i-1 ==j)     c[i][j]=(h[i]/6);
     if(abs(i-j)>=2) c[i][j]=0;
     b[i-1][j-1]=c[i][j];
  }
  for(i=1;i<n-1;i++)
  {
      d[i] = (y[i+1]-y[i])/h[i+1] - (y[i]-y[i-1])/h[i];
      b[i-1][n-2]=d[i];
  }

  m=Gays(b, n-1);

  for(i=0;i<n;i++)
  {
      if((x[i]<=t)&&(x[i+1]>t))
      k=i+1;
  }



  for (i=n-1; i>0; i--) m[i] = m[i-1];
  m[0] = 0;
  m[n-1] = 0;

  a3=pow((x[k]-t),3);
  a2=pow((t-x[k-1]), 3);

 // s=m[k]*a3/(6*h[k]) + m[k+1]*a2/(6*h[k]) + (y[k-1] - m[k]*h[k]*h[k]/6)*((x[k]-t)/h[k]) + (y[k] - m[k+1]*h[k]*h[k]/6)*((t-x[k-1])/h[k]);

  s=m[k-1]*a3/(6*h[k]) + m[k]*a2/(6*h[k]) + (y[k-1] - m[k-1]*h[k]*h[k]/6)*((x[k]-t)/h[k]) + (y[k] - m[k]*h[k]*h[k]/6)*((t-x[k-1])/h[k]);

 return s;
}


void Graphic(float xxx[], float y[][N], int m, int k) //График
{
 GraphInit();
 long double hx, hy, x1, x2, y1, y2;
 float i,yN,y0,hdx,hdy,xx,yy, Ny;
 int dec,sign,j;
 char *txt,*str;

 line(NX, 1, NX, NY);
 line(NX, NY, MX, NY);
 line(NX,1,NX-4,13);       //Strelochka po y
 line(NX,1,NX+4,13);
 line(MX,NY,MX-12,NY-4);     //po x
 line(MX,NY,MX-12,NY+4);

 yN=y[1][0];
 y0=y[1][0];

 for (j=0;j<m;j++)
 {
/*   if (y[0][j]<y0) y0=y[0][j];
   if (y[0][j]>yN) yN=y[0][j];*/
   if (y[1][j]<y0) y0=y[1][j];
   if (y[1][j]>yN) yN=y[1][j];
 }

 y0=0;
 hx=(MX-NX)/(xxx[m-1]-xxx[0]);   //Masshtab  dla grafika
 hy=NY/(yN-y0);
 hdx=(MX-NX)/DELEN;                 //Shag dla delenii po x
 hdy=NY/DELEN;

 for(j=0;j<k;j++)
 for(i=1;i<m;i++)
 {
  setcolor(j+3);
  if ((y[j][i]<=yN) && (y[j][i]>=y0))
  {
    x1 = NX+(xxx[i-1]-xxx[0])*hx;
    y1 = NY-(y[j][i-1]-y0)*hy;
    x2 = NX+(xxx[i]-xxx[0])*hx;
    y2 = NY-(y[j][i]-y0)*hy;
    line((int)x1, (int)y1, (int)x2, (int)y2);
  }
 }
}

void GraphInit() //Инициализация графики
{
 int grd=DETECT,grm;

 initgraph(&grd,&grm,"");
}
