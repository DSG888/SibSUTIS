program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

var a:real;
begin
writeln('vvedite stoimost pokypki');
readln (a);
if (a<500)  then writeln (a:5:2);
if (a<1000) and (a>=500) then writeln (a-(3*a/100):5:2);
if (a>=1000)   then writeln (a-(a*5/100):5:2);
readln;
end.
