#include <stdio.h>
#include <conio.h>
#include <math.h>

#define N 2
#define EPS 0.0001

float x0[N] = {2, 2};
float x[N], xn[N];
float F[N], W[N][N], y[N];
float matr[N][N + 1];
float norm_x;

void func_F()
{
	F[0] = x[0] * x[0] - x[0] * x[0] * x[0] - 6;
	F[1] = x[0] + x[1] - 4;
}

void func_W()
{
	W[0][0] = 2 * x[0] - 3 * x[1] * x[1];
	W[0][1] = 0;
	W[1][0] = 1;
	W[1][1] = 1;
}

int main()
{
	int i, j, k;
	float tmp, temp = 0;
	for (i = 0; i < N; ++i)
		x[i] = x0[i];
	do
	{
		norm_x = 0;
		func_F();
		func_W();

		for(i = 0; i < N; ++i)
			for(j = 0; j < N; ++j)
				matr[i][j] = W[i][j];

		for(i = 0; i < N; ++i)
			matr[i][N] = F[i];
    /* Прямой ход метода Гаусса */
		for (i = 0; i < N; ++i)
		{
			for (j = i + 1; j < N; ++j)
			{
				tmp =- matr[j][i] / matr[i][i];
				for (k = 0; k <= N; ++k)
					matr[j][k] += tmp * matr[i][k];
			}
		}
		/* Обратный ход */
		for(i = N - 1; i >= 0; --i)
		{
			y[i] = matr[i][N] / matr[i][i] - temp;
			for (temp = 0, j = N - 1; j >= i; --j)
				temp += (matr[i - 1][j] * y[j]) / matr[i - 1][i - 1];
		}
		for (i = 0; i < N; ++i)
			xn[i] = x[i] - y[i];
		for (i = 0; i < N; ++i)
			norm_x += fabs(xn[i] - x[i]);

		for (i = 0; i < N; ++i)
			x[i] = xn[i];
	} while(norm_x > EPS);

	for (i = 0; i < N; ++i)
		printf("x[%d] == %.3f\t", i, x[i]);
	return 0;
}
