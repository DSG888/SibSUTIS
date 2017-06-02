#include <stdio.h>
#include <conio.h>
#include <math.h>

float absf(float num) {
    if (num < 0) num *= (-1);
    return num;
}

float pf(float q) {
    float result;
    result = 2*q;
    return (result);
}

float f(float q) {
    float result;
    result = (q * q) - 2;
    return (result);
}

int main() {
    float a, x[100], y, c, e, Cn = 0, m;
    int i, b;
    printf("Vvedite x0: ");
    scanf("%f", &x[0]);
    printf("Vvedite e: ");
    scanf("%f", &e);
    m = 1;
    for (i = 1; ; i++) {
        x[i] = x[i-1] - (f(x[i-1]) / pf(x[i-1]));
        m = absf((x[i] - x[i-1]) / 2);
        b = i;
        if (m < e) break;
    }
    printf("Otvet: %10.4f", x[b]);
    getch();
    return (0);
}
