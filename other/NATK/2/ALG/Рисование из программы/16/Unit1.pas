unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls;

type
  TForm1 = class(TForm)
    Timer1: TTimer;
    procedure FormCreate(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  x,y:integer;
implementation

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
begin
x:=0;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin
Canvas.Pen.Color:=form1.color;
canvas.Pen.width:=10;
Canvas.Ellipse(300,300,600,600);
Canvas.Pen.Color:=clblack;
Canvas.Ellipse(300,300,600,600);
Canvas.pen.color:=form1.Color;
Canvas.Pen.width:=2;
Canvas.MoveTo(x+550,x-550);
Canvas.lineto(450,450);
Canvas.Pen.Color:=clred;
Canvas.MoveTo(x+550,x-550);
x:=x+100;
canvas.lineto(450,450);
end;
end.
