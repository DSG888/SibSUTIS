unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
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
  a,b,c:integer;
begin
  AssignFile(f,'P:\phone.txt');
  {$I-}
  append(f);
  {$I+}
  if Ioresult<>0 then
begin
     rewrite(f);
end;
begin
  writeln(f,Edit1.Text);
  writeln(f,Edit2.Text);
  writeln(f,Edit3.Text);
end;
closefile(f);
end;

end.
