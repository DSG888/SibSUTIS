#include<stdlib.h>
#include<time.h>

#define x_max Form1->Image1->Width
#define y_max Form1->Image1->Height


#define imj Image1->Canvas

struct colorRGB
{
 int R;
 int G;
 int B;
};

class tPoint
{
private:
	int cord_x,cord_y;
	int move_x,move_y;
        colorRGB color;
public:
	int set_cord(int,int);
	void print_point(void);
	void move_point_strait(void);
	void move_point_rand(void);
	tPoint();
};

tPoint::tPoint()
{
        
	int a=rand()%2;
	if(a==0)
		move_x=-1;
	else
		move_x=1;
	a=rand()%2;
	if(a==0)
		move_y=-1;
	else
		move_y=1;
	cord_x=0;
	cord_y=0;
        color.R=(rand()%255);
        color.G=(rand()%255);
        color.B=(rand()%255);

}

int tPoint::set_cord(int x,int y)
{
	
	if(x<0 || y<0 || x>x_max || y>y_max)
		return 1;
	cord_x=x;
	cord_y=y;
	return 0;
}

void tPoint::print_point(void)
{
       /*	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color );     

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 

	csbiInfo.dwCursorPosition.X = cord_x;
	csbiInfo.dwCursorPosition.Y = cord_y;

	SetConsoleCursorPosition(hConsole,csbiInfo.dwCursorPosition);
                                                     */
       //	std::cout << "*";

	return;
}


void tPoint::move_point_strait(void)
{
	

	if(cord_x+1>x_max)
		move_x=-1;
	if(cord_y+1>y_max)
		move_y=-1;

	if(cord_x-1<0)
		move_x=+1;
	if(cord_y-1<0)
		move_y=+1;
      /*
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 

	csbiInfo.dwCursorPosition.X = cord_x;
	csbiInfo.dwCursorPosition.Y = cord_y;

	SetConsoleCursorPosition(hConsole,csbiInfo.dwCursorPosition);
        */
      //	std::cout << " ";

	cord_x+=move_x;
	cord_y+=move_y;

	return;
}


void tPoint::move_point_rand(void)
{
	int m_x,m_y;

	int a=rand()%2;
	if(a==0)
		m_x=-1;
	else
		m_x=1;
	a=rand()%2;
	if(a==0)
		m_y=-1;
	else
		m_y=1;


	if(cord_x+1>x_max)
		m_x=-1;
	if(cord_y+1>y_max)
		m_y=-1;

	if(cord_x-1<0)
		m_x=+1;
	if(cord_y-1<0)
		m_y=+1;

    /*	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 

	csbiInfo.dwCursorPosition.X = cord_x;
	csbiInfo.dwCursorPosition.Y = cord_y;

	SetConsoleCursorPosition(hConsole,csbiInfo.dwCursorPosition);   */
       //	std::cout << " ";

	cord_x+=m_x;
	cord_y+=m_y;


	return;
}

