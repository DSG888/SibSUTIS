uses crt,graph;
const e=0.01;
      xi:array[0..5] of Real=(0.0,0.2,0.4,0.6,0.8,1.0);

type
mas=array[0..100] of real;
mass=array[0..3,0..100]of real;

var
  T:text;
  ch:char;
  fi:array[0..5] of real;
  tab:array[0..4,1..5] of real;
  nstar,nnov,i,j,d,gd,gm:integer;
  a,b,m,n,r,k,c,h,h1,n1,s,oldh,edx,edy,MinY,maxY,newH:real;
  flag:boolean;
  f1,ynov,ystar,ystar1,ynov1,x,y1,y, yprom,yprom1,yprom2:mas;
  Sx,Sy:array[1..51] of real;
  mx,My:array [1..51] of integer;

function newton(z:real):real;
  var i:integer;
      q,qn,sum,den:real;
  begin
    q:=(z-xi[0])/h;
    sum:=fi[0];
    den:=1;
    qn:=q;
    for i:=1 to 5 do
      begin
        sum:=sum+Tab[0,i]*qn/den;
        den:=den*(i+1);
        qn:=qn*(q-i);
      end;
    newton:=sum;
  end;

procedure init_points;
  var i,j:byte;
  begin
    NewH:=(xi[5]-xi[0])/nnov;
    sx[1]:=xi[0];
    sy[1]:=newton(sx[1]);
    for i:=2 to nnov+1 do
      begin
        sx[i]:=sx[i-1]+NewH;
        Sy[i]:=newton(Sx[i]);
      end;
  end;

procedure run_check;
  var i,j:byte;
  begin
    MinY:=Sy[1];
    MaxY:=Sy[1];
    for i:=2 to nnov do
      begin
        if Sy[i]>MaxY then maxY:=Sy[i];
        if Sy[i]<MinY then minY:=Sy[i];
      end;
    EdX:=GetMaxX/(Xi[5]-Xi[0]);
    EdY:=GetMaxY/(MaxY-MinY);
  end;

procedure ShowCons;
  var i:byte;
  begin
    moveto(round((Sx[1]-xi[0])*EdX),round((MaxY-Sy[1])*EdY));
    setcolor(4);
    setlinestyle(0,0,3);
    for i:=2 to nnov do
      begin
        lineto(round((Sx[i]-xi[0])*EdX),round((MaxY-Sy[i])*EdY));
      end;
    for i:=0 to 5 do
      circle(round((xi[i]-xi[0])*EdX),round((MaxY-fi[i])*EdY),2);
  end;

function p(z,x,y1:real):real;
  begin
    p:=z+exp(x*(2.1+z))+1.7*y1;
  end;

function v(a,b:real):real;
  begin
    v:=(a+b)/2;
  end;

procedure xx1(x,y1:real);
  var a,b,n,m,r:real;
    begin
      a:=-1; b:=1; n:=0; m:=-1; r:=1;
      repeat
        if p(n,x,y1)*p(m,x,y1)<=0 then break
        else
          if (m+r)>=b then
            begin
              b:=b+1; a:=-b; r:=1/b; m:=a; n:=m+r;
            end
          else
            begin
              m:=m+r; n:=n+r;
            end;
      until (0>1);
      a:=m;b:=n;
      repeat
        c:=v(a,b);
        if p(c,x,y1)*p(a,x,y1)>=0 then
          a:=c else b:=c;
      until abs((a-b)/2)<0.000001;
  end;


function f(x,y1:real):real;
  begin
    xx1(x,y1);
    f:=c;
  end;

procedure formf(x,y1:real);
  begin
    f1[1,j]:=y1;
    f1[2,j]:=f(x,y1);
  end;

procedure fy;
  begin
    yprom[i]:=y[i]+h*f1[1,j];
    yprom1[i]:=y1[i]+h*f1[2,j];
  end;

procedure formy;
  begin
    j:=1;
    formf(x[i],y1[i]);
    fy;
    x[i]:=x[i]+h;
    j:=2;
    formf(x[i],yprom1[i]);
    y[i+1]:=y[i]+h/2*(f1[1,1]+f1[1,2]);
    y1[i+1]:=y1[i]+h/2*(f1[2,1]+f1[2,2]);
    x[i]:=x[i]-h;
  end;

procedure yok;
begin
i:=0;
repeat
formy;
inc(i);
x[i]:=x[0]+i*h;
until x[i]>=1;{?}
end;

procedure pereschet;
var max:real;
begin
 ystar1[0]:=y1[0];
   repeat
  yok;
nstar:=round((x[i]-x[0])/h);
for i:=0  to nstar-1 do begin
ystar[i+1]:=y[i+1];
ystar1[i+1]:=y1[i+1];
end;
h:=h/2;
yok;
nnov:=round((x[i]-x[0])/h);
for i:=0  to nnov-1 do  begin
 ynov[i+1]:=y[i+1];
 ynov1[i+1]:=y1[i+1];
end;
writeln(T,'сравниваю старый и новый массивы. NNov=',nnov,'  ;NStar=',nstar);
max:=0;
for i:=0 to nstar-1 do begin
R:=abs(ynov[2*i+2]-ystar[i+1]);
if R>max then max:=R;
end;
writeln(T,' max погрешность=',max);
until R<3*e;
oldh:=h;
writeln(T);
end;

function g(k:real):real;
begin
writeln(T,'     ******   считаю G(',k,')   ******');
i:=0;
h:=0.1;
x[0]:=0;y[0]:=-1;y1[0]:=k;
pereschet;
writeln(T,'  найдено  G(',k,')=',ystar1[i+1] );
g:=ystar1[i+1];
end;

function xx2:real;
var a,b,n,m,r,c:real;
begin
writeln(T,'Ищу интервал a,b');
a:=-1;b:=1;
n:=0;m:=-1;r:=1;
 repeat
    if g(n)*g(m)<=0 then break
      else if (m+r)>=b then begin b:=b+1; a:=-b; r:=1/b; m:=a; n:=m+r; end
         else begin m:=m+r; n:=n+r; end;
  until (0>1);

  a:=m;b:=n;
  writeln(T,'Найден интервал a=',a,' b=',b);
repeat
   c:=v(a,b);
      if g(c)*g(a)>=0 then a:=c else b:=c;
until abs((a-b)/2)<0.000001;
writeln(T,' Найдено решение k=',c);
xx2:=c;
end;

procedure ShowLast;
var i:integer;
      hx:real;
      x:real;
begin
ynov[0]:=-1;
x:=0;
i:=0;
hx:=oldh;
repeat
putpixel(round(EdX*(x-xi[0])),round((MaxY-ynov[i])*EdY),15);
x:=x+hx;
inc(i);
until (x>=1);
end;

procedure ACDC;
const  h:real=0.1;
       x:real=0.12;
var i:integer;
Nt:real;
begin
writeln(T,'Вычисление мощности тока');
for i:=1 to 9 do begin
nt:=newton(x);
writeln(T,'t=',x,'  N(t)=',nt*nt);
x:=x+h;
end;
end;

begin
assign(T,'result.ugn');
rewrite(T);
clrscr;
i:=0;
y1[0]:=xx2;
h:=0.1;
pereschet;
h:=0.2;
fi[0]:=-1;
i:=1;
repeat
fi[i]:=ynov[round(nnov/5*i)];
inc(i);
until i=6;
writeln(T,'Точки для интерполяции');
for i:=0 to 5 do
writeln(T,'x[',i,']=',xi[i],' f[',i,']=',fi[i]);
h:=0.2;
for i:=4 downto 0 do
  tab[i,1]:=fi[i+1]-fi[i];
for j:=2 to 5 do
  for i:=5-j downto 0 do
  tab[i,j]:=tab[i+1,j-1]-tab[i,j-1];
init_points;
ACDC;
initgraph(gd,gm,'c:\work\bp\bgi');
run_check;
ShowCons;
showlast;
writeln(T,'Сравниваю точки интерполяции и значения функции');
for i:=0 to nnov do begin
writeln(T,'* ',i,'. x=',x[i],' ynov=',ynov[i]);
writeln(T,'    Sx=',sx[i+1],'  Sy=',Sy[i+1]);
end;
close(T);
end.