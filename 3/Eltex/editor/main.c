#include "edit.h"

int main(int argc, char **argv)
{	 
	WINDOW *winMAIN;
	WINDOW *winWork;
	WINDOW *winMenu;
	int ch;	
	char str[256];				// Путь до файла
	initscr(); 
	keypad(stdscr, TRUE);	
	refresh();
	cbreak();
	noecho();
	curs_set(0);
	mvprintw (LINES - 2, 1, "F2 OPEN, F3 SAVE, F4 EDIT, F5 QUIT");
	winWork = create_newwin(LINES - 3, COLS, 0, 0);
	winMenu = create_newwin(3, COLS, LINES - 3, 0);
	box(winWork, 0 , 0);	 
	box(winMenu, 0 , 0); 
  	wrefresh(winWork);
	wrefresh(winMenu);  
	signal(SIGWINCH, sig_winch);
	// Открываем файл, если он задан
	if (argc == 2)
	{
		if (myopen(winMAIN, winWork, argv[1]))
		{
			delwin(winMenu);
			delwin(winWork);
			delwin(winMAIN);
			refresh();
			endwin();
			printf("Файла нет\n");
			exit(EXIT_SUCCESS);			
		}
		else
		{
			int i;
			for (i = 0; argv[1][i] != '\0'; i++)
			{
				str[0] = argv[1][i];
			}
			str[i + 1] = '\0';
		}
	}
	while((ch = getch()) != KEY_F(5))
	{	
		switch(ch)
		{
			case KEY_F(2):
				//TODO Спросить юзера
				myopen(winMAIN, winWork, str);
				break;
			case KEY_F(3):
				save(winWork, str);
				break;
			case KEY_F(4):
				input(winWork);
		}
		noecho();
		curs_set(0);
	}
	delwin(winMenu);
	delwin(winWork);
	delwin(winMAIN);
	refresh();
	endwin();
	exit(EXIT_SUCCESS);
}
