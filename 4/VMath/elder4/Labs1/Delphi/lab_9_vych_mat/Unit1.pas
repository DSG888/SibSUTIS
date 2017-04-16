unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Grids, DBGrids;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Memo1: TMemo;
    Label1: TLabel;
    Edit1: TEdit;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  a:real;
  i,j,s,r,s1,m,a1,k,n:integer;
  mas:array[1..10,1..10] of real;
  wx:array[1..10,1..10] of real;
  fx:array[1..4] of real;
  x0:array[1..2,1..2] of real;
  z:real;
implementation

function x1fund(funcnumber:integer;x0:real;x1:real):real;
begin
if funcnumber=1 then x1fund:=x0*x0*x0+x1*x1-8;
if funcnumber=2 then x1fund:=2*x0+x1*x1*x1-6;;
end;

function x1fund2(funcnumber:integer;x0:real;x1:real):real;
begin
if funcnumber=1 then x1fund2:=3*x0*x0;
if funcnumber=2 then x1fund2:=2*x1;
if funcnumber=3 then x1fund2:=2;
if funcnumber=4 then x1fund2:=x1*x1*3;
end;
{$R *.dfm}



procedure TForm1.Button1Click(Sender: TObject);
begin
x0[1,2]:=2;
memo1.Lines.Clear;
x0[2,2]:=1;
s1:=0;
while (abs(x0[1,1]-x0[1,2])>strtofloat(Edit1.Text)) and (abs(x0[2,1]-x0[2,2])>strtofloat(Edit1.Text))do begin
x0[2,1]:=x0[2,2];
x0[1,1]:=x0[1,2];
fx[1]:=x1fund(1,x0[1,1],x0[2,1]);
fx[2]:=x1fund(2,x0[1,1],x0[2,1]);
s1:=s1+1;
wx[1,1]:=x1fund2(1,x0[1,1],x0[2,1]);
wx[2,1]:=x1fund2(2,x0[1,1],x0[2,1]);
wx[1,2]:=x1fund2(3,x0[1,1],x0[2,1]);
wx[2,2]:=x1fund2(4,x0[1,1],x0[2,1]);
n:=3;
for i:=1 to 2 do
for j:=1 to 2 do
mas[i,j]:=wx[i,j];
for j:=1 to 2 do
for i:=3 to 4 do begin
if i-2<>j then mas[i,j]:=0
else mas[i,j]:=1;
end;
for i:=1 to 2 do
for j:=i to 1 do
if mas[i,i]<>0 then begin        
a:=-mas[i,j+1]/mas[i,i];
for a1:=1 to 4 do
mas[a1,j+1]:=mas[a1,j+1]+mas[a1,i]*a;

end;
for i:=2 downto 1 do
for j:=i downto 1 do
if mas[i,i]<>0 then begin
a:=-mas[i,j-1]/mas[i,i];
for a1:=4 downto 1 do
mas[a1,j-1]:=mas[a1,j-1]+mas[a1,i]*a;
end;
x0[1,2]:=0;
x0[2,2]:=0;
for j:=1 to 2 do
for i:=3 to 4 do
mas[i,j]:=mas[i,j]/mas[j,j];
for i:=1 to 2 do
for k:=1 to 2 do
x0[i,2]:=x0[i,2]+mas[k+2,i]*fx[k];
x0[2,2]:=x0[2,1]-x0[2,2];
x0[1,2]:=x0[1,1]-x0[1,2];
memo1.Lines.Add('шаг'+' ' +inttostr(s1)+' значения x1   '+floattostr(x0[1,2])+'  значения x2    '+floattostr(x0[2,2]));
end;
end;

end.

