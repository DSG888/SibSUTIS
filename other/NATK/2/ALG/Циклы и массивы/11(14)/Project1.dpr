program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

Var
MAS: array of integer;
I,N,K,MAX,IMAX:integer;

begin
   Begin
   ReadLn(i);
   ReadLn(n);
   ReadLn(k);
   if (i<=0)or(n>=k) then
       begin
       Writeln('Error');
       Readln;
       Exit;
       end;
       SetLength(mas,i);
       Randomize;
       For i:=1 to i do
             begin
             mas[i]:=Random(k-n+1)+n;
             writeln('[',i,']=',mas[i]);
             end;
             Writeln;
             max:=mas[1];
             for i:=2 to i-1 do
             if max<mas[i] then
                  begin
                  max:=mas[i];
                  imax:=i;
                  end;
                  Writeln('Max value - [',imax,']');
                  Readln;
                  end.

