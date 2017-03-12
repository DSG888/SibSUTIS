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
/*
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
			//занимаем 2 байта маской
			}
			break;
		case myINT15:
			if ((32767 < value) || (-32768 > value))
			{
			//АшиПка!	
			}
			else
			{
			//занимаем 2 байта маской
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
}*/

int sc_memorySet(byte *mem, int addr, int value)
{
	if ((0 >= addr) || (MaxMemory < addr))
		return 1;
	else
	{
		mem[addr] = value;
		if (value == mem[addr])
			return 0;
		else
			return 2;
	}
}

int sc_memoryGet(byte *mem, int addr, int *value)
{
	if ((0 >= addr) || (MaxMemory < addr))
		return 1;
	*value = mem[addr];
	return 0;
}

int sc_memorySave(byte *mem, char *filename)
{
	FILE *save;
	int res;
	
	save = fopen(filename, "wb");
	if (NULL == save)
		return 1;
	res = fwrite(mem, sizeof(byte) * MaxMemory, 1, save);
	fclose(save);
	if (res != 1)
		return 2;
	else
		return 0;
}

int sc_memoryLoad(byte *mem, char *filename)
{
	FILE *save;
	int res, i;
	
	save = fopen(filename, "rb");
	if (save == NULL)
		return 1;
	res = fread(mem, sizeof(byte) * MaxMemory, 1, save);
	for (i = 0; i < MaxMemory; ++i)
		mem[i] &= 0x7FFF;
	fclose(save);
	if (res != 1)
		return 2;
	else
		return 0;
}

void sc_regInit()
{
	Flags.C = 0;
	Flags.E = 0;
	Flags.P = 0;
	Flags.V = 0;
	Flags.Z = 0;
}

int sc_regSet(int reg, int value)
{
	if (0 == value || 1 == value)
		if (FlagV == reg || FlagZ == reg || FlagE == reg || FlagP == reg || FlagC == reg)
		{
			//Flags = Flags && (value * 0xff) && reg;		//HACKME
			switch (reg)//FIXME
			{
				case FlagV:
					Flags.V = value;
					break;
				case FlagZ:
					Flags.Z = value;
					break;
				case FlagE:
					Flags.E = value;
					break;
				case FlagP:
					Flags.P = value;
					break;
				case FlagC:
					Flags.C = value;
					break;
			}
			return 0;
		}
		else
			return 2;
	else
		return 1;
}

int sc_regGet (int reg,  int *value)
{
	if (FlagV == reg || FlagZ == reg || FlagE == reg || FlagP == reg || FlagC == reg)
	{
		//Flags = Flags && (value * 0xff) && reg;		//HACKME
		switch (reg)//FIXME
		{
			case FlagV:
				*value = Flags.V;
				break;
			case FlagZ:
				*value = Flags.Z;
				break;
			case FlagE:
				*value = Flags.E;
				break;
			case FlagP:
				*value = Flags.P;
				break;
			case FlagC:
				*value = Flags.C;
				break;
		}
		return 0;
	}
	return 1;
}

int int_cmp(const void *a, const void *b)
{
	if (*(int*)a < *(int*)b)
		return -1;
	else
	if (*(int*)a > *(int*)b)
		return 1;
	else
		return 0;
}


const int correct_ops[] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40,
						   0x41, 0x42, 0x43, 0x59};
const int ops_num = 13;

int sc_commandEncode(int command, int operand, int *value)
{
	void *command_ptr;
	
	command_ptr = bsearch(&command, correct_ops, ops_num, sizeof(int), int_cmp);
	if (command_ptr != NULL)
	{
		*value = (command << 7) | operand;
		return 0;
	}
	else
		return 1;
}


int sc_commandDecode(int value, int *command, int *operand)
{
	void *correct_command;
	int attribute;
	int tmp_command, tmp_operand;
	
	attribute = (value >> 14) & 1;
	if (attribute == 0)
	{
		tmp_command = (value >> 7) & 0x7F;
		tmp_operand = value & 0x7F;
		correct_command = bsearch(&tmp_command, correct_ops, ops_num, sizeof(int), int_cmp);
		if (correct_command != NULL)
		{
			*command = tmp_command;
			*operand = tmp_operand;
		}
		else
			return 1;
	}
	else
		return 2;
	return 0;
}
