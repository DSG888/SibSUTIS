program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

var i,y:integer;
 p1,p2,x:real;
begin
writeln('Vvedite radios kolca');
readln(i);
if i<0 then writeln ('radius ne mojet bit < 0')
else
  begin
    writeln('Vvedite radius otverstia');
    readln(y);
    if y<0 then writeln ('Otverstie ne mojet bit < 0') else
    begin
    if y<=i then
      begin
        p1:=PI*(i*i);
        p2:=PI*(y*y);
        x:=p1-p2;
        writeln ('Radius kolca=',x);
      end
    else writeln('Otverstie ne mojet bit  bolshe kolca');
  end;
 readln;

end;

end.
