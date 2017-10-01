//---------------------------------------------------------------------------
#include <stdio.h>
#include <math.h>
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{ 	float f1,f2,f3,c,cc=0,a,b,e=0;
	int i=1;

	printf("Vvedite znachenia a i b 4erez probel: ");
	scanf("%f %f",&a, &b);
	printf("Uravnenie x^2-3=0\n");
	do
	{
		f1=a*a-3;
		f2=b*b-3;

		printf("\nSHAG[%2d]: Interval [%.8f,%.8f]",i++,a,b);
		c=(a*f2-b*f1)/(f2-f1);
		f3=c*c-c-4;
		printf("\n          C=%.8f\n",c);

		if((f1<0)&&(f3>0))b=c;
		if((f1>0)&&(f3<0)){b=a;a=c;}

		if((f2<0)&&(f3>0)){a=b;b=c;}
		if((f2>0)&&(f3<0))a=c;

		e=c-cc;
		cc=c;
	}while(!(fabs(e)<0.00000001));

	getchar();
	getchar();
	return 0;
}
//---------------------------------------------------------------------------
