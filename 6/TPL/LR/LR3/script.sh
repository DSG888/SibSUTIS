#!/usr/bin/env bash

flex -o lab3.c lab3.l
gcc -o lab3 lab3.c hashTable.c -lfl
./lab3 text1
rm lab3.c lab3
