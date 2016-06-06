#!/bin/sh

# Использование: split_by_words.sh <text-file>

INFILE=$1
MINCHARS=4

#
# Выводим файл $INFILE | разбиваем поток строк на слова | удаляем из потока слова с длиной <= $MINCHARS |
#     преобразуем слова потока в нижний регистр | сортируем слова | удаляем повторяющиеся слова
#
cat $INFILE | tr -s '[[:punct:][:space:]]' '\n' | grep -E ".{$MINCHARS}" | sed 's/[[:upper:]]*/\L&/' | sort | uniq | shuf
