{$N+}
Program kurs_vm;
Uses Crt,Graph;
const
  arg:array[0..5] of real=(0,0.2,0.4,0.6,0.8,1);
type
  mass=array[1..2] of real;
Var
  c:array [0..5,0..5] of real;
  d:array [1..4] of real;
  m,yy,alfa,betta:array[0..5] of real;
  s:string;
  fun:array[0..5] of real;
  x0,vopros,h,strel_y:real;
  i,j,n,gd,gm,ch:integer;
  y,y_zv:mass;

function spline(xx:real):real;
var
  k:integer;
  i:integer;
begin
  for i:=1 to 5  do
  if (xx>arg[i-1]) and (xx<arg[i]) then  k:=i;
  spline:=m[k-1]*sqr(arg[k]-xx)*(arg[k]-xx)/(6*h)+
          m[k]*sqr(xx-arg[k-1])*(xx-arg[k-1])/(6*h) +
          (fun[k-1]-m[k-1]*sqr(h)/6)*(arg[k]-xx)/h +
          (fun[k]-m[k]*sqr(h)/6)*(xx-arg[k-1])/h;
end;

function runge(xxx:real;strel_y:real;t:boolean):real;
var                  {При t=true вычисляется Y(x)}
  rab_x,h:real;      {При t=false вычисляется Y^(x)(сила тока)}
  i,j:integer;

function f(xx:real;yy:mass;t:boolean):double;
begin
    if not(t) then f:=yy[2]
            else f:=(xx*xx+yy[1])+x0*yy[2]-sin(yy[1]);
end;

begin
  h:=0.01;
  y[1]:=1;
  y[2]:=strel_y;
  rab_x:=0;
  while rab_x<=xxx+h do
  begin
    y_zv[1]:=y[1]+h*f(rab_x,y,false);
    y_zv[2]:=y[2]+h*f(rab_x,y,true);
    y[1]:=y[1]+h*(f(rab_x,y,false)+f(rab_x+h,y_zv,false))/2;
    y[2]:=y[2]+h*(f(rab_x,y,true)+f(rab_x+h,y_zv,true))/2;
    rab_x:=rab_x+h;
  end;
  if t then runge:=y[1] else runge:=y[2];
end;

function ff(x:real):real;
 begin
   ff:=2*x*x*x-sin(x)-3 ;
 end;

procedure pol_del;
var
  delta,x,y,c,a,b,e:real;
  n:integer;
begin
  e:=0.001;
  x:=0;y:=0;
  repeat
    y:=y+1;
    delta:=1/y;
    a:=x;
    b:=a+delta;
    while (a<>y) and (ff(a)*ff(b)>=0) do
    begin
      a:=a+delta;
      b:=b+delta;
    end;
  until ff(a)*ff(b)<0;
  n:=0;
  while abs((b-a)/2)>=e do
  begin
    c:=(b+a)/2;
    n:=n+1;
    if ff(a)*ff(c)<0 then b:=c
                     else a:=c;
  end;
  x0:=(b+a)/2;
  writeln('Минимальный положительный корень уровнения 2*x*x*x-sin(x)-3=0  x=',x0:9:8);
  readln;
end;

procedure method_strelb;
var
  x2,y2,rab_x,h:real;
begin
  h:=1;
  x2:=1;
  y2:=0.5;
  while abs(runge(x2,strel_y,false)-y2)>0.001 do
  begin
    if abs(runge(x2,strel_y,false)-y2)>abs(runge(x2,strel_y+h,false)-y2)
    then strel_y:=strel_y+h
    else
       if abs(runge(x2,strel_y,false)-y2)>abs(runge(x2,strel_y-h,false)-y2)
         then strel_y:=strel_y-h
         else h:=h/2;
  end;
end;

BEGIN
  clrscr;
  n:=5;
  pol_del;
  h:=0.2;
  strel_y:=random(100);
  method_strelb;
  for i:=0 to 5 do
  fun[i]:=runge(arg[i],strel_y,true);
  gd:=detect;
  InitGraph(gd,gm,'d:\tp\bgi\');
  line(50,getmaxy-50,getmaxx-50,getmaxy-50);
  line(50,50,50,getmaxy-50);
  for i:=0 to 10 do
  begin
    line(50+round(540*i/10),getmaxy-52,50+round(540*i/10),getmaxy-48);
    str(i/10:4:2,s);
    outtextxy(40+round(540*i/10),getmaxy-40,s);
    str((i+5)/10:4:2,s);
    line(48,getmaxy-50-(i+5)*40+150,52,getmaxy-50-(i+5)*40+150);
    outtextxy(0,getmaxy-50-(i+5)*40+150,s);
  end;
  line(round(50+0.18*540),round(getmaxy-50-spline(0.18)*400)+150,195,201+150);
  outtextxy(200,200+150,'Интерполяция сплайнами');
  vopros:=0.05;
  i:=1;
  while vopros<1 do
  begin
    if vopros<>arg[i] then
    begin
      putpixel(round(50+vopros*540),150+round(getmaxy-50-SPLINE(vopros)*400),white);
      inc(i);
    end
    else
      putpixel(round(50+vopros*540),150+round(getmaxy-50-SPLINE(vopros)*400),white);
    vopros:=vopros+0.01;
  end;
  readln;
  vopros:=0;
  ch:=0;
  setcolor(3);
  line(195,151,round(50+0.15*540),150+round(getmaxy-50-runge(0.15,strel_y,true)*400));
  outtextxy(200,150,'Метод Рунге-Кутта');
  while vopros<=1.05 do
  begin
    inc(ch);
    circle(round(50+vopros*540),150+round(getmaxy-50-runge(vopros,strel_y,true)*400),2);
    vopros:=vopros+0.05;
  end;
  setcolor(yellow);
  outtextxy(580,465,'x');
  outtextxy(10,10,'y(x)');
  readln;
  CloseGraph;
  vopros:=0;
  writeln('Вычисленные значения силы тока в точках I=dq/dt :');
  while vopros<=1.05 do
  begin
    writeln('t=',vopros:10:8,'   I(x)=',runge(vopros,strel_y,false):12:10);
    vopros:=vopros+0.05;
  end;
  readln;
END.