/*
	Добавить в программу, разработанную в лабораторной работе No2, функции
	формирования таблицы идентификаторов и поиска в ней по заданному методу. Для студентов с
	четными номерами по журналу – метод цепочек, с нечетными – открытая адресация.
	Вариант 3
*/

%option yylineno
%{
#include <stdio.h>
#include <stdlib.h>
#include "hashTable.h"

int ch;
hashTable* myTable;
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
   ht_insert(myTable, yytext, "Identifier");
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

    myTable = allocateNewTable();
    
    if ((yyin = fopen(argv[1], "r")) == NULL) {
        printf("\nCannon open file %s.\n", argv[1]);
        return -1;
    }
    ch = 1;
    yylineno = 1;
    yylex();
    print_ht(myTable);	

    fclose(yyin);
    deleteHashTable(myTable);
    return 0;
}
