#include <graphics.h>
#include <math.h>
#include <algorithm>
#include "header.h"

const int width = 1000;
const int height = 1000;

void init_window() {
    initwindow(width, height);
    setcolor(WHITE);
    line(width / 2, 0, width / 2, height);
    line(0, height / 2, width, height / 2);
}

void draw_y(int steps, double **points) {
    moveto(width / 2, height / 2);
    setcolor(MAGENTA);
    int x_0 = getx();
    int y_0 = gety();
    for (int i = 0; i < steps; i++) {
        double x = points[i][0];
        double y = points[i][1];
        double coord_x = x_0 + x * 400;
        double coord_y = y_0 + y * 400;
        double invert_y = (coord_y - y_0) * 2;
        if (x == points[0][0]) moveto(coord_x, coord_y - invert_y);
        lineto(coord_x, coord_y - invert_y);
    }
}

void draw_spline(double *h, double *d, double **points_of_interpolation) {
    double round_x, round_el_array;
    int i = 0, k = 0;
    setcolor(YELLOW);
    moveto(width / 2, height / 2);
    int x_0 = getx();
    int y_0 = gety();
    while (1) {
        if (k == count_points) break;
        double x = points_of_interpolation[k][0];
        double y = cubic_interpolation(h, d, points_of_interpolation, x);
        double coord_x = x_0 + x * 400;
        double coord_y = y_0 + y * 400;
        double invert_y = (coord_y - y_0) * 2;
        round_x = round(x * 1000000) / 1000000;
        round_el_array = round(points_of_interpolation[i][0] * 1000000) / 1000000;
        if (round_x == round_el_array) {
            setcolor(RED);
            setfillstyle(1, RED);
            circle(coord_x, coord_y - invert_y, 7);
            floodfill(coord_x, coord_y - invert_y, RED);
            setcolor(YELLOW);
            i++;
            if (i == count_points) i = 0;
        }
        if (x == 0) moveto(coord_x, coord_y - invert_y);
        lineto(coord_x, coord_y - invert_y);
        k++;
    }
}

void gauss(double **array, int rows, int cols, double *&result) {
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
    gauss(C, rows, cols, M);
    for (int i = count_points - 1, k = count_points - 2; i >= 0; i--, k--) M[i] = M[k];
    M[0] = 0;
    M[count_points - 1] = 0;
    std::reverse(M, M + count_points - 1);
}

double cubic_interpolation(double *h, double *d, double **points_of_interpolation, double x) {
    double *M = new double [count_points];
    calculate_moments(h, d, M);
    int index = 0;
    for (int i = 0; i < count_points - 1; i++) {
        if (points_of_interpolation[i][0] <= x && points_of_interpolation[i + 1][0] >= x) {
            index = i + 1;
            break;
        }
    }
    double sums[4];
    sums[0] = M[index - 1] * (pow(points_of_interpolation[index][0] - x, 3)) / (6 * h[index]);
    sums[1] = M[index] * (pow(x - points_of_interpolation[index - 1][0], 3)) / (6 * h[index]);
    sums[2] = (points_of_interpolation[index - 1][1] - (M[index - 1] * pow(h[index], 2)) / 6) * (points_of_interpolation[index][0] - x) / h[index];
    sums[3] = (points_of_interpolation[index][1] - (M[index] * pow(h[index], 2)) / 6) * (x - points_of_interpolation[index - 1][0]) / h[index];
    double S = 0;
    for (int i = 0; i < 4; i++) S += sums[i];
    return S;
}
