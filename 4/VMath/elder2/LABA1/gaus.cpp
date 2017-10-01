#include <stdio.h>


#define W 4
#define H 3
float mas[H][W] = {
	2,1,-3,-4,
	-4,1,4,4,
	6,-2,-3,0
};
float x[W-1];


int main(int argc, char* argv[]) {
	int i,j;
	int k=0;
	float d;

	puts("before:");
	for(i=0;i<H;i++) {
		for(j=0;j<W;j++)
			printf("%.2f ", mas[i][j]);
		printf("\n");
	}

	// p
	for(i=0; i<W-1; i++) {
		for(j=i+1; j<H;j++) {
			d = - mas[i][i] / mas[j][i];
			for(k=0; k<W; k++)
				mas[j][k] = mas[i][k] + mas[j][k] * d; 
		}
	}

	puts("after:");
	for(i=0;i<H;i++) {
		for(j=0;j<W;j++)
			printf("%f ", mas[i][j]);
		printf("\n");
	}

	// o
	for(i=H-1; i>=0; i--) {
		d = mas[i][W-1];
		for(j=i+1; j<W; j++)
			d -= mas[i][j] * x[j];
		x[i] = d / mas[i][i];
		printf("%d = %f\n", i, x[i]);
	}
	return 1;
}