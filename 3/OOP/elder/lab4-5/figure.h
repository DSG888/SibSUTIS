//--------------------------------------ОБЪЯВЛЕНИЕ КЛАССОВ--------------------------
class tfigure { // общий класс для фигур
      protected: // поля для самого класса и дочерних
       int dx,dy; // приращение
       int color; //цвет
       int width, height;      // высота ширина поля
      public: // поля для всех
       tfigure(int, int); // конструктор
       virtual void move() {}; // метод движения
};
class tpoint: public tfigure { // класс точки наследуется от класса фигуры
      protected:
       int x,y;     // координаты
      public:
       tpoint(int, int); // коструктор
       virtual void move(); // движение
};
class tline: public tpoint { // линия наследуется от точки
      protected:
       int x1,y1; // первая координата отрезка наследуетсяот точки, вторая обьявляется тут
       int typemove;   // тип движения
       float time,length;  // время и длинна отрезка (это для вращения)
      public:
       tline(int, int);
       virtual void move();
};
class tcircle: public tpoint { // наследуется от точки
      protected:
       int r1; // радиус
      public:
       tcircle(int, int);
       virtual void move();
};
class trectangle: public tline { // класс прямоугольника наследуется от линии
      protected:
       int x2,y2; // третья координата вершины, четвертая вычисляется
       float angle; // угол
      public:
       trectangle(int, int);
       virtual void move();
};
class trhomb: public tline { // ромб от линии
      protected:
       int x2,y2; // третья координата, четвертая будет вычисляться
       float angle; // угол
      public:
       trhomb(int, int);
       virtual void move();
};
class ttriangle: public tline { // треугольник от линии
      protected:
       int x2,y2; // третья координата
       float angle; // угол
      public:
       ttriangle(int, int);
       virtual void move();
};
class tellipse: public tcircle { // эллипс  от окружности
      protected:
       int r2; // второй радиус
      public:
       tellipse(int, int);
       virtual void move(); 
};
//--------------------------ОПИСАНИЕ КОНСТРУКТОРОВ----------------------------------
tfigure::tfigure(int w, int h) { // конструктор общий, для фигуры
     width=w; // ширина
     height=h; // высота  
     dx=rand()%3-1; // приращение
     dy=rand()%3-1;
     while ((dx==0)&(dy==0)) dy=rand()%3-1; // эта ситуация должна уже быть знакома
     color=COLOR(rand()%256,rand()%256,rand()%256); // цвет
}
tpoint::tpoint(int w, int h):tfigure(w,h) { // конструктор точки, сначала вызывается конструктор фигуры
     x=rand()%w; // задаются координаты
     y=rand()%h;
}
tline::tline(int w, int h):tpoint(w,h) { // линия
     typemove=rand()%2;                 // тип движения
     x1=rand()%100-50; // вторая координата (смещение относительно первой точки от -50 до 50)
     y1=rand()%100-50;
     while (y1==0) y1=rand()%100-50; // пока игрек = 0 генерируем заново, чтобы не получилась точка вместо прямой
     if (x+abs(x1)>w) x=w-x1;   // смотри чтобы отрезок не вышел за границы экрана
     if (x-abs(x1)<0) x=x1;        
     if (y+abs(y1)>h) y=h-y1;        
     if (y-abs(y1)<0) y=y1;       
     length=sqrt(x1*x1+y1*y1); // считаем длину
     time=rand()%360;   // время - случ. величина (иначе говоря угол поворота)              
}
tcircle::tcircle(int w, int h):tpoint(w,h) { // окружность
     r1=rand()%40+10;
     if (x+r1>w) x=w-r1;        
     if (x-r1<0) x=r1;        
     if (y+r1>h) y=h-r1;        
     if (y-r1<0) y=r1;                       
}
trectangle::trectangle(int w, int h):tline(w,h) {
     x2=-x1;
     y2=y1;
     if (x+abs(x1)>w) x=w-x1;        
     if (x-abs(x1)<0) x=x1;        
     if (y+abs(y1)>h) y=h-y1;        
     if (y-abs(y1)<0) y=y1;   
     angle=2*atan(abs(x1/y1)); // вычисляем угол поворота прямоугольника, зная координаты углов
}
trhomb::trhomb(int w, int h):tline(w,h) {
     x2=-x1;
     y2=y1;
     if (x+abs(x1)>w) x=w-x1;        
     if (x-abs(x1)<0) x=x1;        
     if (y+abs(y1)>h) y=h-y1;        
     if (y-abs(y1)<0) y=y1; 
     angle=2*atan(abs(x1/y1));
}
ttriangle::ttriangle(int w, int h):tline(w,h) {  
     x2=-x1;
     y2=y1;
     if (x+abs(x1)>w) x=w-x1;        
     if (x-abs(x1)<0) x=x1;        
     if (y+abs(y1)>h) y=h-y1;        
     if (y-abs(y1)<0) y=y1;   
     angle=2*atan(abs(x1/y1));                   
}
tellipse::tellipse(int w, int h):tcircle(w,h) {
     r2=rand()%40+10;     
     if (x+r2>w) x=w-r2;        
     if (x-r2<0) x=r2;        
     if (y+r2>h) y=h-r2;        
     if (y-r2<0) y=r2;
}
//------------------------ОПИСАНИЕ ДВИЖЕНИЯ---------------------------------------
void tpoint::move() { // движение точки
     setcolor(0); // закрашиваем старую точку
     rectangle(x,y,x+1,y+1);
     if (x+dx>width) dx=-dx;
     if (x+dx<0) dx=-dx;
     if (y+dy>height) dy=-dy;
     if (y+dy<0) dy=-dy; //двигаем
     x+=dx;
     y+=dy;  //перемещаем
     setcolor(color); // рисуем
     rectangle(x,y,x+1,y+1);     
}
void tline::move() { // движение линии
     setcolor(0); // закрашиваем
     line(x-x1,y-y1,x+x1,y+y1);
     if (typemove==1) { // если тип движения - вращение вокруг оси
        time+=0.05; // поворачиваем
        x1=int(sin(time)*length); // вычисляем новые координаты
        y1=int(cos(time)*length);        
     } else { // иначе
         if ((x+x1+dx>width)|(x-x1+dx>width)) dx=-dx; // смотрим чтобы не вышли концы отрезка за границы экрана
         if ((x+x1+dx<0)|(x-x1+dx<0)) dx=-dx;
         if ((y+y1+dy>height)|(y-y1+dy>height)) dy=-dy;
         if ((y+y1+dy<0)|(y-y1+dy<0)) dy=-dy; 
         x+=dx; // двигаем
         y+=dy; 
     }      
     setcolor(color); // рисуем
     line(x-x1,y-y1,x+x1,y+y1);     
}
void tcircle::move() { // окружность
     setcolor(0); // тут все понятно
     circle(x,y,r1);
     if (x+dx+r1>width) dx=-dx;
     if (x+dx-r1<0) dx=-dx;
     if (y+dy+r1>height) dy=-dy;
     if (y+dy-r1<0) dy=-dy; 
     x+=dx;
     y+=dy;       
     setcolor(color);
     circle(x,y,r1);     
}
void trectangle::move() { // прямоугольник
     setcolor(0); // закрашиваем
     line(x-x1,y-y1,x-x2,y-y2);
     line(x-x2,y-y2,x+x1,y+y1);
     line(x+x1,y+y1,x+x2,y+y2);
     line(x+x2,y+y2,x-x1,y-y1);
     if (typemove==1) { // если нужно вертеть
        time+=0.05; // меняем время
        x1=int(sin(time)*length); // вычисляем координаты после поворота
        y1=int(cos(time)*length); 
        x2=int(sin(time+angle)*length);
        y2=int(cos(time+angle)*length);        
     } else { // иначе просто двигаем
         if ((x+x1+dx>width)|(x-x1+dx>width)) dx=-dx; // проверка чтобы не уходил за границы
         if ((x+x1+dx<0)|(x-x1+dx<0)) dx=-dx;
         if ((y+y1+dy>height)|(y-y1+dy>height)) dy=-dy;
         if ((y+y1+dy<0)|(y-y1+dy<0)) dy=-dy; 
         x+=dx; //смещаем
         y+=dy; 
     }      
     setcolor(color); // рисуем
     line(x-x1,y-y1,x-x2,y-y2);
     line(x-x2,y-y2,x+x1,y+y1);
     line(x+x1,y+y1,x+x2,y+y2);
     line(x+x2,y+y2,x-x1,y-y1);     
}
void trhomb::move() { // ромб - вершины ромба - середины сторон прямоугольнка
     setcolor(0);  // закрашиваем
     line(((x-x1)+(x-x2))/2,((y-y1)+(y-y2))/2,((x-x2)+(x+x1))/2,((y-y2)+(y+y1))/2);
     line(((x-x2)+(x+x1))/2,((y-y2)+(y+y1))/2,((x+x1)+(x+x2))/2,((y+y1)+(y+y2))/2);
     line(((x+x1)+(x+x2))/2,((y+y1)+(y+y2))/2,((x+x2)+(x-x1))/2,((y+y2)+(y-y1))/2);
     line(((x+x2)+(x-x1))/2,((y+y2)+(y-y1))/2,((x-x1)+(x-x2))/2,((y-y1)+(y-y2))/2);
     if (typemove==1) { // если нужно крутить вокруг своей оси
        time+=0.05;
        x1=int(sin(time)*length); // вычисляем координаты
        y1=int(cos(time)*length); 
        x2=int(sin(time+angle)*length);
        y2=int(cos(time+angle)*length);        
     } else {
         if ((x+x1+dx>width)|(x-x1+dx>width)) dx=-dx;
         if ((x+x1+dx<0)|(x-x1+dx<0)) dx=-dx;
         if ((y+y1+dy>height)|(y-y1+dy>height)) dy=-dy;
         if ((y+y1+dy<0)|(y-y1+dy<0)) dy=-dy; 
         x+=dx;
         y+=dy; 
     }      
     setcolor(color);
     line(((x-x1)+(x-x2))/2,((y-y1)+(y-y2))/2,((x-x2)+(x+x1))/2,((y-y2)+(y+y1))/2);
     line(((x-x2)+(x+x1))/2,((y-y2)+(y+y1))/2,((x+x1)+(x+x2))/2,((y+y1)+(y+y2))/2);
     line(((x+x1)+(x+x2))/2,((y+y1)+(y+y2))/2,((x+x2)+(x-x1))/2,((y+y2)+(y-y1))/2);
     line(((x+x2)+(x-x1))/2,((y+y2)+(y-y1))/2,((x-x1)+(x-x2))/2,((y-y1)+(y-y2))/2);     
}
void ttriangle::move() { // аналогично
     setcolor(0);
     line(x-x1,y-y1,x-x2,y-y2);
     line(x-x2,y-y2,x+x1,y+y1);
     line(x+x1,y+y1,x-x1,y-y1);
     if (typemove==1) {
        time+=0.05;
        x1=int(sin(time)*length);
        y1=int(cos(time)*length); 
        x2=int(sin(time+angle)*length);
        y2=int(cos(time+angle)*length);        
     } else {
         if ((x+x1+dx>width)|(x-x1+dx>width)) dx=-dx;
         if ((x+x1+dx<0)|(x-x1+dx<0)) dx=-dx;
         if ((y+y1+dy>height)|(y-y1+dy>height)) dy=-dy;
         if ((y+y1+dy<0)|(y-y1+dy<0)) dy=-dy; 
         x+=dx;
         y+=dy; 
     }      
     setcolor(color);
     line(x-x1,y-y1,x-x2,y-y2);
     line(x-x2,y-y2,x+x1,y+y1);
     line(x+x1,y+y1,x-x1,y-y1);          
}
void tellipse::move() { // аналогично (эллипс не крутится)
     setcolor(0);
     ellipse(x,y,0,0,r1,r2);                  
     if (x+dx+r1>width) dx=-dx;
     if (x+dx-r1<0) dx=-dx;
     if (y+dy+r2>height) dy=-dy;
     if (y+dy-r2<0) dy=-dy; 
     x+=dx;
     y+=dy;     
     setcolor(color);
     ellipse(x,y,0,0,r1,r2);       
}
