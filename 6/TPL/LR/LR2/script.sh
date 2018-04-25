#!/usr/bin/env bash

flex -o lab2.c lab2.l
gcc -o lab2 lab2.c -lfl
./lab2 text
rm lab2.c lab2
