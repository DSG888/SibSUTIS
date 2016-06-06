#define CTEST_MAIN

#include "./external/ctest.h"
#include "../src/consts.h"
#include "../src/calc.h"

CTEST(NormalValue, twoRoots)
{
	double a = 2;
	double b = 2;
	double c = -4;

	double x1;
	double x2;
	int RES;

	RES = SolveEquation(a, b, c, &x1, &x2);

	const double OK_x1 = -2;
	const double OK_x2 = 1;

	ASSERT_EQUAL(RES, TWO_ROOTS);
	ASSERT_DBL_NEAR(OK_x1, x1);
	ASSERT_DBL_NEAR(OK_x2, x2);
	ASSERT_NOT_EQUAL(RES, -1);
}

CTEST(NormalValue, twoRootsCE0)
{
	double a = 2;
	double b = 4;
	double c = 0;

	double x1;
	double x2;
	int RES;

	RES = SolveEquation(a, b, c, &x1, &x2);

	const double OK_x1 = -2;
	const double OK_x2 = 0;

	ASSERT_EQUAL(RES, TWO_ROOTS);
	ASSERT_DBL_NEAR(OK_x1, x1);
	ASSERT_DBL_NEAR(OK_x2, x2);
	ASSERT_NOT_EQUAL(RES, -1);
}

CTEST(NormalValue, oneRootAE0)
{
	double a = 0;
	double b = 2;
	double c = 4;

	double x1;
	double x2;
	int RES;

	RES = SolveEquation(a, b, c, &x1, &x2);

	const double OK_x1 = -2;
	const double OK_x2 = 0;

	ASSERT_EQUAL(RES, ONE_ROOT);
	ASSERT_DBL_NEAR(OK_x1, x1);
	ASSERT_DBL_NEAR(OK_x2, x2);
	ASSERT_NOT_EQUAL(RES, -1);
}
//TODO
CTEST(NormalValue, NoRootAE0aBE0)
{
	double a = 0;
	double b = 0;
	double c = 1;

	double x1;
	double x2;
	int RES;

	RES = SolveEquation(a, b, c, &x1, &x2);

	const double OK_x1 = 0;
	const double OK_x2 = 0;

	ASSERT_EQUAL(RES, NO_ROOT);
	ASSERT_DBL_NEAR(OK_x1, x1);
	ASSERT_DBL_NEAR(OK_x2, x2);
	ASSERT_NOT_EQUAL(RES, -1);
}


CTEST(NormalValue, oneRoot)
{
	double a = 1;
	double b = 2;
	double c = 1;

	double x1;
	double x2;
	int RES;

	RES = SolveEquation(a, b, c, &x1, &x2);

	const double OK_x1 = -1;
	const double OK_x2 = 0;

	ASSERT_EQUAL(RES, ONE_ROOT);
	ASSERT_DBL_NEAR(OK_x1, x1);
	ASSERT_DBL_NEAR(OK_x2, x2);
	ASSERT_NOT_EQUAL(RES, -1);
}

CTEST(NormalValue, noRoots)
{
	double a = 2;
	double b = 2;
	double c = 4;

	double x1;
	double x2;
	int RES;

	RES = SolveEquation(a, b, c, &x1, &x2);

	const double OK_x1 = 0;
	const double OK_x2 = 0;

	ASSERT_EQUAL(RES, NO_ROOT);
	ASSERT_DBL_NEAR(OK_x1, x1);
	ASSERT_DBL_NEAR(OK_x2, x2);
	ASSERT_NOT_EQUAL(RES, -1);
}

CTEST(NormalValue, Endless_roots)
{
	double a = 0;
	double b = 0;
	double c = 0;

	double x1;
	double x2;
	int RES;

	RES = SolveEquation(a, b, c, &x1, &x2);

	const double OK_x1 = 0;
	const double OK_x2 = 0;

	ASSERT_EQUAL(RES, ENDLESS_ROOTS);
	ASSERT_DBL_NEAR(OK_x1, x1);
	ASSERT_DBL_NEAR(OK_x2, x2);
	ASSERT_NOT_EQUAL(RES, -1);
}

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
