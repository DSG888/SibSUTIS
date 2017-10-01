Program kurs_vm;
{$N+}
Uses Crt,Graph;
const
  arg:array[0..5] of real=(0,0.2,0.4,0.6,0.8,1);
  eps=0.1;
type
  mass=array[1..2] of real;{}
Var c: array[0..5,0..5] of real;
  s:string;
  fun:array[0..5] of real;
  x0,vopros,h,h_run,strel_y:real;
  i,j,n,gd,gm,ch,n_run:integer;
  y,y_zv:mass;

function fakterial(nn:integer):integer;{интеpполяций }
begin
  if nn in [0..1] then fakterial:=1
  else fakterial:=nn*fakterial(nn-1);
end;

function Interpol(vopros:real):real;
function delta(nn:integer):real;
var
  j:integer;
  temp:real;
begin
  temp:=0;
  for j:=0 to nn do
  if j mod 2=0 then
  temp:=temp+(fakterial(nn)/(fakterial(j)*fakterial(nn-j)))*fun[n-j]
  else temp:=temp-(fakterial(nn)/(fakterial(j)*fakterial(nn-j)))*fun[n-j];
  delta:=temp;
end;

function q(nn:integer):real;
var
  j:integer;temp:real;
begin
  temp:=1;
  for j:=1 to nn do
  temp:=temp*(((vopros-arg[n])/h)+j-1);
  q:=temp;
end;

var
  temp:real;
  j:integer;
Begin
  temp:=fun[n];
  for j:=2 to n do
  temp:=temp+(q(j-1)*delta(j-1))/fakterial(j-1);
  interpol:=temp;
End;
function MyFun(x:real):real;
  begin
     MyFun:=interpol(x)*interpol(x);
  end;
function integral(h:real):real;
  const
      a=0; b=1;
  var
     i,k:integer;
     OddE1,ParE1:real;
  begin
     k:=round((b-a)/(h));
     i:=1;
     OddE1:=0;{сумма нечетных}
     while i<=k do
      begin
       OddE1:=OddE1+MyFun(a+i*h);
       i:=i+2;
      end;
    i:=2;
    ParE1:=0;
    while i<=k-1 do
     begin
      ParE1:=ParE1+MyFun(a+i*h);{сумма четных}
      i:=i+2;
     end;
    integral:=(h/3)*(MyFun(a)+MyFun(b)+4*OddE1+2*ParE1);
  end;


function f(xx:real;yy:mass;t:boolean):double;{втоpая пpоизводная}
begin
  if not (t) then f:=yy[2]  {1 пpоизв}

              else f:=(sin(xx)+2*yy[2]+x0*exp(-2*xx));{2 пpоизв}
end;

function runge(xxx:real;strel_y:real;t:boolean;h:real):real;
var
  rab_x:real;
  i,j:integer;


begin
  y[1]:=1;      {функц}
  y[2]:=strel_y; {1 пpоизв}
  rab_x:=0;
  while rab_x<=xxx+h do
  begin
    y_zv[1]:=y[1]+h*f(rab_x,y,false)/2;  {7.3}
    y_zv[2]:=y[2]+h*f(rab_x,y,true)/2;
    y[1]:=y[1]+h*f(rab_x+h/2,y_zv,false);
    y[2]:=y[2]+h*f(rab_x+h/2,y_zv,true);
    rab_x:=rab_x+h;
  end;
  if t then runge:=y[1] else runge:=y[2];
end;


function ff(x:real):real;
 begin
   ff:=x*x*x*x*x-sin(x)-1 ;
 end;

{procedure horda;
 label 1;
var
  delta,x,y,a,b,e,x01,tempa,tempb:real;
  n:integer;
begin
  clrscr; e:=0.01;
  for i:=1 to 3 do
 begin
  a:=0; b:=y; delta:=1/y; x:=a;
  while x<b do
    begin tempa:=x; tempb:=x+delta;
    if ff(tempa)*ff(tempb)<0 then
    begin a:=tempa; b:=tempb; goto 1; end;
    x:=x+delta; end;  end;
  1: y:=0;
  repeat
   x01:=x0;
   x0:=(ff(b)*a-ff(a)*b)/(ff(b)-ff(a));
   y:=y+1;
   if ff(a)*ff(x0)<0 then
   b:=x0 else a:=x0;
   until abs(x01-x0)<e; writeln('rtyyryt x= ',x0:9:8);
   writeln('коpень уpавнения x^5-sin(x)-1=0  x=',x0);
end;}
procedure pol_del;
var
  delta,x,y,c,a,b,e:real;
  n:integer;
begin
  e:=0.1;
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
  writeln('Минимальный положительный корень уравнения x*x*x*x*x-sin(x)-1=0  x=',x0:9:8);
  readln;
end;


procedure strelba;
var
  prav,lev,a,b,x2,y2,rab_x,h:real;
{var
  delta,x2,y2,c,a,b,e:real;
  h:integer;
begin
  e:=0.1; b:=0; strelb_y:=0;
  x2:=0;y2:=0;
  repeat
    y2:=y2+1;
    delta:=1/y2;
    a:=x2;
    b:=a+delta;
    while (a<>y2) and (ff(a)*ff(b)>=0) do
    begin
      a:=a+delta;
      b:=b+delta;
    end;
  until ff(a)*ff(b)<0;
  h:=0;
  while abs((b-a)/2)>=e do
  begin
    c:=(b+a)/2;
    n:=n+1;
    if ff(a)*ff(c)<0 then b:=c
                     else a:=c;
  end;
  x0:=(b+a)/2;
  writeln('Минимальный положительный корень уравнения x*x*x*x*x-sin(x)-1=0  x=',x0:9:8);
  readln;
end;                            }

begin
  x2:=1;
  y2:=0.5;
  b:=0;
  strel_y:=0;
  repeat
    b:=b+1;
    strel_y:=strel_y-1;
  until ((runge(x2,strel_y,false,h_run)-y2>0) and (runge(x2,b,false,h_run)-y2<0))
     or ((runge(x2,strel_y,false,h_run)-y2<0) and (runge(x2,b,false,h_run)-y2>0));
  a:=strel_y;
  while abs(runge(x2,strel_y,true,h_run)-y2)>0.001 do
  begin
    strel_y:=(a+b)/2;
    if ((runge(x2,strel_y,false,h_run)-y2>0) and (runge(x2,b,false,h_run)-y2<0))
    or ((runge(x2,strel_y,false,h_run)-y2<0) and (runge(x2,b,false,h_run)-y2>0))
     then a:=strel_y
                 else b:=strel_y;
  end;
  writeln('Y(1) полученное методом стрельб = ',strel_y:10:8);
end;
{метод двойного пересчета}
procedure pereschet;
var
  ll:integer;
begin
  n_run:=1;
  repeat
  n_run:=n_run*2;
  h_run:=1/n_run;
  ll:=0;
  for i:=1 to round(n_run/2) do
  if abs(runge(i*2*h_run,strel_y,true,2*h_run)-runge(i*2*h_run,strel_y,true,h_run))>eps then inc(ll);
  until ll=0;
  writeln('   Количество интервалов, полученное методом двойного пересчета= ',n_run);
  writeln('   Полученный шаг для метода Рунге-Кутта = ',h_run:6:4); readln
end;

BEGIN
  n:=5;
  clrscr;
 { horda}pol_del; writeln('корень уравнения x^5-sin(x)-1=0  x=',x0:9:8);
  h:=0.1;
  pereschet;
  strelba;
  readln;
  for i:=0 to 5 do
  fun[i]:=runge(arg[i],strel_y,true,h_run);
  gd:=detect;
  InitGraph(gd,gm,'d:\tp\bgi');
  line(50,getmaxy-50,getmaxx-50,getmaxy-50);
  line(50,50,50,getmaxy-50);
  for i:=1 to 10 do
  begin
    line(50+round(540*i/10),getmaxy-52,50+round(540*i/10),getmaxy-48);
    str(i/10:4:2,s);
    outtextxy(40+round(540*i/10),getmaxy-40,s);
    str(i/10:4:2,s);
    line(48,getmaxy-50-i*20,52,getmaxy-50-i*20);
    outtextxy(0,getmaxy-50-i*20,s);
  end;
  line(round(50+0.18*540),round(getmaxy-50-Interpol(0.18)*200),195,201);
  outtextxy(200,200,'Интерполяция по Ньютону');
  vopros:=0;
  while vopros<1 do
  begin
    putpixel(round(50+vopros*540),round(getmaxy-50-Interpol(vopros)*200),white);
    vopros:=vopros+0.001;
  end;
  vopros:=0 ;
  ch:=0;
  setcolor(3);
  line(195,181,round(50+0.15*540),round(getmaxy-50-runge(0.15,strel_y,true,h_run)*200));
  outtextxy(200,180,'Метод Рунге-Кутта');
  while vopros<=1.05 do
  begin
    inc(ch);
    circle(round(50+vopros*540),round(getmaxy-50-runge(vopros,strel_y,true,h_run)*200),2);
    if frac(ch/3)=0 then
    begin
      line(50,round(getmaxy-50-runge(vopros,strel_y,true,h_run)*200),round(50+vopros*540),
      round(getmaxy-50-runge(vopros,strel_y,true,h_run)*200));
      line(round(50+vopros*540),getmaxy-50,round(50+vopros*540),round(getmaxy-50-runge(vopros,strel_y,true,h_run)*200));
    end;
    vopros:=vopros+0.05;
  end;
  setcolor(yellow);
  outtextxy(580,465,'x');
  outtextxy(10,10,'y(x)');
  readln;
  CloseGraph;
  vopros:=0;
  writeln('Вычисленные количество теплоты по формуле Q= :');
  while vopros<=1.05 do
  begin
    writeln('t=',vopros:10:8,'   Q=',integral(h):12:10);
    vopros:=vopros+0.05;
  end;

  readln;
END.