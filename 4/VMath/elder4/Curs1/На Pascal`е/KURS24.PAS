uses crt, graph;
const eps=0.00001;
      y_0=1.0;
      y1_1=0.5;
      rastx=200;
      rasty=200;
type
typeY=array[1..2] of real;

var k,kkk:real;
    yy:TypeY;
    EndH:real;
    uzels:array[1..6,1..6] of real;
function func(r:shortint; x:real; y:real; y1:real; xx:real):real;
begin
if r=1 then func:=x*x*x*x*x-sin(x)-3;
if r=2 then func:=y1-(xx*xx+y)-k*x+sin(x);
end;
function Proizvod(r:shortint; x:real; y:real; y1:real; xx:real):real;
begin
proizvod:=1.2*(func(r,x-0.2,y,y1,xx)-8*func(r,x-0.1,y,y1,xx)+8*func(r,x+0.1,y,y1,xx)-func(r,x+0.2,y,y1,xx));
end;

procedure searchInt(var a:real; var b:real; r:shortint; y:real; y1:real; xx:real);
var c,d,h,fa,fb: real;
    i: integer;
begin
c:=-1; d:=1;h:=1; a:=c; b:=a+h;
fa:=1; fb:=1;
 while fa*fb>0 do
   begin     {y2}
   a:=c;b:=a+h;
   fa:=func(r,a,y,y1,xx); fb:=func(r,b,y,y1,xx);
   while b<d do
      begin a:=b;
            b:=b+h;
            fa:=fb;
            fb:=func(r,b,y,y1,xx);
            if fa*fb<0 then break;
      end;
      c:=c-1; d:=d+1; h:=h/2;
   end;
end;


procedure Mh(r:shortint;y:real; y1:real; xx:real; var kr:real);
var fa,fb,fc,c,cp,a,b:real;
begin
     searchInt(a,b,r,y,y1,xx);
     fa:=func(r,a,y,y1,xx);fb:=func(r,b,y,y1,xx);
     c:=0; cp:=(fb*a-fa*b)/(fb-fa);
     While (abs(cp-c)>eps) do
      begin
        c:=cp;
        fc:=func(r,c,y,y1,xx);
        if fa*fc<0 then begin b:=c; fb:=fc; end
        else begin a:=c; fa:=fc; end;
        cp:=(fb*a-fa*b)/(fb-fa);
      end;
        kr:=cp;
end;

procedure newton(r:shortint;y:real; y1:real; xx:real; var kr:real);
var kk: real;
begin
 kk:=kr-func(r,kr,y,y1,xx)/proizvod(r,kr,y,y1,xx);
  while (abs(kk-kr)>eps) do
    begin
     kr:=kk;
     kk:=kr-func(r,kr,y,y1,xx)/proizvod(r,kr,y,y1,xx);
    end;
  kr:=kk;
end;

function Difur(x:real; y:real; y1:real):real;
var a,b,kkk:real;
begin
Mh(2,y,y1,x,kkk);
{newton(2,y,y1,x,kkk);}
difur:=kkk;
end;


function Ronge_Kutt(xi:real; var Y:TypeY; h:real):real;{выдает Yi+1}
var K:array[1..4,1..2] of real;
    rrr:typeY;
begin
k[1,1]:=y[2]; k[1,2]:=difur(xi,y[1],y[2]);
k[2,1]:=y[2]+(h/2)*k[1,2]; k[2,2]:=difur(xi+h/2,y[1]+(h/2)*k[1,1],y[2]+(h/2)*k[1,2]);
k[3,1]:=y[2]+(h/2)*k[2,2]; k[3,2]:=difur(xi+h/2,y[1]+(h/2)*k[2,1],y[2]+(h/2)*k[2,2]);
k[4,1]:=y[2]+h*k[3,2]; k[4,2]:=difur(xi+h,y[1]+h*k[3,1],y[2]+h*k[3,2]);
y[1]:=y[1]+(h/6)*(k[1,1]+2*k[2,1]+2*k[3,1]+k[4,1]);
y[2]:=y[2]+(h/6)*(k[1,2]+2*k[2,2]+2*k[3,2]+k[4,2]);
end;

procedure DoblePereschet(var Yb:typeY; kr:real);
var hh, xi:real;
    Yh,Yh_2:TypeY;
    i: integer;
begin
hh:=0.05;
xi:=0;
yh[1]:=y_0;
yh[2]:=kr;
yh_2:=yh;
While (xi<1) do
  begin
  Ronge_Kutt(xi,Yh,hh);
  Ronge_Kutt(xi,Yh_2,hh/2);
  Ronge_Kutt(xi+hh/2,Yh_2,hh/2);

  if (abs(Yh[1]-Yh_2[1])>3*eps) then
     begin
       hh:=hh/2;
       xi:=0;
       yh[1]:=y_0;
       yh[2]:=kr;
       yh_2:=yh;
     end else xi:=xi+hh;
end;
endH:=hh/2;
yb:=yh_2;
writeln( yh_2[1]:10:10,'      ',yh_2[2]:10:10);
end;

function func_k(kkk:real):real;
var yb:Typey;
begin
doblepereschet(yb,kkk);
func_k:=yb[2]-y1_1;
end;

function Proizvod1(kkk:real):real;
begin
proizvod1:=1.2*(func_k(kkk-0.2)-8*func_k(kkk-0.1)+8*func_k(kkk+0.1)-func_k(kkk+0.2));
end;

procedure searchInt1(var a:real; var b:real);
var c,d,h,fa,fb: real;
    i: integer;
begin
c:=1; d:=2;h:=0.1; a:=c; b:=a+h;
fa:=1; fb:=1;
 while fa*fb>0 do
   begin
   a:=c;b:=a+h;
   fa:=func_k(a); fb:=func_k(b);
   while b<d do
      begin a:=a+h;
            b:=b+h;
            fa:=fb;
            fb:=func_k(b);
            if fa*fb<0 then break;
      end;
      c:=c-1; d:=d+1; h:=h/2;
   end;
end;


procedure Mh1(var kkk:real);
var fa,fb,fc,c,cp,a,b:real;
begin
     searchInt1(a,b);
     writeln('a=  ',a:10:3,'  b=  ',b:10:3);
     fa:=func_k(a);fb:=func_k(b);
     c:=0;cp:=(fb*a-fa*b)/(fb-fa);
     While (abs(cp-c)>eps) do
      begin
        c:=cp;
        fc:=func_k(c);
        if fa*fc<0 then begin b:=c; fb:=fc; end
        else begin a:=c; fa:=fc; end;

        cp:=(fb*a-fa*b)/(fb-fa);
      end;
        kkk:=cp;
end;

procedure newton1( var kkk:real);
var kk: real;
begin
 kk:=kkk-(func_k(kkk)/proizvod1(kkk));
  while (abs(kk-kkk)>eps) do
    begin
     kkk:=kk;
     kk:=kkk-(func_k(kkk)/proizvod1(kkk));
     writeln('kk= ',kk:10:10)
    end;
  kkk:=kk;
end;

procedure strelba;
var a,b:real;
begin
 Mh1(kkk);
 writeln('Решение краевой задачи k=y1(0)===',kkk:10:10);
end;



procedure zapoln_tabl;
 var i,j:integer;
  begin
     for i:=2 to 6 do
       for j:=6-i+1 downto 1 do
         uzels[j,i]:=uzels[j+1,i-1]-uzels[j,i-1];
  end;
procedure print;
 var i,j:integer;
  begin
     for i:=1 to 6 do
       begin
         for j:=1 to 6 do
           write(uzels[i,j]:10:4);
         writeln;
       end;
  end;

function nuton(x:real; h:real):real;
 var  i,j   :integer;
     fuck   :longint;
     q,qq,p :real;
  begin
      fuck:=1;
      q:=(x)/h;
      qq:=q;
      p:=uzels[1,1];

      for i:=2 to 6 do
        begin
          p:=p+(uzels[1,i]*qq)/fuck;
          qq:=qq*(q-i+1);
          fuck:=fuck*i;
        end;
      nuton:=p;
  end;

procedure graphik;
 var i:real; j,gm,gd: integer;
     yy:Typey;
     oy,ox:integer;
  begin
     gm:=0; gd:=0;
     initgraph(gm,gd,'c:\tp7\bgi');
     cleardevice;
     settextstyle(7,0,3);
     outtextxy(170,350,'Гpафик функции найденой из ДУ');
     setcolor(green);
     outtextxy(190,400,'и интерполирующей функции');

     ox:=20;
     oy:=470;
     uzels[1,1]:=y_0;
     j:=1;
     yy[1]:=y_0;
     yy[2]:=kkk;

    setcolor(white);
    line(ox,0,ox,480);
    line(0,oy,640,oy);

    i:=0;
    moveto(round(i*rastx)+ox,oy-round(y_0*rasty));
    while i<=1 do
       begin
         ronge_Kutt(i,yy,endh);
         i:=i+endh;
         lineto(round(i*rastx)+ox,oy-round(yy[1]*rasty));
         if round(i*1000)=round(200*j) then
           begin
              uzels[j+1,1]:=yy[1];
              inc(j);
           end;
       end;
    readkey;
    zapoln_tabl;
    setcolor(2);
    i:=0;
    moveto(round(i*rastx)+ox,oy-round(nuton(i,0.2)*rasty));
    while i< 1.1 do
       begin
         i:=i+endh;
         lineto(round(i*rastx)+ox,oy-round(nuton(i,0.2)*rasty));
       end;

    setcolor(white);
    for j:=0 to 5 do
      circle(round((j/5)*rastx)+ox,oy-round(uzels[j+1,1]*rasty),3);
   readkey;
   closegraph;

  end;

function Simpson(a:real; b:real; h:real):real;
var aa,bb,int:real;
begin
aa:=a; bb:=a+2*h;
Int:=0;

while round(bb*1000)<round((b+2*h)*1000) do
     begin
      if bb>=b then bb:=b;
      Int:=Int+(bb-aa)*((1/6)*nuton(aa,0.2)*nuton(aa,0.2)+
      (2/3)*nuton(aa+(bb-a)/2,0.2)*nuton(aa+(bb-a)/2,0.2)+(1/6)*nuton(bb,0.2)*nuton(bb,0.2));
      aa:=bb; bb:=bb+2*h;
     end;
Simpson:=Int;
end;
procedure KursWork;
var gd,gm,i:integer;
    c:char;
begin
gm:=0;
gd:=0;
c:='`';
initgraph(gm,gd,'c:\tp7\bgi');
cleardevice;
settextstyle(7,0,6);

for i:=1 to 6 do
     begin
       setcolor(lightblue);
       outtextxy(60,150,'Курсовая работа');
       delay(random(500));
       setcolor(0);
       outtextxy(60,150,'Курсовая работа');
       delay(random(500));
     end;

while c='`' do
     begin
       settextstyle(7,0,6);
       setcolor(lightblue);
       outtextxy(60,150,'Курсовая работа');
       delay(random(1000));
       setcolor(0);
       outtextxy(60,150,'Курсовая работа');
       delay(random(1000));
       settextstyle(7,0,3);
       setcolor(red);
       outtextxy(40,250,'По курсу Вычислительная Математика');
       delay(random(1000));
       setcolor(0);
       outtextxy(40,250,'По курсу Вычислительная Математика');
       delay(random(1000));
       setcolor(green);
       outtextxy(270,370,'Выполнил : Юсупов Ренат');
       outtextxy(270,400,'            Группа П-94 ');
       delay(random(1000));
       setcolor(0);
       outtextxy(270,370,'Выполнил : Юсупов Ренат');
       outtextxy(270,400,'            Группа П-94 ');
       delay(random(1000));
       if keypressed then c:=readkey;
     end;

closegraph;
end;
procedure vivod;
var i: integer;
    yy: typeY;
    x:real;
begin
  clrscr;
  x:=0;
  yy[1]:=y_0;
  yy[2]:=kkk;
  i:=1;
  writeln('y(',x:2:2,')= ',yy[1]:10:10,'   ','y1(',x:2:2,')= ',yy[2]:10:10,'   ','nuton(',x:2:2,')= ',nuton(x,0.2):10:10);
    while x<=1 do
       begin
         ronge_Kutt(x,yy,endh);
         x:=x+endh;
         if round(x*1000)=round(50*i) then
           begin
             writeln('y(',x:2:2,')= ',yy[1]:10:10,'   ','y1(',x:2:2,')= ',
             yy[2]:10:10,'   ','nuton(',x:2:2,')= ',nuton(x,0.2):10:10);
             inc(i);
           end;
       end;
    readkey;

end;

var i: integer;
begin
kurswork;
clrscr;

Mh(1,0,0,0,k);
newton(1,0,0,0,k);
writeln;
writeln('      x^5 - sin(x) -3 = 0');
writeln;
writeln('Решение этого уравнения x=',k:10:10);

yy[1]:=y_0;
yy[2]:=y1_1;
writeln;
writeln(' Идет просесс метода стрельб....');
strelba;
writeln('Конечный H соответствующий точности = ',endh:10:10);
writeln('Press any key...');
readkey;

graphik;

clrscr;
writeln('Таблица конечных разностей для метода Ньютона');
print;
readkey;
writeln('Количество тепла =====',Simpson(0,1,0.01):10:10);
readkey;
vivod;
end.