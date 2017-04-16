#include <stdio.h>

#define EPS 0.00000001
#define H 0.1

double fnc(double a)
{
	return 1/a;
}

double dabs(double b)
{
	if(b<0.0)return -b;
   return b;
}

int main()
{
	double a, b, res=0.0, res_1=0.0, i, tmp_0, tmp_1, h=H/2.0;
   int k=0;
	printf("Lab 9 - Formula of Simson\nEnter limits of integration\n\na: ");
   scanf("%lf", &a);
   printf("b: ");
   scanf("%lf", &b);
   putchar('\n');
   for(i=a; i<b-H; i+=2.0*H)
       res+=(1.0/6.0)*fnc(i)+(2.0/3.0)*fnc(i+H)+(1.0/6.0)*fnc(i+2*H);
   printf("General Formula of Simson:\n%.10lf\n", res*=(2*H));
   res_1=res;
   do{
      res=res_1;
      res_1=0.0;
      for(i=a; i<b-h; i+=2.0*h)
       res_1+=(1.0/6.0)*fnc(i)+(2.0/3.0)*fnc(i+h)+(1.0/6.0)*fnc(i+2*h);
      res_1*=(2*h);
      k++;
      h/=2.0;
   }while(dabs(res-res_1)>15*EPS);
   printf("\nResult of Method of double recalculation:\n%.10lf -- %d\n\nMethod of correction at double recalculation:\n%.10lf\n", res_1, k, res_1+(1.0/5.0)*(res_1-res));
	return 0;
}
