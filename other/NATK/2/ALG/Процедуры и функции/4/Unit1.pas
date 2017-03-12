unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Edit4: TEdit;
    Button1: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
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

function procent (c:real;h:real;z:real):real;
begin
  result:=(((((h*z)/365))*(c/100))+c);
end;
procedure TForm1.Button1Click(Sender: TObject);
begin
Edit4.text:=(FloatTostr(procent(StrToInt(Edit1.text),StrToInt(Edit2.text),StrToInt(Edit3.text))));
end;
end.
