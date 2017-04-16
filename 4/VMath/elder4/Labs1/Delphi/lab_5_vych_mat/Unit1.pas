unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Grids, DBGrids;

type
  TForm1 = class(TForm)
    Button1: TButton;
    StringGrid1: TStringGrid;
    Edit1: TEdit;
    Label2: TLabel;
    OpenDialog1: TOpenDialog;
    Label5: TLabel;
    Button3: TButton;
    StringGrid3: TStringGrid;
    StringGrid4: TStringGrid;
    Memo1: TMemo;
    Memo2: TMemo;
    Edit2: TEdit;
    procedure Button1Click(Sender: TObject);
    procedure StringGrid1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button3Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  a:real;
  i,j,s,k,l,k1,s1,m,a1,n:integer;
  mas,mas2,mas1:array[1..100,1..10] of real;
  z:real;
implementation

{$R *.dfm}



procedure TForm1.Button1Click(Sender: TObject);
begin
for i:=1 to StringGrid1.ColCount-1 do
for j:=1 to StringGrid1.RowCount-1 do
mas[i,j]:=strtofloat(StringGrid1.Cells[i,j]);
for i:=1 to 3 do
mas[6,i]:=mas[i,i];
for j:=1 to 3 do
for i:=1 to 4 do
mas[i,j]:=mas[i,j]/mas[6,j];
for i:=1 to 3 do
mas[i,i]:=0;
for i:=1 to StringGrid1.ColCount-1 do
for j:=1 to StringGrid1.RowCount-1 do
StringGrid3.Cells[i,j]:=floattostr(mas[i,j]);
for j:=1 to StringGrid1.ColCount-1 do
StringGrid4.Cells[1,j]:=floattostr(mas[4,j]);
mas[5,1]:=0;
mas[5,2]:=0;
mas[5,3]:=0;
j:=0;
while (abs(mas[5,1]-mas[6,1])>strtofloat(edit2.Text)) or (abs(mas[5,2]-mas[6,2])>strtofloat(edit2.Text)) or (abs(mas[6,3]-mas[5,3])>strtofloat(edit2.Text)) do begin
j:=j+1;
k1:=3*(j-1);
for i:=1 to 3 do begin
mas[6,i]:=mas[5,i];
mas[5,i]:=mas[4,i];
k1:=k1+1;
for k:=1 to 3 do
mas[5,i]:=mas[5,i]-mas[k,i]*mas[5,k];
memo2.lines.Add('x'+inttostr(j)+inttostr(i)+'='+floattostr(mas[4,i])+'-(');
for k:=1 to 3 do begin
memo2.lines.strings[k1]:=memo2.lines.strings[k1]+floattostr(round(mas[k,i]*10000)/10000)+'*'+floattostr(round(mas[5,k]*10000)/10000);
if k<>3 then memo2.lines.strings[k1]:=memo2.lines.strings[k1]+'+';
end;
memo2.lines.strings[k1]:=memo2.lines.strings[k1]+')='+floattostr(round(mas[5,i]*10000)/10000);
end;
        end;


for i:=1 to StringGrid3.ColCount-1 do
for j:=1 to StringGrid1.RowCount-1 do
mas2[i,j]:=0;
end;

procedure TForm1.StringGrid1Click(Sender: TObject);
begin
  if StringGrid1.Cells[StringGrid1.Col,StringGrid1.Row]<>'1' then StringGrid1.Cells[StringGrid1.Col,StringGrid1.Row]:='1'
  else StringGrid1.Cells[StringGrid1.Col,StringGrid1.Row]:='0' ;
  StringGrid1.Cells[StringGrid1.Col,StringGrid1.Row]:=edit1.text;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
for i:=1 to StringGrid1.RowCount do
for j:=1 to StringGrid1.ColCount do
StringGrid1.Cells[i,j]:='0';
for i:=1 to StringGrid3.RowCount do
for j:=1 to StringGrid3.ColCount do
StringGrid3.Cells[i,j]:='0';
for i:=1 to StringGrid4.RowCount+1 do
for j:=1 to StringGrid4.ColCount+1 do
StringGrid3.Cells[0,0]:='C';
StringGrid4.Cells[0,0]:='B';
end;

procedure TForm1.Button3Click(Sender: TObject);
var k:integer;
begin
opendialog1.Execute;
memo1.Lines.LoadFromFile(opendialog1.FileName);
k:=1;
for j:=1 to StringGrid1.RowCount-1 do begin
for i:=1 to StringGrid1.ColCount-1 do begin
StringGrid1.Cells[i,j]:='';
while (memo1.Lines.text[k]<>#13) and (memo1.Lines.text[k]<>' ')do
begin
StringGrid1.Cells[i,j]:=StringGrid1.Cells[i,j]+memo1.Lines.text[k];
k:=k+1;
end;
if memo1.Lines.text[k]=#13 then k:=k+1;
k:=k+1;
end;end;
end;

end.
