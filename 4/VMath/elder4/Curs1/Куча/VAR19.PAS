{$N+}
{$S-}
uses crt,graph;
const
  e=0.0001;
  e2=0.001;{для МПД}
type
  TY=array [1..2] of single;
  TSetka = record
    X:single;
    Y:TY;
  end;
  Ty2 = record
    Y:array [0..300] of real;
    num:word;
  end;
  Psetka=array [0..2500] of tsetka;
var
  k,rr:real;
  n:integer;
  setka:PSetka;
  setka2:PSetka;
  AX0,ay0:ty2;
{Проседура вычисляющая значение в точке X для Ньютона}
function Pn(n:word;x0,y0:Ty2;x:real;pos:integer;h:real):real;
var
  p,q:real;
  i,j:word;
  KONras:ty2;
function ras(l:word):real;
var
  k:real;
  i:word;
begin
  if l=1 then begin
    for i:=0 to y0.num-2 do
      konras.y[i]:=y0.y[i+1]-y0.y[i];
    konras.num:=y0.num-1;
  end
  else
    begin
      for i:=0 to konras.num-2 do
        konras.y[i]:=konras.y[i+1]-konras.y[i];
      dec(konras.num);
    end;
  for i:=konras.num to 300 do
    konras.y[i]:=0;
  ras:=konras.y[pos];
end;
function factorial(l:word):real;
var
  i:word;
  t:real;
begin
  t:=1;
  for i:=1 to l do
    t:=t*i;
  factorial:=t;
end;
begin
  p:=Y0.y[pos];
  i:=0;
  repeat
    inc(i);
    q:=1;
    for j:=1 to i do
      q:=q*(((x-ax0.y[pos])/h)-j+1);
   p:=p+q*ras(i)/factorial(i);
  until i=n;
  pn:=p;
end;

{---------------------------------------------------}
function f3(X:real):real; {возвращает значение Y в точке X используя сетку}
var
  r:real;
  i:integer;
begin
  for i:=0 to n do
    if setka[i].x>=x then break;
  r:=setka[i].y[1];
  f3:=r;
end;
{---------------------------------------------------}
function f2(X:real;Y:TY):real;{Вычисляяет вторую производ в X}
var
  r:real;
function mXord(ia,ib:real):real;
var
  c2,c:real;
  f1,f2:real;
function f(c:real):real;
var
  r:real;
begin
  r:=c+4*y[2]+1/(16+c*c)-10*exp(-x);
  f:=r;
end;
begin
  c:=1000;
  repeat
  c2:=c;
  f1:=f(ia);
  f2:=f(ib);
  c:=ia+(f1*ia-f1*ib)/(f2-f1);
  ia:=c;
  until abs(c2-c)<e;
  mxord:=c;
end;
begin
  r:=mxord(-20,20);
  f2:=r;
end;
{-----------------------------------------------}
function ex(x1,x2:psetka):boolean;
var
  i:integer;
  r:integer;
begin
    r:=0;
  repeat
    r:=r+1;
    if abs(x1[r].y[1]-x2[2*r].y[1])>e then begin ex:=false; exit;end;
  until r>=(n div 2);
  ex:=true;
end;
{-----------------------------------------------}
procedure getset2(h,pod:real);{Просто строит сетку с заданным шагом}
var
  xb,yyy,fff,fff2:real;
  y1:Ty;
  i,ll,o:integer;
  k1,k2,k3,k4,temp:ty;
begin
  n:=0;
  xb:=0;
  n:=0;
  setka[n].Y[1]:=10;
  setka[n].Y[2]:=pod;
  setka[n].X:=0;
  repeat
    xb:=xb+h;
    inc(n);
    setka[n].X:=xb;
    {Рунге- Кутта 4 порядка}
    for i:=1 to 2 do k1[i]:=f2(setka[n-1].x,setka[n-1].y);
    for i:=1 to 2 do temp[i]:=setka[n-1].y[i]+(h/2)*k1[i];
    for i:=1 to 2 do k2[i]:=f2(setka[n-1].x+h/2,temp);
    for i:=1 to 2 do temp[i]:=setka[n-1].y[i]+(h/2)*k2[i];
    for i:=1 to 2 do k3[i]:=f2(setka[n-1].x+h/2,temp);
    for i:=1 to 2 do temp[i]:=setka[n-1].y[i]+h*k3[i];
    for i:=1 to 2 do k4[i]:=f2(setka[n-1].x+h,temp);
    for i:=1 to 2 do setka[n].y[i]:=setka[n-1].y[i]+(h/6)*(K1[i]+2*k2[i]+2*k3[i]+k4[i]);
  until xb>=1.2;
end;
procedure getset(h,pod:real);
var
  xb,yyy:real;
  y1:Ty;
  i,ll,o:integer;
begin
  n:=0;
  repeat
    for ll:=1 to 2 do begin
      for o:=0 to n do setka2[o]:=setka[o];
      getset2(h,pod);
      h:=h/2;
    end;
  until ex(setka2,setka);
end;
{---------------------------------------------------}
procedure MPD(var c:real;ia,ib:real);
var
  c2:real;
  f1,f2,rrr:real;
begin
  c:=10000;
  repeat
  c2:=c;
  c:=(ia+ib)/2;
  getset(0.1,c);
  rrr:=f3(1);
  if rrr>2 then ia:=c else ib:=c;
  until (abs(rrr-2)<e2);
end;
{---------------------------------------------------}
procedure madetab;{Строит сетку для интерполяции}
var
  x:real;
  i:word;
begin
  x:=0;
  i:=0;
  repeat
    inc(i);
    Ax0.y[i-1]:=x;
    AY0.y[i-1]:=f3(x);
    x:=x+0.2;
  until X>1.3;
    Ax0.num:=i;
    ay0.num:=i;
end;
{------------------------------------------}
function change(x0:ty2;t:real):integer; {Для метода Ньютона, находит Y0}
var
  i:word;
  fun:boolean;
begin
  fun:=false;
  for i:=0 to x0.num-1 do begin
    if abs(t-x0.y[i])<0.000001 then begin
      fun:=true;
      change:=i;
      break;
    end;
    if t<x0.y[i] then begin change:=i;break;end;
  end;
end;
{------------------------------------}
var
  i,s,d,g:integer;
  qq,r:real;
begin
  clrscr;
  mpd(rr,8,11);
  madetab;
  d:=detect;
  writeln('Подбор k = ',rr:2:6);
  rr:=0.12;
  for i:=1 to 9 do
    begin
      writeln('X= ',rr:2:2,' Мощность = ',(f3(rr)*f3(rr)):2:6);
      rr:=rr+0.1;
    end;
  readln;
  initgraph(d,g,'c:\tp\bgi');
  setviewport(20,400,400,479,false);
  qq:=0;
  line(0,0,600,0);
  line(0,-400,0,300);
  repeat
    putpixel(round(qq*600),-round(f3(qq)*30),14);
    s:=change(ax0,qq);
    putpixel(round(qq*600),-round(pn(1,ax0,ay0,qq,s,0.15)*30),12);
    qq:=qq+0.0005;
  until qq>=1;
  readln;
  closegraph;
  
end.