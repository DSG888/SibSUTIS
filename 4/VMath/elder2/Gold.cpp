#include <iostream>
#include <cmath>

#define eps 1E-4

float func(float x)
{
	return (pow(x, 2) - x * 2 - 10);
}

int main(int argc, const char *argv[])
{
	float a = 4, b = 5, x1, x2, min;
    while (std::abs(a - b) > eps)
	{
		x1 = b - ((b - a) / 1.618);
        x2 = a + ((b - a) / 1.618);
	    if (func(x1) >= func(x2))
			a = x1;
		else 
			b = x2;
	}
    min = ((a + b) / 2);
    std::cout << "min = " << min << std::endl;
	return 0;
}