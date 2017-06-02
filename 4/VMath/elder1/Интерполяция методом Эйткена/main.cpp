#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define n 4

double x[4], y[4];

void grafik(int m) {
    initwindow(400, 300);
    moveto(200, 0);
    lineto(200, 400);
    moveto(200, 0);
    lineto(198, 5);
    moveto(200, 0);
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
        setcolor(3);
        circle(200+x[l]*m, 200-y[l]*m, 2);
    }
    for (xg = -200; xg < 200; xg+=0.01) {
        yg = ((sqrt(xg) * (xg - x[n-1])) - sqrt(xg) * (xg - x[0])) / (x[0] - x[n-1]);
        putpixel(200+xg*m, 200-yg*m, 2);
    }
}

int main() {
    double X, P;
    int i, j;
    printf("Metod Eitkena.\nVvedite X:");
    scanf("%lf", &X);
    for (i = 0; i < n; i++) {
        x[i] = 1 + 0.2 * i;
        y[i] = sqrt(x[i]);
    }
    P = ((sqrt(X) * (X - x[n-1])) - sqrt(X) * (X - x[0])) / (x[0] - x[n-1]);
    printf("%.2lf", P);
    grafik(50);
    getch();
    return (0);
}
