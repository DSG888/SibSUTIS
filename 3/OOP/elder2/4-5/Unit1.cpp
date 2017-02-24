//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int w = 897;
int h = 409;

bool M = true;

class tOneKoord
{
protected:
   TPoint *xy;
   int r;
   int g;
   int b;
   int dx;
   int dy;
public:
   virtual void Init() = 0;
   virtual void Hide() = 0;
   virtual void Draw() = 0;
   virtual void Move() = 0;
};


class tTwoKoord: public tOneKoord
{
protected:
        static int N;
public:
        void Init();
        virtual void Hide() = 0;
        virtual void Draw() = 0;
        void Move();
};


class tPoint: tOneKoord
{
public:
   void Init();
   void Hide();
   void Draw();
   void Move();
};

class tLine: public tTwoKoord
      {
      //protected:
      //  static int N;
      public:
      void Hide();
      void Draw();
      };

class tCircle: public tTwoKoord
      {
      protected:
                int R;
      public:
        void Init();
        void Hide();
        void Draw();
        void Move();
      };

class tRectangle: public tTwoKoord
      {
      public:
      void Hide();
      void Draw();
      };

class tTriangle: public tOneKoord
{
protected:
        static int N;
public:
        void Init();
        void Hide() ;
        void Draw() ;
        void Move();
};


class tEllipse: public tTwoKoord
      {
      public:
      void Hide();
      void Draw();
      };

class tRomb:  public tTwoKoord
      {
      public:
      void Hide();
      void Draw();
      };

int tTwoKoord::N = 2;
int tTriangle::N = 3;


void tPoint::Init()
{
  randomize;

  xy = new TPoint[0];

  xy[0].x=random(w-6)+2;
  xy[0].y=random(h-6)+2;

  r=random(255);
  g=random(255);
  b=random(255);

  dx=dy=1;
  if (random(2)) dx=dx*(-1);
  if (random(2)) dy=dy*(-1);
}

void tPoint::Draw()
{

	Form1->PaintBox1->Canvas->Brush->Color = RGB(r,g,b);
        Form1->PaintBox1->Canvas->Pen->Color = RGB(r,g,b);
        Form1->PaintBox1->Canvas->Ellipse(xy[0].x-2,xy[0].y-2,xy[0].x+2,xy[0].y+2);
}

void tPoint::Hide()
{

  Form1->PaintBox1->Canvas->Brush->Color = clBtnFace;
  Form1->PaintBox1->Canvas->Pen->Color = clBtnFace;
  Form1->PaintBox1->Canvas->Ellipse(xy[0].x-2,xy[0].y-2,xy[0].x+2,xy[0].y+2);
}

void tPoint::Move()
{

  Hide();
  if(M) // если М ==1, т.е. движение линейно, то 
  {
        //если дошли до края канвы, то меняем направление движения
	if ((xy[0].x>=w-2)||(xy[0].x<=3)) dx=dx*(-1);
        if ((xy[0].y>=h-2)||(xy[0].y<=1)) dy=dy*(-1);
  }
  else // если нет
  {	// тут направление движения случайно каждый раз
        if(random(2))dx=dx*(-1);
        if(random(2))dy=dy*(-1);
	//если при следующем шаге пересечем край канвы, то меняем направление
        if (((xy[0].x+dx)>w-2)||((xy[0].x+dx)<3)) dx=dx*(-1);
        if (((xy[0].y+dy)>h-2)||((xy[0].y+dy)<3)) dy=dy*(-1);
  }
// двигаем
  xy[0].x+=dx;
  xy[0].y+=dy;
  Draw();
}


void tTwoKoord::Init()
{

        int i;
        randomize;
        xy=new TPoint[N];
        for(i=0;i<N;i++)
        {
                xy[i].x=random(w-6)+2;
                xy[i].y=random(h-6)+2;
        }
        r=random(255);
        g=random(255);
        b=random(255);
        dx=dy=1;
        if (random(2)) dx=dx*(-1);
        if (random(2)) dy=dy*(-1);
        }

void tLine::Draw()
     {

     Form1->PaintBox1->Canvas->MoveTo(xy[0].x,xy[0].y);
     Form1->PaintBox1->Canvas->Brush->Color = RGB(r,g,b);
     Form1->PaintBox1->Canvas->Pen->Color = RGB(r,g,b);
     Form1->PaintBox1->Canvas->LineTo(xy[1].x,xy[1].y);
     }

void tLine::Hide()
     {
     Form1->PaintBox1->Canvas->MoveTo(xy[0].x,xy[0].y);;
     Form1->PaintBox1->Canvas->Brush->Color = clBtnFace;
     Form1->PaintBox1->Canvas->Pen->Color = clBtnFace;
     Form1->PaintBox1->Canvas->LineTo(xy[1].x,xy[1].y);;
     }

void tTwoKoord::Move()
{
  Hide();
  int i;
  TPoint t1,t2;

  t1=t2=xy[0];
  for(i=1;i<N;i++)
  {
  if(xy[i].x>t2.x)
         t2.x=xy[i].x;
  if(xy[i].x<t1.x)
         t1.x=xy[i].x;
  if(xy[i].y>t2.y)
         t2.y=xy[i].y;
  if(xy[i].y<t1.y)
         t1.y=xy[i].y;
  }

  if(M)
  {
        if ((t2.x>=w-1)||(t1.x<=1)) dx=dx*(-1);
        if ((t2.y>=h-1)||(t1.y<=1)) dy=dy*(-1);
        //dx=dx+1-1;
  }
  else
  {
        if(random(2))dx=dx*(-1);
        if(random(2))dy=dy*(-1);
        if (((t2.x+dx)>w-1)||((t1.x+dx)<1)) dx=dx*(-1);
        if (((t2.y+dy)>h-1)||((t1.y+dy)<1)) dy=dy*(-1);
  }
  for(i=0;i<N;i++)
  {
        xy[i].x+=dx;
        xy[i].y+=dy;
  }
Draw();
}

void tCircle::Init()
     {
        randomize;
        xy = new TPoint[0];
        xy[0].x=random(w-6)+2;
        xy[0].y=random(h-6)+2;
        r=random(255);
        g=random(255);
        b=random(255);
  dx=dy=1;
  if (random(2)) dx=dx*(-1);
  if (random(2)) dy=dy*(-1);
  R=random(40)+10;
     }

void tCircle::Draw()
     {
     Form1->PaintBox1->Canvas->Brush->Color = RGB(r,g,b);
     Form1->PaintBox1->Canvas->Pen->Color = RGB(r,g,b);
     Form1->PaintBox1->Canvas->Ellipse(xy[0].x-R/2,xy[0].y-R/2,xy[0].x+R/2,xy[0].y+R/2);
     }

void tCircle::Hide()
     {
     Form1->PaintBox1->Canvas->Brush->Color = clBtnFace;
     Form1->PaintBox1->Canvas->Pen->Color = clBtnFace;
     Form1->PaintBox1->Canvas->Ellipse(xy[0].x-R/2,xy[0].y-R/2,xy[0].x+R/2,xy[0].y+R/2);
     }

void tCircle::Move()
{
  Hide();
  if(M)
  {
        if ((xy[0].x>=w-2)||(xy[0].x<=3)) dx=dx*(-1);
        if ((xy[0].y>=h-2)||(xy[0].y<=1)) dy=dy*(-1);
  }
  else
  {
        if(random(2))dx=dx*(-1);
        if(random(2))dy=dy*(-1);
        if (((xy[0].x+dx)>w-2)||((xy[0].x+dx)<3)) dx=dx*(-1);
        if (((xy[0].y+dy)>h-2)||((xy[0].y+dy)<3)) dy=dy*(-1);
  }
  xy[0].x+=dx;
  xy[0].y+=dy;
  Draw();
}

void tRectangle::Draw()
     {
     Form1->PaintBox1->Canvas->Brush->Color = RGB(r,g,b);
     Form1->PaintBox1->Canvas->Pen->Color = RGB(r,g,b);
     Form1->PaintBox1->Canvas->Rectangle(xy[0].x,xy[0].y,xy[1].x,xy[1].y);
     }

void tRectangle::Hide()
     {
     Form1->PaintBox1->Canvas->Brush->Color = clBtnFace;
     Form1->PaintBox1->Canvas->Pen->Color = clBtnFace;
     Form1->PaintBox1->Canvas->Rectangle(xy[0].x,xy[0].y,xy[1].x,xy[1].y);
     }


void tEllipse::Draw()
     {
     Form1->PaintBox1->Canvas->Brush->Color = RGB(r,g,b);
     Form1->PaintBox1->Canvas->Pen->Color = RGB(r,g,b);
     Form1->PaintBox1->Canvas->Ellipse(xy[0].x,xy[0].y,xy[1].x,xy[1].y);
     }

void tEllipse::Hide()
     {
     Form1->PaintBox1->Canvas->Brush->Color = clBtnFace;
     Form1->PaintBox1->Canvas->Pen->Color = clBtnFace;
     Form1->PaintBox1->Canvas->Ellipse(xy[0].x,xy[0].y,xy[1].x,xy[1].y);
    }

void tRomb::Draw()
     {
     int i;
        TPoint xy2[4];
        xy2[0].x=xy[0].x;
        xy2[0].y=xy[0].y + (xy[1].y - xy[0].y)/2;
        xy2[1].x=xy[0].x + (xy[1].x - xy[0].x)/2;
        xy2[1].y=xy[1].y;
        xy2[2].x=xy[1].x;
        xy2[2].y=xy[0].y + (xy[1].y - xy[0].y)/2;
        xy2[3].x=xy[0].x + (xy[1].x - xy[0].x)/2;
        xy2[3].y=xy[0].y;
        Form1->PaintBox1->Canvas->Brush->Color = RGB(r,g,b);
        Form1->PaintBox1->Canvas->Pen->Color = RGB(r,g,b);
        Form1->PaintBox1->Canvas->Polygon(xy2,3);
     delete xy2;
     }

     void tRomb::Hide()
     {
     int i;
     TPoint xy2[4];
        xy2[0].x=xy[0].x;
        xy2[0].y=xy[0].y + (xy[1].y - xy[0].y)/2;
        xy2[1].x=xy[0].x + (xy[1].x - xy[0].x)/2;
        xy2[1].y=xy[1].y;
        xy2[2].x=xy[1].x;
        xy2[2].y=xy[0].y + (xy[1].y - xy[0].y)/2;
        xy2[3].x=xy[0].x + (xy[1].x - xy[0].x)/2;
        xy2[3].y=xy[0].y;
        Form1->PaintBox1->Canvas->Brush->Color = clBtnFace;
        Form1->PaintBox1->Canvas->Pen->Color = clBtnFace;
        Form1->PaintBox1->Canvas->Polygon(xy2,3);
     delete xy2;
     }



void tTriangle::Init()
{
        // треугольник, тоже аналогично, только точки уже три рандомится
	int i;
        randomize;
        xy=new TPoint[N];
        for(i=0;i<N;i++)
        {
                xy[i].x=random(w-6)+2;
                xy[i].y=random(h-6)+2;
        }
        r=random(255);
        g=random(255);
        b=random(255);
        dx=dy=1;
        if (random(2)) dx=dx*(-1);
        if (random(2)) dy=dy*(-1);
        }



void tTriangle::Move()
{
  Hide();
  int i;
  TPoint t1,t2;
  t1=t2=xy[0];
  for(i=1;i<N;i++)
  {
  if(xy[i].x>t2.x)
         t2.x=xy[i].x;
  if(xy[i].x<t1.x)
         t1.x=xy[i].x;
  if(xy[i].y>t2.y)
         t2.y=xy[i].y;
  if(xy[i].y<t1.y)
         t1.y=xy[i].y;
  }

  if(M)
  {
        if ((t2.x>=w-1)||(t1.x<=1)) dx=dx*(-1);
        if ((t2.y>=h-1)||(t1.y<=1)) dy=dy*(-1);
        //dx=dx+1-1;
  }
  else
  {
        if(random(2))dx=dx*(-1);
        if(random(2))dy=dy*(-1);
        if (((t2.x+dx)>w-1)||((t1.x+dx)<1)) dx=dx*(-1);
        if (((t2.y+dy)>h-1)||((t1.y+dy)<1)) dy=dy*(-1);
  }
  for(i=0;i<N;i++)
  {
        xy[i].x+=dx;
        xy[i].y+=dy;
  }
Draw();
}


void tTriangle::Draw()
     {
      Form1->PaintBox1->Canvas->Brush->Color = RGB(r,g,b);
      Form1->PaintBox1->Canvas->Pen->Color = RGB(r,g,b);
      Form1->PaintBox1->Canvas->Polygon(xy,2);
     }
     void tTriangle::Hide()
     {
      Form1->PaintBox1->Canvas->Brush->Color = clBtnFace;
      Form1->PaintBox1->Canvas->Pen->Color = clBtnFace;
      Form1->PaintBox1->Canvas->Polygon(xy,2);
     }

//---------------------------------------------------------------------------
// объявляем вектора для объектов
// вектор - прошаренный динамический массив
// лежит он в библиотеке vectors.h
vector <tPoint> point;
vector <tTriangle> tri;
vector <tLine> line;
vector <tRectangle> rect;
vector <tRomb> romb;
vector <tCircle> circle;
vector <tEllipse> ellipse;
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Linear1Click(TObject *Sender)
{
//переключалка на линейное движение
Form1->Timer1->Enabled = true;
M = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
// по таймеру происходит движение
unsigned int i;
//*name_vector*.size возвращает количество элементов в векторе. Размер массива, короче говоря 
for(i=0;i<rect.size();i++)
        rect[i].Move();
for(i=0;i<romb.size();i++)
        romb[i].Move();
for(i=0;i<ellipse.size();i++)
        ellipse[i].Move();
for(i=0;i<tri.size();i++)
        tri[i].Move();

for(i=0;i<circle.size();i++)
        circle[i].Move();
for(i=0;i<line.size();i++)
        line[i].Move();
for(i=0;i<point.size();i++)
        point[i].Move();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Line1Click(TObject *Sender)
{
// добавляем в вектор объект Линию
tLine temp;
temp.Init();
temp.Draw();
//*name_vector*.push_back(obj) - добавляет в конец вектора элемент
line.push_back(temp);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Point1Click(TObject *Sender)
{
tPoint temp;
temp.Init();
temp.Draw();
point.push_back(temp);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Chaotic1Click(TObject *Sender)
{
Form1->Timer1->Enabled = true;
M = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Rectangle1Click(TObject *Sender)
{
tRectangle temp;
temp.Init();
temp.Draw();
rect.push_back(temp);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Circle1Click(TObject *Sender)
{
tCircle temp;
temp.Init();
temp.Draw();
circle.push_back(temp);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Ellipse1Click(TObject *Sender)
{
tEllipse temp;
temp.Init();
temp.Draw();
ellipse.push_back(temp);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Romb1Click(TObject *Sender)
{

tRomb temp;
temp.Init();
temp.Draw();
romb.push_back(temp);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Triangle1Click(TObject *Sender)
{
tTriangle temp;
temp.Init();
temp.Draw();
tri.push_back(temp);
}
//---------------------------------------------------------------------------
