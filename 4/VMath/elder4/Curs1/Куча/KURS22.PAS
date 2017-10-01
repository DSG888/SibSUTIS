uses crt, graph;
const eps=0.0001;
      y_0=1;
      y_1=0.5;
      rastx=400;
      rasty=200;
type
  qY=array[1..2] of real;
  qC=array[1..4,1..4] of real;
  qD=array[1..4] of real;
  qMiX=array[0..5] of real;
  qh=array[1..5] of real;
var kkk:real;
    yy:qY;
    EndH:real;
    c: qc;
    d: qD;
    m,x,sp: qMix;
    h: qH;

function f(x:real; y:real; y1:real; y2:real):real;
begin
f:=y2+sin(y2)+y+x*x+y1;
end;

procedure searchInt(var a:real; var b:real; x:real; y:real; y1:real);
var c,d,h,fa,fb: real;
    i: integer;
begin
c:=-1; d:=1 ;h:=1; a:=c; b:=a+h;
fa:=1; fb:=1;
 while fa*fb>0 do
   begin
   a:=c;b:=a+h;
   fa:=f(x,y,y1,a); fb:=f(x,y,y1,b);
   while b<d do
      begin a:=b;
            b:=b+h;
            fa:=fb;
            fb:=f(x,y,y1,b);
            if fa*fb<0 then break;
      end;
      c:=c-1; d:=d+1; h:=h/2;
   end;
end;


procedure Mh(x:real; y:real; y1:real; var kr:real);
var fa,fb,fc,c,cp,a,b:real;
begin
     searchInt(a,b,x,y,y1);
     fa:=f(x,y,y1,a);fb:=f(x,y,y1,b);
     c:=0; cp:=(fb*a-fa*b)/(fb-fa);
     While (abs(cp-c)>eps) do
      begin
        c:=cp;
        fc:=f(x,y,y1,c);
        if fa*fc<0 then begin b:=c; fb:=fc; end
        else begin a:=c; fa:=fc; end;
        cp:=(fb*a-fa*b)/(fb-fa);
      end;
        kr:=cp;
end;

function Dif(x:real; y:real; y1:real):real;
var a,b,kk:real;
begin
Mh(x,y,y1,kk);
dif:=kk;
end;


function R_K4(xi:real; var Y:qY; h:real):real;{выдает Yi+1}
var K:array[1..4,1..2] of real;
    rrr:qY;
begin
k[1,1]:=y[2]; k[1,2]:=dif(xi,y[1],y[2]);
k[2,1]:=y[2]+(h/2)*k[1,2]; k[2,2]:=dif(xi+h/2,y[1]+(h/2)*k[1,1],y[2]+(h/2)*k[1,2]);
k[3,1]:=y[2]+(h/2)*k[2,2]; k[3,2]:=dif(xi+h/2,y[1]+(h/2)*k[2,1],y[2]+(h/2)*k[2,2]);
k[4,1]:=y[2]+h*k[3,2]; k[4,2]:=dif(xi+h,y[1]+h*k[3,1],y[2]+h*k[3,2]);
y[1]:=y[1]+(h/6)*(k[1,1]+2*k[2,1]+2*k[3,1]+k[4,1]);
y[2]:=y[2]+(h/6)*(k[1,2]+2*k[2,2]+2*k[3,2]+k[4,2]);
end;

procedure D_P(var Yb:qY; kr:real);
var hh, xi:real;
    Yh,Yh_2:qY;
    i: integer;
begin
hh:=0.05;
xi:=0;
yh[1]:=y_0;
yh[2]:=kr;
yh_2:=yh;
While (xi<1) do
  begin
  R_K4(xi,Yh,hh);
  R_K4(xi,Yh_2,hh/2);
  R_K4(xi+hh/2,Yh_2,hh/2);

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
writeln(' y(1)=', yh_2[1]:10:10,'     y"(1)= ',yh_2[2]:10:10);
end;

procedure searchInt1(var a:real; var b:real);
var c,d,h:real;
    ya:qY; t:boolean;
begin
a:=-2; h:=0.5; b:=-1.5;
D_P(ya,a);
if ya[1]<y_1 then t:=true else t:=false;
while (t=(ya[1]<y_1)) do
   begin
     if ya[1]<y_1 then begin t:=true; a:=b; b:=b+h; end else begin t:=false; b:=a; a:=a-h; end;
     D_P(ya,a);
   end;
   b:=a; a:=a-h;
end;

procedure strelba;
var  a,b,c,t:real;
     ya,yb,yc:qY;
Begin
  writeln('Search int :');
  searchInt1(a,b);
  writeln(' a= ',a:2:2,'   b=',b:2:2);
  D_P(ya,a);D_P(yb,b);
  repeat
    c:=(a+b)/2;
    D_P(yc,c);
    if ((ya[1]-y_1)*(yc[1]-y_1))<0 then begin b:=c; yb:=yc;  end else begin a:=c; ya:=yc; end;
  until (abs(y_1-yc[1])<eps);
 kkk:=c;
  writeln(' k=y1(0)=',kkk:10:10);
end;

Procedure z_X;
var i:integer;
begin
 for i:=0 to 5 do x[i]:=0.2*i;
end;

procedure p_H;
 var i :integer;
   begin
      for i:=1 to 5 do
      h[i]:=abs(x[i]-x[i-1]);
   end;

procedure z_C;
 var i: integer;
  begin
     for i:=1 to 4 do
       begin
          if (i-1)<>0 then c[i,i-1]:=h[i]/6;
          c[i,i]:=(h[i]+h[i+1])/3;
          if i<>(4) then c[i,i+1]:=h[i+1]/6;
       end;
  end;
procedure z_D;
 var i: integer;
   begin
      for i:=1 to 4 do
       d[i]:=((sp[i+1]-sp[i])/h[i+1])-((sp[i]-sp[i-1])/h[i]);
   end;

function spline(xx:real):real;
 var i:integer;
     s,t,t1: real;
  begin
     for i:=1 to 5 do
        if (xx>=x[i-1])and(xx<=x[i]) then break;
       t:= x[i]-xx;
       t1:=xx-x[i-1];
     s:=m[i-1]*t*t*t/(6*h[i])+m[i]*t1*t1*t1/(6*h[i])
        +(sp[i-1]-(m[i-1]*h[i]*h[i]/6))*(t/h[i])
        +(sp[i]-(m[i]*h[i]*h[i]/6))*(t1/h[i]);
     spline:=s;
  end;

procedure hod_pr(var c:qC; var d:qD);
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

procedure back(c:qC; d:qD; var m:qMiX);
 var i,j:integer;
  begin
    for i:=4 downto 1 do
        begin
             m[i]:=d[i];
             for j:=4 downto i+1 do m[i]:=m[i]-c[i, j]*m[j];
             m[i]:=m[i]/c[i, i];
        end;
    m[0]:=0; m[5]:=0;
    writeln;
  end;

procedure graphik;
 var i,t,h:real; j,gm,gd,e: integer;
     yy:qy;
     oy,ox:integer;
     st:string;
  begin
     gm:=0; gd:=0;
     initgraph(gm,gd,'c:\tp\bgi');
     cleardevice;
     setcolor(white);
     ox:=30;
     oy:=460;
     sp[0]:=y_0;
     j:=1;
     yy[1]:=y_0;
     yy[2]:=kkk;
     line(ox,0,ox,480);
    line(0,oy,640,oy);
    line(30,0,23,4);
    line(30,0,37,4);
    line(640,460,632,457);
    line(640,460,632,463);
    outtextxy(630,465,'Y');
    outtextxy(2,10,'X');
    for e:=1 to 5 do begin
    line(25+e*80,455,25+e*80,465);
    line(25,470-(12+e*40),35,470-(12+e*40));
    str(e/5:3:1,st);
    outtextxy(25+e*80,470,st);
    outtextxy(5,470-(15+e*40),st);
    end;
    setcolor(1);
    i:=0;
    moveto(round(i*rastx)+ox,oy-round(y_0*rasty));
    while i<=1 do
       begin
         r_K4(i,yy,endh);
         i:=i+endh;
         lineto(round(i*rastx)+ox,oy-round(yy[1]*rasty));
         if round(i*1000000)=round(200000*j) then
           begin
              sp[j]:=yy[1];
              inc(j);
           end;
       end;
    readkey;
    z_X;
    p_H;
    z_C;
    z_D;
    hod_pr(c,d);
    back(c,d,m);
    setcolor(4);
    i:=0;
    moveto(round(i*rastx)+ox,oy-round(Spline(i)*rasty));
    while i< 1 do
       begin
         i:=i+endh;
         lineto(round(i*rastx)+ox,oy-round(Spline(i)*rasty));
       end;

    setcolor(3);
    for j:=0 to 5 do
      circle(round((j/5)*rastx)+ox,oy-round(sp[j]*rasty),3);
   readkey;
   closegraph;

  end;

Procedure Moschn;
var x:real; i:integer;
begin
x:=0.12;
while round(x*100)<=round(0.92*100) do
        begin
        if round(x*100)<>round(0.22*100) then
           writeln('Moscnost(',x:2:2,') = ',spline(x)*spline(x):10:10);
           x:=x+0.1;
        end;
end;
procedure vivod;
var i,k: integer;
    yy: qY;
    x:real;
begin
  clrscr;
  x:=0;
  yy[1]:=y_0;
  yy[2]:=kkk;
  i:=1;
  writeln('y(',x:2:2,')= ',yy[1]:10:9, '   ',  'Interpolation(',x:2:2,')= ',Spline(x):10:9);
    while x<=1 do
       begin
         r_K4(x,yy,endh);
         x:=x+endh;
         if round(x*10000000)=round(500000*i) then
           begin
             writeln('y(',x:2:2,')= ',yy[1]:10:9,'   ',
              'Interpolation(',x:2:2,')= ',spline(x):10:9);
             inc(i);
           end;
       end;
    readkey;

end;

var i: integer;
begin
clrscr;
writeln;
writeln('       _');
writeln('      | y"-(x*x+y)+y""+sin(y"")=2y" ');
writeln('     <| y(0)=1 ');
writeln('      |_y(1)=0.5 ');
writeln;
strelba;
readkey;
graphik;
clrscr;
Moschn;
readkey;
vivod;

end.













