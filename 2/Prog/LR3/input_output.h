#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdio.h>
#include "processing.h"

void interrogation(char *path, char *dir);
void Read(char *fname, char *textfile);
void Write(char *fname, stu *sign, int count);
void WriteCLS(stu *sign, int count);

#endif
