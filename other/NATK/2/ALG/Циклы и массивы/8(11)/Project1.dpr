program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

var
  i,j,n:integer;
  m1:array of integer;
  sum:integer;
  ind:integer;
begin
  try
    writeln('Vvedite dliny massiva');
    readln(i);
    writeln('Vvedite diapazon massiva');
    readln(n);
    setlength(m1,i);
    randomize;
    m1[0]:=random(n);
    sum:=m1[0];
    writeln(m1[0]);
    ind:=0;
    for j:=1 to i - 1 do
      begin
        m1[j]:=random(n);
        writeln(m1[j]);
        if (m1[j] < sum) then
        begin
         ind:=j;
          sum:=m1[j];
          end;
      end;
  except
    on E:Exception do
      Writeln(E.Classname, ': ', E.Message);
  end;
  writeln(ind);
  writeln(sum);
  readln;
end.
