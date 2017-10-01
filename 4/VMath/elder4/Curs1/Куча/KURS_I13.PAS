USES crt,graph;
CONST  EPS=0.1;
       eps1=0.1;
       eps2=0.1;
       eps3=0.1;
       eps4=0.0001;
       Yv0=1;
       Yv1=5;
       a=0;
VAR  tt,kk:integer;
     Xin:array[1..7] of real;
     dy:array[1..7,1..7] of real;
     Y1v0:real;
   {*******************************************************************}
   {*********=- nahodim 2uiu proizvodnuiu metodom Niutona-=************}
   function y2(x,y,y1:real):real;
   var  y2_t:array[1..2] of real;
        delta:real;
        go:integer;
   begin
      y2_t[1]:=x+sin(1.4*y1)+2.3*y;
      go:=0;
      while go=0 do
        if -cos(y2_t[1])*sin(y2_t[1])>0 then  go:=1
           else y2_t[1]:=y2_t[1]+1.57;
      repeat
        y2_t[2]:=y2_t[1]-(y2_t[1]+sin(y2_t[1])-x-sin(1.4*y1)-2.3*y)/(1+cos(y2_t[1]));
        delta:=y2_t[2]-y2_t[1];
        y2_t[1]:=y2_t[2];
      until abs(delta)<eps2;
      y2:=y2_t[2];
   end;
  {**********************=- nahodim y(x) pri dannom y1 -=***************}
   function y(x,yy,y1:real):real;        {procedure RUNGE_KUTTA_4;}
   var   flag,jk,ch,ii:integer;
         k1,k2,k3,k4,y2h,yh:array[1..2,1..2] of real;
         h:real;
   begin
     flag:=0;
     h:=0.01;
     y2h[1,1]:=yy;
     y2h[2,1]:=y1;
     yh[1,1]:=yy;
     yh[2,1]:=y1;
     while  flag<2*(x-a)/h  do
     begin
      for jk:=1 to trunc((x-a)/h) do
      begin
       k1[1,1]:=y1;                               {f(x[i],y[j,i])}
       k1[1,2]:=y2(x,yy,y1);
       k2[1,1]:=y1+k1[1,1]*h/2;                     {f(x[i]+h/2,y[j,i]+k1[j]*h/2)}
       k2[1,2]:=y2(x+h/2,yy,y1)+k1[1,2]*h/2;
       k3[1,1]:=y1+k2[1,1]*h/2;                     {f(x[i]+h/2,y[j,i]+k2[j]*h/2)}
       k3[1,2]:=y2(x+h/2,yy,y1)+k2[1,2]*h/2;
       k4[1,1]:=y1+k3[1,1]*h;                       {f(x[i]+h,y[j,i]+k3[j]*h)}
       k4[1,2]:=y2(x+h,yy,y1)+k2[1,2]*h/2;
       y2h[1,2]:=y2h[1,1]+(k1[1,1]+2*k2[1,1]+2*k3[1,1]+k4[1,1])*h/6;
       y2h[2,2]:=y2h[2,1]+(k1[1,2]+2*k2[1,2]+2*k3[1,2]+k4[1,2])*h/6;
       h:=h/2;
       for ch:=1 to 2 do
       begin
          k1[2,1]:=y1;                            {f(x[i],y[j,i])}
          k1[2,2]:=y2(x,yy,y1);
          k2[2,1]:=y1+k1[2,1]*h*ch/2;                  {f(x[i]+h/2,y[j,i]+k1[j]*h/2)}
          k2[2,2]:=y2(x+h*ch/2,yy,y1)+k1[2,2]*h*ch/2;
          k3[2,1]:=y1+k2[2,1]*h*ch/2;                  {f(x[i]+h/2,y[j,i]+k2[j]*h/2)}
          k3[2,2]:=y2(x+h*ch/2,yy,y1)+k2[2,2]*h*ch/2;
          k4[2,1]:=y1+k3[2,1]*h*ch;                    {f(x[i]+h,y[j,i]+k3[j]*h)}
          k4[2,2]:=y2(x+h*ch,yy,y1)+k2[2,2]*h*ch/2;
          yh[1,2]:=yh[1,1]+(k1[2,1]+2*k2[2,1]+2*k3[2,1]+k4[2,1])*h*ch/6;
          yh[2,2]:=yh[2,1]+(k1[2,2]+2*k2[2,2]+2*k3[2,2]+k4[2,2])*h*ch/6;
       end;
       h:=h*2;
       for  ii:=1 to 2 do
       begin
         if abs(y2h[ii,2]-yh[ii,2])<eps3 then flag:=flag+1;
         y2h[ii,1]:=y2h[ii,2];
         yh[ii,1]:=yh[ii,2];
       end;
      end;
     end;
     y:=yh[2,2]-(y2h[2,2]-yh[2,2])/15;
   end;
 {************************=- ytochniaiem y1(0) -=***************************}
   procedure MPD(aa,hst:real);
   var   ga,gb,gc:real;
   begin
     ga:=aa;
     gb:=aa+hst;
     while abs(ga-gb)>2*eps4 do
     begin
       gc:=(ga+gb)/2;
       if (y(1,Yv0,ga)-Yv1)*(y(1,Yv0,gc)-Yv1)<0 then gb:=gc
          else ga:=gc;
       writeln(' K=',gc:6:6,'.....g(k)=',y(1,Yv0,gc):6:6);
     end;
{!}  Y1v0:=(ga+gb)/2;
   end;
 {*******************=- nahodim y'(0) -=***********************}
   procedure STRELbBA;
   var  k:integer;
        hs,k1:real;
   begin
      k:=-1;
      hs:=1;
      k1:=k;
      while 1=1 do
      begin
        writeln(' K=',k1:6:6,'.....g(k)=',y(1,Yv0,k1):6:6);
        if (y(1,Yv0,k1)-Yv1)*(y(1,Yv0,k1+hs)-Yv1)<0 then
          begin
             writeln(' K=',(k1+hs):6:6,'.....g(k)=',y(1,Yv0,k1+hs):6:6);
             MPD(k1,hs); break;
          end;
        k1:=k1+hs;
        if k1>=abs(k) then
            begin  k:=k*2; hs:=hs/2; k1:=k; end;
      end;
   end;

 {*******************=- nahodim znachenie mosh'nosti -=****************}
   procedure MOSHbNOSTb;
   var  consta,shag:real;
       u:integer;
   begin
     consta:=0.02;
     shag:=0.1;
     for u:=1 to 9 do
       writeln('X=',consta+shag*u:2:2,'   Y2=',sqr(y(consta+shag*u,Yv0,Y1v0)):6:6);
   end;
 {******************=- raznosti -=*******************************}
  procedure  DELbTbI;
  var jj,sr,sl:integer;
  begin
    for jj:=1 to 7 do
       dy[1,jj]:=y(Xin[jj],Yv0,Y1v0);
    for sr:=2 to 7 do
       for sl:=1 to 7-sr do
         dy[sr,sl]:=dy[sr-1,sl+1]-dy[sr-1,sl];
  end;

 {**************=- interpoliaciia po Niutonu  -=*****************}
   function Pn(Xi,Xkoor:real):real ;
   var   ll,fac:integer;
         hin,qq,bb,Pn1:real;
   begin
     fac:=1;
     hin:=0.2;
     qq:=(Xi-Xkoor)/hin;
     bb:=1;
     Pn1:=y(Xkoor,Yv0,Y1v0);
     for ll:=1 to 6 do
     begin
       bb:=bb*(qq-ll+1);
       fac:=fac*ll;
       Pn1:=Pn1+dy[ll+1,1]*bb/fac;
     end;
     Pn:=Pn1;
   end;
 {**************=- risuem graphik -=*************}
 procedure GRAPHIK;
 var koef,n_toch,gd,gm,xsm,ysm,zz,hh,rr,oo:integer;
     xk,yk:real;
 begin
   koef:=10000;
   n_toch:=100;
   gd:=0;
   initgraph(gd,gm,'c:\tp\bgi');
   xsm:=20;
   ysm:=20;
   {--------oci--------}
   setcolor(7);
   line(trunc(xsm*0.5),getmaxy-ysm,getmaxx-2*xsm,getmaxy-ysm);
   line(xsm,getmaxy-trunc(ysm*0.5),xsm,ysm*2);
   {-------graphik y(x)------}
   setcolor(14);
   moveto(xsm,getmaxy-ysm);
   for zz:=1 to n_toch do
   begin
      xk:=(getmaxx-3*xsm)/n_toch*zz;
      yk:=getmaxy-y(xk,Yv0,Y1v0)*koef;
      lineto(xsm+trunc(xk*koef),trunc(yk-ysm));
   end;
   {-------tochki-------------}
   setcolor(5);
   for hh:=1 to 7 do
     circle(trunc((hh-1)*n_toch*koef/6),trunc(getmaxy-y((hh-1)*n_toch*koef/6,Yv0,Y1v0)*koef),5);
   {-------graphik Pn(x)------}
   setcolor(12);
   moveto(xsm,getmaxy-ysm);
   for oo:=1 to 6  do
     for rr:=1 to trunc(n_toch/6) do
     begin
        xk:=(getmaxx-3*xsm)/n_toch*rr;
        yk:=getmaxy-Pn(rr/n_toch,Xin[oo]);
        lineto(trunc(xsm+xk*koef),trunc(yk*koef-ysm));
     end;
   closegraph;
 end;
BEGIN
  writeln('**********=-PODBIRAEM ZNACHENIE K -=**********');
  STRELbBA;
  writeln('**********=- ZNACHENIE MOSHbNOSTI -=**********');
  MOSHbNOSTb;
  writeln('******=- ZNACHENIE INTERPOLICIONNOGO MNOGOCHLENA -=******');
  for kk:=1 to 7 do
     Xin[kk]:=(kk-1)/0.2;
  DELbTbI;
  for tt:=1 to 6 do
     writeln('  X=',Xin[tt]:2:2,'.......Pn(x)=',Pn(Xin[tt],Xin[tt]):6:6);
  readkey;
{  GRAPHIK;}
END.
