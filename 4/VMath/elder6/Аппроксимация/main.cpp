#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>

int pow_polynom, n, h, x_0;
int width = 1000, height = 1000;

void Gauss(double **array, int rows, int cols, double *&result) {
    for (int diag = 0; diag < rows - 1; diag++) {
        for (int k = diag + 1; k < rows; k++) {
            double ratio = -(array[k][diag] / array[diag][diag]);
            for (int l = 0; l < cols; l++) {
                array[k][l] += array[diag][l] * ratio;
            }
        }
    }
    result[0] = array[rows - 1][cols - 1]/array[rows - 1][cols - 2];
    double temp;
    int index_1 = 1;
    for (int m = rows - 2; m >= 0; m--) {
        int index_2 = 0;
        temp = -array[m][cols - 1];
        for (int p = cols - 2; p >= m; p--) {
            if (p == m) {
                temp /= array[m][p];
                result[index_1++] = -temp;
            }
            else {
                temp += array[m][p] * result[index_2++];
            }
        }
    }
}

double f(double x) {
    return x * x;
}

double g(int number, double x) {
    if (number == 0) return 1;
    if (number == 1) return sqrt(x);
    if (number == 2) return x;
}

double *get_coefficient(double **array) {
    double *result = (double*) malloc(pow_polynom * sizeof(double));
    double **coefficients;
    coefficients = (double**) malloc(pow_polynom * sizeof(double));
    for (int i = 0; i < pow_polynom; i++) {
        coefficients[i] = (double*) malloc((pow_polynom + 1) * sizeof(double));
    }
    for (int i = 0; i < pow_polynom; i++) {
        for (int j = 0; j <= pow_polynom; j++) {
            coefficients[i][j] = 0.0;
        }
    }
    for (int j = 0; j < pow_polynom; j++) {
        for (int p = 0; p < pow_polynom; p++) {
            for (int k = 0; k < n; k++) {
                coefficients[j][p] += g(j, array[k][0]) * g(p, array[k][0]);
            }
        }
    }
    for (int p = 0; p < pow_polynom; p++) {
        for (int i = 0; i < n; i++) {
            coefficients[p][pow_polynom] += array[i][1] * g(p, array[i][0]);
        }
    }
    Gauss(coefficients, pow_polynom, pow_polynom + 1, result);
    return result;
}

double approx_function(double *coef, double x) {
    double value = 0;
    for (int i = 0, k = pow_polynom - 1; i < pow_polynom; i++, k--) {
        value += coef[i] * g(k, x);
    }
    return value;
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
        double coord_x = x_0 + x * 30;
        double coord_y = y_0 + y * 30;
        double invert_y = (coord_y - y_0) * 2;
        if (x == begin) moveto(coord_x, coord_y - invert_y);
        lineto(coord_x, coord_y - invert_y);
    }
}

void draw_polynom(int begin, int end, double *coefficient, double **array_values) {
    double round_x, round_el_array;
    int i = 0;
    setcolor(YELLOW);
    moveto(width / 2, height / 2);
    int x_0 = getx();
    int y_0 = gety();
    for(double x = begin; x <= end; x += 0.1) {
        double y = approx_function(coefficient, x);
        double coord_x = x_0 + x * 30;
        double coord_y = y_0 + y * 30;
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
    FILE *file = fopen("data.txt", "r");
    fscanf(file, "%d%d%d%d", &pow_polynom, &n, &h, &x_0);
    fclose(file);
    double *res = (double*) malloc(pow_polynom * sizeof(double));
    double **array_x_y;
    array_x_y = (double**) malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        array_x_y[i] = (double*) malloc(n * sizeof(double));
    }
    for (int i = 0; i < n; i++) {
        array_x_y[i][0] = x_0 + i * h;
        array_x_y[i][1] = f(array_x_y[i][0]);
    }
    res = get_coefficient(array_x_y);
    for (int i = 0; i < pow_polynom; i++) printf("%lf ", res[i]);
    init_window();
    draw_function(-10, 10);
    draw_polynom(0, 10, res, array_x_y);
    system("pause");
}
