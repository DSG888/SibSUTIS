program kur_pro;
 uses crt,graph;
  const
   e=0.0001;
   n=8; m=5;
   x:array [1..n] of real=(0.12,0.32,0.42,0.52,0.62,0.72,0.82,0.92);
   a:array [0..m] of real=(0,0.2,0.4,0.6,0.8,1.0);
  type
   mas=array [1..2] of real;
   matr=array [1..n] of real;
   mask=array [1..2,1..4] of real;
  var
   dyg,i,graphcurent_x,graphcurent_y:integer;
   q,h,curent_y,curent_yy:real;
   res,r:matr;
   y:mas;
   dy:array [0..m] of real;

  function fun(x:real;y:mas;i:integer):real;
   begin
    case i of
     1: fun:=y[1];
     2: fun:=x+sin(1.4*Y[1])-2.3*Sqr(Y[2]);
    end;
   end;

  procedure do_k(x,h:real;y:mas;var k:mask);
   var
    i:integer;
    yy:mas;
   begin
    for i:=1 to 2 do begin
     yy:=y;
     k[i,1]:=fun(x,yy,i);
     yy[i]:=y[i]+(h/2)*k[i,1];
     k[i,2]:=fun(x+(h/2),yy,i);
     yy[i]:=y[i]+(h/2)*k[i,2];
     k[i,3]:=fun(x+(h/2),yy,i);
     yy[i]:=y[i]+h*k[i,3];
     k[i,4]:=fun(x+h,yy,i);
    end;
   end;

  function mrk(xx,h:real):real;
   var
    y:mas;
    i:integer;
    x:real;
    k:mask;
   begin
    x:=0;
    y[1]:=1;
    y[2]:=5;
    while x<=xx do begin
     do_k(x,h,y,k);
     for i:=1 to 2 do y[i]:=y[i]+(h/6)*(k[i,1]+2*k[i,2]+2*k[i,3]+k[i,4]);
     x:=x+h;
    end;
    mrk:=Y[1];
   end;

  function mrk1(x,h:real):real;
   var
    d1,d2:real;
   begin
    repeat
     d1:=mrk(x,h);
     d2:=mrk(x,h/2);
     h:=h/2;
    until abs(d1-d2)<=e;
    mrk1:=d1;
   end;

  procedure do_dy;
   var
    t:array [0..m] of real;
    i,j:integer;
   begin
    writeln('                            МЕТОД НЬЮТОНА');
    writeln;
    writeln('               Значение функции в узлах интерполяции');
    writeln;
    for i:=0 to m do begin
     t[i]:=mrk1(a[i],h);
     writeln(t[i]);
    end;
    dy[0]:=t[0];
    for i:=1 to m do begin
     for j:=0 to m-i do begin
      t[j]:=t[j+1]-t[j];
     end;
     dy[i]:=t[0];
    end;
   end;

  procedure made_q(xxx:real);
   begin
    q:=(xxx-a[0])/h;
   end;

  function p(xx:real):real;
   var
    ch,zn:real;
    i,j:integer;
    p1:real;
   begin
    made_q(xx);
    p1:=mrk1(a[0],h);
    for i:=1 to m do begin
     ch:=1; zn:=1;
     for j:=0 to i-1 do ch:=ch*(q-j);
     for j:=1 to i do zn:=zn*j;
     p1:=p1+dy[i]*ch/zn;
    end;
    p:=p1;
   end;

  procedure grafik;
   var
    i:integer;
    st:string;
    grDriver : Integer;
    grMode   : Integer;
   begin
    grDriver := Detect;
    InitGraph(grDriver,grMode,'d:\bp\bgi');
    dyg:=round(GetMaxY/17);
    line(20,GetMaxY-20,620,GetMaxY-20); { OX }
    line(30,GetMaxY-10,30,10);  { OY }
    line(620,GetMaxY-20,600,GetMaxY-17);
    line(620,GetMaxY-20,600,GetMaxY-23);
    line(30,10,27,40);
    line(30,10,33,40);
    for i:=0 to 10 do begin  { Разметка по OX }
     line((i+1)*50-20,GetMaxY-18,(i+1)*50-20,GetMaxY-22);
     str(i/10:3:1,st);
     OutTextXY((i+1)*50-20,GetMaxY-12,st);
   end;
   for i:=1 to 15 do begin { Разметка по OY }
    line(28,GetMaxY-20-(16-i)*dyg,32,GetMaxY-20-(16-i)*dyg);
    str(i/5:3:1,st);
    OutTextXY(0,GetMaxY-23-i*dyg,st);
   end;
   OutTextXY(10,20,'Y');
   OutTextXY(GetMaxX-60,GetMaxY-18,'X');
  end;


 begin
  clrscr;
  h:=0.02;
  writeln('                        МЕТОД РУНГЕ - КУТТА');
  writeln;
  writeln('                   Значения мощности (в точках):');
  writeln;
  for i:=1 to n do begin
   res[i]:=mrk1(x[i],h);
   writeln('X[',i,']=',X[i]:1:2,'    y(',X[i]:1:2,')^2=',Sqr(res[i]));
  end;
  readln;
  clrscr;
  do_dy;
  h:=0.2;
  writeln;
  writeln('Значение многочлена (в точках):');
  writeln;
  for i:=1 to n do
   writeln('X[',i,']=',X[i]:1:2,'    y(',X[i]:1:2,')=',p(x[i]));
  readln;
  clrscr;
  writeln('                   Разность между значениями функции,');
  writeln('          вычисленными методами Рунге-Кутта и Ньютона в точках:');
  writeln;
  for i:=1 to n do begin
   r[i]:=p(x[i])-res[i];
   writeln('X[',i,']=',X[i]:1:2,'    r(',X[i]:1:2,')=',r[i]);
  end;
  readln;
  clrscr;
  grafik;
  for i:=0 to 80 do begin
   graphcurent_x:=round(i*6.25+30);
   curent_y:=p(i/80);
   graphcurent_y:=round(GetMaxY-(i+20)-curent_y*3.3*dyg-48);
   Setcolor(3);
   Line(graphcurent_x,graphcurent_y,7+graphcurent_x,-2+graphcurent_y);
   if i/16=round(i/16) then circle(graphcurent_x,graphcurent_y,3);
  end;
  for i:=0 to 80 do begin
   graphcurent_x:=round(i*6.25+30);
   curent_y:=mrk1(i/80,0.02);
   graphcurent_y:=round(GetMaxY-(i+20)-curent_y*3.3*dyg-48);
   Setcolor(4);
   Line(graphcurent_x,graphcurent_y,7+graphcurent_x,-4+graphcurent_y);
   if i/16=round(i/16) then circle(graphcurent_x,graphcurent_y,3);
  end;
  readln;
 end.