#ifndef CONSTs
#define CONSTs

#define NO_ROOT       0
#define ONE_ROOT      1
#define TWO_ROOTS     2
#define ENDLESS_ROOTS 3

#define IsZero(x)     (fabs(x) <= DBL_EPSILON)
#define IsMoreZero(x) (x > DBL_EPSILON)
#define IsLessZero(x) (x < -DBL_EPSILON)

#endif
