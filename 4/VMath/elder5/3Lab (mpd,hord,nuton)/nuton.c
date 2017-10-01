#include <math.h> 
#include <stdio.h>

double roots(double *xLeft, double *xRight)
{
    double a = 1, b = 1, c = -10, x1, x2;
    if((b * b - 4 * a * c) >= 0) 
    {
        x1 = ( -1*b + sqrt(b*b - 4*a*c) ) / (2 * a);
        printf("Первый корень равен = %lf\n", x1);
        
        x2 = ( -1*b - sqrt(b*b - 4*a*c) ) / (2 * a);
        printf("Второй корень равен = %lf\n", x2);
       
    }
    else
    {
        printf("Дискриминант меньше 0, корни невещественные.");
    }

    if (x1 > x2) {
        *xLeft = floor(x1);
        *xRight = ceil(x1);
   
    }
    else {
        *xLeft = floor(x1);
        *xRight = ceil(x1);
        
    }
    return 0;
} 


double f(double x) 
{ 
      return (x*x) - 2; 
} 

double f1(double x) 
{ 
      return 2*x;
} 

int main() 
{ 
    double xLeft = 1, xRight = 2, ysl, staroe; 
    double xMiddle;
    int i = 1;
    double epsilon = 0.00001; 
    printf("Начальный интервал [%lf; %lf]\n\n", xLeft, xRight);
    xMiddle = -(f(xLeft) / f1(xLeft)) + xLeft;
    ysl = xMiddle;
    while(fabs(ysl) > epsilon) 
    { 
        staroe = xMiddle;
        printf("Шаг = %d, cредний элемент = %12.15lf\n", i, xMiddle); //вывод среднего
        xMiddle = -(f(xMiddle) / f1(xMiddle)) + xMiddle;
        ysl = xMiddle - staroe;
        i++;
      } 

      printf("x = %12.15lf\n", xMiddle);

	  return 0;
}
