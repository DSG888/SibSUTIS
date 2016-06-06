#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

#include "string.h"

#define MAXPATH 261
#define MAXCNT 10
#define MAXSIZE (MAXPATH*MAXCNT)

#define clRed "\033[38;05;196m"
#define clBoldRed "\033[01;38;05;196m"
#define clNormal "\033[m"
#define clBoldBlue "\033[01;38;05;21m"

void myexit()
{
	__asm__("movl $1, %eax\n"
			"movl $0, %ebx\n"
			"int $0x80\n" );
}

void input(char *a, char *c, char *d)
{
	int i;
	printf(" paths: ");
	fgets(a, MAXSIZE, stdin);

	if ((slen(a) == 1))
	{
		printf("%sСтрока не введена%s\n", clBoldRed, clNormal);
		myexit();
	}

	printf(" dir: ");
	fgets(c, MAXPATH, stdin);
	if (slen(c) == 1)
	{
		printf("%sПуть не введен%s\n", clBoldRed, clNormal);
		myexit();
	}
	printf(" delim: ");
	scanf("%c", d);
//	scanf("%c%*c",&b);

	if (c[0] != '/')
	{
		printf("%sПуть dir не является абсолютным%s\n", clBoldRed, clNormal);
		myexit();
	}

	a[slen(a) - 1] = '\0';
	c[slen(c) - 1] = '\0';

	for (i = slen(a)-1; i > 1; --i)
		if ((a[i]=='/')&&(a[i-1]=='/'))
		{
			printf("%sСтрока не корректна%s\n", clBoldRed, clNormal);
			myexit();
		}

	for (i = slen(c)-1; i >= 1; --i)
		if ((c[i]=='/')&&(c[i-1]=='/'))
		{
			printf("%sПуть не корректен%s\n", clBoldRed, clNormal);
			myexit();
		}

	if (c[slen(c) - 1] == '/')
		c[slen(c) - 1] = '\0';

	for (i=0; a[i]!='\0'; i++)
		if ((32>a[i]) || (a[i]==34) || (a[i]==42) || (a[i]==58) || (a[i]==60) || (a[i]==62) || (a[i]==63) || (a[i]==64) || (a[i]==92) || (126<a[i]))
		{
			printf("Строка содержит запрещенный заданием символ: \"%c\"\n", a[i]);
			printf("Запрещенный заданием символ по счету: \"%d\"\n", i);
			myexit();
		}

	for (i=0; c[i]!='\0'; i++)
		if ((32>c[i]) || (c[i]==34) || (c[i]==42) || (c[i]==58) || (c[i]==60) || (c[i]==62) || (c[i]==63) || (c[i]==64) || (c[i]==92) || (126<c[i]))
		{
			printf("Путь содержит запрещенный заданием символ: \"%c\"\n", c[i]);
			printf("Запрещенный заданием символ по счету: \"%d\"\n", i);
			myexit();
		}

	if ((32 > *d) || (126 < *d))
	{
		printf("%sВведен запрещенный разделительный символ%s\n",clBoldRed,clNormal);
		myexit();
	}
	return;
}

void check(char *pat, char *dir, char del)
{
	char *RAW[MAXSIZE];
	int Z = 0, i;
	Z = stok(pat, del, RAW);
	for (i = 0; i < Z; i++)
	{
		if (slen(RAW[i]) > (MAXPATH - 2))
		{
			printf("%sПолучен путь (%d) длина которого больше разрешенной%s\n", clBoldRed, i + 1, clNormal);
			myexit();
		}
		if (( (RAW[i][0]) != '~') && ( (RAW[i][0]) != '/'))
		{
			printf("%sПолучен путь (%d) который не является частью фс unix%s\n", clBoldRed, i+1,clNormal);
			myexit();
		}
	}
	suntok(pat, del, RAW, Z);
}

void process(char *pat, char *dir, char del)
{
	char *RAW[MAXSIZE];
	char *TOK[MAXSIZE];
	char *a;
	int Z = 0, R = 0, i, j, k, dLEN, pLEN;
	pLEN = slen(pat);
	Z = stok(pat, del, RAW);
	dLEN = slen(dir);
	if (Z > 10)
	{
		printf("%sПо заданию программа не может обработать больше 10 путей%s\n", clBoldRed, clNormal);
		myexit();
	}
	for (i = 0; i < Z; i++)
	{
		R = stok(RAW[i], '/', TOK);
		for (j = 0; j < R; j++)
		{
			if ((j == 0) && (slen(TOK[j]) > 1) && (TOK[j][0] == '~'))
			{
				for (a = pat + pLEN; a > TOK[j]; --a)
					*(a + dLEN) = *a;
				scpy(TOK[j], dir);
				*(TOK[j]+dLEN) = '/';
				for (k = i + 1; k < Z; k++)
					RAW[k] += dLEN;
				for (k = j - 1; k < R; k++)
					TOK[k] += dLEN;
			}
		}
		suntok(RAW[i], '/', TOK, R);
	}
	suntok(pat, del, RAW, Z);
	return;
}


void output(char *str)
{
	printf(" new paths: %s\n", str);
}

int main()
{
	char DELIM = 0;
	char PATHS[MAXSIZE+MAXSIZE*MAXCNT] = {'\0'};
	char DIR[MAXSIZE] = {'\0'};

	input(PATHS, DIR, &DELIM);
	process(PATHS, DIR, DELIM);
	check(PATHS, DIR, DELIM);
	output(PATHS);
	return 0;
}
