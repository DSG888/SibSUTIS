#include "main.h"




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


int main(int argc, char **argv)
{
	setlocale(LC_ALL, "");
	int RAMVPointer = 3;		// Позиция отображаемого участка памяти
	int ActiveWindow = WIN_MEM;	// Активное окно
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
	
	mvwprintw(winREG, 1, 1, " A: FF");
	mvwprintw(winREG, 2, 1, " IC: FF");
	mvwprintw(winREG, 3, 1, " FLAGS: FF");
	mvwprintw(winProgram, 1, 1, " 87 50: LOGRC 70");
	
	viewram(winRAM, RAMVPointer, 0);//fixme
	wrefresh(winREG);
	wrefresh(winTerminal);
	wrefresh(winRAM);
	wrefresh(winProgram);
	refresh();

	move(1, 1);
	paintbox(winRAM, 1);
	
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
						case KEY_TAB://FIXME смена активного окна
							goto TERMINATE;
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
							wrefresh (winRAM);
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
							wrefresh (winRAM);
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
							wrefresh (winRAM);
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
							wrefresh (winRAM);
						}
						break;
					}
				}
			}
			break;
			case WIN_PRO:
			{
				
			}
			break;
			case WIN_REG:
			{
			
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
	return 0;
}
