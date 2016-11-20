#include "processing.h"

int Researcher(char *Str)
{
	int isipv4(char *str)
	{
		char *EL[MAXSIZE];
		int i, j;
		if ((7 > slen(str)) || (15 < slen(str)))
			return 0;
		int Z = stok(str, '.', EL);
		if (Z != 4)
		{
			suntok(str, '.', EL, Z);
			return 0;
		}
		for (i = 0; i < Z; ++i)
		{
			for (j = 0; EL[i][j] != '\0'; ++j)
			{
				if (myisdigit(EL[i][j]))
					continue;
				else
				{
					suntok(str, '.', EL, Z);
					return 0;
				}
			}
			if (255 < myatoi(EL[i]))
			{
				suntok(str, '.', EL, Z);
				return 0;
			}
		}
		suntok(str, '.', EL, Z);
		return 1;
	}
	
	int isdomain(char *str)
	{
		char d_ru[] = "ru";
		char d_com[] = "com";
		char d_org[] = "org";
		char *EL[MAXSIZE];
		int i;
		if (6 > slen(str))
			return 0;
		int Z = stok(str, '.', EL);
		if (!((scmp(EL[Z - 1], d_ru) == 0) || (scmp(EL[Z - 1], d_com) == 0) || (scmp(EL[Z - 1], d_org) == 0)))
		{
			suntok(str, '.', EL, Z);
			return 0;
		}
		suntok(str, '.', EL, Z);
		if (3 != Z)
			return 0;
		for (i = 0; str[i] != '\0'; i++)
		{
			if (!((str[i] >= 'A')&&(str[i] <= 'Z') || ( (str[i] >= 'a')&&(str[i] <= 'z')) || str[i] == '.' ))
				return 0;
		}
		return 1;
	}
	
	int ispath(char *str)
	{
		int i;
		if (1 > slen(str))
			return 0;
		for (i=0; str[i]!='\0'; i++)
			if ((' '>str[i]) || (str[i]=='"') || (str[i]=='*') || (str[i]==':') || (str[i]=='<') || (str[i]=='>') || (str[i]=='?') || (str[i]=='\\') || ('~'<str[i]))
				return 0;
		if ( ( (str[0]) != '~') && ( (str[0]) != '/') )
		{
			if (str[0] != '@')
				return 0;
			else
				if (!(isipv4(&str[1]) || isdomain(&str[1])))
					return 0;
		}
		return 1;
	}
	
	int isservice(char *str)
	{
		char *EL[MAXSIZE];
		int i;
		if ((str[0] == '*') || (str[0] == '.') || (str[slen(str)-1] == '.'))
			return 0;
		if (3 > slen(str))
			return 0;
		int Z = stok(str, '.', EL);
		suntok(str, '.', EL, Z);
		if (2 != Z)
			return 0;
		for (i = 0; str[i] != '\0'; i++)
		{
			if (!((str[i] >= 'A')&&(str[i] <= 'Z') || ( (str[i] >= 'a')&&(str[i] <= 'z')) || (str[i] == '.') || (str[i] == '*') ))
				return 0;
		}
		return 1;
	}

	if (Str[0] == '#')
		return 4;
	if (Str[0] == '+')
		if (isipv4(&Str[1]) || isdomain(&Str[1]))
			return 2;
	if (ispath(Str))
		return 1;
	if (isservice(Str))
		return 0;
	return -1;
}

int SplitStr(char *text, stu *sig)
{
	char word[MAXPATH]= {' '};
	int CountWord = 0, i, inWord = 0, WLen = 0, count = 0, line = 0;
	

	for (i=0; text[i] != '\0'; i++)
	{
		if (myisspace(text[i]) || text[i] == '\n')
		{
			inWord = 0;
			if (WLen)
			{
				word[WLen] = '\0';
				sig[count].value = (char*)malloc((WLen + 1) * sizeof(char));
				sig[count].id = Researcher(word);
				sig[count].line = line;
				scpy(sig[count].value, word);
				count++;
			}
			word[0] = text[i];
			word[1] = '\0';
			sig[count].value = (char*)malloc(2 * sizeof(char));
			sig[count].id = 3;
			sig[count].line = line;
			scpy(sig[count].value, word);
			count++;
			WLen = 0;
			if (text[i] == '\n')
				line++;
		}
		else
		{
			word[WLen] = text[i];
			++WLen;
			if(inWord == 0)
			{
				inWord = 1;
				++CountWord;
			}
		}
	}
	return count;
}

void OverwritePath(char *pat, char *dir)
{
	int R = 0, k, dLEN, pLEN;
	char *TOK[MAXSIZE];
	char *a;
	pLEN = slen(pat);
	dLEN = slen(dir);

	R = stok(pat , '/', TOK);
	if ((slen(TOK[0]) > 1) && (TOK[0][0] == '~'))
	{
		for (a = pat + pLEN; a > TOK[0]; --a)
			*(a + dLEN) = *a;
		scpy(TOK[0], dir);
		*(TOK[0] + dLEN) = '/';
		for (k = 0 - 1; k < R; k++)
			TOK[k] += dLEN;
	}
	suntok(pat, '/', TOK, R);
	return;	
}

int process(char *Text, char *dir, stu *Sign)
{
	int Z = SplitStr(Text, Sign);
	int i, j, k;
	
	for (i=0; i < Z ; i++)
	{
		// замена по заданию
		if (Sign[i].id == 1)
		{
			if (Sign[i].value[0] == '~')
			{
				Sign[i].value = (char*)realloc(Sign[i].value, slen(Sign[i].value) + slen(dir) + 1);
				OverwritePath(Sign[i].value, dir);
			}
		}
/*		if (Sign[i].id == -1)
		{
			for (j = 0; j < Z; ++j)
			{
				if (Sign[j].line == Sign[i].line)
				{
					Sign[j].id = -1;
				}
			}
			
		}*/ //Убрать все в ошибочной строке. Очень грубо.
		
		
		// Более аккуратно:
		//path-у (1) должен предшествовать service&priority (0)
		if (Sign[i].id == 1)
		{
			// Пропускаем пробелы/разделители
			for (k = i - 1; (k >= 0)&&( (Sign[k].id == 3)||(Sign[k].id == 4) ); k--)
			{
				continue;
			}
			if ( (k >= 0)&&(Sign[k].id != 0) )
				Sign[i].id = -1;
		}
		
		//после service&priority (0) должен быть path (1)
		if (Sign[i].id == 0)
		{
			// Пропускаем пробелы/разделители
			for (k = i + 1; (k < Z)&&( (Sign[k].id == 3)||(Sign[k].id == 4) ); k++)
			{
				continue;
			}
			if ((k <= Z) && (Sign[k].id != 1))
				Sign[i].id = -1;
		}
	}
	return Z;
}
