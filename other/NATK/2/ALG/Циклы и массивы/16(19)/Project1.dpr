program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

type
TMas=array of integer;
Var
MAS1,MAS2,MASS:TMas;
Z1,N1,K1,Z2,N2,K2:integer;
i,j,k,u:integer;
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
 Writeln(val,':',mas[val]);
end;
Begin
ReadLn(z1);
ReadLn(n1);
ReadLn(k1);
ReadLn(z2);
ReadLn(n2);
ReadLn(k2);
if (Z1<=0)or(n1>=k1) then begin Writeln('Error'); Readln; Exit; end;
if (Z2<=0)or(n2>=k2) then begin Writeln('Error'); Readln; Exit; end;
SetLength(mas1,Z1);
SetLength(mas2,Z2);
SetLength(masS,Length(mas1)+Length(mas2));
Randomize;
GenMas(mas1,Z1,N1,K1);
GenMas(mas2,Z2,N2,K2);
SMas(mas1);
SMas(mas2);
j:=0; i:=0; k:=0;
while (i<Length(MAS1)) and (j<Length(MAS2)) do
begin
 if Mas1[i]<mas2[j] then
 begin
  masS[k]:=mas1[i];
  i:=i+1;
 end
 else
 begin
  MasS[k]:=Mas2[j];
  j:=j+1;
 end;
k:=k+1;
end;
if i=Length(mas1) then
for u:=k to Length(mass)-1 do
 mass[u]:=mas2[j+(u-k)]
else
for u:=k to Length(mass)-1 do
 mass[u]:=mas1[i+(u-k)];
Vyvod(mas1);
writeln;
Vyvod(mas2);
writeln;
Vyvod(masS);
Readln;
end.
