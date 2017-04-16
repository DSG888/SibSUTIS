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
  en,q,i:integer;  N:integer;
  e:real;
  k:real;    x1,x2:real;
  p,x:array[1..4] of real;
  w:real;

implementation
function s1(c:real):real;
begin
if form1.radiobutton1.Checked then s1:=c*c-4*c;
else if form1.radiobutton2.Checked then s1:=1/c;
end;
{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var j:integer;
r:string;
res,res_1,tmp_0:real;
h,q:real;
begin   a:=strtoint(edit1.text);
e:=          strtofloat(edit4.text);
k:=           strtofloat(edit3.text);
   b:=strtoint(edit2.text);
              N:=trunc(ln((b-a)/(E))/ln(2));
         x1:=(a+(b-a)*k);
 x2:=(b-(b-a)*k);
   for i:=1 to n do
   begin      memo1.Lines.Add('step'+inttostr(i) +' x1 '+floattostr(round(x1*100000)/100000)+' x2 '+floattostr(round(x2*100000)/100000)+' f1 '+floattostr(round(s1(x1)*100000)/100000)+' f2  '+floattostr(round(s1(x2)*100000)/100000));
                if   s1(x2)>s1(x1) then begin
                b:=x2      ;
                x2:=x1;
                x1:=a+(b-a)*k;
                end
                else if
                s1(x1)>s1(x2)
                then begin a:=x1;x1:=x2;

                x2:=b-(b-a)*k
                end;
                end;
                res:=(a+b)/2;
                       memo1.Lines.Add('rez-ko '+floattostr(round(res*100000)/100000)+' f2 '+floattostr(round(s1(x2)*10000)/10000));

end;

procedure TForm1.FormCreate(Sender: TObject);
var j:integer;
begin

end;

end.
