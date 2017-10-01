//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <math.h>

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
double h,//Начальный шаг
       gh,//Шаг после двойного пересчета
       e;//Точность расчетов
int n;//Количество шагов

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//Уравнение для вычисления
double fnc(double y, double y1, double x){
	return exp(x)+sin(y);
}
//---------------------------------------------------------------------------
//Нахождение y(b) при помощи Рунге-Кутта 4-ого порядка с двойным пересчетом
double kutt(double yp1, double yp2, double x){
	double k1, k2, k3, k4;
        double k11, k22, k33, k44;
        double d, last, next, y1, y2;
	int i;

        y1=yp1;
        y2=yp2;
        //Двойной пересчет
        do{
                yp1=y1;
                yp2=y2;
                x=StrToFloat(Form1->x1N->Text);
        	for(i=0; i<n; i++){
        		k11=yp2;
        		k1=fnc(yp1, k11, x);

        		k22=yp2+h/2*k1;
        		k2=fnc(yp1+h/2*k1, k22, x+h/2);

        		k33=yp2+h/2*k2;
        		k3=fnc(yp1+h/2*k2, k33, x+h/2);

        		k44=yp2+h*k2;
        		k4=fnc(yp1+h*k3, k44, x+h);

        		yp1=yp1+h/6*(k11+2*k22+2*k33+k44);
        		yp2=yp2+h/6*(k1+2*k2+2*k3+k4);

        		x+=h;
        	}
                last=yp1;

                yp1=y1;
                yp2=y2;
                x=StrToFloat(Form1->x1N->Text);
                h/=2;
                n=(StrToFloat(Form1->x2N->Text)-StrToFloat(Form1->x1N->Text))/h+h/2;
                for(i=0; i<n; i++){
        		k11=yp2;
        		k1=fnc(yp1, k11, x);

        		k22=yp2+h/2*k1;
        		k2=fnc(yp1+h/2*k1, k22, x+h/2);

        		k33=yp2+h/2*k2;
        		k3=fnc(yp1+h/2*k2, k33, x+h/2);

        		k44=yp2+h*k2;
        		k4=fnc(yp1+h*k3, k44, x+h);

        		yp1=yp1+h/6*(k11+2*k22+2*k33+k44);
        		yp2=yp2+h/6*(k1+2*k2+2*k3+k4);

        		x+=h;
                }
                next=yp1;

                d=next-last;
        }while(fabs(d)>e);//Проверка точности

        gh=h;
        //Востановление начальных параметров
        h=StrToFloat(Form1->hN->Text);
        n=(StrToFloat(Form1->x2N->Text)-StrToFloat(Form1->x1N->Text))/h+h/2;

	return yp1;
}
//---------------------------------------------------------------------------
//Нахождение Y' методом половинного деления
double mpd(double a, double b, double y){
	double c, f1, f2, f3;

	do{
		if(a>b){
			c=b;
			b=a;
			a=c;
		}

		f1=kutt(StrToFloat(Form1->y1N->Text), a, StrToFloat(Form1->x1N->Text));
		f2=kutt(StrToFloat(Form1->y1N->Text), b, StrToFloat(Form1->x1N->Text));
		c=(a+b)/2;
		f3=kutt(StrToFloat(Form1->y1N->Text), c, StrToFloat(Form1->x1N->Text));

		if((y>f1)&&(y<f3))b=c;else
		if((y>f3)&&(y<f2))a=c;

	}while(fabs(f3-y)>e);

	return c;
}
//---------------------------------------------------------------------------
//метод стрельб
double strelba(double y1, double y2, double a){
	double yp, k=y1, ks, kn=y1;
	int d=0;

	do{
		ks=k;
		k=kn;

		yp=kutt(y1, k, a);

		if(yp>y2)
			if(d!=2){kn-=h; d=1;}else d=3;

		if((yp<y2)&&(d!=3))
			if(d!=1){kn+=h; d=2;}else d=3;
	}while(d!=3);

	k=mpd(k, ks, y2);

	return k;
}
//---------------------------------------------------------------------------
//Вывод на экран результатов расчета
void kutt2(double yp1, double yp2, double x){
	double k1, k2, k3, k4;
        double k11, k22, k33, k44, gn, gx=StrToFloat(Form1->x1N->Text), y1=yp1, y2=yp2;
	int i, step;

        Form1->Memo1->Lines->Add("x="+Form1->x1N->Text+"; y="+FloatToStr(yp1));
        for(step=0; step<n; step++){
                gx+=h;
                gn=(gx-StrToFloat(Form1->x1N->Text))/gh;
                x=StrToFloat(Form1->x1N->Text);
                yp1=y1;
                yp2=y2;
                for(i=0; i<gn; i++){
                	k11=yp2;
                	k1=fnc(yp1, k11, x);

                        k22=yp2+gh/2*k1;
                	k2=fnc(yp1+gh/2*k1, k22, x+gh/2);

                        k33=yp2+gh/2*k2;
                	k3=fnc(yp1+gh/2*k2, k33, x+gh/2);

                	k44=yp2+gh*k2;
                	k4=fnc(yp1+gh*k3, k44, x+gh);

                	yp1=yp1+gh/6*(k11+2*k22+2*k33+k44);
                	yp2=yp2+gh/6*(k1+2*k2+2*k3+k4);

                	x+=gh;
                }
                Form1->Memo1->Lines->Add("x="+FloatToStr(gx)+"; y="+FloatToStr(yp1));
        }
}
//---------------------------------------------------------------------------
//Основная функция
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	double a, b, ydash, y1, y2, x;
	int i,my_time;

	Memo1->Lines->Clear();//Очистка экрана

        //Установка начальных значений
	y1=StrToFloat(y1N->Text);
	a=StrToFloat(x1N->Text);

	y2=StrToFloat(y2N->Text);
	b=StrToFloat(x2N->Text);

	h=StrToFloat(hN->Text);
	e=StrToFloat(eN->Text);

	n=(b-a)/h+h/2;


	ydash=strelba(y1, y2, a);//Запуск функции метода стрельб

	Memo1->Lines->Add("y'="+FloatToStr(ydash));//Вывод у'
	kutt2(y1, ydash, a);//Вывод значений на каждом шаге h
}
//---------------------------------------------------------------------------


