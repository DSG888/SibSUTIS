#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define br putchar('\n');

int main()
{
 srand(time(NULL));   
    
 int i,j=0,n,U,V,W,XY,a_,b_,c_,d_,x0=0,x1=0,y0=0,y1=0;
 char *X,*Y,*a,*b,*c,*d,ed,*p,*q;
 
 scanf("%d",&n);
 
 X=new char [n+1]; // +1 is '\0'
 Y=new char [n+1];
 a=new char [n/2+1];
 b=new char [n/2+1];
 c=new char [n/2+1];
 d=new char [n/2+1];
 p=new char [n+1];
 q=new char [n+1];
 
 X[n+1]='\0'; 
 Y[n+1]='\0';
 *(a+n/2+1)='\0'; 
 *(b+n/2+1)='\0';
 *(c+n/2+1)='\0'; 
 *(d+n/2+1)='\0'; 
 *(q+n+1)='\0';
 *(p+n+1)='\0'; 
 
 /////////////////////////////////////////////////////////////////////////////////////
 
 scanf("%s %s",X,Y);
 printf("\n\nX=%s Y=%s",X,Y); 

 br;
 
 for(i=0; i < n/2; i++) {a[i]=X[i]; c[i]=Y[i]; }
 for(i=0; i < n/2; i++) {b[i]=X[i+n/2]; d[i]=Y[i+n/2];}
 
 br;   
 
 printf("%s %s %s %s",a,b,c,d);
 
 a_=atoi(a);
 b_=atoi(b);
 c_=atoi(c);
 d_=atoi(d);
 
 V=a_*c_;
 W=b_*d_;
 U=(a_+b_)*(c_+d_);
    
 printf("\n\nV=%d*%d=%d\nW=%d*%d=%d\nU=(%d+%d)(%d+%d)=%d]",a_,c_,V=a_*c_,b_,d_,W=b_*d_,a_,b_,c_,d_,U);  
 
 br;
 
 sprintf(p,"%d",a_+b_);
 sprintf(q,"%d",c_+d_);
 
 br;
  
    if(strlen(p) > n/2) {x0=1; j=1;}
    else x0=0;          
    if(x0 > 0){for(i=0; i < strlen(p); i++) {p[i]=p[i+1];}}
    x1=atoi(p);
    // -- //
    if(strlen(q) > n/2) {y0=1; j=1;}
    else y0=0;
    if(y0 > 0){for(i=0; i < strlen(q); i++) {q[i]=q[i+1];}}
    y1=atoi(q);
    
    printf("||x0=%d x1=%d y0=%d y1=%d||",x0,x1,y0,y1);
    
 if(j > 0)
 {
  U=x0*y0*(int)pow(10,2)+(x0*y1+y0*x1)*(int)pow(10,1)+x1*y1;
  printf("\nU=%d*%d*%d+(%d*%d+%d*%d)*%d+%d*%d=%d\n",x0,y0,(int)pow(10,2),x0,y1,y0,x1,(int)pow(10,1),x1,y1,U);                             // формула расчета U при переполнении
 }
 
 printf("Result=%d",XY=V*(int)pow(10,2)+(U-V-W)*(int)pow(10,1)+W);
 
 getch(); return 0;
}
