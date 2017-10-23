#include "main.h"

key_t key;
int shmid;
void *shmem_segment = NULL;


void term(int signum)
{
    shmctl (shmid , IPC_RMID , NULL);
}

void sig_handler(int signo)
{
	switch (signo)
	{
		case SIGINT:
			printf("received SIGINT\n");	//FIXME
			break;
		case 
			SIGUSR1:
			printf("restart\n");	//FIXME
			break;
		case SIGTERM:
		case SIGQUIT:
		//	if (shmdt(shmem_segment) == -1)
		//	{
		//		perror("shmdt:");
		//		exit(EXIT_FAILURE);
		//	}
			shmctl (shmid , IPC_RMID , NULL);
			break;
	}
}



//WINDOW *create_win(int starty, int startx, int height, int width)
//{
//	WINDOW *wnd;
//	wnd = newwin(height, width, starty, startx);
//	box(wnd, 0, 0);
//	wrefresh(wnd);
//	return wnd;
//}


typedef struct raw_s {
	list_node *ptrpro;
	msg_node *ptrmsg;
} raw_t;


int main(int argc, char **argv)
{
	struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);
	
	if (signal(SIGUSR1, sig_handler) == SIG_ERR)
		perror("\ncan't catch SIGUSR1\n");
	if (signal(SIGTERM, sig_handler) == SIG_ERR)
		perror("\ncan't catch SIGUSR1\n");
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		perror("\ncan't catch SIGUSR1\n");
		
//	if (signal(SIGKILL, sig_handler) == SIG_ERR)
//		perror("\ncan't catch SIGUSR1\n");			// Не захватываетя

//	key = ftok(argv[0], PROJ_ID);
	
//	if ((shmem_segment = shmat(shmid, NULL, 0)) == (void *)-1)
//	{
		//Отлично, память еще не выделена. Нужно выделить
//		if ((shmid = shmget(key, SHMEM_SIZE, 0666 | IPC_CREAT)) < 0)
//		{
//			perror("shmget:");
//			exit(EXIT_FAILURE);
//		}
//		if ((shmem_segment = shmat(shmid, NULL, 0)) == (void *)-1)
//		{
			// Ну тогда совсем все плохо
//			perror("shmat:");
//			exit(EXIT_FAILURE);
//		}
//	}

	int ch;						// Буфер для символа из терминала
	char strline[87] = {'\0'};	// Строка набора текста
	int curpos = 0;
	int mypid = getpid();		// pid
	int first = 1;
	int num;

	if ((key = ftok("/etc/fstab", PROJ_ID)) == -1)
	{
		perror("Failed to make a key with file\n");
		exit(EXIT_FAILURE);
	}
	if ((shmid = shmget(key, SHMEM_SIZE, 0666 | IPC_CREAT | IPC_EXCL)) == -1)
	{
		// Возможно это 2е подключение
		if ((shmid = shmget(key, SHMEM_SIZE, 0666 | IPC_EXCL)) == -1)
		{
			perror("Failed to get a shared memory segment\n");
			exit(EXIT_FAILURE);
		}
		first = 0;
	}
	if ((shmem_segment = shmat(shmid, NULL, 0)) == (void *) -1)
	{
		perror("Failed to attach to our shared memory segment\n");
		exit(EXIT_FAILURE);
	}
	
	raw_t *raw = NULL;
	
	//list_node *lptr
	
	int rawsize = sizeof(raw_t);
	int listsize = sizeof(raw_t);
	if (first)
	{
		// Первое подключение
		raw = (raw_t *) shmalloc(shmid, &rawsize, shmem_segment, SHMEM_SIZE);
		
		raw->ptrpro = (list_node *) shmalloc(shmid, &listsize, shmem_segment, SHMEM_SIZE);
		
		if (raw==NULL)
		{
			perror("Failed to attach to our shared memory segment\n");
			exit(EXIT_FAILURE);
		}
		
	//	raw->ptrpro -> next = NULL;
	//	raw->ptrpro -> npid = mypid;
	//	raw->ptrpro -> num = 0;
		num = 0;
	}
	else
	{
//		list_node *tmpl;
//		int cou = 0;
//		for (tmpl = raw->ptrpro, ++cou; tmpl = tmpl->next; tmpl->next != NULL){}
		
//		tmpl = (list_node *) shmalloc(shmid, &listsize, shmem_segment, SHMEM_SIZE);
//		tmpl -> next = NULL;
//		tmpl -> npid = mypid;
//		tmpl -> num = cou;
//		num = cou;
	}

	

//	int lenR, lenL;
//	int cur_x = 1, cur_y = 1;
	// Подготовка интерфейса
	WINDOW *win_chat = newwin(0, 0, LINES - 3, COLS);
	WINDOW *win_line = newwin(LINES - 3, 0, 3, COLS);

	
	initscr();
	start_color();
	keypad(stdscr, TRUE);
	refresh();
	noecho();
	curs_set(1);

//	box(win_chat, 0, 0);
//	wrefresh(win_chat);
	

	win_chat = create_win(LINES - 3, COLS, 0, 0);
	win_line = create_win(3, COLS, LINES - 3, 0);
	
	wclear(win_chat);
	wclear(win_line);
	
	
	bool flag = FALSE;
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	init_pair(2, COLOR_BLUE, COLOR_CYAN);
	wbkgd(win_chat, COLOR_PAIR(1));
	wbkgd(win_line, COLOR_PAIR(2));
	
	box(win_chat, 0, 0);
	box(win_line, 0, 0);
	mvwprintw(win_chat, 0, 1, "PID: %d [%d]", mypid, num);
//	mvwprintw(win_chat, 2, 1, "arg[0]: %s", argv[0]);
	
	wrefresh(win_chat);
	wrefresh(win_line);
	move(22, 1);
	refresh();

//	printw("%d %d", LINES, COLS);	/* Print Hello World		  */
//	refresh();			/* Print it on to the real screen */
//	getch();	
	
	
//	initdir(&left, dir, entry);
//	initdir(&right, dir, entry);
//	lenR = View(win_chat, &right);
	int dbl_size = sizeof(list_node);
//	list_node *lptr = (double *) shmalloc(3, &dbl_size, shmem_segment, SHMEM_SIZE);
	
	
	while (1)
	{
		ch = getch();
		//wmove(win_line, 1, 1);
		
		switch (ch)
		{	

			case KEY_TAB:
				if (flag)
				{
					wbkgd(win_chat, COLOR_PAIR(1));
					wbkgd(win_line, COLOR_PAIR(2));
					flag = FALSE;
					wmove(win_line, 1, 1 + curpos);
					curs_set(1);
				}
				else
				{
					wbkgd(win_chat,COLOR_PAIR(2));
					wbkgd(win_line,COLOR_PAIR(1));
					flag = TRUE;
					curs_set(0);
				}
				break;
//			case KEY_UP:
//				if (flag)
//				{
//					
//				}
//				break;
//			case KEY_DOWN:
//				if (flag)
//				{
//					
//				}
//				break;
			case 'q':
				goto TERMINATE;
			case KEY_ENTER:
				if (!flag)
				{
					
				}	
				break;
			case KEY_BACKSPACE:
				if ( !flag && 0 < curpos)
				{
					strline[curpos] = '\0';
					mvwprintw(win_line, 1, curpos, " ");
					wmove(win_line, 1, curpos);
					--curpos;
				}
				break;
			default:
				if (!flag && isprint(ch) && 67 > curpos)
				{
					strline[curpos] = (char)ch;						
					mvwprintw(win_line, 1, 1 + curpos, "%c", strline[curpos]);
					wmove(win_line, 1, 2 + curpos);
					++curpos;
				}
				break;
		}
		wrefresh(win_chat);
		wrefresh(win_line);
	}
TERMINATE:
	delwin(win_chat);
	delwin(win_line);
	echo();	
	endwin();
	
//	mt_clrscr();	
//shmctl(shmid, 1, NULL);
		    if (shmdt(shmem_segment) == -1)
		    {
				perror("shmdt:");
				exit(EXIT_FAILURE);
			}
		
			shmctl(shmid, PROJ_ID, NULL);

	return EXIT_SUCCESS;
}
