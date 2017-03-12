unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    ListBox1: TListBox;
    Edit1: TEdit;
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
  f:TextFile;
  a:string;
begin
  AssignFile(f,'P:\numbers.txt');
  reset(f);   
  while not EoF(f) do
begin
  readln(f,a);
  ListBox1.Items.Add(a);
end;
  closefile(f);
end;

end.
