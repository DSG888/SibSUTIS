#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#include "memory.h"

typedef struct {	//Регистр флагов содержит 5 разрядов:
	unsigned V : 1;		//переполнение при выполнении операции
	unsigned Z : 1;		//ошибка деления на 0
	unsigned E : 1;		//ошибка выхода за границы памяти
	unsigned P : 1;		//игнорирование тактовых импульсов
	unsigned C : 1;		//указана неверная команда
	unsigned F1 : 1;	//ЗАРЕЗЕРВИРОВАНО
	unsigned F2 : 1;	//ЗАРЕЗЕРВИРОВАНО
	unsigned F3 : 1;	//ЗАРЕЗЕРВИРОВАНО
} tFlags;

uint16_t A;	//Аккумулятор
uint8_t IC;	//Счетчик команд
tFlags Flags;

//0x07c0

void loadbios(byte * mem);

#endif
