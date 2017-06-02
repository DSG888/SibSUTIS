#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <graphics.h>
#define n 4

double x[40], y[40], M[4], s1, s2, s3, s4;

double abs(double input) {
    if (input < 0) return (input * (-1));
    else return (input);
}

void grafik(int m) {
     int ig;
     double h;
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
        yg = sin(xg);
        putpixel(200+xg*m, 200-yg*m, 4);
    }
    for (l = 0; l < n; l++) {
        setcolor(3);
        circle(200+x[l]*m, 200-y[l]*m, 2);
    }
    for (xg = x[0]; xg < x[3]; xg+=0.0001) {
    for (l = 0; l < n; l++) {
        if (xg > x[l-1] && xg < x[l]) ig = l;
        if (l == 0) ig = 0;
        if (l == n) ig = n;
    }
           h = x[ig] - x[ig-1];
           yg = (((M[ig-1]*pow((x[ig] - xg), 3))/(6*h)) + ((M[ig]*pow((xg - x[ig-1]), 3))/(6*h)) + (y[ig-1] - ((M[ig-1] * h *h)/6))*((x[ig] - xg)/h) + (y[ig] - ((M[ig] * h * h)/6))*((xg - x[ig-1])/h));
        putpixel(200+xg*m, 200-yg*m, 2);
    }
}

void gauss(double Ag[4][5], double * Bg, int ng, int mg) {
    int ig, jg, kg, xg;
    double maxg, zg;
    for (kg = 0; kg < mg-1; kg++) {
        for (ig = kg+1; ig < mg; ig++) {
            zg = Ag[ig][kg] / Ag[kg][kg];
            for (jg = kg; jg < ng; jg++)
            Bg[jg] = Ag[kg][jg] * zg;
            for (jg = kg; jg < ng; jg++) {
                Ag[ig][jg] -= Bg[jg];
            }
        }
    }
    for (ig = 0; ig < mg; ig++) Bg[ig] = 0;
    for (kg = (mg-1); kg >= 0; kg--) {
        maxg = Ag[kg][ng-1];
        for (ig = (ng-2); ig > kg; ig--)
            maxg = (maxg - (Ag[kg][ig]*Bg[ig]));
        Bg[ig] = maxg / Ag[kg][kg];
    }
}

int main() {
    double s, S[4], C[4][5], d[4], h= 0.7, X;
    int i, j;
    printf("Vvedite X:");
    scanf("%lf", &X);
    for (i = 0; i < 4; i++) {
        x[i] = 1 + i * h;
        y[i] = sin(x[i]);
    }
    for (i = 0; i < 4; i++) {
        if (i >= 1 && i <= 2) d[i] = ((y[i+1] - y[i])/ h) - ((y[i] - y[i-1]) / h);
        if (i < 1) d[i] = ((y[i+1] - y[i])/ h) - ((y[i]) / h);
        if (i > 3) d[i] = ((y[i])/ h) - ((y[i] - y[i-1]) / h);
        C[i][4] = d[i];
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == j) C[i][j] = ((2 * h) / 3);
            if (j == i + 1) C[i][j] = h/6;
            if (j == i - 1) C[i][j] = h/6;
            if (abs(i-j) >= 2) C[i][j] = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            printf("  %6.2lf  ", C[i][j]);
        }
        printf("\n");
    }
    gauss(C, M, 5, 4);
    for (i = 0; i < 4; i++) {
        printf("%6.2lf\n", M[i]);
    }
    printf("\n");
    for (i = 0; i < 4; i++) {
    h = x[i] - x[i-1];
    s1 = M[i-1] * (pow((x[i] - X), 3) / 6*h);
    s2 = M[i] * (pow((X - x[i-1]), 3) / 6*h);
    s3 = (y[i-1] - ((M[i-1]*h*h) / 6)) * ((x[i] - X) / h);
    s4 = (y[i] - ((M[i]*h*h) / 6)) * ((X - x[i-1]) / h);
    S[i] = (s1 + s2 + s3 + s4);
    printf("%6.2lf\n", S[i]);
    }
        if (X <= x[0]) i = 0;
    if (X > x[0] && X <= x[1]) i = 1;
    if (X > x[1] && X <= x[2]) i = 2;
    if (X > x[2] && X <= x[3]) i = 3;
    if (X > x[3]) i = 4;
    h = x[i] - x[i-1];
    s = (((M[i-1]*pow((x[i] - X), 3))/(6*h)) + ((M[i]*pow((X - x[i-1]), 3))/(6*h)) + (y[i-1] - ((M[i-1] * h * h)/6))*((x[i] - X)/h) + (y[i] - ((M[i] * h * h)/6))*((X - x[i-1])/h));
    printf("\n\n%6.2lf", s);
    grafik(60);
    getch();
    return (0);
}
