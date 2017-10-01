#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include "header.h"

const double eps = 0.000001;
double h;
double a, b;
double **koshi;
double **points;
double **points_of_interpolation;
int steps;
int n;
int count_records;

double diffur(double x, double y_2, double igrek[]) {
    //return pow(y_2, 5) + 6 * x * y_2 - cos(x) - 5 * exp(x) * Y[1] - (Y[0] / pow(x + 4, 3));
    //return pow(y_2, 3) + 8 * cos(x) * y_2 - (4 * x + 7 * exp(x) * Y[1] - 5 * Y[0] * (x + 8));
    return y_2 + pow(y_2, 3) - exp(x) - exp(3 * x);
    //return 3 * x * x * igrek[0] + x * x * exp(x * x * x);
}

double mpd(double x, double igrek[]) {
    double left = -20, right = 20, c;
    do {
        c = (left + right) / 2;
        if (diffur(x, c, igrek) * diffur(x, left, igrek) < 0) right = c;
        else left = c;
    } while ((fabs(right - left) / 2) > eps);
    return (left + right) / 2;
}

void F(double array[], double x, double igrek[]) {
    double Y_strih[n];
    for (int i = 0; i < n - 1; i++) {
        Y_strih[i] = igrek[i + 1];
    }
    if (n != 1) Y_strih[n - 1] = mpd(x, igrek);
    else Y_strih[0] = diffur(x, 0, igrek);
    for (int i = 0; i < n; i++) array[i] = Y_strih[i];
}

void shot_method() {
    int k = 0;
    double y_b = koshi[n - 1][1];
    double left = -1, right = -1;
    double c = 0;
    double y[n + 1];
    koshi[n - 1][0] = koshi[n - 2][0];
    while (1) {
        koshi[n - 1][1] = k;
        runge_kutt(y, 0, h);
        if (y[0] - y_b < 0) left = k;
        if (y[0] - y_b > 0) right = k;
        if (left != -1 && right != -1) {
            while (1) {
                c = (left + right) / 2;
                koshi[n - 1][1] = c;
                runge_kutt(y, 0, h);
                if (fabs(y[0] - y_b) < eps) {
                    double_counting(y, 1, h);
                    printf("\nAngle: %lf\n\n", c);
                    return;
                }
                else {
                    if (y[0] < y_b) left = c;
                    else right = c;
                }
            }
        }
        k++;
    }
}

void double_counting(double array[], int flag_print, double step) {
    double y_left[n + 1], y_right[n + 1];
    runge_kutt(y_left, 0, step);
    runge_kutt(y_right, 0, step / 2);
    if ((fabs(y_left[0] - y_right[0]) < 3 * eps)) {
        runge_kutt(array, flag_print, step);
    }
    else double_counting(array, flag_print, step / 2);
}

void runge_kutt(double array[], int flag, double step) {
    int k = 1;
    double Y[n + 1], Y_st[n], Y_prev[n + 1], F_1[n], F_2[n];
    double x_0 = a, step_print;
    for (int i = 0; i < n; i++) Y_prev[i] = koshi[i][1];
    points_of_interpolation[0][0] = x_0;
    points_of_interpolation[0][1] = Y_prev[0];
    steps = ((b - a) / step) + 1;
    step_print = (b - a) / count_records;
    if (flag == 2) {
        points = (double**) malloc(steps * sizeof(double));
        for (int p = 0; p < steps; p++) points[p] = (double*) malloc(steps * sizeof(double));
    }
    for (int i = 0; i < steps; i++) {
        F(F_1, x_0, Y_prev);
        for (int p = 0; p < n; p++) {
            Y_st[p] = Y_prev[p] + (step / 2) * F_1[p];
        }
        F(F_2, x_0 + step, Y_st);
        for (int p = 0; p < n; p++) {
            Y[p] = Y_prev[p] + (step / 2) * (F_1[p] + F_2[p]);
        }
        Y[n] = mpd(x_0, Y);
        for (int p = 0; p <= n; p++) Y_prev[p] = Y[p];
        x_0 += step;
        if (flag == 1) {
            double round_x_0 = round(x_0 * 1000000) / 1000000;
            double round_step_print = round(step_print * 1000000) / 1000000;
            if (round_x_0 == round_step_print) {
                printf("%lf ", x_0);
                for (int loop = 0; loop <= n; loop++) printf("%1.15lf ", Y[loop]);
                printf("\n");
                step_print += (b - a) / count_records;
            }
        }
        if (flag == 2) {
            points[i][0] = x_0;
            points[i][1] = Y[0];
            points_of_interpolation[k][0] = x_0;
            double round_x = round(points[i][0] * 1000000) / 1000000;
            if (round_x == 0.2 || round_x == 0.4 || round_x == 0.6 || round_x == 0.8 ||
                round_x == 1) {
                points_of_interpolation[k][0] = points[i][0];
                points_of_interpolation[k][1] = points[i][1];
                k++;
            }
        }
    }
    for (int i = 0; i <= n; i++) array[i] = Y[i];
}

int main() {
    printf("Enter count of derivatives: ");
    scanf("%d", &n);
    printf("Enter step: ");
    scanf("%lf", &h);
    //выделение памяти под массивы//
    double y[n + 1];
    double *h_1 = (double*) malloc(count_points * sizeof(double));
    double *d = (double*) malloc((count_points - 1) * sizeof(double));
    koshi = (double**) malloc(n * sizeof(double));
    points_of_interpolation = (double**) malloc(count_points * sizeof(double));
    for (int i = 0; i < n; i++) koshi[i] = (double*) malloc(n * sizeof(double));
    for (int i = 0; i < count_points; i++) points_of_interpolation[i] = (double*) malloc(count_points * sizeof(double));
    //..//
    while (1) {
        system("cls");
        printf("1) Solve Koshi task\n");
        printf("2) Shooting method\n");
        printf("3) Build graphics\n");
        char ch = _getch();
        switch (ch) {
            case '1': {
                system("cls");
                printf("Koshi task\n\n");
                for (int i = 0; i < n; i++) {
                    printf("X: ");
                    scanf("%lf", &koshi[i][0]);
                    printf("Y: ");
                    scanf("%lf", &koshi[i][1]);
                    printf("\n");
                }
                system("cls");
                printf("Enter interval (a,b):\n");
                scanf("%lf%lf", &a, &b);
                system("cls");
                printf("Enter count of records in print: ");
                scanf("%d", &count_records);
                system("cls");
                double_counting(y, 1, h);
                system("pause");
            } break;
            case '2': {
                system("cls");
                printf("Koshi task\n\n");
                for (int i = 0; i < n; i++) {
                    printf("X: ");
                    scanf("%lf", &koshi[i][0]);
                    printf("Y: ");
                    scanf("%lf", &koshi[i][1]);
                    printf("\n");
                }
                system("cls");
                a = koshi[n - 2][0];
                b = koshi[n - 1][0];
                printf("Enter count of records in print: ");
                scanf("%d", &count_records);
                system("cls");
                shot_method();
                system("pause");
            } break;
            case '3': {
                a = 0, b = 1;
                runge_kutt(y, 2, h);
                for (int i = 1; i < count_points; i++) {
                    h_1[i] = points_of_interpolation[i][0] - points_of_interpolation[i - 1][0];
                }
                for (int i = 1; i < count_points - 1; i++) {
                    double minuend = (points_of_interpolation[i + 1][1] - points_of_interpolation[i][1]) / h_1[i + 1];
                    double subtrahend = (points_of_interpolation[i][1] - points_of_interpolation[i - 1][1]) / h_1[i];
                    d[i] = minuend - subtrahend;
                }
                init_window();
                draw_y(steps, points);
                draw_spline(h_1, d, points_of_interpolation);
            } break;
            default: break;
        }
    }
}
