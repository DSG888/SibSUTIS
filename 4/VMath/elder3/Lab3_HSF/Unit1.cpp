//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define pi 3.1415926535
TForm1 *Form1;
float *mas;
int N;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
 int i;
 N=StrToInt(Edit1->Text);
 mas=new float [N];

Memo1->Lines->Clear();
for (i=0; i<N; i++){
        mas[i]=random(100);
        Memo1->Lines->Append(FloatToStr(mas[i]));
               }
}

//---------------------------------------------------------------------------
/* ceil

*/


void __fastcall TForm1::Button3Click(TObject *Sender)
{
AnsiString str;
float **A;
int CMP=0;
int k,p1,p2,k1,j1,j2;
float arg;
float *A_d, *A_m;

A=(float**)malloc(sizeof(float*)*2);
A[0]=(float*)malloc(sizeof(float)*N);
A[1]=(float*)malloc(sizeof(float)*N);


p1=(int)ceil(sqrt(N));
p2=N/p1;
if (p1*p2!=N) { ShowMessage("Error!!!"); return; }
A_d=(float *)malloc(p1*p2*sizeof(float));
A_m=(float *)malloc(p1*p2*sizeof(float));
Memo4->Lines->Clear();

for (k1=0; k1<p1; k1++)
        for (j2=0; j2<p2; j2++){
*(A_d+k1*p2+j2)=0.0; // k1=0, j2=0: 0+0*4+0; k1=0, j2=1: 0+0*4+1; k1=0, j2=2: 0+0*4+2; j2=3: 0+0*4+3;
// k1=1, j2=0: 0+1*4+0; k1=1, j2=1: 0+1*4+1(5); k1=1, j2=2: 0+1*4+2(6); k1=1, j2=3: 0+1*4+3(7)
// k1=2, j2=0: 0+2*4+0;
*(A_m+k1*p2+j2)=0.0;
  for (j1=0; j1<p1; j1++){
                 CMP++;
                 arg=(-2)*pi*k1*j1/p1;
                 *(A_d+k1*p2+j2)+=mas[j2+j1*p2]*cos(arg);
                 *(A_m+k1*p2+j2)+=mas[j2+j1*p2]*sin(arg);

                 /* k1=1
                    j2=0, j1=0: 0+0*4(0); j2=0, j1=1: 0+1*4(4); j2=0, j1=2: 0+2*4(8) ...
                    j2=1, j1=0: 1+0*4(1) ... (5)... (9) ... (13)
                    j2=2, ... : (2) .. (6) .. (10) .. (14)
                    j2=3, ... : (3) .. (7) .. (11) .. (15)

                    k1=2
                    ...
                  */

                 }
                *(A_d+k1*p2+j2)/=p1;
                *(A_m+k1*p2+j2)/=p2;
                }

for (k=0; k<N; k++){   // N*p операций эквивалетно p*p*p операциям
        A[0][k]=0.0; // [] [N]
        A[1][k]=0.0;
        k1=k%p1; // k=0: k1=0, k=1: k1=1, k=2: k1=2, k=3: k1=3, // k=4: k1=0  .  .  .

        for (j2=0; j2<p2; j2++){
                CMP++;
                arg=(-2)*pi*j2/N*k; // N=p1*p2, k=k1*p1*k
                /* (a+bi)*e^iф=(a+bi)*(cosф+isinф)=(a+bi)*(c+di) ... --> ... (ac-bd)+i(ad+bc) */
                A[0][k]+=*(A_d+k1*p2+j2)*cos(arg)-*(A_m+k1*p2+j2)*sin(arg);  // (ac-bd)
                A[1][k]+=*(A_m+k1*p2+j2)*cos(arg)+*(A_d+k1*p2+j2)*sin(arg);  // (ad+bc)

                //  A{0,1,2,3 | 4,5,6,7 | 8,9,10,11 | 12,13,14,15 || 0,1,2,3 .... || ... || ...}
                // A04 = sum(A 0,1,2,3), A05= sum(

                }
        A[0][k]/=p2;
        A[1][k]/=p2;
        str.printf("%5.5f+i(%5.5f)",A[0][k],A[1][k]);
        Memo4->Lines->Append(str);
        }

Memo5->Lines->Clear();
Label2->Caption=IntToStr(CMP);

for (k1=0; k1<p1; k1++)
        for (j2=0; j2<p2; j2++){
                *(A_d+k1*p2+j2)=0.0;
                *(A_m+k1*p2+j2)=0.0;
                for (j1=0; j1<p1; j1++){
                        arg=2*pi*k1*j1/p1;
                        *(A_d+k1*p2+j2)+=A[0][j2+j1*p2]*cos(arg)-A[1][j2+j1*p2]*sin(arg);
                        *(A_m+k1*p2+j2)+=A[1][j2+j1*p2]*cos(arg)+A[0][j2+j1*p2]*sin(arg);
                        }
                }

for(k=0; k<N; k++){
        A[0][k]=0.0;
        A[1][k]=0.0;
        k1=k%p1;

        for (j2=0; j2<p2; j2++){
                arg=2*pi*k*j2/N;
                A[0][k]+=*(A_d+k1*p2+j2)*cos(arg)-*(A_m+k1*p2+j2)*sin(arg);
                A[1][k]+=*(A_m+k1*p2+j2)*cos(arg)+*(A_d+k1*p2+j2)*sin(arg);
                }

        str.printf("%5.5f",A[0][k]);
        Memo5->Lines->Append(str);
        }

Memo4->Show();
Memo5->Show();
}
//---------------------------------------------------------------------------


