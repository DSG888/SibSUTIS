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



class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TTimer *Timer1;
        TMemo *Memo1;
        void __fastcall Timer1Timer(TObject *Sender);
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

class geom_f
{

protected:
        colorRGB color;
       // int *x,*y;
       int *cord_x,*cord_y;
        float ygol;
        geom_f();

public:
        void set_color(int R,int G,int B)
        {
                color.R=R;
                color.G=G;
                color.B=B;
        }
        void set_ygol(float y)
        {
                ygol=y;
        }
        void vrash_cord(float,int,int);
};
#endif
