#include "./external/ctest.h"
#include "../src/calc.h"

#define NO_ROOT       0
#define ONE_ROOT      1
#define TWO_ROOTS     2
#define ENDLESS_ROOTS 3

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
}
