uses crt, graph;
const eps=0.0001;
      y_0=0;
      y_1=-1;
      rastx=400;
      rasty=200;
type
  typeY=array[1..2] of real;
  TypeC=array[1..4,1..4] of real;
  TypeD=array[1..4] of real;
  TypeMiX=array[0..5] of real;
  typeh=array[1..5] of real;
var kkk:real;
    yy:TypeY;
    EndH:real;
    c: Typec;
    d: typeD;
    m,x,uzels: typeMix;
    h: typeH;

function func(x:real; y:real; y1:real; y2:real):real;
begin
func:=y2+sin(y2)+y+x*x+y1;
end;

procedure searchInt(var a:real; var b:real; x:real; y:real; y1:real);
var c,d,h,fa,fb: real;
    i: integer;
begin
c:=-1; d:=1 ;h:=1; a:=c; b:=a+h;
fa:=1; fb:=1;
 while fa*fb>0 do
   begin
   a:=c;b:=a+h;
   fa:=func(x,y,y1,a); fb:=func(x,y,y1,b);
   while b<d do
      begin a:=b;
            b:=b+h;
            fa:=fb;
            fb:=func(x,y,y1,b);
            if fa*fb<0 then break;
      end;
      c:=c-1; d:=d+1; h:=h/2;
   end;
end;


procedure Mh(x:real; y:real; y1:real; var kr:real);
var fa,fb,fc,c,cp,a,b:real;
begin
     searchInt(a,b,x,y,y1);
     fa:=func(x,y,y1,a);fb:=func(x,y,y1,b);
     c:=0; cp:=(fb*a-fa*b)/(fb-fa);
     While (abs(cp-c)>eps) do
      begin
        c:=cp;
        fc:=func(x,y,y1,c);
        if fa*fc<0 then begin b:=c; fb:=fc; end
        else begin a:=c; fa:=fc; end;
        cp:=(fb*a-fa*b)/(fb-fa);
      end;
        kr:=cp;
end;

function Difur(x:real; y:real; y1:real):real;
var a,b,kk:real;
begin
Mh(x,y,y1,kk);
difur:=kk;
end;


function Ronge_Kutt(xi:real; var Y:TypeY; h:real):real;{выдает Yi+1}
var K:array[1..4,1..2] of real;
    rrr:typeY;
begin
k[1,1]:=y[2]; k[1,2]:=difur(xi,y[1],y[2]);
k[2,1]:=y[2]+(h/2)*k[1,2]; k[2,2]:=difur(xi+h/2,y[1]+(h/2)*k[1,1],y[2]+(h/2)*k[1,2]);
k[3,1]:=y[2]+(h/2)*k[2,2]; k[3,2]:=difur(xi+h/2,y[1]+(h/2)*k[2,1],y[2]+(h/2)*k[2,2]);
k[4,1]:=y[2]+h*k[3,2]; k[4,2]:=difur(xi+h,y[1]+h*k[3,1],y[2]+h*k[3,2]);
y[1]:=y[1]+(h/6)*(k[1,1]+2*k[2,1]+2*k[3,1]+k[4,1]);
y[2]:=y[2]+(h/6)*(k[1,2]+2*k[2,2]+2*k[3,2]+k[4,2]);
end;

procedure D_P(var Yb:typeY; kr:real);
var hh, xi:real;
    Yh,Yh_2:TypeY;
    i: integer;
begin
hh:=0.05;
xi:=0;
yh[1]:=y_0;
yh[2]:=kr;
yh_2:=yh;
While (xi<1) do
  begin
  Ronge_Kutt(xi,Yh,hh);
  Ronge_Kutt(xi,Yh_2,hh/2);
  Ronge_Kutt(xi+hh/2,Yh_2,hh/2);

  if (abs(Yh[1]-Yh_2[1])>3*eps) then
     begin
       hh:=hh/2;
       xi:=0;
       yh[1]:=y_0;
       yh[2]:=kr;
       yh_2:=yh;
     end else xi:=xi+hh;
end;
endH:=hh/2;
yb:=yh_2;
writeln(' y(1)=', yh_2[1]:10:10,'     y1(1)= ',yh_2[2]:10:10);
end;

procedure searchInt1(var a:real; var b:real);
var c,d,h:real;
    ya:TypeY; t:boolean;
begin
a:=-2; h:=0.5; b:=-1.5;
D_P(ya,a);
if ya[1]<y_1 then t:=true else t:=false;
while (t=(ya[1]<y_1)) do
   begin
     if ya[1]<y_1 then begin t:=true; a:=b; b:=b+h; end else begin t:=false; b:=a; a:=a-h; end;
     D_P(ya,a);
   end;
   b:=a; a:=a-h;
end;

procedure strelba;
var  a,b,c,t:real;
     ya,yb,yc:TypeY;
Begin
  writeln('Search int :');
  searchInt1(a,b);
  writeln(' a= ',a:2:2,'   b=',b:2:2);
  D_P(ya,a);D_P(yb,b);
  repeat
    c:=(a+b)/2;
    D_P(yc,c);
    if ((ya[1]-y_1)*(yc[1]-y_1))<0 then begin b:=c; yb:=yc;  end else begin a:=c; ya:=yc; end;
  until (abs(y_1-yc[1])<eps);
 kkk:=c;
  writeln(' k=y1(0)=',kkk:10:10);
end;

Procedure z_X;
var i:integer;
begin
 for i:=0 to 5 do x[i]:=0.2*i;
end;

procedure p_H;
 var i :integer;
   begin
      for i:=1 to 5 do
      h[i]:=abs(x[i]-x[i-1]);
   end;

procedure z_C;
 var i: integer;
  begin
     for i:=1 to 4 do
       begin
          if (i-1)<>0 then c[i,i-1]:=h[i]/6;
          c[i,i]:=(h[i]+h[i+1])/3;
          if i<>(4) then c[i,i+1]:=h[i+1]/6;
       end;
  end;
procedure z_D;
 var i: integer;
   begin
      for i:=1 to 4 do
       d[i]:=((uzels[i+1]-uzels[i])/h[i+1])-((uzels[i]-uzels[i-1])/h[i]);
   end;

function spline(xx:real):real;
 var i:integer;
     s: real;
  begin
     for i:=1 to 5 do
        if (xx>=x[i-1])and(xx<=x[i]) then break;

     s:=m[i-1]*(x[i]-xx)*(x[i]-xx)*(x[i]-xx)/(6*h[i])
        +m[i]*(xx-x[i-1])*(xx-x[i-1])*(xx-x[i-1])/(6*h[i])
        +(uzels[i-1]-(m[i-1]*h[i]*h[i]/6))*((x[i]-xx)/h[i])
        +(uzels[i]-(m[i]*h[i]*h[i]/6))*((xx-x[i-1])/h[i]);
     spline:=s;
  end;

procedure hod_pr(var c:TypeC; var d:typeD);
 var  b     :real;
      l,i,j :integer;
  begin
     for i:=1 to 3 do
         begin
              for j:=i+1 to 4 do
                  begin
                       b:=c[j,i]/c[i,i];
                       for l:=i to 4 do c[j,l]:=c[j,l]-c[i,l]*b;
                       d[j]:=d[j]-d[i]*b;
                  end;
         end
  end;

procedure back(c:typeC; d:typeD; var m:typeMiX);
 var i,j:integer;
  begin
    for i:=4 downto 1 do
        begin
             m[i]:=d[i];
             for j:=4 downto i+1 do m[i]:=m[i]-c[i, j]*m[j];
             m[i]:=m[i]/c[i, i];
        end;
    m[0]:=0; m[5]:=0;
    for i:=0 to 5 do
        writeln('m[',i,']= ',m[i]:8:4);
    writeln;
  end;

procedure graphik;
 var i:real; j,gm,gd: integer;
     yy:Typey;
     oy,ox:integer;
  begin
     gm:=0; gd:=0;
     initgraph(gm,gd,'h:\siaod\bgi');
     cleardevice;
     setcolor(green);
     ox:=20;
     oy:=200;
     uzels[0]:=y_0;
     j:=1;
     yy[1]:=y_0;
     yy[2]:=kkk;

    setcolor(white);
    line(ox,0,ox,480);
    line(0,oy,640,oy);

    i:=0;
    moveto(round(i*rastx)+ox,oy-round(y_0*rasty));
    while i<=1 do
       begin
         ronge_Kutt(i,yy,endh);
         i:=i+endh;
         lineto(round(i*rastx)+ox,oy-round(yy[1]*rasty));
         if round(i*1000000)=round(200000*j) then
           begin
              uzels[j]:=yy[1];
              inc(j);
           end;
       end;
    readkey;
    z_X;
    p_H;
    z_C;
    z_D;
    hod_pr(c,d);
    back(c,d,m);
    setcolor(2);
    i:=0;
    moveto(round(i*rastx)+ox,oy-round(Spline(i)*rasty));
    while i< 1.1 do
       begin
         i:=i+endh;
         lineto(round(i*rastx)+ox,oy-round(Spline(i)*rasty));
       end;

    setcolor(white);
    for j:=0 to 5 do
      circle(round((j/5)*rastx)+ox,oy-round(uzels[j]*rasty),3);
   readkey;
   closegraph;

  end;

Procedure Power;
var x:real; i:integer;
begin
x:=0.12;
while round(x*100)<=round(0.92*100) do
        begin
        if round(x*100)<>round(0.22*100) then
           writeln('Power(',x:2:2,') = ',spline(x)*spline(x):10:10);
           x:=x+0.1;
        end;
end;
procedure vivod;
var i: integer;
    yy: typeY;
    x:real;
begin
  clrscr;
  x:=0;
  yy[1]:=y_0;
  yy[2]:=kkk;
  i:=1;
  writeln('y(',x:2:2,')= ',y:10:9,   'Spline(',x:2:2,')= ',Spline(x):10:9);
    while x<=1 do
       begin
         ronge_Kutt(x,yy,endh);
         x:=x+endh;
         if round(x*10000000)=round(500000*i) then
           begin
             writeln('y(',x:2:2,')= ',yy[1]:10:9,'   ','y1(',x:2:2,')= ',
             yy[2]:10:9,'   ','Spline(',x:2:2,')= ',Spline(x):10:9);
             inc(i);
           end;
       end;
    readkey;

end;

var i: integer;
begin
clrscr;
writeln;
writeln(' Method strelb....');
strelba;
readkey;
graphik;
clrscr;
Power;
readkey;
vivod;
end.













Read:



















Решение дифферинциального уравнения начинается с краевой задачи.
Известно : Функция в точке 0 и функция в точке 1, хотя нужно
для решения диф. уравнения производная первая в точке 0.
Для того чтобы это найти,используется метод стрельб.
Это по суди и есть например метод половинного деления. Нужно подобрать
такую первую производную в точке 0 чтобы при подстановке в диф уравнение
функция в точке 1 была = 0.2. Что и делает метод стрельб.
Метод стрельб подставляет первую производную в точке 0 в Doublepereschet
который возвращает значение функции и значение производной в точке 1 и
сравнивает с -1 т.е с начальными условиями.

Двойной пересчет считает значение функции и производной с шагом h и h/2
от 0 до 1 и сравнивается по точности. Считая значения в точках
двойной пересчет вызывает метод Ronge_kutt и запоминает конечный шаг в
котором достигается точность.
Метод ронге кутт выдает y y1 в точке x+h с подставленными параметрами
x y y1,
Метод ронге-Кутт использует значение второй производной, которое выдает
Difur, но вторая производная задана не явно
Поэтому функция Difur решает методом хорд уравнение, где неизвестной является
вторая производная.
В итоге найдено значение производной в точке 0 то которое нужно;
Подставляя это значение, тоетсь начальные параметры, в Ronge-Kutt
получается значение функции в различных точках. Значения в
точках i*0.2 где i=0..5 запоминаются в массиве и далее используется
обычная интерполяция сплайном.
И для нахождения мощности в точках просто возводится в квадрат значение
функции в этих точках.
Еще сделан вывод значений функции, производной, и Сплайна с шагом 0.05.
При сдаче курсовика это обычно требуется.
