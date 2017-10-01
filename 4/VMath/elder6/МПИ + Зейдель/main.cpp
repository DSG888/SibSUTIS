#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int cols, rows;
const int count_elem_results = 50;

void print_matrix(float **matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j == cols - 1) printf("|");
            printf("%1.3f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void get_cols_rows() {
    FILE *file = fopen("matrix.txt", "r");
    char string[1];
    double number = 0;
    fscanf(file, "%s", string);
    number = atof(string);
    rows = (int)number;
    fscanf(file, "%s", string);
    number = atof(string);
    cols = (int)number;
    fclose(file);
}

void read_matrix(float **matrix) {
    FILE *file = fopen("matrix.txt", "r");
    int i = 0, j = 0;
    char string[6];
    double number = 0;
    fscanf(file, "%s", string);
    number = atof(string);
    rows = (int)number;
    fscanf(file, "%s", string);
    number = atof(string);
    cols = (int)number;
    while (!feof(file)) {
        fscanf(file, "%s", string);
        number = atof(string);
        matrix[i][j] = (float)number;
        j++;
        if (j == cols) {
            i++;
            j = 0;
        }
    }
}

float maximum(float *array) {
    float max = array[0];
    for (int i = 1; i < rows; i++) {
        if (array[i] > max) max = array[i];
    }
    return max;
}

float norm_vector_b(float **matrix) {
    float array[rows];
    for (int i = 0; i < rows; i++) {
        array[i] = matrix[i][cols - 1];
    }
    float max = maximum(array);
    return max;
}

float number_of_steps(float norm_matrix, float norm_vector, float eps) {
    float N = 0;
    float var_1 = (eps * (1 - norm_matrix))/norm_vector;
    float chislitel = log(var_1);
    float znamenaytel = log(norm_matrix);
    N = (chislitel / znamenaytel) + 1;
    return N;
}

float norm_matrix(float **matrix) {
    int i;
    float sum_cols = 0;
    float sums[rows];
    for (i = 0; i < rows; i++) {
        for (int j = 0; j < cols - 1; j++) {
            sum_cols += fabsf(matrix[i][j]);
        }
        sums[i] = sum_cols;
        sum_cols = 0;
    }
    float max = maximum(sums);
    if (max >= 1) return -1;
    else return max;
}

int simple_iterations(float **matrix, float **results, float eps) {
    for (int i = 0; i < rows; i++) {
        float diagonal_el = matrix[i][i];
        matrix[i][i] = 0;
        for (int j = 0; j < cols; j++) {
            matrix[i][j] /= diagonal_el;
        }
    }
    float norm_m = 0;
    if (norm_matrix(matrix) == -1) return -1;
    else {
        norm_m = norm_matrix(matrix);
        printf("Norm of matrix: %1.3f\n\n", norm_m);
    }
    float norm_vector = norm_vector_b(matrix);
    float N = number_of_steps(norm_m, norm_vector, 0.00001);
    printf("Number of steps: %1.0f\n\n", N);
    print_matrix(matrix);
    int k = 1;
    float intermediate_results[cols - 1];
    for (int i = 0; i < cols - 1; i++) intermediate_results[i] = 0;
    while (1) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols - 1; j++) {
                intermediate_results[i] += matrix[i][j] * results[k - 1][j];
            }
        }
        for (int i = 0; i < rows; i++) {
            results[k][i] = matrix[i][cols - 1] - intermediate_results[i];
        }
        for (int i = 0; i < cols - 1; i++) intermediate_results[i] = 0;
        int count_elem_less_eps = 0;
        for (int i = 0; i < rows; i++) {
            float dif = fabsf(results[k - 1][i] - results[k][i]);
            if (dif < eps) count_elem_less_eps++;
        }
        if (count_elem_less_eps == cols - 1) break;
        else k++;
    }
    return 0;
}

int zeidel_method(float **matrix, float **results, float eps) {
    for (int i = 0; i < rows; i++) {
        float diagonal_el = matrix[i][i];
        matrix[i][i] = 0;
        for (int j = 0; j < cols; j++) {
            matrix[i][j] /= diagonal_el;
        }
    }
    float norm_m = 0;
    if (norm_matrix(matrix) == -1) return -1;
    else {
        norm_m = norm_matrix(matrix);
        printf("Norm of matrix: %1.3f\n\n", norm_m);
    }
    float norm_vector = norm_vector_b(matrix);
    float N = number_of_steps(norm_m, norm_vector, 0.00001);
    printf("Number of steps: %1.0f\n\n", N);
    print_matrix(matrix);
    int k = 1;
    float intermediate_results[cols - 1];
    for (int i = 0; i < cols - 1; i++) intermediate_results[i] = 0;
    int determ_elem = 0;
    while (1) {
        for (int i = 0; i < rows; i++) {
            for (int x = 0; x < cols - 1; x++) {
                if (results[k][x] != 10) determ_elem++;
            }
            for (int j = 0; j < cols - 1; j++) {
                for (int p = 0; p < determ_elem; p++, j++) {
                    intermediate_results[i] += matrix[i][j] * results[k][j];
                }
                determ_elem = 0;
                intermediate_results[i] += matrix[i][j] * results[k - 1][j];
                results[k][i] = matrix[i][cols - 1] - intermediate_results[i];
            }
        }
        for (int i = 0; i < cols - 1; i++) intermediate_results[i] = 0;
        int count_elem_less_eps = 0;
        for (int i = 0; i < rows; i++) {
            float dif = fabsf(results[k - 1][i] - results[k][i]);
            if (dif < eps) count_elem_less_eps++;
        }
        if (count_elem_less_eps == cols - 1) break;
        else k++;
    }
    return 0;
}

int main() {
    float **array;
    get_cols_rows();
    array = new float *[rows];
    for (int i = 0; i < rows; i++) {
        array[i] = new float [cols];
    }
    read_matrix(array);
    print_matrix(array);
    float **results;
    results = new float *[count_elem_results];
    for (int i = 0; i < count_elem_results; i++) {
        results[i] = new float [cols - 1];
    }
    for (int i = 0; i < count_elem_results; i++) {
        for (int j = 0; j < cols - 1; j++) {
            results[i][j] = 10;
        }
    }
    results[0][0] = 0.0, results[0][1] = 0.0, results[0][2] = 0.0;
    printf("1) MPI\n");
    printf("2) Zeidel method\n\n");
    int ch = getch();
    switch (ch) {
        case 49: {
            if (simple_iterations(array, results, 0.001) == -1) {
                print_matrix(array);
                printf("Norm of matrix more than 1, no solution\n\n");
                system("pause");
                return 0;
            }
            break;
        }
        case 50: {
            if (zeidel_method(array, results, 0.001) == -1) {
                print_matrix(array);
                printf("Norm of matrix more than 1, no solution\n\n");
                system("pause");
                return 0;
            }
            break;
        }
    }
    int count_elements = 0;
    for (int i = 0; i < count_elem_results; i++) {
        if (*results[i] != 10) count_elements++;
    }
    printf("Results:\n\n");
    int x = 0, y = 0;
    for (x = 0; x < count_elements; x++) {
        printf("(%d iteration) ", x);
        for (y = 0; y < cols - 1; y++) {
            printf("%1.3f ", results[x][y]);
        }
        printf("\n");
    }
    printf("\n");
    getch();
    //system("pause");
}
