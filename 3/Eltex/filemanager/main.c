#include "main.h"

int main()
{
	int lenR, lenL;
	int x = 1, y = 1;
	WINDOW *right_wnd;
	WINDOW *left_wnd;
	WINDOW *sub_wnd;
	DirList right;
	DirList left;
	sprintf(right.dir, "%s", ".");
	sprintf(left.dir, "%s", ".");
	bool flag = TRUE;
	int ch;

	DIR *dir = NULL;
	struct dirent *entry = NULL;
	initscr();
	start_color();
	keypad(stdscr, TRUE);		
	refresh();
	noecho();
	curs_set(1);
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	init_pair(2, COLOR_BLUE, COLOR_CYAN);
	right_wnd = create_win(LINES - 3, COLS / 2, 0, 0);
	left_wnd = create_win(LINES - 3, COLS / 2, 0, COLS / 2);
	sub_wnd = create_win(3, COLS, LINES - 3, 0);
	mvwprintw(sub_wnd, 1, 1,"TAB | > | < | v | ^");
	wrefresh(sub_wnd);
	move(1, 1);
	wbkgd(right_wnd, COLOR_PAIR(2));
	initdir(&left, dir, entry);
	lenL = View(left_wnd, &left);
	initdir(&right, dir, entry);
	lenR = View(right_wnd, &right);
	
	while (1)
	{
		ch = getch();
		switch (ch) 
		{	
			case KEY_TAB:
				if (flag)
				{	
					x = 1;
					y = COLS / 2 + 1;
					wbkgd(left_wnd, COLOR_PAIR(2));
					wbkgd(right_wnd, COLOR_PAIR(1));	
					flag = FALSE;
				}
				else
				{	
					x = 1;
					y = 1;
					wbkgd(right_wnd,COLOR_PAIR(2));
					wbkgd(left_wnd,COLOR_PAIR(1));	
					flag = TRUE;
				}
				break;
			case KEY_DOWN:
				if (x < LINES - 4)
				{
					if (flag)
					{
						if (x < lenR)
							x++;
					}
					else
					{
						if (x < lenL)
							x++;
					}
				}
				break;
			case KEY_UP:
				if (x > 1)
					x--;
				break;
			case KEY_RIGHT:
				if (flag == TRUE)
				{
					Transition(&right,x,dir, entry);
					lenR = View(right_wnd, &right);
					x = 1;
					y = 1;
				}
				else 
				{
					Transition(&left,x,dir, entry);
					lenL = View(left_wnd, &left);
					x = 1;
					y = COLS / 2 + 1;
				}
				break;
			case KEY_LEFT:
				if (flag)
				{	
					UP(&right, dir, entry);
					lenR = View(right_wnd, &right);
					x = 1;
					y = 1;
				}
				else
				{	
					UP(&left, dir, entry);
					lenL = View(left_wnd, &left);
					x = 1;
					y = COLS / 2 + 1;
				}
				break;
		}
		move(x,y);
		wrefresh(left_wnd);
		wrefresh(right_wnd);
	}	
	delwin(right_wnd);
	delwin(left_wnd);
	delwin(sub_wnd);
	echo();	
	endwin();
	closedir(dir);
	return 0;
}
