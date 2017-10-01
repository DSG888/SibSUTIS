#include <iostream>
#include <cmath>

#define size 3
#define eps 1E-4

int main(int argc, const char *argv[])
{
	float matrix[size][size + 1] = {{5, -1, 2, 3}, {1, -10, 2, -6}, {1, 2, 5, 12}};
	float tmp, maxB, maxC, out[size], max[size], B[size], C[size][size], mat[size];
	int N, step = 0;
	
	for (int i = 0; i < size; i++)
	{
		tmp = matrix[i][i];
		for (int j = 0; j < size + 1; j++)
		{
			matrix[i][j] /= tmp;
			if (j == size)
				B[i] = matrix[i][j];
			out[i] = 0;
		}
	}
	
	for	(int i = 0; i < size; i++)
	{
		max[i] = 0;
		for	(int j = 0; j < size; j++)
		{
			C[i][j] = matrix[i][j];
			C[i][i] = 0;
			max[i] += C[i][j];
		}
	}
	
	for (int i = 0; i < size; i++)
	{
		if(maxC < max[i])
			maxC = max[i];
		if(maxB < B[i])
			maxB = B[i];
	}
	
	N = (log(eps * (1 - maxC) / maxB)) / log(maxC);
	
	while (step <= N)
	{
		for (int i = 0; i < size; i++)
		{
			mat[i] = 0;
			for (int j = 0; j < size; j++)
			{
				mat[i] = mat[i] + C[i][j] * out[j];
				out[i] = B[i] - mat[i];
			}
		}
		step++;
	}
	
	std::cout << "Норма C = " << maxC << std::endl << "Норма B = " << maxB << std::endl;
    std::cout << "Кол-во шагов, необходимых для достижения заданной точности: " << N << std::endl;
    for (int i = 0; i < size; i++)
		std::cout << "x[" << i << "] = " << out[i] << std::endl;
	return 0;
}