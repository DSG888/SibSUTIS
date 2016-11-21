#include "check.h"
#include <stdio.h>
#include <stdlib.h>
#include "check_func.h"

#define str_size 1024

void check(char str[], char delim)
{
	space_before(str);	//убирает пробел перед строкой
		
	int two_delim_flg = chk_two_delim(str, delim);
	if (two_delim_flg != -1)
	{
		printf("Warning! Two delim! '%c%c' idx '%d %d'\n", str[two_delim_flg], str[two_delim_flg + 1], two_delim_flg, two_delim_flg + 1);
	}

	int str_long = chk_strlong(str);
	if (str_long > str_size)
	{
		printf("Excess path length!\nMAX_long:%d!\n", str_size);
		exit(EXIT_FAILURE);
	}
	
	int null_after_del = chk_null_after_delim(str, delim);
	if (null_after_del != -1)
	{
		printf("Warning! No path after delim!\n");
	}
}
