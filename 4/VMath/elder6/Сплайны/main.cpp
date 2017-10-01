#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>

const int width = 1000;
const int height = 1000;
double **array_values;
int count_points;

void reverse(double *a, double *b) {
    if (a < b) {
        *a += *b; *b = *a - *b; *a -= *b;
        reverse(a + 1, b - 1);
    }
}

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

void calculate_moments(double *h, double *d, double *&M) {
    int rows = count_points - 2;
    int cols = count_points - 1;
    double **C;
    C = new double *[rows];
    for (int i = 0; i < rows; i++) C[i] = new double [cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == j) C[i][j] = (h[i + 1] + h[i + 2]) / 3;
            if (j == i + 1) C[i][j] = h[i + 2] / 6;
            if (j == i - 1) C[i][j] = h[i + 1] / 6;
            if (abs(i - j) > 1) C[i][j] = 0;
            if (j == cols - 1) C[i][j] = d[i + 1];
        }
    }
    Gauss(C, rows, cols, M);
    for (int i = count_points - 1, k = count_points - 2; i >= 0; i--, k--) M[i] = M[k];
    M[0] = 0;
    M[count_points - 1] = 0;
    reverse(M, M + count_points - 1);
}

double cubic_interpolation(double *h, double *d, double x) {
    double *M = new double [count_points];
    calculate_moments(h, d, M);
    int index = 0;
    for (int i = 0; i < count_points - 1; i++) {
        if (array_values[i][0] <= x && array_values[i + 1][0] >= x) {
            index = i + 1;
            break;
        }
    }
    double sums[4];
    sums[0] = M[index - 1] * (pow(array_values[index][0] - x, 3)) / (6 * h[index]);
    sums[1] = M[index] * (pow(x - array_values[index - 1][0], 3)) / (6 * h[index]);
    sums[2] = (array_values[index - 1][1] - (M[index - 1] * pow(h[index], 2)) / 6) * (array_values[index][0] - x) / h[index];
    sums[3] = (array_values[index][1] - (M[index] * pow(h[index], 2)) / 6) * (x - array_values[index - 1][0]) / h[index];
    double S = 0;
    for (int i = 0; i < 4; i++) S += sums[i];
    return S;
}

double f(double x) {
    return 1/x;
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
        double coord_x = x_0 + x * 40;
        double coord_y = y_0 + y * 30;
        double invert_y = (coord_y - y_0) * 2;
        if (x == begin) moveto(coord_x, coord_y - invert_y);
        lineto(coord_x, coord_y - invert_y);
    }
}

void draw_polynom(int begin, int end, double *h, double *d) {
    double round_x, round_el_array;
    int i = 0;
    setcolor(YELLOW);
    moveto(width / 2, height / 2);
    int x_0 = getx();
    int y_0 = gety();
    for(double x = begin; x <= end; x += 0.1) {
        double y = cubic_interpolation(h, d, x);
        double coord_x = x_0 + x * 40;
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
            if (i == count_points) i = 0;
        }
        if (x == begin) moveto(coord_x, coord_y - invert_y);
        lineto(coord_x, coord_y - invert_y);
    }
}

int main() {
    double step, x0;
    FILE *file = fopen("data.txt", "r");
    fscanf(file, "%d%lf%lf", &count_points, &step, &x0);
    double *h = new double [count_points];
    double d[count_points - 1];
    array_values = new double *[count_points];
    for (int i = 0; i < count_points; i++) array_values[i] = new double [2];
    array_values[0][0] = x0;
    array_values[0][1] = f(x0);
    for (int i = 1; i < count_points; i++) {
        array_values[i][0] = x0 + i * step;
        array_values[i][1] = f(array_values[i][0]);
    }
    fclose(file);
    for (int i = 1; i < count_points; i++) {
        h[i] = array_values[i][0] - array_values[i - 1][0];
    }
    for (int i = 1; i < count_points - 1; i++) {
        double minuend = (array_values[i + 1][1] - array_values[i][1]) / h[i + 1];
        double subtrahend = (array_values[i][1] - array_values[i - 1][1]) / h[i];
        d[i] = minuend - subtrahend;
    }
    printf("    X          Y\n");
    for (int i = 0; i < count_points; i++) {
        printf("%lf   %lf\n", array_values[i][0], array_values[i][1]);
    }
    printf("\n");
    init_window();
    draw_function(0, 13);
    draw_polynom(array_values[0][0], array_values[count_points - 1][0], h, d);
    /*double S_1 = cubic_interpolation(h, d, 3);
    double S_2 = cubic_interpolation(h, d, 5);
    double S_3 = cubic_interpolation(h, d, 9);
    printf("Value of cubic polynomial in point 3: %lf\n", S_1);
    printf("Value of cubic polynomial in point 5: %lf\n", S_2);
    printf("Value of cubic polynomial in point 9: %lf\n\n", S_3);*/
    system("pause");
    return 0;
}
