unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Grids, ExtCtrls, ColorGrd;

type
  TForm1 = class(TForm)
    Button1: TButton;
    SG: TStringGrid;
    Edit5: TEdit;
    Image1: TImage;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Memo1: TMemo;
    procedure Button1Click(Sender: TObject);
    procedure SGClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  bi,ai,ci,a,ais1,ais2,b,c:real;
  en,q,i:integer;
  k:integer;
  p,x:array[1..4] of real;
  x1,w:real;

implementation
function s1(c:real):real;
begin

end;
{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var j:integer;
begin
for i:=1 to 10 do
memo1.Lines.Add('');
for j:=1 to strtoint(edit3.text) do
x[j]:=strtofloat(sg.Cells[j,1]);
x1:=strtofloat(edit1.Text);
for j:=1 to strtoint(edit3.text) do p[j]:=sin(x[j]);
for j:=1 to strtoint(edit3.text) do
  begin
  for i:=1 to strtoint(edit3.text)-j do
    begin
    p[i]:=(P[i]*(x1-x[i+j])-P[i+1]*(x1-X[i]))/(X[i]-X[i+j]);
    memo1.Lines.Strings[i]:=memo1.Lines.strings[i]+' '+(floattostr(round(p[i]*100)/100));    end;
    memo1.Lines.Add('');
    end;
  edit2.Text:=floattostr(p[1]);
  image1.Canvas.CleanupInstance();
  for i:=1 to strtoint(edit3.text) do
  image1.Canvas.Ellipse(round(x[i]*50)+5+3,297-round(sin(x[i])*50)+5,round(x[i]*50)-5+3,297-round(sin(x[i])*50)-5);
  image1.Canvas.Ellipse(round(x1*50)+5+3,297-round(sin(x1)*50)+5,round(x1*50)-5+3,297-round(sin(x1)*50)-5);
  image1.Canvas.TextOut(3,3,'y');
  image1.Canvas.TextOut(340,280,'x');
  image1.Canvas.MoveTo(3,297);
  x1:=0;
  image1.Canvas.Pen.Color:=rgb(0,0,0);
  image1.Canvas.MoveTo(3,3);
  image1.Canvas.LineTo(3,297);
  image1.Canvas.LineTo(340,297);
  image1.Canvas.MoveTo(3,297);
  image1.Canvas.Pen.Color:=rgb(255,0,0);
  if edit3.Text='2' then
  image1.Canvas.moveto(3,258);
  if edit3.Text='4' then
  image1.Canvas.moveto(3,400);
  while x1<=8 do
    begin
    x1:=x1+0.01;
    for i:=1 to strtoint(edit3.text) do P[i]:=sin(x[i]);
    for k:=1 to strtoint(edit3.text) do
      begin
	    for i:=1 to strtoint(edit3.text)-k do
	    P[i]:=(P[i]*(x1-X[i+k])-P[i+1]*(x1-X[i]))/(X[i]-X[i+k]);
      end;
    image1.Canvas.lineto(round(x1*50+2),round(297-P[1]*50));
    end;
  end;

procedure TForm1.SGClick(Sender: TObject);
begin
SG.Cells[SG.Col,SG.Row]:=edit5.text;
image1.Canvas.Ellipse(1,2,3,4);
end;

procedure TForm1.FormCreate(Sender: TObject);
var j:integer;
begin
for j:=1 to 4 do
sg.Cells[j,1]:=inttostr(j);
end;

end.
