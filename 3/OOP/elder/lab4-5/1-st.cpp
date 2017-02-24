#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include "E:\Рабочий стол\Учеба\ООП\lab4-5\figure.h" // путь к нашему модулю
const 
     int w=800, h=600;      // константы для высоты и ширины поля                          
main() {
    initwindow(w,h); // инициализация графического окна
    tfigure *fig[50]; // массив для фигур
    for (int i= 0;i<20;i++) fig[i]=new tpoint(w,h); // 20 точек
    for (int i=20;i<25;i++) fig[i]=new tline(w,h);  // 5 линий
    for (int i=25;i<30;i++) fig[i]=new tcircle(w,h); // 5 кругов
    for (int i=30;i<35;i++) fig[i]=new trectangle(w,h);  // 5 прямоугольников
    for (int i=35;i<40;i++) fig[i]=new trhomb(w,h); // 5 ромбов
    for (int i=40;i<45;i++) fig[i]=new ttriangle(w,h);  // 5 треугольников
    for (int i=45;i<50;i++) fig[i]=new tellipse(w,h); // 5 эллипсов

    while (1) {
          for (int i=0;i<50;i++) fig[i]->move(); // двигаем фигуры
    }
    closegraph();
}
