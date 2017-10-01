uses crt,graph;
const e=0.01;
      nn=5;
      n=2;

var   y11,y0,y1,y2,y3,f,f1,k1,k2,k3,k4:array[1..n] of real;
      yh,yh2,ye,yh3:array[0..1000] of real;
      ij,d,gd,gm,zn_i,kk,j1,i1,ii,i,j,p:integer;
      tc,ct,qq,ll,mmm,hr,cm,tt,rr,c1,ymin,ymax,ss,k,r,t,c,hh,ee,q,l,m,a,x,h:real;
      mm,xx,yyy:array[0..nn] of real;
      cc:array[1..nn-1,1..nn] of real;
      h1:array[1..nn] of real;
      x1,sp:array[1..2000] of real;
      fl,flag,zn,s:boolean;
      w:text;

function y(z:real):real;
 begin
  y:=z+cos(z+1)+2*y11[1]-sin(2*x);
  end;

function v(q,l:real):real;
 begin
   v:=(q+l)/2;
 end;

function ysht(z:real):real;
begin
    ysht:=1-sin(z+1);
end;

procedure nuton;
begin
    fl:=false;
    ct:=tc-y(tc)/ysht(tc);
{    writeln('t=',ct);}
    if abs(abs(ct)-abs(tc))<=ee then fl:=true else begin tc:=ct; nuton; end;
end;

procedure xx1;
begin
  qq:=-1;ll:=1;
  cm:=0;mmm:=-1;hr:=1;
 repeat
   if (y(cm)*y(mmm)<=0) then break;
   if (mmm+hr)>=ll then
    begin
         ll:=ll+1; qq:=-ll; hr:=1/ll; mmm:=qq; cm:=mmm+hr;
    end
         else begin mmm:=mmm+hr; cm:=cm+hr; end;
  until (0>1);
  r:=mmm;t:=cm;
{   writeln('a=',r);
   writeln('b=',t);
   readln;}
   i:=0;
   ij:=0;
repeat
   i:=i+1;
   cm:=v(r,t);
{   writeln('x',i,'=',cm);}
{   readln;}
      if y(cm)*y(r)>=0 then r:=cm else t:=cm;
      inc(ij);
{      writeln('ij=',ij,'  r=',r,'   t=',t);}
   if  abs(abs(t)-abs(r))<ee then break;
   fl:=false;
   if ij=5 then begin tc:=cm; nuton; end;
   if fl=true then begin cm:=ct; break; end;
until 0>1;
{               writeln('y^^=',cm);}
end;


procedure podschet_f;
begin
     f[1]:=y11[2];
     f[2]:=cm;
end;

procedure podchet_k1;
begin
      xx1;
      podschet_f;
      for i:=1 to n do
        begin
            k1[i]:=f[i];
        end;
end;

procedure podchet_k2;
begin
       for i:=1 to n do  y11[i]:=y1[i]+h/2*k1[i];
        x:=x+h/2;
        xx1;
            podschet_f;
      for i:=1 to n do
        begin
            k2[i]:=f[i];
        end;
end;

procedure podchet_k3;
begin
      for i:=1 to n do y11[i]:=y1[i]+h/2*k2[i];
      xx1;
            podschet_f;
      for i:=1 to n do
        begin
            k3[i]:=f[i];
        end;
end;

procedure podchet_k4;
begin
      for i:=1 to n do y11[i]:=y1[i]+h*k3[i];
            x:=x+h/2;
            xx1;
            podschet_f;
      for i:=1 to n do
        begin
            k4[i]:=f[i];
        end;
end;

procedure podschet_y;
begin
      for i:=1 to n do y1[i]:=y0[i];
      for i:=1 to n do y11[i]:=y0[i];
       podchet_k1;
       podchet_k2;
       podchet_k3;
       podchet_k4;
{       writeln('cm=',cm);
       readln;            }
{      for i:=1 to n do begin write (k1[i],' ',k2[i],' ',k3[i],' ',k4[i]); writeln; end;}
      for i:=1 to n do
           y2[i]:=y0[i]+h/6*(k1[i]+2*k2[i]+2*k3[i]+k4[i]);
{      for i:=1 to n do writeln(y0[i],'    ',y1[i],'   ',y2[i] );
      writeln;
      readln;}
end;

procedure y_h;
begin
      j:=1;
      repeat
{          writeln('x = ',x);}
          podschet_y;
          yh2[j]:=y2[1];
          yh3[j]:=y2[n];
{          writeln(w,'yh2[',j,'] = ',yh2[j]);
          writeln(w,'yh3[',j,'] = ',yh3[j]);}
          inc(j);
          for i:=1 to n do y0[i]:=y2[i];
      until x>=a+1-h/4;
{      readln;}
end;

function g(kk:real):real;
begin
      a:=0;
      y0[1]:=0; y0[2]:=kk;
      for i:=1 to n do y3[i]:=y0[i];
      x:=a;
      h:=0.1;
{      writeln('pешение с шагом ',h);}
      y_h;
      repeat
          for i:=1 to j-1 do yh[i]:=yh2[i];
          p:=j-1;
          h:=h/2;
          x:=a;
          for i:=1 to n do y0[i]:=y3[i];
{          writeln('pешение с шагом ',h);}
          y_h;
          i:=0;
          while i<p do
            begin
                inc(i);
                ye[i]:=abs(abs(yh[i])-abs(yh2[2*i]));
{               writeln('ye[',i,'] = ',ye[i]);
                writeln(yh[i],'     ',yh2[2*i]);
                readln;}
            end;
{         readln;}
          zn:=true;
          for i:=1 to p do if ye[i]>15*e then zn:=false;
          if zn=true then break;
      until 1<0;
      g:=y2[1]+1;
      writeln('функция = ',y2[1]+1);
{      readln;}
end;


procedure strelb;
begin
  q:=-1;l:=1;
  c:=0;m:=-1;hh:=1;
 repeat
   if (g(c)*g(m)<=0) then  break;
   if (m+hh)>=l then begin l:=l+1; q:=-l; hh:=1/l; m:=q; c:=m+hh; end
         else begin m:=m+hh; c:=c+hh; end;
  until (0>1);
  writeln('найденный интеpвал:');
  writeln(w,'найденный интеpвал:');
{  readln;}
  rr:=m;tt:=c;
   writeln('a=',rr);
   writeln('b=',tt);
   writeln(w,'a=',rr);
   writeln(w,'b=',tt);
   readln;
   ii:=0;
repeat
   ii:=ii+1;
   c1:=v(rr,tt);
   writeln('k',ii,'=',c1);
   writeln(w,'k',ii,'=',c1);
      if g(c1)*g(rr)>=0 then rr:=c1 else tt:=c1;
   if  abs(abs(tt)-abs(rr))<ee then break;
until 0>1;
               writeln('k=',c1);
               writeln(w,'k=',c1);
               g(c1);
end;

function poisk_i(j:integer):integer;
begin
    for i1:=1 to nn do
    if (x1[j]>=xx[i1-1]) and (x1[j]<=xx[i1]) then poisk_i:=i1;
end;

procedure step;
begin
    writeln('шаги: ');
    for i:=1 to nn do begin h1[i]:=xx[i]-xx[i-1]; write(h1[i]:10:5,'  '); end;
    writeln;
end;

procedure matrisa_c;
begin
    for i:=1 to nn-1 do
         for j:=1 to nn do begin
               if i=j then cc[i,j]:=(h1[i]+h1[i+1])/3;
               if j=i+1 then cc[i,j]:=h1[i+1]/6;
               if j=i-1 then cc[i,j]:=h1[i]/6;
               if abs(i-j)>1 then cc[i,j]:=0;
          end;
    for i:=1 to nn-1 do cc[i,nn]:=(yyy[i+1]-yyy[i])/h1[i+1]-(yyy[i]-yyy[i-1])/h1[i];
end;

procedure atap;
begin
      for i:=j1+1 to nn-1 do begin
        ss:=cc[i,j1]/cc[j1,j1];
      for j:=j1 to nn do
      cc[i,j]:=cc[i,j]-cc[j1,j]*ss; end;
      ss:=0;
end;

procedure perestanovka;
begin
     flag:=true;
     for i:=j1+1 to nn-1 do
       if cc[i,j1]<>0 then begin
            for j:=1 to nn do begin
                  ss:=cc[j1,j]; cc[j1,j]:=cc[i,j]; cc[i,j]:=ss; end;
                  flag:=false; exit; end;
end;

procedure prhod;
begin
      for j1:=1 to nn-1 do begin
      if ss<>0 then j1:=j1-1;
      if cc[j1,j1]<>0 then
      if j1=nn then exit else atap else perestanovka; end;
end;

procedure obrhod;
begin
     mm[0]:=0; mm[nn]:=0;
     mm[nn-1]:=cc[nn-1,nn]/cc[nn-1,nn-1];
     for i:=nn-2 downto 1 do
     begin
     ss:=0;
     for j:=i+1 to nn-1 do
     ss:=ss+cc[i,j]*mm[j];
     mm[i]:=(-ss+cc[i,nn])/cc[i,i];
     end;
end;

function kx(x:real):integer;
begin
     kx:=round(639*(x-xx[0])/(xx[nn]-xx[0]));
end;
function ky(y:real):integer;
begin
     ky:=479-round(479*(y-ymin)/(ymax-ymin));
end;

procedure spline;
begin
   writeln(w,'интеpполиpуем  сплайном:');
   writeln('массивы x и y: ');
   writeln(w,'массивы x и y: ');
    for i:=0 to nn do begin writeln(xx[i],'   ',yyy[i]);
    writeln(w,xx[i],'   ',yyy[i]); end;
    ss:=0;
    step;
    matrisa_c;
    writeln('матрица c  ');
    writeln(w,'матрица c  ');
    for i:=1 to nn-1 do  begin
       for j:=1 to nn do begin
             write(cc[i,j]:10:5);
             write(w,cc[i,j]:10:5); end;
             writeln; writeln(w);
             end;
writeln;
writeln(w);
     prhod;
     for i:=1 to nn-1 do begin for j:=1 to nn do write(cc[i,j]:10:5); writeln; end;
     if flag=true then  writeln('матрица невырожденная')
     else begin obrhod;
     writeln('вывод моментов:  ');
     writeln(w,'вывод моментов:  ');
     for i:=0 to nn do begin write(mm[i]:10:5);write(w,mm[i]:10:5);end;
     end;
     writeln;
     readln;
       writeln('ответ: ');
for j:=1 to kk do begin
       zn_i:=poisk_i(j);
 sp[j]:=mm[zn_i-1]*(xx[zn_i]-x1[j])*(xx[zn_i]-x1[j])*(xx[zn_i]-x1[j])/(6*h1[zn_i])
       +mm[zn_i]*(x1[j]-xx[zn_i-1])*(x1[j]-xx[zn_i-1])*(x1[j]-xx[zn_i-1])/(6*h1[zn_i])
       +(yyy[zn_i-1]-mm[zn_i-1]*sqr(h1[zn_i])/6)*(xx[zn_i]-x1[j])/h1[zn_i]
       +(yyy[zn_i]-mm[zn_i]*sqr(h1[zn_i])/6)*(x1[j]-xx[zn_i-1])/h1[zn_i];
  write(sp[j]:10:5,'   ');
 end;
    readln;

end;

procedure graphik;
begin
 ymin:=yyy[0];  ymax:=yyy[0];
for i:=0 to nn do begin
     if yyy[i]<ymin then ymin:=yyy[i];
     if yyy[i]>ymax then ymax:=yyy[i];
    end;
for i:=1 to kk do begin
     if sp[i]<ymin then ymin:=sp[i];
     if sp[i]>ymax then ymax:=sp[i];
    end;
    writeln('ymin = ',ymin,'   ymax = ',ymax);
    readln;

 gd:=0;
 initgraph(gd,gm,'l:\bgi');
 moveto(kx(xx[0]),ky(yyy[0]));
for i:=1 to kk do     lineto(kx(x1[i]),ky(yh2[i]));
 moveto(kx(x1[1]),ky(sp[1]));
for j:=2 to kk do begin
     lineto(kx(x1[j]),ky(sp[j]));
   end;
 line(kx(0),ky(ymin),kx(0),ky(ymax));
 line(kx(xx[0]),ky(0),kx(xx[nn]),ky(0));
 readln;
 closegraph;
end;

begin
  clrscr;
  assign(w,'rezult.dat');
  rewrite(w);
  writeln(w,'            _________     PЕЗУЛЬТАТЫ     _________');
  writeln(w);
  ee:=0.01;
  writeln(w,'точность  для  МПД:  ',ee);
  writeln(w,'МЕТОД  СТPЕЛЬБ: ');
  strelb;
  writeln(w,'МЕТОД  PУHГЕ-КУТТА  4-ГО  ПОPЯДКА:');
  writeln('шаг = ',h);
  writeln(w,'конечный шаг = ',h);
  readln;
  writeln(w,'нашли у(х) and y^(x):');
  yh2[0]:=y3[1];
  yh3[0]:=y3[n];
  writeln('y(',a,') = ',yh2[0]);
  writeln('y^(',a,') = ',yh3[0]);
  writeln(w,'x=',a,' y=',yh2[0],' y^=',yh3[0]);
  x:=a;
  for i:=1 to 2*p do begin x:=x+h;writeln('yh2[',x,'] = ',yh2[i]);
  writeln('yh3[',x,'] = ',yh3[i]);
  writeln(w,'x=',x,' y=',yh2[i],' y^=',yh3[i]); readln; end;
  readln;
  yyy[0]:=y3[1];
  d:=round(2*p*h/(0.1*2));
  writeln('d = ',d);
  for i:=1 to d do yyy[i]:=yh2[round(0.1*2*i/h)];
  for i:=0 to d do writeln('y[',i,'] = ',yyy[i]);
  readln;
     xx[0]:=0;
   for i:=1 to nn do xx[i]:=xx[i-1]+0.2;
   kk:=0;
   ss:=xx[0]+h;
repeat
    inc(kk);
    x1[kk]:=ss;
    ss:=ss+h;
until ss>=xx[nn];
  writeln(w,'находим  значения  у(х):');
  spline;
 writeln(w);
 for i:=1 to kk do begin
       write(w,'x=',x1[i],'   y=',yh2[i],'    p=',sp[i]);
       writeln(w); end;
  graphik;
x1[1]:=0.12;
for i:=2 to 9 do x1[i]:=x1[i-1]+0.1;
kk:=9;
  yyy[0]:=sqr(y3[1]);
  for i:=1 to d do yyy[i]:=sqr(yh2[round(0.1*2*i/h)]);
  for i:=0 to d do writeln('y[',i,'] = ',yyy[i]);
  readln;
  writeln(w,'находим  величину  мощности:');
  spline;
 writeln(w);
 for i:=1 to kk do begin
       write(w,'x=',x1[i],'      p=',sp[i]);
       writeln(w); end;
  close(w);
end.
