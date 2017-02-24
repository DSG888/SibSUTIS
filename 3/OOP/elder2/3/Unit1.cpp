//---------------------------------------------------------------------------

#include <vcl.h>
#include <conio.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

class tPoint
{
protected:
   int x;
   int y;
   int dx;
   int dy;
   int r;
   int g;
   int b;
   int mm;
public:
   void Init();
   void Draw();
   void Hide();
   void Move();
};

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void tPoint::Init()
{
        randomize;
        x=random(887)+2;
        y=random(359)+2;
        r=random(255);
        g=random(255);
        b=random(255);
        mm=random(2); // 1 - L; 0 - Ch
        dx=dy=2;
        if (random(2)) dx=dx*(-1);
        if (random(2)) dy=dy*(-1);
}

void tPoint::Draw()
{
  Form1->PaintBox1->Canvas->Brush->Color = RGB(r,g,b);
  Form1->PaintBox1->Canvas->Pen->Color = RGB(r,g,b);
  Form1->PaintBox1->Canvas->Ellipse(x-2,y-2,x+2,y+2);
}
void tPoint::Hide()
{
  Form1->PaintBox1->Canvas->Brush->Color = RGB(255,255,255);
  Form1->PaintBox1->Canvas->Pen->Color = RGB(255,255,255);
  Form1->PaintBox1->Canvas->Ellipse(x-2,y-2,x+2,y+2);
}
void tPoint::Move()
{
  Hide();
  if(mm)
  {
        if ((x>=887)||(x<=3)) dx=dx*(-1);
        if ((y>=359)||(y<=1)) dy=dy*(-1);
        //dx=dx+1-1;
  }
  else
  {
        if(random(2))dx=dx*(-1);
        if(random(2))dy=dy*(-1);
        if (((x+dx)>887)||((x+dx)<3)) dx=dx*(-1);
        if (((y+dy)>359)||((y+dy)<3)) dy=dy*(-1);
  }
  x+=dx;
  y+=dy;
  //}
  Draw();
}

tPoint Dot[100];

void __fastcall TForm1::Button2Click(TObject *Sender)
{
Form1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
int i;
PaintBox1->Canvas->Pen->Color = clWhite;
PaintBox1->Canvas->Brush->Color = clWhite;
PaintBox1->Canvas->Rectangle(0,0,889,361);
for(i=0;i<100;i++)
   {
      Dot[i].Init();
      Dot[i].Draw();
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
int i,j;
Form1->Timer1->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
int i;
for(i=0;i<100;i++)
        {
        Dot[i].Move();
        }
}
//---------------------------------------------------------------------------

