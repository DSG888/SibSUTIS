#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>

double f(double x) {
    double y = pow(x, 2) - 3;
    return y;
}

double first_derivative(double x, double eps) {
    double der = (f(x + eps) - f(x)) / eps;
    return der;
}

double second_derivative(double x, double eps) {
    double der = (f(x + eps) - 2 * f(x) + f(x - eps)) / pow(eps, 2);
    return der;
}

void bisection_method(double a, double b, double eps) {
    if (f(a) * f(b) > 0) return;
    int i = 1;
    double c = 0;
    while (fabs(b - a) > eps) {
        c = (a + b) / 2;
        if (f(a) * f(c) < 0) b = c;
        if (f(c) * f(b) < 0) a = c;
        printf("%d iteration: ", i);
        printf("Point c = %1.6lf ", c);
        printf("Interval: (%1.6lf ; %1.6lf)\n", a, b);
        i++;
    }
}

void chord_method(double a, double b, double eps) {
    double c_prev = 0, c = (a * f(b) - b * f(a)) / (f(b) - f(a));
    int i = 1;
    while (fabs(c - c_prev) > eps) {
        c_prev = c;
        if (f(a) * f(c) < 0) b = c;
        if (f(c) * f(b) < 0) a = c;
        c = (a * f(b) - b * f(a)) / (f(b) - f(a));
        printf("%d iteration: ", i);
        printf("Point c = %1.6lf ", c);
        printf("Interval: (%1.6lf ; %1.6lf)\n", a, b);
        i++;
    }
}

void newton_method(double a, double b, double eps) {
    double p1 = 0, p2 = 0, x0 = 0, x = 0;
    int i = 1;
    p1 = f(a);
    p2 = second_derivative(a, eps);
    if (p1 * p2 >= 0) x0 = a;
    else x0 = b;
    x = x0 - (f(x0) / first_derivative(x0, eps));
    while (fabs(x - x0) > eps) {
        x0 = x;
        x = x - (f(x) / first_derivative(x, eps));
        printf("%d iteration: ", i);
        printf("Point x = %1.6lf\n", x);
        i++;
    }
}

int main() {
    printf("1) Bisection method\n2) Chord method\n3) Newton method\n\n");
    /*int ch = getch();
    switch (ch) {
        case 49: bisection_method(1, 2, 0.0001); break;
        case 50: chord_method(1, 2, 0.0001); break;
        case 51: newton_method(1, 2, 0.0001); break;
        default: break;
    }*/
    bisection_method(1, 2, 0.0001);
    printf("\n\n");
    chord_method(1, 2, 0.0001);
    printf("\n\n");
    newton_method(1, 2, 0.0001);
    system("pause");
    return 0;
}
