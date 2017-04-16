#include<stdio.h>
#define n 2

void funct(float *F0, float *F1,float x, float y){
	*F0 = x*x+y*y-8;
	*F1 = x*y-3;
}

void matrica(float *matr, float x, float y){
	*matr = 2*x;   *(matr+1) = 2*y;
	*(matr+4) = y;     *(matr+5) = x;
}


int main(){
	int i, j, k, a, b,step=1;
	float matr[n][n+n], matrob[n][n], x[n],xp[n], F[n], per[n], delit, koof, tmp,E, tmpE[2];
    printf("Vvedite Epsilon: ");
        scanf("%f", &E);
	x[0] = 2;	x[1] = 1;
	printf("\nX0 = %7.1f\nX1 = %7.1f\n", x[0], x[1]);	
//***********************************

do{
	matrica (&matr[0][0], x[0], x[1]);
// обратная матрица 
// приписываем единичную матрицу	
	for(i=0;i<n;i++){
		for(j=n; j<n+n; j++)
			if(i == j-n) matr[i][j] = 1.0;
				else matr[i][j] = 0.0;
	}
/*	for(i=0;i<n;i++){
		for(j=0;j<n+n;j++)
			printf("%7.2f ",matr[i][j]);
		printf("\n");
	}
*/	
// считаем обратную матрицу
	for(i=0; i<n; i++){
		delit = matr[i][i];
		for(j=0; j<n; j++){
			if(i==j) continue;
			koof = matr[j][i]/delit;
			for(k=i; k<n+n; k++){
				matr[j][k] -= matr[i][k]*koof;
				matr[i][k] /= delit;
			}
		}
	}
//***************************
	printf("\nObratnaya:\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			matrob[i][j] = matr[i][j+n];
//			printf("%7.2f ", matrob[i][j]);
		}
//		printf("\n");
	}

	funct(&F[0], &F[1], x[0], x[1]);

// перемножаем матрицы
	xp[0] = x[0]; xp[1] = x[1];
    for(i=0; i<n; i++){
		tmp = 0.0;
		for(j=0; j<n; j++){
 			tmp += matrob[i][j]*F[j];
		}
			x[i] -= tmp;	
    }
    tmpE[0] = fabs(x[0]-xp[0]);
    tmpE[1] = fabs(x[1]-xp[1]);
	printf("\nX0 = %7.12f\nX1 = %7.12f", x[0], x[1]);
    printf("\nstep=%d",step++);	
    tmpE[0] = (tmpE[0] > tmpE[1] ? tmpE[0] : tmpE[1]);
    printf("\nPogrewhost: %f", tmpE[0]);
	printf("\n*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/\n");
}while(tmpE[0] > E);
	getch();
	return 0;
}








































