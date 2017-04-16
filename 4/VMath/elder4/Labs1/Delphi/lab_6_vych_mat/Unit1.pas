unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Button1: TButton;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  bi,ais1,ais2,ai,ci,a,b,c:real;
  en,i:integer;
implementation
function s1(c:real):real;
begin
s1:=c*c-cos(c);
end;
{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
begin
a:=1;
b:=2;
while en<>1 do begin
c:=(a+b)/2;
ci:=s1(c);
ai:=s1(a);
bi:=s1(b);
if ai*(ci)<0 then b:=c
else a:=c;
ais1:=c;
if (abs(ais1-ais2)<0.001) and (abs(ais1-ais2)>0) then en:=1;
ais2:=c;
end;
edit1.Text:=floattostr(c);
end;

end.
