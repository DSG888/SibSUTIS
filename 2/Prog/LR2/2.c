#include <stdio.h>

typedef struct
{
//	char str[3];
//	int num;
	int num;
	char str[3];
} NumberRepr;

void format(NumberRepr* number)
{
	sprintf(number->str, "%3d", number->num);
}

int main()
{
	NumberRepr number = { .num = 1025 };
	format(&number);
	printf("str: %s\n", number.str);
	printf("num: %d\n", number.num);
	return 0;
}
