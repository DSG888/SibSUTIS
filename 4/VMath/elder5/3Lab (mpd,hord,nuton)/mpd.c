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

int main() 
{ 
    double xLeft = 1, xRight = 2; 
    double xMiddle; 
    int i = 1;
    double epsilon = 0.00001; 
    printf("Начальный интервал [%12.9lf; %12.9lf]\n\n", xLeft, xRight);
    xMiddle = (xLeft + xRight) / 2; 

    while(fabs(xRight - xLeft) > epsilon) 
    { 
       	    printf("Шаг = %d, cредний элемент = %12.9lf\n", i, xMiddle); //вывод среднего
        if ( f(xLeft) * f(xMiddle) < 0) 
            xRight = xMiddle; 
        else if (f(xRight) * f(xMiddle) < 0) 
            xLeft = xMiddle;
        printf("Интервал [%12.9lf; %12.9lf]\n\n", xLeft, xRight);
        xMiddle = (xLeft + xRight) / 2;  
        i++;
      } 

      printf("x = %12.15lf\n", xMiddle);

	  return 0;
}

