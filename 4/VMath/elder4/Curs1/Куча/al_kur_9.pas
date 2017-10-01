Uses  crt,graph;
Const eps=0.001;
	  Int=1;
	  x0=0;{y(0)=1}
	  y0=1;
	  X_Newton:array[0..5] of real=(0,0.2,0.4,0.6,0.8,1);
      X_Power :array[1..9] of real=
			(0.12, 0.22, 0.32, 0.42, 0.52, 0.62, 0.72, 0.82, 0.92);
Type  mass=array[1..4] of real;
Var   K,L:mass;
	  delta:array[1..5] of real;
          Y_m:array[1..5] of real;
          X_delta:array[1..5] of real;
	  del1,del2,del3,del4,del5:array[0..4] of real;
	  Y_Newton:array[0..5] of real;
	  h,hh,sum,h_eps,a,b,aa,bb,kk,k1,m,x,y,y1,y_rez,yy_rez,g_rez,mm,maxx:real;
	  i,j,jj,ii,iii,n,nn,n1:integer;
	  yy,yy1,yy2,yyy,raz:array [1..400] of real;
Function Fun(x,y,y1,y2:real):real;
  begin
	fun:=y2+4*y1+1/(16+y2*y2)-10*exp(-x);
  end;
Function MPD(a,b,x,y,y1:real):real;
  var c,a1,b1:real;
  begin
	a1:=a;
	b1:=b;
	  repeat
	  c:=(a1+b1)/2;
	  if (fun(x,y,y1,c)*fun(x,y,y1,b))<0 then
			 a1:=c
		 else b1:=c;
		until (b1-a1)/2 < eps;
	MPD:=c;
  end;
Procedure Interval(x,y,y1:real);
  begin
	hh:=0.3;
	a:=-hh;
	b:=hh;
	Repeat
	  a:=2*a;
	  b:=b*2;
	Until Fun(x,y,y1,a)*Fun(x,y,y1,b)<0;
  end;
Procedure Runge_Cutt(h,x,y,g:real);
  begin
	K[1]:=g;
	Interval(x,y,g);
	L[1]:=MPD(a,b,x,y,g);
	K[2]:=g+L[1]*h/2;
	Interval(x+h/2,y+K[1]*h/2,g+L[1]*h/2);
	L[2]:=MPD(a,b,x+h/2,y+K[1]*h/2,g+L[1]*h/2);
	K[3]:=g+L[2]*h/2;
	Interval(x+h/2,y+K[2]*h/2,g+L[2]*h/2);
	L[3]:=MPD(a,b,x+h/2,y+K[2]*h/2,g+L[2]*h/2);
	K[4]:=g+L[3]*h;
	Interval(x+h,y+K[3]*h,g+L[3]*h);
	L[4]:=MPD(a,b,x+h,y+K[3]*h,g+L[3]*h);
	y_rez:=y+h/6*(K[1]+2*K[2]+2*K[3]+K[4]);
	g_rez:=g+h/6*(L[1]+2*L[2]+2*L[3]+L[4]);
  end;
Procedure Collection(h1,k1:real);
   begin
	  x:=x0; y:=y0; y1:=k1;
	  for j:=1 to round(Int/h1) do
		begin
		  Runge_cutt(h1,x,y,y1);
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
	 for ii:=1 to n1 do raz[ii]:=abs(yy1[ii]-yy2[2*ii]);
	 maxx:=0;
	 for ii:=1 to n1 do if  maxx<raz[ii] then maxx:=raz[ii];
	 max:=maxx;
   end;
Function pereschet(kk:real):real;
   begin
	  h_eps:=0.05;
        {  h_eps:=0.2;}
	  collection(h_eps,kk);
		for i:=1 to round(Int/h_eps) do
		  yy2[i]:=yy[i];
	repeat
		for i:=1 to round(Int/h_eps) do
			   yy1[i]:=yy2[i];
		h_eps:=h_eps/2;
		collection(h_eps,kk);
			for ii:=1 to round(Int/h_eps) do
			   yy2[ii]:=yy[ii];
			maxx:=max;
	until maxx < 15*eps;
	  yy_rez:=yy2[round(Int/h_eps)]+1/15*(yy2[round(Int/h_eps)]-yy1[round(Int/h_eps/2)]);
	  pereschet:=yy_rez-2;
  end;
Function MPD_str(a,b:real):real;
  var c,a1,b1:real;
	i,n:integer;
  begin
	a1:=a;
	b1:=b;
	n:=round(ln((b1-a1)/eps)/Ln(2));
	For i:=1 to n do
	  begin
		c:=(a1+b1)/2;
		if ((pereschet(a1))*(pereschet(c)))<0 then b1:=c
		  else a1:=c;
	  end;
	MPD_str:=c;
  end;
Function Strelb:real;
  begin
	aa:=-0.05;
	bb:=-aa;
	h:=0.1;
	repeat
	  aa:=aa*2;
	  bb:=-aa;
	Until pereschet(aa)*pereschet(bb)<0;
	Strelb:=MPD_str(aa,bb);
  end;
procedure Make_Y_Newton;
   begin
	  Y_Newton[0]:=1;
	  for i:=1 to 5 do
		 begin
		   j:=round(X_newton[i]/h_eps);
		   Y_Newton[i]:=yy2[j];
		 end;
   end;
Function Fact(n1:integer):integer;
   var f,i:integer;
   begin
	 f:=1;
	 for i:=1 to n1 do f:=f*i;
	 Fact:=f;
   end;
Procedure Make_delta;
   begin
	 for i:=0 to 4 do del1[i]:=Y_Newton[i+1]-Y_Newton[i];
	 delta[1]:=del1[0];
	 for i:=0 to 3 do del2[i]:=del1[i+1]-del1[i];
	 delta[2]:=del2[0];
	 for i:=0 to 2 do del3[i]:=del2[i+1]-del2[i];
	 delta[3]:=del3[0];
	 for i:=0 to 1 do del4[i]:=del3[i+1]-del3[i];
	 delta[4]:=del4[0];
	 for i:=0 to 0 do del5[i]:=del4[i+1]-del4[i];
	 delta[5]:=del5[0];
   end;
Function Newton(x:real):real;
var qtmp,q,sum:real;
	begin
		sum:=Y_Newton[0];
		q:=(x-X_Newton[0])/0.2;
		qtmp:=q;
		for i:=1 to 5 do
			begin
				sum:=sum+(delta[i]*qtmp)/Fact(i);
				qtmp:=qtmp*(q-i);
			end;
		Newton:=sum;
	end;

procedure Power;
var j:integer;
   begin
	  writeln;
	  for j:=1 to 9 do
		 begin
			writeln('x= ',X_power[j]:3:2,' мощность(интеpп.)= ',sqr(Newton(X_power[j])):8:6);
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

procedure Uzli;
begin
 for j:=1 to 5 do
  X_delta[j]:=X_Newton[j]+ h_eps;
 for i:=1 to  5 do
        begin
          j:=round(X_Newton[i]/h_eps);
		   Y_m[i]:=yy2[j+1];
        end;
 for j:=1 to 5 do
        begin
	writeln('x= ',X_Delta[j]:3:2,' Знач. интеpп.многочл.= ',Newton(X_Delta[j]):8:6);
        writeln('x= ',X_Delta[j]:3:2,' Знач. функции = ',Y_m[j]:8:6);
	end;
end;

Begin

  clrscr;
  kk:=strelb;
  writeln('K = ',kk:8:6);
  writeln('y(1) = ',yy2[round(Int/h_eps)]:8:6);
  Make_Y_Newton;
  Make_delta;
  Power;
  readln;
  Uzli;
  readln;
  graphic;
  readln;
  closegraph;
end.