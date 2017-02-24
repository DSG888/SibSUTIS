#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

typedef unsigned char byte;

enum tintype
{
	myINT16 = 16,	//положительное 16бит
	myINT15 = 15,	//
	myINT8 = 8,		//положительное 8бит
	myINT7 = 7		//
};

byte *Memory;

byte *sc_memoryInit(int size);
void sc_memorySet(byte *mem, int addr, int value, int type);


#endif
