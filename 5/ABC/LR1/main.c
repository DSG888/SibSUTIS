#include <stdio.h>
#include <sys/time.h>

double wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main()
{
	double t1, t2 = wtime();
	int a = 0, b = 0, c, i;
	a = 2;
	b = 4096;

	for (i = 0, c = 1; i < b; ++i)
		c *= a;
	t2 = wtime() - t2;
	printf("C:\t%d ^ %d = %d; %f sec.\n", a, b, c, t2);
	c = 0;

	t1 = wtime();
	__asm__ ("movs r0, %1\n\t"
		"movs r1, %2\n\t"
//		"mov r1, %1\n\t"
		"movs r2, #0\n\t"	//c
		"movs r3, #0\n\t"	//i
		"sub r1, #1\n\t"
		"cmp r1, r3\n\t"
	//	"bgt .E1\n\t"
		"movs r2, #1\n\t"
		".E0: mul r2, r0, r2\n\t"
		"adds r3, #1\n\t"
		"cmp r3, r1\n\t"
		"ble .E0\n\t"
		".E1: movs %0, r2"
	: "=r"(c)
	: "r"(a),"r"(b)
	: "r0", "r1", "r2", "r3"
	);
	t1 = wtime() - t1;
	printf("ASM:\t%d ^ %d = %d; %f sec.\n", a, b, c, t1);

}
