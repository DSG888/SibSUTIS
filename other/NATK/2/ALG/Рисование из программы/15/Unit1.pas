unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls;

type
  TForm1 = class(TForm)
    Timer1: TTimer;
    Button1: TButton;
    procedure Timer1Timer(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
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
begin
Refresh;
x:=0;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
x:=0;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
var
rec:TRect;
begin
Canvas.Pen.Color:=form1.color;
canvas.Pen.width:=1000;
Canvas.Ellipse(x-50,x-50,x+50,x+50);
x:=x+1;
Canvas.Pen.Color:=clgreen;
Canvas.Ellipse(x-50,x-50,x+50,x+50);
end;

end.
