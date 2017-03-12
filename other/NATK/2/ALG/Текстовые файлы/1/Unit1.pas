unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Edit1: TEdit;
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
  rewrite(g);
  begin
    writeln(g,x);
  end;
  closefile(g);
end;

end.
