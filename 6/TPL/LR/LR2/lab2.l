/*
	1) написать программу, которая выполняет лексический анализ входного текста в
	соответствии с заданием и порождает таблицу лексем с указанием их типов. Программа
	должна выдавать сообщения о наличии во входном тексте ошибок, которые могут быть
	обнаружены на этапе лексического анализа;
	2) в качестве вспомогательного средства для генерации кода лексического анализатора
	использовать Flex.
	
	Вариант 3:
	Входной язык содержит операторы условия if ... then ... else и if ... then, разделённые
	символом ; (точка с запятой). Операторы условия содержат идентификаторы, знаки
	сравнения <, >, =, шестнадцатеричные числа, знак присваивания (:=). Шестнадцатеричными
	числами считать последовательность цифр и символов a, b, c, d, e, f, начинающуюся с цифры
	(например, 89, 45ac, 0abc).	
*/

%option yylineno
%{
#include <stdio.h>

int ch;
%}

digit[0-9a-f]
letter[a-zA-Z]
delim[();]
oper[*+/-=]
ws[ \t\n]

%%

if {
   printf("KEYWORD (%d, %d): %s\n", yylineno, ch, yytext);
   ch += yyleng;
}

else {
   printf("KEYWORD (%d, %d): %s\n", yylineno, ch, yytext);
   ch += yyleng;
}

then {
   printf("KEYWORD (%d, %d): %s\n", yylineno, ch, yytext);
   ch += yyleng;
}

[-+]?({digit}+) {
   printf("NUMBER (%d, %d): %s\n", yylineno, ch, yytext);
   ch += yyleng;
}

("_"|{letter})("_"|{letter}|{digit})* {
   printf("IDENTIFIER (%d, %d): %s\n", yylineno, ch, yytext);
   ch += yyleng;
}

{oper} { printf("OPERATION (%d, %d): %s\n", yylineno, ch, yytext);
   ch += yyleng;
}

":=" { printf("OPERATION (%d, %d): %s\n", yylineno, ch, yytext);
   ch += yyleng;
}

{delim} { printf("DELIMITER (%d, %d): %s\n", yylineno, ch, yytext);
   ch += yyleng;
}

{ws}+ {ch += yyleng; }
. { printf("Unknown character (%d, %d): %s\n", yylineno, ch, yytext);
   ch += yyleng;
}

%%

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("\nNot enough arguments. Please specify filename.\n");
        return -1;
    }
    if ((yyin = fopen(argv[1], "r")) == NULL) {
        printf("\nCannon open file %s.\n", argv[1]);
        return -1;
    }
    ch = 1;
    yylineno = 1;
    yylex();
    fclose(yyin);
    return 0;
}
