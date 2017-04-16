//---------------------------------------------------------------------------

#include <vcl.h>
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


void __fastcall TForm1::Button1Click(TObject *Sender)
{
 AnsiString str1,str2,str3,temp_str;
 AnsiString z;
 int m1=0,m2=0,ii,k=1,t=0,p=0,w=0,i,j,r,l,m,n,s=0,x=-1;
 char ch;

 str1=Edit1->Text;
 str2=Edit2->Text;

 //

 if (str1[1] == '-') { m1=1; str1=str1.Delete(1,1); }
 if (str2[1] == '-') { m2=1; str2=str2.Delete(1,1); }

  l=str1.Length();
  r=str2.Length();
  m=r+l;

 // ShowMessage(m);

  for(i=0; i < m; i++)
  {
   str3+="0";
  }
//  ShowMessage(str3);
//  ShowMessage(str3[1]);
//  ShowMessage(str3[2]);
//  ShowMessage(str3[3]);
//  ShowMessage(str3[4]);

  k=m;

  for(i=r; i > 0; i--)
  {
   x++;
   k=m-x;
   for(j=l; j > 0; j--)
   {

//    ShowMessage("0 label");
    temp_str.sprintf("%d",StrToInt(str2[i])*StrToInt(str1[j]) );
//    ShowMessage(temp_str);
    n=temp_str.Length();
//    ShowMessage(n); //ShowMessage(n);
    // почему вот это не работает??? ShowMessage("k="+k);
//    ShowMessage(k);
    t=k;


    for(ii=n; ii > 0; ii--)
    {
     w=0;

//     ShowMessage("str3[t]=");
//     ShowMessage(str3[t]);
//     ShowMessage("temp_str[ii]=");
//     ShowMessage(temp_str[ii]);
//     ShowMessage("p=");
//     ShowMessage(p);

     s=StrToInt(str3[t])+StrToInt(temp_str[ii])+p;
//     ShowMessage("s="); ShowMessage(s);
     if(s > 9)
     {
//      ShowMessage("A label");
      do
      {
       s=StrToInt(str3[t-w])+StrToInt(temp_str[ii])+p;
//       ShowMessage(s);

       if(s > 9)
       {
//        ShowMessage("B label");
//        ShowMessage("str3[t-w]");
//        ShowMessage(str3[t-w]);
//        ShowMessage("temp");
//        ShowMessage(temp_str[ii]);

        s=StrToInt(str3[t-w])+StrToInt(temp_str[ii])+p-10;

//        ShowMessage("s="); // пизец!!!
//        ShowMessage(s);
        z=IntToStr(s);
//        ShowMessage(z);
//        ShowMessage(z[1]);
z=s;
      //ShowMessage(ch);


      str3[t-w]=z[1];
        p=1;

        s=0;
        z=s;

        temp_str[ii]=z[1];
       }

       else
       {
        s=StrToInt(str3[t-w])+StrToInt(temp_str[ii])+p;
//        ShowMessage("C2 label");
        z=s;
//        ShowMessage("C3 label");      /////аааа :((((
        str3[t-w]=z[1];
//        ShowMessage("C4 label");
//        ShowMessage(str3[t-w]);
        p=0;
       }
       w++;

//       ShowMessage("w=");
//       ShowMessage(w);

      }
      while(p != 0);
     }

     else
     {
      s=StrToInt(str3[t-w])+StrToInt(temp_str[ii])+p;
      z=s;
      str3[t]=z[1];
//      ShowMessage(str3[t]);
     }

     t--;

    }
//    ShowMessage(str3);

    k--;
   }
  }


 // Edit3->Text=str3;

 if( (m1==1 && m2==0) || (m1==0 && m2==1))
 {
  str3.Insert("-",1);
  Edit3->Text=str3;
 }
  else
  {
   Edit3->Text=str3;
  }
 }
//---------------------------------------------------------------------------



