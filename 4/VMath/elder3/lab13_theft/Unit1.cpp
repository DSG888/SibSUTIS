//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int n=0, max=0;
TStringList* str1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
 Panel3->Color=RGB(100,255,100);
}
//---------------------------------------------------------------------------
int maxx(int a, int b)
{
 if(a >= b) return a;
 else return b;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N1Click(TObject *Sender)
{
 AnsiString s;
 int *m, *c, *cc, *f, *g, ff, i, j, k, p=0, w;  /// w - count



 str1=new TStringList();
 RichEdit2->Clear();

 n=Edit1->Text.ToInt();

// ShowMessage(n);


 max=Edit2->Text.ToInt();
 m=new int [n+1];
 c=new int [n];
 cc=new int [n];
 f=new int [max+1];
 g=new int [max+1];

 s="";

// str1->Delimiter=' ';

 str1->CommaText=RichEdit1->Lines->Text;

 //ShowMessage(str1->Strings[0]);

 //ShowMessage(str1->Strings[0]);

 for(i=0; i < n; i++)
 {
  m[i]=str1->Strings[i].ToInt();
  c[i]=str1->Strings[i+n].ToInt();
 }


 for(i=0; i <= max; i++)
 {
  f[i]=0;

  for(j=0; j < n ; j++)
  {
   if(m[j] <= i)
   {
    f[i]=maxx(f[i],f[i-m[j]]+c[j]);
   }
  }
    s="f";
    s+="(";
    s+=(i);
    s+=")";
    s+="=";
    s+=f[i];
    Form1->RichEdit2->Lines->Add(s);
 }

 /// reverse

 for(i=0; i <= max; i++)
 {
  g[i]=0;
 }

for(i=0; i < n; i++)
 {
  cc[i]=0;
 }

 k=n;
 m[k]=0;
 p=0;

 i=max;
// ff=0;

 while(i-p > 0)
 {
  //ShowMessage(i-p);
  i=i-p;
  //ShowMessage("i=");
  //ShowMessage(i);

  for(j=0; j < n ; j++)
  {
   if( (i-m[j] >= 0) && (g[i] <= f[i-m[j]]+c[j])   )
   {
    ff=1;
    g[i]=f[i-m[j]]+c[j];
    k=j;
  //  ShowMessage("k=");
  //  ShowMessage(k);
   }
  }
   if(ff) {cc[k] += 1; ff=0;}
   p=m[k];
  // f=0;   разобраться


 }

 AnsiString zz;

 for(k=0; k < n; k++)
 {
  if(cc[k] != 0)
  {
  zz = k+1;
  zz +=" tovar=";
  zz += c[k];
  zz += " po ";
  zz += cc[k];
 // ShowMessage(cc[k]);
 // ShowMessage(c[k]);
  ShowMessage(zz);
  }
  zz="";
 }

}
//---------------------------------------------------------------------------


