unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Button1: TButton;
    Label1: TLabel;
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
var
 g:TextFile;
 x:integer;
begin
  x:=StrToint(Edit1.text);
  AssignFile(g, 'P:\numbers.txt');
  append(g);
  begin
    writeln(g,x);
  end;
  closefile(g);
end;

end.
