#include <stdio.h>
#include <conio.h>
#include <math.h>

float form(float q) {
    float result;
    result = (q * q) - 2;
    return (result);
}

int main() {
    float a, b, x, y, c, e, m;
    printf("Vvedite a: ");
    scanf("%f", &a);
    printf("Vvedite b: ");
    scanf("%f", &b);
    printf("Vvedite e: ");
    scanf("%f", &e);
    c = (a + b) / 2;
    m = ((b - a) / 2);
    while (m >= e) {
        c = (a + b) / 2;
        if (form(a)*form(c) < 0) b = c;
        if (form(c)*form(b) < 0) a = c;
        m = ((b - a) / 2);
    }
    printf("Otvet: %10.4f", c);
    getch();
    return (0);
}
