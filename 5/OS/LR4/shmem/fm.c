#include "main.h"

WINDOW *create_win(int height, int width, int starty, int startx)
{ 
	WINDOW *wnd;
	wnd = newwin(height, width, starty, startx);
	wbkgd(wnd, COLOR_PAIR(1));
	box(wnd, 0, 0);
	wrefresh(wnd); 
	return wnd;
}


