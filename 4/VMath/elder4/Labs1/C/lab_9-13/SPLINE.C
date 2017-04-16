#include <stdio.h>
#include <graphics.h>

#define N 5

int gd=DETECT, gm=VGAHI;

double x[N]={1.0, 2.0, 3.0, 4.0, 5.0}, y[N]={2.0, 3.0, 2.0, 1.0, 2.0};
double m[N], mx[N-2][N-1];

double dabs(double a)
{
        if(a<0.0)return -a;
        return a;
}

double fnd_hi(int i)
{
	return (x[i]-x[i-1]);
}

int iabs(int a)
{
        if(a<0)return -a;
        return a;
}

double pow(double a, int i)
{
        int j=0;
        double rez=1;
        for(j=0; j<i; j++) rez*=a;
        return rez;
}

void fill_mx()
{
        int i=0,j=0;
        for(i=1; i<N-1; i++)
          for(j=0; j<N-2; j++){
                   if((i-1)==j)mx[i-1][j]=(fnd_hi(i)+fnd_hi(i+1))/3.0;
                     else if(j==i)mx[i-1][j]=(fnd_hi(i+1))/6.0;
                       else if(j==(i-2))mx[i-1][j]=(fnd_hi(i))/6.0;
                         else if(iabs((i-1)-j)>=2)mx[i-1][j]=0.0;
          }
        for(i=1; i<N-1; i++)mx[i-1][N-2]=(y[i+1]-y[i])/fnd_hi(i+1)-(y[i]-y[i-1])/fnd_hi(i);
}

void slau_gu()
{
        int i=0, j=0, k=0;
	double mr=0.0;
	for(i=0; i<N-2; i++){
   	         for(j=i+1; j<N-1; j++){
                   if((mr=-(mx[j][i]/mx[i][i]))!=0)
         	   for(k=i; k<N; k++)mx[j][k]+=mr*mx[i][k];
                 }
        }
	for(i=N-3; i>-1; i--){
   		for(m[i+1]=mx[i][N-2], j=N-3; j>i; j--)m[i+1]-=mx[i][j]*m[j+1];
       		m[i+1]/=mx[i][i];
   	}
        m[0]=0.0;
        m[N-1]=0.0;
}

int i_rtn(double a)
{
        int k=0;
        if(a>1.0 && a<2.0)return 1;
        if(a>4.0 && a<5.0)return 4;
        if(a>2.3 && a<2.5)return 3;
        for(k=0; k<N; k++)
                 if(a>=x[k] && a<=x[k+1]){
                   if(dabs(a-x[k])>dabs(x[k+1]-a))return k+1;
                     else return k;
                 }
}

double fnc(double a)
{
        int i=0;
        double hi=0.0;
        i=i_rtn(a);
        hi=fnd_hi(i);
        return (m[i-1]*pow((x[i]-a), 3))/(6.0*hi)+(m[i]*pow((a-x[i-1]), 3))/(6.0*hi)+((y[i-1]-(m[i-1]*pow(hi, 2))/6.0)*(x[i]-a)/hi)+((y[i]-(m[i]*pow(hi, 2))/6.0)*(a-x[i-1])/hi);
}

void osi()
{
        int i;
        initgraph(&gd, &gm, "");
        line(0, 240, 639, 240);
        line(320, 0, 320, 479);
        for(i=0; i<11; i++){
                 line(70+50*i, 237, 70+50*i, 243);
                 line(317, 40+50*i, 323, 40+50*i);
        }
        moveto(310 ,10);
        outtext("y");
        moveto(600 ,250);
        outtext("x");
        moveto(310 ,250);
        outtext("0");
}

void grf(double k, double fk, int clr)
{
        putpixel(320+k*50, 240-fk*50, clr);
}

void grf_pt()
{
        int i=0;
        for(setcolor(7), i=0; i<N; i++)circle(320+x[i]*50, 240-fnc(x[i])*50, 3);
}

int main()
{
        double k=0.0;
        fill_mx();
        slau_gu();
        printf("Program SPLine\n\nfnc(2.5)= %.5lf\n", fnc(2.5));
        getchar();
        osi();
        for(k=1.0; k<5.0; k+=0.0001){
                   grf(k, fnc(k), 2);
        }
        grf_pt();
        getchar();
        closegraph();
        return 0;
}
