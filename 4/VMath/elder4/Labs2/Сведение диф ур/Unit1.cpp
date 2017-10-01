//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
double fnc(double y, double y1, double y2, double x){
	return x*y1+y-y2;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	double h, x, y, y1, y2, y3;
	int i, n=10;

	Memo1->Lines->Clear();

	y=StrToFloat(Edit1->Text);
	y1=StrToFloat(Edit2->Text);
	y2=StrToFloat(Edit3->Text);
	x=StrToFloat(Edit4->Text);
	h=StrToFloat(Edit5->Text);

	for(i=0; i<=n;i++){
		y3=fnc(y, y1, y2, x);
		y+=h*y1;
		y1+=h*y2;
		y2+=h*y3;
		Memo1->Lines->Add("x="+FloatToStr(x)+"; y="+FloatToStr(y)+"; y'="+FloatToStr(y1)+"; y''="+FloatToStr(y2));
		x+=h;
	}
}
//---------------------------------------------------------------------------
