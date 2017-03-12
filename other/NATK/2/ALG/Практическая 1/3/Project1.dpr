program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

var
  a:Integer;
begin
 Readln (a);
if (a mod 2)<>0 then writeln ('a nechetnoe')
else writeln ('a chetnoe');
 readln;
end.
