 uses crt,graph;
const n=5;
      Yo=1;
      Xo=0;
      eps_mpd=0.2;
      eps_newton=0.001;
      eps_strelb=0.001;
      eps_runge=0.01;
      h=0.1;
      x_spline:array[0..n] of real= (0,0.2,0.4,0.6,0.8,1);
      x_power:array[1..8] of real=(0.12,0.32,0.42,0.52,0.62,0.72,0.82,0.92);
type  data=record
      k:real;
      l:real;
     end;
     mas_runge=array[1..2] of real;
     mas_koeficent=array[1..4] of data;
     mas_pereschet=array[1..5000] of real;
     mas_spline=array[0..n] of real;
     mass_c=array[1..n-1,1..n-1] of real;
     mass_h=array[1..n] of real;
     mass_d=array[1..n-1] of real;
     mas_power=array[1..8] of real;
var an,bn,cn,yx,dif_x,sh,k:real;
   Y,Y0:mas_runge;
   koeficent:mas_koeficent;
   yh,yh2:mas_pereschet;
   y_power:mas_power;
   y_spline:mas_spline;
   i,j,gd,gm:integer;
   h_spline:mass_h;
   m_spline:mas_spline;
   d_spline,a_spline,b_spline,c1_spline:mass_d;
   c_spline:mass_c;
function y1(x,y,y2:real):real;
begin
     y1:=y2-cos(y2+sqr(x))+2.9*y;
end;
function y_first(x,y:real):real;
begin
     y_first:=1+sin(y+sqr(x));
end;
procedure divider1(x,y,shag:real);
var   x_0,shag_0,koef,x1,x2,rab:real;
   i:integer;
   old:array[1..2] of real;
   root:boolean;
begin
     root:=false;
     x_0:=0;
     shag_0:=shag;
     koef:=1;
     for  i:=1 to 2 do
     old[i]:=y1(x,y,x_0);
     repeat
           for i:=1 to 2 do
           begin
               x1:=koef*x_0;x2:=koef*shag_0;
               rab:=y1(x,y,x2);
               if old[i]*rab<0 then
                  begin
                  Root:=true;
                  an:=x1; bn:=x2;
                  repeat
                    cn:=(an+bn)/2;
                    if y1(x,y,cn)*y1(x,y,bn)<0 then an:=cn else bn:=cn;
                  until abs((bn-an)/2 )<=eps_mpd;
                  end;
                  old[i]:=rab;
               koef:=-koef;
           end;
           x_0:=shag_0;  shag_0:=shag_0+shag;
until root;
end;
Function Dif_ur(x,y:real):real;
 function Newton(x,y:real):real;
 var
   x_0,x1,x2:real;
   i:integer;
 begin
    divider1(x,y,1);
    x_0:=an;
     repeat
          x1:=x_0-y1(x,y,x_0)/y_first(x,x_0);
          x2:=x_0;
          x_0:=x1;
     until abs(x2-x1)<eps_newton;
     Newton:=x1;
 end;
begin
     Dif_ur:=Newton(x,y);
end;
procedure Big_Y(x,y2,y3:real);
begin
     Y[1]:=y3;
     Y[2]:=dif_ur(x,y2);
end;
procedure Make_K(x,shag:real);
begin
     big_y(x,y0[1],y0[2]);
     koeficent[1].k:=y[1];
     koeficent[1].l:=y[2];
     big_y(x+shag/2,y0[1]+(shag/2)*koeficent[1].k,y0[2]+(shag/2)*koeficent[1].l);
     koeficent[2].k:=y[1];
     koeficent[2].l:=y[2];
     big_y(x+shag/2,y0[1]+(shag/2)*koeficent[2].k,y0[2]+(shag/2)*koeficent[2].l);
     koeficent[3].k:=y[1];
     koeficent[3].l:=y[2];
     big_y(x+shag,y0[1]+shag*koeficent[3].k,y0[2]+shag*koeficent[3].l);
     koeficent[4].k:=y[1];
     koeficent[4].l:=y[2];
end;
function RungeKutt(m,shag,k:real):real;
var
   i:integer;
   x:real;
begin
 x:=xo;
  for i:=1 to trunc((m-xo)/shag) do
  begin
     make_k(x,shag);
     y0[1]:=y0[1]+(shag/6)*(koeficent[1].k+2*koeficent[2].k+2*koeficent[3].k+koeficent[4].k);
     y0[2]:=y0[2]+(shag/6)*(koeficent[1].l+2*koeficent[2].l+2*koeficent[3].l+koeficent[4].l);
     yh2[i]:=y0[1];
     x:=x+shag;
  end;
  RungeKutt:=y0[2];
  yx:=y0[1];
  dif_x:=y0[2];
   y0[1]:=yo;
   y0[2]:=k;
end;
function Pereschet(m,shag,k:real):real;
var   rez,old_yx,old_dif_x:real;
   c,i:integer;
begin    c:=1;
    rungekutt(m,shag,k);
    repeat
           c:=0; yh:=yh2;
           old_yx:=yx;
           old_dif_x:=dif_x;
           shag:=shag/2;
           rez:=RungeKutt(m,shag,k);
           for i:=1 to round((m-xo)/(2*shag)) do
               if abs(yh[i]-yh2[2*i])>=15*eps_runge then inc(c);
    until c=0;
    pereschet:=rez+(1/15)*(rez-old_dif_x);yx:=yx+(1/15)*(yx-old_yx);sh:=shag;
end;
function Strelba(k:real):real;
begin
     y0[1]:=yo;
     y0[2]:=k;
     strelba:=pereschet(1,h,k)-0.2;
end;
procedure divider;
var   x_0,shag,x1,x2,rab,a,b,c,c1:real;
   i,koef:integer;
   old:array[1..2] of real;
   root:boolean;
begin
     root:=false;
     x_0:=0;     shag:=1;     koef:=1;
     for  i:=1 to 2 do
     old[i]:=strelba(0);
     repeat
           for i:=1 to 2 do
               begin
               x1:=koef*x_0;x2:=koef*shag;
               rab:=strelba(x2);
               if old[i]*rab<0 then
                  begin
                  Root:=true; a:=x1; b:=x2;
                  repeat
                        c:=(a+b)/2;
                        if strelba(c)*strelba(b)<0 then a:=c else b:=c;
                  until abs((b-a)/2 )<=eps_mpd;
                  Repeat
                        c:=(strelba(b)*a-strelba(a)*b)/(strelba(b)-strelba(a));
                        if strelba(a)*strelba(c)<0 then b:=c
                        else a:=c;
                        c1:=(strelba(b)*a-strelba(a)*b)/(strelba(b)-strelba(a));
                  until (abs(c-c1)<eps_strelb);
                  k:=c1;
                  end;
                  old[i]:=rab;
               koef:=-koef;
               end;
           x_0:=shag; shag:=shag+1;
until root;
end;
procedure  make_h;
var   i:integer;
begin
     for i:=1 to n do
     h_spline[i]:=x_spline[i]-x_spline[i-1];
end;
procedure make_d;
var   i:integer;
begin
     for i:=1 to n-1 do
     d_spline[i]:=((y_spline[i+1]-y_spline[i])/h_spline[i+1]-(y_spline[i]-y_spline[i-1])/h_spline[i]);
end;
procedure make_c;
var   i,j:integer;
begin
     for i:=1 to n-1 do
     begin
     for j:=1 to n-1 do
     if i=j then
                 c_spline[i,j]:=(h_spline[i]+h_spline[i+1])/3
     else
     if j=i+1 then
                 c_spline[i,j]:=h_spline[i+1]/6
     else
     if  i=j+1 then
                 c_spline[i,j]:=h_spline[i]/6
     else
     c_spline[i,j]:=0;
     end;
end;
procedure abc;
var   k:integer;
   i,j:integer;
begin
     for k:=1 to n-1 do
     a_spline[k]:=c_spline[k,k];
     for i:=1 to n-1 do
     begin
     for j:=1 to n-1 do
     begin
     if  i=j+1 then
     c1_spline[j]:=c_spline[i,j];
        if  j=i+1 then
     b_spline[j]:=c_spline[i,j];
     end;
     end;
end;
procedure MethodProgonki;
type mas=array[0..n-1] of real;
var   alfa,beta:mas;
   k:integer;
begin
     for k:=1 to n-1 do
     begin
       alfa[k]:=-c1_spline[k]/(a_spline[k]+b_spline[k]*alfa[k-1]);
       beta[k]:=(d_spline[k]-b_spline[k]*beta[k-1])/(a_spline[k]+b_spline[k]*alfa[k-1]);
     end;
     for k:=n-1 downto 1 do
       m_spline[k]:=alfa[k]*m_spline[k+1]+beta[k];
end;
function FindInterval(perem:real):integer;
var   i:integer;
begin
if (perem<=x_spline[n])and(perem>=x_spline[0]) then
     begin
        if perem=x_spline[0] then
        Findinterval:=1
        else
        for i:=0 to n-1 do
          if (perem>x_spline[i])and(perem<=x_spline[i+1])
          then
            FindInterval:=i+1
     end
end;
function s(perem:real):real;
var i:byte;
begin
    i:=FindInterval(perem);
    s:=(m_spline[i-1]*(x_spline[i]-perem)*(x_spline[i]-perem)*(x_spline[i]-perem)) /(6*h_spline[i])
    +(m_spline[i]*(perem-x_spline[i-1])*(perem-x_spline[i-1])*(perem-x_spline[i-1]))/(6*h_spline[i])
    +(y_spline[i-1]-(m_spline[i-1]*h_spline[i]*h_spline[i])/6)*(x_spline[i]-perem)/h_spline[i]
    +((y_spline[i]-(m_spline[i]*h_spline[i]*h_spline[i])/6)*(perem-x_spline[i-1]))/h_spline[i];
end;
procedure Graphic;
var   gd,gm,i:integer;
   xx,xmin,xmax,ymin,ymax:real;
   st:string;
   ch:char;
function kx(x:real):integer;
begin
     kx:=round(590*(x-xmin)/(xmax-xmin));end;
function ky(y:real):integer;
begin
     ky:=(450-round(440*(y-ymin)/(ymax-ymin)));
end;
begin
     gd:=detect;
     initgraph(gd,gm,'bgi');
     xmin:=x_spline[0];
     xmax:=x_spline[n];
     xx:=xmin;   ymin:=0;     ymax:=0;
     while xx<=xmax do
      begin
           if ymin>s(xx) then ymin:=s(xx);
           if ymax<s(xx) then ymax:=s(xx);
           xx:=xx+0.01;
      end;
     xx:=xmin;
     setcolor(cyan);
     setlinestyle(0,0,3);
     moveto(kx(xx),ky(s(xx)));
     while xx<=xmax do
      begin
           lineto(kx(xx),ky(s(xx)));
           xx:=xx+0.01;
      end;
     setcolor(lightred);
     for i:=0 to n do
         circle(kx(x_spline[i]),ky(y_spline[i]),2);
     ch:=readkey;
     if ord(ch)=ord('+') then
     begin
          setcolor(8);
          setlinestyle(1,0,1);
          for i:=0 to n do
              begin
                   line(kx(x_spline[i]),ky(y_spline[i]),getmaxx,ky(y_spline[i]));
                   line(kx(x_spline[i]),ky(y_spline[i]),kx(x_spline[i]),getmaxy);
              end;
          setcolor(yellow);
          for i:=0 to n do
              begin
                   str(x_spline[i]:2:1,st);
                   outtextxy(kx(x_spline[i]),getmaxy-7,st);
                   str(y_spline[i]:3:2,st);
                   outtextxy(getmaxx-40,ky(y_spline[i])-2,st);
              end;
          setcolor(13);
          setlinestyle(0,0,1);
          pereschet(0,h,k);
          moveto(kx(0),ky(yx));
          pereschet(1,h,k);
          for j:=1 to trunc(1/h) do
               lineto(kx(j*h),ky(yh2[trunc(j*h/sh)]+(1/15)*(yh2[trunc(j*h/sh)]-yh[trunc(j*h/(2*sh))])));
     end
     else exit;
     readln;
     closegraph;
     restorecrtmode;
end;
begin gd:=0;
     initgraph(gd,gm,'c:\tp\bgi');
     settextstyle(0,0,4);
     outtextxy(130,200,'Please wait!');
   divider;
     closegraph;
     restorecrtmode;
clrscr;
       y0[1]:=yo; y0[2]:=k;
       writeln('k=',k:10:8);
       pereschet(0.92,0.01,k);
       for  i:=1 to 8 do
       begin
            j:=trunc(x_power[i]/sh);
            y_power[i]:=sqr(yh2[j]+(1/15)*(yh2[j]-yh[trunc(j/2)]));
       end;
       y_spline[0]:=yo;
       pereschet(1,h,k);
       for i:=1 to 5 do
       begin
            j:=trunc(x_spline[i]/sh);
            y_spline[i]:=yh2[j]+(1/15)*(yh2[j]-yh[trunc(j/2)]);
       end;
       writeln('Мощность в точке');
       for i:=1 to 8 do
       writeln(x_power[i]:7:2,'       ',y_power[i]:7:5);
       readln;
       clrscr;
       Make_h; Make_c; Make_d;abc;
       MethodProgonki;
       pereschet(0,h,k);
       writeln('x=0.00','  Delta=',(yx-s(0)):12:10);
       pereschet(1,h,k);
       for j:=1 to trunc(1/h) do
       writeln('x=',j*h:3:2,'  Delta=',
       abs(s(j*h)-(yh2[trunc(j*h/sh)]+(1/15)*(yh2[trunc(j*h/sh)]-yh[trunc(j*h/(2*sh))]))):12:10);
       readln;
       Graphic;
end.