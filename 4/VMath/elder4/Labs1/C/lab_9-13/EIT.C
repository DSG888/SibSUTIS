#include <stdio.h>
#include <math.h>
#include <graphics.h>

double fnc(double x)
{
	return sqrt(x);
}

double x[4]={1.0, 1.5, 2.0, 2.5}, y[4];

int gd=DETECT, gm=VGAHI;

int main()
{
        int i, j;
        double k, p[4], pf;

        for(i=0; i<4; i++) y[i]=fnc(x[i]);

        initgraph(&gd, &gm, "");
        line(0,240,639,240);
        line(320,0,320,479);
        for(i=0; i<5; i++){
                 line(120+100*i, 237, 120+100*i, 243);
                 line(317, 40+100*i, 323, 40+100*i);
        }
        moveto(310,10);
        outtext("y");
        moveto(600,250);
        outtext("x");
        moveto(310,250);
        outtext("0");

        /*Interpolaycia*/

           for(k=0.0; k<4.0; k+=0.001)
           {
                for(i=0; i<4; i++) p[i]=y[i];

                for(i=1;i<4;i++)
	        {
	                for(j=0;j<4-i;j++)
	                  p[j]=(p[j]*(k-x[j+i])-p[j+1]*(k-x[j]))/(x[j]-x[j+i]);
	        }
                putpixel(320+k*100,240-p[0]*100,4);
           }

        /*Graphic korniay iz X*/

        for(k=0.0; k<4.0; k+=0.001)
                  putpixel(320+k*100, 240-fnc(k)*100, 2);
        for(i=0, setcolor(7); i<4; i++)
                 circle(320+x[i]*100, 240-y[i]*100, 3);

        getchar();
        closegraph();
	return 0;
}