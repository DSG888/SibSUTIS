#include "edit.h"

int len (int lineno)
{
	int linelen = COLS - 1;
	while (linelen >= 0 && mvinch (lineno, linelen) == ' ')
	{
		linelen--;
		return linelen + 1;
	}
}

int findNoSpace(WINDOW *w, int li, int le)
{
	int i;
	for (i = 1; i < le; i++)
	{
		if (' ' != mvwinch(w, li, i))
			return 1;
	}
	return 0;
}

int save(WINDOW *wnd, char* str)
{
	int i, l, n;
	char buf[1];
	FILE *f = NULL;
	f = fopen("test.txt", "wt");	//fixme
	if (NULL == f)
	{
		perror("Файл не открывается\n");
		return 1;
	}
	for (l = 1; l < LINES - 4; ++l)
	{
		n = len(l);
		if (findNoSpace(wnd, l, n))
			for (i = 1; i < n; i++)
			{
				buf[0] = mvwinch(wnd, l, i);
				if (!(fwrite(buf, 1, 1, f)))
				{
					perror("Нет доступа на запись\n");
					return 1;
				}
			}
		buf[0] = '\n';
		fwrite(buf, 1, 1, f);
	}
	fclose(f);
	return 0;
}

void input(WINDOW *wnd)
{  
	int row = 1, col = 1, c;				
	curs_set (1);
	while (1)
	{  
		move (row,col);
		c = getch();
		switch (c) 
		{
			case KEY_LEFT:
				if (col > 1)
					col--;
				else
					flash ();
				break;
			case KEY_DOWN:
				if (row < LINES - 5)
					row++;
				else
					flash ();
				break;
			case KEY_UP:
				if (row > 1)
					row--;
				else
					flash ();
				break;
			case KEY_RIGHT:
				if (col < COLS - 2)
					col++;
				else
					flash ();
				break;
			case KEY_BACKSPACE:
				if (col > 1)
				{
					mvwprintw (wnd, row, --col, "%c", ' ');
					wrefresh (wnd);
				}
				else
					flash();			
				break;
				box (wnd, 0 , 0);
			case KEY_DL:
				deleteln();
				box (wnd, 0 , 0);
				break;
				
			case '\n':
				if (row < LINES - 5)
				{
					row++;
					col = 1;
				}
				else
					flash ();
				break;

			default:
				if (c == KEY_F(4))
				{
					refresh();
					return;
				}
				if(col < COLS - 1)
					mvwinsch(wnd, row, ++col - 1, c);
				else
				{
					col = 0;
					row++;
					mvwinsch(wnd, row, ++col, c);	 
				}	  
				box(wnd, 0, 0);
				wrefresh (wnd);
				break;
		}
	}
}

void sig_winch(int signo)
{
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	resizeterm(size.ws_row, size.ws_col);
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	wrefresh(local_win); 
	return local_win;
}

int myopen(WINDOW *my_win, WINDOW *wnd, char str[256])
{
	echo();
	int y = 1, x = 1, res;
	int ch;
	my_win = create_newwin(3, 50,((LINES - 3) / 2), ((COLS - 50) / 2));
	box(my_win, 0, 0); 
	mvwprintw(my_win, 1, 1, "tape directory:");
	wrefresh(my_win);
	move(((LINES - 3) / 2) + 1, ((COLS - 50) / 2) + 16);
//	if(argc != 0)
//		str=argv[1];
//	else
//		getstr(str);
	FILE* f;
	if((f = fopen(str, "r")) == NULL)
	{
		perror("Нет доступа к файлу");
		return 1;
	}
	werase(my_win); 
	wrefresh(my_win);
	while((ch = getc(f)) != EOF)
	{
		if (ch == '\n')
		{
			y++;
			x = 1;
			continue;
		}
		mvwprintw(wnd, y, x++, "%c", ch);
		wrefresh(wnd);
	}
	fclose(f);
	return 0;
}

void destroy_win(WINDOW *local_win)
{  
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}
