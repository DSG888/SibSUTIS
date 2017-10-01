program kursovik;
uses crt,graph;
const x0=0;y0=1;a=0;b=1;e=0.001;
type mas=array[0..1000] of real;
var 
  l:boolean;f1:text;v1,v2,u1,u2,e1,r1:mas;
  h1,h2,h3,h4,k1,k2,k3,k4,kc,x,h,min,max:real;
  i,k,m1,m2,m3,m4,gt,gm:integer;
function f(x,y:real):real; begin f:=x/y end;
function cx(x:real):integer; begin cx:=round(10+(x-a)/(b-a)*300) end;
function cy(y:real):integer; begin cy:=round(190-(y-min)/(max-min)*180) end;
procedure rk(m:integer;var y:mas);
  begin
    h:=(b-a)/m;y[0]:=1;
    for i:=0 to (m-1) do
     begin 
       k1:=f(a+i*h,y[i]);            k2:=f(a+i*h+h/2,y[i]+k1*h/2);
       k3:=f(a+i*h+h/2,y[i]+k2*h/2); k4:=f(a+i*h+h,y[i]+k3*h);
       kc:=(k1+2*k2+2*k3+k4)/6;
       y[i+1]:=y[i]+kc*h;
     end;
   end;
   procedure elr(m:integer;var y:mas);
  begin
    h:=(b-a)/m;y[0]:=1;
    for i:=0 to (m-1) do
       y[i+1]:=y[i]+f(a+i*h,y[i])*h;
  end;
  procedure gr(c,m:integer;h:real;var y:mas);
    begin
      setcolor(c);writeln(f1);x:=a;
      for i:=0 to m-1 do
        begin
          line(cx(x),cy(y[i]),cx(x+h),cy(y[i+1]));
          writeln(f1,x:12:5,y[i]:16:5);
          x:=x+h;
        end;
      writeln(f1);      writeln(f1);
     end;
  begin
    assign(f1,'ff1.txt');rewrite(f1);
    m1:=5;elr(m1,e1);rk(m1,r1);h1:=h;
    k:=5;
    repeat
      elr(k,v1);k:=k*2;elr(k,v2);
      l:=true;m2:=k div 2;
      if abs(v2[k]-v1[m2])>e then l:=false;
    until l;
    m3:=k;h3:=h;
    k:=5;
    repeat
      rk(k,u1);k:=k*2;rk(k,u2);
      l:=true;m2:=k div 2;
      if (abs(u2[k]-u1[m2])/15)>e then l:=false;
    until l;
    m4:=k;h4:=h;
    gt:=1;gm:=0;initgraph(gt,gm,'e:\pas\bgi');
    i:=10;repeat line(i,5,i,195);i:=i+10 until i>310;
    i:=10;repeat line(5,i,310,i);i:=i+10 until i>190;
    min:=e1[0];max:=min;
    for i:=1 to m1 do
     begin
       if e1[i]>max then max:=e1[i] ;
       if e1[i]<min then min:=e1[i];
     end;
    gr(1,m1,h1,e1);  readln;
    gr(2,m1,h1,r1);   readln;gr(3,m3,h3,v2);  readln;
    gr(1,m4,h4,u2);
    readln;
    closegraph;close(f1);
 end. 
