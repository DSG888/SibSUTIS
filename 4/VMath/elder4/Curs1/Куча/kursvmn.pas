uses crt, graph;

const
 Eps = 0.001;
 ndif = 2; { level of dif eq. }
 hdif = 0.1; { step for solve dif eq. }
 numInt = 100; { num of vertexes = 0..(1/hdif) }

type
 Vector = array[1..ndif] of double;
 Buffer = array[0..numInt] of double;

const
 DEBx : Vector = (0, 1);
 DEBy : Vector = (1,0.5); { start conditions  y(0)=1, y(1)=0.5 }

var
 Yint : Buffer;
 k, h, sd, hd : double;
 Gd, Gm : integer;


function Fact(t : byte) : longint;
var
 s : longint;
 i : byte;
begin
 s:=1;
 for i:=t downto 2 do s:=s*i;
 Fact:=s;
end;

function C(n, k : byte) : word;
begin
 C:=Fact(n) div (Fact(k)*Fact(n-k));
end;

function dky0(k, d : byte) : double;
var
 i : byte;
 j : shortint;
 s : double;
begin
 s:=0;
 for i:=0 to k do
 begin
  if i mod 2 = 0 then j:=1 else j:=-1;
  s:=s+j*C(k,i)*Yint[d*(k-i)]  { d=(0.2/hd) - because difference }
 end;
 dky0:=s;
end;

function NewtonInt(x : double; num : byte) : double; { takes data from Yint ... }
var
 i, j : shortint;
 res, qi : double;
begin
 res:=0;
 for i:=0 to num do
 begin
  qi:=1;
  for j:=0 to i-1 do
  begin
   qi:=qi*(((x-DEBx[1])/(0.2))-j);
  end;
  res:=res+dky0(i,round(0.2/hd))*qi/Fact(i);
 end;
 NewtonInt:=res;
end;

function GetYs(x : double) : double; { takes same h}
const
 loc : array[0..4] of integer = (-25,48,-36,16,-3);
var
 i : byte;
 rs : double;
begin
 rs:=0;
 for i:=0 to 4 do rs:=rs+loc[i]*NewtonInt(x+i*hd,4);
 rs:=rs/(12*hd);
 GetYs:=rs;
end;

function SolveEq : double; { uses m. Hordes }
const
 it : byte = 0;
 L : double = 0;
 R : double = 3;
var
 m, ls, rs : double;
 function Eq(t : double) : double;
 begin
  Eq:=2*t*t*t*t*t-sin(t)-3;
 end;
begin
 repeat
  rs:=Eq(R); ls:=Eq(L);
  m:=(rs*L-ls*R)/(rs-ls);
  if ls*Eq(m) > 0 then L:=m
                  else R:=m;
  if abs(Eq(m)) <= Eps then inc(it);
 until it = 2;
 SolveEq:=m;
end;

procedure FillDE(x : double; const Y : Vector; var Ys : Vector);
begin
 Ys[1]:=Y[2];
 Ys[2]:=x*x+Y[1]+k*Y[2]-sin(Y[2]);{k*Y[1]-cos(Y[2])-exp(-2*x);}
end;

procedure RK2_time(x : double; const Y : Vector; var OutY : Vector);
var
 k1, tmp : Vector;
begin
 FillDE(x, Y, k1);
  tmp[1]:=Y[1]+(h/2)*k1[1];
  tmp[2]:=Y[2]+(h/2)*k1[2];
 FillDE(x+h/2, tmp, k1);

 OutY[1]:=Y[1]+h*k1[1];
 OutY[2]:=Y[2]+h*k1[2];
end;


procedure SolveDE(s, step : double; var Out : Buffer);
var
 i : byte;
 Yt : Vector;
 sx,as : double;
 Tsa : Buffer;
begin
 i:=0;
 h:=step;
 sx:=DEBx[1];
 Yt[1]:=DEBy[1]; { y(0)=DEBy[1] }
 Yt[2]:=s;       { means y'(0)=s }
                 { searching for s; or solve with given s }

{ while sx < DEBx[2] do}
 for i:=0 to round(1/step) do
 begin
  Tsa[i]:=Yt[1];
  RK2_time(sx,Yt,Yt);
  sx:=sx+h;
 { inc(i);}
  { must store getted y(sx) for interpolation & solve again }
 end;
 Tsa[i]:=Yt[1];
 Out:=Tsa;
end;

function DoubleReSolve(sa : double) : double; { ret. - edgeY }
var
 t2 : Buffer;
 distort, href : double;
 i : byte;
begin
 href:=hdif;

 SolveDE(sa,href,Yint);
 repeat
  t2:=Yint;
  SolveDE(sa,href/2,Yint);

  distort:=abs(t2[1]-Yint[2]);
  for i:=2 to trunc(1/href) do if abs(t2[i]-Yint[2*i]) > distort then
   distort:=abs(t2[i]-Yint[2*i]);

  href:=href/2;
 until distort <= Eps;

 hd:=href;
 DoubleReSolve:=Yint[round(1/href)];
end;

function SeekS : double; { still uses Hordes }
const
 L : double = -1;
 R : double = 0;
 it : byte = 0;
var
 rs, ls, m, ms : double;
begin
 repeat
  rs:=DoubleReSolve(R)-DEBy[2];
  ls:=DoubleReSolve(L)-DEBy[2];
  m:=(rs*L-ls*R)/(rs-ls);
  ms:=DoubleReSolve(m)-DEBy[2];
  if ls*ms > 0 then L:=m else R:=m;

  if abs(ms) <= Eps then inc(it);
 until it = 2;
 SeekS:=m;
end;

procedure OutGraphs(xc, yc, zx, zy : integer);
var
 xn, yn : integer;
 s : string[6];
begin
 settextstyle(0,0,1);
 settextjustify(2,0);
 outtextxy(600,25,'Blue - diff. eq. solved.');
 outtextxy(600,45,'Red - Newton interpolated.');
 settextstyle(2,0,2);
 line(0,yc,640,yc);
 line(xc,0,xc,480);
 setlinestyle(3,0,1);
 for Gd:=0 to round(1/hd) do
 begin
  setcolor(11);
  xn:=round( (hd*Gd*zx+xc) );
  yn:=round( yc-Yint[Gd]*zy );
  circle(xn,yn,1);
  if Gd mod 2 = 0 then
  begin
   str(Yint[Gd]:2:4,s);
   outtextxy(xc-5,yn,s);
   str(hd*Gd:2:3,s);
   outtextxy(xn+10,yc+10,s);
   setcolor(7);
   line(xc,yn,xn,yn);
   line(xn,yc,xn,yn);
  end else
  begin
   str(Yint[Gd]:2:4,s);
   outtextxy(xn+10,yn-12,s);
   setcolor(12);
   str(NewtonInt(Gd*hd,4):2:4,s);
   outtextxy(xn+10,yn-5,s);
  end;
 end;
end;


begin
 clrscr;
 k:=SolveEq;
 writeln('Неиэвестный параметр k = ',k:2:6);
 sd:=SeekS;
 writeln('y''(0) = ',sd:2:6);
 writeln('y(1) = ', DoubleReSolve(sd):2:6, ' h = ',hd:2:3);
 write('При интерполяции h = 0.2');
 readln;
{ write('No.  Реш.ДУ    Интерпол. Производная   ');}
 writeln('No.  Реш.ДУ    Интерпол.  Производная');
 for Gd:=0 to round(1/hd) do
 begin
  if (Gd+1)/21 > 1 then gotoxy(40,Gd-15);
  write(Gd,'   ',Yint[Gd]:2:6);
  write('   ',NewtonInt(Gd*hd,5):2:6);
  writeln('   ',GetYs(Gd*hd):2:6);
 end;
{ writeln(NewtonInt(0.05,4):2:4);  { 5 - max num, uses less}
 readln;
 Gd:=detect;
 InitGraph(Gd,Gm,'c:\work\bp\bgi');
{ moveto(round(640*hdif)-20,480-round(400*Yint[1]));
 for Gd:=2 to 20 do lineto(round((640*hdif)*Gd)-20,480-round(400*Yint[Gd]));}
 OutGraphs(40,450,500,350);
 readln;
 CloseGraph;
end.