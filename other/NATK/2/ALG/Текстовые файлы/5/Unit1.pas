unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    ListBox1: TListBox;
    Button1: TButton;
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
  z:TextFile;
  x:string;
begin
  x:=Edit1.Text;
  AssignFile(z,x);
  reset(z,x);
  while not EoF(z) do
begin
  readln(z,x);
  ListBox1.Items.Add(x);
end;
  closefile(z);
end;
end.
