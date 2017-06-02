#include <stdio.h>
#include <conio.h>
#include <math.h>

float absf(float num) {
    if (num < 0) num *= (-1);
    return num;
}

float f(float q) {
    float result;
    result = (q * q) - 2;
    return (result);
}

float GetC(float a1, float b1) {
    float res, fa, fb;
    fa = f(a1);
    fb = f(b1);
    res = ((a1 * fb - b1 * fa) / (fb - fa));
    return (res);
}

int main() {
    float a, b, x, y, c, e, Cn = 0, m;
    printf("Vvedite a: ");
    scanf("%f", &a);
    printf("Vvedite b: ");
    scanf("%f", &b);
    printf("Vvedite e: ");
    scanf("%f", &e);
    m = 1;
    while (m >= e) {
        c = GetC(a, b);
        m = absf(c - Cn);
        Cn = c;
        if (f(a)*f(c) < 0) b = c;
        if (f(c)*f(b) < 0) a = c;
    }
    printf("Otvet: %10.4f", c);
    getch();
    return (0);
}
