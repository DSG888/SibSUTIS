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
  en,i,k1:integer;
  x:array[1..5] of double;
  x1,k,fp,w,i1:double;
  ch,zn,n,q:double;
  p:array[1..5,1..5] of double;
  zm,cl:array[1..4] of double;

implementation
function s1(c:real):real;
begin

end;
{$R *.dfm}
function factorial(a:integer):integer;
begin
en:=a;
for i:=1 to en do
a:=a*i;
factorial:=a;
end;
procedure TForm1.Button1Click(Sender: TObject);
var j:integer;
rs,bq:real;
begin
  for j:=1 to 5 do
    x[j]:=strtofloat(sg.Cells[j,1]);
  image1.Canvas.moveTo(3,297);
  for j:=1 to 5 do p[j][1]:=sqrt(x[j]);
  k:=0;
  k1:=1;
    for j:=2 to 5 do
      begin
        for i:=1 to 4-k1 do
          begin
            p[i,j]:=p[1+i][j-1]-p[i][j-1];
          end;
          k1:=k1+1;
      end;
  n:=1.5;
  q:=(n-x[1])*5;bq:=1;
  n:=p[1][1];
         for j:=1 to 4 do
            begin
              rs:=1;
              for i:=1 to j do rs:=rs*i;
              bq:=bq*(q-j+1);
              n:=n+(p[1][j+1]/rs)*bq;
            end;
         edit5.Text:=floattostr(sqrt(1.5));
         edit1.Text:=floattostr(n);
image1.Canvas.LineTo(+3+round((i1)*50), 297-round(fp*50));
while k<=3 do
  begin
    k:=k+0.0001;
    q:=(k-x[1])*5;bq:=1;
    n:=p[1][1];
    for j:=1 to 4 do
      begin
        rs:=1;
        rs:=factorial(j);
        bq:=bq*(q-j+1);
        n:=n+(p[1][j+1]/rs)*bq;
      end;
image1.Canvas.MoveTo(4+round(k*50),296-round(n*50));
image1.Canvas.Pen.Color:=rgb(255,0,0);;
image1.Canvas.LineTo(3+round(k*50),297-round(n*50));
image1.Canvas.Pen.Color:=rgb(0,0,0);;
image1.Canvas.MoveTo(4+round(k*50),296-round(sqrt(k)*50));
image1.Canvas.LineTo(3+round(k*50),297-round(sqrt(k)*50));

                 end;      image1.Canvas.Pen.Color:=rgb(0,0,0);
for i:=1 to 5 do
image1.Canvas.ellipse(round(x[i]*50),300-round(sqrt(x[i])*50),6+round(x[i]*50),294-round(sqrt(x[i])*50));
image1.Canvas.MoveTo(3,3);
image1.Canvas.LineTo(3,297);
image1.Canvas.LineTo(297,297);
image1.Canvas.TextOut(3,3,'y');
image1.Canvas.TextOut(280,280,'x');
end;

procedure TForm1.SGClick(Sender: TObject);
begin
SG.Cells[SG.Col,SG.Row]:=edit5.text;
end;

procedure TForm1.FormCreate(Sender: TObject);
var j:integer;
begin
for j:=1 to 5 do
sg.Cells[j,1]:=floattostr((j-1)*0.2+1);
end;

end.
