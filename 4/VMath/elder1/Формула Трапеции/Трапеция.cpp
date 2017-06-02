#include <stdio.h>
//#include <graphics.h>
#include <conio.h>
//#include <math.h>
int nain() {
    float x[10],y[10],y0,x0 = 2,y1 = 2,h = 1,a,b,c;
    int i ;//значение пр. ф-ии х*х в точке х0=0
    printf("Эйлер");
    a = 1; b = 0;c=0;
   // y1 = 2*a*x0 + b; 
  // y0 = a*x0*x0 + b*x0 +c;
    y[0] = y0;
    x[0] = x0;
   for(i=0;i<8;i++){
                    y1 = 2*a*x[i] + b; 
                     y[i+1] = y[i] + y1;
                     printf("%g",y[i]);
                     }
                     getch ();
                     scanf("%f",&a);
                     return 0;
                     }
    
