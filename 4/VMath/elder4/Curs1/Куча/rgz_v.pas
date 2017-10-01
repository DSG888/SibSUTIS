{
{ y'' + y+ 2*y'= 5*sin(y'') + 3*x^2
{ y(0)=1
{ y(1)=0.3;
}

uses crt,graph;

type
vector=array[0..1] of real;
const
e=0.0001;
masx:array[1..9] of real=(0,0.12,0.32,0.42,0.52,0.62,0.72,0.82,0.92);{ТОчки для расчета мошности}

var
masy:array[1..9] of real;
x,y:real;
a,b:real;
ynach:vector;
mas1y,mas1x:array[1..6] of real;{дЛя сплайна}
k:real;
i,j:integer;
yr:vector; {У - результирующее}
maxy,miny:real;                  {Для масштабировки}

function fp(yp2,yp1,y,x:real):real;   {Возвращает значение F(x,y,y',y'') }
begin
fp:=yp2+y+ 2* yp1 - 5*sin(yp2) - 3*x*x; { y'' + y+ 2*y'= 5*sin(y'') + 3*x^2}
end;

function fpr(yp2:real):real;  {dF(x,y,y',y'')/d(y'')}
begin
fpr:=1-5*cos(yp2);{}
end;

procedure f(x:real;y1:vector;var fxy:vector);{Возвращает
          значение y'' в точке (x,y,y')}
var
y,y2:real;
a,b,h,c:real;
begin
a:=-2;
b:=2;
h:=1.1;
y:=a-h;
{Поиск интервала где функцыя миняет знак}
repeat
y:=y+h;{у начинается с а}
if(y>b) then begin
        a:=a*2;
        b:=b*2;
        h:=h/2;
        y:=a;
        end;
until fp(y,y1[1],y1[0],x)*fp(y+h,y1[1],y1[0],x)<0;
a:=y;
b:=y+h;
repeat     {MPD}
c:=(b+a)/2;
if (fp(a,y1[1],y1[0],x)*fp(c,y1[1],y1[0],x)<0) then b:=c
                                               else a:=c;
until abs(a-b)<0.1;
y2:=(a+b)/2; {y2 - y с точностью 0.1}
repeat  {Метод ньютона}
y:=y2;
y2:=y - (fp(y,y1[1],y1[0],x)/fpr(y));
until abs(y2-y)<e;
fxy[0]:=y1[1];
fxy[1]:=y2;
end;

procedure rk1h(x:real;y:vector;h:real;var yo:vector);{1 шаг рунге - кутта}
var
k1,k2,k3,k4:vector;
vspomk:vector;
begin
f(x,y,k1);
vspomk[0]:=y[0]+(h/2)*k1[0];
vspomk[1]:=y[1]+(h/2)*k1[1];
f(x+h/2,vspomk,k2);
vspomk[0]:=y[0]+(h/2)*k2[0];
vspomk[1]:=y[1]+(h/2)*k2[1];
f(x+h/2,vspomk,k3);
vspomk[0]:=y[0]+(h)*k3[0];
vspomk[1]:=y[1]+(h)*k3[1];
f(x+h,vspomk,k4);
yo[0]:=y[0]+(h/6)*(k1[0]+2*k2[0]+2*k3[0]+k4[0]);
yo[1]:=y[1]+(h/6)*(k1[1]+2*k2[1]+2*k3[1]+k4[1]);
end;

const
h:real=0.5;

{Двойной пересчет}
procedure dvoinoi_pereshet(x0,xn:real;yn:vector;var rezy:vector);
var
x:real;
kp:boolean;
y,y1,y2:vector;
begin
h:=h*2;
repeat
y[0]:=yn[0];
y[1]:=yn[1];
kp:=true;
x:=x0;
while (x<=xn) and (kp) do begin
      rk1h(x,y ,h  ,y1);
      rk1h(x,y ,h/2,y2);
      rk1h(x,y2,h/2,y2);
      if(abs(y1[0]-y2[0])>e) then kp:=false;
      y[0]:=y1[0];
      y[1]:=y1[1];
      x:=x+h;
      end;
{gotoXY(1,1);
writeln(h:5:12);}
h:=h/2;
until kp;
      rezy[0]:=y2[0];
      rezy[1]:=y2[1];
end;

function krae(y:vector):real; {краевая задача}
var
k:real;
yk,yr,yr1:vector;
a,b,c,h:real;
begin
a:=-5;
b:=5;
h:=1;
k:=a-h;
yk[0]:=y[0];
yk[1]:=a;
dvoinoi_pereshet(0,1,yk,yr);
{gotoxy(1,5);}
writeln('Пpестpелка k = ',k:5:7,' y =',yr[0]:5:7);
repeat
yr1[1]:=yr[1];yr1[0]:=yr[0];
k:=k+h;
if(k>b) then begin
        a:=a*2;
        b:=b*2;
        h:=h/2;
        k:=a;
        end;
yk[1]:=k;
dvoinoi_pereshet(0,1,yk,yr);
{gotoxy(1,5);}
writeln('Пpестpелка k = ',k:5:7,' y =',yr[0]:5:7);
until (yr[0]-y[1])*(yr1[0]-y[1])<0; {Ищем интервал, где ответ перешел через y[1]}

{MPD}
a:=k-h;
b:=k;
repeat     {MPD}
c:=(b+a)/2;
yk[1]:=a;
dvoinoi_pereshet(0,1,yk,yr);
yk[1]:=c;
dvoinoi_pereshet(0,1,yk,yr1);
if (yr[0]-y[1])*(yr1[0]-y[1])<0 then b:=c
                                else a:=c;
{gotoxy(1,5);  }
writeln('Пpестpелка k = ',((a+b)/2):5:7,' y =',yr[0]:5:7);
until abs(a-b)<e;

krae:=(a+b)/2;{Параметр K}
end;

const n=6;
var
c:array[1..n,1..n] of real;
d,m:array[1..n] of real;

procedure vichmatr;
var
i,j,k:integer;
h,del:real;
begin
h:=0.2;
for i:=2 to n-1 do
for j:=2 to n-1 do begin
    if(i=j)           then c[i,j]:=(h+h)/3;
    if(j=i+1)         then c[i,j]:=h/6;
    if(j=i-1)         then c[i,j]:=h/6;
    if(abs(i-j)>1)   then c[i,j]:=0;
end;
for i:=2 to n-1 do d[i]:=(mas1y[i+1]-mas1y[i])/h-(mas1y[i]-mas1y[i-1])/h;


    for k:=2 to n-1 do begin
    for i:=k+1 to n-1 do begin
    del:=c[i,k]/c[k,k];
    for j:=k to n-1 do c[i,j]:=c[i,j]-c[k,j]*del;
    d[i]:=d[i]-d[k]*del;
    end;
    end;

    for i:=1 to n-1 do m[i]:=0;

    for i:=n-1 downto 2 do  begin
    m[i]:=c[i,i];
     for j:=i+1 to n-1 do m[i]:=m[i]+c[i,j]*m[j];
    m[i]:=(d[i]/m[i]);
    end;

end;

function s(x:real):real;{Сплайн }
var
i:integer;
si:real;
begin
i:=trunc(x/0.2)+2;
si:=0;
if i=7 then i:=6;
{if i=1 then i:=2;
{if i=1 then i:=3;}
si:=m[i-1]*(mas1x[i]-x)*(mas1x[i]-x)*(mas1x[i]-x)/(6*0.2);
si:=si+m[i]*(x-mas1x[i-1])*(x-mas1x[i-1])*(x-mas1x[i-1])/(6*0.2);
si:=si+(mas1y[i-1]-(m[i-1]*(0.04/6)))*(mas1x[i]-x)/0.2;
si:=si+(mas1y[i]-m[i]*(0.04/6))*(x-mas1x[i-1])/0.2;
s:=si;
end;




procedure GetMaxAndMinY;
var
  x:   real;
  i:integer;
begin
  miny:=0;
  maxY:=0;
  x:=0;
  while x<=1 do begin
      if s(x) < minY then minY:=s(x);
      if s(x) > maxY then maxY:=s(x);
      x:=x+0.1;
      end;

   for i:=1 to 8 do
    begin
      if masy[i] < minY then minY:=masy[i];
      if masy[i] > maxY then maxY:=masy[i];
    end;
end;

function kx(x:real):integer;
begin
  kx:= round(639*x);
end;

function ky(y:real):integer; {Масштабировалка}
begin
  ky:= round(479*(maxy-y)/(maxy-miny));
end;

var
gm,gd:integer;
begin
clrscr;
ynach[0]:=1;
ynach[1]:=0.3;
k:=krae(ynach);
ynach[1]:=k;
writeln('K = ',k:10:4);
readln;
clrscr;
for i:=1 to 9 do begin
    dvoinoi_pereshet(0,masx[i],ynach,yr);
    masy[i]:=yr[0];
    writeln('      Мощность в точке: ',masx[i]:5:2,' = ',masy[i]*masy[i]:5:2);
end;
    readln;

x:=0;
for i:=1 to n do  begin
    dvoinoi_pereshet(0,x,ynach,yr);
    mas1x[i]:=x;
    mas1y[i]:=yr[0];
    x:=x+0.2;
end;
    vichmatr;

    clrscr;
    x:=0;
    writeln('x':6,'y(x)':20,'Знач. Сплайна':20);
    repeat
    dvoinoi_pereshet(0,x,ynach,yr);
    writeln('x = ',x:10:4,'   y(x) = ',yr[0]:5:4,'   S(x) = ',s(x):5:4);
    x:=x+0.05;
    until x>1;
    readln;

    gm:=detect;
    initgraph(gd,gm,'c:\bl\bp\bgi');

    GetMaxAndMinY;
    for i:=1 to 7 do
        circle(kx(masx[i]),ky(masy[i]),2);
 {
    for i:=1 to n do
        circle(kx(mas1x[i]),ky(mas1y[i]),2);
}
    x:=0;
    moveto(kx(x),ky(s(x)));
    repeat
    lineto(kx(x),ky(s(x)));
    x:=x+0.002;
    until x>1;

    repeat until keypressed;
    closegraph;
end.{Конец программы}

