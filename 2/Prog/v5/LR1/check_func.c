#include "check_func.h"
#include "strings.h"
#include <stdio.h>

void space_before(char str[])
{
	int i;
	while (str[0] == ' ')
	{
		for (i = 0; str[i] != '\0'; i++)
		{
			str[i] = str[i + 1];
		}
	}
}

//превышение допустимой длины строки
int chk_strlong(char str[])
{
	int i = 0;
	while (str[i] != '\0')
	{
		i = i + 1;
	}
	return i;
}

//проверка на запрещённые символы
int chk_err_sym(char str[])
{
	char err_sym[] = { '?', '<', '>', '|', '"', '@', '+', ',', '*', '#', ';', '$', '%', '^', '&', '(', ')', '\0' };

	int len = slen(err_sym), i;
	int flg = -1;
	for (i = 0; i < len; i++)
	{
		flg = schr(str, err_sym[i]);
		if (flg != -1)
		{
			break;
		}
	}
	int j, len_str = slen(str);
	for (j = 0; j < len_str; j++)
	{
		if (((str[j] == '\\') && (str[j + 1] == '\\')) || ((str[j] == '/') && (str[j + 1] == '/')))
		{
			flg = j;
		}
	}
	return flg;
}

//два разделителя подряд
int chk_two_delim(char str[], char delim)
{
	int j, flg = -1;
	int len_str = slen(str);
	for (j = 0; j < len_str; j++)
	{
		if ((str[j] == delim) && (str[j + 1] == delim))
		{
			flg = j;
		}
	}
	return flg;
}

int chk_drv_in_str(char str[])
{
	char drive[] = { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M'};
	char suf_drive = ':';
	int i = schr(str, suf_drive); 
	if ((i != -1) && (str[i + 1] == '\\'))
	{
		int j = schr(drive, str[i - 1]);
		if (j != -1)
		{
			return i - 1;
		}
		else
		{
			return j;
		}
	}
	else
	{
		return -1;
	}
}

//неправильные имена дисков
int chk_name_drive(char str[])
{
	int flg = 0;
	int j = 0;
	int i = chk_drv_in_str(str);
	if (i == 0) {
		for (; i<2; i++)
		{
			int tmp = drv_in_str(&(str[0+j]));
			j= j+2;
			if (tmp != -1)
			{
				flg++;
			}
		}
		return flg;
	}
	else
		if (i > 0)
		{
			return -2;
		}
		else
			if ((i == -1) && (str[0] == '/'))
			{
				return 0;
			} 
			else
				if (i == -1)
				{
					return i;
				}
	return 0;
}

int chk_sl(char str[])
{
	int dr = drv_in_str(str);
	if (dr != -1)
	{
		int flg = colch(str,'/');
		return flg;
	}
	return dr;
}

//нет пути после делителя
int chk_null_after_delim(char str[], char delim)
{
	int j, flg = -1;
	int len_str = slen(str);
	for (j = 0; j <= len_str + 3; j++)
	{
		if ((str[j] == delim) && (str[j+2] == '\0'))
		{
			flg = j;
		}
	}
	return flg;
}
