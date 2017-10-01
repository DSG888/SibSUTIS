uses graph,crt;
type tip=array[0..1]of real;
const kl=6;

var yb_0,yb_1:tip;
    nach_usl:array[1..2,0..1] of real;
    hh,xx,minx:real;
    i,j:integer;
    rez:array[1..2,0..999] of real;
    rez_gr:array[1..2,0..20] of real;
    rez_g2:array[1..3,0..20] of real;
    c:array[0..kl-1,1..kl+1] of real;
    grerror,gd,gm,k:integer;

function ff(x:real):real;
 begin
   ff:=2*x*x*x*x*x-sin(x)-3;
 end;

procedure pol_del;
var
  delta,x,y,c,a,b,e:real;
begin
  clrscr;
  e:=0.001;
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
  while abs((b-a)/2)>=e do
  begin
    c:=(b+a)/2;
    if ff(a)*ff(c)<0 then b:=c
                     else a:=c;
  end;
  minx:=(b+a)/2;
  writeln('Минимальный положительный корень уравнения 2*x^5-sin(x)-3=0  x=',minx:9:8);
  writeln;
end;

function yy(x,y,yr,yrr:real):real;
  begin
   yy:=yrr-cos(yrr)-(x*x+y)-minx*yr;
  end;

function second (x0,y,yr:real):real;
var  x,xr,xl,xpr,l,r,h,left,right:real;
     bool,good,answ,count,i,j,n:integer;
 procedure mch;
  begin
  i:=0;
  repeat
   inc(i);
   xr:=yy(x0,y,yr,right);xl:=yy(x0,y,yr,left);
   xpr:=x;
   x:=(xr*left-xl*right)/(xr-xl);
    if yy(x0,y,yr,x)*xl>0 then left:=x else right:=x;
  until (abs(xpr-x)<0.0001)or(i>10000);
  end;

begin
answ:=0;
l:=-1; r:=1;h:=1;
repeat
h:=h/2;r:=r*2;l:=-r;
repeat
   l:=l+h;bool:=0;
   if yy(x0,y,yr,l)*yy(x0,y,yr,l-h)<0 then
    begin
       bool:=1;
       if l>l-h then begin left:=l-h;right:=l;end else
                     begin left:=l;right:=l-h;end;
       mch;
    end;


until (r=l)or(bool=1);
until bool=1;
second:=x;
end;

procedure heat;
const a=0;b=1;h=0.001;
var  k,t,g,s,fa,fk,fb,simps:real;
     n:integer;
   begin
   g:=0;t:=0;n:=1;
   fa:=rez[2,0];fb:=rez[2,999];
   s:=fa+fb;
    repeat
      k:=a+n*h;
      fk:=rez[2,round(k*1000)]*rez[2,round(k*1000)];
      if n mod 2=0 then g:=g+fk
      else
      t:=t+fk;
      n:=n+1;
    until (k>=b-h);
    simps:=h*(s+4*t+2*g)/3;
    writeln;
    writeln('Q = ',simps:6:8);
 readkey;
end;

function R_K_4(yb_1:tip;hh,xx:real):real;
 procedure F(x:real;Y:tip;var rez:tip);
   begin
     rez[0]:=Y[1];
     rez[1]:=second(x,Y[0],Y[1]);
   end;
 procedure add(var x1:tip;x2:tip);
   begin
    x1[0]:=x1[0]+x2[0];
    x1[1]:=x1[1]+x2[1];
   end;
 procedure mul(x1:tip;x:real;var rez:tip);
   begin
    rez[0]:=x1[0]*x;
    rez[1]:=x1[1]*x;
   end;
 procedure copy(var x1:tip;x2:tip);
   begin
    x1[0]:=x2[0];
    x1[1]:=x2[1];
   end;
var b1,b2,b3,b4,b5:tip; h,log:real;
begin
    h:=(xx-hh)/50;
      repeat
    copy(yb_0,yb_1);

       F(hh,yb_0,b1);
        mul(b1,h/2,b2);
        add(b2,yb_0);
       F(hh+h/2,b2,b2);
        mul(b2,h/2,b3);
        add(b3,yb_0);
       F(hh+h/2,b3,b3);
        mul(b3,h,b4);
        add(b4,yb_0);
       F(hh+h,b4,b4);
          copy(b5,b4);
          mul(b3,2,b3);
          add(b5,b3);
          mul(b2,2,b2);
          add(b5,b2);
          add(b5,b1);
          mul(b5,h/6,b5);
          add(b5,yb_0);
       copy(yb_1,b5);
    hh:=hh+h;
    until hh>=xx;

R_K_4:=yb_1[0];
end;

procedure metod_strelb;
var pr1,shag:real;g:integer;
begin
 shag:=2;           yb_1[1]:=2; g:=0;
    nach_usl[1,0]:=0;    nach_usl[1,1]:=1;
    nach_usl[2,0]:=1;    nach_usl[2,1]:=0.5;  writeln(' METOD STRELB: ');
 repeat g:=g+1;                  write('  ',g,'-y vstrel ');
    yb_1[0]:=nach_usl[1,1];
    xx:=nach_usl[2,0];
    hh:=nach_usl[1,0];

  pr1:=R_K_4(yb_1,hh,xx);
  if abs(pr1-nach_usl[2,1])<shag then shag:=shag/5;
  if pr1>nach_usl[2,1] then yb_1[1]:=yb_1[1]-shag;
  if pr1<nach_usl[2,1] then yb_1[1]:=yb_1[1]+shag;


 writeln('K = ',pr1:5:5);
 until abs(nach_usl[2,1]-pr1 )<0.0001;
end;

procedure R_K_4_2;
 procedure F(x:real;Y:tip;var rez:tip);
   begin
     rez[0]:=Y[1];
     rez[1]:=second(x,Y[0],Y[1]);
   end;
 procedure add(var x1:tip;x2:tip);
   begin
    x1[0]:=x1[0]+x2[0];
    x1[1]:=x1[1]+x2[1];
   end;
 procedure mul(x1:tip;x:real;var rez:tip);
   begin
    rez[0]:=x1[0]*x;
    rez[1]:=x1[1]*x;
   end;
 procedure copy(var x1:tip;x2:tip);
   begin
    x1[0]:=x2[0];
    x1[1]:=x2[1];
   end;
var b1,b2,b3,b4,b5:tip;
    h,log,znach,znach1:real;
begin
    yb_1[0]:=nach_usl[1,1];
    xx:=nach_usl[2,0];
    hh:=nach_usl[1,0];
    h:=0.001;log:=0;
    rez_g2[2,0]:=yb_1[0];
    znach:=0.2;znach1:=0.05;

    repeat
    yb_0[0]:=yb_1[0];
    yb_0[1]:=yb_1[1];

       F(hh,yb_0,b1);
        mul(b1,h/2,b2);
        add(b2,yb_0);
       F(hh+h/2,b2,b2);
        mul(b2,h/2,b3);
        add(b3,yb_0);
       F(hh+h/2,b3,b3);
        mul(b3,h,b4);
        add(b4,yb_0);
       F(hh+h,b4,b4);
          copy(b5,b4);
          mul(b3,2,b3);
          add(b5,b3);
          mul(b2,2,b2);
          add(b5,b2);
          add(b5,b1);
          mul(b5,h/6,b5);
          add(b5,yb_0);
       copy(yb_1,b5);
    rez[2,round(hh*1000)]:=yb_1[0];
    rez[1,round(hh*1000)]:=hh;

    hh:=hh+h;
    if abs(hh-znach)<0.0001 then begin
                        rez_gr[2,round(hh*100) div 20]:=yb_1[0];
                        rez_gr[1,round(hh*100) div 20]:=hh;znach:=znach+0.2;
                                     end;
    if abs(hh-znach1)<0.0001 then begin
                        rez_g2[2,round(hh*100) div 5]:=yb_1[0];
                        rez_g2[1,round(hh*100) div 5]:=hh;znach1:=znach1+0.05;
                                     end;
    until hh>=xx;


    rez_gr[2,0]:=nach_usl[1,1];                                               rez_g2[2,0]:=nach_usl[1,1];

end;

procedure draw;
const path_of_driver='D:\TP\bgi';
      si=230;
procedure init_c;
 begin
for j:=3 to kl+1 do
for i:=0 to kl-j+1 do
c[i,j]:=c[i+1,j-1]-c[i,j-1];
 end;

function njuton1(xx:real):real;
var s,q,qq,k:real;
 begin
 s:=c[0,2];q:=1;k:=1;qq:=(xx-c[0,1])/(c[1,1]-c[0,1]);
 for i:=0 to kl-2 do
   begin
     q:=q*(qq-i);
     k:=k*(i+1);
     s:=s+c[0,3+i]*q/k;
   end;
 njuton1:=s;
 end;


procedure draw;
var i,j:integer;
begin
setcolor(7);
for i:=0 to kl-1 do circle(320+round(c[i,1]*si),240-round(c[i,2]*si),3);
end;

procedure dra;
var x0,y0,xp,yp,xg0,yg0,xg,yg:longint;
    x:real;
begin
x0:=0;xg0:=0;
x:=0;
repeat
setcolor(7);
  xp:=round(x*si)+320;
        yp:=240-round(njuton1(x)*si);
                  if x0<>0 then line(xp,yp,x0,y0);
  x0:=xp;y0:=yp;
  if x<=1.05 then rez_g2[3,round(x*20)]:=njuton1(x);
x:=x+0.05;
until x>1.05;
end;


begin
      clrscr;
 for i:=0 to kl-1 do
  begin
   c[i,2]:=rez_gr[2,i];
   c[i,1]:=rez_gr[1,i];
  end;
      init_c;

  gd:=detect;
  initgraph(gd,gm,path_of_driver);
      begin
      setcolor(10);
      line(320,0,320,480);
      line(0,240,640,240);
setcolor(10);
for i:=0 to 14 do circle(320+round(rez[1,(i*70)]*si),240-round(rez[2,(i*70)]*si),2);
      draw;
      dra;
      end;
end;

begin
pol_del;
metod_strelb;
R_K_4_2;
  writeln;
  for i:=0 to 5 do writeln('y(',rez_gr[1,i]:2:2,')=',rez_gr[2,i]:5:5,'  ');
heat;
draw;
readkey;
closegraph;
  clrscr;
  for i:=0 to 20 do writeln('x=',rez_g2[1,i]:2:2,'  y=',rez_g2[2,i]:8:8,'  p=',rez_g2[3,i]:8:8,'    ');
  readkey;
end.
