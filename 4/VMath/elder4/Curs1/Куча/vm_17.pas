Uses  crt,graph;
Const eps=0.001;
      Int=1;
      x0=0;
      y0=10;
      X_Newton:array[0..5] of real=(0,0.2,0.4,0.6,0.8,1);
Type  mass=array[1..4] of real;
Var   K,L:mass;
      ch:char;
      delta:array[1..5] of real;
      del1,del2,del3,del4,del5:array[0..4] of real;
      Y_Newton:array[0..5] of real;
      Batt,XX:array[1..9] of real;
      h,hh,sum,h_eps,a,b,aa,bb,kk,k1,m,x,y,y1,y_rez,yy_rez,g_rez,mm,maxx:real;
      i,j,jj,ii,iii,n,nn,n1:integer;
      yy,yy1,yy2,yyy,raz:array [1..400] of real;
Function Fun(x,y,y1,y2:real):real;
  begin
     Fun:=y2-4*cos(y2)+16*y/(16+y2)-10*exp(-15*x);
  end;
Function MPD(a,b,x,y,y1:real):real;
  var c,a1,b1:real;
  begin
    a1:=a;
    b1:=b;
    n:=round(ln((b1-a1)/eps)/Ln(2));
    For i:=1 to n do
      begin
        c:=(a1+b1)/2;
        if (Fun(x,y,y1,a1)*Fun(x,y,y1,c))<0 then b1:=c
          else a1:=c;
      end;
    MPD:=c;
  end;
Procedure Interval(x,y,y1:real);
  begin
    hh:=0.3;
    a:=-hh;
    b:=hh;
    Repeat
      m:=Fun(x,y,y1,a)*Fun(x,y,y1,b);
      a:=2*a;
      b:=b*2;
    Until m<0;
  end;
Function F1(gi:real):real;
  begin
     F1:=gi;
  end;
Procedure Runge_Cutta(h,xi,yi,gi:real);
  begin
    K[1]:=F1(gi);
    Interval(xi,yi,gi);
    L[1]:=MPD(a/2,b/2,xi,yi,gi);
    K[2]:=F1(gi+L[1]*h/2);
    Interval(xi+h/2,yi+K[1]*h/2,gi+L[1]*h/2);
    L[2]:=MPD(a/2,b/2,xi+h/2,yi+K[1]*h/2,gi+L[1]*h/2);
    K[3]:=F1(gi+L[2]*h/2);
    Interval(xi+h/2,yi+K[2]*h/2,gi+L[2]*h/2);
    L[3]:=MPD(a/2,b/2,xi+h/2,yi+K[2]*h/2,gi+L[2]*h/2);
    K[4]:=F1(gi+L[3]*h);
    Interval(xi+h,yi+K[3]*h,gi+L[3]*h);
    L[4]:=MPD(a/2,b/2,xi+h,yi+K[3]*h,gi+L[3]*h);
    y_rez:=yi+h/6*(K[1]+2*K[2]+2*K[3]+K[4]);
    g_rez:=gi+h/6*(L[1]+2*L[2]+2*L[3]+L[4]);
  end;
Procedure Tabl(h1,k1:real);
   begin
      x:=x0;
      y:=y0;
      y1:=k1;
      for j:=1 to round(Int/h1) do
        begin
          Runge_cutta(h1,x,y,y1);
          x:=x+h1;
          y:=y_rez;
          y1:=g_rez;
          yy[j]:=y_rez;
        end;
      x:=0;
   end;
Function max:real;
   begin
     n1:=round(Int/h/2);
     for ii:=1 to n1 do
             raz[ii]:=abs(yy1[ii]-yy2[2*ii]);
     maxx:=0;
     for ii:=1 to n1 do
        if  maxx<raz[ii] then maxx:=raz[ii];
     max:=maxx;
   end;
Function Int_str(kk:real):real;
   begin
      h_eps:=0.05;
      Tabl(h_eps,kk);
      for i:=1 to round(Int/h_eps) do
         yy1[i]:=yy[i];
      h_eps:=h_eps/2;
      Tabl(h_eps,kk);
      for i:=1 to round(Int/h_eps) do
          yy2[i]:=yy[i];
      maxx:=max;
      while maxx>15*eps do
         begin
            for i:=1 to round(Int/h_eps) do
               yy1[i]:=yy2[i];
            h_eps:=h_eps/2;
            Tabl(h_eps,kk);
            for ii:=1 to round(Int/h_eps) do
               yy2[ii]:=yy[ii];
            maxx:=max;
         end;
      yy_rez:=yy2[round(Int/h_eps)]+1/15*(yy2[round(Int/h_eps)]-yy1[round(Int/h_eps/2)]);
      Int_str:=yy_rez-12;
  end;
Function MPD_str(a,b:real):real;
  var c,a1,b1:real;
  begin
    a1:=a;
    b1:=b;
    nn:=round(ln((b1-a1)/eps)/Ln(2));
    For iii:=1 to nn do
      begin
        c:=(a1+b1)/2;
        if ((Int_str(a1))*(Int_str(c)))<0 then b1:=c
          else a1:=c;
      end;
    MPD_str:=c;
  end;
Function Strelb:real;
  begin
    aa:=-0.1;
    bb:=0.1;
    h:=0.1;
    Repeat
      m:=Int_str(aa)*Int_str(bb);
      aa:=2*aa;
      bb:=bb*2;
    Until m<0;
    Strelb:=MPD_str(aa/2,bb/2);
  end;
procedure Make_Y_Newton;
   begin
      Y_Newton[0]:=10;
      for i:=1 to 5 do
         begin
           j:=round(X_newton[i]/h_eps);
           Y_Newton[i]:=yy2[j];
         end;   end;
Function Factorial(n1:integer):integer;
   var f,j1:integer;
   begin
     f:=1;
     for j1:=1 to n1 do
        f:=f*j1;
     Factorial:=f;
   end;
Procedure Make_delta;
   begin
     for i:=0 to 4 do
        del1[i]:=Y_Newton[i+1]-Y_Newton[i];
     delta[1]:=del1[0];
     for i:=0 to 3 do
        del2[i]:=del1[i+1]-del1[i];
     delta[2]:=del2[0];
     for i:=0 to 2 do
        del3[i]:=del2[i+1]-del2[i];
     delta[3]:=del3[0];
     for i:=0 to 1 do
        del4[i]:=del3[i+1]-del3[i];
     delta[4]:=del4[0];
     for i:=0 to 0 do
        del5[i]:=del4[i+1]-del4[i];
     delta[5]:=del5[0];
   end;
Function Newton(perem:real):real;
   var q,q1,pr:real;
   begin
      pr:=1;
      sum:=Y_Newton[0];
      q:=(perem-X_Newton[0])/0.2;
      q1:=q;
      for i:=1 to 5 do
         begin
            for ii:=1 to i do
              begin
                 pr:=pr*q1;
                 q1:=q1-1;
              end;
            q1:=q;
            sum:=sum+delta[i]*pr/Factorial(i);
            pr:=1;
         end;
      Newton:=sum;
   end;
procedure Power;
   begin
      writeln('Вычисление мощности');
      writeln('с помощью интерполяции многочленом Ньютона');
      writeln;
      XX[1]:=0.12;
      for i:=2 to 9 do
        XX[i]:=XX[i-1]+0.1;
      for jj:=1 to 9 do
         begin
            YY[jj]:=Newton(XX[jj])*Newton(XX[jj]);
            writeln('при x = ',XX[jj]:3:2,' мощность равна ',YY[jj]:8:6);
         end;
   end;
procedure Graphic;
var
   gd,gm,i:integer;
   xx,xmin,xmax,ymin,ymax:real;
function kx(x:real):integer;
   begin
     kx:=30+round(570*(x-xmin)/(xmax-xmin));
   end;
function ky(y:real):integer;
   begin
     ky:=380-round((280*(y-ymin)/(ymax-ymin)));
   end;
  begin
     gd:=detect;
     initgraph(gd,gm,'bgi');
     xmin:=0;
     xmax:=1;
     ymin:=0;
     ymax:=yy2[1];
     for i:=1 to round(Int/h_eps) do
        begin
           if ymax<yy2[i] then ymax:=yy2[i];
        end;
     xx:=xmin;
     setlinestyle(0,0,3);
     moveto(kx(xx),ky(y0));
     for i:=1 to round(Int/h_eps) do
        begin
           xx:=xx+h_eps;
           lineto(kx(xx),ky(yy2[i]));
        end;
     setcolor(white);
     setlinestyle(0,0,0);
     line(kx(0),ky(ymin),kx(0),ky(ymax));
     line(kx(xmin),380,kx(xmax),380);
     line(kx(0),ky(ymax),kx(0)-5,ky(ymax)+5);
     line(kx(0),ky(ymax),kx(0)+5,ky(ymax)+5);
     line(kx(xmax),380,kx(xmax)-5,375);
     line(kx(xmax),380,kx(xmax)-5,385);
     xx:=xmin;
     setcolor(red);
     setlinestyle(0,0,2);
     moveto(kx(xx),ky(Newton(xx)));
     while xx<=xmax do
        begin
           xx:=xx+h_eps;
           lineto(kx(xx),ky(Newton(xx)));
        end;
     setcolor(white);
     setlinestyle(0,0,3);
     for i:=0 to 5 do
        circle(kx(X_Newton[i]),ky(Y_Newton[i]),2);
  end;
Begin
  clrscr;
  mm:=strelb;
  writeln('Метод стрельб:');
  writeln('K = ',mm:8:6);
  writeln('При таком значении К значение функции y(1) = ',yy2[round(Int/h_eps)]:8:6);
  writeln;
  writeln('Метод Рунге-Кутта 4-ого порядка с точностью eps = 0.001');
  writeln('Точность достигнута при шаге = ',h_eps:5:4);
  writeln('Количество элементов в таблице:',round(Int/h_eps));
  writeln('Для вывода таблицы значений функции нажмите ENTER ');
  ch:=readkey;
  if ch=#13 then
    begin
     x:=0;
     readln;
     for i:=1 to round(Int/h_eps) do
        begin
           writeln(i);
           x:=x+h_eps;
           writeln('x = ',x:8:6);
           writeln('y(x) = ',yy2[i]:7:5);
           readln;
        end;
    end;
   writeln;
   Make_Y_Newton;
   Make_delta;
   Power;
   writeln;
   writeln('Нажмите ENTER для вывода');
   writeln('графика сравнения значений функции');
   writeln('и результатов интерполяции многочленом Ньютона');
   ch:=readkey;
   if ch=#13 then
     begin
      graphic;
      readln;
     end;
closegraph;
end.
