#include <stdio.h>
#include <conio.h>

float absf(float num);

int main() {
    FILE *f;
    int n, m, i, j, k, x;
    float A[10][11], B[11], max, z;
    f = fopen("Matrix.txt", "rt");
    m = 3;
    n = (m + 1);
    for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
    fscanf(f, "%f", &A[i][j]);
    fclose(f);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
        printf("%12.2f", A[i][j]);
        printf("\n");
    }
    for (k = 0; k < m-1; k++) {
        if (k != m) {
            x = k;
            max = A[k][k];
        for (j = k; j < m; j++) {
            if (absf(A[j][k]) > max) x = j;
        }
        }
        if (k != x) {
            printf("MeH9leM CTpoKy %d Ha cTpoKy %d\n\n", k+1, x+1);
            for (i = 0; i < n; i++) {
                B[i] = A[k][i];
                A[k][i] = A[x][i];
                A[x][i] = B[i];
            }
        }
        else printf("He MeH9leM CTpoKy\n\n");
        for (i = k+1; i < m; i++) {
            z = A[i][k] / A[k][k];
            for (j = k; j < n; j++)
            B[j] = A[k][j] * z;
            for (j = k; j < n; j++) {
                A[i][j] -= B[j];
            }
        }
        for (i = 0; i < m; i++){
        for (j = 0; j < n; j++)
        printf("%12.2f", A[i][j]);
        printf("\n");
    }
    getch();
    }
    for (i = 0; i < 11; i++) B[i] = 0;
    for (k = (m-1); k >= 0; k--) {
        max = A[k][n-1];
        for (i = (n-2); i > k; i--)
            max = (max - (A[k][i]*B[i]));
        B[i] = max / A[k][k];
    }
    for (i = 0; i < m; i++)
        printf("x%d = %f\n", (i+1), B[i]);
    getch();
    return (0);
}

float absf(float num) {
    if (num < 0) num *= (-1);
    return num;
}
