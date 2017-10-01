uses crt, graph;

const
 Eps = 0.001;
 ndif = 2; { level of dif eq. }
 nint = 6; { for interpolation 10 - as step is 0.1 & +1 for correction }
 hdif = 0.1; { step for solve dif eq. }
 numInt = 200; { num of vertexes = 0..(1/hdif) }

type
 SpVect = array[0..nint] of double;
 Vector = array[1..ndif] of double;
 Matrix = array[0..nint,0..nint+1] of double;
 Buffer = array[0..numInt] of double;

const
 DEBx : Vector = (0, 1);
 DEBy : Vector = (1, 0.5); { start conditions  y(0)=1, y'(1)=0.5 }

var
 Yint : Buffer;
 k, h, sd, hd : double;
 Gd, Gm : integer;
 M, d : SpVect;
 C : Matrix;


function Interv(x : double) : byte;
var
 s : byte;
begin
 s:=1;
 while s*0.2 < x do inc(s);
 Interv:=s;
end;

function power(j : shortint; num : double) : double;
var
 i : byte;
 p : double;
begin
 p:=1;
 i:=0;
 while i < j do begin p:=p*num; inc(i); end;
 power:=p;
end;

procedure TheC(var C : Matrix);
var
 i, j, qw : byte;
 t : double;
begin
 qw:=round(0.2/hd);
 for i:=1 to nint-1 do
 begin
  for j:=1 to nint-1 do
  begin
   if i=j then C[i,j]:=0.4/3 else
    if j=i+1 then C[i,j]:=0.2/6 else
     if j=i-1 then C[i,j]:=0.2/6 else C[i,j]:=0;
  end;
  C[i,nint+1]:=((Yint[qw*(i+1)]-Yint[qw*i])/0.2)-((Yint[qw*i]-Yint[qw*(i-1)])/0.2);
 end;
end;

procedure TriDiagSolve(const C : Matrix; var M : SpVect);
var
 a, b : SpVect;
 ck, bk, xa : double;
 i : byte;
begin
 a[0]:=0;
 b[0]:=0;
 M[nint]:=0;
 M[0]:=0;

 for i:=1 to nint-1 do
 begin
  if i=1 then bk:=0 else bk:=C[i,i-1];
  if i=nint-1 then ck:=0 else ck:=C[i,i+1];

  a[i]:=-ck/(C[i,i]+bk*a[i-1]);
  b[i]:=(C[i,nint+1]-bk*b[i-1])/(C[i,i]+bk*a[i-1]);
 end;

 for i:=nint-1 downto 1 do
 begin
  xa:=M[i+1];
  M[i]:=a[i]*xa+b[i];
 end;

end;

function Spline(i : byte; xa : double) : double;
var
 qw : byte;
begin
 qw:=round(0.2/hd);
 Spline:=M[i-1]*power(3,hd*qw*i-xa)/(6*0.2)+
         M[i]*power(3,xa-hd*qw*(i-1))/(6*0.2)+
         (Yint[qw*(i-1)]-M[i-1]*sqr(0.2)/6)*((hd*qw*i-xa)/0.2)+
         (Yint[qw*i]-M[i]*sqr(0.2)/6)*((xa-hd*qw*(i-1))/0.2);
end;


function GetYs(x : double) : double; { takes same h }
const
 loc : array[0..4] of integer = (-25,48,-36,16,-3);
var
 i, j : byte;
 rs : double;
begin
 rs:=0;
 for i:=0 to 4 do rs:=rs+loc[i]*Spline(Interv(x+i*hd),x+i*hd);
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
  Eq:=2*sqr(t)*t-sin(t)-3;
 end;
begin
 repeat
  rs:=Eq(R); ls:=Eq(L);
  m:=(rs*L-ls*R)/(rs-ls);
  if ls*Eq(m) > 0 then L:=m else R:=m;

  if abs(Eq(m)) <= Eps then inc(it);
 until it = 2;
 SolveEq:=m;
end;

procedure FillDE(x : double; const Y : Vector; var Ys : Vector);
begin
 Ys[1]:=Y[2];
 Ys[2]:=(sqr(x)+Y[1])+k*Y[2]-sin(Y[1]);
end;

procedure RK2_proizv(x : double; const Y : Vector; var OutY : Vector);
var
 k1, k2, tmp : Vector;
begin
 FillDE(x, Y, k1);
  tmp[1]:=Y[1]+h*k1[1];
  tmp[2]:=Y[2]+h*k1[2];
 FillDE(x+h, tmp, k2);

 OutY[1]:=Y[1]+(h/2)*(k1[1]+k2[1]);
 OutY[2]:=Y[2]+(h/2)*(k1[2]+k2[2]);
end;


procedure SolveDE(s, step : double; var Out, Outs : Buffer);
var
 i : byte;
 Yt : Vector;
 sx,as : double;
 Tsa, Tsas : Buffer;
begin
 i:=0;
 h:=step;
 sx:=DEBx[1];
 Yt[1]:=DEBy[1]; { y(0)=DEBy[1] }
 Yt[2]:=s;       { means y'(0)=s }
                 { searching for s; or solve with given s }

{ while sx < DEBx[2] do}
 for i:=0 to round(1/step)+round(0.2/step) do  { adds round(0.2/step) }
 begin                                         { to get one more interval }
  Tsa[i]:=Yt[1];                               { for Spline interpolation }
  Tsas[i]:=Yt[2];
  RK2_proizv(sx,Yt,Yt);
  sx:=sx+h;
 { inc(i);}
  { must store getted y(sx) for interpolation & solve again }
 end;
 Tsa[i]:=Yt[1];
 Tsas[i]:=Yt[2];
 Out:=Tsa;
 Outs:=Tsas;
end;

function DoubleReSolve(sa : double) : double; { ret. - edgeY }
var
 t2, ts : Buffer;
 distort, href : double;
 i : byte;
begin
 href:=hdif;

 SolveDE(sa,href,Yint,ts);
 repeat
  t2:=Yint;
  SolveDE(sa,href/2,Yint,ts);

  distort:=abs(t2[1]-Yint[2]);
  for i:=2 to trunc(1/href) do if abs(t2[i]-Yint[2*i]) > distort then
   distort:=abs(t2[i]-Yint[2*i]);

  href:=href/2;
 until distort <= Eps;

 hd:=href;
 DoubleReSolve:={Yint}ts[round(1/href)];
end;

function SeekS : double; { still uses Hordes }
const
 L : double = -1;
 R : double = 1;
 it : byte = 0;
var
 rs, ls, m, ms : double;
begin
 repeat
  rs:=DoubleReSolve(R)-DEBy[2]; ls:=DoubleReSolve(L)-DEBy[2];
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
 outtextxy(260,15,'Blue - Diff. eq. solved.');
 outtextxy(260,25,'Red - Spline interpolated.');
 settextstyle(2,0,2);
{ line(0,yc,640,yc);}
 line(xc,0,xc,480);
 setlinestyle(3,0,1);
 for Gd:=0 to round(1/hd) do
 begin
  setcolor(12);
  xn:=round( (hd*Gd*zx+xc) );
  yn:=round( yc-(Spline(Interv(Gd*hd),Gd*hd)-1)*zy*28 );
  circle(xn,yn,1);
  setcolor(11);
  xn:=round( (hd*Gd*zx+xc) );
  yn:=round( yc-(Yint[Gd]-1)*zy*28 );
  circle(xn,yn,1);
  if (Gd mod 8 = 0) then
  begin
   str(Yint[Gd]:2:4,s);
   outtextxy(xc-5,yn,s);
   str(hd*Gd:2:3,s);
   outtextxy(xn+10,yc+25,s);

   setcolor(12);
   str(Spline(Interv(Gd*hd),Gd*hd):2:4,s);
   outtextxy(xn+25,yn+10,s);

   setcolor(7);
   line(xc,yn,xn,yn);
   line(xn,yc+20,xn,yn);
  end;
 end;
end;


begin
 clrscr;
 k:=SolveEq;
 writeln('Неиэвестный параметр k = ',k:2:6);
 sd:=SeekS;
 writeln('y''(0) = ',sd:2:6);
 writeln('y''(1) = ', DoubleReSolve(sd):2:6, ' h = ',hd:2:4);
 write('Нажмите ENTER ...');
 readln;
 TheC(C);
 TriDiagSolve(C,M);
 write('No.  Решен.ДУ   Интерпол. Производная   ');
 writeln('No.  Решен.ДУ   Интерпол. Производная');
 for Gd:=0 to round(1/hd) do
 begin
  if (Gd+1)/21 > 1 then gotoxy(41,Gd-15);
  write(Gd:2,'   ',Yint[Gd]:2:6);
  write('   ',Spline(Interv(Gd*hd),Gd*hd):2:6);
  writeln('   ',GetYs(Gd*hd):2:6);
 end;
 readln;
 Gd:=detect;
 InitGraph(Gd,Gm,'c:\work\bp70\bgi');
 OutGraphs(40,350,500,150);
 readln;
 CloseGraph;
end.