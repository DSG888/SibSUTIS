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

void initdir(DirList *full, DIR* dir, struct dirent *entry)
{	
	dir = opendir(full->dir);
	int i;
	static int *c_ptr = &ListLength;
	chdir(full->dir);
	i = 0;
	while ((entry = readdir(dir)) != NULL)
		sprintf(full->list[i++], "%s", entry->d_name);
	*c_ptr = i;
}

int View(WINDOW* wnd, DirList *full)
{	
	int x = 1, i = 0;
	static int *c_ptr = &ListLength;
	wclear(wnd);
	mvwprintw(wnd, 30, 30, "%d", *c_ptr);
	box(wnd, 0, 0);
	while ((x < LINES - 4) && (i < *c_ptr))
		mvwprintw(wnd, x++, 1, "%s", full->list[i++]); 	
	wrefresh(wnd);
	return i;
}

void Transition(DirList *full,int x, DIR* dir,struct dirent *entry)
{	
	int i;
	static int *c_ptr = &ListLength;
	struct stat buff;
	stat(full->list[x - 1], &buff);
	switch(buff.st_mode & S_IFMT)
	{
		case S_IFDIR:
			dir = opendir(full->dir);
			chdir(full->list[x - 1]);
			getcwd(full->dir, 100);
			dir = opendir(full->dir);
			i = 0;
			while ((entry = readdir(dir)) != NULL)
				sprintf(full->list[i++], "%s", entry->d_name);
			*c_ptr = i;
			closedir(dir);
			break;
	}
}

void UP(DirList *full, DIR* dir, struct dirent *entry)
{	
	int i;
	static int *c_ptr = &ListLength;
	chdir("..");
	getcwd(full->dir, 100);
	dir = opendir(full->dir);
	i = 0;
	while ((entry = readdir(dir)) != NULL)
		sprintf(full->list[i++], "%s", entry->d_name);
	*c_ptr = i;
}
