#include "terminal.h"

// производит очистку и перемещение курсора в левый верхний угол экрана;
void mt_clrscr ()
{
	printf("\E[H\E[2J");
	
}

// перемещает курсор в указанную позицию. Первый параметр номер строки, второй - номер столбца;
int mt_gotoXY (int x, int y)
{
	int rows, cols;

	mt_getscreensize(&rows, &cols);
	if ((y < rows) && (x < cols) && (x >= 0) && (y >= 0))
	{
		printf("\E[%d;%dH", y, x);
		return 0;
	}
	else
		return 1;
}

// определяет размер экрана терминала (количество строк и столбцов);
int mt_getscreensize (int *rows, int *cols)
{
	struct winsize w;

	if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &w))
	{
		*rows = w.ws_row;
		*cols = w.ws_col;
		return 0;
	}
	else
		return 1;
}

// устанавливает цвет последующих выводимых символов. В качестве параметра передаѐтся константа из созданного Вами перечислимого типа colors , описывающего цвета терминала;
int mt_setfgcolor (enum colors color)
{
	switch (color) {
		case cl_black:
			printf("\E[30m");
			break;
		case cl_red:
			printf("\E[31m");
			break;
		case cl_green:
			printf("\E[32m");
			break;
		case cl_brown:
			printf("\E[33m");
			break;	
		case cl_blue:
			printf("\E[34m");
			break;
		case cl_magenta:
			printf("\E[35m");
			break;
		case cl_cyan:
			printf("\E[36m");
			break;
		case cl_light_blue:
			printf("\E[37m");
			break;
		case cl_default:
			printf("\E[39m");
			break;
		default:
			return -1;
	}
	return 0;
}

// устанавливает цвет фона последующих выводимых символов. В качестве параметра передаѐтся константа из созданного Вами перечислимого типа colors , описывающего цвета терминала.
int mt_setbgcolor (enum colors color)
{
	switch (color) {
		case cl_black:
			printf("\E[40m");
			break;
		case cl_red:
			printf("\E[41m");
			break;
		case cl_green:
			printf("\E[42m");
			break;
		case cl_brown:
			printf("\E[43m");
			break;
		case cl_blue:
			printf("\E[44m");
			break;
		case cl_magenta:
			printf("\E[45m");
			break;
		case cl_cyan:
			printf("\E[46m");
			break;
		case cl_light_blue:
			printf("\E[47m");
			break;
		case cl_default:
			printf("\E[49m");
			break;
		default:
			return -1;
	}
	return 0;
}
