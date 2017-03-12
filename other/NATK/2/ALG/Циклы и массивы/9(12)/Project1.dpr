program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

var
    m1:array of integer;
  i,j,n,m:Integer;
  sum:real;

begin
  try
    writeln('Vvedite dliny massiva');
    readln(i);
    writeln('Vvedite nachalo diapazona');
    readln(n);
    writeln('Vvedite konez diapazona');
    readln(m);
    if i<=0 then
    begin
      writeln('Ne iz chego schitat srednee arifmeticheskoe');
      readln;
      exit;
    end;
    setlength(m1,i);
    randomize;
      sum:=0;
    for j:=0 to i-1 do
    begin
      m1[j]:=random(m-n+1)+n;
      writeln(m1[j]);
      sum:= sum + M1[j];
    end;
    sum:=sum/i;
  writeln (sum);
  readln;

  except
    on E:Exception do
      Writeln(E.Classname, ': ', E.Message);
  end;

end.
