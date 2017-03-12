program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

var
  i,j,n:integer;
  m1:array of integer;
  V:integer;
  sum:integer;
begin
  try
    writeln('Vvedite razmer massiva');
    readln(i);
    writeln('Vvedite granicu diapazona');
    readln(n);
    setlength(m1,i);
    randomize;
    for j := 0 to length(m1) - 1 do
      begin
        m1[j]:=random(n);
        writeln(m1[j]);
      end;

    writeln('Zadaite chislo kotoroe nuzhno naiti v massive');
    readln(V);
    n:=-1;
    for j := 0 to length(m1)-1 do
      begin
        if m1[j]=v then
        n:=j;
      end;
      if n=-1 then
      writeln('')
      else writeln(n);
  except
    on E:Exception do
      Writeln(E.Classname, ': ', E.Message);
  end;
end.
