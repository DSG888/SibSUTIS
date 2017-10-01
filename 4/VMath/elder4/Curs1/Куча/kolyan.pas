program Kurs_K;
uses crt,graph;
const

n=1;
a=0.0;
b=1.0;
ya=1.0;
yb=0.5;
mn=5; {степень многочлена Ньютона}
sh=0.001; {шаг построения графика}
eps=0.001;
var
d:array[0..mn,0..mn]of real;{конечные разности}
shx:real;
xg,yg:array[0..mn]of real;
xdop,ydop:array [0..10]of real;
gd,gm:integer;
k:real;


function g(y__:real;x:real;vy:array of real):real;
begin
g:=y__-sin(y__)-sin(vy[0])-2*vy[1]-k*exp(-2*x);
end;


function sg(x:real):integer;
begin
if x<0 then sg:=-1;
if x>0 then sg:=1;
if x=0 then sg:=0;
end;

function k1(x:real):real;
begin
k1:=x*x*x*x*x-sin(x)-1;
end;

function k2:real;
var
shag,p,r,center:real;
i:real;
flag:byte;
begin
p:=0.0;
r:=0.7;
shag:=r/2;

repeat
flag:=0;
r:=r*2;
shag:=shag/2;
i:=-1;
  repeat
  i:=i+1;

    if sg(k1(p+shag*i))<>sg(k1(p+shag*(i+1))) then
      begin
      r:=p+shag*(i+1);
      p:=p+shag*i;
      flag:=1;
      end;
  until (flag=1) or ((p+shag*i)>(r-shag/5));
until flag=1;
{mpd}
repeat
center:=(p+r)/2;
if sg(k1(center))=sg(k1(p)) then p:=center;
if sg(k1(center))=sg(k1(r)) then r:=center;

until (abs(p-r)<eps)or(k1(center)=0);
k2:=center;
end;


function f__(x:real;vy:array of real):real;
var
shag,p,r,center:real;
i:real;
flag:byte;
begin
p:=-13.0;
r:=13.0;
shag:=(r-p)/2;

repeat
flag:=0;
p:=p*2;
r:=r*2;
shag:=shag/2;
i:=-1;
  repeat
  i:=i+1;

    if sg(g(p+shag*i,x,vy))<>sg(g(p+shag*(i+1),x,vy)) then
      begin
      r:=p+shag*(i+1);
      p:=p+shag*i;
      flag:=1;
      end;
  until (flag=1) or ((p+shag*i)>(r-shag/5));
until flag=1;
{mpd}
repeat
center:=(p+r)/2;
if sg(g(center,x,vy))=sg(g(p,x,vy)) then p:=center;
if sg(g(center,x,vy))=sg(g(r,x,vy)) then r:=center;

until (abs(p-r)<eps)or(g(center,x,vy)=0);
f__:=center;
end;


procedure f(var vy:array of real;tochka:real);
{Рунге-Кутт}
var
y,y1,y1zvd2,vf,vfzvd2:array[0..n]of real;
i,j,w,kd:integer;
x,h,max,otrezok,nr:real;
vse1,vse2:array [1..4*512,0..n] of real;

begin
otrezok:=tochka-a;
kd:=1;
for i:=0 to n do
  begin
  vse1[1,i]:=0;
  vse1[2,i]:=0;
  end;

repeat
kd:=kd*2;
h:=otrezok/kd;
x:=a;
for i:=0 to n do
  y[i]:=vy[i];

  for w:=1 to kd do
      begin


  for i:=0 to n-1 do
    vF[i]:=Y[i+1];
  vF[n]:=f__(x,Y);

  for i:=0 to n do
    y1zvd2[i]:=y[i]+h/2*vF[i];

  for i:=0 to n-1 do
    vFzvd2[i]:=y1zvd2[i+1];
  vFzvd2[n]:=f__(x+h/2,y1zvd2);

  for i:=0 to n do
    begin
    y1[i]:=y[i]+h*vFzvd2[i];
    y[i]:=y1[i];
    vse2[w,i]:=y1[i];
    end;
      x:=x+h;
  end;

  max:=0;
  for i:=1 to round(kd/2) do
    begin
    nr:=0;
    for j:=0 to n do
       begin
       nr:=nr+abs( vse1[i,j]-vse2[2*i,j]);
       end;
    if nr>max then max:=nr;
    end;

  for i:=1 to kd do
    for j:=0 to n do
       vse1[i,j]:=vse2[i,j];
until max<eps;

for i:=0 to n do
  vy[i]:=y1[i];
{write(#7);}
end;

function Pn(x:real):real;
var
 i:integer;
 s,q0,q,fac:real;

begin
s:=d[0,0];
fac:=1;
q0:=(x-a)/shx;
q:=q0;
 for i:=1 to mn do
   begin
   fac:=fac*i;
   s:=s+(d[0,i])*q/fac;
   q:=q*(q0-i);
   end;

Pn:=s;
end;


procedure Newton; {интерполяция по первой формуле Ньютона}


var
i,j:integer;
r:real;
ymax,ymin,kx,ky:real;


Begin

shx:=xg[1]-xg[0];

for i:=0 to mn do
  d[i,0]:=yg[i];

for i:=1 to mn do
  for j:=0 to mn-i do
    d[j,i]:=d[j+1,i-1]-d[j,i-1];


kx:=639/(b-a);
ymin:=yg[0];
ymax:=yg[0];
r:=a;
repeat
r:=r+sh;
if Pn(r)<ymin then ymin:=Pn(r);
if Pn(r)>ymax then ymax:=Pn(r);
until r>=b;
ky:=479/(ymax-ymin);
initgraph(gd,gm,'c:\tp\bgi');

setcolor(14);
for i:=0 to mn do
  begin
  circle(round(kx*(xg[i]-a)),round(479-ky*(yg[i]-ymin)),3);
  circle(round(kx*(xg[i]-a)),round(479-ky*(yg[i]-ymin)),2);
  circle(round(kx*(xg[i]-a)),round(479-ky*(yg[i]-ymin)),1);
  end;


setcolor(1);
moveto(round(kx*(a-a)),round(479-ky*(Pn(a)-ymin)));
r:=a;
repeat
r:=r+sh;
lineto(round(kx*(r-a)),round(479-ky*(Pn(r)-ymin)));
until r>=b;

readkey;
closegraph;
end;





var
middle,q,r,step:real;
ybp,ybk,ybmiddle:real;
i:integer;
j:real;
flag:byte;
vY:array[0..n]of real;

begin
k:=k2;

clrscr;
textcolor(7);
writeln(' Поиск значения производной в точке а');

q:=-0.45;
r:=0.45;
step:=(r-q)/2;
write(' обстрел ') ;
repeat
write('.');
q:=q*2;
r:=r*2;
step:=step/2;

j:=-1;
flag:=0;
  repeat
  j:=j+1;

  vy[0]:=ya;
  vy[1]:=q+step*j;
  f(vy,b);
  ybp:=vy[0];     { значение производной в точке b }


  vy[0]:=ya;
  vy[1]:=q+step*(j+1);
  f(vy,b);
  ybk:=vy[0];     { значение производной в точке b }

    if sg(ybp-yb)<>sg(ybk-yb) then
      begin
      r:=q+step*(j+1);
      q:=q+step*j;
      flag:=1;
      end;
  until (flag=1) or ((q+step*j)>(r-step/5));
until flag=1;


writeln;
writeln('`~=',q:5:5);
write('  применение МПД');
repeat
write(#219);
middle:=(q+r)/2;

  vy[0]:=ya;
  vy[1]:=q;
  f(vy,b);
  ybp:=vy[0];          {значение в точке b }

  vy[0]:=ya;
  vy[1]:=r;
  f(vy,b);
  ybk:=vy[0];          {значение в точке b }

  vy[0]:=ya;
  vy[1]:=middle;
  f(vy,b);
  ybmiddle:=vy[0];

if sg(ybmiddle-yb)=sg(ybp-yb) then q:=middle;
if sg(ybmiddle-yb)=sg(ybk-yb) then r:=middle;
until ((abs(q-r)<eps)or((ybmiddle-yb)=0));
writeln;
textcolor(7);
r:=middle;
writeln('f`(a)=',r:5:5);
for i:=1 to 9 do
   begin
   xdop[i]:=0.1*i+0.02;
   vy[0]:=ya;
   vy[1]:=r;
   f(vy,xdop[i]);
   ydop[i]:=vy[0];
   writeln(xdop[i]:5:5,'  ',ydop[i]:5:5);
   end;
writeln('для Ньютона:');
for i:=0 to mn do
   begin
   xg[i]:=0.2*i;
   vy[0]:=ya;
   vy[1]:=r;
   f(vy,xg[i]);
   yg[i]:=vy[0];
   writeln(xg[i]:5:5,'  ',yg[i]:5:5);
   end;
writeln('PRESS ANY KEY');
readkey;
Newton;

for i:=0 to 20 do
   begin
   j:=i*5/100;
   vy[0]:=ya;
   vy[1]:=r;
   f(vy,j);
   writeln(j:2:2,'  ',vy[0]:5:5,'    ',pn(j):5:5);
   end;
writeln('PRESS ANY KEY');
readkey;
end.














