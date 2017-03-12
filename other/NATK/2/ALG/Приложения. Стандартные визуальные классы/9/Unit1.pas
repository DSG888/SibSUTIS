unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Menus, ActnList;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Edit1: TEdit;
    Label1: TLabel;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Edit2: TEdit;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    RadioButton3: TRadioButton;
    RadioButton4: TRadioButton;
    MainMenu1: TMainMenu;
    PopupMenu1: TPopupMenu;
    N1: TMenuItem;
    N2: TMenuItem;
    N3: TMenuItem;
    N4: TMenuItem;
    N5: TMenuItem;
    N6: TMenuItem;
    N7: TMenuItem;
    N8: TMenuItem;
    N9: TMenuItem;
    Label2: TLabel;
    Label3: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure RadioButton1Click(Sender: TObject);
    procedure RadioButton2Click(Sender: TObject);
    procedure RadioButton3Click(Sender: TObject);
    procedure RadioButton4Click(Sender: TObject);
    procedure N2Click(Sender: TObject);
    procedure N3Click(Sender: TObject);
    procedure N4Click(Sender: TObject);
    procedure N5Click(Sender: TObject);
    procedure N6Click(Sender: TObject);
    procedure N7Click(Sender: TObject);
    procedure N8Click(Sender: TObject);
    procedure N9Click(Sender: TObject);
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
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=StrToInt(a)+StrToInt(b);
Label1.Caption:=IntToStr(c);
end;

procedure TForm1.Button2Click(Sender: TObject);
var
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=StrToInt(a)-StrToInt(b);
Label1.Caption:=IntToStr(c);
end;

procedure TForm1.Button3Click(Sender: TObject);
var
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=(StrToint(a)) div (StrToInt(b));
Label1.Caption:=IntToStr(c);
end;

procedure TForm1.Button4Click(Sender: TObject);
var
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=StrToInt(a)*StrToInt(b);
Label1.Caption:=IntToStr(c);
end;
procedure TForm1.N2Click(Sender: TObject);
var
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=StrToInt(a)+StrToInt(b);
Label1.Caption:=IntToStr(c);
end;

procedure TForm1.N3Click(Sender: TObject);
var
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=StrToInt(a)-StrToInt(b);
Label1.Caption:=IntToStr(c);
end;

procedure TForm1.N4Click(Sender: TObject);
var
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=(StrToint(a)) div (StrToInt(b));
Label1.Caption:=IntToStr(c);
end;

procedure TForm1.N5Click(Sender: TObject);
var
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=StrToInt(a)*StrToInt(b);
Label1.Caption:=IntToStr(c);
end;

procedure TForm1.N6Click(Sender: TObject);
var
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=StrToInt(a)+StrToInt(b);
Label1.Caption:=IntToStr(c);
end;

procedure TForm1.N7Click(Sender: TObject);
var
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=StrToInt(a)-StrToInt(b);
Label1.Caption:=IntToStr(c);
end;

procedure TForm1.N8Click(Sender: TObject);
var
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=(StrToint(a)) div (StrToInt(b));
Label1.Caption:=IntToStr(c);
end;

procedure TForm1.N9Click(Sender: TObject);
var
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=StrToInt(a)*StrToInt(b);
Label1.Caption:=IntToStr(c);
end;

procedure TForm1.RadioButton1Click(Sender: TObject);
var
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=StrToInt(a)+StrToInt(b);
Label1.Caption:=IntToStr(c);
end;

procedure TForm1.RadioButton2Click(Sender: TObject);
var
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=StrToInt(a)-StrToInt(b);
Label1.Caption:=IntToStr(c);
end;

procedure TForm1.RadioButton3Click(Sender: TObject);
var
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=(StrToint(a)) div (StrToInt(b));
Label1.Caption:=IntToStr(c);
end;

procedure TForm1.RadioButton4Click(Sender: TObject);
var
c:integer; a,b:string;
begin
c:=0;
a:=edit1.text;
b:=edit2.text;
c:=StrToInt(a)*StrToInt(b);
Label1.Caption:=IntToStr(c);
end;

end.
