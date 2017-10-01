uses crt,graph;
Type
  Vector=array [0..1] of real;
Const
  h=0.2;
  h_tr=0.01;
  e=0.001;
  N=5;
  x0:array [0..N] of real=(0,0.2,0.4,0.6,0.8,1);
Var
  kf:real;
  y0:array [0..n] of real;
  kr:array[0..n,0..n] of real;
  Endh:real;

Procedure FindK;

  Function f(x:real):real;
  begin
   f:=sqr(sqr(x))*x-sin(x)-3;
  end;

  Function MHD(a,b:real): real;
  Var
     c:real;
  Begin
    while abs((b-a)/2)>=e do begin
      c:=(a+b)/2;
      if (f(a)*f(c)<0) then b:=c else a:=c;
    end;
    mhd:=c;
  end;

Var
   a,b,step,ax,bx:real;
begin
  a:=0; b:=1; step:=1;
  while (b<4) do begin
    b:=b*2;
    step:=step/2;
    ax:=a; bx:=a+step;
    while bx<b do begin
      if ((f(ax)*f(bx))<0) then kf:=MHD(ax,bx);
      ax:=ax+step; bx:=bx+step;
    end;
  end;
end;
{----------------------------}
Function du (x,y,y1,y2:real):real;
begin
  du:=y2-cos(y2)-cos(y)-kf*y1+exp(-2*x);
end;

Function Find_yss (x,y,y1:real):real;

  Function MHD(a,b:real): real;
  Var
    c:real;
  Begin
    c:=(a+b)/2;
    while abs((b-a)/2)>=e do begin
      c:=(a+b)/2;
      if (du(x,y,y1,a)*du(x,y,y1,c)<0) then b:=c else a:=c;
    end;
    mhd:=c;
  end;

Var
  a,b,step,ax,bx:real;
begin
  a:=-1; b:=1; step:=1;
  while (a>-5) do begin
    a:=a*2; b:=b*2;
    step:=step/2;
    ax:=a; bx:=a+step;
    while bx<b do begin
      if ((du(x,y,y1,ax)*du(x,y,y1,bx))<0) then begin Find_yss:=MHD(ax,bx); a:=-10; break; end;
      ax:=ax+step; bx:=bx+step;
    end;
  end;
end;

procedure MRK (h1,x:real; var y:real;var ys:real);

  procedure largeY (y,ys:real;var lY:vector);
  begin
    lY[0]:=y;
    lY[1]:=ys;
  end;
  procedure largeF (x:real;lY:vector;var lF:vector);
  begin
    lF[0]:=lY[1];
    lF[1]:=Find_yss(x,lY[0],lY[1]);
  end;
  procedure mul (a:real;b:vector;var c:vector);
  begin
    c[0]:=a*b[0]; c[1]:=a*b[1];
  end;
  procedure add (a,b:vector;var c:vector);
  begin
    c[0]:=a[0]+b[0]; c[1]:=a[1]+b[1];
  end;

Var
  lY,lF,lFnew,t,tt:vector;
begin
   largeY(y,ys,lY);
   largeF(x,lY,lF);
    mul(h1,lF,t);
    add(lY,t,tt);
   largeF(x+h1,tt,lFnew);
   add(lF,lFnew,t);
   mul(h1/2,t,tt);
   add(lY,tt,t);
   ys:=t[1];
   y:=t[0];
end;

function doubleP(kr:real):real;
var h,x,y,y1,y_2,y1_2,yy:real;
begin
h:=0.1;
x:=0;
y:=1;
y1:=kr;
y_2:=y;
y1_2:=y1;
While (x<1) do
  begin
  MRK(h,x,y,y1);
  MRK(h/2,x,y_2,y1_2);
  MRK(h/2,x+h/2,y_2,y1_2);

  if (abs(y_2-y)>3*E) then
     begin
       h:=h/2;
       x:=0;
       y:=1;
       y1:=kr;
       y_2:=y;
       y1_2:=y1;
     end else x:=x+h;
end;
doubleP:=y_2;
EndH:=h/2;
end;

Function Find_ys (x,y:real):real;
Var
  a,b,c,t,tt:real;
Begin
  a:=-0.65; b:=-0.6;
  repeat
    c:=(a+b)/2;
    t:=DoubleP(c);
    if (t>0.5) then b:=c else a:=c;
  until (abs(0.5-t)<e);
  Find_ys:=c;
end;
{----------------------------}
Procedure Build_kr_Table;
Var
  i,j,k:integer;
begin
  for i:=0 to n do kr[0,i]:=y0[i];
  k:=n;
  for j:=1 to n do begin
    for i:=0 to k do
      kr[j,i]:=kr[j-1,i+1]-kr[j-1,i];
    dec(k);
  end;
end;

Function Pn(xi:real):real;
Var
  k:integer;
  p,q:real;

  Function qu(k:integer):real;
  Var
    g:real;
    i:integer;
  begin
    g:=1;
    for i:=0 to k-1 do g:=g*(q-i);
    qu:=g;
  end;

  Function Fact(k:integer):real;
  begin
    if k<=1 then fact:=1 else fact:=k*fact(k-1);
  end;

begin
  q:=(xi-x0[0])/h;
  p:=0;
  for k:=0 to n do begin
    p:=p+(kr[k,0]/fact(k))*qu(k);
  end;
  Pn:=p;
end;
{----------------------------}
Function Integral:real;
Var
  i:integer;
  x:array [0..100] of real;
  s:real;
begin
  s:=0.001;
  for i:=0 to 100 do begin
    x[i]:=s;
    s:=s+h_tr;
  end;
  s:=0;
  for i:=1 to 100-1 do s:=s+sqr(Pn(x[i]));
  Integral:=h_tr*((sqr(Pn(x[0]))+sqr(Pn(x[n])))/2+s);
end;
{----------------------------}

Var
  t,y,y1,x:real;
  i,gd,gm:integer;

Begin clrscr;
FindK;
writeln('k=',kf:10:8);
y1:=Find_ys(0,1);
writeln('y1(0)=',y1:12:10,' ');
writeln('endh=',endh:10:8);
y:=1;
x:=0;
i:=0;
while (x-endh)<=1 do
  begin
   if round(x*100000)=round(0.2*i*100000) then
       begin
         writeln('y(',x:2:2,')= ',y:10:5,'   y1(',x:2:2,')= ',y1:10:5);
         y0[i]:=y;
         inc(i);
       end;
   MRK(endh,x,y,y1);
   x:=x+endh;
  end;
for i:=0 to n do write(y0[i]:6:5,' ');
writeln;writeln;
Build_kr_Table;
for i:=0 to n do write(Pn(x0[i]):6:5,' ');
writeln;
writeln('Q=',Integral:12:10);
readkey;

gd:=detect;
initgraph(gd,gm,'c:\units\pascal\bgi\');
for i:=0 to n do circle(round(x0[i]*150+200),getmaxy-round(y0[i]*30+300),3);
moveto(round(-0.6*150+200),getmaxy-round(Pn(-0.6)*30+300));
t:=0; x:=-0.6;
while x<1.6 do begin
t:=Pn(x);
lineto(round(x*150+200),getmaxy-round(t*30+300));
x:=x+h/10;
end;
line(200,50,200,400);
line(50,getmaxy-200,500,getmaxy-200);
readkey;
closegraph;
end.