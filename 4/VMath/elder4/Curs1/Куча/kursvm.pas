 Uses  Graph,Crt;
 Const  eps=0.001;   h:real=0.01;

 { -------- Функция для нахождения k- наименьшего положительного ----- }
 { --------  корня  уравнения  2xxxxx - sin(x) - 3 = 0 .             ----- }
 {method newtona}
 Function K:real;
  var    xo,xi,e1,f0,f1: real;
  const  eps= 0.01;
  begin
    xo:=0;
    xi:=xo;
    repeat
       xo:=xi;
       f0:=2*xo*xo*xo*xo*xo-sin(xo)-3;   f1:=10*xo*xo*xo*xo+cos(xo);
       xi:=xo-f0/f1;
       e1:=abs(xo-xi);
    until (e1<eps);
    k:=xi;
  end;

 { -------  Диференциальное  уравнение  отн-но  Y'. --------------- }
 Function f(x,y,ko:real): real;
   begin   f:=1+ko*y*sin(x)-y*y;
   end;

 { -------------  Метод  Рунге - Кутта  2-го  порядка. ------------ }
 Function Runge_Kutt(h,a:real; yi:real; ko:real): real;
  var  fi0,fi1:real;
  begin
    fi0:=f(a,yi,ko);
    fi1:=f(a+h/2,yi+h*fi0,ko);
    yi:=yi+(fi0+fi1)*h/2;
    Runge_Kutt:=yi;
  end;

 { -------------  Пересчет.  ------------------------ }
 Function y(x:real): real;
  const eps = 0.01;
  var  i,n: longint;
       yo,yi1,yz,ko: real;
  begin
    yo:=0.2;  yi1:=1;
    ko:=k;    h:=0.05;
    if x=0 then y:=0.2
           else begin  while abs(yo-yi1)>eps do
                          begin  n:=Round(x/h);
                                 yo:=yi1;
                                 yi1:=0.2;
                                 for i:=0 to n-1 do
                                   yi1:=Runge_Kutt(h,i*h,yi1,ko);
                                 h:=h/2;
                          end;
                       y:=yi1;
                end;
  end;

 { ------------  Интерполяция  по  Ньютону.  ------------------- }
 Function P(n:longint; x:real): real;
  const  h= 0.2;  xo= 0;
    function Del(x:real;n:longint):real;
      begin
        if n=0 then del:=y(x)
               else if n=1 then del:=y(x+h)-y(x)
                           else del:=del(x+h,n-1)-del(x,n-1);
      end;
  var q,pt,s: real;
      i,j: longint;
  begin
    q:=(x-xo)/h;
    s:=1;
    pt:=y(xo);
    for i:=1 to n do  begin  s:=s*(q-i+1)/i;
                             pt:=pt+s*del(xo,i);
                      end;
    p:=pt;
  end;

 { ------------  Основная  программа.   --------------
     ----------  Вывод  pезультатов.    -------------- }
 Var  grDriver: integer;
      grMode: integer;
      ErrCode: integer;
      i,n,xa,ya: integer;
      stt: string;
      xx: real;
 Begin
  clrscr;     writeln;
  writeln(' k - наименьший положительный корень уравнения ');
  writeln('    2x - sin(x) - 3 = 0 .');
  writeln(' Значение k =',k:10:7);
  readln;
  clrscr;    n:=20;
  writeln(' -------------------------------------------------------- ');
  writeln(' I  i  I    x(i)    I  y(i) -Ньютон I  y(i) -Рунге-Кутт I ');
  writeln(' -------------------------------------------------------- ');
  for i:=0 to 20 do
     writeln(' I ',i:2,'  I   ',i/n:2:2,'     I   ',p(5,i/n):2:7,
             '   I      ',y(i/n):2:7,'    I ');
  readln;

 { ------------  Постpоение гpафиков.  --------------- }
  grDriver:= Detect;
  InitGraph(grDriver,grMode,'l:\bgi');
  ErrCode:= GraphResult;
  if ErrCode = grOk then
    begin
      Line(GetMaxX div 2-210,GetMaxY div 2+100,GetMaxX-50,GetMaxY div 2+100);
      Line(GetMaxX div 2-200, 50,GetMaxX div 2-200,GetMaxY div 2+110);
      line(120,50,124,55); line(118,50,114,55);
      line(584,334,590,338); line(584,344,590,340);
      OutTextXY(100,40,'Y');
      OutTextXY(GetMaxX-65,GetMaxY-130,'X');
      for i:=0 to 5 do
        begin
          Circle(GetMaxX div 2-200+I*80,GetMaxY div 2+100,2);
          Str(i/5:2:2,Stt);
          OutTextXY(GetMaxX div 2-220+I*80,GetMaxY div 2+120,Stt);
        end;
      for i:=0 to 8 do
        begin
          Circle(GetMaxX div 2-200,GetMaxY div 2+100-i*33,2);
          Str(i/6:3:3,Stt);
          OutTextXY(GetMaxX div 2-260,GetMaxY div 2+95-i*33,Stt);
        end;
 { ---------------  Ньютон.  ----------------- }
      n:=16;   i:=0;
      xa:=Round(i*25+GetMaxX div 2-200);
      ya:=Round((-1)*P(5,i/n)*200+GetMaxY div 2+100);
      MoveTo(xa,ya);
      for i:=0 to n do
        begin  xa:=Round(i*25+GetMaxX div 2-200);
               ya:=Round((-1)*P(5,i/n)*200+GetMaxY div 2+100);
               LineTo(xa,ya);
        end;
      OuttextXY(Getmaxx-200,Getmaxy-330,' Nuton');
 { ---------------  Рунге-Кутт.  ------------------ }
      n:=100;   i:=0;
       xa:=Round(i*4+GetMaxX div 2-200);
       ya:=Round((-1)*y(i/n)*200+GetMaxY div 2+100);
       MoveTo(xa,ya);
       SetColor(12);
       for i:=0 to n do
         begin  xa:=Round(i*4+GetMaxX div 2-200);
                ya:=Round((-1)*Y(i/n)*200+GetMaxY div 2+100);
                LineTo(xa,ya);
         end;
       OuttextXY(Getmaxx-300,Getmaxy-400,' Runge-Kutt');
       readLn;
       CloseGraph;
    end
                    else writeln('Graphic error:',GraphErrorMsg(ErrCode));

 { ---------- Вычисление силы тока для любого момента вpемени x ------- }
 { ----------            из интеpвала [0,1].   --------- }
    clrscr;
    n:=20;
    writeln(' -------------------------------------- ');
    writeln(' I   i   I     X      I    Сила тока  I ');
    writeln(' -------------------------------------- ');
    for i:=1 to 19 do
       begin
         xx:=i*0.05;
         writeln(' I   ',i:2,'  I   ',xx:2:2,'     I   ',
                 (1/(2*0.05))*(y(xx+0.05)-y(xx-0.05)):10:7,'  I ');
       end;
    readln;
 End.
