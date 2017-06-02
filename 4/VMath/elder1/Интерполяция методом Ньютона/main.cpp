#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define n 4

double x[4], y[4], d1y[3], d2y[2], d3y;

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
    double xg, yg, qg;
    for (xg = -200; xg < 200; xg+=0.01) {
        yg = pow(xg, 0.5);
        putpixel(200+xg*m, 200-yg*m, 4);
    }
    for (l = 0; l < n; l++) {
        setcolor(3);
        circle(200+x[l]*m, 200-y[l]*m, 2);
    }
    for (xg = -200; xg < 200; xg+=0.01) {
        qg = ((xg - x[n-1]) / 0.2);
        yg = y[n-1] + (d1y[n-2] * qg) + ((d2y[n-3] * qg * (qg + 1)) / 2) + ((d3y * qg * (qg + 1) * (qg + 2)) / 6);
        putpixel(200+xg*m, 200-yg*m, 2);
    }
}

int main() {
    double X, q, P;
    int i, j;
    printf("Vvedite X:");
    scanf("%lf", &X);
    for (i = 0; i < n; i++) {
        x[i] = 1 + i * 0.2;
        y[i] = pow(x[i], 0.5);
    }
    q = ((X - x[n-1]) / 0.2);
    d1y[2] = y[3] - y[2]; d1y[1] = y[2] - y[1]; d1y[0] = y[1] - y[0];
    d2y[1] = d1y[2] - d1y[1]; d2y[0] = d1y[1] - d1y[0];
    d3y = d2y[1] - d2y[0];
    printf("   x     y   d1y   d2y   d3y\n\n");
    printf("%5.2lf %5.2lf %5.2lf %5.2lf %5.2lf\n", x[0], y[0], d1y[0], d2y[0], d3y);
    printf("%5.2lf %5.2lf %5.2lf %5.2lf\n", x[1], y[1], d1y[1], d2y[1]);
    printf("%5.2lf %5.2lf %5.2lf\n", x[2], y[2], d1y[2]);
    printf("%5.2lf %5.2lf\n", x[3], y[3]);
    P = y[n-1] + (d1y[n-2] * q) + ((d2y[n-3] * q * (q + 1)) / 2) + ((d3y * q * (q + 1) * (q + 2)) / 6);
    printf("\n%5.2lf", P);
    grafik(60);
    getch();
    return (0);
}
