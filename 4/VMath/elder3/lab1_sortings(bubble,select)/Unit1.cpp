//---------------------------------------------------------------------------
#include <vcl.h>
#include <time.h>
#include <stdlib.h>
#include <iostream.h>
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

void swap(int *a, int *b)
{
 int t;
 t=*a; *a=*b; *b=t;
}


int f=0,mas_count;

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
 int j;

 if(Edit1->Text > 0)  {
 StringGrid1->ColCount=StrToInt(Edit1->Text);

 for(j=0; j < StringGrid1->ColCount; j++)
 StringGrid1->Cells[j][0]=random(100);

 f=1;

 }

 else
 {
  StringGrid1->ColCount=1;
  StringGrid1->Cells[0][0]="";
 }

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
 int jPos,jMin,j,tmp,n;
 n=StringGrid1->ColCount;

 if(f != 0)
 {
 for(jPos=0; jPos < n; jPos++)
 {
  jMin=jPos;

  for(j=jPos+1; j < n; j++)
  {
   if(StrToInt(StringGrid1->Cells[j][0]) < StrToInt(StringGrid1->Cells[jMin][0])) jMin=j;
  }

  if(jMin != jPos)
  {
  tmp=StrToInt(StringGrid1->Cells[jMin][0]);
  StringGrid1->Cells[jMin][0]=StringGrid1->Cells[jPos][0];
 StringGrid1->Cells[jPos][0]=tmp;


  }
 }
 f=0;
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
 int k,jMin,j,tmp,n,flag=0;

 n=StringGrid1->ColCount;

 if(f!=0)
 {
 for(j=0; j < n; j++)
 {
  flag=0;
  for(k=n-1; k >= j+1; k--)
  {
   if(StrToInt(StringGrid1->Cells[k][0]) < StrToInt(StringGrid1->Cells[k-1][0]))
   {
    flag++;
    tmp=StrToInt(StringGrid1->Cells[k][0]);
    StringGrid1->Cells[k][0]=StringGrid1->Cells[k-1][0];
    StringGrid1->Cells[k-1][0]=tmp;
   }
  }
   if(flag==0) break;
 }
 f=0;
 }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
 int *a,*b,j,k=0;

 mas_count=StringGrid1->ColCount;

 a=(int*)malloc(sizeof(int)*(int)mas_count/2+1);
 b=(int*)malloc(sizeof(int)*(int)mas_count/2+1);

 for(j=0; j < mas_count; j++) if(j%2==0) {a[k]=StrToInt(StringGrid1->Cells[j][0]); k++;}
 k=0;
 for(j=0; j < mas_count; j++) if(j%2==1) {b[k]=StrToInt(StringGrid1->Cells[j][0]); k++; }

 StringGrid2->ColCount=int(mas_count/2)+1;
 StringGrid4->ColCount=int(mas_count/2)+1;

 StringGrid2->Visible=true;
 StringGrid4->Visible=true;

 for(j=0; j < mas_count/2+1; j++)
 {
  StringGrid2->Cells[j][0]=a[j];
  StringGrid4->Cells[j][0]=b[j];
 }


}
//---------------------------------------------------------------------------

