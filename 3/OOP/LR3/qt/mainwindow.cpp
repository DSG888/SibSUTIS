#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QObject>
#include <QTime>
#include <iostream>
#include <unistd.h>

#include "myvector.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    timer = new QTimer;
    //Связываем сигнал переполнения таймера со слотом
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timer_overflow()));
    //Задаем время срабатывания таймера (в мс)
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}



class mypoint: public QObject
{
    protected:
        int x,y;    //Расположение
        int r,g,b;  //Цвет
        int l;
        QPainter *painter;

        void drawpoint()
        {
            painter->setPen(QPen(QColor(r, g, b), l));
            painter->drawPoint(x, y);
        }



    public:
        mypoint(QPainter *uPainter, int uX = 0, int uY = 0, int uR = 0, int uG = 0, int uB = 0, int uL = 0) //Констурктор
        {
            x = uX;
            y = uY;
            r = uR;
            g = uG;
            b = uB;
            l = uL;
            painter = uPainter;
            drawpoint();
            std::cout << "Была создана точка в кординатах " << x << "x" << y << "." << std::endl;
        }

        ~mypoint() //Деструктор
        {
            r = 255;
            g = 255;
            b = 255;
            drawpoint();
            std::cout << "Была удалена точка в кординатах " << x << "x" << y << "." << std::endl;
        }

        void refresh()
        {
            drawpoint();
        }

        void moveto(int uX = 0, int uY = 0)
        {
            if ((uX != x) && (uY != y))
            {
                int tmpR = r, tmpG = g, tmpB = b;
                r=255;
                g=255;
                b = 255;
                drawpoint();
                r = tmpR;
                g = tmpG;
                b = tmpB;
                x = uX;
                y = uX;
                drawpoint();
                std::cout << "Точка была перемещена в " << x << "x" << y << std::endl;
            }
        }
};

/*
class movePoint: public mypoint
{
    public:
        movePoint(QPainter *uPainter, int uX = 0, int uY = 0, int uR = 0, int uG = 0, int uB = 0, int uL = 0):
            mypoint(uPainter, uX, uY, uR, uG, uB,  uL)
        {}
        //movePoint(QPainter *uPainter, int uX = 0, int uY = 0, int uR = 0, int uG = 0, int uB = 0, int uL = 0) //Констурктор

        void MoveTo(int uX = 0, int uY = 0)
        {
            if ((uX != x) && (uY != y))
            {
                int tmpR = r, tmpG = g, tmpB = b;
                drawpoint();
                r = tmpR;
                g = tmpG;
                b = tmpB;
                x = uX;
                y = uX;
                drawpoint();
            }
        }
};
*/

class line
{
    protected:
        QPainter *painter;
        myVector <mypoint*> points;
        int l;
    private:
        int r, g, b;
        int nX, nY, kX, kY;

        int distance(double oldx, double oldy, double newx, double newy)
        // Число точек для создания линии
        {
            //int distance(double d_x1, double d_x2, double d_y1, double d_y2)
            // return (int)sqrt(pow(d_x2 - d_x1,2)+pow(d_y2 - d_y1,2));
            int count = 0;
            double x2 = newx;
            double y2 = newy;
            if (fabs(y2 - oldy) > fabs(x2 - oldx))
                for (newy = oldy; newy != y2; newy += (y2 - oldy < 0)?-1:1, count++);

            else
                for (newx = oldx; newx != x2; newx += (x2 - oldx < 0)?-1:1, count++);
            if (count)
                count++;
            return count;
       }


    public:
        line(QPainter *uPainter, double x1, double y1, double x2, double y2, int uR, int uG, int uB, int uL)
        {
            nX = (int)x1;
            nY = (int)y1;
            kX = (int)x2;
            kY = (int)y2;
            r = uR;
            g = uG;
            b = uB;
            l = uL;
            double rx = x1;
            double ry = y1;
            double tmpx = x2;
            double tmpy = y2;
            double dy = tmpy - ry;
            double dx = tmpx - rx;
            painter = uPainter;

            if (fabs(dy) > fabs(dx))
            {
//                for (y2 = ry; y2 != tmpy; y2 += Sign(dy))
                for (y2 = ry; y2 != tmpy; y2 += (dy < 0)?-1:1)

                {
                    x2 = rx + (y2 - ry) * dx / dy;
                    points.push_back(new mypoint(uPainter, int(y2), int(x2), r, g, b, l ));
                    //painter->drawPoint((int)y,(int)x);
                }
            }
            else
            {
                for (x2 = rx; x2 != tmpx; x2 += (dx < 0)?-1:1)
//                for (x2 = rx; x2 != tmpx; x2 += Sign(dx))
                {
                    y2 = ry + (x2 - rx) * dy / dx;
                    points.push_back(new mypoint(uPainter, int(y2), int(x2), r, g, b, l ));
                    //painter->drawPoint((int)y,(int)x);
                }
            }
            points.push_back(new mypoint(uPainter, int(tmpy), int(tmpx), r, g, b, l));
            //painter->drawPoint((int)tmpy,(int)tmpx);
            std::cout << "Была создана линия в кординатах [" << x1 << "x" << y1 << ":" << tmpx << "x" << tmpy << "]." << std::endl;
        }

        ~line() //Деструктор
        {
            int i = points.size();
            for (; i > 0; i--)
            {
                points.pop_back();
            }
        }

        void moveto(int x1, int y1, int x2, int y2)
        {
            int newd = distance(x1, y1, x2, y2);
        //    int oldd = points.size();
            while (newd != (int)points.size())
            {
                if (newd > (int)points.size())
                {
                    points.push_back(new mypoint(painter, -1, -1, 255,255,255, 1));
                }
                else
                {
                    points.pop_back();
                  //  delete *tmp;
                }
            }
            int counter = 0;


            nX = (int)x1;
            nY = (int)y1;
            kX = (int)x2;
            kY = (int)y2;
            double rx = x1;
            double ry = y1;
            double tmpx = x2;
            double tmpy = y2;
            double dy = tmpy - ry;
            double dx = tmpx - rx;

            if (fabs(dy) > fabs(dx))
            {
                for (y2 = ry; y2 != tmpy; y2 += (dy < 0)?-1:1)

                {
                    x2 = rx + (y2 - ry) * dx / dy;
                    //points.push_back(new mypoint(uPainter, int(y2), int(x2), 255,0,255, 2 ));
                    points[counter]->moveto(int(y2), int(x2));
                    counter++;
                }
            }
            else
            {
                for (x2 = rx; x2 != tmpx; x2 += (dx < 0)?-1:1)
                {
                    y2 = ry + (x2 - rx) * dy / dx;
                    //points.push_back(new mypoint(uPainter, int(y2), int(x2), 255,0,255, 2 ));
                    points[counter]->moveto(int(y2), int(x2));
                    counter++;
                }
            }
            //points.push_back(new mypoint(uPainter, int(tmpy), int(tmpx), 255,0,255, 2 ));
            points[counter]->moveto(int(tmpy), int(tmpx));
            std::cout << "Была создана линия в кординатах [" << x1 << "x" << y1 << ":" << tmpx << "x" << tmpy << "]." << std::endl;






        }



};


class circle
{

    protected:
        QPainter *painter;
    public:
        circle(QPainter *uPainter, int x, int y, int r)
        {
            painter = uPainter;
            QPen penHLines(QColor(0,0,0), 3);
            painter->setPen(penHLines);
            double dn = 1/(double)(r);
            double n = 0;
            while (n < 2 * 3.141592653589793238462643383279502)
            {
                painter->drawPoint((int)(x + r*cos(n)),(int)(y + r*sin(n)));
                n += dn;
            }
        }
};

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    QPainter *cq = &p;

    QPen penHLines(QColor(255,0,0), 3);
    p.setPen(penHLines);

    p.fillRect(0,0,4000,4000, QColor(255,255,255)); //Фон

    mypoint *rew = new mypoint (cq, 200,200,255,0,0,5);
//    movePoint *reg = new movePoint(cq, 200,200,255,0,0,5);

    line *azaza = new line(cq, 50, 50, 70, 70, 255, 64, 0, 2);
    azaza->moveto(10,10,220,220);

    circle zxcv(cq, 100,100,80);
}


//Следующий метод (слот) вызывется при каждом переполнении таймера
void MainWindow::timer_overflow()
{
    //Обновляем значение времени на форме
   // ui->label->setText(QTime::currentTime().toString());
}
