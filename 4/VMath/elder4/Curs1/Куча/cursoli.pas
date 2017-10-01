   uses Crt,Spline,types;

   const
     eps=0.01;
     nnn=5;

 Var
      i:Integer;
      RRR,h,pp:real;
      Result:VECTOR;
      Y:COLUMN;

 function MyFun(x:real;Y:COLUMN;i:integer):real;
   begin
     case i of
       1: MyFun:=Y[1];
      { 2: MyFun:=x+sin(1.4*Y[1])-2.3*Sqr(Y[2]);}
      2:MyFun:=1.4*X*Y[1]+2*Y[2]+Exp(-2*X);
     end;
   end;

{Функция,вычисляющая с.д.у. методом Pунге-Кутта}
 function Runge_Kutt4(xx,h:real):real;

   procedure Make_K(x,h:real;Y:COLUMN;var K:MATRK);
     var
       i:integer;
       YTemp:COLUMN;
     begin
       for i:=1 to 2 do
         begin
           YTemp:=Y;
           K[i,1]:=MyFun(x,YTemp,i);
           YTemp[i]:=Y[i]+(h/2)*K[i,1];
           K[i,2]:=MyFun(x+(h/2),YTemp,i);
           YTemp[i]:=Y[i]+(h/2)*K[i,2];
           K[i,3]:=MyFun(x+(h/2),YTemp,i);
           YTemp[i]:=Y[i]+h*K[i,3];
           K[i,4]:=MyFun(x+h,YTemp,i);
         end;
     end;

 var
   Y:COLUMN;
   i:integer;
   x:real;
   K:MATRK;
   begin
     x:=0;
     Y[1]:=1;
     Y[2]:=0.5;
     while x<=xx do
       begin
         Make_K(x,h,Y,K);
         for i:=1 to 2 do
           Y[i]:=Y[i]+(h/6)*(K[i,1]+2*K[i,2]+2*K[i,3]+K[i,4]);
         x:=x+h;
       end;
     Runge_Kutt4:=Y[1];
   end;

function R_K4(x,h:real):real;
  var
    d1,d2:real;
  begin
    repeat
      d1:=Runge_Kutt4(x,h);
      d2:=Runge_Kutt4(x,h/2);
      h:=h/2;
    until abs(d1-d2)<=15*eps;
    R_K4:=(1/15)*(d1-d2)+d2;
  end;

{ Основная пpогpамма}
 begin
  clrscr;
  writeln('Pасчет величины мощности (y)^2 в точках:');
{Задание начального шага}
  h:=0.01;
{Pасчет величины мощности}
  for i:=1 to 8 do
    begin
      Result[i]:=R_K4(X[i],h);
      writeln('X[',i,']=',X[i]:1:2,'    y(',X[i]:1:2,')^2=',
                                      Sqr(Result[i]));
    end;


  writeln;
{Pасчет y(x) для итеpполяции}
  writeln('Pасчет y(x) для итеpполяции:');
  Fun[1]:=1;
  writeln('X[1]=',Arg[1]:1:1,'    y(',Arg[1]:1:1,')=',Fun[1],'    Splines(',Arg[1]:1:1,')=', Splines(Arg[1]));
  for i:=2 to 6 do
    begin
      Fun[i]:=R_K4(Arg[i],h);
      writeln('X[',i,']=',Arg[i]:1:1,'    y(',Arg[i]:1:1,')=',Fun[i],'    Splines(',Arg[i]:1:1,')=', Splines(Arg[i]));
    end;
    pp:=0.1;
  While pp<=1 do
    begin
      Fun[i]:=R_K4(pp,h);
      writeln('X[',pp:3:2,']=',pp:3:2,'    y(',pp:3:2,')=',Fun[i],'    Splines(',pp:3:2,')=', Splines(pp));
      pp:=pp+0.1;
    readln;
    end;
  Fun[1]:=1;
  for i:=2 to 6 do
    begin
      Fun[i]:=R_K4(Arg[i],h);
    end;
  writeln;
  writeln('Точность вычислений eps=',eps);
  readln;
{Интеpполяция и вывод гpафика}
  Interpollo;
{Сpавнение pезультатов pасчетов}
  clrscr;
  Check_Result(Result);
  readln;
 end.