
uses crt, graph;
type
  vector = array [1..2] of real;

const
  eps = 0.00001;
  yab: array[1..2] of real = (1,0.5);
   xx: array[0..5] of real = (0,0.2,0.4,0.6,0.8,1);
  a = 0;
  b = 1;

var
                        yy:   array[0..5] of real;
    kr,miny, maxy, k, h, x:   real;
                 gd,gm,j,i:   integer;
                         C:   array[1..4,1..5] of real;
                         m:   array[0..5] of real;
                       txt:   text;

function arcsin(x:real):real;
begin
  if x=0 then arcsin:=0
  else arcsin:=pi-arctan(sqrt(x/(1-sqr(x))));
end;

function funct(x:real):real;
begin
  funct:=4*sqr(sqr(x))*x-arccos(x)-1;
end;

{Решение уравнения (наименьший положительный корень)}
function minK:real;
var
     ok:   boolean;
  c,A,B:   real;
begin
  {Поиск в положительном направлении}
  b:=0;
  ok:=true;
  while ok do
    begin
      a:=b;
      b:=b+1;
      if funct(A)*funct(B)<0 then
        ok:=false;
    end;
  {МПД}
  repeat
    c:=(a+b)/2;
    if funct(c)*funct(a)<0 then b:=c else a:=c;
  until eps>abs(a-b)/2;
  minK:=c;
end;
{вектор-функция F}
procedure f(x:real;var y:vector);
var
  tmp:   vector;
begin
  tmp:=y;
  y[1]:=y[2];
  y[2]:=cos(tmp[1])+k*tmp[2]-exp(-x);
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

function findKr(kr:real):real;
var
  yh,yh2:   vector;
  x: real;
begin
  h:=0.1;
  yh2[1]:=yab[1];
  yh2[2]:=kr;
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
  findKr:=yh2[1]+(yh2[1]-yh[1])/15;
end;

{Нахождение коэфициента}
function kraeZ:real;
var
        c:   real;
     a, b:   real;
       ok:   boolean;
      tmp:   vector;
begin
  {Нахождение интервала на котором функция > и < yab[2]}
  A:=-1;B:=0;
  ok:=true;
  while ok do
    begin
      if ((findKr(A)<yab[2])and(findKr(B)>yab[2])) or
         ((findKr(A)>yab[2])and(findKr(B)<yab[2]))  then
         break;
      if ((findKr(-A)>yab[2])and(findKr(-B)<yab[2])) or
         ((findKr(-A)<yab[2])and(findKr(-B)>yab[2])) then
         break;
      B:=A;
      A:=A-1;
    end;
  {Метод половинного деления}
  repeat
    c:=(a+b)/2;
    if ((findKr(b)>yab[2])and(findKr(c)<yab[2])) or
       ((findKr(b)<yab[2])and(findKr(c)>yab[2])) then a:=c else b:=c;
  until eps>abs(b-a)/2;
  kraeZ:=c;
end;

{Метод двойного прохода}
function prohod2(v:real):real;
var
  yh,yh2:   vector;
  x: real;
begin
  h:=0.1;
  yh2[1]:=yab[1];
  yh2[2]:=kr;
  if v=a then
    begin
      prohod2:=yab[1];
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
  prohod2:=yh2[1]+(yh2[1]-yh[1])/15;
end;

{Интерполяция сплайном}
function inter(x:real):integer;
var
  i:   integer;
begin
  for i:=1 to 5 do
    if (x > xx[i-1]) and (x < xx[i]) then break;
  inter:=i;
end;

function s(x:real):real;
var
  sum:   real;
  i:   integer;
begin
  i:=inter(x);
  sum:=M[i-1]*(xx[i]-x)*sqr(xx[i]-x)/(6*0.2);
  sum:=sum+M[i]*(x-xx[i-1])*sqr(x-xx[i-1])/(6*0.2);
  sum:=sum+(yy[i-1]-M[i-1]*sqr(0.2)/6)*(xx[i]-x)/0.2;
  s:=sum+(yy[i]-M[i]*sqr(0.2)/6)*(x-xx[i-1])/0.2;
end;

procedure matrix;
var
  sum,d:   real;
  i,j,k:   integer;
begin
  for i:=1 to 5-1 do
    for j:=1 to 5-1 do
      if i=j then c[i,j]:=(0.2+0.2)/3
      else
      if j=i+1 then c[i,j]:=0.2/6
      else
      if j=i-1 then c[i,j]:=0.2/6
      else
        c[i,j]:=0;
  for i:=1 to 5-1 do
    c[i,5]:=(yy[i+1]-yy[i])/0.2-(yy[i]-yy[i-1])/0.2;

  for j:= 1 to 5 do
    for i:= j + 1 to 5-1 do
      begin
        d:=c[i,j];
        for k:= j to 5 do
          c[i,k]:= c[i,k] - c[j,k] * d / c[j,j];
      end;
  for i:= 5 - 1 downto  1 do
    begin
      m[i]:= c[i,5];
      for j:= i + 1 to 5 do
        m[i]:= m[i] - c[i,j] * m[j];
      m[i]:= m[i] / c[i,i];
    end;

end;
{---------------------------------------------------}
procedure GetMaxAndMinY;
var
  x:   real;
begin
  x:=0;
  while x<=1 do
    begin
      if -s(x) < minY then minY:=-s(x);
      if -s(x) > maxY then maxY:=-s(x);
      if -prohod2(x) < minY then minY:=-prohod2(x);
      if -prohod2(x) > maxY then maxY:=-prohod2(x);
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
  moveto(kx(x),ky(s(x)));
  while x<=1 do
    begin
      lineto(kx(x),ky(s(x)));
      x:=x+0.05;
    end;
  x:=0;
  moveto(kx(x),ky(prohod2(x)));
  while x<=1 do
    begin
      lineto(kx(x),ky(prohod2(x)));
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
    y[i]:=prohod2(0.01*i);

  for i:=1 to k-1 do
    sum:=sum+y[2*i];

  for i:=1 to k do
    sum1:=sum1+y[2*i-1];

  SimpsonsFor:=(y[0]+y[100]+2*sum+4*sum1)*0.01/3;
end;

begin
  clrscr;
  k:=minK;

  kr:=kraeZ;
  writeln(prohod2(b):15:10);
  assign(txt,'resna.txt');
  rewrite(txt);
  writeln('K = ',k:10:15);
  writeln(txt,'K = ',k:10:15);
  writeln('kr = ',kr:10:15);
  writeln(txt,'kr = ',kr:10:15);

  writeln('Кол-во теплоты : ',SimpsonsFor:15:10);
  writeln(txt,'Кол-во теплоты : ',SimpsonsFor:15:10);
  x:=0;
  for i:=0 to 5 do
    begin
      yy[i]:=prohod2(x);
      x:=x+0.2;
    end;

  x:=0;
  for i:=0 to 20 do
    begin
      writeln(x:20:2,prohod2(x):20:14,s(x):20:14);
      writeln(txt,x:20:2,prohod2(x):20:14,s(x):20:14);
      x:=x+0.05;
    end;

  readln;
  GetMaxAndMinY;
  gm:=detect;
  initgraph(gd,gm,'bgi');
  Graf;
  close(txt);
  repeat until keypressed;
  closegraph;
end.