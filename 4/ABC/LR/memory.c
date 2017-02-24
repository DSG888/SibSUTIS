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

int power(int x, int n)
{
	double a = 1;
	while(n)
	{
		if(n % 2)
		{
			a *= x;
			n--;
		}
		else
		{
			x *= x;
			n /= 2;
		}
	}
	return a;
}

void sc_memorySet(byte *mem, int addr, int value, int type)
{
	if ((8 <= type ) && ((0 >= addr) || (MaxMemory < addr)))
	{}//exit
	if ((8 > type ) && ((0 >= addr) || (MaxMemory < addr + 1)))
	//mem[addr] = value;
	switch (type)
	{
		case myINT16:
			if ((65535 < value) || (0 > value))
			{
			//АшиПка!	
			}
			else
			{
			//занимаем 2 байта	
			}
			break;
		case myINT15:
			if ((32767 < value) || (-32768 > value))
			{
			//АшиПка!	
			}
			else
			{
			//занимаем 2 байта	
			}
			break;
		case myINT8:
			break;
			if ((255 < value) || (0 > value))
			{
			//АшиПка!	
			}
			else
			{
			//занимаем 1 байт
			}
		case myINT7:
			if ((127 < value) || (-128 > value))
			{
			//АшиПка!	
			}
			else
			{
			//занимаем 1 байт	
			}
			break;
	}
}
