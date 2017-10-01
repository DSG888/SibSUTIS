program LJUDA;
uses crt,Graph;

  const
   n=6;
type
mas=array[1..5] of real;
matr=array[1..100] of real;
TM=array[0..100] of real;
TY=array[1..2] of real;
 TM2=array[1..N] of real;
 TM3=array[0..N+1] of real;
     const
   X1:TM3=(0.12,0.32,0.42,0.52,0.62,0.72,0.82,0.92);
      X2:TM2=(0,0.2,0.4,0.6,0.8,1.0);

var
 xa,ya: integer;
stt: string;
mx:mas;
Result,y:TM;
Y2:TM2;
y1:tm3;
f:array[1..100]of real;
xn:array[1..100]of real;
  grDriver: Integer;
  grMode: Integer;
  ErrCode: Integer;
Yb,x,h,xx,yy1,yy2,y3,y4,kk,kl,a1,b1,c1:real;
a,b,c,d:matr;
i,j,l,p,j1,i1,k:integer;
m:array[1..n-1,1..n-1]of real;
{Вычисление с[i]   методом гаусса }
          Procedure metg;
 var
  a,c: array[1..4,1..4] of real;
  b,y: mas;
  i,j,k: integer;
  d:real;
 begin
  a[1,1]:=4;  a[1,2]:=1;  a[1,3]:=1; a[1,4]:=0;
  a[2,1]:=1;  a[2,2]:=4;  a[2,3]:=1; a[2,4]:=1;
  a[3,1]:=1;  a[3,2]:=1;  a[3,3]:=4; a[3,4]:=1;
  a[4,1]:=0;  a[4,2]:=1;  a[4,3]:=1; a[4,4]:=4;

  b[1]:=3*(y2[1]-2*y2[2]+y2[3]);
  b[2]:=3*(y2[2]-2*y2[3]+y2[4]);
  b[3]:=3*(y2[3]-2*y2[4]+y2[5]);
  b[4]:=3*(y2[4]-2*y2[5]+y2[6]);
  for k:=1 to 3 do
    begin
      y[k]:=b[k]/a[k,k];
      for j:=k+1 to 4 do  c[k,j]:=a[k,j]/a[k,k];
      for i:=k+1 to 4 do
        begin  b[i]:=b[i]-a[i,k]*y[k];
               for j:=k+1 to 4 do
               a[i,j]:=a[i,j]-a[i,k]*c[k,j];
        end;
      end;

  mx[4]:=b[4]/a[4,4];
  mx[3]:=(b[3]-a[3,4]*mx[5])/a[3,3];
  mx[2]:=(b[2]-(a[2,4]*mx[5]+a[2,3]*mx[4]))/a[2,2];
  mx[1]:=(b[1]-(a[1,4]*mx[5]+a[1,3]*mx[4]+a[1,2]*mx[3]))/a[1,1];
 end;

{--------Метод Эйлера реш-я диф. ур-я ----------------------}
procedure eiler(H,yy:real;var yy1:real;var Result:TM);
var Y:TY;
    i,Np:integer;
function Fnz(X,Y,dY:real):real;
  begin    Fnz:=5*sin(3*x)-2*dY-Y;
  end;
  begin
  Y[1]:=0;   Y[2]:=yy;
  Result[0]:=Y[1];
  i:=1;
  Np:=1;
  repeat
    Y[1]:=Y[1]+H*Y[2];
    Y[2]:=Y[2]+H*Fnz(i*0.01,Y[1],Y[2]);
    if (Int(100*H*I)=Np) then
    begin
      Result[Np]:=Y[1];
      inc(Np);
    end;
    inc(i);
  until Np=101;
  yy1:=result[100];
end;

function num1(Index:integer):real;
var k:integer;
begin
  k:=round(X1[index]*100);
  num1:=Result[k];
end;

function num2(Index:integer):real;
var k:integer;
begin
  k:=round(X2[index]*100);
  num2:=Result[k];
end;


{***************Интерполяция сплайном**************}
 Function s(xx:real):real;
  begin
     for i:=1 to n-1 do
    if (xx>=x2[i]) and (xx<x2[i+1]) then
        s:=a[i]+b[i+1]*(xx-x2[i])+c[i]*sqr(xx-x2[i])+
           d[i]*sqr(xx-x2[i])*(xx-x2[i]);
  end;

     {*****************Основная программа*****************}
 begin
      clrscr; h:=0.01;
      a1:=-1;   b1:=1;
      repeat
        eiler(h,a1,yy1,result);  a1:=a1-1;
        eiler(h,b1,yy2,result);  b1:=b1+1;
      until (yy1*yy2)<0;
      repeat
        c1:=(a1+b1)/2;
        eiler(h,c1,y3,result);
        if y3>0 then b1:=c1;
        if y3<0 then a1:=c1;
      until y3<0.01;

      for i:=1 to n do begin
      Y2[i]:=num2(i);  end;
      for i:=1 to n do begin
      a[i]:=Y2[i];  ;end;
      metg;
      c[1]:=0;c[2]:=mx[1];c[3]:=mx[2];c[4]:=mx[3];c[5]:=mx[4];c[6]:=0;
            h:=0.2;
            for i:=2 to n-1 do
      begin
      b[i]:=(Y2[i]-Y2[i-1])/h-h*(c[i+1]+2*c[i])/3;end;
      for i:=1 to n-1 do begin
      d[i]:=(c[i+1]-c[i])/h*3;
      end;
     b[6]:=(Y2[n]-Y2[n-1])/h;d[6]:=0;
            h:=0.01;
    writeln('*******************************************************') ;
    writeln;
           for i:=0 to n+1 do
    begin
    Y1[i]:=sqr(num1(i));
    Writeln('           X : ',X1[i]:2:2,'    Мощность ',Y1[i]:2:5);
  end;
  WRITELN;
  WRITELN;
  writeln('Нажмите Enter...' );
       kl:=0;
     for l:=0 to 99 do begin
     xx:=kl;
     y[l]:=s(xx);
     kl:=kl+h; end;

  Writeln;
  readln;
    writeln('************************************************************ ');
    writeln('    N      x(i)          м.Эйлера          Сплайн          ');

    writeln('************************************************************ ');
  x:=0;  h:=0.05;  i:=0;  k:=1;
   repeat
 writeln('   ',k:2,'     ',x:3:2,'          ',result[i]:10:7,'        ',
        y[i]:10:7);
     i:=i+5;  x:=x+h;  k:=k+1;
   until i=100;
  readln;
 { ------------  Постpоение гpафиков.  --------------- }
  grDriver:= Detect;
  InitGraph(grDriver,grMode,'l:\bgi');
  ErrCode:= GraphResult;
  if ErrCode = grOk then
    begin
      Line(GetMaxX div 2-200,GetMaxY div 2+100,GetMaxX-20,GetMaxY div 2+100);
      Line(GetMaxX div 2-200, 50,GetMaxX div 2-200,GetMaxY div 2+210);
      line(120,50,124,55); line(118,50,114,55);
      line(614,334,620,338); line(614,344,620,340);
      OutTextXY(100,40,'Y');
      OutTextXY(GetMaxX-30,GetMaxY-130,'X');
      for i:=0 to 4 do
        begin
          Circle(GetMaxX div 2-200+I*102,GetMaxY div 2+100,2);
          Str(i/5:2:1,Stt);
          OutTextXY(GetMaxX div 2-210+I*102,GetMaxY div 2+110,Stt);
        end;
      for i:=-7 to 18 do
        begin
          Circle(GetMaxX div 2-200,GetMaxY div 2+100-i*15,2);
          Str(i/10:3:2,Stt);
          OutTextXY(GetMaxX div 2-245,GetMaxY div 2+95-i*15,Stt);
        end;
 { --------------- Сплайн ----------------- }
      j1:=100;   i:=0;
      xa:=Round(i*5+GetMaxX div 2-200);
      ya:=Round((-0.5)*y[i]*230+GetMaxY div 2 +100);
      MoveTo(xa,ya);
      setcolor(61);
      for i:=0 to j1 do
        begin  xa:=Round(i*5+GetMaxX div 2-200);
                       ya:=Round((-0.5)*y[i]*230+GetMaxY div 2+100);
               LineTo(xa,ya);
        end;
      OuttextXY(Getmaxx-90,Getmaxy-200,' SPLAIN');
 { ---------------  Эйлер  ------------------ }
      j1:=100;   i:=0;
       xa:=Round(i*5+GetMaxX div 2-200);
       ya:=Round((-0.5)*result[i]*230+GetMaxY div 2+100);
       MoveTo(xa,ya);
       SetColor(58);
       for i:=0 to j1 do
         begin  xa:=Round(i*5+GetMaxX div 2-200);
                ya:=Round((-0.5)*result[i]*230+GetMaxY div 2+100);
                LineTo(xa,ya);
         end;
       OuttextXY(Getmaxx-90,Getmaxy-180,'ELER ');
       SETCOLOR(62) ;
    outtextxy(getmaxx-400,getmaxy-50,'Exit-Enter');
       readLn;
       CloseGraph;
    end
                        else writeln('Graphic error:',GraphErrorMsg(ErrCode));
END.
