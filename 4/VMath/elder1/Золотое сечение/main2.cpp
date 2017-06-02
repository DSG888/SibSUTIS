#include <stdio.h>
#include <math.h>
#include <conio.h>
#include "rus.h"
//y=x^2-4*x
double fabs(double input) {
    if (input < 0) return (input*(-1));
    else return (input);
}

double f(double input) {
       double output;
       output = pow(input, 2) - 4*input;
       return (output);
}

int main() {
    int n;
    double a, b, x1, x2, y1, y2, eps = 0.001, fi = 1.618, x;
    a = 3;
    b = 6;
    x1 = b - ((b - a) / fi);
    x2 = a + ((b - a) / fi);
    y1 = f(x1);
    y2 = f(x2);
    Rus("Метод золотого сечения.");
  //  Rus("\nВведите Е ");
  //  scanf("%lf", &eps);
    for (n = 0;; n++) {
        if (y1 >= y2) {
            b = x2;
            x2 = x1;
            x1 = b - ((b - a) / fi);
            y2 = y1;
            y1 = f(x1);
        }
        else {
            a = x1;
            x1 = x2;
            x2 = a + ((b - a) / fi);
            y1 = y2;
            y2 = f(x2);
        }
        if (fabs(b - a) < eps) {
            if (y1 < y2) x = x1;
            if (y2 <= y1) x = x2;
            break;
        }
    }
    printf("x = %g", x);
    Rus("\nКоличество итераций:");
    printf("%d", n);
    getch();
    return (0);
}
