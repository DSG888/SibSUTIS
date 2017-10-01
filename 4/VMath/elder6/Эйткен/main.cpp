#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>

const int width = 1000;
const int height = 1000;
double **array_values;
int n;
double point = 3.2;

double aitken_interpolation(double x) {
    int h;
    double *polynoms = new double [n + 1]; 
    double ratio, polynomial;
    for (int i = 0; i < n; i++) {
        polynoms[i] = array_values[i][1];
    }
    for (int var = n - 1, var_1 = 1; var > 0; var--, var_1++) {
        h = 1;
        for (int i = 0; i < var; i++) {
            int k = i, l = i + var_1;
            ratio = 1 / (array_values[k][0] - array_values[l][0]);
            polynomial = ratio * (polynoms[k] * (x - array_values[l][0]) - polynoms[h++] * (x - array_values[k][0]));
            polynoms[i] = polynomial;
        }
    }
    return polynoms[0];
}

double f(double x) {
    return 0.994 * pow(x, 3) + 0.056 * pow(x, 2) - 0.164026 * x + 0.153;
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
        double coord_y = y_0 + y * 5;
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
        double y = aitken_interpolation(x);
        double coord_x = x_0 + x * 100;
        double coord_y = y_0 + y * 5;
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
    draw_function(-5, 5);
    draw_polynom(-5, 5);
    double result = aitken_interpolation(point);
    printf("Value of polynomial in point %1.2lf: %1.3lf\n\n", point, result);
    system("pause");
    return 0;
}
