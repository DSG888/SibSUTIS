#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <graphics.h>

const int height = 1000;
const int width = 1000;
double **array_values;
int n;
double point = 2.2, h;

struct complex {
    double real;
    double image;
};

double f(double x) {
    return x;
}

complex multiple_complex(complex a, complex b) {
    complex result;
    result.real = 0, result.image = 0;
    result.real = a.real * b.real - a.image * b.image;
    result.image = a.real * b.image + a.image * b.real;
    return result;
}

complex calculate_A(int number) {
    complex complex_number, sum;
    complex_number.real = 0, complex_number.image = 0, sum.real = 0, sum.image = 0;
    double index = 0;
    for (int k = 0; k < n; k++) {
        index = (-2 * M_PI * k * number) / n;
        complex_number.real = cos(index) * array_values[k][1];
        complex_number.image = sin(index) * array_values[k][1];
        sum.real += complex_number.real;
        sum.image += complex_number.image;
    }
    sum.real /= n;
    sum.image /= n;
    return sum;
}

complex trigonometric_interpolation(double x) {
    int j;
    complex complex_number, A, result, sum;
    complex_number.real = 0, complex_number.image = 0, A.real = 0, A.image = 0, result.real = 0, result.image = 0,
            sum.real = 0, sum.image = 0;
    double index = 0;
    if (n % 2 == 0) j = -(n / 2) + 1;
    else j = -(n / 2);
    for (j; j <= n / 2; j++) {
        A = calculate_A(j);
        index = (2 * M_PI * j * (x - array_values[0][0])) / (n * h);
        complex_number.real = cos(index);
        complex_number.image = sin(index);
        result = multiple_complex(complex_number, A);
        sum.real += result.real;
        sum.image += result.image;
    }
    return sum;
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
        double coord_y = y_0 + y * 20;
        double invert_y = (coord_y - y_0) * 2;
        if (x == begin) moveto(coord_x, coord_y - invert_y);
        lineto(coord_x, coord_y - invert_y);
    }
}

void draw_real_part(int begin, int end) {
    complex comp;
    comp.real = 0, comp.image = 0;
    double round_x, round_el_array;
    int i = 0;
    setcolor(YELLOW);
    moveto(width / 2, height / 2);
    int x_0 = getx();
    int y_0 = gety();
    for(double x = begin; x <= end; x += 0.1) {
        comp = trigonometric_interpolation(x);
        double coord_x = x_0 + x * 60;
        double coord_y = y_0 + comp.real * 20;
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

void draw_image_part(int begin, int end) {
    complex comp;
    comp.real = 0, comp.image = 0;
    double round_x, round_el_array;
    int i = 0;
    setcolor(GREEN);
    moveto(width / 2, height / 2);
    int x_0 = getx();
    int y_0 = gety();
    for(double x = begin; x <= end; x += 0.1) {
        comp = trigonometric_interpolation(x);
        double coord_x = x_0 + x * 60;
        double coord_y = y_0 + comp.image * 20;
        double invert_y = (coord_y - y_0) * 2;
        round_x = round(x * 1000000) / 1000000;
        round_el_array = round(array_values[i][0] * 10000000) / 10000000;
        if (round_x == round_el_array) {
            setcolor(BLUE);
            setfillstyle(1, BLUE);
            circle(coord_x, coord_y - invert_y, 7);
            floodfill(coord_x, coord_y - invert_y, BLUE);
            setcolor(GREEN);
            i++;
            if (i == n) i = 0;
        }
        if (x == begin) moveto(coord_x, coord_y - invert_y);
        lineto(coord_x, coord_y - invert_y);
    }
}

int main() {
    complex value;
    double x0;
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
    value = trigonometric_interpolation(point);
    printf("Result: %lf %lf\n\n", value.real, value.image);
    init_window();
    draw_function(-10, 10);
    draw_real_part(-10, 10);
    draw_image_part(-10, 10);
    system("pause");
}
