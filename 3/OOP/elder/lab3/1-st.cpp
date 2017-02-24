#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include "point.h" 
main() {
    initwindow(800,600); // инициализируем графическое окно
    tpoint *pt[200]; // массив для 200 точек
    for (int i=0;i<200;i++) {
        pt[i]=new tpoint(800,600); // инициализируем кажду точку (вызываем для каздой конструктор)
    }
    while (1) { // бесконечный цикл
          for (int i=0;i<200;i++)
              pt[i]->move(); // двигаем каждую точку
    }
    closegraph(); // закрываем графическое окно
}
