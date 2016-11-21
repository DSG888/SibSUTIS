/*
5. Преобразовать все Windows пути во входном списке к Linux-путям, используя формат эмулятора Cygwin.
	Вход:
		delim: +
		paths: C:\Windows\system32+E:\Distrib\msoffice.exe+/home/alex/prog/lab4.c
	Выход:
		new paths: /cygdrive/c/Windows/system32+/cygdrive/e/Distrib/msoffice.exe+/home/alex/prog/lab4.c 
*/

#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "process.h"
#include "check.h"
#include "output.h"

#define str_size 2048

int main()
{
	char str[str_size] = {'\0'};
//	char str[str_size] = "C:\\Windows\\system32+E:\\Distrib\\msoffice.exe+/home/alex/prog/lab4.c";
	char delim = '\0';
	input(str, &delim);
	check(str, delim);
	process(str, delim);
	output(str);
	return 0;
}
