#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

int cols, rows;

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

int search_maximum(float **array, int j) {
    int i, k;
    float max = fabsf(array[j][j]);
    for (i = j + 1; i < rows; i++) {
        if (fabsf(array[i][j]) > max) {
            max = array[i][j];
            k = i;
        }
        else k = j;
    }
    return k;
}

void swap_rows(float **array, int row_1, int row_2) {
    for (int j = 0; j < cols; j++) {
        float temp = array[row_1][j];
        array[row_1][j] = array[row_2][j];
        array[row_2][j] = temp;
    }
}

void modified_gauss(float **array) {
    printf("Source matrix: \n");
    for (int k = 0; k < rows; k++) {
        for (int l = 0; l < cols; l++) {
            if (l == cols - 1) printf(" | ");
            printf("%1.1f ", array[k][l]);
        }
        printf("\n");
    }
    printf("\nModified Gauss method: \n\n");
    int diag = 0;
    for (int j = 0; j < rows - 1; j++) {
        int row = search_maximum(array, j);
        printf("Changing %d and %d rows\n\n", j + 1, row + 1);
        if (row != j) {
            printf("Changing %d and %d rows\n\n", j + 1, row + 1);
            swap_rows(array, row, j);
        }
        for (int k = diag + 1; k < rows; k++) {
            float ratio = -(array[k][diag] / array[diag][diag]);
            for (int l = j; l < cols; l++) {
                array[k][l] += array[diag][l] * ratio;
            }
            for (int k = 0; k < rows; k++) {
                for (int l = 0; l < cols; l++) {
                    if (l == cols - 1) printf(" | ");
                    printf("%1.1f ", array[k][l]);
                }
                printf("\n");
            }
            printf("\n");
        }
        diag++;
    }
    int size = cols - 1;
    float *result = new float [size];
    result[0] = array[rows - 1][cols - 1]/array[rows - 1][cols - 2];
    float temp;
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
    printf("Result: ");
    for (int p = size - 1; p >= 0; p--) {
        printf("%1.1f ", result[p]);
    }
    printf("\n\n");
}

void Gauss(float **array) {
    printf("Source matrix: \n");
    for (int k = 0; k < rows; k++) {
        for (int l = 0; l < cols; l++) {
            if (l == cols - 1) printf(" | ");
            printf("%1.1f ", array[k][l]);
        }
        printf("\n");
    }
    printf("\nGauss method: \n");
    for (int diag = 0; diag < rows - 1; diag++) {
        for (int k = diag + 1; k < rows; k++) {
            float ratio = -(array[k][diag]/array[diag][diag]);
            for (int l = 0; l < cols; l++) {
                array[k][l] += array[diag][l] * ratio;
            }
            for (int k = 0; k < rows; k++) {
                for (int l = 0; l < cols; l++) {
                    if (l == cols - 1) printf(" | ");
                    printf("%1.1f ", array[k][l]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
    int size = cols - 1;
    float *result = new float [size];
    result[0] = array[rows - 1][cols - 1]/array[rows - 1][cols - 2];
    float temp;
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
    printf("Result: ");
    for (int p = size - 1; p >= 0; p--) {
        printf("%1.1f ", result[p]);
    }
    printf("\n\n");
}

int main() {
    float **array;
    get_cols_rows();
    array = new float *[rows];
    for (int i = 0; i < rows; i++) {
        array[i] = new float [cols];
    }
    read_matrix(array);
    //Gauss(array);
    modified_gauss(array);
    getch();
}
