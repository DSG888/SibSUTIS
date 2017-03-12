unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Edit2: TEdit;
    Button1: TButton;
    Edit3: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;

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
function f1 (c:real;h:real):real;
begin
  result:=PI*(c*c)*h;
end;
procedure TForm1.Button1Click(Sender: TObject);
begin
Edit3.text:=(FloatTostr(f1(StrToInt(Edit1.text),StrToInt(Edit2.text))));
end;
end.
