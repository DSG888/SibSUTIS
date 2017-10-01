#include <iostream>
#include <cmath>

#define eps 1E-4

float func(float x) 
{
	return (pow(x, 2) - x * 2 - 10);
}

float _func(float x) 
{
    return (2 * x - 2);
}   
 
int main() 
{
	float a = 4, b = 5, c = b, d = 0;
	int step = 0;
	
	do
    {
		d = c;
		c = c - (func(c) / _func(c));
		std::cout << "x = " << c << "\tn = " << ++step << std::endl;
	} while (std::abs(c - d) > eps);
	return 0;
}