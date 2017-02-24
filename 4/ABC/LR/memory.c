#include "memory.h"

byte *initmemory(int size)
{
	unsigned char *Mem = malloc(size * sizeof(unsigned char));
	int i;
	if (NULL != Mem)
		for (i = 0; i < size; ++i)
			Mem[i] = 0;
	return Mem;
}
