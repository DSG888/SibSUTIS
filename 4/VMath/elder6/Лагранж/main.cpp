#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>

const int width = 1000;
const int height = 1000;
double **array_values;
int n;
int count;
double point;

double f(double x) {
    return sqrt(x);
}

double factorial(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    else return n * factorial(n - 1);
}

double M() {
    double value = 0, arr[n];
    for (int i = 0; i <= n; i++) {
        value = fabs(0.9375 * pow(array_values[i][0], -3.5));
        arr[i] = value;
    }
    double max = arr[0];
    for (int i = 0; i <= n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

double eps_usech() {
    double c1 = M()/factorial(n + 1);
    double c2 = 1;
    for (int i = 0; i <= n; i++) {
        c2 *= point - array_values[i][0];
    }
    return c1 * fabs(c2);
}

double eps_round(double eta) {
    return eta * pow(2, n - 1);
}

double q(int number_iter, double value) {
    double numerator = 1, denomenator = 1;
    for (int i = 0; i <= n; i++) {
        if (number_iter != i) {
            numerator *= value - array_values[i][0];
            denomenator *= array_values[number_iter][0] - array_values[i][0];
        }
    }
    double fraction = numerator/denomenator;
    return fraction;
}

double interpolation(double value) {
    double p = 0;
    for (int i = 0; i <= n; i++) {
        p += array_values[i][1] * q(i, value);
    }
    return p;
}

void init_window() {
    initwindow(width, height);
    setcolor(WHITE);
    line(width / 2, 0, width / 2, height);
    line(0, height / 2, width, height / 2);
}

void draw_function(int begin, int end) {
    moveto(width / 2, height / 2);
    setcolor(MAGENTA);
    int x_0 = getx();
    int y_0 = gety();
    for (double x = begin; x <= end; x += 0.1) {
        double y = f(x);
        double coord_x = x_0 + x * 60;
        double coord_y = y_0 + y * 60;
        double invert_y = (coord_y - y_0) * 2;
        lineto(coord_x, coord_y - invert_y);
    }
}

void draw_polynom(int begin, int end) {
    double round_x, round_el_array;
    int i = 0;
    setcolor(YELLOW);
    moveto(width / 2, height / 2);
    int x_0 = getx();
    int y_0 = gety();
    moveto(0, interpolation(begin));
    for(double x = begin; x <= end; x += 0.1) {
        double y = interpolation(x);
        double coord_x = x_0 + x * 60;
        double coord_y = y_0 + y * 60;
        double invert_y = (coord_y - y_0) * 2;
        round_x = round(x * 1000000) / 1000000;
        round_el_array = round(array_values[i][0] * 10000000) / 10000000;
        if (round_x == round_el_array) {
            setcolor(RED);
            setfillstyle(1, RED);
            circle(coord_x, coord_y - invert_y, 7);
            floodfill(coord_x, coord_y - invert_y, RED);
            setcolor(YELLOW);
            i++;
            if (i == count) i = 0;
        }
        lineto(coord_x, coord_y - invert_y);
    }
}

int main() {
    init_window();
    FILE *file = fopen("data.txt", "r");
    fscanf(file, "%d%d%lf", &n, &count, &point);
    array_values = new double *[count];
    for (int i = 0; i < count; i++) array_values[i] = new double [2];
    for (int i = 0; i < count; i++) {
        fscanf(file, "%lf", &array_values[i][0]);
        fscanf(file, "%lf", &array_values[i][1]);
    }
    fclose(file);
    printf("    X          Y\n");
    for (int i = 0; i < count; i++) {
        printf("%lf   %lf\n", array_values[i][0], array_values[i][1]);
    }
    printf("\n");
    draw_function(0, 100);
    draw_polynom(-10, 100);
    double value = interpolation(point);
    double eps = eps_usech();
    double eps_r = eps_round(0.00005);
    printf("Value of polynominal P%d in point %1.2lf: %1.3lf\n\n", n, point, value);
    printf("Error(usech): %1.3lf\n\n", eps);
    printf("Error(round): %lf\n\n", eps_r);
    system("pause");
}
