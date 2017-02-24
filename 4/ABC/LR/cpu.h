#ifndef CPU_H
#define CPU_H

//Регистр флагов содержит 5 разрядов: 






//Счетчик команд

struct _rflags {
	unsigned F1 : 1;
	unsigned F2 : 1;
	unsigned V : 1;		//переполнение при выполнении операции
	unsigned Z : 1;		//ошибка деления на 0
	unsigned E : 1;		//ошибка выхода за границы памяти
	unsigned P : 1;		//игнорирование тактовых импульсов
	unsigned C : 1;		//указана неверная команда
} Flags;

#endif
