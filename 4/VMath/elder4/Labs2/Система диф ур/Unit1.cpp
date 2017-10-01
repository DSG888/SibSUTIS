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
double fnc1(double t, double x, double y){
	return x*y+t;
}
//---------------------------------------------------------------------------
double fnc2(double t, double x, double y){
	return x-y-t;
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	double a, b, t, h, x, y, xn, yn;
	int n, i;

	Memo1->Lines->Clear();

	x=StrToFloat(numA->Text);
	b=StrToFloat(numB->Text);
	h=StrToFloat(numH->Text);
	y=StrToFloat(numY0->Text);
	t=a=StrToFloat(Edit1->Text);

	n=(b-a)/h+h/2;

	Memo1->Lines->Add("X[0]=("+FloatToStr(x)+"; "+FloatToStr(y)+");");
	for(i=1;i<=n;i++){
		xn=x+h*fnc1(t, x, y);
		yn=y+h*fnc2(t, x, y);
		x=xn;
		y=yn;
		t+=h;
		Memo1->Lines->Add("X["+IntToStr(i)+"]=("+FloatToStr(x)+"; "+FloatToStr(y)+");");

	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	double a, b, t, h, x, y, xs, ys, xn, yn;
	int n, i;

	Memo1->Lines->Clear();

	x=StrToFloat(numA->Text);
	b=StrToFloat(numB->Text);
	h=StrToFloat(numH->Text);
	y=StrToFloat(numY0->Text);
	t=a=StrToFloat(Edit1->Text);
	
	n=(b-a)/h+h/2;

	Memo1->Lines->Add("X[0]=("+FloatToStr(x)+"; "+FloatToStr(y)+");");
	for(i=1;i<=n;i++){
		xs=x+h*fnc1(t, x, y);
		ys=y+h*fnc2(t, x, y);
		xn=x+h/2*(fnc1(t, x, y)+fnc1(t+h, xs, ys));
		yn=y+h/2*(fnc2(t, x, y)+fnc2(t+h, xs, ys));
		x=xn;
		y=yn;
		t+=h;
		Memo1->Lines->Add("X["+IntToStr(i)+"]=("+FloatToStr(x)+"; "+FloatToStr(y)+");");
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	double a, b, t, h, x, y, xs, ys, xn, yn;
	int n, i;

	Memo2->Lines->Clear();

	x=StrToFloat(numA->Text);
	b=StrToFloat(numB->Text);
	h=StrToFloat(numH->Text);
	y=StrToFloat(numY0->Text);
	t=a=StrToFloat(Edit1->Text);

	n=(b-a)/h+h/2;

	Memo2->Lines->Add("X[0]=("+FloatToStr(x)+"; "+FloatToStr(y)+");");
	for(i=1;i<=n;i++){
		xs=x+h/2*fnc1(t, x, y);
		ys=y+h/2*fnc2(t, x, y);
		xn=x+h*fnc1(t+h/2, xs, ys);
		yn=y+h*fnc2(t+h/2, xs, ys);
		x=xn;
		y=yn;
		t+=h;
		Memo2->Lines->Add("X["+IntToStr(i)+"]=("+FloatToStr(x)+"; "+FloatToStr(y)+");");
	}
}
//---------------------------------------------------------------------------

