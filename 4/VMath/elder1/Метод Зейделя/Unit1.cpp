#include <conio.h>
#include <stdio.h>
#define n 4
#define m 3

int main() {
    FILE *f;
    int i, j, k, t;
    float matr[3][4], C[3][3], x[4][3], b[3], A[4], sum[3] = {0}, C1[3] = {0};
    f = fopen("Matrix.txt", "rt");
    for (j = 0; j < n; j++) x[0][j] = 0;
    for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
    fscanf(f, "%f", &matr[i][j]);
    printf("Matrix:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
        printf("%12.4f", matr[i][j]);
        printf("\n");
    }
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) A[j] = matr[i][j] / matr[i][i];
        for (j = 0; j < n; j++) matr[i][j] = A[j];
    }
    for (i = 0; i < m; i++)
    matr[i][i]--;
    for (i = 0; i < m; i++)
    for (j = 0; j < n-1; j++)
    C[i][j] = matr[i][j];
    for (i = 0, j = (n-1); i < m; i++) b[i] = matr[i][j];
    for (i = 0; i < 3; i++) C1[i] = C[0][i] + C[1][i] + C[2][i];
    printf("C:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++)
        printf("%12.4f", C[i][j]);
        printf("\n");
    }
    printf("B:\n");
    for (i = 0; i < m; i++)
    printf("%12.4f\n", b[i]);
    printf("Vvedite kolichestvo shagov: ");
    scanf("%d", &k);
    j++;
    for (t = 0; t < k; t++){
        printf("\n");
        for (i = 0; i < 3; i++) {
            if (i == 0) x[t][i] *= C1[i];
            else x[t][i] = x[t][i-1] * C1[i];
        }
        printf("\nx%d:\n", t+1);
        for (i = 0; i < 3; i++) {
            x[t+1][i] = b[i] - x[t][i];
            printf("%12.4f\n", x[t+1][i]);
        }
    }
    printf("result: \n");
    for (i = 0; i < m; i++)
    printf("\nx%d =%12.4f", i, x[k][i]);
    return (0);
}
