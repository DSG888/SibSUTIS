Program KURS;
Uses Graph, CRT;
Const EPS=1E-6;                     {Epsilon}
      STEP=1.25E-3;                             {Graphic}
      DX=STEP*5;                     {X-Step}
      DY=STEP*10;                    {Y-Step}
      iSTEP=0.2;                     {Interpolation step}
      iMin=0;                        {Interpolation limits}
      iMax=1;
      N=Round((iMax-iMin)/iStep);    {Number of interpolation intervals}
      dMin=0;                        {Differentiation limits}
      dMax=1;
      dStep=0.05;                    {Differentiation step}
      dN=Round((dMax-dMin)/dStep);   {Number of differentiation intervals}
      dH=0.05;

var Gd,Gm:integer;
    i,j:integer;
    IntX,IntY:array[0..N] of real;
    DelY:array[0..N,0..N] of real;
    dIntX,dIntY:array[0..dN+5] of real;       {  float dDelY[N+1][M+1]}
    dDelY:array[0..dN+5,0..dN+5] of real;
    X,X0:real;
    K,dK:real;
    L,R,C:real;
    cr:real;

{----------------------------------------------------------------------------}

function F(X:real):real;
begin
 f:=2*X*X*X-Sin(X)-3;
end;

{----------------------------------------------------------------------------}
function dF(X:real):real;
begin
 dF:=6*X*X-Cos(X);
end;

{Equation--------------------------------------------------------------------}
function ndF(X,Y,dY:real):real;
var L,R,C:Real;

function nF(X,Y,dY,d2Y:real):real;
begin
 nF:=d2Y-cos(d2Y)-(X*X+Y)-K*Y;
end;

begin
 L:=0;R:=10;
 Repeat
  C:=(L+R)/2;
  if nF(x,Y,dY,C)*nF(x,Y,dY,L)<0 then R:=C
   else if nF(x,Y,dY,C)*nF(x,Y,dY,R)<0 then L:=C
    else break;
 Until ABS(((R-L)/2))<EPS;
 ndF:=C;
end;

{Dif. equation---------------------------------------------------------------}
function difF(X,X0,Y0,dY0:real):real;
var wX:real;
    Y,oldY,Ys:array[0..1] of real;
    i:integer;
begin
 Y[0]:=Y0;
 Y[1]:=dY0;
 wX:=X0;

 while(ABS(X-wX)>=EPS) do
  begin
   oldY:=Y;
   Ys[0]:=oldY[0]+dH/2*oldY[1];
   Ys[1]:=oldY[1]+dH/2*(ndF(wX,oldY[0],oldY[1]));

   Y[0]:=oldY[0]+dH*Ys[1];
   Y[1]:=oldY[1]+dH*(ndF(wX+dH/2,Ys[0],Ys[1]));
   wX:=wX+dH;
  end;

 difF:=Y[0];
end;

function diFfF(X,X0,Y0,dY0:real):real;
var wX:real;
    Y,oldY,Ys:array[0..1] of real;
    i:integer;
begin
 Y[0]:=Y0;
 Y[1]:=dY0;
 wX:=X0;

 while(ABS(X-wX)>=EPS) do
  begin
   oldY:=Y;
   Ys[0]:=oldY[0]+dH/2*oldY[1];
   Ys[1]:=oldY[1]+dH/2*(ndF(wX,oldY[0],oldY[1]));

   Y[0]:=oldY[0]+dH*Ys[1];
   Y[1]:=oldY[1]+dH*(ndF(wX+dH/2,Ys[0],Ys[1]));
   wX:=wX+dH;
  end;

 difFF:=Y[1];
end;

{Dif. equation decision------------------------------------------------------}
function inF(X:real):real;
begin
 inF:=difFF(X,0,1,dK);
end;
{----------------------------------------------------------------------------}

function iY(X:real):real; {Neuton's method (I)}
var Q,C,V,W:real;
    i:integer;
begin
{Interpolate function}
 Q:=(X-IntX[0])/iStep;
 C:=1;W:=DelY[0,0];
 for i:=1 to N do
  begin
   C:=C*i;
   V:=DelY[0,i]/C;
   for j:=0 to i-1 do V:=V*(Q-j);
   W:=W+V;
  end;
 iY:=W;
end;

{Differentiation-------------------------------------------------------------}
function difFunc(num:integer):real;
var W:real;
    i:integer;
    sign:shortint;
begin
 W:=0;sign:=1;
 W:=dDelY[num,1]-1/2*dDelY[num,2]+1/3*dDelY[num,3]-1/4*dDelY[num,4];

 W:=W/dStep;
 difFunc:=W;
end;
{----------------------------------------------------------------------------}

Begin
ClrScr;
Write('-----------------------------Lebedev Vasily, P-21-------------------------------');
Writeln('                       ---------SibSUTI, 2003---------');Writeln;

{Equation 2*X-Sin(X)-3=0 (minimal positive decision)-------------------}
 Writeln('1. 2*X-Sin(X)-3=0');Writeln;
 X:=2;
 Repeat
  X0:=X;
  X:=X0-F(X0)/dF(X0);
 Until ABS(X-X0)<EPS;
 Writeln('X=',X:10:10);Writeln('K=',X:10:10);
 K:=X;


{Dif. equation---------------------------------------------------------------}
{Shoot method  (Eiler)}

 L:=-10;R:=10;
 Repeat
  C:=(L+R)/2;
  if (difFF(1,0,1,C)-0.5)*(difFF(1,0,1,L)-0.5)<0 then R:=C
   else if (difFF(1,0,1,C)-0.5)*(difFF(1,0,1,R)-0.5)<0 then L:=C
    else break;
 Until ABS((difFF(1,0,1,L)-difFF(1,0,1,R))/2)<EPS;
 dK:=C;

writeln(inF(1));

readln;

{----------------------------------------------------------------------------}
 x:=0;
 repeat
  Writeln('F(',x:3:2,')=',difF(X,0,1,dK):5:5,'   dF(',x:3:2,')=',difFF(x,0,1,dK):5:5);
  x:=x+0.2;
 until x>1;
 readln;


{Interplation---------------------------------------------------------------}
{Make interpolation grid}
 for i:=0 to N do
  begin
   IntX[i]:=iMin+i*iStep;
   IntY[i]:=inF(IntX[i]);
  end;

{Make D-Matrix}
 FillChar(DelY,SizeOf(DelY),0);
 for i:=0 to N do DelY[i,0]:=IntY[i];
 for i:=1 to N do
  for j:=0 to N do
   DelY[j,i]:=DelY[j+1,i-1]-DelY[j,i-1];

{Show graphic}
 Gd:=Detect;
 InitGraph(Gd,Gm,'c:\tp\bgi');
 Line(0,240,640,240);
 Line(320,0,320,480);
 SetColor(LightBlue);

 for i:=0 to N do Circle(320+Round(IntX[i]/DX),240-Round(IntY[i]/DY),3);

 {Original function graphic}
 SetColor(White);
 X:=iMin;
 MoveTo(Round(320+X/DX),240-Round(inF(X)/DY));
 Repeat
  LineTo(Round(320+X/DX),240-Round(inF(X)/DY));
  X:=X+0.05;
 Until X>iMax;
 Readln;

 {Interpolated function graphic}
 SetColor(LightRed);
 X:=iMin;
 MoveTo(Round(320+X/DX),240-Round(iY(X)/DY));
 Repeat
  LineTo(Round(320+X/DX),240-Round(iY(X)/DY));
  X:=X+STEP;
 Until X>iMax;

 Readln;
 CloseGraph;


{Differentiation-------------------------------------------------------------}
 ClrScr;
 Writeln('3. Differentiation');Writeln;

 {Make interpolation grid}
 for i:=0 to dN+5 do
  begin
   dIntX[i]:=dMin+i*dStep;
   dIntY[i]:=inF(dIntX[i]);
  end;

{Make D-Matrix}
 FillChar(dDelY,SizeOf(dDelY),0);
 for i:=0 to dN+2 do dDelY[i,0]:=dIntY[i];
 for i:=1 to dN+2 do
  for j:=0 to dN-i+2 do
   dDelY[j,i]:=dDelY[j+1,i-1]-dDelY[j,i-1];

 for i:=0 to dN do
  Writeln('Q(',i*dStep:2:2,')=',dintY[i]:10:10,
  '    I(',i*dStep:2:2,')=',difFunc(i):10:10);

 Readln;

End.