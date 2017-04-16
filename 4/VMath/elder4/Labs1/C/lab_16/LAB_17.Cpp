#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <graphics.h>

#define n 10
#define k 3
#define h 0.2
#define E 6

float d, z, x[n], y[n], g[n];
float gM[k][n], C[k][k], CB[k][k+1];
float B[k], A[k];
int i,j,l,t, gd, gm;

float g0(){ return 1; }

float g1(float x){ return (x); }

float g2(float x){ return (x*x); }

float f(float x){
		return (exp(x+0.1));
}

main()
{
       clrscr();
       x[0]=0.4; y[0]=f(x[0]);

		 for (i=1; i<n; i++)
		 {
            x[i]=x[i-1]+h;
            y[i]=f(x[i]);
       }

		 gotoxy((E+6)/2, 1); printf("x");
		 gotoxy(E+7+(E+6)/2, 1); printf("y\n");

		 for (i=0; i<n; i++)
			printf(" %.6f  | %.6f\n", x[i], y[i]);

		 for (i=0; i<n; i++)
		 {
				gM[0][i]=g0();
            gM[1][i]=g1(x[i]);
            gM[2][i]=g2(x[i]);
       }

		 for (i=0; i<k; i++)
            for (j=0; j<k; j++)
                 for (l=0; l<n; l++)
                      C[i][j]+=gM[i][l]*gM[j][l];

		 printf("Матрица C:\n");
		 for (i=0; i<k; i++)
		 {
            for (j=0; j<k; j++)
                 printf("%.6f  ", C[i][j]);
            printf("\n");
		 }

       for (i=0; i<k; i++)
            for (j=0; j<n; j++)
                 B[i]+=gM[i][j]*f(x[j]);

		 printf("Вектор B:\n");
       for (i=0; i<k; i++)
			printf("%.6f\n", B[i]);

		for (i=0; i<k; i++)
			for (j=0; j<k+1; j++)
				if (j<k) CB[i][j]=C[i][j];
				else CB[i][j]=B[i];
		printf("%.6f  ", CB[i][j]);

		for(j=0; j<k; j++)
			for(i=j+1; i<k; i++)
			{
				d=-CB[i][j]/CB[j][j];
				if(d!=0)
					for(l=0; l<k+1; l++)
						CB[i][l]+=d*CB[j][l];
			}

		for(i=k-1; i>=0; i--)
		{
			A[i]=CB[i][k]/CB[i][i]-z;
			z=0;
			if(i>0)
				for(j=k-1; j>=i; j--)
					z+=(CB[i-1][j]*A[j])/CB[i-1][i-1];
		}

		 printf("\nВектор A:\n");
       for (i=0; i<k; i++)
			printf("%.6f\n", A[i]);

       getch();
       clrscr();

       for (i=0; i<n; i++)
            for (j=0; j<k; j++)
		 g[i]+=gM[j][i]*A[j];

		 gotoxy((E+6)/2, 1); printf("x");
		 gotoxy(E+7+(E+6)/2, 1); printf("y");
		 gotoxy(2*E+14+(E+6)/2, 1);printf("g\n");

		 for (i=0; i<n; i++)
			printf("%.6f    %.6f    %.6f\n", x[i], y[i], g[i]);

		 getch();

       gd=0;
       initgraph(&gd, &gm,"C:\\bc\\bgi");
       cleardevice();

       setcolor(WHITE);
       outtextxy(600, 400, "X");
       outtextxy(30, 40, "Y");

		 setcolor(WHITE);
       line(40, 40, 40, 400);
       line(40, 400, 600, 400);

		 for (j=40, i=0; i<8; i++)
		 {
            j+=40;
            line(j, 398, j, 402);
       }

		 for (j=400, i=0; i<6; i++)
		 {
              j-=40;
              line(38, j, 42, j);
       }

       moveto(40, 400);
		 setcolor(DARKGRAY);
		 for (d=0; d<10.5; d+=0.1)
            lineto(40+(d)*40,400-f(d)*40);

       moveto(40+0.1*40, 400-f(0.1)*40);
		 setcolor(5);

		 for (j=0; j<n; j++)
			circle(40+x[j]*40, 400-g[j]*40, 2);

		 setcolor(GREEN);
		 for (j=0; j<n; j++)
				circle(40+x[j]*40, 400-y[j]*40, 2);

       getch();
       closegraph();

}