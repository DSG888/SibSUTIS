#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<string.h>

#define HordA -10
#define Hstep 0.5
#define h 0.1

#define Npoints        11
#define NsplinePoints  Npoints/2+1
#define E              0.0001
#define VectSize       2
#define Target         0.5

#define MaxYvalue 1.5


float  LeftPointVect[VectSize]={1,0}, LeftPointX=0,
       k, Y[Npoints], SumStorage[VectSize], Ystorage[VectSize],
       Fstorage[VectSize], K1st[VectSize], K2st[VectSize],
       K3st[VectSize], K4st[VectSize], StepResStorage[VectSize],
       PassageResultStorage[VectSize],

       x[NsplinePoints], y[NsplinePoints], hspl[NsplinePoints-1], CMd[NsplinePoints-2][NsplinePoints-1], M[NsplinePoints],

       Xo=LeftPointX, Xn=LeftPointX+(Npoints-1)*h;

float NU(float x);
void HordNU();
float NUHD(float x, float *Y, float yHiDif);
float HordNUHD(float x, float *Y);
float *F(float x, float *Y);
float *sum(float c1, float *V1, float c2, float *V2);
float *RK4(float x, float *Y, float H);
float RKpass(float d1y0);
float *RKstep(float x, float *Y);
float approx(float start, float step);
void ShootEmAll();

void formVectsForSpline();
void matrix();
void findM();
float interpol(float arg);
void GraphInit();
void graphic();

float function(float argument);
float Integral();
float SumY1(float H);
float SumY2(float H);




/******BbI4ucJI9Iem 3Ha4eHue HY**************************************/

float NU(float x)
{
 return pow(x,5)-3*x-1;
}

/******BbI4ucJI9Iem kopeHb HY MemogoM xopg***************************/

void HordNU()
{
 int i;
 float a=HordA , b=(HordA+Hstep) , apr1 , apr2;

 while( NU(a)*NU(b) > 0 )
 {
  a=a+Hstep;
  b=b+Hstep;
 }

 do
 {

  apr1=( ( NU(b)*a-NU(a)*b ) / ( NU(b)-NU(a) ) );

  if( NU(a)*NU(apr1) > 0 )	 a=apr1;	else	b=apr1;

  apr2=( (NU(b)*a-NU(a)*b) / (NU(b)-NU(a)) );

  if( NU(a)*NU(apr2) > 0 )       a=apr2;	else	b=apr2;

 } while( (fabs(apr2-apr1)) > E );

 k=apr2;
}

/*****BbI4ucJI9Iem 3Ha4eHue DY om cmapweu npou3BogHou****************/

float NUHD(float x, float *Y, float yHiDif)
{
 return ( Y[1]-(x*x+k*Y[0])-yHiDif+sin(yHiDif) /*x*yHiDif+pow(x,2)*Y[0]-Y[1]+Y[2]*/ );
}

/****Pewaem DY omHocumeJIbHo cmapweu npou3BogHou*********************/

float HordNUHD(float x, float *Y)
{
 int i;
 float a=HordA , b=10 , apr1 , apr2;


 do
 {

  apr1=( ( NUHD(x,Y,b) * a - NUHD(x,Y,a) *b ) / ( NUHD(x,Y,b) - NUHD(x,Y,a) ) );

  if( NUHD(x,Y,a) * NUHD(x,Y,apr1) > 0 )	 a=apr1;	else	b=apr1;

  apr2=( (NUHD(x,Y,b) * a-NUHD(x,Y,a)*b) / (NUHD(x,Y,b) - NUHD(x,Y,a) ) );

  if( NUHD(x,Y,a) * NUHD(x,Y,apr2) > 0 )       a=apr2;	else	b=apr2;

 } while( (fabs(apr2-apr1)) > E );

 return apr2;
}

/******(I)opMupyem Bekmop npou3BogHbIx*******************************/

float *F(float x, float *Y)
{
 int i;
 float *F;

 for(i=0; i<VectSize-1; i++) Fstorage[i]=Y[i+1];

 Fstorage[VectSize-1]=HordNUHD(x, Y);

 F=Fstorage;

 return F;
}

/******CyMMupyem Bekmopa, goMHo)I(eHHbIe Ha ko-)(I)(I)uu,eHmbI*******/

float *sum(float c1, float *V1, float c2, float *V2)
{
 int i;
 float *sum;

 for(i=0; i<VectSize; i++)
 {
 SumStorage[i]=(*(V1+i))*c1+(*(V2+i))*c2;
 }

 sum=SumStorage;

 return sum;
}

/*******War MemogoM PyHre-Kymma 4 nop9Igka***************************/

float *RK4(float x, float *Y, float H)
{
 int i;
 float *Yp, *K1, *K2, *K3, *K4;

 K1=F(x, Y);
 for(i=0; i<VectSize; i++) K1st[i]=K1[i];

 K2=F(x+H/2, sum(1,Y,H/2,K1) );
 for(i=0; i<VectSize; i++) K2st[i]=K2[i];

 K3=F(x+H/2, sum(1,Y,H/2,K2) );
 for(i=0; i<VectSize; i++) K3st[i]=K3[i];

 K4=F(x+H  , sum(1,Y,H,  K3) );
 for(i=0; i<VectSize; i++) K4st[i]=K4[i];

 Yp=sum(1,Y,H/6, sum(1, sum(1,K1st,2,K2st), 1, sum(2,K3st,1,K4st) ) );

 for(i=0; i<VectSize; i++) Ystorage[i]=Yp[i];

 Yp=Ystorage;

 return Yp;
}

/*****IIpoxog no Memogy PK om JIeBou mo4ku k npaBou******************/

float RKpass(float d1y0)
{
  int i, j;
  float *Ytmp, PrevVect[VectSize],  x, rightY;

  for(i=0; i<VectSize; i++) PrevVect[i]=LeftPointVect[i];

  PrevVect[1]=d1y0;

  Ytmp=PrevVect;

  x=LeftPointX;

 for(i=0; i<=Npoints; i++)
 {
 Y[i]=Ytmp[0];
 Ytmp=RKstep(x,PrevVect);
 for(j=0; j<VectSize; j++) PrevVect[j]=Ytmp[j];
 x+=h;
 }

 rightY=Y[Npoints-1];

 return(rightY);
}

/*****War PyHre-KymmoM c gBouHbIM nepec4emoM*************************/

float *RKstep(float x, float *Y)
{
 int n, i;
 float *RK, *RKprev, RK2H[VectSize], H;

 n=1;
 H=h;

 RK=RK4(x, Y, H);
 do
 {
  H/=2;
  n*=2;

  for(i=0; i<VectSize; i++) RK2H[i]=RK[i];

  RKprev=Y;



  for(i=0; i<n; i++)
  {
  RK=RK4(x, RKprev, H);
  RKprev=RK;
  }




 } while( fabs(RK[0]-RK2H[0]) > 15*E );

 for(i=0; i<VectSize; i++) StepResStorage[i]=RK[i];

 RK=StepResStorage;

 return (RK);
}

/**Haxo)I(geHue uHmepBaJIa 3agaHHou wupuHbI, BkJIIO4aIOwero**********/
/**uckoMoe 3Ha4eHue nepBou npou3BogHou B JIeBou mo4ke****************/

float approx(float start, float step)
{
 float lValue=start, lV, lVs, lVval, lVsval;



 while( !( ((lVsval=RKpass(lVs=lValue+step)) > Target) && ((lVval=RKpass(lV=lValue)) < Target) ) )
 {
 if( (RKpass(lValue) > Target) && (RKpass(lValue+step) > Target) )
 lValue-=step;

 else
 lValue+=step;
 }

 if(fabs(lVsval-Target) < fabs(lVval-Target)) return lVs;
 else return lV;

}

/*********Memog CmpeJIbI6********************************************/

void ShootEmAll()
{
 float start=-2, step=1;


 do

 {
  start=approx(start, step);
  step/=2;
 } while (fabs(Y[Npoints-1]-Target) > E);
}

/********************************************************************/
/*******(I)yHku,uu kyI6u4eckoro cnJIauHa*****************************/
/********************************************************************/

void formVectsForSpline()
{
 int i;

 for(i=0; i<NsplinePoints; i++) x[i]=LeftPointX+i*2*h;
 for(i=0; i<NsplinePoints; i++) y[i]=Y[i*2];
 for(i=0; i<NsplinePoints; i++) hspl[i]=h*2;

}

/******UHuu,uaJIu3au,u9I rpa(I)u4eckoro pe)I(uMa*********************/

void GraphInit()
{
 int grd=DETECT,grm;
 initgraph(&grd,&grm,"");
}

/*******(I)opMupoBaHue Mampuu,bI CMD*********************************/

void matrix()
{
 int i,j;
 float C[NsplinePoints-2][NsplinePoints-2], d[NsplinePoints-2];

 for(i=0;i<NsplinePoints-2;i++)
 {
   d[i]=(y[i+2]-y[i+1])/hspl[i+1]-(y[i+1]-y[i])/hspl[i];
 }

 for(i=0;i<NsplinePoints-2;i++)
 {
   for(j=0;j<NsplinePoints-2;j++)
   {
    if(i==j)        C[i][j]=(hspl[i]+hspl[i+1])/3;
    if(j==(i+1))    C[i][j]=hspl[i+1]/6;
    if(j==(i-1))    C[i][j]=hspl[i]/6;
    if(fabs(i-j)>1) C[i][j]=0;
   }
 }

 for(i=0;i<NsplinePoints-2;i++)
 {
   for(j=0;j<NsplinePoints-1;j++)
   {
    if(j<NsplinePoints-2)  CMd[i][j]=C[i][j];
    if(j==NsplinePoints-2) CMd[i][j]=d[i];
   }
 }

}

/*****Haxo)I(geHue M MemogoM I'aycca*********************************/

void findM(void)
{
 int i,j,k,nmax;
 float t;

 for(k=0;k<NsplinePoints-3;k++)

  for(i=k+1;i<NsplinePoints-2;i++)
  {
   t=(CMd[i][k]/CMd[k][k]);

   for(j=0;j<NsplinePoints-1;j++)    CMd[i][j]=CMd[i][j]-CMd[k][j]*t;
  }

  for(k=0;k<NsplinePoints;k++)   M[k]=0;

  for(i=NsplinePoints-3;i>=0;i--)
  {
   for(t=0,j=0;j<NsplinePoints-2;j++)
   t=t+M[j+1]*CMd[i][j];

   M[i+1]=(CMd[i][NsplinePoints-2]-t)/CMd[i][i];
  }
}

/*******UHmepnoJIupoBaHue********************************************/

float interpol(float arg)
{
 int i;
 float approx;

 for(i=1;i<NsplinePoints;i++)
 if(arg<x[i] & arg>x[i-1]) break;

 approx=M[i-1]*pow((x[i]-arg),3)/(6*hspl[i-1])+M[i]*pow((arg-x[i-1]),3)/(6*hspl[i-1])+(y[i-1]-(M[i-1]*pow(hspl[i-1],2)/6))*(x[i]-arg)/hspl[i-1]+(y[i]-(M[i]*pow(hspl[i-1],2)/6))*(arg-x[i-1])/hspl[i-1];

 for(i=0;i<NsplinePoints;i++)
 if(arg==x[i]) approx=y[i];

 return approx;
}

/********IIocmpoeHue I'pa(I)uka**************************************/
void graphic()
{
 float  war, MacwmaI6, warPa3Memku=0.2;
 int i, n,
     Pa3Memka=3, maxx=getmaxx(), maxy=getmaxy();


 char far *text, *buf;

 struct {int x,y;} O, CP;

 CP.x=O.x=40;
 CP.y=O.y=maxy-30;

 MacwmaI6=O.y/MaxYvalue;
 war=warPa3Memku*MacwmaI6;

 line(O.x,0,  O.x,maxy);
 line(0,O.y,  maxx,O.y);

 moveto(O.x, 0);
 linerel(-3, 6);
 moveto(O.x, 0);
 linerel( 3, 6);

 moveto(maxx, O.y);
 linerel(-6, -3);
 moveto(maxx, O.y);
 linerel(-6,  3);

 n=(maxx-O.x)/(war);

 for(i=0; i<n; i++)
 {
  CP.x=O.x+i*war;
  moveto(CP.x, CP.y-Pa3Memka);
  linerel(0, 2*Pa3Memka);
  text=gcvt(i*warPa3Memku, 3, buf);
  moveto(CP.x-textwidth(text), CP.y+textheight(text));
  outtext(text);
 }

 CP.x=O.x;
 CP.y=O.y;

 n=(O.y)/(war);

 for(i=1; i<=n; i++)
 {
  CP.y=O.y-i*war;
  moveto(CP.x+Pa3Memka, CP.y);
  linerel(-2*Pa3Memka, 0);
  text=gcvt(i*warPa3Memku, 2, buf);
  moveto(CP.x-textwidth(text), CP.y+textheight(text));
  outtext(text);
 }

 text="x";
 moveto(maxx-textwidth(text), O.y+2*textheight(text));
 outtext(text);

 text="y";
 moveto(O.x-4*textwidth(text), 0+textheight(text));
 outtext(text);

 for(i=0; i<(int)MacwmaI6; i++)
 putpixel(O.x+i+MacwmaI6*LeftPointX, O.y-MacwmaI6*interpol((LeftPointX*MacwmaI6+i)/MacwmaI6), 9);


}
/**************************************************/
/******(I)yHku,uu uHmerpupoBaHu9I******************/
/**************************************************/

float function(float argument)
{
 return pow(interpol(argument), 2);
}

/*BbI4ucJIeHue uHmerpaJIa no oI6weu (I)opMyJIe CuMncoHa*/

float Integral()
{
 float I, Iprev, H=0.01;

 I=(H/3) * ( (function(Xo)+function(Xn) ) + 4*SumY1(H)+2*SumY2(H) );

 do
 {
 Iprev=I;

 H/=2;

 I=(H/3) * ( (function(Xo)+function(Xn) ) + 4*SumY1(H)+2*SumY2(H) );


 } while(fabs(I-Iprev)>3*E);

 return(I);

}

/*BbI4ucJIeHue cyMMbI 3Ha4eHuu (I)yHku,uu B mo4kax******/
/*c He4emHbIMu HoMepaMu*********************************/

float SumY1(float H)
{
 int i, n, k;
 float Sapr=0, x;

 n=((Xn-Xo+0.000001)/H)+1;
 k=n/2;
 x=Xo;

 for(i=1; i<=k; i++) Sapr+=function(x+(2*i-1)*H);

 return(Sapr);
}

/*-/- c 4emHbIMu************************************/

float SumY2(float H)
{
 int i, n, k;
 float Sapr=0, x;

 n=((Xn-Xo+0.000001)/H)+1;
 k=n/2;
 x=Xo;

 for(i=1; i<=k; i++) Sapr+=function(x+(2*i)*H);

 return(Sapr);
}



/********************************************************************/



int main()
{
 int i;
 char *k;

 clrscr();

 HordNU();
 ShootEmAll();

 formVectsForSpline();

 matrix();
 findM();

 for(i=0;i<Npoints; i++)
 {
  printf("In x = %2.1f: Interpolated: %f\t",LeftPointX+i*h, interpol(LeftPointX+i*h));
  printf("Found by RK: %f\n", Y[i]);
 }

 getch();

 GraphInit();

 graphic();

 getch();
 closegraph();

 printf("Value of heat is %f", Integral());

 getch();

 return 0;
}
