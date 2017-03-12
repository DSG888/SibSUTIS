unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Edit1: TEdit;
    Edit2: TEdit;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  x:integer;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var
i:integer;
begin
canvas.MoveTo (0,200);
for I:= 0 to 1000 do
begin
canvas.LineTo(i, round(StrToInt(Edit1.Text)*sin(x+StrToInt(Edit2.Text))));
X:=x+1;
end;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
X:=0;
end;

end.

