/*
	Лабораторная работа предполагает выполнение задания первого или второго уровня
сложности. Если студент претендует на отличную оценку на экзамене по результатам работы в
семестре необходимо выбирать задание второго уровня сложности.
	Номер варианта выбирается в соответствии с номером студента в журнале преподавателя
(необходимо уточнить) по формуле (i – 1) mod n + 1, где i – номер студента по журналу, n –
количество заданий.

	При разработке подпрограмм в соответствии с заданием следует учитывать, что:
1. Необходимо использовать функции, созданные в рамках Лабораторной работы No 4
(ЛР No 4). Они должны быть расположены в отдельном файле с именем strings.c.
Необходимо также создать заголовочный файл strings.h, в котором разместить прототипы
всех функций из strings.c. Файл strings.h предназначен для связи других файлов с
исходными кодами программ с файлом strings.c.
2. Функции input() и output(), созданные в рамках ЛР No 4, должны быть
переработаны для работы с файлами. Функции работы с фалами должны быть размещены в
файле io.c/io.h. Выходные данные программ должны помещаться в файл:
a) для первого уровня сложности название файла задается с клавиатуры;
b) для заданий второго уровня сложности изменяется входной файл.
3. Функции по работе с форматами файлов также должны быть вынесены в отдельный
файл format.c/format.h.
4. В отчете о лабораторной работе должен присутствовать список тестовых входных
данных, на которых проверялась корректность работы программы, и полученные результаты.
Набор тестов должен обеспечивать проверку поведения программы для всех классов входных
данных.

II уровень сложности. Вариант 3
Входными данными для всех программ данного раздела является:
	1) имя файла с входными данными;
	2) содержимое этого файла;
	3) дополнительные данные, требуемые по заданию, вводятся с клавиатуры.
Выходные данные представляют собой модифицированный входной файл (результаты
обработки сохраняются в исходном файле).

	Выполнить обработку syslog.conf-файла. Проверить все селекторы на допустимость
значения полей служба и приоритет. Проверить допустимость IP адресов и доменных имен
удаленных узлов. К строкам, соответствующим действиям над информацией поступающей с
удаленных узлов, применить обработку согласно заданию ЛР No 4:
	Преобразовать все пути входного списка, заданные относительно домашних каталогов
указанных пользователей (вида ~alex/somedir), к абсолютным путям. Имя каталога (dir), в
котором находятся домашние каталоги пользователей, вводится с клавиатуры.
	Вход:
	delim: +
	dir: /home/stud
	paths: ~/games/packman.cpp+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc
	Выход:
	new paths: ~/games/packman.cpp+/home/stud/alex/docs+~/study/Prog/lab4.c +/usr/bin/gcc

*/

#include <stdio.h>
#include <stdlib.h>

#include "string.h"
#include "processing.h"
#include "input_output.h"

int main()
{
	char filepath[MAXPATH];
	char dir[MAXPATH] = "/home";
	char textfile[100000] = {"\0"};
	stu sign[1000];

	interrogation(filepath, dir);

	Read(filepath, textfile);
	int Z = process(textfile, dir, sign);
//	printf("%s", textfile);

	Write(filepath, sign, Z);
	return 0;
}
