PROGRAM AS_Kurs_VM;

Uses Crt,graph,Antunit;

Var  l:real;

Type
     vector = array [0..9] of real;
     matr3 =array [1..9,1..9] of real;
     typ = array [0..10] of real;
Var
 x,y,yy:typ;
 M,d,h:vector;
 C:matr3;q,hh:real;
 vopros,gd,gm,i,j,n:integer;
 dy,mm:array [0..5] of real;

{---------Метод Ньютона---------
 Procedure do_dy;
  Var
   t:array [0..5] of real;
   i,j:integer;
  Begin
    writeln('----------------------- Метод Ньютона ---------------------------');
    writeln;
    For i:=0 to 5 do t[i]:=y[i];
     dy[0]:=t[0];
    For i:=1 to 5 do
     Begin
      for j:=0 to 5-i do t[j]:=t[j+1]-t[j];
      dy[i]:=t[0];
     End;
  End;                          }
   procedure pred_spline;
   var dd,alfa,betta:array[0..5] of real;
       cc:array[0..4,0..4] of real;
       i,j:integer;
  begin
  for i:=1 to 4 do
  dd[i]:=(yy[i+1]-yy[i])/hh-(yy[i]-yy[i-1])/hh;
  for i:=1 to 4 do
  for j:=1 to 4 do
  if j=i-1 then cc[i,j]:=hh/6 else
         if j=i then cc[i,j]:=2*hh/3   else
               if j=i+1 then cc[i,j]:=hh/6
  else      cc[i,j]:=0;
  cc[1,0]:=0;
  alfa[0]:=0;
  betta[0]:=0;
  for i:=1 to 4 do
  begin
    alfa[i]:=-cc[i,i+1]/(cc[i,i]+cc[i,i-1]*alfa[i-1]);
    betta[i]:=(dd[i]-cc[i,i-1]*betta[i-1])/(cc[i,i]+cc[i,i-1]*alfa[i-1]);
  end;

  mm[5]:=0;
  mm[0]:=0;
  for i:=4 downto 1 do
  mm[i]:=alfa[i]*mm[i+1]+betta[i];
  dy[i]:=yy[i];
end;
function spline(xx:real):real;
var
  k:integer;
  i:integer;
begin
  for i:=1 to 5  do if (xx>x[i-1]) and (xx<x[i]) then  k:=i;
    spline:=mm[k-1]*sqr(x[k]-xx)*(x[k]-xx)/(6*hh) +
    mm[k]*sqr(xx-x[k-1])*(xx-x[k-1])/(6*hh) +
    (yy[k-1]-mm[k-1]*sqr(hh)/6)*(x[k]-xx)/hh +
    (yy[k]-mm[k]*sqr(hh)/6)*(xx-x[k-1])/hh;
end;



{ Procedure made_q(xxxx:real);
  Begin
   q:=(xxxx-x[0])/hh;
  End;

 Function p(xx:real):real;
  Var
   ch,zn:real;
   i,j:integer;
   p1:real;
  Begin
   made_q(xx);
   p1:=y[0];
   For i:=1 to 5 do
    Begin
     ch:=1; zn:=1;
     For j:=0 to i-1 do ch:=ch*(q-j);
     For j:=1 to i do zn:=zn*j;
     p1:=p1+dy[i]*ch/zn;
    End;
    p:=p1;
  End;}

{-------- Процедура нахождения интеграла --------}

 Procedure Integral;
  Type
   typ=array [1..10] of real;
  Var
   y:typ;
   x,b,a,s,ipred,inew,h,result:real;
   i,j,gd,gm,n:integer;
  Label 1;

  Function myfun(arg:real):real;
   Begin
    myfun:=sqr(runge4(arg,0.1));  {Y^2 }
   End;                           {ВЫЗЫВАЕМ ЗНАЧЕНИЯ Y из Рунге-Кутта}

{-------- Метод Симпcона --------}
 Function Integ(h:real):real;
   Const
    a=0;
    b=1;
   Var
    i,k:integer;
    OddEl,ParEl:real;
   Begin
    k:=round((b-a)/(h));
    i:=1;
    OddEl:=0;
    While i<=k do
     Begin
      OddEl:=OddEl+MyFun(a+i*h);
      i:=i+2;
     End;
     i:=2;
     ParEl:=0;
     While i<=k-1 do
      Begin
       ParEl:=ParEl+MyFun(a+i*h);
       i:=i+2;
      End;
     Integ:=(h/3)*(MyFun(a)+MyFun(b)+4*OddEl+2*ParEl);
    End;

{ пока не достигнет точности}
 Procedure Computations;
  Const
   e=1e-4;
  Var
   h,i1,i2:real;
  Begin
   h:=0.01;
   Repeat
    h:=h/2;
    i1:=Integ(h);
    i2:=Integ(h/2);
   until abs(i1-i2)<15*e;
   writeln;
   writeln;
   writeln('Количество теплоты:');
   writeln( '                Q = ',i2:8:8);
   writeln;
  End;

  Begin
   clrscr;
   Computations;
{   readkey;}
  End;
{-------- Основная программа --------}
BEGIN
 Horda;
 write;
 writeln('Расчет для задачи  Коши :  Y^=1-Sin(kx+y)+y/(2+x)');
 writeln(' ':27,'Y(0) = 0');writeln;
 writeln('----------------------- Метод Рунге-Кутта -----------------------');
 writeln;
 yy[0]:=0;
 writeln('При x=0.0  y(x)= ',y[0]:1:8);
 l:=0;
 i:=0;
 While l<1 do
  Begin
   l:=l+0.2;
   i:=i+1;
   yy[i]:=runge4(l,0.1);
   writeln('При x=',l:1:1,'  y(x)h=',{y[i],}(Runge4(l,0.1)):1:8,' y(x)h/2=',runge4(l,0.05):1:8);
  end;
  readln;
  n:=5;
  x[0]:=0;
  x[1]:=0.2;
  x[2]:=0.4;
  x[3]:=0.6;
  x[4]:=0.8;
  x[5]:=1;
  hh:=0.2;

  pred_spline;
  l:=0;
  while l<=1 do
   begin
    writeln('При x=',l:1:1,'  y(x)=',spline(l):8:8);
    l:=l+0.2;
   end;
  Readln;
  Integral;
  InitGraph(gd,gm,'');
  line(0,479,600,479);
  line(0,0,0,480);
    for i:=0 to n do begin
    circle(round(x[i]*600),479-round(y[i]*550),1);
    line(round(x[i]*600),0,round(x[i]*600),479);
    end;
    for j:=0 to n do
    for i:=1 to 640 do putpixel(i,479-round(y[j]*550),15);
    for i:=0 to n do
    circle(round(x[i]*600),479-round(y[i]*550),2);
    l:=0;
 While l<1 do
  Begin
   putpixel(round(l*600),479-round(spline(l)*550),12);{график Ньютона}
   putpixel(round(l*600),479-round(runge4(l,0.01)*550),11);{график Рунге-Кутта}
   l:=l+0.001;
  End;

    setcolor(yellow);
    outtextxy(625,467,'X  ');   outtextxy(10,10,'Y(x)   ');
    outtextxy(5,248,'0.42645'); outtextxy(7,468,'0');
    outtextxy(5,265,'0.39569'); outtextxy(124,468,'0.2');
    outtextxy(5,290,'0.35163'); outtextxy(244,468,'0.4');
    outtextxy(5,329,'0.28071'); outtextxy(364,468,'0.6');
    outtextxy(5,390,'0.16330'); outtextxy(484,468,'0.8');
                                outtextxy(604,468,'1');
    Setcolor(12);
    outtextxy(450,410,'График Ньютона');
    Setcolor(11);
    outtextxy(450,400,'График Рунге-Кутта');
    readln;
    CloseGraph;
END.
