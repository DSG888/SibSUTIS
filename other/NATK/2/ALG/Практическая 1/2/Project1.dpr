program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

var
  a:integer;
begin
readln (a);
if a=0 then writeln ('a=0');
if a>0 then
writeln ('a>0');
if a<0 then
writeln ('a<0');
readln;
end.
