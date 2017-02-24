#include "cpu.h"

uint16_t A = 0;
uint8_t IC = 0;
tFlags Flags = {0,0,0,0,0,0,0,0};

void loadbios(byte *mem)
{
	mem[0] = 10;
	mem[1] = 1;
	mem[2] = 11;
	mem[3] = 2;
	mem[4] = 20;
	mem[5] = 3;
	mem[6] = 30;
	mem[7] = 4;
	mem[8] = 31;
	mem[9] = 5;
	mem[10] = 32;
	mem[11] =  6;
	mem[11] = 33;
	mem[11] = 7;
}
