
program RGZ_VM5;
uses crt,Graph,antunit;

const
n=6;
h=0.2;

type
matr=array[1..n]of real;

var
qpv:string;
f:array[1..n]of real;
xn:array[1..n]of real;
  grDriver: Integer;
  grMode: Integer;
  ErrCode: Integer;
x,s,kk:real;
a,b,c,d:matr;
i,j,l,p,j1,i1:integer;
m:array[1..n-1,1..n-1]of real;
{-----------наименьший положит.корень уравнения------------------}
{function k:real;
const
h=0.01;
e=0.01;
var
x1,x0:real;
begin
x0:=0.831;
repeat
x0:=x0+e/10;
x1:=cos(4*x0*x0*x0*x0*x0-1);
until abs(x0-x1)<=e;
k:=x0;
end;

{--------Метод Эйлера реш-я диф. ур-я ----------------------
function yy(xx:real):real;
const
h=0.01;
e=0.01;
var
y,x:real;
function f(x,y:real):real;
begin
f:=(k-y*y)*cos(x)+2*y;
end;
begin
if xx=0 then y:=1
 else
  begin
   y:=1;x:=0;
   repeat
    y:=y+h*f(x,y);
    x:=x+h;
   until x>=xx;
  end;
yy:=y;
end;


{-------Метод  Симпсона,выч-я интеграла-------}
function s_n:real;
const
e=0.01;
a=0;
b=1;
var
h1:real;
s_n1,s_n2,s:real;
i0,i1,i2:real;
procedure aa;
var
i:integer;
begin
i0:=0;i1:=0;i2:=0;
for i:=0 to trunc((b-a)/h) do
begin
if (i=0) or (i=trunc(b-a)/h) then i0:=i0+runge4(i*0.01,0.01)*runge4(i*0.01,0.01)
 else
  if trunc(i/2)=i/2 then i2:=i2+runge4(i*0.01,0.01)*runge4(i*0.01,0.01)
   else
    i1:=i1+runge4(i*0.01,0.01)*runge4(i*0.01,0.01);
end;
s:=h/3*(i0+4*i1+2*i2);
end;

begin
repeat
aa;
s_n1:=s;
aa;
h1:=h/2;
s_n2:=s;
until (S_n1-S_N2)<=e*15;
s_n:=s_n2;
end;

{----Интерполяция сплайном------------}
function ki(x:real):real;
 begin
  l:=0;
  repeat inc(l) until x<=xn[l];
  ki:=a[l]+b[l]*(x-xn[l])+c[l]*(x-xn[l])*(x-xn[l])+d[l]*(x-xn[l])*(x-xn[l])*(x-xn[l]);
 end;
begin
clrscr;
writeln;
writeln('Наименьший положительный корень уравнения 4X^5-ARCCOS(X)-1=0 :X=',K:6:3);
writeln;
writeln('Результаты для построения графика');
writeln;
writeln('  X        Эйлер:Y(x)        Куб.интерп.:P(x)');
for i:=1 to 6 do
begin
xn[i]:=(i-1)*0.2;
f[i]:=runge4(xn[i],0.01);
end;

for i:=1 to n do
a[i]:=f[i];

for i:=2 to n-1 do
begin
for j:=1 to 3 do m[i,j]:=1;
m[i-1,i-1]:=4;
m[i-1,4]:=3*(f[i-1]-2*f[i]+f[i+1])/h/h;
end;
m[1,3]:=0;m[3,1]:=0;

{метод гаусса}
 l:=3;
  FOR J:=1 TO l-1 DO
   FOR I:=J+1 TO l DO
    BEGIN
     FOR J1:=J TO l DO
      IF m[J1,J]>m[j,j] THEN
       for i1:=j to l+1 do
        begin
	 S:=m[J,i1];
	 m[J,i1]:=m[J1,i1];
	 m[J1,i1]:=S
	END;
      IF m[J,J]=0 THEN
       BEGIN
	WRITEln('MATR VYIROJDENNAYA');
         halt;
       END;
      Kk:=m[I,J]/m[J,J];
      FOR J1:=J TO l+1 DO
       m[I,J1]:=m[I,J1]-m[J,J1]*Kk;
   END;
      IF m[l,l]=0 THEN
       BEGIN
	WRITE('MATR VYIROJDENNAYA');
	halt;
       END;
   c[4]:=m[3,4]/m[3,3];
   fOR I:=l-1 DOWNTO 1 DO
    BEGIN
     S:=0;
      FOR J:=I+1 TO l DO
       S:=S+c[1+j]*m[I,J];
       c[I+1]:=(m[I,l+1]-S)/m[I,I];
    END;

c[1]:=0;c[n]:=0;
for i:=2 to n-1 do
begin
b[i]:=(f[i]-f[i-1])/h-h*(c[i+1]+2*c[i])/3;
d[i]:=(c[i+1]-c[i])/h/3;
end;
b[n]:=(f[n]-f[n-1])/h;d[n]:=0;
for i:=0 to 10 do
writeln(' ',i/10:1:1,'         ',runge4(i/10,0.01):4:6,'      ',ki(i/10):4:6);writeln;
writeln;
writeln('Нажмите ENTER...');
readln;

  grDriver := Detect;
  InitGraph(grDriver, grMode,'l:\bgi');
  ErrCode := GraphResult;
  if ErrCode = grOk then
  begin  { Do graphics }

line(50,350,600,350);
line(50,350,50,50);
outtextxy(47,47,'^');
outtextxy(47,40,'Y');
outtextxy(605,340,'X');
outtextxy(600,347,'>');
for i:=0 to 5 do
begin
line(47,350-round(ki(i*0.2)*100),53,350-round(ki(i*0.2)*100));
str((ki(i*0.2)):3:1,qpv);
outtextxy(22,347-round(ki(i*0.2)*100),qpv);
line(50+round(i*0.2*550),353,50+round(i*0.2*550),347);
str((i*0.2):3:1,qpv);
outtextxy(40+round(i*0.2*550),353,qpv);
end;
moveto(50,round(350-ki(0)*100));
for i:=0 to 4 do
 begin
 setcolor(white);
 circle(50+round((i)*550*0.2),round(350-ki((i)*0.2)*100),2);
 moveto(50+round((i)*550*0.2),round(350-ki((i)*0.2)*100));
 for j:=0 to 5 do
  begin
  lineto(50+round((i+j/5)*550*0.2),350-round(ki((i+j/5)*0.2)*100));
  end;
 moveto(50+round((i)*550*0.2),round(350-ki((i)*0.2)*100));
 setcolor(red);
 for j:=0 to 5 do
  begin
  lineto(50+round((i+j/5)*550*0.2),350-round(runge4((i+j/5)*0.2,0.01)*100));
  end;
 end;
 setcolor(white);
 circle(50+round(550),round(350-ki(1)*100),2);
 setcolor(red);
 outtextxy(50,400,'red-Y(x)');
 setcolor(white);
 outtextxy(50,410,'white-spline');
 outtextxy(50,420,'Wait...');
 str(s_n:9:6,qpv);
 setcolor(0);
 outtextxy(50,420,'Wait...');
 setcolor(green);
 outtextxy(50,420,'Q='+qpv);
 setcolor(blue);
 outtextxy(50,430,'ENTER...');
    Readln;
    CloseGraph;
  end
  else
    Writeln('Graphics error:', GraphErrorMsg(ErrCode));
    writeln
end.