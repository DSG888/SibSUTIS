#ifndef MAIN_H
#define MAIN_H

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/mman.h>
#include <dirent.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/stat.h>

#define KEY_TAB 9

int ListLength;

typedef struct  
{
	char dir[255];
	char list[1000][800];
}DirList;

WINDOW *create_win(int, int, int, int);
void initdir(DirList*, DIR*, struct dirent*);
int View(WINDOW*, DirList*);
void UP(DirList*, DIR*, struct dirent*);
void Transition(DirList*,int, DIR*,struct dirent*);

#endif
