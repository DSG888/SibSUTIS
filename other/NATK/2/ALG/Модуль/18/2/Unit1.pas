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
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
function s(q:String):Boolean; external 'Project1.dll';
implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var
q:string;
begin
q:=edit1.text;
 if s(q) then
  edit2.text:=('Присутствует')
 else edit2.text:=('Отсутсвует');
end;
end.
