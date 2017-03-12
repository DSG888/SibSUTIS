program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

var
  arr1:array[1..100] of integer;
  i:integer;
begin
  randomize;
  for i:=1 to 100 do
     begin
       arr1 [i] := random (100);
       writeln (arr1 [i]);
     end;
     readln;
end.
