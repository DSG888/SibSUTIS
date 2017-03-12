program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

Var
MAS: array of integer;
I,J,N,K,min,y,b,G,h,c:integer;
Bool:Boolean;

Begin
ReadLn(i);
ReadLn(n);
ReadLn(k);
Readln(g);
if (i<=0)or(n>=k) then
begin                 
Writeln('Error');    
Readln;               
Exit;                 
end;                  
SetLength(mas,i);
Randomize;
Bool:=false;
h:=0;
For i:=0 to i-1 do
 begin                      
 mas[i]:=Random(k-n+1)+n;   
 writeln('[',i,']:',mas[i]);
 h:=h+1;
  if g=mas[i] then           
  begin                      
   C:=i;                     
   Bool:=true;
  end;                       
 end;                       
If bool then
begin
Writeln('Yes');
Writeln('Index-[',c,']');
Writeln('Total comparisons=',h);
end
else
Writeln('No');
Readln;
end.
