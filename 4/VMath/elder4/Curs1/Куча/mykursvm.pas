USES crt,graph;
Const  H=0.2;
       E=0.001;
       N=5;
TYPE
       mas1= array [1..2] of real;
       mas2= array [0..N] of real;
       mas3= array [0..5,0..5] of real;
VAR
       delY,YYY:mas2;
       m:mas3;
       K:real;
       i:word;
       f:text;
Function Find_K(x:real):real;
begin
  Find_K:=2*x*x*x*x*x-sin(x)-3;
end;

Function Found_K:real;
Var a,b,xlev,xprav:real;
begin
   a:=0;  b:=2;  xlev:=0;
   repeat
         xprav:=xlev;
         xlev:=(a+b)/2;
         if (Find_K(a)*Find_K(xlev)<0) then b:=xlev
         else a:=xlev;
   until (abs(xprav-xlev)<E);
   Found_K:=xlev;
end;

Procedure Func_for_F( x:real; y:mas1; var F:mas1);
 begin
   F[1]:=y[2];
   F[2]:=k*y[2]-sin(y[2])+(sqr(x)+y[1]);
 end;

Procedure FIND_YYY;
Var
   k1,k2,k3,k4:mas1;
   Yi,Yt:mas1;
   hh,Y5,dif,a,b:real;
   i,nk,m:word;
begin
   YYY[0]:=1;
   a:=-1; b:=0;
 repeat
       dif:=(a+b)/2;
       hh:=h;
       YYY[5]:=100;
       repeat
             Yi[1]:=1;
             Yi[2]:=dif;
             Y5:=YYY[5];
             nk:=Trunc(1/hh);
             for i:=1 to nk do
                              begin
                                   Func_for_F(i*hh,Yi,k1);
                                   Yt[1]:=Yi[1]+hh/2*k1[1];
                                   Yt[2]:=Yi[2]+hh/2*k1[2];
                                   Func_for_F(i*hh+hh/2,Yt,k2);
                                   Yt[1]:=Yi[1]+hh/2*k2[1];
                                   Yt[2]:=Yi[2]+hh/2*k2[2];
                                   Func_for_F(i*hh+hh/2,Yt,k3);
                                   Yt[1]:=Yi[1]+hh*k3[1];
                                   Yt[2]:=Yi[2]+hh*k3[2];
                                   Func_for_F(i*hh+hh,Yt,k4);
                        Yi[1]:=Yi[1]+hh/6*(k1[1]+2*k2[1]+2*k3[1]+k4[1]);
                        Yi[2]:=Yi[2]+hh/6*(k1[2]+2*k2[2]+2*k3[2]+k4[2]);
                        m:=Trunc(i*hh/h);
                        if ((m-i*hh/h)=0) then YYY[m]:=Yi[1];
                               end;
            hh:=hh/2;
        until (abs(Y5-YYY[5])<E);
    if (YYY[5]<0.5) then a:=dif
    else b:=dif;
 until (abs(YYY[5]-0.5)<E);
 writeln(f,'Значение Y''(0) : ',dif:4:3);
end;

Procedure FORM_DELTA_Y;
Var i,j:word;
 Begin
    for i:=0 to N do
      m[i,0]:=YYY[i];
    for j:=1 to N do
     for i:=N-j downto 0 do
      m[i,j]:=m[i+1,j-1]-m[i,j-1];
    for i:=1 to N do
     DELY[i]:=m[0,i];
 end;

Function NUTON(x:real):real;
Var i,p:integer;
    q,s,q1:real;
 Begin
   q:=(x-1)/h;
   q1:=q;
   p:=1;
   s:=YYY[5];
    for i:=1 to N do
     begin
       s:=s+m[N-i,i]*q1/p;
       q1:=q1*(q+i);
       p:=p*(i+1);
     end;
    NUTON:=s;
  end;

Procedure VivodX;
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

Procedure Grafica;
Var gd,gm,ErrCode:integer;
              i,y:word;
              y1:real;
              str:string;
Begin
  gd:=Detect;
  InitGraph(gd,gm,'c:\tp\bgi');
  ErrCode:=GraphResult;
  if ErrCode<>grOk then
   begin
     writeln('graphics error: ',graphErrorMsg(ErrCode));
   end;
  Line(30,0,30,480);
  Line(0,450,640,450);
   for i:=1 to N do
                   Line(i*120+30,445,i*120+30,455);
                   Line(25,50,35,50);
                   Line(25,250,35,250);
                   VivodX;
                   for i:=0 to 600 do
                                     begin
                                          y1:=Nuton(i/600);
                                          y:=450-Trunc(y1*400);
                                          PutPixel(i+30,y,1);
                                     end;
  readln;
  closegraph;
  end;

Function FORMULA_SIMSONA:real;
Var x,Q,h1:real;
    f_0,f_h,f_1:real;
  begin
    H1:=0.01; x:=0;  Q:=0;
     repeat
           f_0:=sqr(Nuton(x));
           f_h:=sqr(Nuton(x+h1));
           f_1:=sqr(Nuton(x+2*h1));
           Q:=Q+2*h1*(f_0/6+2/3*f_h+f_1/6);
           x:=x+2*h1;
    until  (x>=1);
    FORMULA_SIMSONA:=Q;
   end;


BEGIN
  clrscr;
  assign(f,'a.txt');
  reset(f);
  K:=Found_K;
  Writeln(f,' Коэффициент K из (2*x*x*x*x*x-sin(x)-3)   =   ',k:5:5);
  writeln(f);
  FIND_YYY;
  FORM_DELTA_Y;
  writeln(f);
  Writeln(f,'Рунге-Кутт 4-го порядка ' );
  for i:=0 to N do
  writeln(f,'Yx(',I*h:2:1,')=',YYY[i]:6:5);
  writeln(f);
  writeln(f,' Интерполяция по Ньютону ');
  for i:=0 to N do
  writeln(f,' Yx(',i*h:2:1,')=',Nuton(i*h):6:5);
  writeln(f);
  writeln(f,'Количество теплоты  Q:',FORMULA_SIMSONA:5:4);
  close(f);
  readln(f);
  Grafica;
END.
