//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
AnsiString str;
#define pi 3.14

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
 srand(time(NULL));
}
//---------------------------------------------------------------------------
void fill_rand2(double *x, int n)
{
 for(int i=0;i<n;i++){x[i]=random(100)+1;}
}


void print(double *x, int n, TColor cl){
     AnsiString s;
     for(int i=0; i<n; i++){
        s+=x[i];
        s+=' ';
     }
     Form1->RichEdit1->SelAttributes->Color=cl;
     Form1->RichEdit1->Lines->Add(s);
}

void print_fur(double *fd, double *fm, int n, TColor cl, int f)
{
 AnsiString str="";
 int i;

 if(f==0) // выводим прямое
 {
  for(i=0; i < n; i++)
  {
   str.sprintf("%f+i(%f)",fd[i],fm[i]);

   Form1->RichEdit1->SelAttributes->Color=cl;
   Form1->RichEdit1->Lines->Add(str);
  }
 }
 else
 {
  for(i=0; i < n; i++)
  {
   str.sprintf("%f",fd[i]);

   Form1->RichEdit1->SelAttributes->Color=cl;
   Form1->RichEdit1->Lines->Add(str);
  }
 }
}

void FT(double *f, double *fd, double *fm, int n)
{
 int k,j;
 double arg;
 for(k=0; k<n; k++)
 {
  fd[k]=0;
  fm[k]=0;
  for(j=0; j<n; j++)
  {
   arg=-2*pi*k*j/n;
   fd[k]+=cos(arg)*f[j];
   fm[k]+=sin(arg)*f[j];
  }
 fd[k]/=n;
 fm[k]/=n;
 }
}

void IFT(double *fd, double *fm, double *ifd, double *ifm, int n)
{
 int k,j;
 double arg;

 for(k=0; k<n; k++)
 {
  ifd[k]=0;
  ifm[k]=0;
  for(j=0; j<n; j++)
  {
   arg=2*pi*k*j/n;
   ifd[k]+=cos(arg)*fd[j]-sin(arg)*fm[j];
   ifm[k]+=cos(arg)*fm[j]+sin(arg)*fd[j];
  }
 }
}

void conv(double *fa, double *fa_, double *fb, double *fb_, double *fc, double *fc_, int n)
{
 for(int i=0;i<n;i++)
 {
  fc[i]=n*(fa[i]*fb[i]-fa_[i]*fb_[i]); // действительная
  fc_[i]=n*(fa[i]*fb_[i]+fa_[i]*fb[i]);                 // мнимая
 }
}

//---------------------------------------------------------------------------



// US CONV //
void fill_rand(int count,double *N, TColor p)
{
 int i;
 for(i=0; i < count/2; i++)
 {
  N[i]=rand()%90+10;
  str+=N[i];
  str+=" ";
 }

 for(i=count/2; i < count; i++) {
 N[i]=0;
str+=N[i];
  str+=" ";
  }

 Form1->RichEdit1->SelAttributes->Color=p;
 Form1->RichEdit1->SelAttributes->Size=14;
 Form1->RichEdit1->SelAttributes->Style << fsBold;
 Form1->RichEdit1->Lines->Add(str);

}

// **************************************************************************

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
 srand(time(NULL));
                               // n двойного РАЗМЕРА //
 int n,count;

 double *a, *b, *c, *C, *fa, *fa_, *fb, *fb_, *fc, *fc_, *ifa, *ifa_, *ifb, *ifb_, *ifc, *ifc_;
                                                // _ мнимая
 int i,l,k,sum;

 Form1->RichEdit1->Clear();

 if(StrToInt(Edit1->Text) > 0) n=2*StrToInt(Edit1->Text);

 ShowMessage(n);

 a=new double[n];
 b=new double[n];
 C=new double[n];

 //count=2*n-2;

 str="A -> ";
 fill_rand(n,a,clBlue);
 str="B -> ";
 fill_rand(n,b,clBlue);

 //ShowMessage(2*(n-1)/2);

 for(i=0;;i++)
 {
  if(i >= (2*n-1)/2) break;
  Form1->RichEdit1->SelAttributes->Size=12;
  sum=0;
  str="C";
  str=str+i+" -> ";

  for(k=0; k < n/2; k++)
  {
   for(l=0; l < n/2; l++)
   {
    if( (k+l) == i){
    sum+=a[k]*b[l];
    str=str+"A"+k+"*"+"B"+l;
    str+="+";       }
   }
  }
  str=str.Delete(str.Length(),1);
  str=str+"="+sum;
  RichEdit1->Lines->Add(str);
 }

 RichEdit1->Lines->Add("==================================================");
// //// ///////////////////////////////////////////////////////////////////


 fa=new double [n];
 fa_=new double [n];
 fb=new double [n];
 fb_=new double [n];
 fc=new double [n];
 fc_=new double [n];

 ifa=new double [n];
 ifa_=new double [n];
 ifb=new double [n];
 ifb_=new double [n];

 randomize();

 FT(a,fa,fa_,n);
 FT(b,fb,fb_,n);
// print_fur(fa,fa_,n,clGreen,0);
// print_fur(fb,fb_,n,clRed,0);

//RichEdit1->Lines->Add("==================================================");

 IFT(fa,fa_,ifa,ifa_,n);
 IFT(fb,fb_,ifb,ifb_,n);
// print_fur(ifa,ifa_,n,clBlue,1);
// print_fur(ifb,ifb_,n,clBlue,1);

//RichEdit1->Lines->Add("==================================================");

 conv(fa,fa_,fb,fb_,fc,fc_,n);
// print_fur(fc,fc_,n,clTeal,0);



//RichEdit1->Lines->Add("==================================================");

 IFT(fc,fc_,ifa,ifa_,n);
 print_fur(ifa,ifa_,n-1,clBlack,1);

 /*

free(ifa);
free(ifa_);
free(ifb_);
free(ifb);
free(a);
free(b);
free(ifc);
free(ifc_);

      */



 }



//---------------------------------------------------------------------------
/*
AnsiString Name="http://devoid.com.ua";
Name="-="+Name+"=-";
Label1->Caption=Name;
*/
