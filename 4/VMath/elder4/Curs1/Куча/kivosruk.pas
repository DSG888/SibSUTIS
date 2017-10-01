{$N+}
program Kursovik;


 Uses GRAPH, CRT;
 Const H=0.2;
 Const DX=0.05;
 Const EPS=0.005;
 Const X_=0.0;
 Const Y_=1.0;
 Const Yt=0.5;
 Const n=6;
 Const XN : array[1..n] of real = (0,0.2,0.4,0.6,0.8,1.0);

 Type
     twofloor = array[1..2] of real;


 Var k, x, y, y__ : double;
     kf_r : array[1..2,1..4] of real;
     vector_y : twofloor;
     maxx_r, minx_r, maxy_r, miny_r, q  : real;
     y1, y0 , x0, x1, kx, ky, t, r, n1 : integer;
     YN : array[1..n] of real;
     koord : array[1..2,1..21] of double;
     Sel : char;

     f : text;
{*************************Grafika******************************************}

 function XG(xx:real):integer;
   begin
     XG:=trunc(x0+kx*(xx-minx_r));
   end;

  function YG(yy:real):integer;
   begin
     YG:=trunc(y1+ky*(yy-miny_r)){-t)/q)+y0};
   end;

 procedure initgr;
   var gd,gm : integer;
     begin
       gd:= Detect;
       InitGraph(gD,gM,'d:\bp\BGI');
     end;

 function ff(aa:integer):integer;
   var i, fak : integer;
     begin
       fak:=1;
       for i:=1 to aa do
            fak:=fak*i;
       ff:=fak;
     end;

 function Nuton(xx:real):real;
    var i, k, j : integer;
        C, P, qi, q_r : real;
        dy : array [1..n,1..n] of real;

    begin
      P:=YN[1];
      q_r:=(xx-XN[1])/H;
      qi:=q_r;

      for i:=1 to n do
        dy[i,1]:=YN[i];

      for i:=2 to n do
        for j:=1 to (n-1) do
          dy[j,i]:=dy[j+1,i-1]-dy[j,i-1];


      for i:=1 to (n-1) do
        begin
          P:=P+dy[1,i+1]*qi/ff(i);
          qi:=qi*(q_r-i);
        end;

      Nuton:=P;

    end;


{****************уравнение для поиска  k***********************************}

 function Fk(z:real) : real;
   begin
     Fk:=2*z-SIN(z)-1.2;
   end;

{**********************************МПД-k***********************************}

 function MPD (a:real; b:real) : real;
    Var x1, x2, zn : real;
    Begin

       x1:=0;
       Repeat
          x2:=x1;
          x1:=(Fk(b)*a-Fk(a)*b)/(Fk(b)-Fk(a));
          zn:=Fk(a)*Fk(x1);
          if zn<0 then b:=x1 else a:=x2;
       Until (abs(x1-x2)<0.0001);
       MPD:=x1;

     End;



{********************************  G(x) ***********************************}

 Function G(z:real; zy:real; zy1:real; zy11:real) : real;
   Begin
      G:=zy11+COS(zy11)-(z*z+zy)-k*zy1+SIN(zy1);
{      writeln('#');}
   End;


{*****************************Пoиск k****************************************}

 function k_search : real;

  Var i, val, kd : integer;
      zn, a, b, x1, step, x_sr : double;

   Begin

     a:=0.0;
     b:=1.0;
     kd:=1;
     step:=b/kd;
{     kd:=round(b/step);}
     Repeat
       x1:=a;
       For i:=1 to kd do
        begin
         val:=1;
         zn:=Fk(x1)*Fk(x1+step);
         writeln ('[',x1:5:2,';',(x1+step):5:2,']');
         if zn<0 then
            begin
              val:=0;
              x_sr:=MPD(x1,x1+step);
            end
            else  x1:=x1+step;
        end;
     b:=b*2;
     kd:=kd*2;
     step:=b/kd;
     Until (val=0);
     k_search:=x_sr;
   End;


{*******************************Пoдбoр Y''(a)********************************}

 Function Y_search(z:real; yz:real; yz1:real):real;
  Var a, b, yz11, zn, get_y, val, step : double;
      flag, i, kd : integer;

  Begin
   a:=-0.5;
   b:=0.5;
   kd:=1;

   Repeat
      step:=(b-a)/2;
      yz11:=a;
      flag:=0;
      For i:=0 to kd do
          begin
           zn:=G(z,yz,yz1,yz11)*G(z,yz,yz1,yz11+step);

           if zn<0 then
             begin
               a:=yz11;
               b:=yz11+step;
               val:=0;
               Repeat
                 val:=yz11;
                 yz11:=(a+b)/2;
                 zn:=G(z,yz,yz1,a)*G(z,yz,yz1,yz11);
                 if zn<0 then b:=yz11 else a:=yz11;
               Until (abs(val-yz11)<0.001);
               get_y:=yz11;
               flag:=1;
             end
             else yz11:=yz11+step;
             if flag=1 then break;
         end;
        a:=a-0.01;
        b:=b+0.01;
     {   kd:=kd*2;}
   Until (flag=1);
   Y_search:=get_y;


  End;

{**************************Рунге-Кутт 4-гo пoрядкa **************************}



 procedure Runge(step:real);
  Var temp : twofloor;
      i    : integer;

  Begin

    kf_r[1,1]:=vector_y[2];
    kf_r[2,1]:=y__;
    for i:=1 to 2 do
        temp[i]:=vector_y[i]+step/2*kf_r[i,1];

    kf_r[1,2]:=temp[2];
    kf_r[2,2]:=Y_search(x+step/2,temp[1],temp[2]);

    for i:=1 to 2 do
        temp[i]:=vector_y[i]+step/2*kf_r[i,2];

    kf_r[1,3]:=temp[2];
    kf_r[2,3]:=Y_search(x+step/2,temp[1],temp[2]);

    for i:=1 to 2 do
        temp[i]:=vector_y[i]+step*kf_r[i,3];

    kf_r[1,4]:=temp[2];
    kf_r[2,4]:=Y_search(x+step,temp[1],temp[2]);

    for i:=1 to 2 do
        vector_y[i]:=vector_y[i]+step/6*(kf_r[i,1]+2*kf_r[i,2]+
                     2*kf_r[i,3]+kf_r[i,4]);


  End;


{******************************* Sila toka **********************************}

 procedure Volt;
   Var index : integer;

   Begin
      x:=0.05;
      writeln;
      writeln;
      writeln('                  |    З ряд q   |   сила тока  I   | ' );
{      writeln(f ,'                  |    З ряд q   |   сила тока  I   | ' );
 }     writeln('                   ----------------------------------');
  {    writeln(f,'                   ----------------------------------');
   }   For index:=2 to 20 do
        begin
            writeln('                  |     ',x:4:2,'     |   ',abs(koord[2,index]):10:7,'    | '  );
{            writeln(f,'                  |     ',x:4:2,'     |   ',abs(koord[2,index]):10:7,'    | '  );
 }           x:=x+0.05;
        end;

   End;


{****************************** Title *************************************}

 Procedure Title;

   Begin
{
     initgr;
     ClearDevice;
     SetBkColor(7);
     SetColor(1);
     SetTextStyle(10,0,6);
     SetColor(15);
     SetTextStyle(10,1,5);
     OutTextXY(10,135,' Press <Enter> to continue');

     Readln;


    ClearDevice;
    SetTextJustify(1,1);
    SetBkColor(8);
    SetColor(15);
    SetTextStyle(10,0,9);
    OutTextXY(320,190,'1. Решение дифференци "ьн(r)г(r) ур внения 2-г(r) п(r)рядк ');
    OutTextXY(320,230,'2. Гр фик y(x)');
    OutTextXY(320,270,'3. Р счёт т(r)к ');
    OutTextXY(320,310,'4. Вых(r)д');

    Readln;
    ClearDevice;

    CloseGraph;
                          }
                          clrscr;
    writeln('тут было меню');
          readln;
   End;






{********************** main begin ***********************************}

 Var temp : twofloor;
     i, j, m, kd, kd1, x_g, y_g : integer;
     dbl_take, dbl_takeh : array[1..2,1..1024] of double;
     norma, delta, yx, delta1, zn : double;
     a, b, a1, b1, val1, yb_real, step, step1, val : real;
     flag : byte;



 Begin

{   assign(f, 'result.dat');}
   {Title;}

   clrscr;
   k:=k_search;


   a1:=-0.45;
   b1:=0.2;
   delta:=0;

   writeln('метод стpельб');
   Repeat

       step:=abs((b1-a1)/2);
       yx:=a1;
       vector_y[1]:=1;
       vector_y[2]:=yx;
       flag:=0;
       for m:=1 to 2 do
           temp[m]:=vector_y[m];

       For j:=0 to kd1 do
           begin


           y__:=Y_search(0,1,yx);


              a:=0.0;
              b:=1.0;
              kd:=1;
              x:=a;
              norma:=0;
              step1:=(b-a)/kd;

              For i:=1 to kd do
                  begin

                     Runge(step1);

                     for m:=1 to 2 do
                     dbl_take[m,i]:=vector_y[m];
                     x:=x+step1;
                  end;

              Repeat
                  x:=a;
                  for m:=1 to 2 do
                      vector_y[m]:=temp[m];

                  kd:=kd*2;
                  step1:=(b-a)/kd;

                  For i:=1 to kd do
                  begin
                      Runge(step1);
                      for m:=1 to 2 do
                         dbl_takeh[m,i]:=vector_y[m];
                      x:=x+step1;
                  end;

                  norma:=0;
                  for i:=1 to round (kd/2) do
                      begin
                         delta:=0;
                         for m:=1 to 2 do
                           delta:=delta+abs(dbl_take[m,i]-dbl_takeh[m,2*i-1]);

                          if delta>norma then norma:=delta;
                      end;


                  For i:=1 to kd do
                      For m:=1 to 2 do
                          dbl_take[m,i]:=dbl_takeh[m,i];

              Until (norma<EPS);

              flag:=0;
              delta:=vector_y[1];
              zn:=abs(delta-Yt);

{ !!!}         writeln('k = ',yx:8:5,'    y[b] = ',vector_y[1]:15:11); {}

              if zn<0.001 then
                 begin
                   val1:=yx;
                   writeln;
                   write('МПД ');
                   a:=yx;
                   b:=yx+step;
                   val:=0;
                   Repeat
                       val:=yx;
                       yx:=(a+b)/2;
                       zn:=(a-Yt)*(yx-Yt);
                       if zn<0 then b:=yx else a:=yx;
                       {write('*');}
                       writeln('yx=',yx:4:5);
                       {delay(500);}
                   Until (abs(val-yx)<0.0001);
                   val:=yx;
                   flag:=1;
                 end
                 else yx:=yx+step;

                 if flag=1 then break;
             {write('.');}
             end;


             a1:=a1-0.005;
             b1:=b1+0.005;

    Until (flag=1);

    y__:=Y_search(0,1,val1);

{    writeln;
    writeln;
    writeln;}
    writeln('y'' = ',val1:9:6);
{    writeln; }
    writeln('y'''' = ',y__:10:7);


    readln;
    clrscr;

    vector_y[1]:=1;
    vector_y[2]:=val1;

    x:=0.05;
    for i:=2 to 21 do
      begin
        Runge(0.05);
        koord[1,i]:=vector_y[1];
        koord[2,i]:=vector_y[2];
        x:=x+0.05;
      end;
     koord[1,1]:=1;
     koord[2,1]:=val1;
     koord[1,21]:=0.5;


    YN[1]:=koord[1,1];
    YN[2]:=koord[1,5];
    YN[3]:=koord[1,9];
    YN[4]:=koord[1,13];
    YN[5]:=koord[1,17];
    YN[6]:=koord[1,21];

    readln;
    clrscr;
    for i:=1 to 21 do
        writeln (koord[1,i]:7:4);
    readln;
    clrscr;


{*************************************************************************}

 initgr;
 ClearDevice;

 SetBkColor(7);
 maxx_r:=1;
 minx_r:=0;
 t:=0;
 q:=1;
 r:=0;

 maxy_r:=koord[1,21];
 miny_r:=koord[1,1];

 x0:=40;
 x1:=600;
 y0:=190;
 y1:=290;
 SetColor(2);

 line(40,450,600,450);
 line(40,450,40,30);
 line(600,450,585,445);
 line(600,450,585,455);
 line(40,30,35,45);
 line(40,30,45,45);

 kx:=trunc((x1-x0)/(maxx_r-minx_r));
 ky:=trunc((y1-y0)/(maxy_r-miny_r));


 SetColor(15);
 x:=minx_r;
 y:=koord[1,1];
 moveto(XG(x),YG(y));
 for i:=1 to 21 do
   begin
     y:=koord[1,i];
     x_g:=XG(x);
     y_g:=YG(y);
     lineto(x_g,y_g);
     x:=x+DX;
   end;
 readln;

{**************************************************************************}

  for i:=1 to n do
    begin
      x_g:=XG(XN[i]);
      y_g:=YG(YN[i]);
      line(x_g-3, y_g, x_g+3, y_g);
      line(x_g, y_g-3, x_g, y_g+3);
      line(x_g-3, y_g-3, x_g+3, y_g+3);
      line(x_g-3, y_g+3, x_g+3, y_g-3);
    end;

 x:=minx_r;
 y:=Nuton(x);
 x_g:=XG(x);
 y_g:=YG(y);

 setcolor(4);
 moveto(x_g, y_g);
for i:=1 to 21 do
   begin
     x_g:=XG(x);
     y:=Nuton(x);
     y_g:=YG(y);
     lineto(x_g,y_g);
     delay(500);
     x:=x+DX;
   end;
 readln;


 CloseGraph;

{  rewrite(f);}
  Volt;
{  close(f);    }
  readln;




 End.
