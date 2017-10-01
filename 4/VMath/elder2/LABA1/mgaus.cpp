#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
FILE *fl;

float mx[SIZE][SIZE], rs[SIZE];

void print() {
	int i, j;
	printf("Your matrix:\n");
	for(i=0; i<SIZE-1; i++) {
   		for(j=0; j<SIZE; j++)
			printf("%.2f\t", mx[i][j]);
		putchar('\n');
	}
}

void input() {
	int i, j;
	if (!(fl=fopen("input.txt", "r"))){
   		printf("File input.txt not exist!\n");
		exit(0);
	}
	for(i=0; i<SIZE; i++)
   		for(j=0; j<SIZE; j++)
			fscanf(fl, "%f", &mx[i][j]);
	fclose(fl);
}

void gssfrwmd() {
	int i, j, k, imd;
	float mr ,a ,b;
	for(i=0; i<SIZE-2; i++) {
		imd=0;
		mr=0.0;
		for(k=i+1; k<SIZE-1; k++){
			if(mx[i][i]<0.0)a=-mx[i][i];
		      	else a=mx[i][i];
		    if(mx[k][i]<0.0)b=-mx[k][i];
			 	else b=mx[k][i];
      		if(a<b && b>mr){
         		mr=b;
				imd=k;
        }
	}

    if(imd!=0 && mr!=0.0){
		printf("\nSwitch %d and %d strings\n", i, imd);
      	for(k=0; k<SIZE; k++){
         	a=mx[i][k];
            mx[i][k]=mx[imd][k];
            mx[imd][k]=a;
        }
    }

   	for(j=i+1; j<SIZE; j++)
   		if((mr=-(mx[j][i]/mx[i][i])))
         	for(k=i; k<SIZE; k++)mx[j][k]+=mr*mx[i][k];
		print();
    }
}

void gssbkw() {
	int i, j;
	for(i=SIZE-2; i>-1; i--){
		for(rs[i]=mx[i][SIZE-1], j=SIZE-2; j>i; j--) 
			rs[i]-=mx[i][j]*rs[j];
		rs[i]/=mx[i][i];
    }
	putchar('\n');
	for(i=1; i<SIZE; i++)
		printf("x%d: %f\n", i, rs[i-1]);
}

int main() {
   input();
   print();
   gssfrwmd();
   gssbkw();
   getchar();
   return 0;
}