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

procedure TForm1.Button1Click(Sender: TObject);
begin
Canvas.Pen.Color:=clBlack;
Canvas.Pen.Width:=5;
canvas.MoveTo (StrToInt(edit1.text), StrToInt(Edit2.text));
canvas.LineTo (StrToInt(edit3.text), StrToInt(Edit4.text));
end;

end.
