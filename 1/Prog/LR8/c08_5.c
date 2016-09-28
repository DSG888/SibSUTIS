#include <stdio.h>
int main ()
{
	int a, b, t;

	a = 5;
	b = 6;
	printf("a=%d b=%d\n",a, b);
	t = a;
	a = b;
	b = t;
	printf("a=%d b=%d t=%d\n", a, b, t);		
	return 0;	
}
