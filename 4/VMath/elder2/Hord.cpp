#include <iostream>
#include <cmath>

#define eps 1E-4

float func(float x)
{
	return (pow(x, 2) - x * 2 - 10);
}

int main(int argc, const char *argv[])
{
	int step = 0;
	float a = 4, b = 5, c = 0, d = 0;
	
    do
    {
		d = c;
		c = ((func(a) * b) - (func(b) * a)) / (func(a) - func(b));
        if ((func(a) * func(c)) < 0) 
			b = c;
		if ((func(c) * func(b)) < 0)  
			a = c;
		std::cout << "x = " << c << "\tn = " << ++step << std::endl;
	} while (std::abs(c - d) > eps);
	return 0;
}