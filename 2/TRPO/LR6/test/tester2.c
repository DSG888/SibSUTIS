#define CTEST_MAIN

#include "./external/ctest.h"
#include "mytests.c"

int main(int argc, const char** argv)
{
	return ctest_main(argc, argv);
/*	int a, b, c, lA=10, lB=10, lC=10, i, LEN;
	char *Out = (char *)malloc(800 * sizeof(*Out));

	for (a=-10; a <= lA; a++)
		for (b=-10; b <= lB; b++)
			for (c=-10; c <= lC; c++)
			{
				fCalc((double)a, (double)b, (double)c, Out);
				printf("%s\n", Out);
			}
	free(Out);*/


}
