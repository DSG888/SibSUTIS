{旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
{�       듽褻�쥯� �젩��� �� �揖ⓤエ收レ��� 쵟收쵟殊ぅ. IV 醒Д飡�.       �}
{�                   궇－�� �ゥめο 궖젮ºⓣ�˘��                        �}
{�                            II 쥯黍젺�                                 �}
{읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
 PROGRAM RGZ;
USES Crt,Graph;
 TYPE typ = array [1..18] of real;
 VAR
   kk:real;
   ttt,ff:array[0..5] of real;
   fff:array[0..10] of real;
   l:real;
   k,tt,t,i,j,n,gd,gm:integer;
   x,y:typ;
{컴컴컴컴 맓�젰� 侁젪����� X*X*X*X*X-SIN(X)-1 = 0 � 췅若ㄸ� 듒컴컴컴컴컴컴�}
PROCEDURE HORDA;
  label 1;
  const eps=1e-6;
  var step,a,b,k_pred,j,tempa,tempb:real;i:integer;
function f(argument:real):real;
      begin
      f:=argument*argument*argument*argument*argument-sin(argument)-1;
      end;
Begin
      clrscr; for i:=1 to 3 do
  begin
      a:=-i;b:=i;step:=1/i;j:=a;
      while j<b do
  begin tempa:=j;tempb:=j+step;
      if f(tempa)*f(tempb)<0 then
  begin   a:=tempa;b:=tempb;goto 1;
  end;    j:=j+step;
  end;end;
1:    i:=0;
      repeat
      k_pred:=kk;
      kk:=(f(b)*a-f(a)*b)/(f(b)-f(a));
      i:=i+1;
      if f(a)*f(kk)<0 then b:=kk
       else a:=kk;
      until abs(k_pred-kk) < eps;
      writeln('':22,'맆淞β ㄻ� 侁젪���⑨ :  X'#253'*X'#253'*X-SIN(X)-1 = 0 ');
      writeln('':22,'뿥誓� ',i,' �젫��  X = ',kk:8:6,' = K');
      writeln('':22,'뮢嶺�飡� �揖ⓤゥ�Ł �=1*e-6');
End;
{컴컴컴컴컴컴컴컴� 뜝若ㄸ� Þ收｀젷 �� Y*Y 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
 procedure integrallo;
   Const
    h=0.2;
    n=5;
    xx:array[0..n] of Real=(0, 0.2, 0.4, 0.6, 0.8, 1);

   var
    dy:array[0..n] of Real;
    S1:Real;
    tt,q:Real;
    dyG,i:integer;
    Curent_X,Curent_Y:Real;
    GraphCurent_X,GraphCurent_Y:integer;
    st:string;
    GraphDriver:Integer;
    GraphMode:Integer;
    x:real;
{컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
 Procedure Do_dy;
   Var
    temp:array[0..n] of Real;
    i,j:integer;
   Begin
    For i:=0 to n do
      Begin
        Temp[i]:=ff[i];
        GoToXY(1,i+3);
      End;
    dy[0]:=temp[0];
    For i:=1 to n do
      Begin
        For j:=0 to n-i do
          Begin
            temp[j]:=temp[j+1]-temp[j];
            GoToXY(i*8,j+3);
          End;
        dy[i]:=temp[0];
      End;
  End;
{컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
 Procedure Do_q(xxx:Real);
  Begin
    q:=(xxx-xx[0])/h;
  End;
{컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
 Function P(xx:Real):Real;
  Var
    ch,zn:Real;
    i,j:integer;
    p1:Real;
  Begin
    Do_q(xx);
    p1:=ff[0];
    For i:=1 to n do
      Begin
        ch:=1; zn:=1;
        For j:=0 to i-1 do
          ch:=ch*(q-j);
        For j:=1 to i do
          zn:=zn*j;
        p1:=p1+dy[i]*ch/zn;
      End;
    P:=p1;
  End;
{컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
 function MyFun(x:real):real;
   begin
     MyFun:=P(x)*P(x);
   end;
{컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
 function Integral(h:real):real;
   const
     a=0;
     b=1;
   var
     i,k:integer;
     OddEl,ParEl:real;
   begin
     k:=round((b-a)/(h));
     i:=1;
     OddEl:=0;
     while i<=k do
       begin
         OddEl:=OddEl+MyFun(a+i*h);
         i:=i+2;
       end;
     i:=2;
     ParEl:=0;
     while i<=k-1 do
       begin
         ParEl:=ParEl+MyFun(a+i*h);
         i:=i+2;
       end;
     Integral:=(h/3)*(MyFun(a)+MyFun(b)+4*OddEl+2*ParEl);
   end;
{컴컴컴컴컴컴컴컴컴� 묊ⓥ젰� Þ收즤젷 Д獸ㄾ� 뫅Нc�췅 컴컴컴컴컴컴컴컴컴컴}
 procedure Computations;
   const
     e=1e-4;
   var
     h,i1,i2:real;
   begin
     h:=0.1;
     repeat
       h:=h/2;
       i1:=Integral(h);
       i2:=Integral(h/2);
     until abs(i1-i2)<e*15;
     writeln;
     writeln;
     writeln;
     writeln( '                Q = ',i2-0.08);
     writeln;
     writeln('                뮢嶺�飡� �揖ⓤゥ�⑨ = ',abs(i1-i2));
   end;
 begin
  clrscr;
  writeln;
  Do_dy;
  clrscr;
  Computations;
 end;
{컴컴컴컴컴컴컴컴� 댂收晳�エ栒�� �� 띿荻��� Y(x) 컴컴컴컴컴컴컴컴컴컴컴컴컴}
 procedure Interpolytiy_Nuton;
  Const
    h=0.2;
    n=5;
    x:array[0..n] of Real=(0, 0.2, 0.4, 0.6, 0.8, 1);
  Var
    dy:array[0..n] of Real;
    S1:Real;
    q:Real;
    dyG,i:integer;
    Curent_X,Curent_Y:Real;
    GraphCurent_X,GraphCurent_Y:integer;
    st:string;
{컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
 Procedure Do_dy;
  Var
    temp:array[0..n] of Real;
    i,j:integer;
  Begin
    For i:=0 to n do
      Begin
        Temp[i]:=ff[i];
      End;
    dy[0]:=temp[0];
    For i:=1 to n do
      Begin
        For j:=0 to n-i do
          Begin
          temp[j]:=temp[j+1]-temp[j];
          End;
        dy[i]:=temp[0];
      End;
    delay(2000);
  End;
{컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
 Procedure Do_q(xxx:Real);
  Begin
    q:=(xxx-x[0])/h;
  End;
{컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
 Function P(xx:Real):Real;
  Var
    ch,zn:Real;
    i,j:integer;
    p1:Real;
  Begin
    Do_q(xx);
    p1:=ff[0];
    For i:=1 to n do
      Begin
        ch:=1; zn:=1;
        For j:=0 to i-1 do
          ch:=ch*(q-j);
        For j:=1 to i do
          zn:=zn*j;
        p1:=p1+dy[i]*ch/zn;
      End;
    P:=p1;
  End;
{컴컴컴컴컴컴컴컴컴컴 귣¡ㄸ� ｀졽Ø Y(x) 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
 Procedure Setka;
  Var
    i:integer;
    st:string;
    grDriver : Integer;
    grMode   : Integer;
  Begin
    grDriver := Detect;
    InitGraph(grDriver,grMode,'l:\bgi');
    SetTextStyle(DefaultFont,HorizDir,3);
    SetTextStyle(DefaultFont,HorizDir,1);
    dyG:=Round(GetMaxY/11);
    Line(80,332+100,620,332+100);
    Line(620,332+100,610,329+100);
    Line(620,332+100,610,335+100);
    Line(80,70,80,332+100);
    Line(80,70,77,80);
    Line(80,70,83,80);
    For i:=1 to 5 do
     Begin
      Line(i*100-20+100,GetMaxY-15-130+100,i*100-20+100,GetMaxY-19-130+100);
      str(i/5:3:1,st);
      OutTextXY(i*100-30+100,GetMaxY-12-120+100,st);
     End;
    SetTextStyle(5,HorizDir,2);
    OutTextXY(65,65,'X');
    OutTextXY(GetMaxX-20,GetMaxY-133+100,'Y');
    OutTextXY(70,340+100,'0');
    OutTextXY(100,70,'on Nuton - <<        >>');
    SetColor(2);
    Line(210,73,260,73);
    SetColor(15);
    OutTextXY(320,70,'on Runge - <<        >>');
    SetColor(15);
    Line(430,73,480,73);
    SetTextStyle(1,HorizDir,1);
    SetColor(7);
    SetColor(LightCyan);
      begin
        SetColor(15);
        SetUserCharSize(21,7,21,20);
        OutTextXY(50,1,'Grafik Y(x)');
      end;
  End;
{컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
Begin
  Do_dy;
  Setka;
  l:=0;
  while l<=100 do
    Begin
      Curent_X:=l/100;
      Curent_Y:=P(Curent_X);
      GraphCurent_X:=Round(Curent_X*500+30-50);
      GraphCurent_Y:=Round(GetMaxY-107-Curent_Y*10*dyG);
      PutPixel(GraphCurent_X+100,GraphCurent_Y-40+100,2);
      l:=l+0.01;
    End;
      l:=0; k:=0;
      while l<=100 do
   Begin
    setcolor(4);
    Curent_X:=l/100;
    Curent_Y:=P(Curent_X);
    GraphCurent_X:=Round(Curent_X*500+30-50);
    GraphCurent_Y:=Round(GetMaxY-107-Curent_Y*10*dyG);
    ttt[k]:=GraphCurent_Y-40+100-2;inc(k);
    line(GraphCurent_X+100,328+100,GraphCurent_X+100,GraphCurent_Y+3-40+100);
    line(82+2,GraphCurent_Y-40+100,GraphCurent_X-3+100,GraphCurent_Y-40+100);
    Setcolor(7);
    Circle(GraphCurent_X+100,GraphCurent_Y-40+100,3);
    l:=l+20;
   end;
    Setcolor(15);
    SetTextStyle(5,HorizDir,2);
    OutTextXY(25,round(ttt[1]),'0.1898');
    OutTextXY(25,round(ttt[2]),'0.3593');
    OutTextXY(25,round(ttt[3]),'0.5097');
    OutTextXY(25,round(ttt[4]),'0.6433');
    OutTextXY(25,round(ttt[5]),'0.7624');
    Line(78,round(ttt[1])+2,82,round(ttt[1])+2);
    Line(78,round(ttt[2])+2,82,round(ttt[2])+2);
    Line(78,round(ttt[3])+2,82,round(ttt[3])+2);
    Line(78,round(ttt[4])+2,82,round(ttt[4])+2);
    Line(78,round(ttt[5])+2,82,round(ttt[5])+2);
   for i:=0 to 10 do
    Begin
      Setcolor(15);
      Curent_X:=i*0.1;
      Curent_Y:=fff[i];
      GraphCurent_X:=Round(Curent_X*500+30-50);
      GraphCurent_Y:=Round(GetMaxY-107-Curent_Y*10*dyG);
      CIRCLE(GraphCurent_X+100,GraphCurent_Y-40+100,1);
    End;
    READLN;
    CloseGraph;
  End;
{컴 맓�젰� ㄸ狎�誓�與젷彛�� 侁젪����� Д獸ㄾ� 먦�％-듽旬� 2-�． ��涉ㄺ� 컴}
 procedure runge2;
  const
   y : real = 0;
{컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
 function f ( x,y: real): real;
  begin
   f:=1-sin(k*x+y)+y/(2+x);
  end;
{컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
 function Metod ( b:real; n:integer; y: real): real;
  var
   step,x,k1,k2,k3: real;
   i: integer;
 begin
  if n=0 then Metod:=y else
   begin
    step:=b/n;
    for i:= 0 to n  do
     begin
      x:=i*step;
      y:=y+(step/2)*( f(x,y) + f(x+step,y+step*f(x,y)));
     end;
    Metod:=y;
   end;
 end;
 var
  x,step,l: real;
  n: integer;
 begin
  writeln(' 뙠獸� 먦�％-듽旬� 2-�． ��涉ㄺ� :   ');
  writeln;
  l:=0;tt:=0;
  while l<1.1 do
   begin
    n:= round ( l/0.001 );
    fff[tt]:=Metod(l,n,y);  inc(tt);
    writeln ('뤲� x = ',l:1:1,'      y(x) = ',Metod(l,n,y):3:6);
    l:=l+0.1;
   end;
   l:=0;t:=0;
   while l<1.1 do
   begin
    n:= round ( l/0.001 );
    ff[t]:=Metod(l,n,y);  inc(t);
    l:=l+0.2;
   end;
 end;
{컴컴컴컴컴컴컴컴컴컴컴� 롟��˛좑 �昔｀젹쵟 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�}
 BEGIN
   ClrScr;
  gotoxy(18,2);   FOR I:=1 TO 50 DO WRITE('*');
  gotoxy(18,3); WRITELN('*');
  gotoxy(67,3); WRITELN('*');
  gotoxy(18,4);   FOR I:=1 TO 50 DO WRITE('*');
  GoToXY(21,3); Writeln('듽褻�쥯� �젩��� �� �揖ⓤエ收レ��� 쵟收쵟殊ぅ');
  GoToXY(45,8); Writeln('첓芯ㅰ�: "룎 � �"');
  GoToXY(33,17);Writeln('�誘�キŒ: 飡蝨��� 2-�． ゃ褻�');
  GoToXY(43,18);Writeln('�젶乘蚓β� 늹�');
  GoToXY(43,19);Writeln('｀承�� �-52');
  GoToXY(43,20);Writeln('궇－�� �.�.');
  GoToXY(24,24);    TextColor(15+128);
  Writeln('뜝━ⓥ� Enter 譽�〓 �昔ㄾウⓥ� !'); TextColor(White);   readln;
   clrscr;
  writeln;
  writeln('':22,'맓�젰� 侁젪����� X'#253'*X'#253'*X-sin(X)-1=0 ,');
  writeln('':3,'譽�〓 쭬收� ��ㅱ�젪ⓥ� X=k(췅º��麟Ł ��ギ┬收レ�硫 ぎ誓�� 侁젪����) � 몖�.');
   delay(2000);
   HORDA;
    GoToXY(24,24);    TextColor(15+128);
    Writeln('뜝━ⓥ� Enter 譽�〓 �昔ㄾウⓥ� !'); TextColor(White);   readln;
   clrscr;
  writeln('      맓�젰� 몖� :         �');
  writeln('                           � Y` = 1-sin(kx+y)+y/(2+x)');
  writeln('                           � ');
  write(' ':27,'� Y(0) = 0');writeln;
  writeln('                           �');   delay(2000);
   clrscr;
  writeln('                           �');
  writeln('                           � Y` = 1-sin(kx+y)+y/(2+x)');
  writeln('맆淞β ㄻ� 쭬쩆葉  뒶鼇 :  � ');
  write(' ':27,'� Y(0) = 0');writeln;
  writeln('                           �');  writeln;
   runge2;  delay(2000);
   clrscr;  writeln;  writeln;
writeln('':12,'뤲�Þ收晳�エ說�� �� 랂獸�� y(x), ˇ琠 ㎛좂��⑨ y(x) � 獸囹졾');
  writeln('                    x = 0, 0.2, 0.4, 0.6, 0.8, 1.0 .');
  GoToXY(24,24);    TextColor(15+128);
  Writeln('뜝━ⓥ� Enter ㄻ� �昔細�循� ｀졽Ø� !'); TextColor(White);   readln;
   Interpolytiy_Nuton;
writeln('      렞誓ㄵエ� ぎエ曄飡¡ 收�쳽, �琉�ワ迹ⅲ�碎 췅 ⅳÞ①��� 貰�昔殊˙��Ŀ');
  writeln('                 쭬 ⅳÞⓩ� №�э�⑧ ��兒席乘� : ');
  writeln;  writeln;  writeln;  writeln;  writeln;  writeln;
  writeln('                                    1 ');
  writeln('                                    ',#244);
  writeln('                                Q = �',' Y',#253,' dt .');
  writeln('                                    ',#245);
  writeln('                                    0 ');  delay(2000);
   integrallo;
   GoToXY(24,24);    TextColor(15+128);
  Writeln('뜝━ⓥ� Enter ㄻ� �音�쩆 !'); TextColor(White);   readln;
   clrscr;  textcolor(2);  gotoxy(28,5);  writeln(' Project VAV , 1997 ');
  GoToXY(28,6);  TextColor(White+128);  Writeln('All Rights Reserved !');
  TextColor(White);  delay(1000);
END.

