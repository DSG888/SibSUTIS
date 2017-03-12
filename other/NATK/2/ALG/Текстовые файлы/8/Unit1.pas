unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    ListBox1: TListBox;
    Edit1: TEdit;
    Button1: TButton;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1; F:textfile;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var
a,b,c,s:string;
begin
Assignfile(F,'P:\phone.txt');
{I-}
reset(F);
{I+}
if IOResult <> 0 then
ShowMessage('Not files');
while not(Eof(F)) do
  begin
    readln(F,b);
   if edit1.text=b then
    begin
     readln(F,c);
     listbox1.items.Add(c);
    end;
  end;
closeFile(f);
end;
end.
