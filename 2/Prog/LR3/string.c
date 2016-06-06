#include "string.h"

int slen(char *s)
//	Функция вычисления длины строки
{
	int i, c = 0;
	for ( i = 0; s[i] != '\0'; i++ )
		++c;
	return c;
}

int schr(char s[], char c)
//	Поиск символа в строке
{
	int i, num = -1;
	for(i=0; (s[i] != '\0') && (s[i] != c); i++);
		if(s[i] == c) 
			num = i;
		return num;
}

int stok(char str[], char delim, char *ptr[])
//	Разбиение строки на поля
{
	char *suf = str;
	ptr[0] = str; // первое поле – начало str
	int i, j = 1; // j – счетчик полей
	while( ( i = schr(suf, delim) ) >= 0 )
	{
		suf[i] = '\0';
		suf = suf + i + 1;
		ptr[j] = suf;
		j++;
	}
	return j;
}

int suntok(char *str, char delim, char *ptr[80],int cnt)
//	Сборка строки из полей
{
	int i;
	for(i = 1; i < cnt; i++)
		*(ptr[i] - 1) = delim;
	return 0;
}

void scpy(char m[], char y[])
//	Функция копирования строк
{
	int i;
	for(i=0; y[i] != '\0'; i++)
		m[i] = y[i];
	m[i] = '\0';
}

int scmp(char m[], char n[])
//	Функция сравнения строк
{
	int i, j = 0;
	if(slen(m) == slen(n))
	{
		for(i = 0; i < slen(m); i++)
			if(m[i] == n[i])
				j++;
		if(i == j)
			return 0;
	}
	else
		return 1;
	return -1;
}

char *skip_spaces(char *suf)
// Функция пропуска пробельных символов
{
	while( schr(" \t\n",*suf) )
	{
		suf++;
	}
	return suf;
}

int myisspace(int c)
// Функция определения пробельных символов
{ 
	return ((c) == ' ' || ((c) >= '\t' && (c) <= '\r'));
}

int myisdigit(int c)
// Функция определения цифр
{ 
	return ((c) >= '0' && (c) <= '9');
}

int myatoi(char *string)
// Функция перевода строки в число
{
    int result = 0;
    unsigned int digit;

    for ( ; ; string += 1)
    {
		digit = *string - '0';
		if (digit > 9)
		{
			break;
		}
		result = (10 * result) + digit;
    }
    return result;
}
