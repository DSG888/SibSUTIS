#include "main.h"

WINDOW *create_win(int starty, int startx, int height, int width)
{ 
	WINDOW *wnd;
	wnd = newwin(height, width, starty, startx);
	wbkgd(wnd, COLOR_PAIR(1));
	box(wnd, 0, 0);
	wrefresh(wnd); 
	return wnd;
}

int viewram(WINDOW *wnd, int pointer, int vector)
{
	switch (vector)
	{
		case 1:
			if (MaxMemory < (16 * (pointer + 1)))
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
	int RAMVPointer = 3;
	Memory = initmemory(MaxMemory);
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
	keypad(stdscr, TRUE);		
	refresh();
	noecho();
	
	curs_set(1);
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_BLUE, COLOR_CYAN);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	
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
	
	viewram(winRAM, 3, 0);
	wrefresh(winREG);
	wrefresh(winTerminal);
	wrefresh(winRAM);
	wrefresh(winProgram);
	refresh();
	
	move(1, 1);
	
	

	scanf("%d");
	
TERMINATE:
	free(Memory);
	delwin(winRAM);
	delwin(winREG);
	delwin(winTerminal);
//	refresh();
	endwin();
	return 0;
	

	
}
