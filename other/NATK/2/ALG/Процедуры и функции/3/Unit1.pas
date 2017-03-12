unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Edit2: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Edit3: TEdit;
    Button1: TButton;
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

function procent (c:real;h:real):real;
begin
  result:=(c/100)*h;
end;
procedure TForm1.Button1Click(Sender: TObject);
begin
Edit3.text:=(FloatTostr(procent(StrToInt(Edit1.text),StrToInt(Edit2.text))));
end;
end.
