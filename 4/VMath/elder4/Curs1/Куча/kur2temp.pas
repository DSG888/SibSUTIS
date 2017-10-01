uses crt,graph;

type	vector	= array[0..1] of real;
const	e	= 1e-4;
	masx	: array[1..9] of real=(0,0.12,0.32,0.42,0.52,0.62,0.72,0.82,0.92);
        h:real=0.5;

var	masy		: array[1..9] of real;
	x		: real;
	a,b		: real;
	ynach		: vector;
	mas1y,mas1x	: array[1..6] of real;
	k		: real;
	i,j		: integer;
	yr		: vector;
	maxy,miny	: real;
	gm,gd           : integer;


function FunF(yp2,yp1,y,x:real):real;{Возвращает значение F(x,y,y',y'') }
begin
	FunF := yp2 + cos(yp2 + 1) + 2 * y - sin(2 * x) + yp1;
end;


procedure funY2(x:real;y1:vector;var fxy:vector);
{Возвращает значение y'' в точке (x,y,y')}
var
	y,y2	: real;
	a,b,h,c: real;
left_lim, right_lim,  c2: real;
            lef,rig:real;
begin
	a:=-2;
	b:=2;
	h:=1.1;
	y:=a-h;
	{Поиск интервала где функция меняет знак}
	left_lim := -5;
	right_lim := 5;
	{поиск интервала}
{поиск интервала}
	while (true) do
	begin
		{|  если ф-ция менят знак на интервалe    |}
		{|  (left_lim;right_lim) - обрываем цикл  |}
		lef:=FunF(left_lim,y1[1],y1[0],x);
		rig:=FunF(right_lim,y1[1],y1[0],x);
		if lef * rig < 0 then break;
		left_lim := right_lim;
		right_lim := right_lim + 1;
	end;
	{конец поиска интервала}
	{конец поиска интервала}
	repeat
		C := (FunF(right_lim,y1[1],y1[0],x)*left_lim - FunF(left_lim,y1[1],y1[0],x)*right_lim) /
			(FunF(right_lim,y1[1],y1[0],x) - FunF(left_lim,y1[1],y1[0],x));
		if (FunF(left_lim,y1[1],y1[0],x)*FunF(C,y1[1],y1[0],x) > 0)
		then left_lim := C
		else right_lim := C;
		C2 := (FunF(right_lim,y1[1],y1[0],x)*left_lim - FunF(left_lim,y1[1],y1[0],x)*right_lim) /
			(FunF(right_lim,y1[1],y1[0],x) - FunF(left_lim,y1[1],y1[0],x));
	until (abs(C2 - C) < 1e-4);
	fxy[0]:=y1[1];
	fxy[1]:=c;
end;


procedure kengurutta(x:real;y:vector;h:real;var rez_vectorY:vector);
var	k1,k2,k3,k4	: vector;
	k		: vector;
begin
	funY2(x,y,k1);
	k[0]:=y[0]+(h/2)*k1[0];
	k[1]:=y[1]+(h/2)*k1[1];
	funY2(x+h/2,k,k2);
	k[0]:=y[0]+(h/2)*k2[0];
	k[1]:=y[1]+(h/2)*k2[1];
	funY2(x+h/2,k,k3);
	k[0]:=y[0]+(h)*k3[0];
	k[1]:=y[1]+(h)*k3[1];
	funY2(x+h,k,k4);
	rez_vectorY[0]:=y[0]+(h/6)*(k1[0]+2*k2[0]+2*k3[0]+k4[0]);
	rez_vectorY[1]:=y[1]+(h/6)*(k1[1]+2*k2[1]+2*k3[1]+k4[1]);
end;


procedure two_peres(x0,xn:real;yn:vector;var rez_vectorY:vector);
var	x	: real;
	kp	: boolean;
	y,y1,y2: vector;
begin
	h:=h*2;
	repeat
		y[0]:=yn[0];
		y[1]:=yn[1];
		kp:=true;
		x:=x0;

		while (x<=xn) do
		begin
			kengurutta(x,y ,h  ,y1);
			kengurutta(x,y ,h/2,y2);
			kengurutta(x,y2,h/2,y2);
			if(abs(y1[0]-y2[0])>e) then kp:=false;
			y[0]:=y1[0];
			y[1]:=y1[1];
			x:=x+h;
		end;

		h:=h/2;
	until kp;
	rez_vectorY[0]:=y2[0];
	rez_vectorY[1]:=y2[1];
end;


function FunK(y:vector):real;
var	k		: real;
	yk,yr,yr1	: vector;
	a,b,c,h	: real;
begin
	a:=-4;
	b:=4;
	h:=1;
	k:=a-h;
	yk[0]:=y[0];
	yk[1]:=a;
	two_peres(0,1,yk,yr);
	writeln('k':9,'y':10,'интервал для k':19);
	writeln(k:5:7,yr[0]:12:7,'  [',a:2:2,'; ',b:2:2,']');

	repeat
		yr1[0]:=yr[0];
		yr1[1]:=yr[1];
		k:=k+h;

		if(k>b) then
		begin
			a:=a*2;
			b:=b*2;
			h:=h/2;
			k:=a;
		end;
		yk[1]:=k;
		two_peres(0,1,yk,yr);
		writeln(k:5:7,yr[0]:12:7,'  [',k-h:2:2,';',k:2:2,']');
	until ((yr[0]-y[1])*(yr1[0]-y[1])<0) ;
	writeln;

	{Ищем интервал, где ответ перешел через y[1]}
	writeln('интервал найден - запускаем МПД');
	{MPD}
	a:=k-h;
	b:=k;


	repeat     {MPD}

                c:=(b+a)/2;
                yk[1]:=a;
		two_peres(0,1,yk,yr);
		yk[1]:=c;

		two_peres(0,1,yk,yr1);
		if (yr[0]-y[1])*(yr1[0]-y[1])<0
		then b:=c
		else a:=c;
                writeln(' k=',c:5:7,'  y=',yr1[0]:5:7);
	until abs(a-b)<e;

	FunK:=(a+b)/2;{Параметр K}
end;


const 	n	= 6;
var	c	: array[1..n,1..n] of real;
	d,m	: array[1..n] of real;


procedure cmatrix;{for spline}
var	i,j,k	: integer;
	h,del	: real;
begin
	h:=0.2;
	for i:=2 to n-1 do
		for j:=2 to n-1 do
		begin
			if(i=j)		then c[i,j]:=(h+h)/3;
			if(j=i+1)		then c[i,j]:=h/6;
			if(j=i-1)		then c[i,j]:=h/6;
			if(abs(i-j)>1)	then c[i,j]:=0;
		end;

	for i:=2 to n-1 do d[i]:=(mas1y[i+1]-mas1y[i])/h-(mas1y[i]-mas1y[i-1])/h;

	for k:=2 to n-1 do 
	begin
		for i:=k+1 to n-1 do 
		begin
			del:=c[i,k]/c[k,k];
			for j:=k to n-1 do c[i,j]:=c[i,j]-c[k,j]*del;
			d[i]:=d[i]-d[k]*del;
		end;
	end;

	for i:=1 to n-1 do m[i]:=0;

	for i:=n-1 downto 2 do  
	begin
		m[i]:=c[i,i];
		for j:=i+1 to n-1 do m[i]:=m[i]+c[i,j]*m[j];
		m[i]:=(d[i]/m[i]);
	end;
end;


function spline(x:real):real;
var	i	: integer;
	si	: real;
begin
	i := trunc(x/0.2)+2;
	si := 0;
	if i = 7 then i := 6;
	si :=m[i-1] * (mas1x[i] - x) * (mas1x[i] - x) * (mas1x[i] - x) / (6 * 0.2);
	si := si + m[i] * (x - mas1x[i-1]) * (x - mas1x[i-1]) * (x - mas1x[i-1]) / (6 * 0.2);
	si := si + (mas1y[i-1] - (m[i-1] * (0.04 / 6))) * (mas1x[i] - x) / 0.2;
	si := si + (mas1y[i] - m[i] * (0.04 / 6)) * (x - mas1x[i-1]) / 0.2;
	spline:=si;
end;


procedure MaxAndMinY;
var	x : real;
	i : integer;
begin
	miny := 0;
	maxY := 0;
	x    := 0;
	while x <= 1 do
	begin
		if spline(x) < minY then minY := spline(x);
		if spline(x) > maxY then maxY := spline(x);
		x := x + 0.1;
	end;

	for i := 1 to 8 do
	begin
		if masy[i] < minY then minY := masy[i];
		if masy[i] > maxY then maxY := masy[i];
	end;
end;


function kx(x : real):integer;
begin
	kx := round(639 * x);
end;


function ky(y : real):integer;
begin
	ky := round(479 * (maxy - y) / (maxy - miny));
end;




{===================main=begin======================}
BEGIN
	clrscr;
	ynach[0] := 0;
	ynach[1] := -1;
	k := FunK(ynach);
	ynach[1] := k;
	writeln('K = ',k:5:4);
	writeln('press..');
	readln;

	clrscr;
	for i := 1 to 9 do
	begin
		two_peres(0,masx[i],ynach,yr);
		masy[i] := yr[0];
		writeln('  P(',masx[i]:5:2,') =  ',masy[i]*masy[i]:5:2);
	end;

	writeln('press..');
	readln;

	x := 0;
	for i := 1 to n do
	begin
		two_peres(0,x,ynach,yr);
		mas1x[i] := x;
		mas1y[i] := yr[0];
		x := x + 0.2;
	end;

	cmatrix;
	clrscr;
	x := 0;

	repeat
		two_peres(0,x,ynach,yr);
		writeln('   y(x) = ',yr[0]:5:4,'   S(x) = ',spline(x):5:4,'  x =',x:2:2);
		x := x + 0.05;
	until x > 1.1;

	writeln('press..');
	readln;

	gm := detect;
	initgraph(gd,gm,'l:\bgi');
	line( 10,155,620,155);
	line( 152,10,152,400);
	outtextXY( 610,141,'x');
	outtextxy( 160,10,'y');
	MaxAndMinY;
	setcolor(white);

	for i := 1 to 9 do
		outtextxy(150 + kx(0.5 * masx[i]), 150 + ky(0.5 * masy[i]), 'x');

	setcolor(RED);
	x :=  0;
	moveto(120 + kx(0.5 * x),100 + ky(0.5 * spline(x)));

	repeat
		lineto(150 + kx(0.5 * x), 150 + ky(0.5 * spline(x)));
		x := x + 0.002;
	until x > 1;

	repeat until keypressed;
	closegraph;
end.