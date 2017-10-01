uses graph,crt;
type tip=array[0..1]of real;
const n=2;kl=6;

var yb_0,yb_1:tip;
    nach_usl:array[1..2,0..1]of real;
    hh,xx:real;
    i,j:integer;
    rez,rez_gr:array[1..2,0..20]of real;
    rez_g2:array[1..3,0..20]of real;
    c:array[0..kl-1,1..kl+1]of real;
    grerror,gd,gm,k:integer;

function y_(x,y,yr,yrr:real):real;
  begin
   y_:=yrr+sin(yrr)-x-sin(1.4*yr)-2.3*y;
  end;

function find_yss(x0,y,yr:real):real;
var  x,xr,xl,xpr,l,r,h,left,right:real;
     bool,good,answ,count,i,j,n:integer;
 procedure xorda;
  begin
  i:=0;
  repeat
   inc(i);
   xr:=y_(x0,y,yr,right);xl:=y_(x0,y,yr,left);
   xpr:=x;
   x:=(xr*left-xl*right)/(xr-xl);
    if y_(x0,y,yr,x)*xl>0 then left:=x else right:=x;
    if i>10000 then begin bool:=0;write(' fuck ');exit;end;
  until (abs(xpr-x)<0.0001)or(i>10000);
  end;

begin                                                  {  write(' yss ');}
answ:=0;
l:=-1; r:=1;h:=1;
repeat
h:=h/2;r:=r*2;l:=-r;
repeat
   l:=l+h;bool:=0;
   if y_(x0,y,yr,l)*y_(x0,y,yr,l-h)<0 then
    begin
       bool:=1;
       if l>l-h then begin left:=l-h;right:=l;end else
                     begin left:=l;right:=l-h;end;
       xorda;
    end;


until (r=l)or(bool=1);
until bool=1;
find_yss:=x;
end;



function hiler(yb_1:tip;hh,xx:real):real;{Эйлер}
 procedure F(x:real;Y:tip;var rez:tip);
   begin
     rez[0]:=Y[1];
     rez[1]:=find_yss(x,Y[0],Y[1]);
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
var b1,b2,b3,b4,b5:tip; h:real;
begin
      h:=(xx-hh)/50;
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
    hh:=hh+h;
    until hh+0.0000001>=xx;

hiler:=yb_1[0];
end;

{*************************************************************************}
{*************************************************************************}

procedure generator;
var um,uv,pr0,pr1,cd:real;
begin
         pr0:=20;     uv:=1;um:=0;   yb_1[1]:=2{1};                  cd:=10;
    nach_usl[1,0]:=0;    nach_usl[1,1]:=1;
    nach_usl[2,0]:=1;    nach_usl[2,1]:=5;
 repeat                                              write('   generator ');
    yb_1[0]:=nach_usl[1,1];
    xx:=nach_usl[2,0];
    hh:=nach_usl[1,0];

  pr1:=hiler(yb_1,hh,xx);
  if cd>abs(pr1-nach_usl[2,1])then cd:=abs(pr1-nach_usl[2,1]);
  if abs(pr0-nach_usl[2,1])>abs(pr1-nach_usl[2,1]) then
     if uv=1 then yb_1[1]:=yb_1[1]+1*cd else
                  yb_1[1]:=yb_1[1]-1*cd;

  if abs(pr0-nach_usl[2,1])<abs(pr1-nach_usl[2,1]) then
     if uv=1 then begin uv:=0;um:=1;yb_1[1]:=yb_1[1]-1.5*cd;cd:=0.3*cd;end else
                  begin uv:=1;um:=0;yb_1[1]:=yb_1[1]+1.5*cd;cd:=0.3*cd;end;

  pr0:=pr1;
  write(pr1:5:5,'   ');
 until abs(nach_usl[2,1]-pr1 )<0.0001;
    writeln;
    writeln('    y"=',yb_1[1]:4:8);
end;


{*************************************************************************}
{*************************************************************************}

procedure hiler2;
 procedure F(x:real;Y:tip;var rez:tip);
   begin
     rez[0]:=Y[1];
     rez[1]:=find_yss(x,Y[0],Y[1]);
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
    yb_1[0]:=nach_usl[1,1];
    xx:=nach_usl[2,0];
    hh:=nach_usl[1,0];
    h:=0.01;log:=0;
    rez_g2[2,0]:=yb_1[0];

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
    if log=1 then  begin
            rez[2,round(hh*100) div 10]:=yb_1[0];
            rez[1,round(hh*100) div 10]:=hh+0.01;
            log:=0;
                    end;
    if (round(hh*100) mod 10)=0 then log:=1;

        hh:=hh+h;
    if (round(hh*100) mod 20)=0 then begin
                        rez_gr[2,round(hh*100) div 20]:=yb_1[0];
                        rez_gr[1,round(hh*100) div 20]:=hh;
                                     end;
    if (round(hh*100) mod 5)=0 then begin
                        rez_g2[2,round(hh*100) div 5]:=yb_1[0];
                        rez_g2[1,round(hh*100) div 5]:=hh;
                                     end;
    until hh>=xx;


    rez_gr[2,0]:=nach_usl[1,1];

end;

{*************************************************************************}
{*************************************************************************}


procedure draw;
const path_of_driver='d:\tp\bgi';
      si=30;
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
for i:=0 to kl-1 do circle(320+round(c[i,1]*si),240-round(c[i,2]*si),2);
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
until x>1.5;
end;


begin                  {1 stroka  2 stolb}
      clrscr;
 for i:=0 to kl-1 do
  begin
   c[i,2]:=rez_gr[2,i];
   c[i,1]:=rez_gr[1,i];
  end;
      init_c;

  gd:=detect;
  initgraph(gd,gm,path_of_driver);
  grerror:=graphresult;
  if grerror<>0 then
    begin
      write('error:',grerror);
      halt(1);
    end
    else
      begin
      setcolor(10);
      rectangle(0,0,639,479);
      line(320,0,320,480);
      line(0,240,640,240);

setcolor(10);
for i:=1 to 9 do circle(320+round(rez[1,i]*si),240-round(rez[2,i]*si),2);

      draw;
      dra;
      end;
end;



begin
  clrscr;
  generator;{ создание y''(a)}

  hiler2;
  writeln;
  for i:=1 to 9 do write('y^2(',rez[1,i]:2:2,')=',sqr(rez[2,i]):5:5,'  ');
  writeln;
  writeln;
  for i:=1 to 9 do write('y(',rez[1,i]:2:2,')=',rez[2,i]:5:5,'  ');
  writeln;
  for i:=0 to 5 do write('y(',rez_gr[1,i]:2:2,')=',rez_gr[2,i]:5:5,'  ');
  writeln;
  writeln;
  writeln;
  readkey;
   draw;  readkey;
  closegraph;
  clrscr;
  for i:=0 to 20 do writeln('x=',rez_g2[1,i]:2:2,'  y=',rez_g2[2,i]:5:5,'  p=',rez_g2[3,i]:5:5,'    ');
  readkey;
  readkey;
end.

