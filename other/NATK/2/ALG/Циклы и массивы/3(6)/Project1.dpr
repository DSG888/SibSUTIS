program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

var
     arr: array [1..100] of integer;
   t,i,n,k,min,imin:integer;
begin
   readln(i, n, k);
   randomize;
   for t:=1 to i do
     begin
       arr[t] := random(k)+n;
       writeln('[',t,']=', arr[t]);
     end;
    min:=arr[1];
    for t:=2 to i-1 do
      if min >arr[t] then
         begin
           min:= arr[t];
           imin:= t;
         end;
     writeln('min value - [', imin,']=',min);
     readln;
end.
