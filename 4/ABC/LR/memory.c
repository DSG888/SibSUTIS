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
