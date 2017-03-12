program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

Var
MAS: array of integer;
I,J,N,K,max,i2,b:integer;


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
WriteLn;
i2:=i-1;
for i := 1 to i2-1 do
  begin
    max:=i;
    for j:=i+1 to i2 do
      if MAS[j]>MAS[max] then
        max:=j;
    b:=MAS[i];
    MAS[i]:=MAS[max];
    MAS[max]:=b;
   end;
For i:=1 to i do
begin
 writeln('[',i,']=',mas[i]);
End;
Readln;
end.
