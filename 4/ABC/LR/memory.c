#include "memory.h"

byte *sc_memoryInit(int size)
{
	byte *Mem = malloc(size * sizeof(byte));
	int i;
	if (NULL != Mem)
		for (i = 0; i < size; ++i)
			Mem[i] = 0;
	return Mem;
}

void sc_memorySet(byte *mem, int addr, int value, int type)
{
	mem[addr] = value;
	switch (type)
	{
		case myINT16:
		
			break;
		case myINT15:
		
			break;
		case myINT8:
			break;
			
		case myINT7:
		
			break;
	}
}
