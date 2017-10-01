
USES crt,graph;
Const
    E=0.001;
    h=0.2;
    N=5;
TYPE
    mas=array[1..2] of real;
    mas1=array[0..N] of real;
    mas2=array[0..5,0..5] of real;
VAR
   K:real;
   delY,Yx:mas1;
   i:word;
   m:mas2;

Function FuncK(x:real):real;
begin
  FuncK:=2*x*sqr(sqr(x))-sin(x)-3;
end;

Function FindK:real;     {поиск K}
Var a,b,x1,xp:real;
begin
   a:=0;  b:=2;  x1:=0;
   repeat
     xp:=x1;
     x1:=(a+b)/2;
      if (FuncK(a)*FuncK(x1)<0) then b:=x1
                                else a:=x1;
    until (abs(xp-x1)<E);
     FindK:=x1;
end;

Procedure FuncF(x:real; y:mas; var F:mas);
 begin
   F[1]:=y[2];
   F[2]:=k*y[2]-sin(y[2])+(sqr(x)+y[1]);
 end;

Procedure CreatYx;    {расчет  Y(x)}
Var hh,Y5,dif,a,b:real;
   k1,k2,k3,k4:mas;
   Yi,Ytmp:mas;
   i,nk,m:word;
begin
   Yx[0]:=1;
   a:=-1; b:=0;
 repeat
  dif:=(a+b)/2;
  hh:=h;
  Yx[5]:=30000;
  repeat
    Yi[1]:=1;
    Yi[2]:=dif;
    Y5:=Yx[5];
    nk:=Trunc(1/hh);
     for i:=1 to nk do
      begin
       FuncF(i*hh,Yi,k1);
        Ytmp[1]:=Yi[1]+hh/2*k1[1];
        Ytmp[2]:=Yi[2]+hh/2*k1[2];
       FuncF(i*hh+hh/2,Ytmp,k2);
        Ytmp[1]:=Yi[1]+hh/2*k2[1];
        Ytmp[2]:=Yi[2]+hh/2*k2[2];
      FuncF(i*hh+hh/2,Ytmp,k3);
        Ytmp[1]:=Yi[1]+hh*k3[1];
        Ytmp[2]:=Yi[2]+hh*k3[2];
      FuncF(i*hh+hh,Ytmp,k4);
        Yi[1]:=Yi[1]+hh/6*(k1[1]+2*k2[1]+2*k3[1]+k4[1]);
        Yi[2]:=Yi[2]+hh/6*(k1[2]+2*k2[2]+2*k3[2]+k4[2]);
        m:=Trunc(i*hh/h);
         if ((m-i*hh/h)=0) then Yx[m]:=Yi[1];
      end;
    hh:=hh/2;
  until (abs(Y5-Yx[5])<E);
    if (Yx[5]<0.5) then a:=dif  else b:=dif;
 until (abs(Yx[5]-0.5)<E);
 writeln('Значение Y''(0) : ',dif:4:3);
end;

Procedure CreateDelY;     {Формирование конечных разностей}
Var i,j:word;
 Begin
    for i:=0 to N do
      m[i,0]:=Yx[i];
    for j:=1 to N do
     for i:=N-j downto 0 do
      m[i,j]:=m[i+1,j-1]-m[i,j-1];
    for i:=1 to N do
     DelY[i]:=m[0,i];
 end;

Function InterNuton(x:real):real;  { Интерполяция по Ньютону}
Var i,p:word;
    q,s,q1:real;
 Begin
   q:=(x-1)/h;
   q1:=q;
   p:=1;
   s:=Yx[5];
    for i:=1 to N do
     begin
       s:=s+m[N-i,i]*q1/p;
       q1:=q1*(q+i);
       p:=p*(i+1);
     end;
    InterNuton:=s;
  end;

Procedure VyvodX;
 begin
   OutTextXY(20,460,'0');
   OutTextXY(140,460,'0.2');
   OutTextXY(260,460,'0.4');
   OutTextXY(380,460,'0.6');
   OutTextXY(500,460,'0.8');
   OutTextXY(620,460,'1');
   OutTextXY(10,47,'1');
   OutTextXY(1,247,'0.5');
 end;

Procedure CreatGrafics;
Var gd,gm,ErrCode:integer;
              i,y:word;
              y1:real;
              str:string;
Begin
  gd:=Detect;
  InitGraph(gd,gm,'c:\work\bp\bgi');
  ErrCode:=GraphResult;
  if ErrCode<>grOk then
   begin
     writeln('graphics error: ',graphErrorMsg(ErrCode));
     Halt;
   end;
  Line(30,0,30,480);
  Line(0,450,640,450);
   for i:=1 to N do
      Line(i*120+30,445,i*120+30,455);
       Line(25,50,35,50);
         Line(25,250,35,250);
      VyvodX;
      for i:=0 to 600 do
       begin
         y1:=InterNuton(i/600);
         y:=450-Trunc(y1*400);
         PutPixel(i+30,y,4);
       end;
     SetColor(3);
      for i:=N to N do begin
       y:=447-Trunc(Yx[i]*400);
       OutTextXY(i*120+30,y,'*');
     end;
     readln;
     closegraph;
  end;

Function VychQ:real;     {Вычисление теплоты}
Var x,Sy,h1:real;
    f1,f2,f3:real;
  begin
    h1:=0.01; x:=0;  Sy:=0;
     repeat
      f1:=sqr(InterNuton(x));
      f2:=sqr(InterNuton(x+h1));
      f3:=sqr(InterNuton(x+2*h1));
      Sy:=Sy+2*h1*(f1/6+2/3*f2+f3/6);
      x:=x+2*h1;
    until  (x>=1);
     VychQ:=Sy;
   end;


BEGIN
  clrscr;
  K:=FindK;
  Writeln(' Коэффициент K из (2*x*x*x*x*x-sin(x)-3)   = ',k:5:3);
  CreatYx;
  CreateDelY;
  writeln;
  textColor(5);
  Writeln('Рунге-Кутт 4-го порядка       Интерполяция по Ньютону ');
  textColor(7);
   for i:=0 to N do
writeln('Yx(',I*h:2:1,')=',Yx[i]:6:5,'                   Yx(',i*h:2:1,')=',InterNuton(i*h):6:5);
    readln;
    CreatGrafics;
    writeln('Количество теплоты  Q:',VychQ:5:4);
    readln;
END.
