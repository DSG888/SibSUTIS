unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Button1: TButton;
    Memo1: TMemo;
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
function s1(c:real;i:integer):real;
begin
if i=1 then s1:=c*c-3;
if i=2 then s1:=2*c;
if i=3 then s1:=2;
end;
{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
begin
a:=2;
b:=1;
c:=2;
while en<>1 do begin
c:=c-s1(c,1)/s1(c,2);
memo1.Lines.Add(floattostr(c));
ci:=s1(c,1);
ai:=s1(a,1);
bi:=s1(b,1);
if ai*(ci)<0 then b:=c
else a:=c;
ais1:=c;
if (abs(ais1-ais2)<0.001) and (abs(ais1-ais2)>0) then en:=1;
ais2:=c;
end;
edit1.Text:=floattostr(c);
end;

end.
