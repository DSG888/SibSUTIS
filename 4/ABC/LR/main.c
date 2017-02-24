#include "main.h"

static const char *sc[] = {"@","@","@","@","@","@","@","@","@","@","READ","WRITE","@","@","@","@","@","@","@","@","LOAD","STORE","@","@","@","@","@","@","@","@","ADD","SUB","DIVIDE","MUL","@","@","@","@","@","@","JUMP","JNEG","JZ","MUL","@","@","@","@","@","@","@","NOT","AND","OR","XOR","JNS","JC","JNC","JP","JNP","CHL","SHR","RCL","RCR","NEG","ADDC","SUBC","LOGLC","LOGRC","RCCL","RCCR","MOVA","MOVR","MOVCA","MOVCR","ADDC","SUBC"};


WINDOW *create_win(int starty, int startx, int height, int width)
{ 
	WINDOW *wnd;
	wnd = newwin(height, width, starty, startx);
	box(wnd, 0, 0);
	wrefresh(wnd); 
	return wnd;
}

void paintbox(WINDOW *wnd, int pair)
{
	wbkgd(wnd, COLOR_PAIR(pair));
	wrefresh(wnd); 
}

int viewram(WINDOW *wnd, int pointer, int vector)
{
	switch (vector)
	{
		case 1:
			if (MaxMemory <= (16 * (pointer + 1)))
				return pointer;
			++pointer;
		case 0:
			break;
		case -1:
			if (3 >= pointer)
				return pointer;
			--pointer;
			break;
		default:
			return pointer;
	}
	int i, j;
	for (i = 0; 3 >= i; ++i)
	{
		char str[80] = {'\0'};
		int oa = 16 * ((pointer) - (i));
		for (j = 0; 16 > j; ++j)
		{
			char buf[3] = {'\0'};
			sprintf(buf, "%02x ", Memory[j + oa]);
			strncat(str, buf, 3);
			if (j == 7)
				strncat(str, " ", 1);
		}
		strncat(str, " |  ", 4);
		for (j = 0; 16 > j; ++j)
			if (isprint(Memory[j + oa]))
			{
				char buf[1] = {'\0'};
				sprintf(buf, "%c", Memory[j + oa]);
				strncat(str, buf, 1);
			}
			else
				strncat(str, ".", 1);
		mvwprintw(wnd, (4 - i), 1, " %04X: %s", oa, str);
	}
	return pointer;
}

int viewprog(WINDOW *wnd, byte *mem, int pointer, int vector)
{
	char **bufa[5][17];

	pointer += vector * 2;
//mvwprintw(wnd, 0, 0, "%d     ", pointer );
//	pointer = 7;
//	mvwprintw(wnd, 1, 1, "%d", pointer );
	int i, is = -1;
//	int ip = 0;
	for (i = 0; i < 5; ++i)
	{
	//	printf("%p %p\n", );
		if (&(mem[pointer % 2 + i + pointer + i - 4]) < mem)
		{
			sprintf((char*)bufa[i], "                 ");
			if (&(mem[pointer % 2 + i + pointer + i - 4]) < mem -4)
				return pointer + vector * 2;
			if (pointer+80 > MaxMemory)
				pointer = 0;
				//FIXME нижнего предела нет
		}
		else
		{
			sprintf((char*)bufa[i], " %02x %02x: %s %x", mem[pointer % 2 + i + pointer + i - 4], mem[pointer % 2 + i + pointer + i + 1 - 4], sc[mem[pointer % 2 + i + pointer + i - 4]], mem[pointer % 2 + i + pointer + i + 1 - 4]);
			if ((pointer % 2 + i + pointer + i + 1 - 4-1) == IC)
				is = i+1;
		}
			 
	}
	
	for (i = 0; i < 5; ++i)
	{
		mvwprintw(wnd, 1 + i, 1, "                 " );
		mvwprintw(wnd, 1 + i, 1, (char *)bufa[i] );
		if (is == i)
		{
			mvwprintw(wnd, i, 1, "[");
			mvwprintw(wnd, i, 17, "]");
		}
	}
	
//	mvwprintw(wnd, 3, 1, "[");
//	mvwprintw(wnd, 3, 17, "]");
	return pointer;
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "");
	uint8_t RAMVPointer = 3;	// Позиция отображаемого участка памяти
	uint8_t PROVPointer = 0;
	int ActiveWindow = WIN_REG;	// Активное окно
	int EditMode = False;		// Режим редактора
	int cx, cy;					// Координаты курсора
	
	Memory = sc_memoryInit(MaxMemory);
	if (NULL == Memory)
	{
		perror("Память не выделена\n");
		goto TERMINATE;
	}
	

	
	
	WINDOW *winRAM;
	WINDOW *winREG;
	WINDOW *winTerminal;
	WINDOW *winProgram;
	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_BLUE, COLOR_CYAN);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	keypad(stdscr, TRUE);		
	refresh();
	noecho();
	
	//curs_set(1);
	curs_set(0);//FIXME
	
	winREG = create_win(0, 0, 11, 15);
	winTerminal = create_win(0, 15, 11, 65);
	winRAM = create_win(18, 0, 6, 80);
	winProgram = create_win(11, 0, 7, 19);
	
	mvwprintw(winREG, 0, 1, "РЕГИСТРЫ");
	mvwprintw(winTerminal, 0, 1, "ТЕРМИНАЛ");
	mvwprintw(winRAM, 0, 1, "ПАМЯТЬ");
	mvwprintw(winProgram, 0, 1, "ПРОГРАММА");
	
	wbkgd(winREG, COLOR_PAIR(3));
	wbkgd(winTerminal, COLOR_PAIR(3));
	
	mvwprintw(winREG, 1, 1, "A:     0x0000");
	mvwprintw(winREG, 2, 1, "IC:      0x00");
//	mvwprintw(winREG, 3, 1, " FLAGS: 0x00");
//	mvwprintw(winREG, 4, 1, " V Z E P C");
//	mvwprintw(winREG, 5, 1, " 0 0 0 0 0");
	mvwprintw(winREG, 3, 1, "F: 0b00000000");
	mvwprintw(winREG, 4, 1, "        VZEPC");

	
	loadbios(Memory);
	viewprog(winProgram, Memory, 0, 0);
	
	
	
	//sc_memorySet(Memory, 17, 5);
	
	
//	sc_memorySave(Memory, (char*)"caca");
	sc_memoryLoad(Memory, (char*)"caca");
	
	viewram(winRAM, RAMVPointer, 0);//fixme
	
	wrefresh(winREG);
	wrefresh(winTerminal);
	wrefresh(winRAM);
	wrefresh(winProgram);
	refresh();

	move(1, 1);
	paintbox(winREG, 1);
	
	int ch;
	while (1)
	{
		ch = getch();
		switch (ActiveWindow)
		{
			case WIN_MEM:
			{
				if (ch == KEY_F(3))
				{
					if (EditMode)
					{
						EditMode = False;
						curs_set(0);
					}
					else
					{
						EditMode = True;
						curs_set(1);
						move(19, 8);
						cx = 8;
						cy = 1;
					}
				}
				if (!(EditMode))
				{
					switch (ch)
					{
						case KEY_DOWN:
							RAMVPointer = viewram(winRAM, RAMVPointer, 1);
							wrefresh(winRAM);
							break;
						case KEY_UP:
							RAMVPointer = viewram(winRAM, RAMVPointer, -1);
							wrefresh(winRAM);
							break;
						case KEY_TAB:
							//goto TERMINATE;
							ActiveWindow = WIN_REG;
							paintbox(winRAM, 3);
							paintbox(winREG, 1);
							ActiveWindow = WIN_REG;
							break;
					}
				}
				else
				{
					int dig = 0, t;
					switch (ch)
					{
						// MAXIMUM MAGIC!
						case 'a' ... 'f':				//case 97 ... 102:
							dig -= 'a' - 'A';			//	dig -= 32;
						case 'A' ... 'F':				//case 65 ... 70:
							--dig;
						case '0' ... '9':				//case 48 ... 57:
							dig += ch - '0';			//	dig += ch - 48
							if ('9' < ch)				//	if (57 < ch)
								dig -= 1 + 'f' - 'a';	//		dig -= 6;
						if (cx < 31)
							t = (cx - 8) % 3;
						else
							t = ((cx - 8) % 3) - 1;	
						Memory[16 * (RAMVPointer - (4 - cy)) + ((cx - 8) / 3)] = ((dig * 0x10 | (Memory[16 * (RAMVPointer - (4 - cy)) + ((cx - 8) / 3)] & 0x0f)) & (!t * 0xff)) + ((dig | (Memory[16 * (RAMVPointer - (4 - cy)) + ((cx - 8) / 3)] & 0xf0)) & (t * 0xff));
						viewram(winRAM, RAMVPointer, 0);
						case KEY_RIGHT:
						{
							if (cx < 31)
							{
								if (cx % 3)
									++cx;
								else
									cx += 2;
								if (cx == 32)
									++cx;
							}
							else
							{
								if (cx % 3)
									cx += 2;
								else
									++cx;
							}
							wmove(winRAM, cy, cx);
							wrefresh (winRAM);//fixme
							if (cx < 57)
								break;
							else
								cx = 8;//FIXME В самом конце
						}
						case KEY_DOWN:
						{
							if (cy > 3)
								RAMVPointer = viewram(winRAM, RAMVPointer, 1);
							else
								++cy;
							wmove(winRAM, cy, cx);
							wrefresh (winRAM);//fixme
						}
						break;
						case KEY_LEFT:
						{
							if (cx > 31)
							{
								if (cx % 3)
									--cx;
								else
									cx -= 2;
								if (cx == 31)
									--cx;
							}
							else
							{
								if (cx % 3)
									cx -= 2;
								else
									--cx;
							}
							wmove(winRAM, cy,cx);
							wrefresh (winRAM);//fixme
							if (cx > 7)
								break;
							else
								if (RAMVPointer == 3)
									cx = 8;
								else
									cx = 55;
						}
						case KEY_UP:
						{
							if (cy <= 1)
								RAMVPointer = viewram(winRAM, RAMVPointer, -1);
							else
								--cy;
							wmove(winRAM, cy, cx);
							wrefresh (winRAM);//fixme
						}
						break;
					}
				}
			}
			break;
			case WIN_PRO:
			{
				
				switch (ch)
				{
					case KEY_UP:
						PROVPointer = viewprog(winProgram, Memory, PROVPointer, -1);
						wrefresh(winProgram);
						break;
					case KEY_DOWN:
						PROVPointer = viewprog(winProgram, Memory, PROVPointer, 1);
						wrefresh(winProgram);
						break;
					case KEY_TAB://FIXME смена активного окна
						//goto TERMINATE;
						ActiveWindow = WIN_MEM;
						paintbox(winProgram, 3);
						paintbox(winRAM, 1);
						ActiveWindow = WIN_MEM;
						break;
				}
			}
			break;
			case WIN_REG:
			{
				switch (ch)
				{
					case KEY_TAB:
					paintbox(winREG, 3);
					paintbox(winTerminal, 1);
					ActiveWindow = WIN_TER;
					break;
				}
			}
			break;

			case WIN_TER:
			{
				switch (ch)
				{
					case KEY_TAB:
					paintbox(winTerminal, 3);
					paintbox(winProgram, 1);
					ActiveWindow = WIN_PRO;
					break;
				}
			}
			break;
			
			
			
		}
	}
	
	
TERMINATE:
	free(Memory);
	delwin(winRAM);
	delwin(winREG);
	delwin(winTerminal);
//	refresh();
	endwin();
//	sc_regSet(4,1);
//	sc_regSet(1,1);
//	printf("%d\n", Flags);
	
	return 0;
}
