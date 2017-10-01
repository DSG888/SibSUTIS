{$M 64000,0,655360}
program course_project;
uses crt,graph;
const
  h_g=0.2;
var
  ss:string;
  h,x0,x_rab,y_rab,k:real;
  grDriver,grMode,ErrCode,ch,i,j,r,z:integer;
  c:array [0..5,0..5] of real;
  d:array [1..4] of real;
  m,x,y,alfa,betta:array[0..5] of real;
procedure polushka;
var
  delta,x,y,c,a,b,e:real;
  n:integer;
function f(x:real):real;
begin
  f:=2*x*x*x-sin(x)-3;
end;
begin
  writeln('  Решение нелинейного уровнения 2*x*x*x - sin(x) - 3=0 :');
  e:=0.00001;
  x:=0;
  y:=0;
  repeat
    y:=y+1;
    delta:=1/y;
    a:=x;
    b:=a+delta;
    while (b<y) and (f(a)*f(b)>=0) do
    begin
      a:=a+delta;
      b:=b+delta;
    end;
  until f(a)*f(b)<0;
  n:=0;
  while abs((b-a)/2)>=e do
  begin
    c:=(b+a)/2;
    n:=n+1;
    if f(a)*f(c)<0 then b:=c
                   else a:=c;
  end;
  x0:=(b+a)/2;
  writeln(' ':3,'x=',x0:9:8);
  writeln(' ':3,'Число шагов',n:3);
  readln;
end;
procedure eiler;
var
  chet:integer;
  y1_rab:real;
function yy(x:real;y:real):real;
begin
  yy:=cos(y/(x+k))+x;
end;
begin
  h:=0.0125;
  for i:=0 to 5 do
  x[i]:=i/5;
  y[0]:=k;
  x_rab:=0;
  y_rab:=k;
  y1_rab:=k;
  r:=1;
  while chet<>0 do
  begin
   x_rab:=0;
  y_rab:=k;
  y1_rab:=k;
  r:=1;
  chet:=0;
  repeat
    y_rab:=y_rab+h*yy(x_rab,y_rab);
    y1_rab:=y1_rab+h*yy(x_rab-h/2,y1_rab)/2;
    y1_rab:=y1_rab+h*yy(x_rab,y1_rab)/2;
    x_rab:=x_rab+h;
    if abs(y_rab-y1_rab)>0.011 then chet:=chet+1;
    if (x_rab>x[r]-0.01) and (x_rab<x[r]+0.1) then
    begin
      y[r]:=y_rab;
      inc(r);
    end;
  until x_rab>=1;
    h:=h/2;
 end;
writeln('   В ходе вычислений достигнута точность 0.01.При этом шаг получился',
         h:6:5);
end;
procedure eiler1;
function yy(x:real;y:real):real;
begin
  yy:=cos(y/(x+k))+x;
end;
begin
  setcolor(yellow);
  x_rab:=0;
  y_rab:=k;
  r:=1;
  repeat
    y_rab:=y_rab+h*yy(x_rab,y_rab);
    x_rab:=x_rab+h;
    putpixel(50+round(500*x_rab),getmaxy-40-round(150*y_rab),yellow);
  until x_rab>=1;
end;
procedure pred_spline;
begin
  for i:=1 to 4 do
  d[i]:=(y[i+1]-y[i])/h_g-(y[i]-y[i-1])/h_g;
  for i:=1 to 4 do
  for j:=1 to 4 do
  if j=i-1 then c[i,j]:=h_g/6 else
         if j=i then c[i,j]:=2*h_g/3   else
               if j=i+1 then c[i,j]:=h_g/6
  else      c[i,j]:=0;
  c[1,0]:=0;
  alfa[0]:=0;
  betta[0]:=0;
  for i:=1 to 4 do
  begin
    alfa[i]:=-c[i,i+1]/(c[i,i]+c[i,i-1]*alfa[i-1]);
    betta[i]:=(d[i]-c[i,i-1]*betta[i-1])/(c[i,i]+c[i,i-1]*alfa[i-1]);
  end;
  m[5]:=0;
  m[0]:=0;
  for i:=4 downto 1 do
  m[i]:=alfa[i]*m[i+1]+betta[i];
end;
function spline(xx:real):real;
var
  k:integer;
begin
  for i:=1 to 5 do if (xx>x[i-1]) and (xx<x[i]) then  k:=i;
    spline:=m[k-1]*sqr(x[k]-xx)*(x[k]-xx)/(6*h_g) +
    m[k]*sqr(xx-x[k-1])*(xx-x[k-1])/(6*h_g) +
    (y[k-1]-m[k-1]*sqr(h_g)/6)*(x[k]-xx)/h_g +
    (y[k]-m[k]*sqr(h_g)/6)*(xx-x[k-1])/h_g;
end;
procedure proizv;
begin
end;
begin
  clrscr;
  polushka;
  k:=x0;
  writeln('  Решение диф. уровнения Y`=cos(y/(k+x))+x');
  writeln(' ':3,'при Y(0)=k  методом Эйлера при k=x :');
  eiler;
  for i:=0 to 5 do
  writeln(' ':3,'x[',i,']=',x[i]:6:2,'   y[',i,']=',y[i]:10:8);
  readln;
  pred_spline;
  readln;
  grDriver := Detect;
  InitGraph(grDriver, grMode,'d:/work/bp/myprog/vova');
  ErrCode := GraphResult;
  if ErrCode = grOk then
  begin
    outtextxy(150,40,' - сплайн S(x).    Точки - функция Y(x).');
    circle(140,43,3);
    line(50,getmaxy-40,getmaxx-40,getmaxy-40);
    line(50,40,50,getmaxy-40);
    line(50,20,53,45);
    line(getmaxx-20,getmaxy-40,getmaxx-45,getmaxy-43);
    line(getmaxx-20,getmaxy-40,getmaxx-45,getmaxy-37);
    line(50,20,53,45);
    line(50,20,47,45);
    setlinestyle(UserBitLn, $C3, 3);
    for j:=1 to 5 do
    begin
      line(50+round(500*x[j]),getmaxy-40-round(150*y[j]),50,getmaxy-40-round(150*y[j]));
      line(50+round(500*x[j]),getmaxy-40-round(150*y[j]),50+round(500*x[j]),getmaxy-40);
      circle(50,getmaxy-40-round(150*y[j]),2);
      circle(50+j*100,getmaxy-40,2);
      str(j/5:6:2,ss);
      outtextxy(20+round(500*x[j]),getmaxy-30,ss);
      str(y[j]:6:2,ss);
      outtextxy(0,getmaxy-40-round(150*y[j]),ss);
    end;
    outtextxy(40,getmaxy-30,'0');
    outtextxy(20,20,'OY');
    outtextxy(getmaxx-30,getmaxy-30,'OX');
    eiler1;
    z:=1;
    setcolor(red);
    setlinestyle(1,1,1);
    x0:=h;
    while x0<1 do
    begin
      if (x0>x[z]-0.001)  and (x0<x[z]+0.001) then
      begin
        circle(50+round(500*x0),getmaxy-40-round(150*y[z]),3);
        inc(z);
      end
     else  circle(50+round(500*x0),getmaxy-40-round(150*spline(x0)),3);
    x0:=x0+h;
    end;
    Readln;
    CloseGraph;
  end
  else
    Writeln('Graphics error:', GraphErrorMsg(ErrCode));
end.



