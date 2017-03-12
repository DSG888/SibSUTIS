unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Edit3: TEdit;
    Button1: TButton;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

function factor (h:real;z:integer):real;
var
n:integer  ;
begin
for z := 1 to n do
    begin
      h:=(h*z);
    end;
  result:=h;
end;
procedure TForm1.Button1Click(Sender: TObject);
begin
Edit3.text:=(FloatTostr(factor(StrToInt(Edit1.text))));
end;
end.
