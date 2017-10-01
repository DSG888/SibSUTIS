//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <math.h>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
double fnc(double x){
	return 1/x;
}

double fact(double n){
	int i, fac=1;
	for(i=2; i<=n; i++)fac*=i;
	return fac;
}

double okr(double x,int p){
	int i;
	for(i=0;i<p;i++)x*=10;
        i=x;
	x=i;
	for(i=0;i<p;i++)x=x/10;
	return x;
}

double max(double xoy[],int n){
	int i;
	float m;

	m=xoy[0];
	for(i=1;i<n;i++)if(xoy[i]>m)m=xoy[i];

	return m;
}

//рисование оси XY
void osi(double x[],double y[],int n,double kfx,double kfy){
	int i,j;
	Form1->PaintBox1->Refresh();
	Form1->PaintBox1->Canvas->Pen->Width=2;
	Form1->PaintBox1->Canvas->Pen->Color=clBlack;
	Form1->PaintBox1->Canvas->Rectangle(0, 0, 501, 501);

	//ось У
	Form1->PaintBox1->Canvas->MoveTo(250,0);
	Form1->PaintBox1->Canvas->LineTo(250,500);
	//Стрелка оси У
	Form1->PaintBox1->Canvas->MoveTo(245,5);
	Form1->PaintBox1->Canvas->LineTo(250,0);
	Form1->PaintBox1->Canvas->LineTo(255,5);
	Form1->PaintBox1->Canvas->TextOutA(235,3,"Y");

	//ось Х
	Form1->PaintBox1->Canvas->MoveTo(5,250);
	Form1->PaintBox1->Canvas->LineTo(498,250);

	//стрелка оси Х
	Form1->PaintBox1->Canvas->MoveTo(493,245);
	Form1->PaintBox1->Canvas->LineTo(498,250);
	Form1->PaintBox1->Canvas->LineTo(493,255);
	Form1->PaintBox1->Canvas->TextOutA(492,260,"X");

	Form1->PaintBox1->Canvas->Pen->Width=1;
	Form1->PaintBox1->Canvas->Pen->Color=clBlue;

	//координатные точки
	for(i=0;i<n;i++){
		//деления на оси Y
		Form1->PaintBox1->Canvas->MoveTo(245,250-y[i]*kfy);
		Form1->PaintBox1->Canvas->LineTo(255,250-y[i]*kfy);
		//нумерование делений
		Form1->PaintBox1->Canvas->TextOutA(215,244-y[i]*kfy,okr(y[i],2));

		//деления на оси X
		Form1->PaintBox1->Canvas->MoveTo(250+x[i]*kfx,245);
		Form1->PaintBox1->Canvas->LineTo(250+x[i]*kfx,255);
		//нумерование делений
		Form1->PaintBox1->Canvas->TextOutA(242+x[i]*kfx,257,okr(x[i],2));

		//круглешки
		Form1->PaintBox1->Canvas->Ellipse(248+x[i]*kfx,248-y[i]*kfy,253+x[i]*kfx,253-y[i]*kfy);
	}
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	int i,j,n;
	double X,p,chl,znm,kfx,kfy,x[20],y[20];
	FILE *f;

	if((f=fopen("x.txt","r"))==NULL)Abort();//Открытие файла

	fscanf(f,"%d",&n);//считывание количества Х

	//Считывание Х из файла в массив
	for(i=0;!feof(f);i++){
		if(feof(f))break;
		fscanf(f,"%lf",&x[i]);
		y[i]=fnc(x[i]);
	}

	kfx=240/max(x, n);//максимальный Х
	kfy=240/max(y, n);//максимальный У


	osi(x,y,n,kfx,kfy);

	//Вывод значений X и Y
	Memo1->Clear();
	for(i=0; i<n; i++)Memo1->Lines->Add("X"+IntToStr(i+1)+"="+FloatToStr(okr(x[i],3))+"  Y"+IntToStr(i+1)+"="+FloatToStr(okr(y[i],3)));//вывод ХY

	PaintBox1->Canvas->Pen->Width=1;
	PaintBox1->Canvas->Pen->Color=clRed;
	/*Интерполяция*/
	PaintBox1->Canvas->MoveTo(250+x[0]*kfx,250-y[0]*kfy);
	for(X=x[0]; X<=x[n-1]; X+=0.01)
	{
		p=0;
		chl=1;
		znm=1;

		for(j=0;j<n;j++)
		{

			for(i=0;i<n;i++)
				if(i!=j)
				{
					chl*=X-x[i];
					znm*=x[j]-x[i];
				}

			p+=y[j]*(chl/znm);
			chl=1;
			znm=1;
		}
		PaintBox1->Canvas->LineTo(250+X*kfx,250-p*kfy);
	}
	fclose(f);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	FILE *f;
	int i, j, n, k=1;
	double X, p, kfx, kfy, x[30], y[30][30], yy[30], q, nq=1, h=0.5;

	if((f=fopen("x.txt","r"))==NULL)Abort();//Открытие файла
        memset(y, 0, sizeof(double)*900);

	fscanf(f,"%d",&n);//считывание количества Х

	//Считывание Х из файла в массив
	for(i=0;i<n;i++){
		if(feof(f))break;
		fscanf(f,"%lf",&x[i]);
		yy[i]=y[i][0]=fnc(x[i]);
	}

	//Вывод значений X и Y
	Memo1->Clear();
	for(i=0; i<n; i++)Memo1->Lines->Add("X"+IntToStr(i+1)+"="+FloatToStr(okr(x[i],3))+"  Y"+IntToStr(i+1)+"="+FloatToStr(okr(yy[i],3)));//вывод ХY

	kfx=240/max(x, n);//максимальный Х
	kfy=240/max(yy, n);//максимальный У

	//вывод оси
	osi(x,yy,n,kfx,kfy);

	//Нахождение дельта Y
	for(i=k=1; i<n; i++){
		for(j=0; j<n-k; j++)y[j][i]=y[j+1][i-1]-y[j][i-1];
		++k;
	}

        //Вывод y и дельта y
        for(i=0, k=0; i<n; i++){
		for(j=0; j<n-k; j++)StringGrid1->Cells[i+1][j+1]=FloatToStr(y[j][i]);
                ++k;
        }

	PaintBox1->Canvas->Pen->Width=1;
	PaintBox1->Canvas->Pen->Color=clRed;
	//итерполяция Ньютона
	PaintBox1->Canvas->MoveTo(250+x[0]*kfx,250-y[0][0]*kfy);
	for(X=x[0]; X<=x[n-1]; X+=0.01){
		p=yy[0];
		nq=1;
		q=(X-x[0])/h;//расчет q
		for(i=1; i<n; i++){
			nq*=q-(i-1);//расчет q(q-1)...(q-(n-1))
			p+=y[0][i]/fact(i)*nq;
		}
		PaintBox1->Canvas->LineTo(250+X*kfx,250-p*kfy);
	}
}
//---------------------------------------------------------------------------
