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
    Edit2: TEdit;
    Edit1: TEdit;
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

  p,x:array[1..4] of real;
  x1,fp,w,i1:real;
  ch,zn,k:real;
  zm,cl:array[1..4] of real;

implementation
function s1(c:real):real;
begin

end;
{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var j:integer;
begin
for j:=1 to 4 do
x[j]:=strtofloat(sg.Cells[j,1]);
image1.Canvas.Pen.Color:=rgb(255,0,0);;
image1.Canvas.moveTo(3,297);
for j:=1 to 4 do p[j]:=sqrt(x[j]);
while i1<=strtoint(edit1.Text) do
  begin
  i1:=i1+0.001;
  fp:=0;
  zn:=1;
  ch:=1;
  for j:=1 to strtoint(edit1.Text) do
    begin
    for i:=1 to strtoint(edit1.Text) do
      begin
      if i<>j then
        begin
        zn:=zn*(x[j]-x[i]);
        ch:=ch*(i1-x[i]);
        end;
      end;
    cl[j]:=ch;
    zm[j]:=zn;
    zn:=1;
    ch:=1;
    fp:=fp+(cl[j]/zm[j])*p[j];
    end;
  edit2.Text:=floattostr(fp);
  image1.Canvas.LineTo(+3+round((i1)*50), 297-round(fp*50));
  end;
image1.Canvas.moveTo(3,297);
image1.Canvas.Pen.Color:=rgb(0,0,0);;
while k<=4 do
  begin
  k:=k+0.0001;
  image1.Canvas.LineTo(3+round(k*50),297-round(sqrt(k)*50));
  end;
edit2.Text:=floattostr(p[1]);
for i:=1 to strtoint(edit1.Text) do
image1.Canvas.Ellipse(round(x[i]*50), 294-round(p[i]*50),6+round(x[i]*50),300-round(p[i]*50));
image1.Canvas.CleanupInstance();
image1.Canvas.MoveTo(3,3);
image1.Canvas.LineTo(3,297);
image1.Canvas.LineTo(297,297);
image1.Canvas.MoveTo(3,297);
image1.Canvas.TextOut(3,3,'y');
image1.Canvas.TextOut(280,280,'x');
image1.Canvas.MoveTo(3,297);
end;

procedure TForm1.SGClick(Sender: TObject);
begin
SG.Cells[SG.Col,SG.Row]:=edit5.text;
end;

procedure TForm1.FormCreate(Sender: TObject);
var j:integer;
begin
for j:=1 to 4 do
sg.Cells[j,1]:=inttostr(j);
end;
end.
