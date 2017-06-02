#include <stdio.h>
#include <conio.h>
#include <math.h>

float absf(float num) {
    if (num < 0) num *= (-1);
    return num;
}

int main() {
    float W[2][2], F[2], x[20][2], det, Wo[2][2], e, S[2] = {0}, e1, e2, E;
    int i, j, k;
    printf("MeTog Newton'a\nCucTeMa:\n( x1^3+x2^3=8\n( x1*x2=3\n");
    printf("BBeguTe To4HocTb: ");
    scanf("%f", &e);
    x[0][0] = 1;
    x[0][1] = 2;
    k = 0;while (e1 > e || e2 > e) {
        W[0][0] = 3*x[k][0];
        W[0][1] = 3*x[k][1];
        W[1][0] = x[k][1];
        W[1][1] = x[k][0];
        det = W[0][0]*W[1][1] - W[0][1]*W[1][0];
         for (i = 0; i < 2; i++) for (j = 0; j < 2; j++) {
             Wo[i][j] = pow(-1, (i+j)) * W[1-i][1-j] / det;
        }
        F[0] = (pow(x[k][0], 3) + pow(x[k][1], 3) - 8);
        F[1] = x[k][0] * x[k][1] - 3;
        for (i = 0; i < 2; i++) for (j = 0; j < 2; j++) S[i] += Wo[i][j] * F[j];
        k++;
        for (i = 0; i < 2; i++) x[k][i] = x[k-1][i] - S[i];
        e1 = (x[k][0] - x[k-1][0]) / (-2);
        e2 = (x[k][1] - x[k-1][1]) / (-2);
    }
    printf("x1 = %f\nx2 = %f\nKolichestvo shagov = %d", x[k][0], x[k][1], k);
    getch();
    return (0);
}
