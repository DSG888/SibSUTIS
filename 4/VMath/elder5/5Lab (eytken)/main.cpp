#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cmath>

using namespace std;

int i, j, n = 4, l, k;
double xmas[25], y[25], p[25], p1[25], p2[25], x, t;

double function( double t) {
	t = cos(t);
	return t;
}

int main()
{
cout << "******Эйткен*********" << endl;
cout << "Функция Cos(x)" << endl;
	
cout << "Введите значения узлов [x0,x1,x2,x3]" << endl;
	for(i = 0; i < n; ++i){
		scanf("%lf", &xmas[i]);
	}

cout << "\nВведите искомый x" << endl;
	scanf("%lf", &x);


for(i = 0; i < n; ++i){
	y[i] = function(xmas[i]);
}	

for(k = 0;k < n - 1; ++k){
l = k + 1;
p[k] = ((y[k] * (x - xmas[l]) - y[l] * (x - xmas[k])) / (xmas[k] - xmas[l]));
}


for(k = 0;k < n - 2; ++k){
l = k + 2;
p1[k] = ((p[k] * (x - xmas[l]) - p[k+1] * (x - xmas[k])) / (xmas[k] - xmas[l]));
}

for(k = 0;k < n - 3 ; ++k){
l = k + 3;
p2[k] = ((p1[k] * (x - xmas[l]) - p1[k+1] * (x - xmas[k])) / (xmas[k] - xmas[l]));
}

// вывод

for(i = 0; i < n -1; ++i){
	printf("\n%lf", p[i]);
}
printf("\n______________");

for(i = 0; i < n -2; ++i){
	printf("\n%lf", p1[i]);
}

printf("\n______________");

for(i = 0; i < n -3; ++i){
	printf("\n%lf", p2[i]);
}
return 0;
}

