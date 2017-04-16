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
	printf("Lab 9 - Formula of Trapezoid\nEnter limits of integration\n\na: ");
   scanf("%lf", &a);
   printf("b: ");
   scanf("%lf", &b);
   putchar('\n');
   tmp_0=fnc(a);
   for(i=a+H; i<b+H; i+=H){
       res+=(tmp_0+(fnc(i)))/2.0;
       tmp_0=fnc(i);
   }
   printf("Result of General formula of Trapezoid:\n%.10lf\n", res*=H);
   res_1=res;
   do{
      res=res_1;
      res_1=0.0;
      tmp_0=fnc(a);
      for(i=a+h; i<b+h; i+=h){
      	res_1+=(tmp_0+fnc(i))/2.0;
         tmp_0=fnc(i);
      }
      res_1*=h;
      k++;
      h/=2.0;
   }while(dabs(res-res_1)>3*EPS);
   printf("\nResult of Method of double recalculation:\n%.10lf -- %d\n\nMethod of correction at double recalculation:\n%.10lf\n", res_1, k, res_1+(1.0/3.0)*(res_1-res));
   getchar();
	return 0;
}