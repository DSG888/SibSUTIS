uses crt;
const
    e=0.01;
    y0=10;
    xx: array [0..8] of real = (0,0.12,0.32,0.42,0.52,0.62,0.72,0.82,0.92);
    xx1: array [0..6] of real = (0,0,0.2,0.4,0.6,0.8,1.0);
var
  i,ii: byte;
  k: integer;
  x,j,h,yy,dy1: real;
  y1: array [1..2] of real;
  y2,y3,ddy: array [1..8] of real;

function y (x,yy,dy: real): real;
begin
  y:=10*(exp((-15)*x))+4*dy-16/(16+yy);
end;

function ei(tmp,h: real): real;
begin
  y1[1]:=0;
  j:=0;
  y1[2]:=5;
  repeat
    y1[1]:=y1[1]+h*y1[2];
    y1[2]:=y1[1]+h*(y(j,y1[2],y2[2]));
    j:=j+h;
  until j>tmp;
  ei:=y1[1];
end;

procedure eiler(k: array of real;num: byte);
var
  d1,d2: real;
begin
  dy1:=5;
  h:=0.01;
  for i:=1 to num do
   begin
     repeat
       d1:=ei(k[i],h);
       d2:=ei(k[i],h/2);
       h:=h/2;
     until (abs(d1-d2))<=e;
     y2[i]:=d1;
   end;
  for i:=1 to num do
   begin
     write('X(',i,')=',k[i]:4:2,'       ');
     write('Y(',i,')=',y2[i]:10:9);
     writeln;
   end;
end;

procedure proizv;
var
  t: array [1..6] of real;
  K: byte;
begin
  for i:=1 to 6 do
   t[i]:=y2[i];
  ddy[1]:=t[1];
  for i:=1 to 6 do
   begin
     for k:=1 to 6-i do
      begin
        t[k]:=t[k+1]-t[k];
      end;
     ddy[i]:=t[1];
   end;
end;

function p(x: real): real;
Var
  ch,zn,p1,q:Real;
  k: byte;
Begin
  q:=(x-xx1[1])/h;
  p1:=y2[1];
  For i:=1 to 8 do
   Begin
     ch:=1;
     zn:=1;
     For k:=0 to i-1 do
      ch:=ch*(q-j);
     For k:=1 to i do
      zn:=zn*j;
     p1:=p1+ddy[i]*ch/zn;
   End;
  P:=p1;
End;

begin
  clrscr;
  eiler(xx,8);
  readln;
  eiler(xx1,6);
  readln;
  proizv;
  H:=0.2;
  writeln('Значения многочлена:');
  for ii:=1 to 8 do
   writeln('X(',ii,')=',Xx[ii]:1:2,'    y(',Xx[ii]:1:2,')=',p(xx[ii]):10,9);
  readln;


end.