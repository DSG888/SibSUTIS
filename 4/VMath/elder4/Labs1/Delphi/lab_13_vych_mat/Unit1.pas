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

  p,x,y:array[1..4] of real;
  x1,fp,w,i1:real;
  ch,mr,zn,k:real;
  m,cl:array[1..5] of real;
  mx:array[1..5,1..5] of real;

implementation
function pow(a:real; i:integer):real;
var        j:integer;
rez:double;
begin

        rez:=1;
        for j:=1 to i do rez:=rez*a;
        pow:=rez;
end;
function i_rtn(c:real):integer;
var
i:integer;
hi:integer;
begin
if (c>1)   and (c<2)   then i_rtn:=1;
if (c>4)   and (c<5)   then i_rtn:=4;
if (c>2.3) and (c<2.5) then i_rtn:=3;
for k:=1 to 5 do
if (c>=x[round(k)])and( c<=x[round(k)+1]) then
if(abs(c-x[round(k)])>abs(x[round(k)+1]-c))then i_rtn:=round(k+1)
else i_rtn:=round(k);
end;

function s1(c:real):real;
var
i:integer;
i1,hi:real;
begin

        i1:=i_rtn(c);
        hi:=x[i+1]-x[i];
        s1:=(m[i]*pow((x[1+i]-c), 3))/(6.0*hi)+(m[1+i]*pow((c-x[i]), 3))/(6.0*hi)+((y[i]-(m[i]*pow(hi, 2))/6.0)*(x[i+1]-c)/hi)+((y[i+1]-(m[i+1]*pow(hi, 2))/6.0)*(c-x[i])/hi);
end;
{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var k1,j:integer;
begin
for j:=1 to 5 do
x[j]:=strtofloat(sg.Cells[j,1]);
for i:=1 to 5 do
y[i]:=strtofloat(sg.Cells[i,2]);
image1.Canvas.moveTo(3,297);
for i:=1 to 3 do                       //fill_mx
for j:=1 to 3 do begin
  if((i-1)=j) then mx[i-1][j]:=0
  else if(j=i)then mx[i-1][j]:=(x[i+2]-x[i])/6
  else if(j=(i-2))then mx[i-1][j+1]:=(x[1+i]-x[i-1])/6
  else if(abs((i-1)-j)>=2)then mx[i-1][j]:=0;
end;
for i:=1 to 3 do
mx[i][3+1]:=(y[i+2]-y[i+1])/(x[1+i+1]-x[i-1])-(y[i+1]-y[i])/(x[1+i]-x[i]);
for i:=2 to 4 do     //slau_gu
for j:=i to 4 do begin if mx[i][i]<>0 then  mr:=-(mx[j][i]/mx[i][i]);
if(mr<>0) then
for k1:=1 to 4 do mx[j][k1]:=mx[j][k1]+mr*mx[i][k1];
end;
for i:=3 downto 1 do begin
m[i+1]:=mx[i][3];
for j:=3 downto i+1 do begin m[i+1]:=m[i+1]-mx[i][j]*m[j+1];end;
if mx[i][i]<>0  then
m[i+1]:=m[i+1]/mx[i][i];
end;
m[1]:=0.0;
m[5]:=0.0;
for j:=1 to 4 do p[j]:=sqrt(x[j]);
while i1<=4 do begin
i1:=i1+0.001;
image1.Canvas.LineTo(3+round(k*50), 297-round(s1(k)*50));
end;
image1.Canvas.LineTo(+3+round((i1)*50), 297-round(fp*50));
image1.Canvas.moveTo(3,297);
image1.Canvas.Pen.Color:=rgb(0,0,0);;
while k<=4 do begin k:=k+0.0001;
image1.Canvas.LineTo(3+round(k*50), 297-round(sqrt(k)*50)); end;
edit2.Text:=floattostr(p[1]);
for i:=1 to 5 do
image1.Canvas.Ellipse(round(x[i]*50), 294-round(p[i]*50),6+round(x[i]*50),300-round(p[i]*50));

end;

procedure TForm1.SGClick(Sender: TObject);
begin
SG.Cells[SG.Col,SG.Row]:=edit5.text;
end;

procedure TForm1.FormCreate(Sender: TObject);
var i:integer;
begin
image1.Canvas.MoveTo(3,3);
image1.Canvas.LineTo(3,297);
image1.Canvas.LineTo(297,297);
image1.Canvas.MoveTo(3,297);
image1.Canvas.TextOut(3,3,'y');
image1.Canvas.TextOut(280,280,'x');
image1.Canvas.MoveTo(3,297);
for i:=1 to 5 do
sg.Cells[i,1]:=inttostr(i);
sg.Cells[1,2]:=inttostr(2);
sg.Cells[2,2]:=inttostr(3);
sg.Cells[3,2]:=inttostr(2);
sg.Cells[4,2]:=inttostr(1);
sg.Cells[5,2]:=inttostr(2);
sg.Cells[0,1]:='x';
sg.Cells[0,2]:='y';
end;

end.
