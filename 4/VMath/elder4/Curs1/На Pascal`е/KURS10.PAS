{$N+}
uses crt, graph;
const eps=0.00001;
      y_0=1;
      y_1=0.5;
      rastx=300;
      rasty=300;
type
  typeY=array[1..2] of double;
  TypeC=array[1..4,1..4] of double;
  TypeD=array[1..4] of double;
  TypeMiX=array[0..5] of double;
  typeh=array[1..5] of double;
  typeCProizv=array[0..20,0..20] of real;

var kkk,k:double; {Сюда записывается найденное значение y1(0)}
    yy:TypeY;
    EndH:double; {Конечный шаг для точности}
    c: Typec;     {Для сплайна}
    d: typeD;                  {Для сплайна}
    m,x,uzels: typeMix;        {Для сплайна}
    h: typeH;                  {Для сплайна}
    CCC:typeCProizv;

function func(x:double; y:double; y1:double; y2:double):double;
begin
func:=y1-cos(y2)-(x*x+y)-4*y2-sin(k*y1);
end;

function FindK:double;
var a,b,k,kt,c,d,h:double;
    i:byte;

  Function f(x:double):double;
  begin
   f:=2*x*x*x-sin(X)-3;
  end;

  Function MPD(a,b:double): double;
  Var
     c:double;
  Begin
    c:=(a+b)/2;
    while abs((b-a)/2)>eps/1000 do begin
      if (f(a)*f(c)<0) then b:=c else a:=c;
      c:=(a+b)/2;
    end;
    mpd:=c;
  end;
begin
  h:=0.5; c:=-0.5; d:=0.5;
  a:=c; b:=a+h;i:=0; k:=10000;
while i<1 do begin
 while b<=d do
  begin
    if f(a)*f(b)<0 then
      begin
         kt:=mpd(a,b);
         if (kt<k) and (kt>0) then k:=kt;
         inc(i);
      end;
    a:=b; b:=b+h;
  end;
c:=c-0.5; d:=d+0.5; h:=h/2;
end;
findK:=k;
end;

procedure searchInt(var a:double; var b:double; x:double; y:double; y1:double);
var c,d,h,fa,fb: double;
    i: integer;
begin
c:=-2; d:=2 ;h:=1; a:=c; b:=a+h;
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


procedure Mh(x:double; y:double; y1:double; var kr:double);
var fa,fb,fc,c,cp,a,b:double;
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
{Возвращает значение y2 c подставленными параметрами}
function Difur(x:double; y:double; y1:double):double;
var a,b,kkk:double;
begin
Mh(x,y,y1,kkk);
difur:=kkk;
end;

{В этот метод подставляются значение  y и y1, а возвращаются в точке x+h}
procedure ronge_Kutt (x:real; var y:typeY; h:real);

  procedure largeF (x:real;lY:typey;var lF:typey);
  begin
    lF[1]:=lY[2];
    lF[2]:=difur(x,lY[1],lY[2]);
  end;
  procedure mul (a:real;b:typeY;var c:typey);
  begin
    c[1]:=a*b[1]; c[2]:=a*b[2];
  end;
  procedure add (a,b:typey;var c:typey);
  begin
    c[1]:=a[1]+b[1]; c[2]:=a[2]+b[2];
  end;

Var
  lF,lFnew,t,tt:typey;
begin

   largeF(x,Y,lF);
    mul(h,lF,t);
    add(Y,t,tt);
   largeF(x+h,tt,lFnew);
   add(lF,lFnew,t);
   mul(h/2,t,tt);
   add(Y,tt,t);
   y:=t;
end;

procedure DoublePereschet(var Yb:typeY; kr:double);
var hh, xi:double;
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
writeln('y(1)= ',yh_2[1]:11:10,'  y1(1)= ',yh_2[2]:11:10,' при y1(0)=',kr:11:10);
end;

procedure searchInt1(var a:double; var b:double);
var c,d,h:double;
    ya:TypeY; t:boolean;
begin
a:=-2; h:=1; b:=a+h;
doublePereschet(ya,a);
if ya[1]<y_1 then t:=true else t:=false;
while (t=(ya[1]<y_1)) do
   begin
     if ya[1]<y_1 then begin t:=true; a:=b; b:=b+h; end else begin t:=false; b:=a; a:=a-h; end;
     doublePereschet(ya,a);
   end;
   b:=a; a:=a-h;
end;

procedure strelba;
var  a,b,c,t:double;
     ya,yb,yc:TypeY;
Begin
  writeln('Поиск интервала :');
  searchInt1(a,b);
  writeln(' a= ',a:2:2,'   b=',b:2:2);
  DoublePereschet(ya,a);DoublePereschet(yb,b);
  repeat
    c:=(a+b)/2;
    DoublePereschet(yc,c);
    if ((ya[1]-y_1)*(yc[1]-y_1))<0 then begin b:=c; yb:=yc;  end else begin a:=c; ya:=yc; end;
  until (abs(y_1-yc[1])<eps);
 kkk:=c;
 writeln('Решение краевой задачи k=y1(0)===',kkk:10:10);
end;

{Для сплайна}
Procedure ZapolnX;
var i:integer;
begin
 for i:=0 to 5 do x[i]:=0.2*i;
end;
{Для сплайна}
procedure podschet_H;
 var i :integer;
   begin
      for i:=1 to 5 do
      h[i]:=abs(x[i]-x[i-1]);
   end;
{Для сплайна}
procedure zapoln_C;
 var i: integer;
  begin
     for i:=1 to 4 do
       begin
          if (i-1)<>0 then c[i,i-1]:=h[i]/6;
          c[i,i]:=(h[i]+h[i+1])/3;
          if i<>(4) then c[i,i+1]:=h[i+1]/6;
       end;
  end;
{Для сплайна}
procedure zapoln_D;
 var i: integer;
   begin
      for i:=1 to 4 do
       d[i]:=((uzels[i+1]-uzels[i])/h[i+1])-((uzels[i]-uzels[i-1])/h[i]);
   end;
{Для сплайна}
function spline(xx:double):double;
 var i:integer;
     s: double;
  begin
     for i:=1 to 5 do
        if (xx>=x[i-1])and(xx<=x[i]) then break;

     s:=m[i-1]*(x[i]-xx)*(x[i]-xx)*(x[i]-xx)/(6*h[i])
        +m[i]*(xx-x[i-1])*(xx-x[i-1])*(xx-x[i-1])/(6*h[i])
        +(uzels[i-1]-(m[i-1]*h[i]*h[i]/6))*((x[i]-xx)/h[i])
        +(uzels[i]-(m[i]*h[i]*h[i]/6))*((xx-x[i-1])/h[i]);
     spline:=s;
  end;
{Прямой ход метода гаусса для решения матрицы для сплайна}
procedure hod_pr(var c:TypeC; var d:typeD);
 var  b     :double;
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
{Обратный ход метода гаусса для решения матрицы для сплайна}
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
{Вывод графиков}
procedure graphik;
 var i:double; j,gm,gd: integer;
     yy:Typey;
     oy,ox:integer;
  begin
     gm:=0; gd:=0;
     initgraph(gm,gd,'c:\tp7\bgi');
     cleardevice;
     settextstyle(7,0,3);
     outtextxy(170,50,'Гpафик функции найденой из ДУ');
     setcolor(green);
     outtextxy(190,100,'и интерполирующей функции');

     ox:=20;
     oy:=470;
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
    zapolnX;
    podschet_H;
    zapoln_C;
    zapoln_D;
    hod_pr(c,d);
    back(c,d,m);
    setcolor(2);
    i:=0;
    moveto(round(i*rastx)+ox,oy-round(Spline(i)*rasty));
    while i<=1 do
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

procedure podschetCCC;
 var i,j:integer;
     x:real; yy:Typey;
 begin

 x:=0; i:=1;
 ccc[0,0]:=kkk;
 yy[1]:=y_0;
 yy[2]:=kkk;
  while x<1-endh do
     begin
        ronge_kutt(x,yy,endh);
        x:=x+endh;
        if round(x*10000)=round(500*i) then begin CCC[i,0]:=yy[2]; inc(i); end;
     end;

     for i:=1 to 20 do
       for j:=20-i downto 0 do
         CCC[j,i]:=ccc[j+1,i-1]-ccc[j,i-1];
 end;

function nuton(x:real; h:real):real;
 var  i,j   :integer;
     fuck   :double;
     q,qq,p :double;
  begin
      fuck:=1;
      q:=(x)/h;
      qq:=q;
      p:=ccc[0,0];

      for i:=1 to 20 do
        begin
          p:=p+(ccc[0,i]*qq)/fuck;
          qq:=qq*(q-i);
          fuck:=fuck*(i+1);
        end;
      nuton:=p;
  end;
procedure vivodSilaToka;
var x: real; i:byte;
begin
 clrscr;
 writeln('Сила тока в моменты времени');
 x:=0.05;
 while x<1 do
   begin
    writeln('Сила тока(',x:1:2,')=  ',Nuton(x,0.05):10:10);
    x:=x+0.05;
   end;
end;

procedure print;
var i,j:integer;
begin
  for i:=0 to 20 do begin
   for j:=0 to 9 do write(ccc[i,j]:7:4);
   writeln;
   end;
end;


{Вывод на экран значений финкции производной и сплайна в точках из [0,1] c шагом 0.05}
procedure vivod;
var i: integer;
    yy: typeY;
    x:double;
begin
  clrscr;
  x:=0;
  yy[1]:=y_0;
  yy[2]:=kkk;
  i:=1;
  writeln('y(',x:2:2,')= ',yy[1]:13:10,'   ','y1(',x:2:2,')= ',yy[2]:13:10,'   ','Spline(',x:2:2,')= ',Spline(x):13:10);
    while x<=1 do
       begin
         ronge_Kutt(x,yy,endh);
         x:=x+endh;
         if round(x*1000000)=round(50000*i) then
           begin
             writeln('y(',x:2:2,')= ',yy[1]:13:10,'   ','y1(',x:2:2,')= ',
             yy[2]:13:10,'   ','Spline(',x:2:2,')= ',Spline(x):13:10);
             inc(i);
           end;
       end;
    readkey;
end;

var i: integer;
begin
clrscr;
writeln;
k:=findk;
writeln('Решение заданного уравнения k===== ',k:10:10);
writeln(' Идет процесс метода стрельб....');
strelba;
writeln('Конечный H соответствующий точности = ',endh:10:13);
writeln('Press any key...');
readkey;
graphik;
clrscr;
PodschetCCC;
VivodSilaToka;
readkey;
vivod;




end.
Read:
Решение дифферинциального уравнения начинается с краевой задачи.
Известно : Функция в точке 0 и функция в точке 1, хотя нужно
для решения диф. уравнения производная первая в точке 0.
Для того чтобы это найти используется метод стрельб.
Это по сути и есть например метод половинного деления. Нужно подобрать
такую первую производную в точке 0 чтобы при подстановке в диф уравнение
функция в точке 1 была = 0.2. Что и делает метод стрельб.
Метод стрельб подставляет первую производную в точке 0 в Doublepereschet
который возвращает значение функции и значение производной в точке 1 и
сравнивает с 0.2 т.е с начальными условиями.
Но сначала нужно найти интервал, что делает SearchInt1;

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
Подставляя это значение, тоетсь начальные параметры в Ronge-Kutt
получается значение функции в различных точках. Значения в
точках i*0.2 где i=0..5 запоминаются в массиве и далее используется
обычная интерполяция сплайном.
И для нахождения мощности в точках просто возводится в квадрат значение
функции в этих точках.
Вообще то начальные условия: задана функция в 0 и производная в 1, но я
поставил что задана функция в 1, т к иначе не решается.Либо функция корявая.
Еще сделан вывод значений функции, производной, и Сплайна с шагом 0.05.
При сдаче курсовика это обычно требуется.