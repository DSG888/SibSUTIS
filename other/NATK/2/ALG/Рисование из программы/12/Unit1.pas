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
    procedure FormPaint(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  rer:array of TRect;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
begin
Canvas.Pen.Color:=clBlack;
Canvas.Pen.Width:=5;
canvas.MoveTo (StrToInt(edit1.text), StrToInt(Edit2.text));
canvas.LineTo (StrToInt(edit3.text), StrToInt(Edit4.text));
setlength(rer,length(rer)+1);
rer[length(rer)-1].Top:=StrToInt(edit1.text);
rer[length(rer)-1].left:=StrToInt(edit2.text);
rer[length(rer)-1].Bottom:=StrToInt(edit3.text);
rer[length(rer)-1].right:=StrToInt(edit4.text);

end;

procedure TForm1.FormPaint(Sender: TObject);
var
  i:Integer;
begin
for i:= 0 to length(rer)-1 do
begin
canvas.MoveTo (rer[i].top,rer[i].left);
canvas.LineTo (rer[i].Bottom,rer[i].right);
end;
end;

end.
