uses crt, graph;
const eps=0.01;
      y_0=1;
      y_1=0.0;
      rastx=200;
      rasty=30;
type
  typY=array[1..2] of double;
  TypC=array[1..4,1..4] of real;
  TypD=array[1..4] of real;
  TypMiX=array[0..5] of real;
  typh=array[1..5] of real;
var kk:real;
    yy:TypY;
    EndH:double;
    c: Typc;
    d: typD;
    m,x,uzels: typMix;
    h: typH;

function functian(x:double; y:real; y1:real; y2:real):real;
begin
functian:=y2-sin(y2)+1.7*y1+exp(x*(2.1+y1));
end;

procedure srchInt(var a:real; var b:real; x:double; y:real; y1:real);
var c,d,h,fa,fb: real;
    i: integer;
begin
c:=-35; d:=35 ;h:=1; a:=c; b:=a+h;
fa:=1; fb:=1;
 while fa*fb>0 do
   begin
   a:=c;b:=a+h;
   fa:=functian(x,y,y1,a); fb:=functian(x,y,y1,b);
   while b<d do
      begin a:=b;
            b:=b+h;
            fa:=fb;
            fb:=functian(x,y,y1,b);
            if fa*fb<0 then break;
      end;
      c:=c-1; d:=d+1; h:=h/2;
   end;
end;


procedure Mhord(x:double; y:real; y1:real; var kr:real);
var fa,fb,fc,c,cp,a,b:real;
begin
     srchInt(a,b,x,y,y1);
     fa:=functian(x,y,y1,a);fb:=functian(x,y,y1,b);
     c:=0; cp:=(fb*a-fa*b)/(fb-fa);
     While (abs(cp-c)>eps) do
      begin
        c:=cp;
        fc:=functian(x,y,y1,c);
        if fa*fc<0 then begin b:=c; fb:=fc; end
        else begin a:=c; fa:=fc; end;
        cp:=(fb*a-fa*b)/(fb-fa);
      end;
        kr:=cp;
end;

function Difur(x:double; y:real; y1:real):real;
var a,b,kkk:real;
begin
Mhord(x,y,y1,kkk);
difur:=kkk;
end;

function RungeKutt(xi:double; var Y:TypY; h:double):real;
var K:array[1..4,1..2] of double;
    rrr:typY;
begin
k[1,1]:=y[2]; k[1,2]:=difur(xi,y[1],y[2]);
k[2,1]:=y[2]+(h/2)*k[1,2]; k[2,2]:=difur(xi+h/2,y[1]+(h/2)*k[1,1],y[2]+(h/2)*k[1,2]);
k[3,1]:=y[2]+(h/2)*k[2,2]; k[3,2]:=difur(xi+h/2,y[1]+(h/2)*k[2,1],y[2]+(h/2)*k[2,2]);
k[4,1]:=y[2]+h*k[3,2]; k[4,2]:=difur(xi+h,y[1]+h*k[3,1],y[2]+h*k[3,2]);
y[1]:=y[1]+(h/6)*(k[1,1]+2*k[2,1]+2*k[3,1]+k[4,1]);
y[2]:=y[2]+(h/6)*(k[1,2]+2*k[2,2]+2*k[3,2]+k[4,2]);
end;

procedure DblCheck(var Yb:typY; kr:real);
var hh, xi:double;
    Yh,Yh_2:TypY;
    i: integer;
begin
hh:=0.05;
xi:=0;
yh[1]:=y_0;
yh[2]:=kr;
yh_2:=yh;
While (xi<1) do
  begin
  RungeKutt(xi,Yh,hh);
  RungeKutt(xi,Yh_2,hh/2);
  RungeKutt(xi+hh/2,Yh_2,hh/2);

  if (abs(Yh[1]-Yh_2[1])>3*eps) then
     begin
       hh:=hh/2;
       xi:=0;
       yh[1]:=y_0;
       yh[2]:=kr;
       yh_2:=yh;
     end else xi:=xi+hh;
end;
endH:=hh/2;
yb:=yh_2;
writeln(' y(1)=',yh_2[1]:10:10,' y''(1)=',yh_2[2]:10:10,' y`(0)= ', kr:10:10);
end;

procedure srchInterval(var a:real; var b:real);
var c,d,h:real;
    ya:TypY; t:boolean;
begin
a:=-14; h:=0.5; b:=a+h;
DblCheck(ya,a);
if ya[2]>y_1 then t:=true else t:=false;
while (t=(ya[2]>y_1)) do
   begin
     if ya[2]>y_1 then begin t:=true; a:=b; b:=b+h; end else begin t:=false; b:=a; a:=a-h; end;
     DblCheck(ya,a);
   end;
   b:=a; a:=a-h;
end;

procedure strelba;
var  a,b,c,t:real;
     ya,yb,yc:TypY;
Begin
  writeln('Поиск интервала :');
  srchInterval(a,b);
  writeln(' a= ',a:2:2,'   b=',b:2:2);
  DblCheck(ya,a);DblCheck(yb,b);
  repeat
    c:=(a+b)/2;
    DblCheck(yc,c);
    if ((ya[2]-y_1)*(yc[2]-y_1))<0 then begin b:=c; yb:=yc;  end else begin a:=c; ya:=yc; end;
  until (abs(y_1-yc[2])<eps);
 kk:=c;
 writeln('Решение краевой задачи k=y1(0)===',kk:10:10);
end;

Procedure ZapolnX;
var i:integer;
begin
 for i:=0 to 5 do x[i]:=0.2*i;
end;

procedure chek_H;
 var i :integer;
   begin
      for i:=1 to 5 do
      h[i]:=abs(x[i]-x[i-1]);
   end;

procedure zapolnC;
 var i: integer;
  begin
     for i:=1 to 4 do
       begin
          if (i-1)<>0 then c[i,i-1]:=h[i]/6;
          c[i,i]:=(h[i]+h[i+1])/3;
          if i<>(4) then c[i,i+1]:=h[i+1]/6;
       end;
  end;

procedure zapolnD;
 var i: integer;
   begin
      for i:=1 to 4 do
       d[i]:=((uzels[i+1]-uzels[i])/h[i+1])-((uzels[i]-uzels[i-1])/h[i]);
   end;

function spline(xx:real):real;
 var i:integer;
     s: real;
  begin
     for i:=1 to 5 do
        if (xx>=x[i-1])and(xx<=x[i]) then break;

     s:=m[i-1]*(x[i]-xx)*(x[i]-xx)*(x[i]-xx)/(6*h[i])
        +m[i]*(xx-x[i-1])*(xx-x[i-1])*(xx-x[i-1])/(6*h[i])
        +(uzels[i-1]-(m[i-1]*h[i]*h[i]/6))*((x[i]-xx)/h[i])
        +(uzels[i]-(m[i]*h[i]*h[i]/6))*((xx-x[i-1])/h[i]);
     spline:=s;
  end;

procedure hod_to(var c:TypC; var d:typD);
 var  b     :real;
      l,i,j :integer;
  begin
     for i:=1 to 3 do
         begin
              for j:=i+1 to 4 do
                  begin
                       b:=c[j,i]/c[i,i];
                       for l:=i to 4 do c[j,l]:=c[j,l]-c[i,l]*b;
                       d[j]:=d[j]-d[i]*b;
                  end;
         end
  end;

procedure hod_back(c:typC; d:typD; var m:typMiX);
 var i,j:integer;
  begin
    for i:=4 downto 1 do
        begin
             m[i]:=d[i];
             for j:=4 downto i+1 do m[i]:=m[i]-c[i, j]*m[j];
             m[i]:=m[i]/c[i, i];
        end;
    m[0]:=0; m[5]:=0;
    for i:=0 to 5 do
        writeln('m[',i,']= ',m[i]:8:4);
    writeln;
  end;

procedure graphik;
 var i:double; j,gm,gd: integer;
     yy:Typy;
     oy,ox:integer;
  begin
     gm:=0; gd:=0;
     initgraph(gm,gd,'L:\BGI');
     cleardevice;
     settextstyle(7,0,3);
     outtextxy(170,50,'Graphic of function from DU');
     setcolor(green);
     outtextxy(190,100,'and interpalation function');
     ox:=20;
     oy:=50;
     uzels[0]:=y_0;
     j:=1;
     yy[1]:=y_0;
     yy[2]:=kk;

    setcolor(white);
    line(ox,0,ox,480);
    line(0,oy,640,oy);

    i:=0;
    moveto(round(i*rastx)+ox,oy-round(y_0*rasty));
    while i<=1 do
       begin
         RungeKutt(i,yy,endh);
         i:=i+endh;
         lineto(round(i*rastx)+ox,oy-round(yy[1]*rasty));
         if round(i*1000000)=round(200000*j) then
           begin
              uzels[j]:=yy[1];
              inc(j);
           end;
       end;
    readkey;
    zapolnX;
    chek_H;
    zapolnC;
    zapolnD;
    hod_to(c,d);
    hod_back(c,d,m);
    setcolor(2);
    i:=0;
    moveto(round(i*rastx)+ox,oy-round(Spline(i)*rasty));
    while i< 1.1 do
       begin
         i:=i+endh;
         lineto(round(i*rastx)+ox,oy-round(Spline(i)*rasty));
       end;

    setcolor(white);
    for j:=0 to 5 do
      circle(round((j/5)*rastx)+ox,oy-round(uzels[j]*rasty),3);
   readkey;
   closegraph;

  end;

Procedure Power;
var x:real; i:integer;
begin
x:=0.12;
while round(x*100)<=round(0.92*100) do
        begin
        if round(x*100)<>round(0.22*100) then
           writeln('Power(',x:2:2,') = ',sqr(spline(x)):8:8);
           x:=x+0.1;
        end;
end;

procedure vivod;
var i: integer;
    yy: typY;
    x:double;
begin
  clrscr;
  x:=0;
  yy[1]:=y_0;
  yy[2]:=kk;
  i:=1;
  writeln('y(',x:2:2,')= ',yy[1]:9:7,'   ','y''(',x:2:2,')= ',yy[2]:9:7,'   ','Spline(',x:2:2,')= ',Spline(x):9:7);
    while x<=1 do
       begin
         RungeKutt(x,yy,endh);
         x:=x+endh;
         if round(x*1000000)=round(50000*i) then
           begin
             writeln('y(',x:2:2,')= ',yy[1]:9:7,'   ','y1(',x:2:2,')= ',
             yy[2]:9:7,'   ','Spline(',x:2:2,')= ',Spline(x):9:7);
             inc(i);
           end;
       end;
    readkey;
end;

var i: integer;
begin
clrscr;
writeln;
strelba;
writeln('Конечный шаг соответствующий точности = ',endh:10:10);
readkey;
graphik;
clrscr;
Power;
readkey;
vivod;
end.