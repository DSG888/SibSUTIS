unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Button1: TButton;
    RadioButton1: TRadioButton;
    RadioButton3: TRadioButton;
    RadioButton4: TRadioButton;
    RadioButton5: TRadioButton;
    RadioButton2: TRadioButton;
    Memo1: TMemo;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  bi,ai,ci,a,ais1,ais2,b,c:real;
  en,q,i:integer;
implementation
function s1(c:real):real;
begin
if form1.radiobutton1.Checked then s1:=c*c-3
else if form1.radiobutton3.Checked then s1:=c
else if form1.radiobutton3.Checked then s1:=c*c
else if form1.radiobutton4.Checked then s1:=c*c+c
else if form1.radiobutton5.Checked then s1:=c*c+c-5
end;
{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
begin
a:=-100;
b:=100;
q:=1;
ais1:=1000;
en:=0;
ais2:=100;
while en<>1 do
//for i:=1 to 1000 do begin
begin
  if (s1(b)-s1(a))<>0 then
  begin
    c:=(a*s1(b)-b*s1(a))/(s1(b)-s1(a));
    ci:=s1(c);
    ai:=s1(a);
    bi:=s1(b);
    i:=i+1;
    if ai*(ci)<0 then b:=c else a:=c;
    memo1.Lines.Add('шаг '+inttostr(i)+'   '+floattostr(c));
    ais1:=c;
    if (abs(ais1-ais2)<0.00001) and (abs(ais1-ais2)>0) then en:=1;
    if ais1=ais2 then en:=1;
    ais2:=c;
  end
  else
  begin
    if q=1 then begin b:=b-1; q:=0;  end
    else begin a:=a+1; q:=1;        end;
    //a:=a+1;
    //b:=b-1;
    ;if a=b then begin c:=0; en:=1;end;
  end;

end;
//end;
edit1.Text:=floattostr(c);
end;

end.
