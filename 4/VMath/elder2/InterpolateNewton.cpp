#include <iostream>
#include <cmath>

double x[4] = {1, 2, 3, 4};

double f(double X)
{
	return (X * X);
}

double fact(double X)
{
	if (X >= 1)
		return X * fact(X - 1);
	else 
		return 1;
}

double Delta(double X, int n, double h)
{
	if (n > 1)
		return (Delta(X + h, n - 1, h) - Delta(X, n - 1, h));
	else
		return (f(X + h) - f(X));
}

void Tabl(double X, int n)
{
	std::cout << X << " " << f(X) << " ";
	for (int i = 1; i <= n; i++)
		std::cout << Delta (X, i, 1) << " ";
	std::cout << std::endl;
}

double P(double X, int h, int n)
{
	double result = y[0], qq, q;
	q = (X - x[0]) / h;
	for (int i = 1; i <= n; i++)
	{
		qq = 1;
		for (int j = 1; j <= i; j++)
			qq *= (q - j + 1);
		result += Delta(x[0], i, h) * qq / fact(i);
	}
	return result;
}


int main()
{
	int X = 5;

	std::cout << "x y Dy Dy2 Dy3" << std::endl;

	Tabl(0, 4);
	Tabl(1, 3);
	Tabl(2, 2);
	Tabl(3, 1);
	Tabl(4, 0);

	std::cout << std::endl << "f("<< X << ") = " << P(X, 1, 4) << std::endl;
	
	//system("pause");
	return 0;
}