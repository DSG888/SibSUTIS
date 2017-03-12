unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Button7: TButton;
    Button8: TButton;
    Button9: TButton;
    Button10: TButton;
    Button12: TButton;
    Button13: TButton;
    Button14: TButton;
    Button15: TButton;
    Edit1: TEdit;
    Button16: TButton;
    Button17: TButton;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Button9Click(Sender: TObject);
    procedure Button10Click(Sender: TObject);
    procedure Button12Click(Sender: TObject);
    procedure Button16Click(Sender: TObject);
    procedure Button15Click(Sender: TObject);
    procedure Button14Click(Sender: TObject);
    procedure Button13Click(Sender: TObject);
    procedure Button17Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

 Var
   a,b,c:real;
   i:integer;
   f: boolean;
{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
begin
  Edit1.Text:='0';
  i:=0;
  f:=false;
end;
procedure TForm1.Button1Click(Sender: TObject);
begin
  if i>0then edit1.clear;
if edit1.Text='0' then
     begin
       Edit1.Text:='1';
       f:=true;
       end
   else edit1.Text:=Edit1.Text+'1';
end;



procedure TForm1.Button2Click(Sender: TObject);
begin
if i>0then edit1.clear;
 if edit1.Text='0' then
     begin
       Edit1.Text:='2';
       f:=true;
     end
   else edit1.Text:=Edit1.Text+'2';
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
if i>0then edit1.clear;
 if edit1.Text='0' then
     begin
       Edit1.Text:='3';
       f:=true;
     end
   else edit1.Text:=Edit1.Text+'3';
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
if i>0then edit1.clear;
 if edit1.Text='0' then
     begin
       Edit1.Text:='4';
       f:=true;
     end
   else edit1.Text:=Edit1.Text+'4';
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
if i>0then edit1.clear;
 if edit1.Text='0' then
     begin
       Edit1.Text:='5';
       f:=true;
     end
   else edit1.Text:=Edit1.Text+'5';
end;

procedure TForm1.Button6Click(Sender: TObject);
begin
if i>0then edit1.clear;
 if edit1.Text='0' then
     begin
       Edit1.Text:='6';
       f:=true;
     end
   else edit1.Text:=Edit1.Text+'6';
end;

procedure TForm1.Button7Click(Sender: TObject);
begin
if i>0then edit1.clear;
 if edit1.Text='0' then
     begin
       Edit1.Text:='7';
       f:=true;
     end
   else edit1.Text:=Edit1.Text+'7';
end;

procedure TForm1.Button8Click(Sender: TObject);
begin
if i>0then edit1.clear;
 if edit1.Text='0' then
     begin
       Edit1.Text:='8';
       f:=true;
     end
   else edit1.Text:=Edit1.Text+'8';
end;

procedure TForm1.Button9Click(Sender: TObject);
begin
if i>0then edit1.clear;
 if edit1.Text='0' then
     begin
       Edit1.Text:='9';
       f:=true;
     end
   else edit1.Text:=Edit1.Text+'9';
end;

procedure TForm1.Button10Click(Sender: TObject);
begin
if i>0then edit1.clear;
 if edit1.Text='0' then
     begin
       Edit1.Text:='0';
       f:=true;
     end
   else edit1.Text:=Edit1.Text+'0';
end;

procedure TForm1.Button12Click(Sender: TObject);
begin
  a:=0;
  b:=0;
  i:=0;
  f:=false;
  Edit1.Text:='0';
end;

procedure TForm1.Button16Click(Sender: TObject);
begin
  if i=5 then a:=c
  else a:=StrToFloat(edit1.Text);
  i:=1;
  f:=false;
end;

procedure TForm1.Button15Click(Sender: TObject);
begin
  if i=5 then a:=c
  else a:=StrToFloat (edit1.Text);
  i:=2;
  f:=false;
end;

procedure TForm1.Button14Click(Sender: TObject);
begin
  If i=5 then a:=c
  else a:=StrToFloat (edit1.Text);
  i:=3;
  f:=false;
end;

procedure TForm1.Button13Click(Sender: TObject);
begin
  if i=5 then a:=c
  else a:=StrToFloat (edit1.Text);
  i:=4;
  f:=false;
end;


procedure TForm1.Button17Click(Sender: TObject);
begin
  b:=StrToFloat (edit1.Text);
  edit1.Clear;
 case i of
  1: begin
       c:=a+b;
       edit1.Text:=FloatToStr (c);

     end;
  2: begin
       c:=a-b;
       edit1.Text:=FloatToStr (c);
     end;
  3: begin
       c:=a*b;
       edit1.Text:=FloatToStr (c);
     end;
  4: If b=0 then edit1.Text:='ббедхре вхякн!!!!!!'
      else
       begin
       c:=a/b;
       edit1.Text:=FloatToStr (c)
end;
end;
end;
end.
