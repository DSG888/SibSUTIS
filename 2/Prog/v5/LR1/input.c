#include "input.h"
#include <stdio.h>

void input(char str[], char *delim)
{
	printf("Input delim: ");
	scanf("%c%*c", delim);
	printf("Input paths: ");
	fgets(str, 1024, stdin);
}
