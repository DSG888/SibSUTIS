//---------------------------------------------------------------------------
#include <stdio.h>
#include <math.h>
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{  	float f1,f2,f3,c,a,b,e;
	int i=1;

	printf("Vvedite znachenia a i b 4erez probel: ");
	scanf("%f %f",&a, &b);
	printf("Uravnenie x^2-x-4=0\n");
	do
	{
		f1=a*a-a-4;
		f2=b*b-b-4;

		printf("\n  SHAG[%d]: Interval: [%.8f,%.8f]",i++,a,b);
		c=(a+b)/2;
		f3=c*c-c-4;
		printf("\n            C=%f\n",c);

	   /*	if((f1<0)&&(f3>0))b=c;else
		if((f1>0)&&(f3<0)){b=a;a=c;}else

		if((f2<0)&&(f3>0)){a=b;b=c;}else
		if((f2>0)&&(f3<0))a=c;  */
        if(f1*f3<0)b=c;else
        if(f3*f2<0)a=c;

		e=(b-a)/2;
	}while(!(0.0001>fabs(e)));

	getchar();
	getchar();

	return 0;
}
//---------------------------------------------------------------------------
