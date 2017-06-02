#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

#define a 1
#define b 2
#define h0 0.1
#define E 0.001

double f(double x) {
    return 1/x;
}

double tr(float h)  {
    double I,S=0,i;
    int n;
    for(i=a;i<=b; i+=h)
        S+=f(i);
    S-=f(a)/2-f(b)/2;
    I=h*S;
    return I;
}

int main() {
    int i,j,n,c;
    float H,h;
    double I1,I2,I3;
    printf("Formula trapecii\n\n\n");
    printf("\n\nRaschet po formule trapezii  %.5f\n\n\n",tr(h0));
    do {
        I1=I2;
        I2=tr(h);
        h=h/2;
    } while(fabs((I1-I2))>(3*E));
    printf("Po formule peresheta  %.7f \n",I2);
    I3=I2+(I2-I1)/3;
    printf("Po formule korrekzii  %.7f\n\n\n",I3);
    getch();
}
