uses crt, graph;
type
  vector = array [1..2] of real;

const
  eps = 0.00001;
  mass: array[1..2] of real = (1,0.5);
       xi: array[0..5] of real = (0,0.2,0.4,0.6,0.8,1);
  a = 0;
  b = 1;

var
                    deltay:   array[0..5] of real;
  koef,miny, maxy, k, h, x:   real;
                 gd,gm,j,i:   integer;
                         C:   array[1..4,1..5] of real;
                         m:   array[0..5] of real;
                    result:   text;

function fun(x:real):real;
begin
  fun:=x*x-3*x-1;
end;

{Решение уравнения (наименьший положительный корень)}
function seekK:real;
var
        seeker:   boolean;
         c,A,B:   real;
begin
  {Поиск в положительном направлении}
  b:=0;
  seeker:=true;
  while seeker do
    begin
      a:=b;
      b:=b+1;
      if fun(A)*fun(B)<0 then
        seeker:=false;
    end;
  {МПД}
  repeat
    c:=(a+b)/2;
    if fun(c)*fun(a)<0 then b:=c else a:=c;
  until eps>abs(a-b)/2;
  seekK:=c;
end;
{вектор-функция F}
procedure f(x:real;var y:vector);
var
  yi:   vector;
begin
  yi:=y;
  y[1]:=y[2];
  y[2]:=yi[2]-(sqr(x)+y[1]*k)+sin(y[1]);
end;

{Метод Рунге-Кутта 4-го порядка}
procedure rk4(x:real;var y:vector);
var
  k1, k2, k3, k4:   vector;
               i:   integer;
begin
  k1:=y;
  f(x,k1);

  for i:=1 to 2 do
    k2[i]:=y[i]+k1[i]*h/2;
  f(x+h/2,k2);

  for i:=1 to 2 do
    k3[i]:=y[i]+k2[i]*h/2;
  f(x+h/2,k3);

  for i:=1 to 2 do
    k4[i]:=y[i]+k3[i]*h;
  f(x+h,k4);

  for i:=1 to 2 do
    y[i]:=y[i]+(k1[i]+2*k2[i]+2*k3[i]+k4[i])*h/6;
end;

function poiskK(k:real):real;
var
  yh,yh2:   vector;
  x: real;
begin
  h:=0.1;
  yh2[1]:=mass[1];
  yh2[2]:=k;
  x:=a;
  while (x<=b) do
    begin
      rk4(x,yh2);
      x:=x+h;
    end;
  repeat
    yh:=yh2;
    h:=h/2;
    x:=a;
    while (x<=b) do
      begin
        rk4(x,yh2);
        x:=x+h;
      end;
  until abs(yh[1]-yh2[1])>15*Eps;
  poiskK:=yh2[1]+(yh2[1]-yh[1])/15;
end;

{Нахождение коэфициента}
function krae:real;
var
        c:   real;
     a, b:   real;
  seeker:   boolean;
      tmp:   vector;
begin
  {Нахождение интервала на котором функция > и < mainy[2]}
  A:=-1;B:=0;
  seeker:=true;
  while seeker do
    begin
      if ((poiskK(A)<mass[2])and(poiskK(B)>mass[2])) or
         ((poiskK(A)>mass[2])and(poiskK(B)<mass[2]))  then
         break;
      if ((poiskK(-A)>mass[2])and(poiskK(-B)<mass[2])) or
         ((poiskK(-A)<mass[2])and(poiskK(-B)>mass[2])) then
         break;
      B:=A;
      A:=A-1;
    end;
  {Метод половинного деления}
  repeat
    c:=(a+b)/2;
    if ((poiskK(b)>mass[2])and(poiskK(c)<mass[2])) or
       ((poiskK(b)<mass[2])and(poiskK(c)>mass[2])) then a:=c else b:=c;
  until eps>abs(b-a)/2;
  krae:=c;
end;

{Метод двойного прохода}
function proh2(v:real):real;
var
  yh,yh2:   vector;
  x: real;
begin
  h:=0.1;
  yh2[1]:=mass[1];
  yh2[2]:=koef;
  if v=a then
    begin
      proh2:=mass[1];
      exit;
    end;
  x:=a;
  while (x<=v) do
    begin
      rk4(x,yh2);
      x:=x+h;
    end;
  repeat
    yh:=yh2;
    h:=h/2;
    x:=a;
    while (x<=v) do
      begin
        rk4(x,yh2);
        x:=x+h;
      end;
  until abs(yh[1]-yh2[1])>15*Eps;
  proh2:=yh2[1]+(yh2[1]-yh[1])/15;
end;

{Интерполяция по Ньютону}
function p(x:real):real;
var
  fac,sum,pr,q:   real;
  i,j:   integer;
begin
  q:=x/0.2;
  sum:=deltay[0];
  fac:=1;
  for i:=1 to 5 do
    begin
      pr:=1;
      fac:=fac*i;
      for j:=0 to i-1 do
        pr:=pr*(q-j);
      sum:=sum+deltay[i]*pr/fac;
    end;
  p:=sum;
end;
{---------------------------------------------------}
{Нахождение min, max значений функции, для построения графика}
procedure GetMaxAndMinY;
var
  x:   real;
begin
  x:=0;
  while x<=1 do
    begin
      if -p(x) < minY then minY:=-p(x);
      if -p(x) > maxY then maxY:=-p(x);
      if -proh2(x) < minY then minY:=-proh2(x);
      if -proh2(x) > maxY then maxY:=-proh2(x);
      x:=x+0.2;
    end;
end;

function kx(x:real):integer;
begin
  kx:= round(639*x);
end;

function ky(y:real):integer;
begin
  ky:= round(479*(-y-miny)/(maxy-miny));
end;

{Построение графика}
procedure Graf;
var
  x:   real;
  i:   integer;
begin
  x:=0;
  moveto(kx(x),ky(p(x)));
  while x<=1 do
    begin
      lineto(kx(x),ky(p(x)));
      x:=x+0.05;
    end;
  x:=0;
  moveto(kx(x),ky(proh2(x)));
  while x<=1 do
    begin
      lineto(kx(x),ky(proh2(x)));
      x:=x+0.01;
    end;
end;
{Формула Симпсона}
function SimpsonsFor:real;
var
         h:   real;
         i:   integer;
         y:   array[0..100] of real;
  sum,sum1:   real;
         k:   integer;
begin
  k:=50;
  sum:=0;sum1:=0;

  for i:=0 to 100 do
    y[i]:=proh2(0.01*i);

  for i:=1 to k-1 do
    sum:=sum+y[2*i];

  for i:=1 to k do
    sum1:=sum1+y[2*i-1];

  SimpsonsFor:=(y[0]+y[100]+2*sum+4*sum1)*0.01/3;
end;

begin
  clrscr;
  k:=seekK;

  koef:=krae;
  writeln(proh2(b):15:10);
  assign(result,'desna.txt');
  rewrite(result);
  writeln('K = ',k:10:15);
  writeln(result,'K = ',k:10:15);
  writeln('Koef = ',koef:10:15);
  writeln(result,'Koef = ',koef:10:15);

  writeln('Кол-во теплоты : ',SimpsonsFor:15:10);
  writeln(result,'Кол-во теплоты : ',SimpsonsFor:15:10);
  x:=0;
  for i:=0 to 5 do
    begin
      deltay[i]:=proh2(x);
      x:=x+0.2;
    end;

  for i:=0 to 4 do
    for j:=5 downto 1+i do
      deltay[j]:=deltay[j]-deltay[j-1];

  x:=0;
  for i:=0 to 20 do
    begin
      writeln(x:20:2,proh2(x):20:14,p(x):20:14);
      writeln(result,x:20:2,proh2(x):20:14,p(x):20:14);
      x:=x+0.05;
    end;

  readln;
  GetMaxAndMinY;
  gm:=detect;
  initgraph(gd,gm,'c:\tp\bgi');
  Graf;
  close(result);
  repeat until keypressed;
  closegraph;

end.