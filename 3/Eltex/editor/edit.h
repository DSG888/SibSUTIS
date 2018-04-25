#ifndef EDIT_H
#define EDIT_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <signal.h>
#include <sys/ioctl.h>


int save(WINDOW*, char*);
void input(WINDOW *wnd);
void sig_winch(int);
WINDOW *create_newwin(int , int , int , int );
int myopen(WINDOW *my_win, WINDOW *wnd, char str[256]);
void destroy_win(WINDOW *);


#endif
