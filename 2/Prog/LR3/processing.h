#ifndef PROCESSING_H
#define PROCESSING_H

#include <stdlib.h>
#include <stdio.h>
#include "string.h"

#define MAXPATH 261
#define MAXCNT 10
#define MAXSIZE (MAXPATH*MAXCNT)

#define clRed "\033[38;05;196m"
#define clBoldRed "\033[01;38;05;196m"
#define clNormal "\033[m"
#define clBoldBlue "\033[01;38;05;21m"

/*
ID	Класс					Символы

0	service&priority		[a-z]
1	path					[0-9a-zA-Z/\!@#$%^&*()":;/?>.<, ]
2	host					[0-9a-zA-Z/\@:. ]
3	space					\n [ ] или \t
4	comment					#.*
-1	error
*/
typedef struct
{
	int id;
	char *value;
	int line;
} stu;

int process(char *Text, char *dir, stu *Sign);

#endif
