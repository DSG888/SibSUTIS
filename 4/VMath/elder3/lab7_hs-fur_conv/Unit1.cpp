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
int p1,p2;
//#define pi 3.14
#define pi 3.1415926535897

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

void FT(double *f, double **A, double *fd, double *fm, int n) // result A
{
 int k1,j2,k,p1=sqrt(n),p2=sqrt(n),j1;
 double arg;

 for (k1=0; k1<p1; k1++)
  for (j2=0; j2<p2; j2++)
  {
   *(fd+k1*p2+j2)=0.0;
   *(fm+k1*p2+j2)=0.0;
   for (j1=0; j1<p1; j1++)
   {
    arg=(-2)*pi*k1*j1/p1;
    *(fd+k1*p2+j2)+=f[j2+j1*p2]*cos(arg);
    *(fm+k1*p2+j2)+=f[j2+j1*p2]*sin(arg);
   }
   *(fd+k1*p2+j2)/=p1;
   *(fm+k1*p2+j2)/=p2;
  }


 for (k=0; k<n; k++){   // N*p операций эквивалетно p*p*p операциям
  A[0][k]=0.0; // [] [N]
  A[1][k]=0.0;

  k1=k%p1; // k=0: k1=0, k=1: k1=1, k=2: k1=2, k=3: k1=3, // k=4: k1=0  .  .  .

  for (j2=0; j2<p2; j2++){
   arg=(-2)*pi*j2/n*k; // N=p1*p2, k=k1*p1*k
   A[0][k]+=*(fd+k1*p2+j2)*cos(arg)-*(fm+k1*p2+j2)*sin(arg);  // (ac-bd)
   A[1][k]+=*(fm+k1*p2+j2)*cos(arg)+*(fd+k1*p2+j2)*sin(arg);  // (ad+bc)

                }
        A[0][k]/=p2;
        A[1][k]/=p2;
        //str.printf("%5.5f+i(%5.5f)",A[0][k],A[1][k]);
        //Memo4->Lines->Append(str);
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

void IFT2(double *fd, double *fm, double **A, int n)  // void IFT2(double *fd, double *fm, int n, double **A)
{
 int k,k1,j2,p1=sqrt(n),p2=sqrt(n),j1;
 double arg;
 
for (k1=0; k1<p1; k1++)
        for (j2=0; j2<p2; j2++){
                *(fd+k1*p2+j2)=0.0;
                *(fm+k1*p2+j2)=0.0;
                for (j1=0; j1<p1; j1++){
                        arg=2*pi*k1*j1/p1;
                        *(fd+k1*p2+j2)+=A[0][j2+j1*p2]*cos(arg)-A[1][j2+j1*p2]*sin(arg);
                        *(fm+k1*p2+j2)+=A[1][j2+j1*p2]*cos(arg)+A[0][j2+j1*p2]*sin(arg);
                        }
                }

for(k=0; k<n; k++){
        A[0][k]=0.0;
        A[1][k]=0.0;
        k1=k%p1;

        for (j2=0; j2<p2; j2++){
                arg=2*pi*k*j2/n;
                A[0][k]+=*(fd+k1*p2+j2)*cos(arg)-*(fm+k1*p2+j2)*sin(arg);
                A[1][k]+=*(fm+k1*p2+j2)*cos(arg)+*(fd+k1*p2+j2)*sin(arg);
                }

       // str.printf("%5.5f",A[0][k]);
      //  Memo5->Lines->Append(str);
        }
 
}

void conv(double **A, double **B, double *fc, double *fc_, int n)
{
 for(int i=0;i<n;i++)
 {
  fc[i]=n*(A[0][i]*B[0][i]-A[1][i]*B[1][i]); // действительная
  fc_[i]=n*(A[0][i]*B[1][i]+A[1][i]*B[0][i]);                 // мнимая
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

 double *a, *b, *c, *C, *fa, *fa_, *fb, *fb_, *fc, *fc_, *ifa, *ifa_, *ifb, *ifb_, *ifc, *ifc_, **A, **B;
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

 A=(double**)malloc(sizeof(double*)*2);
 A[0]=(double*)malloc(sizeof(double)*n);
 A[1]=(double*)malloc(sizeof(double)*n);

 B=(double**)malloc(sizeof(double*)*2);
 B[0]=(double*)malloc(sizeof(double)*n);
 B[1]=(double*)malloc(sizeof(double)*n);

 randomize();

 FT(a,A,fa,fa_,n);      // void FT(double *f, double **A, double *fd, double *fm, int n)
 FT(b,B,fb,fb_,n);
// print_fur(fa,fa_,n,clGreen,0);
// print_fur(fb,fb_,n,clRed,0);

//RichEdit1->Lines->Add("==================================================");

// IFT2(fa,fa_,A,n);      //void IFT2(double *fd, double *fm, double **A, int n)
// IFT2(fb,fb_,B,n);
 
// print_fur(ifa,ifa_,n,clBlue,1);
// print_fur(ifb,ifb_,n,clBlue,1);

//RichEdit1->Lines->Add("==================================================");

 conv(A,B,fc,fc_,n);       //  void conv(double **A, double **B, double *fc, double *fc_, int n)
// print_fur(fc,fc_,n,clTeal,0);



//RichEdit1->Lines->Add("==================================================");

 IFT(fc,fc_,ifa,ifa_,n);
 print_fur(ifa,ifa_,n-1,clBlack,1);


 }
