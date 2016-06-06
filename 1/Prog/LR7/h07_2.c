/*
Модифицировать программу с06_9-cvt2.c так, чтобы она выполняла перевод из десятичной в шестнадцатеричную систему счисления. Проверить ее работу на следующих входных данных:
1) f5
2) ABFF
3) FEFAAA
Вопрос: Какие типы данных достаточны, если входные данные не превышают число 1)? 2)? 3)?
*/

#include <stdio.h>
#include <stdint.h>

int main()
{
	long long int i;
	printf("Input HEX i: ");
	scanf("%x", &i);
	printf("Dec representation of i: %d\n",i);
	return 0;
}
