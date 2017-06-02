#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#define n 4

double matr[3][4], a[3], s1[4], t0[4], ;

void grafik(int m) {
    double xg, y, y2, l2, l1;
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
    for (xg = (-200); xg <= 200; xg+=0.001) {
        y = a[2] * pow(xg, 2);
        putpixel(200+xg*m, 200-y*m, 4);
    }
    for (l = 0; l < 4; l++) {
        circle(200+s1[l]*m, 200-t0[l]*m, 3);
    }
    getch();
}

void gauss(double Ag[3][4], double * Bg, int ng, int mg) {
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
    int i;
    double s0[4] = {1}, s2[4], s3[4], s4[4], t1[4], t2[4], S[8] = {0};
    for (i = 0; i < n; i++) {
        s1[i] = (i+1);
        s2[i] = pow(s1[i], 2);
        s3[i] = pow(s1[i], 3);
        s4[i] = pow(s1[i], 4);
        t0[i] = pow(s1[i], 2);
        t1[i] = s1[i]*t0[i];
        t2[i] = t0[i] * pow(s1[i], 2);
    }
    for (i = 0; i < 4; i++) {
        S[0] += s1[i];
        S[1] += t0[i];
        S[2] += s0[i];
        S[3] += s2[i];
        S[4] += s3[i];
        S[5] += s4[i];
        S[6] += t1[i];
        S[7] += t2[i];
    }
    matr[0][0] = S[2]; matr[0][1] = S[0]; matr[0][2] = S[3]; matr[0][3] = S[1];
    matr[1][0] = S[0]; matr[1][1] = S[3]; matr[1][2] = S[4]; matr[1][3] = S[6];
    matr[2][0] = S[3]; matr[0][1] = S[4]; matr[0][2] = S[5]; matr[0][3] = S[7];
    gauss(matr, a, 4, 3);
    printf("a2 = %6.2lf", a[2]);
    grafik(10);
    return (0);
}
