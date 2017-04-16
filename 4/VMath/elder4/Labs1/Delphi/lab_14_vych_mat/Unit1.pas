unit Unit1;

interface   

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Grids, ExtCtrls, ColorGrd;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Memo1: TMemo;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Edit4: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    Label3: TLabel;
    Label4: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  bi,ai,ci,a,ais1,ais2,b,c:real;
  en,q,i:integer;
  k:integer;
  p,x:array[1..4] of real;
  x1,w:real;

implementation
function s1(c:real):real;
begin
if form1.radiobutton1.Checked then s1:=sqrt(c)
else if form1.radiobutton2.Checked then s1:=1/c;
end;
{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var j,k:integer;
r:string;
res,res_1,tmp_0:real;
h,q:real;
begin

   a:=strtoint(edit1.text);
   b:=strtoint(edit2.text);
  res:=0; tmp_0:=s1(a);
 //  h:=strtofloat(edit3.text);
 h:=(b-a)/4;
   edit3.text:=floattostr(h);
   q:=a+h;
   while q<b+h do
   begin
       res:=res+(tmp_0+(s1(q)))/2.0;
       tmp_0:=s1(q);
          q:=q+h;
   end;
   q:=0;
   memo1.Lines.Add('осноная формула трапеции '+floattostr(res*h));
   res_1:=res;
  res:=0;k:=0;
  while abs(res-res_1)>3*strtofloat(edit4.Text) do begin
      res:=res_1;
      res_1:=0.0;
      tmp_0:=s1(a);
   q:=a+h/2;
   while q<b+h/2 do
   begin
       res_1:=res_1+(tmp_0+(s1(q)))/2.0;
       tmp_0:=s1(q);
       q:=q+h/2;
   end;
      res_1:=res_1*h/2;
      k:=k+1; h:=h/2;  
   end;
   memo1.Lines.Add('результат двойного пересчитывания '+floattostr(res_1)+ ' шага '+floattostr(k)+' метод с корекцией'+ floattostr(res_1+(1.0/3.0)*(res_1-res)));


end;

procedure TForm1.FormCreate(Sender: TObject);
var j:integer;
begin

end;

end.
