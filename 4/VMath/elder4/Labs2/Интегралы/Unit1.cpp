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
double fnc(double x)
{
	return 1/x;
}
//---------------------------------------------------------------------------
double sum1(double x, double h, int n){
	double res=0;
	int i, k;
	k=n/2;

	for(i=1;i<=k;i++)res+=fnc(x+(2*i-1)*h);

	return 4*res;
}
//---------------------------------------------------------------------------
double sum2(double x, double h, int n){
	double res=0;
	int i, k;
	k=n/2;

	for(i=1;i<k;i++)res+=fnc(x+2*i*h);

	return 2*res;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	double x, h, a, b, intg1, intg2, eps=1;
	int n, i, e;

	a=StrToFloat(numA->Text);
	b=StrToFloat(numB->Text);
	n=StrToFloat(numN->Text);
	e=StrToInt(Edit1->Text);
	for(i=0;i<e;i++)eps/=10;

	h=(b-a)/n;/*расчет шага*/
	x=a;

	Memo1->Lines->Clear();
	/*Расчет интеграла методом двойного перерасчета*/
	do{
		Memo1->Lines->Add("Текущий шаг h="+FloatToStr(h));
		intg1=intg2=0;
		/*Расчет интеграла*/
		for(i=1;i<=n;i++)intg1+=h*(fnc(x+(i-1)*h)+fnc(x+i*h))/2;
		Memo1->Lines->Add("Интеграл="+FloatToStr(intg1));/*Вывод интеграла*/

		/*уменьшение шага в 2 раза*/
		n*=2;
		h=(b-a)/n;

		/*Расчет инеграла с меньшим шагом*/
		for(i=1;i<=n;i++)intg2+=h*(fnc(x+(i-1)*h)+fnc(x+i*h))/2;
		Memo1->Lines->Add("");
	}while(fabs(intg2-intg1)>eps);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	double x, h, a, b, intg1, intg2, eps=1;
	int n, i, e;

	a=StrToFloat(numA->Text);
	b=StrToFloat(numB->Text);
	n=StrToFloat(numN->Text);
	e=StrToInt(Edit1->Text);
	for(i=0;i<e;i++)eps/=10;

	h=(b-a)/n;/*расчет шага*/
	x=a;

	Memo2->Lines->Clear();
	/*Расчет интеграла методом двойного перерасчета*/
	do{
		Memo2->Lines->Add("Текущий шаг h="+FloatToStr(h));
		intg1=intg2=0;
		/*Расчет интеграла*/
		intg1=h/3*(fnc(x)+fnc(x+n*h)+sum1(x, h, n)+sum2(x, h, n));
		Memo2->Lines->Add("Интеграл="+FloatToStr(intg1));/*Вывод интеграла*/

		/*уменьшение шага в 2 раза*/
		n*=2;
		h=(b-a)/n;

		/*Расчет инеграла с меньшим шагом*/
		intg2=h/3*(fnc(x)+fnc(x+n*h)+sum1(x, h, n)+sum2(x, h, n));
		Memo2->Lines->Add("");
	}while(fabs(intg2-intg1)>eps);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label2Click(TObject *Sender)
{
	double x, h, a, b, intg1, intg2, eps;
	int n, i, e;
	eps=1*10^-e;
	Sleep(1000);
	h=(b-a)/n;/*расчет шага*/
	x=a;

	Memo2->Lines->Clear();
	/*Расчет интеграла методом двойного перерасчета*/
	do{
		Memo2->Lines->Add("Текущий шаг h="+FloatToStr(h));
		intg1=intg2=0;
		/*Расчет интеграла*/
		intg1=h/3*(fnc(x)+fnc(x+n*h)+sum1(x, h, n)+sum2(x, h, n));
		Memo2->Lines->Add("Интеграл="+FloatToStr(intg1));/*Вывод интеграла*/

		/*уменьшение шага в 2 раза*/
		n*=2;
		h=(b-a)/n;

		/*Расчет инеграла с меньшим шагом*/
		intg2=h/3*(fnc(x)+fnc(x+n*h)+sum1(x, h, n)+sum2(x, h, n));
		Memo2->Lines->Add("");
	}while(fabs(intg2-intg1)>eps);
}
//---------------------------------------------------------------------------

