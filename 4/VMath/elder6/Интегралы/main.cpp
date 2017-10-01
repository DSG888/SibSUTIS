#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int n;
double a, b;

double f(double x) {
    return 1 / x;
}

double trapeze_integral(double h, double eps) {
    int count = 0;
    double integral_h = 0, integral_h_2 = 0;
    do {
        integral_h_2 = integral_h;
        integral_h = 0.5 * (f(a) + f(b));
        for (double i = a + h; ; i += h) {
            if (i > b) break;
            integral_h += f(i);
        }
        integral_h *= h;
        h /= 2;
        count++;
    }
    while (count < 2);
    if (fabs(integral_h - integral_h_2) < 3 * eps) {
        printf("Trapeze rule: %1.15lf", integral_h);
        printf("   h = %1.10lf\n", h);
        return integral_h + ((integral_h - integral_h_2) / 3);
    }
    else trapeze_integral(h / 2, eps);
}

double simpson_integral(double h, double eps) {
    int count = 0;
    double integral_h = 0, integral_h_2 = 0;
    do {
        integral_h_2 = integral_h;
        integral_h = f(a) + f(b);
        for (double i = a + h; ; i += 2 * h) {
            if (i > b - h) break;
            integral_h += f(i) * 4;
        }
        for (double i = a + 2 * h; ; i += 2 * h) {
            if (i > b - h) break;
            integral_h += f(i) * 2;
        }
        integral_h *= (h / 3);
        h /= 2;
        count++;
    }
    while (count < 2);
    if (fabs(integral_h - integral_h_2) < 15 * eps) {
        printf("Simpson's rule: %1.15lf", integral_h);
        printf("   h = %1.10lf\n", h);
        return integral_h + ((integral_h - integral_h_2) / 3);
    }
    else simpson_integral(h / 2, eps);
}

int main() {
    double h, *y;
    FILE *file = fopen("data.txt", "r");
    fscanf(file, "%lf%lf%lf", &a, &b, &h);
    fclose(file);
    int k = 0;
    trapeze_integral(h, 0.00000001);
    simpson_integral(h, 0.00000001);
    system("pause");
}
