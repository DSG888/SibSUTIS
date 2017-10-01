{$N+}
uses crt, graph;
const eps=0.00001;
      y_0=1;
      y_05=0;
      rx=100;
      ry=100;
type
  typeY=array[1..2] of double;
  TypeC=array[1..4,1..4] of double;
  TypeD=array[1..4] of double;
  TypeMiX=array[0..5] of double;
  typeh=array[1..5] of double;

var kk,k:double;
    yy:TypeY;
    EndHag:double;
    c: Typec;
    d: typeD;
    m,x,u: typeMix;
    h: typeH;

function Func(x:double; y:double; y1:double; y2:double):double;
begin
func:=y2-sin(y2)-cos(y)-k*y1+exp(-x);
end;

function FindK:double;
var a,b,k,kt,c,d,h:double;
    i:byte;

  Function f(x:double):double;
  begin
   f:=4*x*x*x*x*x-arctan(x/(sqrt(1+x*x)))-1;
  end;

  Function MPD(a,b:double): double;
  Var
     c:double;
  Begin
    c:=(a+b)/2;
    while abs((b-a)/2)>eps/1000 do begin
      if (f(a)*f(c)<0) then b:=c else a:=c;
      c:=(a+b)/2;
    end;
    mpd:=c;
  end;
begin
  h:=1; c:=-0.5; d:=0.5;
  a:=c; b:=a+h;i:=0; k:=10000;
while i<1 do begin
 while b<=d do
  begin
    if f(a)*f(b)<0 then
      begin
         kt:=mpd(a,b);
         if (kt<k) and (kt>0) then k:=kt;
         inc(i);
      end;
    a:=b; b:=b+h;
  end;
c:=c-1; d:=d+1; h:=h/2;
end;
findK:=k;
end;

procedure PoiskInt(var a:double; var b:double; x:double; y:double; y1:double);
var c,d,h,fa,fb: double;
    i: integer;
begin
c:=-5; d:=5; h:=1; a:=c; b:=a+h;
fa:=1; fb:=1;
 while fa*fb>0 do
   begin
   a:=c;b:=a+h;
   fa:=func(x,y,y1,a); fb:=func(x,y,y1,b);
   while b<d do
      begin a:=b;
            b:=b+h;
            fa:=fb;
            fb:=func(x,y,y1,b);
            if fa*fb<0 then break;
      end;
      c:=c-1; d:=d+1; h:=h/2;
   end;
end;


procedure MHord(x:double; y:double; y1:double; var kr:double);
var fa,fb,fc,c,cp,a,b:double;
begin
     PoiskInt(a,b,x,y,y1);
     fa:=func(x,y,y1,a);fb:=func(x,y,y1,b);
     c:=0; cp:=(fb*a-fa*b)/(fb-fa);
     While (abs(cp-c)>eps) do
      begin
        c:=cp;
        fc:=func(x,y,y1,c);
        if fa*fc<0 then begin b:=c; fb:=fc; end
        else begin a:=c; fa:=fc; end;
        cp:=(fb*a-fa*b)/(fb-fa);
      end;
        kr:=cp;
end;

function Difur(x:double; y:double; y1:double):double;
var a,b,kkk:double;
begin
Mhord(x,y,y1,kkk);
difur:=kkk;
end;


function RungeKutt(xi:double; var Y:TypeY; h:double):double;
var K:array[1..4,1..2] of double;
    rrr:typeY;
begin
k[1,1]:=y[2];              k[1,2]:=difur(xi,y[1],y[2]);
k[2,1]:=y[2]+(h/2)*k[1,2]; k[2,2]:=difur(xi+h/2,y[1]+(h/2)*k[1,1],y[2]+(h/2)*k[1,2]);
k[3,1]:=y[2]+(h/2)*k[2,2]; k[3,2]:=difur(xi+h/2,y[1]+(h/2)*k[2,1],y[2]+(h/2)*k[2,2]);
k[4,1]:=y[2]+h*k[3,2];     k[4,2]:=difur(xi+h,y[1]+h*k[3,1],y[2]+h*k[3,2]);
y[1]:=y[1]+(h/6)*(k[1,1]+2*k[2,1]+2*k[3,1]+k[4,1]);
y[2]:=y[2]+(h/6)*(k[1,2]+2*k[2,2]+2*k[3,2]+k[4,2]);
end;

procedure DoubleP(var Yb:typeY; kr:double);
var hh, xi:double;
    Yh,Yh_2:TypeY;
    i: integer;
begin
hh:=0.05;
xi:=0;
yh[1]:=y_0;
yh[2]:=kr;
yh_2:=yh;
While (round(xi*10000)<round(0.5*10000)) do
  begin
  RungeKutt(xi,Yh,hh);
  RungeKutt(xi,Yh_2,hh/2);
  RungeKutt(xi+hh/2,Yh_2,hh/2);

  if (abs(Yh[1]-Yh_2[1])>3*eps) then
     begin
       hh:=hh/2;
       xi:=0;
       yh[1]:=y_0;
       yh[2]:=kr;
       yh_2:=yh;
     end else xi:=xi+hh;
end;
endHag:=hh/2;
yb:=yh_2;
writeln('y(0.5)= ',yh_2[1]:11:10,'  y1(0.5)= ',yh_2[2]:11:10,' при y1(0)=',kr:11:10);
end;

procedure PoiskInt1(var a:double; var b:double);
var c,d,h:double;
    ya:TypeY; t:boolean;
begin
a:=-2; h:=0.5; b:=a+h;
doubleP(ya,a);
if ya[1]<y_05 then t:=true else t:=false;
while (t=(ya[1]<y_05)) do
   begin
     if ya[1]<y_05 then begin t:=true; a:=b; b:=b+h; end else begin t:=false; b:=a; a:=a-h; end;
     doubleP(ya,a);
   end;
   b:=a; a:=a-h;
end;

procedure shoot;
var  a,b,c,t:double;
     ya,yb,yc:TypeY;
Begin
  writeln('Поиск интервала :');
  PoiskInt1(a,b);
  writeln(' a= ',a:2:2,'   b=',b:2:2);
  DoubleP(ya,a);DoubleP(yb,b);
  repeat
    c:=((yb[1]-y_05)*a-(ya[1]-y_05)*b)/(yb[1]-ya[1]);
    DoubleP(yc,c);
    if ((ya[1]-y_05)*(yc[1]-y_05))<0 then begin b:=c; yb:=yc;  end else begin a:=c; ya:=yc; end;
  until (abs(y_05-yc[1])<eps);
 kk:=c;
 writeln;
 writeln('              Решение краевой задачи y1(0) = ',kk:10:10);
end;


Procedure ZapolnX;
var i:integer;
begin
 for i:=0 to 5 do x[i]:=0.2*i;
end;

procedure podschet_H;
 var i :integer;
   begin
      for i:=1 to 5 do
      h[i]:=abs(x[i]-x[i-1]);
   end;

procedure zapoln_C;
 var i: integer;
  begin
     for i:=1 to 4 do
       begin
          if (i-1)<>0 then c[i,i-1]:=h[i]/6;
          c[i,i]:=(h[i]+h[i+1])/3;
          if i<>(4) then c[i,i+1]:=h[i+1]/6;
       end;
  end;

procedure zapoln_D;
 var i: integer;
   begin
      for i:=1 to 4 do
       d[i]:=((u[i+1]-u[i])/h[i+1])-((u[i]-u[i-1])/h[i]);
   end;

function spline(xx:double):double;
 var i:integer;
     s: double;
  begin
     for i:=1 to 5 do
        if (xx>=x[i-1])and(xx<=x[i]) then break;

     s:=m[i-1]*(x[i]-xx)*(x[i]-xx)*(x[i]-xx)/(6*h[i])
        +m[i]*(xx-x[i-1])*(xx-x[i-1])*(xx-x[i-1])/(6*h[i])
        +(u[i-1]-(m[i-1]*h[i]*h[i]/6))*((x[i]-xx)/h[i])
        +(u[i]-(m[i]*h[i]*h[i]/6))*((xx-x[i-1])/h[i]);
     spline:=s;
  end;

procedure hod_pr(var c:TypeC; var d:typeD);
 var  b     :double;
      l,i,j :integer;
  begin
     for i:=1 to 3 do
         begin
              for j:=i+1 to 4 do
                  begin
                       b:=c[j,i]/c[i,i];
                       for l:=i to 4 do c[j,l]:=c[j,l]-c[i,l]*b;
                       d[j]:=d[j]-d[i]*b;
                  end;
         end
  end;

procedure back(c:typeC; d:typeD; var m:typeMiX);
 var i,j:integer;
  begin
    for i:=4 downto 1 do
        begin
             m[i]:=d[i];
             for j:=4 downto i+1 do m[i]:=m[i]-c[i, j]*m[j];
             m[i]:=m[i]/c[i, i];
        end;
    m[0]:=0; m[5]:=0;
    for i:=0 to 5 do
        writeln('m[',i,']= ',m[i]:8:4);
    writeln;
  end;

procedure graphik;
 var i:double; j,gm,gd: integer;
     yy:Typey;
     oy,ox:integer;
  begin
       gm:=0; gd:=0;
       initgraph(gm,gd,'c:\units\pascal\bgi');
       cleardevice;

       ox:=20;
       oy:=200;
       u[0]:=y_0;
       j:=1;
       yy[1]:=y_0;
       yy[2]:=kk;

       setcolor(white);
       line(ox,0,ox,480);
       line(0,oy,640,oy);

       i:=0;
       moveto(round(i*rx)+ox,oy-round(y_0*ry));
       while i<=1 do
       begin
            rungeKutt(i,yy,endhag);
            i:=i+endhag;
            lineto(round(i*rx)+ox,oy-round(yy[1]*ry));
            if round(i*10000000)=round(2000000*j) then
            begin
                 u[j]:=yy[1];
                 inc(j);
            end;
       end;
       readkey;
       zapolnX;
       podschet_H;
       zapoln_C;
       zapoln_D;
       hod_pr(c,d);
       back(c,d,m);
       setcolor(5);
       i:=0;
       moveto(round(i*rx)+ox,oy-round(Spline(i)*ry));
       while i<=1 do
       begin
            i:=i+endhag;
            lineto(round(i*rx)+ox,oy-round(Spline(i)*ry));
       end;

       setcolor(lightgreen);
       for j:=0 to 5 do
       circle(round((j/5)*rx)+ox,oy-round(u[j]*ry),3);
       readkey;
       closegraph;

    end;

function Simpson(a:double; b:double; h:double):double;
var aa,bb,int:double;
begin
aa:=a; bb:=a+2*h;
Int:=0;

while round(bb*1000)<round((b+2*h)*1000) do
     begin
         if bb>=b then bb:=b;
         Int:=Int+(bb-aa)*((1/6)*Spline(aa)*Spline(aa)+
         (2/3)*Spline(aa+(bb-aa)/2)*Spline(aa+(bb-aa)/2)+(1/6)*Spline(bb)*Spline(bb));
         aa:=bb; bb:=bb+2*h;
     end;
Simpson:=Int;
end;



var i: integer;
begin
  clrscr;
  writeln;
  k:=findk;
  writeln('  Наименьший положительный корень заданного уравнения k = ',k:10:10);
  writeln('                    Идет процесс метода стрельб....');
  shoot;
  Writeln;
  writeln('          Конечный H соответствующий точности = ',endhag:10:13);
  readkey;
  graphik;
  clrscr;
  writeln('Количество выделившейся теплоты = ',Simpson(0,1,0.01):10:10);
  readkey;
end.
