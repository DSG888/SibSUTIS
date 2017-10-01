#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int count_equation = 2;

void print_matrix(double **matrix) {
    for (int i = 0; i < count_equation; i++) {
        for (int j = 0; j < count_equation; j++) {
            printf("%1.6lf ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

double maximum(double *array) {
    double max = fabs(array[0]);
    for (int i = 1; i < count_equation; i++) {
        if (fabs(array[i]) > max) max = fabs(array[i]);
    }
    return max;
}

double f(int number, double x, double y) {
    if (number == 1) return pow(x, 2) + pow(y, 3) - 4;
    if (number == 2) return x/y - 2;
}

double derivative(int number, int variable, double *vector, double eps) {
    if (number == 1 && variable == 1) return (f(number, vector[0] + eps, vector[1]) - f(number, vector[0], vector[1])) / eps;
    if (number == 1 && variable == 2) return (f(number, vector[0], vector[1] + eps) - f(number, vector[0], vector[1])) / eps;
    if (number == 2 && variable == 1) return (f(number, vector[0] + eps, vector[1]) - f(number, vector[0], vector[1])) / eps;
    if (number == 2 && variable == 2) return (f(number, vector[0], vector[1] + eps) - f(number, vector[0], vector[1])) / eps;
}

void build_jacobi_matrix(double **matrix, double *vector) {
    int equation = 1, var = 0;
    for (int i = 0; i < count_equation; i++) {
        for (int j = 0; j < count_equation; j++) {
            var++;
            matrix[i][j] = derivative(equation, var, vector, 0.001);
        }
        equation++;
        var = 0;
    }
}

void back_matrix(double **matrix, double **unit_matrix) {
    for (int i = 0; i < count_equation; i++) {
        double ratio_direct = 1 / matrix[i][i];
        for (int j = 0; j < count_equation; j++) {
            matrix[i][j] *= ratio_direct;
            unit_matrix[i][j] *= ratio_direct;
        }
        for (int k = i + 1; k < count_equation; k++) {
            double ratio = -matrix[k][i];
            for (int j = 0; j < count_equation; j++) {
                matrix[k][j] += matrix[i][j] * ratio;
                unit_matrix[k][j] += unit_matrix[i][j] * ratio;
            }
        }
    }
    int column = count_equation;
    for (int i = count_equation - 1; i >= 0; i--) {
        column--;
        for (int k = i - 1; k >= 0; k--) {
            double ratio_back = -matrix[k][column];
            for (int j = 0; j < count_equation; j++) {
                matrix[k][j] += matrix[i][j] * ratio_back;
                unit_matrix[k][j] += unit_matrix[i][j] * ratio_back;
            }
        }
    }
}

void newton_method(double **jacobi_matrix, double *vector, double eps) {
    int count = 1;
    double *back_vector = new double [count_equation];
    double *differ_vector = new double [count_equation];
    double *solution = new double [count_equation];
    double *intermediate_solution = new double [count_equation];
    double **back_jacobi_matrix;
    back_jacobi_matrix = new double *[count_equation];
    for (int i = 0; i < count_equation; i++) {
        back_jacobi_matrix[i] = new double [count_equation];
        for (int j = 0; j < count_equation; j++) {
            if (i == j) back_jacobi_matrix[i][j] = 1;
            else back_jacobi_matrix[i][j] = 0;
        }
    }
    back_vector[0] = 0;
    back_vector[1] = 0;
    for (int i = 0; i < count_equation; i++) {
        differ_vector[i] = vector[i] - back_vector[i];
        solution[i] = 0;
    }
    while (maximum(differ_vector) > eps) {
        back_vector[0] = vector[0];
        back_vector[1] = vector[1];
        build_jacobi_matrix(jacobi_matrix, vector);
        back_matrix(jacobi_matrix, back_jacobi_matrix);
        solution[0] = f(1, vector[0], vector[1]);
        solution[1] = f(2, vector[0], vector[1]);
        for (int i = 0; i < count_equation; i++) {
            for (int j = 0; j < count_equation; j++) {
                intermediate_solution[i] += back_jacobi_matrix[i][j] * solution[j];
            }
        }
        for (int i = 0; i < count_equation; i++) {
            vector[i] = back_vector[i] - intermediate_solution[i];
        }
        printf("(%d iteration) x = %1.6lf y = %1.6lf\n\n", count, vector[0], vector[1]);
        printf("Back Jacobi matrix:\n\n");
        print_matrix(back_jacobi_matrix);
        count++;
        for (int i = 0; i < count_equation; i++) {
            differ_vector[i] = vector[i] - back_vector[i];
            intermediate_solution[i] = 0;
        }
    }
}

int main() {
    double **matrix;
    double **unit_matrix;
    double **jakobian;
    double *vector = new double [count_equation];
    matrix = new double *[count_equation];
    unit_matrix = new double *[count_equation];
    jakobian = new double *[count_equation];
    for (int i = 0; i < count_equation; i++) jakobian[i] = new double [count_equation];
    for (int i = 0; i < count_equation; i++) {
        matrix[i] = new double [count_equation];
        unit_matrix[i] = new double [count_equation];
    }
    for (int i = 0; i < count_equation; i++) {
        for (int j = 0; j < count_equation; j++) {
            if (i == j) unit_matrix[i][j] = 1;
            else unit_matrix[i][j] = 0;
        }
    }
    vector[0] = 2;
    vector[1] = 1;
    printf("(0 iteration) x = %1.6lf y = %1.6lf\n\n", vector[0], vector[1]);
    newton_method(unit_matrix, vector, 0.0001);
    system("pause");
}
