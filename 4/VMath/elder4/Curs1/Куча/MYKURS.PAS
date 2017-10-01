program mykursovic;
 uses crt,graph;
  const
   e=0.0001;
   n=9;
   X:array [1..n] of real=(0.12,0.22,0.32,0.42,0.52,0.62,0.72,0.82,0.92);
   W:array [0..5] of real=(0,0.2,0.4,0.6,0.8,1);
  type
   masY=array [1..2] of real;
   massiv=array [1..n] of real;
   masK=array [1..2,1..4] of real;
  var
   i,j,z,dyg,graphcurent_x,graphcurent_y,u:integer;
   h,xx,k,x0,curent_x,curent_y:real;
   Result:massiv;
   Y:masY;
   ss:string;
  c:array [0..5,0..5] of real;
  d:array [1..4] of real;
  m,yy,alfa,betta,ff:array[0..5] of real;


function F(x1:real;Y:masY;i:integer):real;
   begin
    case i of
     1: F:=y[1];
     2: F:=sin(y[2])+x1*x1+y[1]+y[2];
    end;
    end;

procedure solve_K(x1,h:real;Y:masY;var K:masK);
    var
     i:integer;
     YYY:masY;
    begin
     for i:=1 to 2 do begin
      YYY:=Y;
      K[i,1]:=F(x1,YYY,i);
      YYY[i]:=Y[i]+(h/2)*K[i,1];
      K[i,2]:=F(x1+(h/2),YYY,i);
      YYY[i]:=Y[i]+(h/2)*K[i,2];
      K[i,3]:=F(x1+(h/2),YYY,i);
      YYY[i]:=Y[i]+h*K[i,3];
      K[i,4]:=F(x1+h,YYY,i);
     end;
    end;

function runge(xx,h:real):real;
   var
    Y:masY;
    i:integer;
    w1:real;
    K:masK;
   begin
    w1:=0;
    Y[1]:=1;
    Y[2]:=0.5;
    while w1<=xx do begin
     solve_K(w1,h,Y,K);
     for i:=1 to 2 do Y[i]:=Y[i]+(h/6)*(K[i,1]+2*K[i,2]+2*K[i,3]+K[i,4]);
     w1:=w1+h;
    end;
    runge:=Y[1];        {y[1]=f}
   end;

function runge1(w,h:real):real;
   var
    d1,d2:real;
   begin
    repeat
     d1:=runge(w,h);
     d2:=runge(w,h/2);
     h:=h/2;
    until abs(d1-d2)<=15*e;
    runge1:=1/15*(d1-d2)+d2;
   end;

procedure pred_spline;
  begin
  for i:=1 to 4 do
  d[i]:=(ff[i+1]-ff[i])/h-(ff[i]-ff[i-1])/h;
  for i:=1 to 4 do
  for j:=1 to 4 do
  if j=i-1 then c[i,j]:=h/6 else
         if j=i then c[i,j]:=2*h/3   else
               if j=i+1 then c[i,j]:=h/6
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
  i:integer;
begin
  for i:=1 to 5  do if (xx>w[i-1]) and (xx<w[i]) then  k:=i;
    spline:=m[k-1]*sqr(w[k]-xx)*(w[k]-xx)/(6*h) +
    m[k]*sqr(xx-w[k-1])*(xx-w[k-1])/(6*h) +
    (ff[k-1]-m[k-1]*sqr(h)/6)*(w[k]-xx)/h +
    (ff[k]-m[k]*sqr(h)/6)*(xx-w[k-1])/h;
end;

procedure grafik;
   var
    i:integer;
    st:string;
    grDriver : Integer;
    grMode   : Integer;
   begin
    grDriver := Detect;
    InitGraph(grDriver,grMode,'c:\tp\bgi');
    dyg:=round(GetMaxY/17);
    line(20,GetMaxY-20,620,GetMaxY-20); { OX }
    line(30,GetMaxY-10,30,10);  { OY }
    line(620,GetMaxY-20,600,GetMaxY-17);    {strelki 4str}
    line(620,GetMaxY-20,600,GetMaxY-23);
    line(30,10,27,40);
    line(30,10,33,40);
    for i:=0 to 10 do begin  { razlinovka OX }
     line((i+1)*50-20,GetMaxY-18,(i+1)*50-20,GetMaxY-22);
     str(i/10:3:1,st);
     OutTextXY((i+1)*50-20,GetMaxY-12,st);
   end;
   for i:=1 to 15 do begin { razlinovka OY }
    line(28,GetMaxY-20-(16-i)*dyG,32,GetMaxY-20-(16-i)*dyG);
    str(i/5:3:1,st);
    OutTextXY(0,GetMaxY-23-i*dyG,st);
   end;
   OutTextXY(10,20,'Y');
   OutTextXY(GetMaxX-60,GetMaxY-18,'X');
  end;

var
  ch:integer;
 begin
  clrscr;
  h:=0.02;
  writeln('Moshnost ravna y^(x); Y(x) polucheno methodom RK 4 poryadka:');
  for i:=1 to n do
    begin
      Result[i]:=runge1(X[i],h);
      writeln('X[',i,']=',X[i]:1:2,'      Y(',X[i]:1:2,')=',sqr(Result[i]):6:4);
      end;
      writeln;
  writeln('Y(X) For spline interpolation:');
     h:=0.2; ff[0]:=1;
     writeln('X[0]=',w[0]:1:1,'     Y(0.0)=',ff[0]:2:8);
    for i:=1 to 5  do
    begin
    ff[i]:=runge1(w[i],h);
     writeln('X[',i,']=',w[i]:1:1,'     Y(',w[i]:1:1,')=',ff[i]:2:8);
           end;
           writeln;
           {clrscr;   }
           pred_spline;
           writeln('Spline v zadanih tochkah :');
           for u:=1 to n do
      writeln('X[',u,']=',x[u]:1:2, '     Y[',x[u]:1:2,']=',spline(x[u]):6:4);
      readln;
    clrscr;
    grafik;
  ch:=0;
  for i:=0 to 80 do begin
  graphcurent_x:=round(i*6.25+30);
   if (i/80>w[ch]-0.01) and (i/80<w[ch]+0.01) then
   begin
     curent_y:=ff[ch];
     ch:=ch+1;
   end
   else
   curent_y:=spline(i/80);
   graphcurent_y:=round(GetMaxY-(i+20)-curent_y*3.3*dyg-48);
   SetColor(3);
   Line(graphcurent_x,graphcurent_y,6+graphcurent_x,-3+graphcurent_y);
   SetColor(6);
   if i/16=round(i/16) then circle(graphcurent_x,graphcurent_y,3);
   end;
   for i:=0 to 80 do begin
   graphcurent_x:=round(i*6.25+30);
   if (i/80>w[ch]-0.01) and (i/80<w[ch]+0.01) then
   begin
     curent_y:=ff[ch];
     ch:=ch+1;
   end
   else
   curent_y:=runge1(i/80,0.02);
   graphcurent_y:=round(GetMaxY-(i+20)-curent_y*3.3*dyg-48);
   SetColor(4);
   Line(graphcurent_x,graphcurent_y,6+graphcurent_x,-3+graphcurent_y);
   SetColor(6);
   if i/16=round(i/16) then circle(graphcurent_x,graphcurent_y,3);
    end;
   readln;
   closegraph;
 end.

