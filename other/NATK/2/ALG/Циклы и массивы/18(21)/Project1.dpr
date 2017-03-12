program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

type
TMas=array of integer;

Var
MAS1:TMas;
Z1,N1,K1,C:integer;


Function GenMas(Mas:TMas; SizeMas,nachalnoe_chislo,konechnoe_chislo:integer): TMas;
var val:Integer;
Begin
 For Val:=0 to SizeMas-1 do
  mas[val]:=Random(konechnoe_chislo-nachalnoe_chislo+1)+nachalnoe_chislo;
result:=mas;
End;

Function SMas(Mas:TMas): TMas;
Var val,min,Vmin,buf:Integer;
Begin
for val:=0 to Length(mas)-2 do           
 begin
    min:=val;
    for Vmin:=val+1 to Length(mas)-1 do
      if MAS[Vmin]<MAS[min] then min:=Vmin;
  buf:=MAS[val];
  MAS[val]:=MAS[min];
  MAS[min]:=buf;
 end;
result:=mas;
End;

Procedure Vyvod(mas:TMas);
var val:integer;
begin
 for val:=0 to Length(mas)-1 do
 Writeln('[',val,']=',mas[val]);
end;

function Poisk(X: Integer; MAS: TMas): Integer;
 function Poisk2(Lg,Rg: Integer): Integer;
 var
  M: Integer;
 begin
  if Rg<=Lg then begin Result:=Lg; Exit; end;
  M:=(Lg+Rg) div 2;
  if MAS[M]=X then begin Result := M; Exit; end;
  if MAS[M]>X then
   Result:=Poisk2(Lg,M-1)
    else
   Result:=Poisk2(M+1,Rg);
 end;
begin
 Result:=Poisk2(Low(MAS),High(MAS));
end;

Begin
ReadLn(z1);
ReadLn(n1);
ReadLn(k1);
ReadLn(C);

if (Z1<=0)or(n1>=k1) then begin Writeln('Error'); Readln; Exit; end;

SetLength(mas1,Z1);
Randomize;
GenMas(mas1,Z1,N1,K1);
SMas(mas1);
Vyvod(mas1);
Writeln(Poisk(C,mas1));

Readln;
end.


