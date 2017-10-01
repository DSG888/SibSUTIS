#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#define M 3
#define N 4

int print(float A[M][N]) {
    int i, j;
    for(i = 0; i < 3; i++)
    {
       for(j = 0; j < 4; j++)
       {
          printf("%10.3f", A[i][j]);
       }
       printf("\n");
    }
    return 0;
}

int mt_clrscr()
{
    printf("\E[H\E[J");
    return 0;
}

int main()
{   
    mt_clrscr();
    printf("Решение СЛАУ методом МПИ: \n\n");
       
    const float e = 0.001;
    int i, j, k, shagINT;
    float maxC[N], maxB = 0, X[M] = {0,0,0};
    float temp, B[M], C[M][M], YM[M] = {0, 0, 0};
    float A1[M][N];  //заполнение матрицы 
    float A[M][N]={{5, -1, -1, 3},
                   {-1, -3, 0, -7},
                   {1, 1, 4, 3}}; 

    for(i = 0; i < M; i++) 
        for(j = 0; j < N; j++)
                A1[i][j] = A[i][j];
    //сохранение первоначальной матрицы

    printf("\nЗаданная матрица: \n\n");
    print(A);
    //приведением матрицы к виду удобному для итерации (деление матрицы на диагональный элемент)
    for(i = 0, j = 0; i < M; i++, j++)
    {   
        temp = A[i][j];
        for(k = 0; k < N; k++)  
        {
            A[i][k] = A[i][k] / temp;
        }
        A[i][j] = 0;
    }
    //вывод преобразованной матрицы с занулением главной диагонали, создание матрицы С и вектора В     
    printf("\nПреобразованная матрица: \n\n");
    print(A);
    for(i = 0; i < M; i++) //переписываем А в С без последнего столбика
        for(j = 0; j < (N - 1); j++)
                C[i][j] = A[i][j]; 

    for(i = 0; i < M; i++) { //Записываем в B значения
            B[i] = A[i][N - 1];
            //printf("%f ", B[i]); //В качестве начального приближения возьмём вектор-столбец свободных членов приведённой системы:
    }
    //ищем max модуль суммы в строке
    maxC[M]=0;
    for(i = 0; i < M; i++)
    {
        for(j = 0; j < M; j++)
        {
            if (A[i][j] < 0)
		A[i][j] = -A[i][j];
            maxC[i] += A[i][j];
        }     
        if(maxC[M] < maxC[i])
            maxC[M] = maxC[i];            
    }

   // for(j = 0; j <= M; j++) 
    //   printf("max = %f ", maxC[j]); //проверка максимального модуля C

    if(maxC[M] >= 1) {
        printf("\nМатрица не удовлетворяет условиям сходимости");
        return 0;
    }

    //поиск НОРМ и расчёта колличества шагов
    printf("\nНормы и количество шагов:\n\n");

    printf("Норма C = %4.3f\n", maxC[M]);
    maxB = 0;
    //ищем максимальный модуль B
    for(i = 0; i < M; i++) {
        if(A[i][N - 1] < 0)
            A[i][N - 1] = -A[i][N - 1];
        if(maxB < A[i][N - 1]) 
            maxB = A[i][N - 1];
    }
    printf("Норма B = %4.3f\n", maxB);
    
    
    shagINT = (log((e * (1 - maxC[M])) / maxB ) / log(maxC[M])) + 1; 
    printf("Количество шагов %d\n",shagINT);
    
    //выполнение первого шагов с выводом
    for(k = 0; k < shagINT; k++) {         
        for(i = 0; i < M; i++)
            for(j = 0; j < M; j++)  
                YM[i] = YM[i] + C[i][j] * X[j]; 

        for(i = 0; i < M; i++) {
            X[i] = B[i] - YM[i];
            YM[i] = 0;
        } 
    }

    printf("\nОтвет:\n");
    for(i = 0; i < M; i++) 
        printf("\nX%d = \t%2.3f", i, X[i]);
    
    
    printf("\n\n\nРешение СЛАУ методом ЗЕЙДЕЛЯ: \n\n");
    
    printf("\nЗаданная матрица: \n\n");
    print(A1);
    printf("\nПреобразованная матрица: \n\n");
    
    for(i = 0; i < M; i++) {
        for(j = 0; j < M; j++) {
            printf("%10.3f", C[i][j]);
        }    
        printf("\n");
    }
    for(i = 0; i < M; i++)   
        X[i] = 0;

    //решение методом зейделя
    for(k = 0; k < shagINT; k++) {
       for(i = 0; i < M; i++) {   
            X[i] = B[i];
            for(j = 0; j < M; j++) {
                if(j == i) 
                    continue; 
                X[i] = X[i] - C[i][j] * X[j];
            }
        } 
    }
    printf("\nОтвет:\n");
    for(i = 0; i < M; i++) 
        printf("\nX%d = \t%2.3f", i, X[i]); 
    printf("\n"); 
    return 0;
}
