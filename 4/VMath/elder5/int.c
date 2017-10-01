#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double eps = 0.00001;
double a = 1;
double b = 2;


double f(double x) {
	return 1/x;
}

int main() {    
    int i;
	double x, y, step = 0.1, delta, oldy;
	printf ("a = %lf\nb = %lf\nШаг = %.1lf\n", a, b, step);
    printf ("\nФормула трапеции:\n");

	/*a1 = a;
	count = 0;
	while (a1 < b){
		count = count + (f(a1) + f(a1 + step)) / 2;
		//printf("count = %lf ", count);
		a1 = a1 + step;
		//printf("a1 = %lf\n", a1);
	}
	y = step * count; */
	

	
	y = (f(a) + f(b)) / 2;
	x = a + step;
	for (i = 1; x < b; x = a + step * i) {
		i++;	
		y = y + f(x);
	}
	y = y * step;
	printf("Ответ: %lf\n", y);
	printf("\n");
	
    printf("Двойной пересчет:\n");
    delta = y;
	while (delta > eps) {
        //printf("delta: %.6f\n", delta);
		oldy = y;
		step = step / 2;
		y = (f(a) + f(b)) / 2;
		x = a + step;
		for (i = 1; x < b; x = a + step * i) {
			i++;	
			y = y + f(x);
		}
		y = y * step;
		delta = fabs(oldy - y);
		printf("Интеграл равен: %.6f, delta: %.6f\n", y, delta);
	}
	

	step = 0.1;
    printf("\n\nФормула Cимпсона:\n");
	printf ("a = %lf\nb = %lf\nШаг = %.1lf\n", a, b, step);

	
	y = 0;
    y = f(a) + f(b);

	x = a + step;
	for (i = 1; x < b;  x = a + step * i) {
		y = y + f(x) * 4; 
		i = i + 2;
	}
	
	x = a + step * 2;
	for (i = 2; x < b - step; x = a + step * i) {
		y = y + f(x) * 2;
		i = i + 2;
		}
	y = y * (step / 3);
	printf("Интеграл равен: %.6f\n\n",y);
	
	printf("Двойной пересчет:\n");
	delta = y;
	while (delta > eps){
		oldy = y;
		step = step / 2;
		y = f(a) + f(b);

		x = a + step;
		for (i = 1; x < b;  x = a + step * i) {
			y = y + f(x) * 4; 
			i = i + 2;
		}
	
		x = a + step * 2;
		for (i = 2; x < b - step; x = a + step * i) {
			y = y + f(x) * 2;
			i = i + 2;
		}
		y = y * (step / 3);
		delta = fabs(oldy - y);
		printf("Интеграл равен: %.6f, delta: %.6f\n", y, delta);
	} 
    return 0;
} 
