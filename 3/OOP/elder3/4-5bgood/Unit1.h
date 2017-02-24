//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------

#define x_max (Form1->Image1->Width)
#define y_max (Form1->Image1->Height)
#define imj Form1->Image1


class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TTimer *Timer1;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------

 struct colorRGB
{
 int R;
 int G;
 int B;
};


class tFigure
{
        protected:
               int *x_center,*y_center,x_move,y_move,brd;
               colorRGB color;
               float ygol;
               virtual void drow();
               void vrash_cord(float ,int ,int );

        public:
               tFigure();
               void print();
               void set_cord(int,int);
               void move();
               void set_cord(float);
              // virtual void set_opt();


};

//*****************************************************************************
class tPoint:public tFigure
{
       protected:
               int x1,y1;
               void drow();
       public:

               void print();
               void set_cord(float);
               void set_cord(int,int);
};
//*****************************************************************************
class tLine:public tPoint
{
       protected:
               int x2,y2;
               void drow();
       public:
               void set_opt(int,int,int,int);


};

//*****************************************************************************


class tRect:public tLine
{
       protected:
               
               void drow();

};


//*****************************************************************************

class tCyrc:public tFigure
{
        protected:
        int x1,y1,H,W;
         void drow();
       public:

               void set_opt(int,int,int,int);

};


//*****************************************************************************

class tRomb:public tCyrc
{

       protected:
               void drow();

};

//*****************************************************************************

class tTria:public tLine
{

      protected:
               void drow();

};







#endif
