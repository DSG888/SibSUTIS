unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Grids, DBGrids;

type
  TForm1 = class(TForm)
    Button1: TButton;
    StringGrid1: TStringGrid;
    StringGrid2: TStringGrid;
    Button2: TButton;
    Edit1: TEdit;
    Edit2: TEdit;
    Label2: TLabel;
    OpenDialog1: TOpenDialog;
    Label5: TLabel;
    CheckBox1: TCheckBox;
    Label1: TLabel;
    Button3: TButton;
    Memo1: TMemo;
    Edit3: TEdit;
    Edit4: TEdit;
    Edit5: TEdit;
    StringGrid3: TStringGrid;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Button7: TButton;
    procedure Button1Click(Sender: TObject);
    procedure StringGrid1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure CheckBox1Click(Sender: TObject);
    procedure Label1Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure StringGrid3Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6KeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  a:real;
  i,j,s,k,s1,m,a1,n:integer;
  mas,mas2,mas1:array[1..10,1..10] of real;
  z:real;
implementation

{$R *.dfm}



procedure TForm1.Button1Click(Sender: TObject);
begin
m:=3;
for i:=1 to 3 do
for j:=1 to 3 do
StringGrid2.Cells[i,j]:='';
for i:=1 to StringGrid1.ColCount-1 do
for j:=1 to StringGrid1.RowCount-1 do
mas[i,j]:=strtofloat(StringGrid1.Cells[i,j]);
if CheckBox1.Checked=false then
for i:=1 to StringGrid1.ColCount-1 do begin
for j:=1 to StringGrid1.RowCount-1 do begin
for k:=1 to StringGrid1.RowCount-1 do begin
mas2[j,i]:=mas2[j,i]+mas[k,i]*mas[j,k];
StringGrid2.Cells[j,i]:=StringGrid2.Cells[j,i]+floattostr(mas[k,i])+'*'+floattostr(mas[j,k]);
if k<>StringGrid1.RowCount-1 then  StringGrid2.Cells[j,i]:=StringGrid2.Cells[j,i]+'+';
end;
end;end
else begin
for i:=1 to StringGrid3.ColCount-1 do
for j:=1 to StringGrid3.RowCount-1 do
mas1[i,j]:=strtofloat(StringGrid3.Cells[i,j]);
for i:=1 to StringGrid1.RowCount-1 do begin
for j:=1 to StringGrid3.ColCount-1 do begin
for k:=1 to StringGrid1.ColCount-1 do begin
mas2[j,i]:=mas2[j,i]+mas[k,i]*mas1[j,k];
StringGrid2.Cells[j,i]:=StringGrid2.Cells[j,i]+floattostr(mas[k,i])+'*'+floattostr(mas1[j,k]);
if k<>StringGrid1.ColCount-1 then  StringGrid2.Cells[j,i]:=StringGrid2.Cells[j,i]+'+';
end;
end;end;
end;

for i:=1 to StringGrid3.ColCount-1 do
for j:=1 to StringGrid1.RowCount-1 do
StringGrid2.Cells[i,j]:=StringGrid2.Cells[i,j]+'='+floattostr(mas2[i,j]);
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
StringGrid1.Cells[i,j]:='0'
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
StringGrid1.ColCount:=strtoint(edit2.text)+1;
StringGrid1.RowCount:=strtoint(edit3.text)+1;
StringGrid3.RowCount:=strtoint(edit2.text)+1;
edit5.Text:=edit2.text;
end;

procedure TForm1.CheckBox1Click(Sender: TObject);
begin
if CheckBox1.Checked=true then CheckBox1.Caption:='Перемножение двух разных матриц'
else CheckBox1.Caption:='матрица в квадрате';
label1.Caption:=CheckBox1.Caption;
end;

procedure TForm1.Label1Click(Sender: TObject);
begin
if label1.Caption='матрица в квадрате' then begin
label1.Caption:='Перемножение двух разных матриц';
CheckBox1.Checked:=true;
edit5.Visible:=true;
Button5.Visible:=true;
edit4.Visible:=true;
Button4.Visible:=true;
edit3.Visible:=true;
StringGrid3.Visible:=true;
end
else begin label1.Caption:='матрица в квадрате';
CheckBox1.Checked:=false;
edit5.Visible:=false;
edit4.Visible:=false;
Button5.Visible:=false;
Button4.Visible:=false;
edit3.Visible:=false;
StringGrid3.Visible:=false;
end;
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

procedure TForm1.Button4Click(Sender: TObject);
begin
StringGrid3.ColCount:=strtoint(edit4.text)+1;
StringGrid3.RowCount:=strtoint(edit5.text)+1;
StringGrid1.ColCount:=strtoint(edit5.text)+1;
edit2.Text:=edit5.text;
end;

procedure TForm1.StringGrid3Click(Sender: TObject);
begin
  if StringGrid3.Cells[StringGrid3.Col,StringGrid3.Row]<>'1' then StringGrid3.Cells[StringGrid3.Col,StringGrid3.Row]:='1'
  else StringGrid3.Cells[StringGrid3.Col,StringGrid3.Row]:='0' ;
  StringGrid3.Cells[StringGrid3.Col,StringGrid3.Row]:=edit1.text;
end;

procedure TForm1.Button5Click(Sender: TObject);
var k:integer;
begin
opendialog1.Execute;
memo1.Lines.LoadFromFile(opendialog1.FileName);
k:=1;
for j:=1 to StringGrid3.RowCount-1 do begin
for i:=1 to StringGrid3.ColCount-1 do begin
StringGrid3.Cells[i,j]:='';
while (memo1.Lines.text[k]<>#13) and (memo1.Lines.text[k]<>' ')do
begin
StringGrid3.Cells[i,j]:=StringGrid3.Cells[i,j]+memo1.Lines.text[k];
k:=k+1;
end;
if memo1.Lines.text[k]=#13 then k:=k+1;
k:=k+1;
end;end;
end;

procedure TForm1.Button6KeyPress(Sender: TObject; var Key: Char);
begin
 if  key='a' then begin button6.Left:=Button6.Left-10;
if button6.Left<button7.Left then button7.Left:=button7.Left-10 else button7.Left:=button7.Left+5;
end;
 if  key='d' then begin button6.Left:=Button6.Left+10;
if button6.Left<button7.Left then button7.Left:=button7.Left-10 else button7.Left:=button7.Left+5;
end;
 if  key='s' then begin button6.top:=Button6.top+10;
if button6.top<button7.top then button7.top:=button7.top-10 else button7.top:=button7.top+5;
end;
 if  key='w' then begin button6.top:=Button6.top-10;
if button6.top<button7.top then button7.top:=button7.top-10 else button7.top:=button7.top+5;
end;
if (button7.Left-button6.Left<20) and (button7.top-button6.top<20) then begin button7.Caption:='ты геймовер'; button6.Caption:='ты геймовер' end;
end;

end.

