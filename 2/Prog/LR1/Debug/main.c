/*
Задание:
При разработке подпрограмм в соответствии с заданием следует учитывать, что:
	1. Исходная задача должна быть разбита на четыре основные подзадачи:
		1) ввод данных – input() – предусматривает взаимодействие с пользователем и возвращает строку, содержащую входные данные (путь);
		2) проверка корректности данных – check() – которая обеспечивает проверку допустимости длины входной строки и используемых в ней символов. Значения, возвращаемые функцией check(), должны позволять определить тип ошибки и (если возможно) номер символа, в которой она обнаружена;
		3) обработка – process() – входных данных согласно заданию;
		4) вывод данных – output
		Взаимодействие между указанными функциями осуществляется через данные. Каждая из них, при необходимости, также разбивается на подзадачи. Разбиение производится до тех пор, пока подзадачи не становятся тривиальными, например, вычисление длины строки.
	2. Каждая подзадача оформляется в виде подпрограммы.
	3. Не допускается использования стандартных функций обработки строк. Все операции над строками должны быть реализованы самостоятельно в виде отдельных подпрограмм. Эти подпрограммы необходимо разместить в отдельном файле strings.c , а прототипы функций – в файле strings.h . Файл strings.h подключается с помощью директивы #include "strings.h" в исходном файле, использующем эти функции. Примерами типичных функций, которые должны присутствовать в каждой программе являются:
		1) функция вычисления длины строки (slen);
		2) функция разбиения строки на элементы-токены (stok), разделенные заданным символом (например, символ “/” при анализе пути или символ “.”, при разборе IP-адресов или доменных имен);
		3) функция проверки символа на принадлежность заданному множеству символов (sspn), необходимая для проверки допустимости используемых символов.
		4) функция сравнения строк (scmp);
		5) функция копирования строк (scpy).
	В отчете о лабораторной работе должен присутствовать список тестовых данных, на которых проверялась корректность работы программы, и соответствующие результаты работы программы.
	Набор тестов должен обеспечивать проверку поведения программы для всех классов входных данных:
		1) некорректный файловый путь;
		2) превышение допустимой длины пути;
		3) допустимый путь, который не удовлетворяет указанным в задании условиям;
		4) допустимый путь, удовлетворяющий условиям.

Вариант 3. II уровень сложности
Преобразовать все пути входного списка, заданные относительно домашних каталогов указанных пользователей (вида ~alex/somedir), к абсолютным путям. Имя каталога (dir), в котором находятся домашние каталоги пользователей, вводится с клавиатуры.
Вход:
	delim: +
	dir: /home/stud/
	paths: ~/games/packman.cpp+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc
Выход:
	new paths: ~/games/packman.cpp+/home/stud/alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc
			   ~/games/packman.cpp+/home/stud/alex/docs+~/study/Prog/lab4.c +/usr/bin/gcc
*/

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
#define CLEAR "\033c"

void myexit()
{
	__asm__("movl $1, %eax\n"
			"movl $0, %ebx\n"
			"int $0x80\n" );
}

void input(char *a, char *c, char *d)
{
	// a - paths
	// d - delim
	// c - dir
	printf("%s Введите строку\n  Пример: ~/games/packman.cpp+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc\n : ",CLEAR);
	fgets(a, MAXSIZE, stdin);

	if ((slen(a) == 1))
	{
		printf("%sСтрока не введена%s\n", clBoldRed, clNormal);
		myexit();
	}

	printf("Введите с клавиатуры имя каталога (dir), в котором находятся домашние каталоги пользователей\n  Пример: /home\n : ");
	fgets(c, MAXPATH, stdin);

	if (slen(c) == 1)
	{
		printf("%sПуть не введен%s\n", clBoldRed, clNormal);
		myexit();
	}
	if (c[slen(c) - 1] == '/')
		c[slen(c) - 1] = '/';

	printf(" Введите разделительный символ\n  Пример: +\n : ");
	scanf("%c", d);
//	scanf("%c%*c",&b);

	if (c[0] != '/')
	{
		printf("%sПуть dir не является абсолютным%s\n", clBoldRed, clNormal);
		myexit();
	}

	a[slen(a) - 1] = '\0';
	c[slen(c) - 1] = '\0';

	printf("%sВходные данные:\n  Строка:\t%s\n  Директория:\t%s\n  Разделительный символ: %c\n\n",CLEAR, a, c, *d);
	if ((32 > *d) || (126 < *d))
	{
		printf("%sВведен запрещенный разделительный символ%s\n",clBoldRed,clNormal);
		myexit();
	}
	return;
}

void check(char *pat, char *dir, char del)
{
	char *RAW[MAXSIZE];						// Указатели на пути
	int Z = 0, i;
	Z = stok(pat, del, RAW);				// Разбиение строки на поля
	for (i = 0; i < Z; i++)
	{
		if (slen(&pat[i]) > MAXPATH - 2)
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
	char *RAW[MAXSIZE];						// Указатели на пути
	char *TOK[MAXSIZE];						// Указатели на токены
	char *a;								// Временный указатель
	int Z = 0, R = 0, i, j, k, dLEN, pLEN;
	pLEN = slen(pat);
	Z = stok(pat, del, RAW);				// Разбиение строки на поля
	dLEN = slen(dir);						// Длина строки
	if (Z > 10)
	{
		printf("%sПо заданию программа не может обработать больше 10 путей%s\n", clBoldRed, clNormal);
		myexit();
	}
	printf(" Строка разбита: %d\n Результат разбиения: \n", Z);
	for (i = 0; i < Z; i++)
		printf("  [%d]: %s\n", i + 1, RAW[i]);

	// Строка разбита на +
	printf(" Результаты разбиения путей на составляющие:\n");
	for (i = 0; i < Z; i++)
	{
		// Обход всех путей
		R = stok(RAW[i], '/', TOK);		// Разбивается путь на каталоги
		printf("  Путь %d разбит: \n", i + 1);
		for (j = 0; j < R; j++)
		{
			printf("   [%d] %s", j+1, TOK[j]);
			if ((j == 0) && (slen(TOK[j]) > 1) && (TOK[j][0] == '~'))
			{
				// Отловлен путь, который нужно изменить
				printf("\t%s[Требуется замена]%s", clBoldBlue, clNormal);
				// Сдвиг строки
				for (a = pat + pLEN; a > TOK[j]; --a)
					*(a + dLEN) = *a;
				// Вставка строки
				scpy(TOK[j], dir);
				*(TOK[j]+dLEN) = '/';
				// Сдвиг указателей
				for (k = i + 1; k < Z; k++)
					RAW[k] += dLEN;
				for (k = j - 1; k < R; k++)
					TOK[k] += dLEN;
			}
			printf("\n");
		}
		suntok(RAW[i], '/', TOK, R);
		printf("  Путь %d собран: %s \n", i + 1, RAW[i]);
		printf("\n");
	}
	suntok(pat, del, RAW, Z);
	return;
}

void output(char *str)
{
	printf(" Выходные данные:\n  Строка:\t%s\n", str);
}

int main()
{
	char DELIM = 0;								// Разделительный символ
	char PATHS[MAXSIZE+MAXSIZE*MAXCNT] = {'\0'};// Старая строка
	char DIR[MAXSIZE] = {'\0'};					// Домашний каталог

//FIXME
//	char PATHS[MAXSIZE] = {"~games/packman.cpp+~alex/docs+~study/Prog/lab4.c+/usr/bin/gcc"};
//	char PATHS[MAXSIZE] = {"~games/packman.cpp+~alex/docs+~study/Prog/lab4.c+/usr/bin/gcc"};

//	char DIR[MAXPATH] = {"/home"};
//	char DELIM = '+';

	input(PATHS, DIR, &DELIM);				// Ввод данных
	process(PATHS, DIR, DELIM);
	check(PATHS, DIR, DELIM);
	output(PATHS);
	return 0;
}
