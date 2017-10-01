#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>

const int width = 1000;
const int height = 1000;
double **array_values;
int n;
double point = 1.68;

double factorial(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    else return n * factorial(n - 1);
}

double f(double x) {
    return 11.68 * pow(x, 2) - 31.2 * x + 21.654 + exp(x);
}

double newton_interpolation(double x) {
    int index = 0;
    double differences[n - 1][n - 1];
    for (int i = 0; i < n - 1; i++) {
        differences[i][0] = array_values[i + 1][1] - array_values[i][1];
    }
    for (int k = n - 2, index = 1; k > 0; k--, index++) {
        for (int i = 0; i < k; i++) {
            differences[i][index] = differences[i + 1][index - 1] - differences[i][index - 1];
        }
    }
    double h = array_values[1][0] - array_values[0][0];
    double q = (x - array_values[0][0]) / h;
    double mult_q = 1;
    double polynomial = array_values[0][1];
    for (int i = 1; i < n; i++) {
        for (int k = 0; k < i; k++) mult_q *= q - k;
        polynomial += (differences[0][index++] / factorial(i)) * mult_q;
        mult_q = 1;
    }
    return polynomial;
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
        double coord_x = x_0 + x * 100;
        double coord_y = y_0 + y;
        double invert_y = (coord_y - y_0) * 2;
        if (x == begin) moveto(coord_x, coord_y - invert_y);
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
    for(double x = begin; x <= end; x += 0.1) {
        double y = newton_interpolation(x);
        double coord_x = x_0 + x * 100;
        double coord_y = y_0 + y;
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
            if (i == n) i = 0;
        }
        if (x == begin) moveto(coord_x, coord_y - invert_y);
        lineto(coord_x, coord_y - invert_y);
    }
}

int main() {
    init_window();
    double h, x0;
    FILE *file = fopen("data.txt", "r");
    fscanf(file, "%d%lf%lf", &n, &h, &x0);
    array_values = new double *[n];
    for (int i = 0; i < n; i++) array_values[i] = new double [2];
    array_values[0][0] = x0;
    array_values[0][1] = f(x0);
    for (int i = 1; i < n; i++) {
        array_values[i][0] = x0 + i * h;
        array_values[i][1] = f(array_values[i][0]);
    }
    fclose(file);
    printf("    X          Y\n");
    for (int i = 0; i < n; i++) {
        printf("%lf   %lf\n", array_values[i][0], array_values[i][1]);
    }
    printf("\n");
    draw_function(-10, 10);
    draw_polynom(-10, 10);
    double result = newton_interpolation(point);
    printf("Value of polynomial in point %1.3lf: %lf\n\n", point, result);
    system("pause");
    return 0;
}
