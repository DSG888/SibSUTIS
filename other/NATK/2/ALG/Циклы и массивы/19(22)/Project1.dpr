program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;
Var
MAS: array of integer;
i,j,n,k,min,y,b:integer;

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
y:=i-1;
for i := 1 to y-1 do
  begin                       
    min:=i;                   
    for j:=i+1 to y do        
      if MAS[j]<MAS[min] then
        min:=j;               
    b:=MAS[i];                
    MAS[i]:=MAS[min];         
    MAS[min]:=b;              
   end;                       
For i:=1 to i do
begin
 writeln('[',i,']=',mas[i]);
End;                        
Readln;
end.


