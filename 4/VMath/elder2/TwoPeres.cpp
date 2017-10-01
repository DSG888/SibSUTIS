#include <iostream>
#include <cmath>

#define eps 1E-4

double integr(double h, int a, int b)
{
	double n = ((b - a) / h);
	int k = (n + 1);
	double x[k], y[k];

	x[0] = a;
	for (int i = 1; i < k; i++)
	{
	   x[i] = (x[i - 1] + h);
	   y[i] = (1 / x[i]);
	}
	double res = 0;

	for (int i = 0; i < k - 1; i++)
	   res += (y[i] + y[i + 1]);

	res = (res * (h / 2));
	return res;
}

int main(int argc, const char *argv[])
{
	double a = 1.0, b = 2.0, h = 0.1, c, d;
	int steps = 0;

	c = integr(h, a, b);
	d = integr(h / 2, a, b);
	h = (h / 2);
	
	std::cout << "Step:" << ++steps << "\th = " << c << "\th/2 = " << d << std::endl;
	
	while (std::abs(c - d) > eps)
	{
		c = d;
		d = integr(h / 2, a, b);
		h = (h / 2);
		
		std::cout << "Step:" << ++steps << "\th = " << c << "\th/2 = " << d << std::endl; 
	}
	return 0;
}
