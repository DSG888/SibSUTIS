/* метод Монте-Карло */
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define ax -2
#define bx 2
#define ay -2
#define by 2
#define k 500
#define N 5

int i, j, l;
float s, Int;

float f(float x, float y)
{
	if (x * x + y * y > 4)
		return (0);
	if (x * x + y * y <= 4)
		return (x * x + y * y);
}

int main()
{
	clrscr();
	randomize();
	l = 0;
	do
	{
		for (i = 0; i < k; ++i)
			for (j = 0; j < k; ++j)
				s += f(ax + (bx - ax) * random(k) / k, ay +(by - ay) * random(k) / k);
		Int = s * (bx - ax) / k * (by - ay) / k;
		printf("Значение интеграла: %.6f\n", Int);
		s = 0;
		l++;
	} while (l < N);
	getch();
	return 0;
}
