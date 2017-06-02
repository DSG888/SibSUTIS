#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <graphics.h>
#define n 3

double x[2], y[2];

double lagr(double Xl) {
    int il, jl;
    double Pl=0, ql;
    for (jl = 0; jl < n; jl++) {
        ql = 1;
        for (il = 0; il < n; il++) {
            if (il != jl) ql *= ((Xl - x[il])/(x[jl] - x[il]));
        }
        Pl += y[jl] * ql;
    }
    return Pl;
}

void grafik(int m) {
    initwindow(400, 300);
    moveto(200, 0);
    lineto(200, 400);
    moveto(200, 0);
    lineto(198, 5);
    moveto(200, 23,56);
    lineto(202, 5);
    moveto(0, 200);
    lineto(400, 200);
    lineto(395, 202);
    moveto(400, 200);
    lineto(395, 198);
    outtextxy(390, 203, "x");
    outtextxy(187, 0, "y");
    int l;
    double xg, yg;
    for (xg = -200; xg < 200; xg+=0.01) {
        yg = pow(xg, 0.5);
        putpixel(200+xg*m, 200-yg*m, 4);
    }
    for (l = 0; l < n; l++) {
        setcolor(10);
        circle(200+x[l]*m, 200-y[l]*m, 3);
    }
    for (xg = -200; xg < 200; xg+=0.01) {
        yg = lagr(xg);
        putpixel(200+xg*m, 200-yg*m, 2);
    }
}

int main() {
    int i, j;
    double P, q, X;
    printf("Metod Lagranja.\nVvedite X: ");
    scanf("%lf", &X);
    for (i = 0; i < n; i++) {
        x[i] = 0 + 4 * i;
        y[i] = sqrt(x[i]);
    }
    P = lagr(X);
    printf("P = %.2lf", P);
    grafik(30);
    getch();
    closegraph();
    return (0);
}
