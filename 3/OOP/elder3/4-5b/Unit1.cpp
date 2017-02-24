//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include <time.h>
#include "Unit1.h"


#include <math.h>


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

#include<stdlib.h>

#define x_max (Form1->Image1->Width)
#define y_max (Form1->Image1->Height)
#define imj Form1->Image1


geom_f::geom_f()
{

 ygol=0;

}


void geom_f::vrash_cord(float tt,int xx,int yy)
        {
                XFORM xform;
                float angle=tt;
                angle = angle * 3.1416 / 180.0;
                xform.eDx = 0.0f;
                xform.eDy = 0.0f;
                xform.eM11 = cos(angle);
                xform.eM12 = sin(angle);
                xform.eM21 = -sin(angle);
                xform.eM22 = cos(angle);
                SetGraphicsMode(imj->Canvas->Handle, GM_ADVANCED);
                SetWorldTransform(imj->Canvas->Handle, &xform);
                SetViewportOrgEx(imj->Canvas->Handle,xx,yy,NULL);

        }



 //**************************************************
 
class tPoint:public geom_f
{

protected:
	int *cord_x1,*cord_y1;

public:
        tPoint();
        void set_cord(int x,int y)
        {
         cord_x1=(int*)malloc(sizeof(int));
         *cord_x1=x;
         cord_y1=(int*)malloc(sizeof(int));
         *cord_y1=y;
    //     x=*cord_x1;
    //     y=*cord_y1;
         return ;
        }
        void drow();
};

tPoint::tPoint()
{
        cord_x1=cord_y1=NULL;
        set_color(0,0,0);
}

void tPoint::drow()
{
        if(cord_x1==NULL)
                return;
        imj->Canvas->Brush->Color=(TColor)RGB(color.R,color.G,color.B);
        imj->Canvas->Pen->Color=(TColor)RGB(color.R,color.G,color.B);
        imj->Canvas->Ellipse(*cord_x1-5,*cord_y1-5,*cord_x1+5,*cord_y1+5);
        imj->Canvas->Brush->Color=(TColor)RGB(255,255,255);
	return;


}

//*************************************************


class tLine:public tPoint
{
protected:
	int *cord_x2,*cord_y2;

public:
        tLine();
        void set_cord(int x1,int y1,int x2,int y2)
        {
         cord_x1=(int*)malloc(sizeof(int));
         *cord_x1=x1;
         cord_y1=(int*)malloc(sizeof(int));
         *cord_y1=y1;
         cord_x2=(int*)malloc(sizeof(int));
         *cord_x2=x2;
         cord_y2=(int*)malloc(sizeof(int));
         *cord_y2=y2;
         cord_x=(int*)malloc(sizeof(int));;
         cord_y=(int*)malloc(sizeof(int));;

         *cord_x=(*cord_x1+*cord_x2)/2;
         *cord_y=(*cord_y1+*cord_y2)/2;
         return ;
        }
        void drow();
        void cler();
};

tLine::tLine()
{
        cord_x1=cord_y1=cord_x2=cord_y2=NULL;
        set_color(0,0,0);
}


void tLine::drow()
{
        if(cord_x1==NULL)
                return;
        vrash_cord(ygol,*cord_x,*cord_y);
        imj->Canvas->Pen->Color=(TColor)RGB(color.R,color.G,color.B);
        imj->Canvas->MoveTo(-(*cord_x2-*cord_x1)/2,-(*cord_y2-*cord_y1)/2);
        imj->Canvas->LineTo((*cord_x2-*cord_x1)/2,(*cord_y2-*cord_y1)/2);
        vrash_cord(0,0,0);
	return;
}

void tLine::cler()
{
        if(cord_x1==NULL)
                return;
        vrash_cord(ygol,*cord_x,*cord_y);
        imj->Canvas->Pen->Color=(TColor)RGB(255,255,255);
        imj->Canvas->MoveTo(-(*cord_x2-*cord_x1)/2,-(*cord_y2-*cord_y1)/2);
        imj->Canvas->LineTo((*cord_x2-*cord_x1)/2,(*cord_y2-*cord_y1)/2);
        vrash_cord(0,0,0);
	return;
}


//******************************************************************************


class tCyrc:public tPoint
{
protected:
	int *R;
public:
        tCyrc();
        void set_cord(int x,int y,int r)
        {
         cord_x1=(int*)malloc(sizeof(int));
         *cord_x1=x;
         cord_y1=(int*)malloc(sizeof(int));
         *cord_y1=y;
         R=(int*)malloc(sizeof(int));
         *R=r;

        x=*cord_x1;
        y=*cord_y1;
         return ;
        }
        void drow();
};

tCyrc::tCyrc()
{
        cord_x1=cord_y1=R=NULL;
        set_color(0,0,0);
}



void tCyrc::drow()
{
        if(cord_x1==NULL)
                return;
       // vrash_cord(ygol,*cord_x,*cord_y);
        imj->Canvas->Pen->Color=(TColor)RGB(color.R,color.G,color.B);
        imj->Canvas->Ellipse(*cord_x1-*R/2,*cord_y1-*R/2,*cord_x1+*R/2,*cord_y1+*R/2);
        vrash_cord(0,0,0);
	return;
}

//******************************************************************************





class tElips:public tPoint
{
protected:
	int *cord_x1,*cord_y1, *H,*W;
public:
        tElips();
        void set_cord(int x,int y,int h,int w)
        {
         cord_x1=(int*)malloc(sizeof(int));
         *cord_x1=x;
         cord_y1=(int*)malloc(sizeof(int));
         *cord_y1=y;
         H=(int*)malloc(sizeof(int));
         *H=h;
         W=(int*)malloc(sizeof(int));
         *W=w;
         cord_x=(int*)malloc(sizeof(int));
         *cord_x=*cord_x1;
         cord_y=(int*)malloc(sizeof(int));
         *cord_y=*cord_y1;
         return ;
        }
        void drow();
        void cler();
};

tElips::tElips()
{
        cord_x1=cord_y1=H=W=NULL;
        set_color(0,0,0);
}

void tElips::drow()
{
        if(cord_x1==NULL)
                return;

        vrash_cord(ygol,*cord_x,*cord_y);
        imj->Canvas->Pen->Color=(TColor)RGB(color.R,color.G,color.B);
        imj->Canvas->Ellipse(-*W/2,-*H/2,*W/2,*H/2);
        vrash_cord(0,0,0);
	return;


}

void tElips::cler()
{
        if(cord_x1==NULL)
                return;
        vrash_cord(ygol,*cord_x,*cord_y);
        imj->Canvas->Pen->Color=(TColor)RGB(255,255,255);
        imj->Canvas->Ellipse(-*W/2,-*H/2,*W/2,*H/2);
        vrash_cord(0,0,0);
	return;


}

//******************************************************************************







class tRect:public tLine
{

public:
        tRect();
        void set_cord(int x1,int y1,int x2,int y2)
        {
         cord_x1=(int*)malloc(sizeof(int));
         *cord_x1=x1;
         cord_y1=(int*)malloc(sizeof(int));
         *cord_y1=y1;
         cord_x2=(int*)malloc(sizeof(int));
         *cord_x2=x2;
         cord_y2=(int*)malloc(sizeof(int));
         *cord_y2=y2;
         
         cord_x=(int*)malloc(sizeof(int));
         *cord_x=(*cord_x1+*cord_x2)/2;
         cord_y=(int*)malloc(sizeof(int));
         *cord_y=(*cord_y1+*cord_y2)/2;
         return ;
        }
        void drow();
        void cler();
};

tRect::tRect()
{
        cord_x1=cord_y1=cord_x2=cord_y2=NULL;
        set_color(0,0,0);
}

void tRect::drow()
{
        if(cord_x1==NULL)
                return;
        vrash_cord(ygol,*cord_x,*cord_y);
        imj->Canvas->Pen->Color=(TColor)RGB(color.R,color.G,color.B);
        imj->Canvas->MoveTo(-(*cord_x2-*cord_x1)/2,-(*cord_y2-*cord_y1)/2);
        imj->Canvas->LineTo(-(*cord_x2-*cord_x1)/2,(*cord_y2-*cord_y1)/2);
        imj->Canvas->LineTo((*cord_x2-*cord_x1),(*cord_y2-*cord_y1)/2);
        imj->Canvas->LineTo((*cord_x2-*cord_x1),-(*cord_y2-*cord_y1)/2);
        imj->Canvas->LineTo(-(*cord_x2-*cord_x1)/2,-(*cord_y2-*cord_y1)/2);
        vrash_cord(0,0,0);
	return;
}

 void tRect::cler()
{
        if(cord_x1==NULL)
                return;
        vrash_cord(ygol,*cord_x,*cord_y);
        imj->Canvas->Pen->Color=(TColor)RGB(255,255,255);
        imj->Canvas->MoveTo(-(*cord_x2-*cord_x1)/2,-(*cord_y2-*cord_y1)/2);
        imj->Canvas->LineTo(-(*cord_x2-*cord_x1)/2,(*cord_y2-*cord_y1)/2);
        imj->Canvas->LineTo((*cord_x2-*cord_x1),(*cord_y2-*cord_y1)/2);
        imj->Canvas->LineTo((*cord_x2-*cord_x1),-(*cord_y2-*cord_y1)/2);
        imj->Canvas->LineTo(-(*cord_x2-*cord_x1)/2,-(*cord_y2-*cord_y1)/2);
        vrash_cord(0,0,0);
	return;
}
//******************************************************************************







class tTria:public tLine
{
private:

public:
        tTria();
        void set_cord(int x1,int y1,int x2,int y2)
        {
         cord_x1=(int*)malloc(sizeof(int));
         *cord_x1=x1;
         cord_y1=(int*)malloc(sizeof(int));
         *cord_y1=y1;
         cord_x2=(int*)malloc(sizeof(int));
         *cord_x2=x2;
         cord_y2=(int*)malloc(sizeof(int));
         *cord_y2=y2;
         cord_x=(int*)malloc(sizeof(int));
         cord_y=(int*)malloc(sizeof(int));
         *cord_x=*cord_x1;
         *cord_y=2*(*cord_y2-*cord_y1)/3+*cord_y1;
         return ;
        }
        virtual void drow();
        virtual void cler();
};

tTria::tTria()
{
        cord_x1=cord_y1=cord_x2=cord_y2=NULL;
        set_color(0,0,0);
}


void tTria::drow()
{
        if(cord_x1==NULL)
                return;
        vrash_cord(ygol,*cord_x,*cord_y);
        imj->Canvas->Pen->Color=(TColor)RGB(color.R,color.G,color.B);
        imj->Canvas->MoveTo(0,-2*(*cord_y2-*cord_y1)/3);
        imj->Canvas->LineTo(*cord_x2-*cord_x1,(*cord_y2-*cord_y1)/3);
        imj->Canvas->LineTo(-*cord_x2+*cord_x1,(*cord_y2-*cord_y1)/3);
        imj->Canvas->LineTo(0,-2*(*cord_y2-*cord_y1)/3);
        vrash_cord(0,0,0);
	return;
}


void tTria::cler()
{
        if(cord_x1==NULL)
                return;
        vrash_cord(ygol,*cord_x,*cord_y);
        imj->Canvas->Pen->Color=(TColor)RGB(255,255,255);
        imj->Canvas->MoveTo(0,-2*(*cord_y2-*cord_y1)/3);
        imj->Canvas->LineTo(*cord_x2-*cord_x1,(*cord_y2-*cord_y1)/3);
        imj->Canvas->LineTo(-*cord_x2+*cord_x1,(*cord_y2-*cord_y1)/3);
        imj->Canvas->LineTo(0,-2*(*cord_y2-*cord_y1)/3);
        vrash_cord(0,0,0);
	return;
}

//******************************************************************************




 
class tRomb:public tElips
{

public:
        tRomb();
        void set_cord(int x,int y,int h,int w)
        {
         cord_x1=(int*)malloc(sizeof(int));
         *cord_x1=x;
         cord_y1=(int*)malloc(sizeof(int));
         *cord_y1=y;
         H=(int*)malloc(sizeof(int));
         *H=h;
         W=(int*)malloc(sizeof(int));
         *W=w;
         cord_x=(int*)malloc(sizeof(int));
         *cord_x=*cord_x1;
         cord_y=(int*)malloc(sizeof(int));
         *cord_y=*cord_y1+*H/2;
         return ;
        }
        void drow();
        void cler();


};



tRomb::tRomb()
{
        cord_x1=cord_y1=H=W=NULL;
        set_color(0,0,0);
}


void tRomb::drow()
{
        if(cord_x==NULL)
                return;
        vrash_cord(ygol,*cord_x,*cord_y);
        imj->Canvas->Pen->Color=(TColor)RGB(color.R,color.G,color.B);
        imj->Canvas->MoveTo(0,-*H/2);
        imj->Canvas->LineTo(-*W/2,0);
        imj->Canvas->LineTo(0,*H/2);
        imj->Canvas->LineTo(*W/2,0);
        imj->Canvas->LineTo(0,-*H/2);
	return;
}


void tRomb::cler()
{
        if(cord_x1==NULL)
                return;
        vrash_cord(ygol,*cord_x,*cord_y);
        imj->Canvas->Pen->Color=(TColor)RGB(255,255,255);
        imj->Canvas->MoveTo(0,-*H/2);
        imj->Canvas->LineTo(-*W/2,0);
        imj->Canvas->LineTo(0,*H/2);
        imj->Canvas->LineTo(*W/2,0);
        imj->Canvas->LineTo(0,-*H/2);
        vrash_cord(0,0,0);
	return;
}

//******************************************************************************
tPoint point;
tLine line;
tCyrc cyrc;
tElips elips;
tRect rect;
tTria tria;
tRomb romb;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{



        srand(time(0));

        Form1->DoubleBuffered=true;


        point.set_cord(20,100);

        point.set_color(100,200,100);
        point.drow();


        line.set_cord(50,50,100,200);
        line.set_color(250,30,50);
        line.drow();




        cyrc.set_cord(50,30,20);
        cyrc.set_color(200,100,0);
        cyrc.drow();



        elips.set_cord(100,100,50,20);
        elips.set_color(139,100,129);
        elips.drow();




        rect.set_cord(150,100,200,200);
        rect.set_color(60,150,70);
        rect.drow();



        tria.set_cord(80,80,60,180);
        tria.set_color(154,178,111);

        tria.drow();



        romb.set_cord(500,100,40,70);
        romb.set_color(90,20,199);
        romb.drow();
}
//---------------------------------------------------------------------------



float i=0;
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
elips.cler();
elips.set_ygol(i);
i+=1;
elips.drow();


line.cler();
line.set_ygol(i);

line.drow();

rect.cler();
rect.set_ygol(i);

rect.drow();


romb.cler();
romb.set_ygol(i);

romb.drow();


 
tria.cler();
tria.set_ygol(i);

tria.drow();

}
//---------------------------------------------------------------------------

