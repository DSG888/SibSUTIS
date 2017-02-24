//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPaintBox *PaintBox1;
        TTimer *Timer1;
        TMainMenu *MainMenu1;
        TMenuItem *Add1;
        TMenuItem *Circle1;
        TMenuItem *Point1;
        TMenuItem *Line1;
        TMenuItem *Rectangle1;
        TMenuItem *Triangle1;
        TMenuItem *Ellipse1;
        TMenuItem *Romb1;
        TMenuItem *Move1;
        TMenuItem *Linear1;
        TMenuItem *Chaotic1;
        void __fastcall Linear1Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Line1Click(TObject *Sender);
        void __fastcall Point1Click(TObject *Sender);
        void __fastcall Chaotic1Click(TObject *Sender);
        void __fastcall Rectangle1Click(TObject *Sender);
        void __fastcall Circle1Click(TObject *Sender);
        void __fastcall Ellipse1Click(TObject *Sender);
        void __fastcall Romb1Click(TObject *Sender);
        void __fastcall Triangle1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
