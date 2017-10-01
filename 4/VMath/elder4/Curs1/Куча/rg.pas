Uses Graph,Crt;
Const Eps=0.001;
      H:Real=0.01;
{************************************************}
Function K:Real;
Function F(X:Real):Real;
Begin
 F:=2*X-Sin(X)-3;
End;

Function Fs(X:Real):Real;
Begin
 Fs:=2+Cos(X);
End;

Var Xo,Xi,E1:Real;
Const Eps=0.01;
Begin
 Xo:=0;
 Xi:=Xo;
 Repeat
  Xo:=Xi;
  Xi:=Xo-F(Xo)/Fs(Xo);
  E1:=Abs(Xo-Xi);
 Until (E1<Eps);
 K:=Xi;
End;
{------- Диференц. уравнение отн-но Y' ----------------}
Function F(X,Y,Ko:Real):Real;
Begin
 F:=1+Ko*Y*Sin(X)-Y*Y;
End;
{--------------- Runge_Kutt 4 Го порядка --------------}
Function Runge_Kutt(h,a:real; yi:real ; Ko : Real): Real;
var
      k10,k20,k30,k40:real;
Begin
   k10:=F(a,yi,ko);
   k20:=F(a+h/2,yi+h/2*k10,Ko);
   k30:=F(a+h/2,yi+h/2*k20,Ko);
   k40:=F(a+h,yi+h*k30,Ko);
   yi:=yi+h/6*(k10+2*k20+2*k30+k40);
   Runge_Kutt:=yi;
End;

{-------------- Пересчет -------------------------}
Function Y(X:Real):Real;
Const Eps = 0.1;
Var I,N:LongInt;
    Yo,Yi1,Yz,Ko:Real;
Begin
 Yo:=0.2; Yi1:=1; Ko:=K;
 H:=0.05;

 If X=0 then Y:=0.2 else begin
 While Abs(Yo-Yi1)>Eps do begin
   N:=Round(X/H);
   Yo:=Yi1;
   Yi1:=0.2;
  For I:=0 to N-1 do
             Yi1:=Runge_Kutt(H,I*H,Yi1,Ko);
  H:=H/2;
 End;
 Y:=Yi1;
 End;
End;
{----------------- Ньютон ------------------------}
Function P(N:LongInt;X:Real):Real;
Const  H = 0.2;
       Xo = 0;

Function Del(X:Real;N:LongInt):Real;
Begin
  If N = 0 then Del:=Y(X)
    else If N = 1 then Del:=Y(X+H)-Y(X)
       else Del:=Del(X+H,N-1)-Del(X,N-1);
End;

Var Q,Pt,S:Real;
    I,J:LongInt;
Begin
 Q:=(X-Xo)/H;
 S:=1;
 Pt:=Y(Xo);
 For I:=1 to N do begin
   S:=S*(Q-I+1)/I;
   Pt:=Pt+S*Del(Xo,I);
 End;
 P:=Pt;
End;
{--------------Оснавная программа--------------}
var
  grDriver : Integer;
  grMode   : Integer;
  ErrCode  : Integer;
  I,N,Xa,Ya:Integer;
  Stt:String;
begin
  grDriver := Detect;
  InitGraph(grDriver,grMode,'BGI');
  ErrCode := GraphResult;
  if ErrCode = grOk then
    begin
      Line(GetMaxX div 2-210, GetMaxY div 2+100, GetMaxX-50, GetMaxY div 2+100);
      Line(GetMaxX div 2-200, 50, GetMaxX div 2-200, GetMaxY div 2+110);
      For I:=0 to 5 do begin
         Circle(GetMaxX div 2-200+I*80,GetMaxY div 2+100,2);
         Str(I/5:2:2,Stt);
         OutTextXY(GetMaxX div 2-220+I*80,GetMaxY div 2+120,Stt);
      End;
      For I:=0 to 8 do begin
         Circle(GetMaxX div 2-200,GetMaxY div 2+100-I*33,2);
         Str(I/6:3:3,Stt);
         OutTextXY(GetMaxX div 2-260,GetMaxY div 2+95-I*33,Stt);
      End;
     {------------------- Ньютон --------------------}
      N:=16;
      I:=0;
       Xa:=Round(I*25+GetMaxX div 2-200);
       Ya:=Round((-1)*P(5,I/N)*200+GetMaxY div 2+100);
       MoveTo(Xa,Ya);
     For I:=0 to N do begin
       Xa:=Round(I*25+GetMaxX div 2-200);
       Ya:=Round((-1)*P(5,I/N)*200+GetMaxY div 2+100);
       LineTo(Xa,Ya);
     End;
     OuttextXY(Getmaxx-50,Getmaxy-200,'Nuton');
     {------------------ Runge_Kutt ------------------}
      N:=100;
      I:=0;
       Xa:=Round(I*4+GetMaxX div 2-200);
       Ya:=Round((-1)*Y(I/N)*200+GetMaxY div 2+100);
       MoveTo(Xa,Ya);
     SetColor(12);
     For I:=0 to N do begin
       Xa:=Round(I*4+GetMaxX div 2-200);
       Ya:=Round((-1)*Y(I/N)*200+GetMaxY div 2+100);
       LineTo(Xa,Ya);
     End;
        OuttextXY(Getmaxx-300,Getmaxy-400,'Runge_Kutt');
      ReadLn;
      CloseGraph;
     {--------------------------------------------}
    end
  else
    WriteLn('Graphics error:',
            GraphErrorMsg(ErrCode));
    ClrScr;
     N:=20;
     I:=0;
       Writeln('  X       Nuton        Runge_Kutt   ');
     For I:=0 to N do
       Writeln(i/n:2:2,'      ',P(5,I/N):2:5,'      ',Y(i/n):2:5);
    Readln;
End.
