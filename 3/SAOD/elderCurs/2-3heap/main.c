#include "ttheap.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
	ttheap_t *TTH = tth_alloc(10);
	tth_insert(TTH, 1, 4);
	
//	tth_print(TTH);
}
