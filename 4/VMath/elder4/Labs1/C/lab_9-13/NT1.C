#include <stdio.h>
#include <graphics.h>

#define H 0.2
#define N 5

int gd=DETECT, gm=VGAHI;

double x[N]={1.0, 1.2, 1.4, 1.6, 1.8}, dlty[N][N];

double fnc(double a)
{
        return 1.0/a;
}

int ft(int a)
{
        int i, rs=1;
        for(i=1; i<a+1; i++)rs=rs*i;
        return rs;
}

void nt1_tbl()
{
        int i, j, k=1;
        for(i=0; i<N; i++)dlty[i][0]=fnc(x[i]);
        for(j=1; j<N; j++){
          for(i=0; i<N-k; i++)dlty[i][j]=dlty[i+1][j-1]-dlty[i][j-1];
          k++;
        }
}

double nt1(double nx)
{
        int i, j;
        double q, bq=1;
        q=(nx-x[0])/H;
        nx=dlty[0][0];
        for(j=1; j<N; j++){
                 bq*=q-j+1;
                 nx+=(dlty[0][j]/ft(j))*bq;
        }
        return nx;
}

void osi()
{
        int i;
				initgraph(&gd, &gm, "c:\\bc31\\bgi");
        line(0, 240, 639, 240);
        line(320, 0, 320, 479);
        for(i=0; i<5; i++){
                 line(120+100*i, 237, 120+100*i, 243);
                 line(317, 40+100*i, 323, 40+100*i);
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
        putpixel(320+k*100, 240-fk*100, clr);
}

void grf_pt()
{
        int i;
        for(setcolor(7), i=0; i<N; i++)circle(320+x[i]*100, 240-fnc(x[i])*100, 3);
}

int main()
{
        double k;
        nt1_tbl();
        printf("\nFirst Formul of Nuton for function y=1/x\n\ny(1.5)=%lf\nnty(1.5)=%lf\n", fnc(1.5), nt1(1.5));
        getchar();
        osi();
        for(k=0.001; k<3.0; k+=0.001){
              grf(k, nt1(k), 4);
              grf(k, fnc(k), 2);
        }
        grf_pt();
        getchar();
        closegraph();
        return 0;
}