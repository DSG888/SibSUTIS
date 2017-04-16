#include<stdio.h>
#include<math.h>

#define A 2
#define B 3
#define E 0.001

float funct(float x){
	return pow(x,2)-x-3;	
}
float prfunct(float x){
	return 2*x -1;
}

void pol(float *a, float *b, float c){
	if(funct(*a)*funct(c) < 0)
		*b = c;
	else
		if(funct(c)*funct(*b) < 0)
			*a = c;
}

int main(){

	float a=A, b=B, c;
	// Ìועמה ÌÏÄ
	printf("Metod MPD\n");
	while(1){
		c = (a+b)/2;
		pol(&a,&b,c);
		if((b-a)/2 < E)
			break;
		
	}
	printf("Otvet = %f\n",c);
	// Ìועמה Õמנהא
	a = A; b = B;
	printf("Metod Hord\n");
	float tmpC=0;
	while(1){
		c = (funct(a)*a-funct(b)*b)/(funct(a)-funct(b));
		if(fabs(tmpC-c) < E)
			break;
		pol(&a,&b,c);
		tmpC = c;
	}
	printf("Otvet = %f\n",c);
	// Ìועמה Íü‏עמם
	printf("Metod Newton\n");
	float tmpB = b;
	tmpC = tmpB;
	while(1){
		c = tmpC - funct(tmpC)/prfunct(tmpC);
		if(fabs(tmpC - c) < E)
			break;
	}
	printf("Otvet = %f",c);
		
	printf("\n");
	system("pause");
	return 0;
}
