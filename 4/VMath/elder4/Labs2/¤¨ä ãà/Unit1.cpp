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
double fnc(double x, double y){
	return (exp(x)+y)/2;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	double a, b, t, h, x, y;
	int n,i;

	Memo1->Lines->Clear();

	x=a=StrToFloat(numA->Text);
	b=StrToFloat(numB->Text);
	h=StrToFloat(numH->Text);
	y=StrToFloat(numY0->Text);

	n=(b-a)/h+h/2;

	Memo1->Lines->Add("x["+FloatToStr(a)+"]="+FloatToStr(x)+"   y["+FloatToStr(a)+"]="+FloatToStr(y));
	for(i=1;i<=n;i++){;
		y=y+h*fnc(x,y);
		x+=h;
		Memo1->Lines->Add("x["+IntToStr(i)+"]="+FloatToStr(x)+"   y["+IntToStr(i)+"]="+FloatToStr(y));
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	double a, b, t, h, x, y, ys;
	int n, i;

	Memo2->Lines->Clear();

	x=a=StrToFloat(numA->Text);
	b=StrToFloat(numB->Text);
	h=StrToFloat(numH->Text);
	y=StrToFloat(numY0->Text);

	n=(b-a)/h+h/2;

	Memo2->Lines->Add("x["+FloatToStr(a)+"]="+FloatToStr(x)+"   y["+FloatToStr(a)+"]="+FloatToStr(y));
	for(i=1;i<=n;i++){
		ys=y+h/2*fnc(x, y);
		y=y+h*(fnc(x+h/2, ys));
		x+=h;
		Memo2->Lines->Add("x["+IntToStr(i)+"]="+FloatToStr(x)+"   y["+IntToStr(i)+"]="+FloatToStr(y));
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	double a, b, t, h, x, y, ys;
	int n, i;

	Memo1->Lines->Clear();

	x=a=StrToFloat(numA->Text);
	b=StrToFloat(numB->Text);
	h=StrToFloat(numH->Text);
	y=StrToFloat(numY0->Text);

	n=(b-a)/h+h/2;

	Memo1->Lines->Add("x["+FloatToStr(a)+"]="+FloatToStr(x)+"   y["+FloatToStr(a)+"]="+FloatToStr(y));
	for(i=1;i<=n;i++){
		ys=y+h*fnc(x, y);
		y=y+h/2*(fnc(x, y)+fnc(x+h, ys));
		x+=h;
		Memo1->Lines->Add("x["+IntToStr(i)+"]="+FloatToStr(x)+"   y["+IntToStr(i)+"]="+FloatToStr(y));
	}
}
//---------------------------------------------------------------------------

