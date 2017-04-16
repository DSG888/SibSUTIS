#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUF 100


int read_line(float *matrix, int numvars, char str[])
{
    int i = 0;
    char *tok = strtok(str, " \n");
    while (tok != NULL && i <= numvars) {
        if (sscanf(tok, "%f", &matrix[i]) != 1)
            return 1;
        tok = strtok(NULL, " \n");
        i++;
    }
    return i < numvars;
}

int read_from_file(char filename[], float ***mx, int *numvars)
{
    FILE *f = fopen(filename, "r");
    char buf[MAX_BUF];
    fgets(buf, sizeof(buf), f);
    if (sscanf(buf, "%i", numvars) != 1)
        return 1;
    
    int i;
    float **matrix;
    matrix = malloc(*numvars*sizeof(float *));
    for (i = 0; i < *numvars; i++) {
        matrix[i] = malloc((*numvars+1)*sizeof(float));
        if (fgets(buf, sizeof(buf), f) == 0)
            return 1;

        if (read_line(matrix[i], *numvars, buf))
            return 1;
    }
    fclose(f);
    
    *mx = matrix;
    return 0;
}

void matrix_free(float **matrix, int numvars)
{
    int i;
    for (i = 0; i < numvars; i++)
        free(matrix[i]);
    free(matrix);
}

void print_matrix(float **matrix, int numvars)
{
    int i, j;
    for (i = 0; i < numvars; i++) {
        for (j = 0; j < numvars; j++)
            printf("%.2f\t", matrix[i][j]);
        printf("= %.2f\n", matrix[i][numvars]);
    }
}

int main()
{
    char filename[200];
    printf("Enter name file: ");
    scanf("%s", filename);

    float **matrix;
    int numvars;
    if (read_from_file(filename, &matrix, &numvars)) {
        printf("Error read file\n");
        return 1;
    }
    
    printf("Matrica1:\n");
    print_matrix(matrix, numvars);
         
    int i, j, k;
    
    for (j = 0; j < numvars; j++)
        for (i = j+1; i < numvars; i++)
            for (k = numvars; k >= j; k--)
                matrix[i][k] -= matrix[i][j]*matrix[j][k]/matrix[j][j];
 
    
    printf("\nПрямой ход:\n");
    print_matrix(matrix, numvars);
    
    for (j = numvars-1; j >= 0; j--)
        for (i = j-1; i >= 0; i--)
            for (k = numvars; k >= j; k--)
                matrix[i][k] -= matrix[i][j]*matrix[j][k]/matrix[j][j];

    printf("\nобратный:\n");
    print_matrix(matrix, numvars);

    printf("\nОтвет:\n");
    for (i = 0; i < numvars; i++) {
        printf("%c = %.2f\n", i+'a', matrix[i][numvars]/matrix[i][i]);
    }
    getchar();
    getchar();
    matrix_free(matrix, numvars);
    
    return 0;
}
