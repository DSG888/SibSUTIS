program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

var a,b,c,d,x1,x2:real;
begin
  writeln ('vvedite koefficienti pri X^2');
  readln(a);
   writeln ('vvedite koefficienti pri X');
   readln(b);
   writeln ('vvedite koefficienti pri C');
    readln(c);
    d:=(b*b)-4*a*c;
    writeln('a=',a,'; +b=',b,';' ,c);
    if a=0  then
    begin
    if  b=0 then
    writeln ('net kornel')
    else
    writeln ('koren=',c/b:4:2);
    end
    else
    if d<0 then writeln ('d<0')
    else
     begin
       x1:=(-b-sqrt(d))/(2*a);
       x1:=(-b+sqrt(d))/(2*a);
       writeln('x1=',x1:4:2);
       writeln('x2=',x2:4:2);
     end;
     readln;
end.
