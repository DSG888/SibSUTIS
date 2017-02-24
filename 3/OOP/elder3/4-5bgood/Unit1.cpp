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

tFigure::tFigure()
{

x_center=NULL;
y_center=NULL;
     color.R=1+(rand()%254);
     color.G=1+(rand()%254);
     color.B=1+(rand()%254);
ygol=0;
        int a=rand()%2;
        if(a==0)
                x_move=1;
        else
                x_move=-1;
        a=rand()%2;
        if(a==0)
                y_move=1;
        else
                y_move=-1;

brd=20;
}

void tFigure::print()
{


        imj->Canvas->Pen->Color=(TColor)RGB(color.R,color.G,color.B);

      vrash_cord(ygol,*x_center,*y_center);
     drow();
      vrash_cord(0,0,0);
     return;
}

void tFigure::set_cord( float c)
{
 if(x_center!=NULL)
vrash_cord(ygol,*x_center,*y_center);
        imj->Canvas->Pen->Color=(TColor)RGB(255,255,255);
        if(x_center!=NULL)
     drow();
        else
                {
                 x_center= new int;
                 y_center= new int;
                }

      ygol=c;

}

void tFigure::set_cord(int x11,int y11)
{
 if(x_center!=NULL)
vrash_cord(ygol,*x_center,*y_center);
        imj->Canvas->Pen->Color=(TColor)RGB(255,255,255);
        if(x_center!=NULL)
     drow();
        else
                {
                 x_center= new int;
                 y_center= new int;
                }


 *x_center=x11;
 *y_center=y11;
}
void tFigure::drow()
{


}

void tFigure::vrash_cord(float tt,int xx,int yy)
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


void tFigure::move()
{
        if(x_center!=NULL)
                vrash_cord(ygol,*x_center,*y_center);
        imj->Canvas->Pen->Color=(TColor)RGB(255,255,255);
        if(x_center!=NULL)
     drow();
        else
                {
                 x_center= new int;
                 y_center= new int;
                }
        
        if(*x_center+x_move>x_max-brd)
                x_move=-1;
        if(*x_center-x_move<brd)
                x_move=1;

         if(*y_center+y_move>y_max-brd)
                y_move=-1;
        if(*y_center-y_move<brd)
                y_move=1;
        *x_center+=x_move;
        *y_center+=y_move;

}

//****************************************************************

void tPoint::drow()
{  
   imj->Canvas->Ellipse(-5,-5,+5,+5);
}

 void tPoint::print()
{

        imj->Canvas->Brush->Color=(TColor)RGB(color.R,color.G,color.B);
        imj->Canvas->Pen->Color=(TColor)RGB(color.R,color.G,color.B);

      vrash_cord(ygol,*x_center,*y_center);
     drow();
      vrash_cord(0,0,0);
       imj->Canvas->Brush->Color=(TColor)RGB(255,255,255);
     return;
}


void tPoint::set_cord(int x11,int y11)
{
         if(x_center!=NULL)
        vrash_cord(ygol,*x_center,*y_center);
        imj->Canvas->Pen->Color=(TColor)RGB(255,255,255);
        imj->Canvas->Brush->Color=(TColor)RGB(255,255,255);
        if(x_center!=NULL)
     drow();
        else
                {
                 x_center= new int;
                 y_center= new int;
                }


 *x_center=x11;
 *y_center=y11;
}

void tPoint::set_cord( float c)
{
         if(x_center!=NULL)
        vrash_cord(ygol,*x_center,*y_center);
        imj->Canvas->Pen->Color=(TColor)RGB(255,255,255);
        imj->Canvas->Brush->Color=(TColor)RGB(255,255,255);
        if(x_center!=NULL)
     drow();
        else
                {
                 x_center= new int;
                 y_center= new int;
                }

      ygol=c;

}
//*****************************************************************************


void tLine::set_opt(int xs,int ys,int xe,int ye)
{
    x1=xs;
    x2=xe;
    y1=ys;
    y2=ye;
    x_center= new int;
    y_center=new int;
    *x_center=(x1+x2)/2;
    *y_center=(y1+y2)/2;

    brd=(x2-x1>y2-y1)?x2-x1:y2-y1;
}




void tLine::drow()
{
        imj->Canvas->MoveTo(-(x2-x1)/2,-(y2-y1)/2);
        imj->Canvas->LineTo((x2-x1)/2,(y2-y1)/2);
}


//***************************************************

void tRect::drow()
{
        imj->Canvas->MoveTo(-(x2-x1)/2,-(y2-y1)/2);
        imj->Canvas->LineTo(-(x2-x1)/2,(y2-y1)/2);
        imj->Canvas->LineTo((x2-x1),(y2-y1)/2);
        imj->Canvas->LineTo((x2-x1),-(y2-y1)/2);
        imj->Canvas->LineTo(-(x2-x1)/2,-(y2-y1)/2);

}

//****************************************************


 void tCyrc::set_opt(int xs,int ys,int hs,int ws)
{
    x1=xs;
    y1=ys;
    H=hs;
    W=ws;
    x_center= new int;
    y_center=new int;
    *x_center=x1;
    *y_center=y1;
    brd=(H>W)?H:W;
}







void tCyrc::drow()
{
         imj->Canvas->Ellipse(-W/2,-H/2,W/2,H/2);
}

//****************************************************


void tRomb::drow()
{

        imj->Canvas->MoveTo(0,-H/2);
        imj->Canvas->LineTo(-W/2,0);
        imj->Canvas->LineTo(0,H/2);
        imj->Canvas->LineTo(W/2,0);
        imj->Canvas->LineTo(0,-H/2);
}

//****************************************************************************

void tTria::drow()
{

        imj->Canvas->MoveTo(0,-2*(y2-y1)/3);
        imj->Canvas->LineTo(x2-x1,(y2-y1)/3);
        imj->Canvas->LineTo(-x2+x1,(y2-y1)/3);
        imj->Canvas->LineTo(0,-2*(y2-y1)/3);

}
//****************************************************************************
    tPoint *point= new tPoint;
    tLine *line=new tLine;
    tRect *rect=new tRect;
    tCyrc *cy=new tCyrc;
    tCyrc *el=new tCyrc;
    tRomb *r=new tRomb;
    tTria *t=new tTria;
    int y=0,k=1;

    tFigure *mas[7];
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

mas[0]=new tPoint;
mas[1]=new tLine;
mas[2]=new tRect;
mas[3]=new tCyrc;
mas[4]=new tCyrc;
mas[5]=new tRomb;
mas[6]=new tTria;
        srand(time(0));

       Form1->DoubleBuffered=true;

       
          line->set_opt(30,30,60,80);


        rect->set_opt(100,100,150,150);


        cy->set_opt(200,200,30,30);

        el->set_opt(400,250,40,20);

        r->set_opt(0,0,50,30);

        t->set_opt(600,250,550,300);

}



//---------------------------------------------------------------------------





void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
//if (k==1)
//{
        y+=1;
        point->move();
        line->move();
        rect->move();
        cy->move();

        el->move();

        r->move();

        t->move();

        point->set_cord(y);
        point->print();
        line->set_cord(y);
        line->print();
        rect->set_cord(y);
        rect->print();
        cy->set_cord(y);
        cy->print();
        el->set_cord(y);
        el->print();
        r->set_cord(y);
        r->print();
        t->set_cord(y);
        t->print();
        
 //}
 /*else
 {
        point->move();
        line->move();
        rect->move();
        cy->move();

        el->move();

        r->move();

        t->move();

        point->print();

        line->print();

        rect->print();

        cy->print();

        el->print();

        r->print();
 
        t->print();

 }      */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
//k=-1*k;        
}
//---------------------------------------------------------------------------

