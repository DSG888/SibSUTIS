#include <stdio.h>
#include <conio.h>

float a,b, Eps;

float f(float x)
{ 
    return (x*x*x-3*x); 
}
float kof(float par)
{ 
    return (par*0.39); 
}

int main()
{ 
    float x1, x2, f_1, f_2;
    printf("VVEDITE OTREZOK [a,b]:\n");
    printf("  a=");  scanf("%f", &a);
    printf("  b=");  scanf("%f", &b);
    printf("VVEDITE TOCHNOST Eps:\n");
    printf("  Eps=");  scanf("%f", &Eps);

    x1=a+kof(b-a);
    x2=b-kof(b-a);
    f_1=f(x1);  
    f_2=f(x2);
    while((b-a)>=Eps) 
    {
        if(f_1<f_2)  
        {
            b=x2; 
            f_2=f_1;
            x1=a+kof(b-a);
            x2=b-kof(b-a);
            f_1=f(x1); 
        }
        else 
        {
            a=x1; 
            f_1=f_2;
            x1=a+kof(b-a);
            x2=b-kof(b-a);
            f_2=f(x2); 
        }
        
        printf("\nMin f[%.3f]=%.3f", (a+b)/2, f((a+b)/2)); 
    }
    printf("\n\nOTVET:Min f[%.3f]=%.3f", (a+b)/2, f((a+b)/2));
    getch(); 
}
