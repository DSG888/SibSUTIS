#ifndef MEMORY_H
#define MEMORY_H

typedef unsigned char byte;

#include <stdlib.h>
#include <stdio.h>
#include "configuration.h"
#include "cpu.h"

enum tintype
{
	myINT16 = 16,	//положительное 16бит
	myINT15 = 15,	//
	myINT8 = 8,		//положительное 8бит
	myINT7 = 7		//
};

byte *Memory;

byte *sc_memoryInit(int size);
//void sc_memorySet(byte *mem, int addr, int value, int type);
int sc_memorySet(byte *mem, int addr, int value);
int sc_memoryGet(byte *mem, int addr, int *value);
int sc_memorySave(byte *mem, char *filename);
int sc_memoryLoad(byte *mem, char *filename);
void sc_regInit();
int sc_regSet(int reg, int value);
int sc_regGet (int reg,  int *value);
int sc_commandEncode (int command, int operand, int * value);// Не используется
int sc_commandDecode (int value, int * command, int * operand);// Не используется

#endif
