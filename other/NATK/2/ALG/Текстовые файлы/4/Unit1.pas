unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Button1: TButton;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

 var
  S:string; i,d:integer; F:TextFile;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
begin
i:=0; d:=0;
Assignfile(F,'numbers.txt');
reset(F);

 while not(Eof(F)) do
  begin
   readln(F,S);
   i:=i+1;
   D:=d+StrToInt(S);
  end;

edit1.Text:=inttostr(D div i);
closeFile(f);
end;

end.
