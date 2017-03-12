program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

var
  m1:array of integer;
  I,j,n:Integer;
  sum:Integer;

begin
  try
    readln(i);
    readln(n);
    setlength(m1,i);
    randomize;
      sum:=0;
    for j:=0 to i-1 do
    begin
      m1[j]:=random(n);
      writeln(m1[j]);

       sum:= sum + M1[j];
    end;
  except
    on E:Exception do
      Writeln(E.Classname, ': ', E.Message);
  end;
  writeln (sum);
  readln;
end.
