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


double simp(float h) {
    double t,I,c,n,M1=0,M2=0;
    int i;
    c=(b-a)/h;
    n=c;
    for (i=1; i<=n; i+=2) {
        t=a+i*h;
        M1+=f(t);
    }
    for (i=2; i<n; i+=2) {
        t=a+i*h;
        M2+=f(t);
    }
    I=h/3*(f(a)+f(b) + 4*M1+ 2*M2);
    return I;
}
int main() {
    int i,j,n,c;
    float H,h;
    double I1,I2,I3;
    printf("Formula Simpsona\n\n\n");
    printf("Raschet po formule simpsona %.7f\n\n",simp(h0));
    H=h0;
    I2=simp(H);
    do {
        I1=I2;
        I2=simp(H/2);
        H=H/2;
    } while((I1-I2)>(15*E));
    printf("Po formule nerescheta  %.7f\n",I2);
    I3=I2+(I2-I1)/15;
    printf("Po formule korrekcii   %.7f",I3);
    getch();
}
