   Uses crt, graph;
   Const epsi=0.0001;
         e=0.000001;
         a_init=0;
         b_init=1;
         y0_init=1;
         y1_init=5;
         n=6;
         ADRES='c:\tp\bgi';
   Type
        MassY=array[1..2] of real;
        Mass=array[0..1000] of MassY;
   Var
        Yn,rez,rez1:Mass;
        k:real;
        h,hh,x0:real;
        d_y:array[0..n-1,0..n-1] of real;
        xk,yk,xf,yf,xmax,xmin,ymax,ymin:integer;

   function ff(x,y,yy:real):real;
   begin
     ff:=yy-x-sin(1.4*yy)-2.3*y;
   end;

   {--------------Вычисление у''(решаем НУ с помощью МПД)-------------}
   Function y2(x,y:real):real;
   Var    a,a1,b,h,c:real;
          l:boolean;
      procedure MPD(aa,bb:real);
      begin
         repeat
           c:=(aa+bb)/2;
           if ff(x,y,aa)*ff(x,y,c)<0 then bb:=c;
           if ff(x,y,bb)*ff(x,y,c)<0 then aa:=c;
         until (bb-aa)/2<e;
      c:=(aa+bb)/2;
      end;
   Begin
   a:= -1; b:= a; h:= 1; l:= false;
     repeat
       a1:=b;
       b:=b+h;
       if ff(x,y,a1)*ff(x,y,b)<0 then
         begin MPD(a1,b); l:=true; end;
       if b>=abs(a) then
         begin h:=h/2; a:=a*2; b:=a; end;
     until l=true;
   y2:=c;
   End;

   {------Вычисление функции F------}
   Procedure F(x:real; Yi:MassY; var Yn:MassY);
   begin
      Yn[1]:=Yi[2];
      Yn[2]:=y2(x,Yi[1]);
   end;

   {--------------Поиск y'(x0)=k методом стрельб | g(k)=y1_init-------------}
   Function R_K(kk:real):real;
   Var
      K1,K2,K3,K4,Yo,Y,Y1:MassY;
      h,a:real;
      i:integer;
   Begin
     a:=a_init;
     h:=0.1;
     i:=0;
     Yo[1]:=y0_init;
     Yo[2]:=kk;
     repeat
        F(a,Yo,K1);
        for i:=1 to 2 do Y[i]:=Yo[i]+K1[i]*h/2;
        F(a+h/2,Y,K2);
        for i:=1 to 2 do Y[i]:=Yo[i]+K2[i]*h/2;
        F(a+h/2,Y,K3);
        for i:=1 to 2 do Y[i]:=Yo[i]+K3[i]*h;
        F(a+h,Y,K4);
        for i:=1 to 2 do
           Y1[i]:=Yo[i]+(h/6)*(K1[i]+2*K2[i]+2*K3[i]+K4[i]);
        a:=a+h;
        Yo:=Y1;
     until a>=b_init;
     R_K:=Y1[1];
   End;

   Procedure Strelba;
   Var  k1,k2,t1,t2,c:real;
   Begin
     k:=1; k1:=0; k2:=0;
     repeat
       if R_K(k)<=y1_init then begin k1:=k; k:=k+1; end
          else begin k2:=k; k:=k-1; end;
     until (k1<>0) and (k2<>0);
     repeat
       c:=(k1+k2)/2;
       if R_K(c)<y1_init then k1:=c else k2:=c;
       writeln('  k=',c:8:5,'  g(k)=',r_k(c):8:5);
     until (k2-k1)/2<e;
     c:=(k2+k1)/2;
     k:=c;
     writeln('Параметр k найден методом стрельб:  ',k:8:5);
   End;

   {---------Решение СДУ I порядка методом Рунге-Кутта IV порядка--------}
   Procedure M_Runge_Kutta;
   Var
      K1,K2,K3,K4,Yo,Y:MassY;
      Yh:mass;
      prer:boolean;
      a,b:real;
      i,ii,j,j1,j2,a1,a2,max,count:integer;
   Begin
     h:=0.02; max:=0; count:=0;
     repeat
     a:=a_init;
     Yo[1]:=y0_init;
     Yo[2]:=k;
     Yn[0]:=Yo;
     Yh:=Yn;
     prer:=true;
     i:=0;
     if count=0 then Yh[0,1]:=2;
     repeat
        inc(i);
        F(a,Yo,K1);
        for j:=1 to 2 do Y[j]:=Yo[j]+K1[j]*h/2;
        F(a+h/2,Y,K2);
        for j:=1 to 2 do Y[j]:=Yo[j]+K2[j]*h/2;
        F(a+h/2,Y,K3);
        for j:=1 to 2 do Y[j]:=Yo[j]+K3[j]*h;
        F(a+h,Y,K4);
        for j:=1 to 2 do
           Yn[i,j]:=Yo[j]+(h/6)*(K1[j]+2*K2[j]+2*K3[j]+K4[j]);
        a:=a+h;
        Yo:=Yn[i];
     until a>b_init+h;

     for ii:=0 to max do
       if abs(Yh[ii,1]-Yn[2*ii,1])>15*epsi then
         begin prer:=false; inc(count); end;
     h:=h/2;  max:=i-1;
     until (prer=true);

     h:=h*2;
     a:=a_init;
     a1:=120; a2:=0;
     j1:=0; j2:=0;
     ii:=0;
     repeat
     if (trunc(a*1000)) = a1 then
           begin
              rez1[j1,1]:=Yn[ii,1];
              rez1[j1,2]:=a;
              a1:=a1+100;
              inc(j1);
           end;
        if (trunc(a*1000))=a2 then
           begin
              rez[j2,1]:=Yn[ii,1];
              rez[j2,2]:=a;
              a2:=a2+200;
              inc(j2);
           end;
     a:=a+h;
     inc(ii);
     until a>=b_init+h;
     for ii:= 0 to j1-1 do
       writeln('x=', rez1[ii,2]:4:2,'  мощность=', sqr(rez1[ii,1]):8:4);
     writeln;
     writeln('Значения, вычисленные методом Рунге-Кутта:');
     for ii:= 0 to j2-1 do
       writeln('y(',rez[ii,2]:3:1,')=',(rez[ii,1]):8:4);
     readln;
   End;

   {--------------Интерполяция по I формуле Ньютона-------------}
      Procedure Table_r;
      var
         i,j:byte;
      begin
      for i:=0 to n-1 do
          d_y[i][0]:=rez[i,1];
      for j:=1 to n-1 do
        for i:=0 to n-j do
        d_y[i][j]:=d_y[i+1][j-1]-d_y[i][j-1];
      {for i:= 0 to n-1 do begin
         for j:= 0 to n-i-1 do
         write(d_y[i][j]:8:4, '  ');
      writeln;
      end;readln;}
      end;

      Function fact(k:byte):longint;
      Var ff:longint;
          i:byte;
      Begin
        ff:=1;
        if k>1 then
           for i:=2 to k do ff:=ff*i;
        fact:=ff;
      End;

      Function  P(x:real):real;
      Var Pp,q,qq:real;
          k:byte;
      Begin
        qq:=(x-x0)/hh;
        q:=qq;
        Pp:=d_y[0][0];
        for k:=1 to n-2 do
          begin
            Pp:=Pp+q*d_y[0][k]/fact(k);
            q:=q*(qq-1);
          end;
        P:=Pp;
      End;

   PROCEDURE Njuton;
   var x:real;
   BEGIN
      hh:=0.2; x0:=0;
      Table_r;
      x:=0.0;
      writeln('Значения, проинтерполированные по Ньютону:');
      while x<=1.1 do
        begin
          writeln(' P(',x:3:1,')=', P(x):8:5);
          x:=x+0.2;
        end;
   END;

   {--------------График-------------}
   Procedure InitGraf;
   var
      GrDriver, GrMode, ErrCode: integer;
   begin
     GrDriver:= Detect;
     InitGraph(GrDriver, GrMode, ADRES);
     ErrCode:= GraphResult;
     if ErrCode <> grOk then
        writeln('Graphics error:', GraphErrorMsg(ErrCode));
     end;

   Function kx(x: real):integer;
   begin
     kx:= round((getmaxx/(xmax-xmin))*(x-xmin)) - 300;
   end;

   Function ky(ty: real):integer;
   begin
     ky:= 680 - round(getmaxy*(ty-ymin)/(ymax-ymin));
   end;

   Procedure Graphic;
   var x: real;
       i: integer;
   Begin
   hh:= 0.2; x0:= 0;
   Table_r;

     InitGraf;
     line(20,getmaxy-37,380,getmaxy-37);
     line(20,getmaxy-37,20,140);
     outtextxy(25,140,'y(x)');
     outtextxy(380,getmaxy-30,'x');
   xmin:=-1;
   xmax:=1;
   ymin:=-5;
   ymax:=5;

   x:=0; i:=1;
   moveto(kx(x),ky(1));
   repeat
     lineto(kx(x),ky(Yn[i,1]));
     setcolor(14);
     x:=x+h;
     inc(i);
   until x>=1;
   x:=0;
   moveto(kx(x),ky(P(x)));
   repeat
     lineto(kx(x),ky(P(x)));
     setcolor(4);
     x:=x+0.1;
   until x>=1.1;
   x:=0;
   for i:=0 to n-1 do
   begin
      setcolor(10);
      circle(kx(x),ky(rez[i,1]),2);
      setlinestyle(1,1,1);
      setcolor(3);
      line(kx(x),ky(0),kx(x),ky(rez[i,1]));
      x:=x+0.2;
   end;
   line(20,ky(rez[n-1,1]),kx(1.0),ky(rez[n-1,1]));
   setlinestyle(0,0,0);
   setcolor(15);
   outtextxy(kx(0.2),ky(0)+8,'0.2');
   outtextxy(kx(0.4),ky(0)+8,'0.4');
   outtextxy(kx(0.6),ky(0)+8,'0.6');
   outtextxy(kx(0.8),ky(0)+8,'0.8');
   outtextxy(kx(1.0),ky(0)+8,'1.0');
   outtextxy(10,ky(rez[n-1,1]),'5');
   outtextxy(10,ky(rez[0,1]),'1');
   outtextxy(320,70,' Runge  -  <<        >>');
   setcolor(14);
   line(430,73,480,73);
   setcolor(15);
   outtextxy(320,80,' Njuton -  <<        >>');
   setcolor(12);
   line(430,83,480,83);

   readln;
   closegraph;
   End;

   BEGIN
     clrscr;
     Strelba;
     M_Runge_Kutta;
     Njuton;
     readln;
     Graphic;
   END.