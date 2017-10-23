#ifndef MAIN_H
#define MAIN_H

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/mman.h>
//#include <dirent.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <locale.h>
#include <ctype.h>
#include <sys/shm.h>
#include "llists.h"
#include "ipc.h"

//#include <errno.h>
//#include <fcntl.h>
//#include <pthread.h>
//#include <sys/mman.h>
//#include <ncurses.h>
//#include <unistd.h>
//#include <sys/stat.h>


#define KEY_TAB 9
#define SHMEM_SIZE 10000000
#define PROJ_ID 1001






WINDOW *create_win(int, int, int, int);
//void initdir(DirList*, DIR*, struct dirent*);
//int View(WINDOW*, DirList*);
//void UP(DirList*, DIR*, struct dirent*);
//void Transition(DirList*,int, DIR*,struct dirent*);

#endif
