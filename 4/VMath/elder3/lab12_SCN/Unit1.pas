unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Math;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    procedure Button1Click(Sender: TObject);
    procedure Clear(Sender : TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  error : boolean;
implementation

{$R *.dfm}
 Function Sum(x,y : string):string;
  Var
   i,j,n,gn,md,overflow : integer;
   s : string;
  Begin
   overflow:=0;
   s:='';
   n:=max(length(x),length(y));
   i:=length(x); j:=length(y);
   while i<n do
    begin
     x:='0'+x;
     inc(i);
    end;
   while j<n do
    begin
     y:='0'+y;
     inc(j);
    end;
   for i:=length(x) downto 1 do
    begin
     gn:=StrToInt(x[i])+StrToInt(y[i])+overflow;
     overflow:=0;
     if gn>=10 then
      begin
       overflow:=1;
       md:=gn mod 10;
      end
     else md:=gn;
     s:=IntToStr(md)+s;
    end;
   if overflow<>0 then s:=IntToStr(overflow)+s;
   result:=s;
  End;

 Function Sub(x,y : string):string;
  Var
   i,j,n,gn,overflow : integer;
   s, ss : string;
  Begin
   overflow:=0;
   s:='';
   n:=max(length(x),length(y));
   i:=length(x); j:=length(y);
   while i<n do
    begin
     x:='0'+x;
     inc(i);
    end;
   while j<n do
    begin
     y:='0'+y;
     inc(j);
    end;
   for i:=length(x) downto 1 do
    begin
     if StrToInt(x[i])<StrToInt(y[i])+overflow then
      begin
      gn:=StrToInt('1'+x[i])-StrToInt(y[i])-overflow;
      overflow:=1;
      end
     else
      begin
       gn:=StrToInt(x[i])-StrToInt(y[i])-overflow;
       overflow:=0;
      end;
     s:=IntToStr(gn)+s;
    end;
   //проблема в конвертации в инт, решение - удалять 0 спереди нормально
   for i:=1 to length(s) do
    if s[i]='0' then
    else break;
   ss:='';
   for j:=i to length(s) do
    ss:=ss+s[j];
   result:=ss;
  End;

 Function Gain(x,y : string):string;
  Var
   i,j,n,k,m : integer;
   a,b,c,d,u,u1,u2,v,w,str : string;
   a1,b1 : string;
   a2,b2 : string;
  Begin
     n:=max(length(x),length(y));
     i:=length(x); j:=length(y);
     while i<n do
      begin
       x:='0'+x;
       inc(i);
      end;
     while j<n do
      begin
       y:='0'+y;
       inc(j);
      end;
     if n=1 then str:=IntToStr(StrToInt(x)*StrToInt(y))
     else
      begin
       k:=n div 2;
       if n mod 2 =1 then m:=k+1
       else m:=k;
       a:=''; b:=''; c:=''; d:='';
       for i:=1 to n do
        if i<=m then begin a:=a+x[i]; c:=c+y[i]; end
        else begin b:=b+x[i]; d:=d+y[i]; end;
       if length(a)>length(b) then begin b:='0'+b; d:='0'+d; end
       else if length(a)<length(b) then begin a:='0'+a; c:='0'+c; end;
       u1:=Sum(a,b);
       u2:=Sum(c,d);
       if length(u1)>length(a) then
        begin
         if length(u1)>length(u2) then u2:='0'+u2
         else if length(u1)<length(u2) then u1:='0'+u1;
         a1:=u1[1]; b1:=u2[1];
         a2:=''; b2:='';
         for i:=2 to length(u1) do
          begin a2:=a2+u1[i]; b2:=b2+u2[i]; end;
         u1:=gain(a1,b1);
         u2:=Sum(Gain(a1,b2),Gain(a2,b1));
         for j:=1 to 2*k do
          begin
          if (j<=k) then u2:=u2+'0';
          if u1<>'0' then u1:=u1+'0';
          end;
         u:=Sum(Sum(u1,u2),gain(a2,b2));
        end
       else u:=Gain(u1,u2);
       v:=gain(a,c);
       w:=gain(b,d);
       a:=v;
       b:=Sub(u,Sum(v,w));
       for j:=1 to 2*k do
        begin
         if (j<=k) then b:=b+'0';
         if v<>'0' then a:=a+'0';
        end;
       Str:=Sum(Sum(a,b),w)
      end;
   //Проблема в умножении на степень десятки, решение - прибавлять нужное число 0 в конец программно
   result:=str;
  End;

 Procedure TForm1.Clear(Sender : TObject);
  Begin
   Edit1.Text:='';
   Edit2.Text:='';
   Edit3.Text:='';
  End;
 Procedure errorr;
  Var
   i : integer;
   exp : boolean;
  begin
   exp:=false;
   for i:=1 to length(form1.Edit1.Text) do
    if (ord(form1.Edit1.Text[i])<48)or(ord(form1.Edit1.Text[i])>57) then
     begin exp:=true; break; end;
   for i:=1 to length(form1.Edit2.Text) do
    if (ord(form1.Edit2.Text[i])<48)or(ord(form1.Edit2.Text[i])>57) then
     begin exp:=true; break; end;
   if exp then
    begin
     error:=true;
     form1.Edit3.Text:='Один из множителей введен неверно!';
    end;
  end;
 Procedure TForm1.Button1Click(Sender: TObject);
  var
   i:longint;
  begin
   //ShowMessage(Sub('10','6'));
   error:=false;
   try
    i:=StrToInt(edit1.Text);
    i:=StrToInt(edit2.Text);
   except
    on EConvertError do errorr;
   end;
   if error then
   else if (edit2.Text<>'')and(edit1.Text<>'') then
         Edit3.Text:=Gain(edit1.Text,edit2.Text)
        else Edit3.Text:='Не введен один и множителей!';
  end; 

end.
